import { InstanceBase, runEntrypoint, InstanceStatus, combineRgb } from '@companion-module/base'
import WebSocket from 'ws'
import { createHash } from 'node:crypto'
import { upgradeScripts } from './upgrade.js'

// how long to wait for more actions before sending a batch, so actions fired together share one batch
const BATCH_WINDOW_MS = 10
const BATCH_TIMEOUT_MS = 5000
const RECONNECT_MS = 5000
const VARIABLE_ID_REGEX = /^[-a-zA-Z0-9_]+$/

// base64(sha256(text)) - the same derivation StreamControl uses
function sha256Base64(text) {
	return createHash('sha256').update(text, 'utf8').digest('base64')
}

// snapshot values are strings, checkboxes are "1"/"0"
function isTruthy(value) {
	return value === true || value === '1' || value === 'true'
}

// widget types aren't in the snapshot, so guess from the value; a real checkbox or number box always matches
const isCheckboxValue = (value) => value === '0' || value === '1'
const isNumberValue = (value) => /^-?\d+$/.test(value)

/*
	A dropdown of the field ids StreamControl has sent, which also accepts any typed id.
	Typed ids can contain variables.
*/
function idOption(label, choices) {
	return {
		type: 'dropdown',
		label,
		id: 'id',
		default: '',
		choices,
		allowCustom: true,
		tooltip: 'The id of the widget in your StreamControl layout. Pick one StreamControl has sent, or type any id.',
	}
}

class StreamControlInstance extends InstanceBase {
	isInitialized = false
	authed = false
	reauthAttempted = false
	snapshot = {}
	variableIds = new Set()
	fieldIds = new Set()
	queue = []
	flushTimer = null
	pending = new Map()
	batchCounter = 0

	async init(config) {
		this.config = config

		this.initVariables()
		this.initActions()
		this.initFeedbacks()
		this.initPresets()

		this.isInitialized = true
		this.initWebSocket()
	}

	async destroy() {
		this.isInitialized = false
		if (this.reconnect_timer) {
			clearTimeout(this.reconnect_timer)
			this.reconnect_timer = null
		}
		this.closeSocket()
	}

	async configUpdated(config) {
		const oldconfig = { ...this.config }
		this.config = config

		if (oldconfig.host !== config.host || oldconfig.port !== config.port || oldconfig.password !== config.password) {
			this.initWebSocket()
		}
	}

	get canControl() {
		return this.ws?.readyState === WebSocket.OPEN && this.authed
	}

	debug(message) {
		if (this.config.debug_messages) {
			this.log('debug', message)
		}
	}

	send(obj) {
		const text = JSON.stringify(obj)
		this.debug(`Sending message: ${text}`)
		this.ws.send(text, (err) => {
			if (err) this.log('error', `Sending message failed: ${err.message}`)
		})
	}

	maybeReconnect() {
		if (this.isInitialized && this.config.reconnect) {
			if (this.reconnect_timer) clearTimeout(this.reconnect_timer)
			this.reconnect_timer = setTimeout(() => {
				this.initWebSocket()
			}, RECONNECT_MS)
		}
	}

	closeSocket() {
		this.authed = false
		this.failQueued('connection closed')
		if (this.ws) {
			this.ws.removeAllListeners()
			// the socket may still be connecting, and close() would throw an unhandled error then
			this.ws.on('error', () => {})
			this.ws.close(1000)
			delete this.ws
		}
	}

