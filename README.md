# StreamControl

StreamControl is a Qt 6 desktop app for managing the dynamic text and graphics that appear on a live stream — scores, player names, country flags, commentator credits, tournament round labels, etc. You fill in fields in the app; StreamControl writes the values to disk as XML and/or JSON, and (optionally) broadcasts them over WebSocket. Your stream overlay reads the file or listens on the socket and updates itself.

It was originally built for fighting-game tournaments but the layout is fully data-driven, so it works for any stream that needs an operator-driven scoreboard or lower-third.

## Features

- **Custom layouts** defined in XML — labels, line edits, spin boxes, checkboxes, comboboxes, radio groups, tabbed sections.
- **Outputs** `streamcontrol.xml` and/or `streamcontrol.json` to a configurable directory every time you hit Save.
- **WebSocket server** (built-in) that pushes the JSON payload to every connected overlay the moment you save, plus a fresh snapshot to each client at connect time.
- **Datasets** with autocomplete — reuse player names, sponsors, characters, etc. across sessions.
- **Toolbar** with configurable labels and comboboxes for global state (event name, round number, stream identifier).
- **Reset / swap / timestamp buttons** for one-click match resets, side switches, and time tracking.
- **CLI hooks** — invoke external commands with field values substituted in (useful for triggering OBS scenes, posting to Discord, etc.).
- **Global hotkeys** (Windows) for triggering buttons without focusing the app.
- **Tweet widget** with media download and URL expansion.
- **Challonge widget** for pulling bracket data.
- **Dark mode**, configurable font sizes, optional always-on-top.

## Requirements

- **Qt 6** (tested against 6.3 – 6.11) with the following modules: `core`, `gui`, `widgets`, `xml`, `network`, `websockets`.
- A C++17 compiler. On Windows, MSVC 2019/2022; on Linux, gcc/clang; on macOS, the Xcode toolchain.

## Building

### Windows (Qt Creator)

1. Install Qt 6 and Qt Creator with the MSVC kit.
2. Open `StreamControl/StreamControl.pro` in Qt Creator.
3. Configure with an MSVC 64-bit kit and build (Release or Debug).

### Linux / macOS

```sh
cd StreamControl
qmake
make
```

The binary is placed in the kit's build directory.

## Running

