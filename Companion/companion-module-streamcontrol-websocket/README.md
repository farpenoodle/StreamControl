# companion-module-streamcontrol-websocket

Bitfocus Companion module for [StreamControl](https://github.com/farpenoodle/StreamControl). It connects to StreamControl's WebSocket server, logs in with the Control Password, and sets fields, presses buttons and saves. Field values are available as variables.

See [companion/HELP.md](companion/HELP.md) and LICENSE. Based on [companion-module-generic-websocket](https://github.com/bitfocus/companion-module-generic-websocket).

# Version History

### v1.0.0

- Initial release: authentication, set field / checkbox, toggle, increase / decrease, press, save and raw actions, actions fired together grouped into one batch, variables from StreamControl's values, field and checkbox feedbacks, ID dropdowns filled from StreamControl's fields that also accept typed IDs