	initWebSocket() {
		if (this.reconnect_timer) {
			clearTimeout(this.reconnect_timer)
			this.reconnect_timer = null
		}
		this.closeSocket()

		const host = (this.config.host || '').trim()
		const port = Number(this.config.port)
		if (!host || !Number.isInteger(port) || port < 1 || port > 65535) {
			this.updateStatus(InstanceStatus.BadConfig, 'Host or port is not defined or invalid')
			return
		}

		this.updateStatus(InstanceStatus.Connecting)

		const url = `ws://${host.includes(':') ? `[${host}]` : host}:${port}`
		const ws = new WebSocket(url)
		this.ws = ws

		ws.on('open', () => {
			this.log('debug', `Connection opened to ${url}`)
			this.reauthAttempted = false
			if (this.config.password) {
				this.updateStatus(InstanceStatus.Connecting, 'Authenticating')
				this.send({ op: 'authRequest' })
			} else {
				this.updateStatus(InstanceStatus.Ok, 'Monitor only (no password set)')
			}
		})

		ws.on('close', (code) => {
			this.log('debug', `Connection closed with code ${code}`)
			if (code === 1008) {
				this.updateStatus(InstanceStatus.BadConfig, 'Closed by StreamControl after too many failed logins')
			} else {
				this.updateStatus(InstanceStatus.Disconnected, `Connection closed with code ${code}`)
			}
			this.authed = false
			this.failQueued('connection closed')
			this.maybeReconnect()
		})

		ws.on('message', this.messageReceivedFromWebSocket.bind(this))

		ws.on('error', (err) => {
			this.log('error', `WebSocket error: ${err.message}`)
		})
	}

	messageReceivedFromWebSocket(data) {
		const text = data.toString()
		this.debug(`Message received: ${text}`)

		let msg
		try {
			msg = JSON.parse(text)
		} catch (e) {
			this.log('warn', `Ignoring message that is not JSON`)
			return
		}
		if (msg === null || typeof msg !== 'object' || Array.isArray(msg)) return

		// messages with an op are control replies, everything else is a snapshot
		switch (msg.op) {
			case undefined:
				this.applySnapshot(msg)
				break
			case 'authChallenge':
				this.handleAuthChallenge(msg)
				break
			case 'authResult':
				this.handleAuthResult(msg)
				break
			case 'batchResult':
				this.handleBatchResult(msg)
				break
			case 'error':
				this.handleError(msg)
				break
			default:
				this.debug(`Ignoring unknown op '${msg.op}'`)
		}
	}

	handleAuthChallenge(msg) {
		const secret = sha256Base64(`${this.config.password}${msg.salt}`)
		this.send({ op: 'auth', auth: sha256Base64(`${secret}${msg.challenge}`) })
	}

	handleAuthResult(msg) {
		if (msg.ok) {
			this.authed = true
			this.reauthAttempted = false
			this.updateStatus(InstanceStatus.Ok)
			this.log('info', 'Authenticated with StreamControl')
		} else {
			// don't retry on our own: StreamControl closes the socket after 5 failures
			this.authed = false
			this.updateStatus(InstanceStatus.BadConfig, `Authentication failed: ${msg.error || 'unknown error'}`)
			this.log('error', `Authentication failed: ${msg.error || 'unknown error'}`)
		}
	}

	handleError(msg) {
		this.log('warn', `StreamControl error: ${msg.error}`)
		if (msg.error === 'not authenticated') {
			// the control password changed in StreamControl; any batch in flight won't get a reply
			this.authed = false
			this.failPending('not authenticated')
			if (this.config.password && !this.reauthAttempted) {
				this.reauthAttempted = true
				this.updateStatus(InstanceStatus.Connecting, 'Authenticating')
				this.send({ op: 'authRequest' })
			} else {
				this.updateStatus(InstanceStatus.BadConfig, 'Not authenticated')
			}
		} else if (msg.error === 'remote control is disabled') {
			this.authed = false
			this.updateStatus(InstanceStatus.BadConfig, 'Remote control is disabled in StreamControl')
		}
	}

	// ── Values / variables ──────────────────────────────────────────

	applySnapshot(snapshot) {
		this.snapshot = snapshot
		const ids = Object.keys(snapshot).filter((id) => id !== 'timestamp')
		if (ids.some((id) => !this.fieldIds.has(id))) {
			for (const id of ids) this.fieldIds.add(id)
			// dropdown choices are fixed when defined, so redefine them with the new ids
			this.initActions()
			this.initFeedbacks()
		}
		this.updateVariableValues(Object.keys(snapshot))
	}

	fieldChoices(filter = () => true) {
		return [...this.fieldIds]
			.filter((id) => filter(this.snapshot[id]))
			.sort()
			.map((id) => ({ id, label: id }))
	}

