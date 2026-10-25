## StreamControl

Controls [StreamControl](https://github.com/farpenoodle/StreamControl) through its built-in WebSocket server.

### Setup in StreamControl

1. Open **Configuration** and enable **WebSocket** (default port `41236`).
2. To control StreamControl from Companion, set a **Control Password** (and leave **Disable** unticked). Without a password the module can only read values.

### Configuration

- **Host**: IP address or host name of the computer running StreamControl.
- **Port**: The WebSocket port set in StreamControl.
- **Control Password**: The same password as in StreamControl. The password is never sent over the network; the module logs in with a challenge–response.
- **Reconnect**: Reconnect after 5 seconds when the connection drops.
- **Debug messages**: Log every message sent and received.

If the password is wrong the connection shows _Authentication failed_ and the module does not keep retrying (StreamControl disconnects clients after 5 failed logins). Fix the password to try again.

---

### Actions

Field and button IDs are the `id` attributes from your StreamControl layout. The ID box is a dropdown of the fields StreamControl has sent (it fills in once connected), and you can also type any ID, including variables. Checkbox and number actions only list fields whose current value looks like a checkbox (`0`/`1`) or a whole number. Buttons aren't part of StreamControl's data, so type their IDs.

Every action except **Save** has a **Save afterwards** option (off by default). Without a save, StreamControl's fields change but the output files and overlays only update when you save.

Actions that run at the same time — for example several actions on one button — are sent to StreamControl together as one batch, in order. If any of them asks to save, a single save runs after all of them.

- **Set field value**: Sets a text field, dropdown, radio group or number box. The value is sent as typed; StreamControl rejects invalid values (an unknown dropdown item, a number out of range) and the error appears in the Companion log.
- **Set checkbox**: Ticks or unticks a checkbox.
- **Toggle checkbox**: Flips a checkbox.
- **Increase / decrease number**: Adds an amount (negative to subtract) to a number box, e.g. a score.
- **Press button**: Presses a reset, swap, timestamp or set button, the same as clicking it.
- **Save**: Writes the output files and updates overlays.
- **Send raw actions**: Sends a JSON array of StreamControl actions as-is, e.g. `[{"action":"set","id":"pName1","value":"Daigo"},{"action":"press","id":"swap1"}]`. A `save` in the array always runs at the end of the batch.

**Toggle checkbox** and **Increase / decrease number** start from the last value the module knows: the last save StreamControl broadcast, plus anything set from Companion since. Edits typed into StreamControl are only seen after they are saved.

---

### Feedbacks

- **Field equals value**: Active while a field has the given value (compared as text, e.g. a checkbox is `1` or `0`).
- **Checkbox is checked**: Active while a checkbox is ticked.

---

### Variables

- Every field StreamControl sends becomes a variable named after its ID, e.g. `$(streamcontrol:pName1)`. New variables appear after the first value is received.
- **lastUpdate**: Unix timestamp (ms) of the last change. Changes on every save, even if no value changed.