1. Launch `StreamControl`.
2. On first run you'll be prompted to configure. Open **Configuration** and set:
   - **Output path** — where `streamcontrol.xml` / `streamcontrol.json` get written. Point this at the directory your overlay reads from (e.g. your OBS sources folder).
   - **Layout XML** — the file describing the form layout. Use one of the examples (see below) or write your own.
   - **Output format** — XML, JSON, or both.
   - **WebSocket** — enable and pick a port (default `41236`) if you want overlays to receive live pushes instead of polling a file. Optionally set a **Control Password** so trusted clients can drive the app (see [Remote control](#remote-control)).
3. Fill in the fields, hit **Save**, and your overlay updates.

## WebSocket protocol

When WebSocket is enabled, StreamControl listens on the configured port (default `41236`) on all interfaces.

- **On connect:** the server sends a single text frame containing the current StreamControl JSON snapshot to the new client.
- **On save:** the server broadcasts the latest JSON snapshot to every connected client as a text frame.

The payload is identical to what `streamcontrol.json` would contain on disk — a flat JSON object whose keys are the widget IDs from your layout, plus a `timestamp` field. Example client:

```js
const ws = new WebSocket("ws://localhost:41236");
ws.onmessage = (e) => {
  const data = JSON.parse(e.data);
  console.log(data.pName1, data.pScore1, "-", data.pScore2, data.pName2);
};
```

The connection auto-reconnects in the example overlays if dropped.

### Remote control

A client can escalate its connection with the **Control Password** from Configuration. An escalated client can set widget values and press buttons. Control is off while the password is empty. Tick **Disable** to turn it off and keep the password.

The password is saved in plain text in `settings.xml` (`websocketPassword`), so protect that file. It never travels over the socket. Authentication is a challenge–response using the same scheme as obs-websocket v5, with a salt that changes every time StreamControl starts or the password changes:

```
secret = base64(sha256(password + salt))
auth   = base64(sha256(secret + challenge))
```

Control messages are JSON text frames with an `op` field. Replies go only to the client that sent the request, so overlays that just listen never see them.

```
→ {"op":"authRequest"}
← {"op":"authChallenge","salt":"…","challenge":"…"}
→ {"op":"auth","auth":"<base64>"}
← {"op":"authResult","ok":true}
```

Each challenge works for one attempt only, so send a fresh `authRequest` before each try. After 5 failed attempts the server closes the socket (code 1008). Changing the password logs out every escalated client.

Once authenticated, send actions in a batch. They run in order. A failing action is reported, and the rest of the batch still runs.

```json
{"op":"batch","id":"any-id","actions":[
  {"action":"set",   "id":"pName1",  "value":"Daigo"},
  {"action":"set",   "id":"pScore1", "value":2},
  {"action":"set",   "id":"finals",  "value":true},
  {"action":"set",   "id":"game",    "value":"sf6"},
  {"action":"set",   "id":"side",    "value":"right"},
  {"action":"press", "id":"swap1"},
  {"action":"save"}
]}
```

| Action | Applies to | Notes |
|---|---|---|
| `set` | `lineEdit` | Any string. Numbers are converted to text. |
| `set` | `spinBox` | An integer or numeric string. Values outside the box's min/max are rejected. |
| `set` | `checkBox` | `true`/`false`, `1`/`0` or `"1"`/`"0"`. |
| `set` | `comboBox` | Matches an item's `value`, then its text. Editable combos accept any text. |
| `set` | `radioGroup` | A radio button's `value`. |
| `press` | `reset`, `swap`, `timestamp`, `setButton` buttons | Same as clicking the button. A button with `saveonclick` still saves. |
| `save` | — | Same as the toolbar Save button: writes the output files and broadcasts. |

A batch does not save on its own. End it with `{"action":"save"}` when the overlay should update. The reply echoes your `id` and has one result per action:

```json
{"op":"batchResult","id":"any-id","results":[{"ok":true},{"ok":false,"error":"unknown widget 'x'"}]}
```

If the batch saves, the snapshot broadcast reaches you before the `batchResult`. Messages with an `op` field are control replies, and the rest are snapshots. Errors outside a batch come back as `{"op":"error","error":"…"}`: invalid JSON, an unknown `op`, or `batch` before authenticating.

The socket is plain `ws://`. The password is protected, but values sent after authenticating are not encrypted, so only expose the port on networks you trust. `examples/ws_control/control.html` is a small test client. Browsers only allow the hashing it uses (`crypto.subtle`) on `http://localhost` or `https://`, so serve the page from localhost rather than opening it as a `file://`.

## Example overlays

Located under `examples/`:

- **`Basic/`** — Minimal HTML overlays demonstrating field readout.
- **`scoreflags/`** — Fighting-game scoreboard with player names, scores, country flags, and a center text label. Two versions: a CreateJS canvas renderer (`ScoreBoard-createjs.html`) and a jQuery + jsTween DOM renderer (`ScoreBoard-jstween.html`). Polls `streamcontrol.xml` every 250 ms.
- **`scoreflags_ws/`** — Same scoreboard as above, but connects to the WebSocket server and receives pushes on save. Edit the `WS_URL` constant at the top of either HTML file if StreamControl is on a different host.
- **`ws_control/`** — Test client for [remote control](#remote-control): authenticate with the control password and send batch JSON.

Load the example's `.xml` (e.g. `scoreflags.xml`) as the StreamControl layout, then open the matching HTML file as a browser source in OBS / XSplit.

## Project layout

```
StreamControl/        Qt project — source for the desktop app
  *.cpp / *.h         Main app, config window, widgets, websocket server
  dialogs/            Modal dialogs (widget settings, etc.)
  widgets/            Custom Qt widgets (ScRadioGroup, tweet, Challonge, ...)
  StreamControl.pro   qmake project file
examples/             Sample layouts and HTML/JS overlays
changelog.txt         Release notes
LICENSE               License terms
```

## Reporting bugs

File issues at https://github.com/farpenoodle/StreamControl/issues.

## License

See `LICENSE`.