	setLocalValue(id, value) {
		this.snapshot[id] = typeof value === 'boolean' ? (value ? '1' : '0') : `${value}`
	}

	updateVariableValues(ids) {
		let newIds = false
		const values = { lastUpdate: Date.now() }
		for (const id of ids) {
			if (!VARIABLE_ID_REGEX.test(id)) continue
			if (!this.variableIds.has(id)) {
				this.variableIds.add(id)
				newIds = true
			}
			const value = this.snapshot[id]
			values[id] = typeof value === 'object' ? JSON.stringify(value) : value
		}
		if (newIds) this.initVariables()
		this.setVariableValues(values)
		this.checkFeedbacks('field_equals', 'checkbox_checked')
	}

	initVariables() {
		const variableDefinitions = [{ name: 'Timestamp when values last changed', variableId: 'lastUpdate' }]
		for (const id of [...this.variableIds].sort()) {
			variableDefinitions.push({ name: id, variableId: id })
		}
		this.setVariableDefinitions(variableDefinitions)
	}

	// ── Batching ────────────────────────────────────────────────────

	/*
		Queues actions to be sent with any others fired at the same time.
		build is an async function returning the actions, or null to send nothing. The caller's
		place in the batch is reserved before build runs, so actions keep the order Companion
		fired them in however long their variables take to parse.
		Resolves with this caller's slice of the batch results.
	*/
	queueActions(build, save = false) {
		if (!this.canControl) {
			const reason = this.config.password ? 'not connected or not authenticated' : 'no control password set'
			this.log('error', `Cannot send to StreamControl: ${reason}`)
			return Promise.resolve([])
		}

		return new Promise((resolve, reject) => {
			const caller = { actions: [], save, resolve, reject }
			caller.ready = Promise.resolve()
				.then(build)
				.then(
					(actions) => {
						if (actions) caller.actions = actions
						else caller.save = false
					},
					(err) => {
						caller.save = false
						this.log('error', `Action failed: ${err.message}`)
					},
				)
			this.queue.push(caller)
			if (!this.flushTimer) {
				this.flushTimer = setTimeout(() => this.flush(), BATCH_WINDOW_MS)
			}
		})
	}

	async flush() {
		const callers = this.queue
		this.queue = []
		await Promise.all(callers.map((caller) => caller.ready))
		// later actions queue up for the next batch while this one waits on variables
		this.flushTimer = null
		if (this.queue.length > 0) {
			this.flushTimer = setTimeout(() => this.flush(), BATCH_WINDOW_MS)
		}

		if (callers.every((caller) => caller.actions.length === 0 && !caller.save)) {
			for (const caller of callers) caller.resolve([])
			return
		}

		if (!this.canControl) {
			for (const caller of callers) caller.reject(new Error('not connected or not authenticated'))
			return
		}

		// only one save per batch, and always last so it captures every change
		const actions = []
		let save = false
		for (const caller of callers) {
			caller.offset = actions.length
			for (const action of caller.actions) {
				if (action?.action === 'save') {
					save = true
				} else {
					actions.push(action)
				}
			}
			caller.count = actions.length - caller.offset
			if (caller.save) save = true
		}
		if (save) actions.push({ action: 'save' })

		const id = `companion-${++this.batchCounter}`
		const timer = setTimeout(() => {
			this.pending.delete(id)
			this.log('error', `No reply from StreamControl for batch ${id}`)
			for (const caller of callers) caller.reject(new Error('batch timed out'))
		}, BATCH_TIMEOUT_MS)
		this.pending.set(id, { actions, callers, timer })

		this.send({ op: 'batch', id, actions })
	}

	handleBatchResult(msg) {
		const batch = this.pending.get(msg.id)
		if (!batch) return
		this.pending.delete(msg.id)
		clearTimeout(batch.timer)

		const results = Array.isArray(msg.results) ? msg.results : []
		const changedIds = []
		batch.actions.forEach((action, i) => {
			const result = results[i]
			if (!result) return
			if (!result.ok) {
				this.log('warn', `${action?.action}${action?.id ? ` '${action.id}'` : ''} failed: ${result.error}`)
			} else if (action?.action === 'set') {
				// snapshots only come on save, so track what we set to keep variables and adjust/toggle current
				this.setLocalValue(action.id, action.value)
				changedIds.push(action.id)
			}
		})
		if (changedIds.length > 0) this.updateVariableValues(changedIds)

		for (const caller of batch.callers) {
			caller.resolve(results.slice(caller.offset, caller.offset + caller.count))
		}
	}

	failPending(reason) {
		for (const batch of this.pending.values()) {
			clearTimeout(batch.timer)
			for (const caller of batch.callers) caller.reject(new Error(reason))
		}
		this.pending.clear()
	}

	failQueued(reason) {
		if (this.flushTimer) {
			clearTimeout(this.flushTimer)
			this.flushTimer = null
		}
		for (const caller of this.queue) caller.reject(new Error(reason))
		this.queue = []
		this.failPending(reason)
	}

	// ── Config ──────────────────────────────────────────────────────

	getConfigFields() {
		return [
			{
				type: 'static-text',
				id: 'info',
				width: 12,
				label: 'Information',
				value:
					"Enable the WebSocket server in StreamControl's Configuration. To control StreamControl, set a <strong>Control Password</strong> there and enter the same password here. Without a password the module only reads values.",
			},
			{
				type: 'textinput',
				id: 'host',
				label: 'Host',
				tooltip: 'IP address or host name of the computer running StreamControl',
				width: 8,
				default: '127.0.0.1',
			},
			{
				type: 'number',
				id: 'port',
				label: 'Port',
				width: 4,
				default: 41236,
				min: 1,
				max: 65535,
			},
			{
				type: 'textinput',
				id: 'password',
				label: 'Control Password',
				tooltip: "The Control Password from StreamControl's Configuration. Leave blank to only read values.",
				width: 12,
				default: '',
			},
			{
				type: 'checkbox',
				id: 'reconnect',
				label: 'Reconnect',
				tooltip: 'Reconnect when the connection drops (after 5 secs)',
				width: 6,
				default: true,
			},
			{
				type: 'checkbox',
				id: 'debug_messages',
				label: 'Debug messages',
				tooltip: 'Log incoming and outgoing messages',
				width: 6,
				default: false,
			},
		]
	}

	// ── Feedbacks ───────────────────────────────────────────────────

	initFeedbacks() {
		this.setFeedbackDefinitions({
			field_equals: {
				type: 'boolean',
				name: 'Field equals value',
				description: 'Active while a StreamControl field has the given value',
				defaultStyle: {
					bgcolor: combineRgb(0, 153, 51),
					color: combineRgb(255, 255, 255),
				},
				options: [
					idOption('Field ID', this.fieldChoices()),
					{
						type: 'textinput',
						label: 'Value',
						id: 'value',
						default: '',
						useVariables: true,
					},
				],
				callback: async (feedback, context) => {
					const id = await context.parseVariablesInString(feedback.options.id)
					const value = await context.parseVariablesInString(feedback.options.value)
					return id in this.snapshot && `${this.snapshot[id]}` === value
				},
			},
			checkbox_checked: {
				type: 'boolean',
				name: 'Checkbox is checked',
				description: 'Active while a StreamControl checkbox is ticked',
				defaultStyle: {
					bgcolor: combineRgb(0, 153, 51),
					color: combineRgb(255, 255, 255),
				},
				options: [idOption('Checkbox ID', this.fieldChoices(isCheckboxValue))],
				callback: async (feedback, context) => {
					const id = await context.parseVariablesInString(feedback.options.id)
					return isTruthy(this.snapshot[id])
				},
			},
		})
	}

	// ── Actions ─────────────────────────────────────────────────────

	initActions() {
		const fields = this.fieldChoices()
		const checkboxes = this.fieldChoices(isCheckboxValue)
		const numbers = this.fieldChoices(isNumberValue)
		const saveOption = {
			type: 'checkbox',
			label: 'Save afterwards',
			id: 'save',
			default: false,
			tooltip: 'Save once every action fired together has run, so overlays update',
		}

		this.setActionDefinitions({
			set_field: {
				name: 'Set field value',
				description:
					'Set a text field, dropdown, radio group or number box. The value is not checked here; StreamControl reports invalid values in the log.',
				options: [
					idOption('Field ID', fields),
					{
						type: 'textinput',
						label: 'Value',
						id: 'value',
						default: '',
						useVariables: true,
					},
					saveOption,
				],
				callback: (action, context) =>
					this.queueActions(async () => {
						const id = await context.parseVariablesInString(action.options.id)
						const value = await context.parseVariablesInString(action.options.value)
						return [{ action: 'set', id, value }]
					}, action.options.save),
			},

			set_checkbox: {
				name: 'Set checkbox',
				options: [
					idOption('Checkbox ID', checkboxes),
					{
						type: 'dropdown',
						label: 'State',
						id: 'state',
						default: 'true',
						choices: [
							{ id: 'true', label: 'Checked' },
							{ id: 'false', label: 'Unchecked' },
						],
					},
					saveOption,
				],
				callback: (action, context) =>
					this.queueActions(async () => {
						const id = await context.parseVariablesInString(action.options.id)
						return [{ action: 'set', id, value: action.options.state === 'true' }]
					}, action.options.save),
			},

			toggle_checkbox: {
				name: 'Toggle checkbox',
				options: [idOption('Checkbox ID', checkboxes), saveOption],
				callback: (action, context) =>
					this.queueActions(async () => {
						const id = await context.parseVariablesInString(action.options.id)
						return [{ action: 'set', id, value: !isTruthy(this.snapshot[id]) }]
					}, action.options.save),
			},

			adjust_number: {
				name: 'Increase / decrease number',
				description: 'Add to a number box, e.g. a score. Starts from the last value the module knows about.',
				options: [
					idOption('Number box ID', numbers),
					{
						type: 'number',
						label: 'Amount (negative to decrease)',
						id: 'delta',
						default: 1,
						min: -1000,
						max: 1000,
					},
					saveOption,
				],
				callback: (action, context) =>
					this.queueActions(async () => {
						const id = await context.parseVariablesInString(action.options.id)
						const current = parseInt(this.snapshot[id], 10)
						const value = (Number.isNaN(current) ? 0 : current) + Number(action.options.delta)
						return [{ action: 'set', id, value }]
					}, action.options.save),
			},

			press_button: {
				name: 'Press button',
				description: 'Press a reset, swap, timestamp or set button',
				options: [idOption('Button ID', []), saveOption],
				callback: (action, context) =>
					this.queueActions(async () => {
						const id = await context.parseVariablesInString(action.options.id)
						return [{ action: 'press', id }]
					}, action.options.save),
			},

			save: {
				name: 'Save',
				description: 'Write the output files and update overlays',
				options: [],
				callback: () => this.queueActions(async () => [{ action: 'save' }]),
			},

			raw_batch: {
				name: 'Send raw actions',
				description:
					'Send a JSON array of StreamControl actions, e.g. [{"action":"set","id":"pName1","value":"Daigo"}]',
				options: [
					{
						type: 'textinput',
						label: 'Actions (JSON array)',
						id: 'actions',
						default: '[]',
						useVariables: true,
					},
					saveOption,
				],
				callback: (action, context) =>
					this.queueActions(async () => {
						const text = await context.parseVariablesInString(action.options.actions)
						let actions
						try {
							actions = JSON.parse(text)
						} catch (e) {
							this.log('error', `Raw actions are not valid JSON: ${e.message}`)
							return null
						}
						if (!Array.isArray(actions)) {
							this.log('error', 'Raw actions must be a JSON array')
							return null
						}
						return actions
					}, action.options.save),
			},
		})
	}

	// ── Presets ─────────────────────────────────────────────────────

	initPresets() {
		this.setPresetDefinitions({
			save: {
				type: 'button',
				category: 'General',
				name: 'Save',
				style: {
					text: 'SAVE',
					size: '18',
					color: combineRgb(255, 255, 255),
					bgcolor: combineRgb(0, 0, 0),
				},
				steps: [{ down: [{ actionId: 'save', options: {} }], up: [] }],
				feedbacks: [],
			},
		})
	}
}

runEntrypoint(StreamControlInstance, upgradeScripts)
