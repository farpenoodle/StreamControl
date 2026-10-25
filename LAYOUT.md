# Layout XML Reference

StreamControl's UI is defined by a layout XML file that you point at via **Configuration → Layout XML**. The file describes the size of the main window, the form widgets you want, an optional toolbar, optional tabs, and an optional CLI hook section. Each interactive widget has an `id` that becomes a key in `streamcontrol.xml` / `streamcontrol.json` / the WebSocket payload.

A working example you can read alongside this doc: [`examples/scoreflags/scoreflags.xml`](examples/scoreflags/scoreflags.xml).

## Document structure

```xml
<!DOCTYPE StreamControlLayout>
<layout width="390" height="140" [tabbed="1"] [fontSize="12"]>
  <toolBar> ... </toolBar>            <!-- optional -->
  <!-- widgets, or <tab>s if tabbed="1" -->
  <cli> ... </cli>                    <!-- optional -->
</layout>
```

### `<layout>` attributes

| Attribute  | Required | Notes |
|------------|----------|-------|
| `width`    | yes      | Window width in pixels. |
| `height`   | yes      | Window height in pixels. |
| `tabbed`   | no       | If `"1"`, the top-level children must be `<tab>` elements that get placed in a tab widget. |
| `fontSize` | no       | Base font size used as the default for child widgets. |

## Geometry

Every interactive element accepts:

| Attribute  | Required | Notes |
|------------|----------|-------|
| `x`, `y`   | yes      | Position in pixels relative to the containing tab / panel. |
| `width`, `height` | yes | Size in pixels. |
| `fontSize` | no       | Overrides the layout's base size. `0` (or omitted) inherits. |

`<radioButton>` children inside a `<radioGroup>` also carry their own geometry — see below.

## Top-level widgets

All of these are valid as children of `<layout>` (or `<tab>` / `<tabSet>` — see "Tabs"). Each one's value is keyed by its `id` in the saved output.

### `<label>`

Static text on the form.

```xml
<label x="10" y="14" width="46" height="13">Title 1</label>
```

No `id`. Text content is the label.

### `<line>`

Horizontal/vertical separator. No content, no `id`.

```xml
<line x="10" y="30" width="370" height="2"/>
```

### `<lineEdit>`

Single-line text input.

| Attribute   | Required | Notes |
|-------------|----------|-------|
| `id`        | yes      | Output key. |
| `dataSet`   | no       | CSV file (relative to the layout) used for autocomplete. |
| `dataField` | no       | 1-indexed column to pull from `dataSet`. Default `1`. |
| `master`    | no       | Another widget's `id`; selecting a value there auto-fills this field from the same row of `dataSet`. |
| `noSave`    | no       | `"1"` to keep this field out of the dataset's saved entries. |

Text content is used as placeholder/initial text.

```xml
<lineEdit id="pName1" x="10" y="10" width="160" height="20" dataSet="players.csv">Player 1</lineEdit>
<lineEdit id="pCountry1" x="180" y="10" width="50" height="20"
          dataSet="players.csv" dataField="2" master="pName1">Country</lineEdit>
```

### `<spinBox>`

Integer input.

| Attribute        | Required | Notes |
|------------------|----------|-------|
| `id`             | yes      | Output key. |
| `maximum`        | no       | Upper bound. |
| `increaseHotkey` | no       | Global hotkey string to increment. |
| `decreaseHotkey` | no       | Global hotkey string to decrement. |

```xml
<spinBox id="pScore1" x="240" y="10" width="40" height="22" maximum="999"/>
```

### `<checkBox>`

| Attribute       | Required | Notes |
|-----------------|----------|-------|
| `id`            | yes      | Output key (`"1"` / `"0"`). |
| `toggleHotkey`  | no       | Hotkey to flip state. |
| `checkHotkey`   | no       | Hotkey that forces checked. |
| `uncheckHotkey` | no       | Hotkey that forces unchecked. |

Text content is the label next to the box.

### `<comboBox>`

Drop-down. Children are `<comboItem>` elements.

| Attribute       | Required | Notes |
|-----------------|----------|-------|
| `id`            | yes      | Output key. |
| `editable`      | no       | `"1"` allows free-text entry. |
| `dataSet`       | no       | Same as `<lineEdit>`. |
| `dataField`     | no       | Same as `<lineEdit>`. |
| `master`        | no       | Same as `<lineEdit>`. |
| `nextHotkey`    | no       | Hotkey to cycle to next item. |
| `previousHotkey`| no       | Hotkey to cycle to previous item. |

`<comboItem>` children:

| Attribute  | Required | Notes |
|------------|----------|-------|
| `value`    | no       | Stored value. Defaults to the text content. |
| `selected` | no       | `"true"` to make this the default item. |

```xml
<comboBox id="round" x="10" y="10" width="120" height="22">
  <comboItem value="WF">Winners Final</comboItem>
  <comboItem value="LF" selected="true">Losers Final</comboItem>
  <comboItem value="GF">Grand Final</comboItem>
</comboBox>
```

### `<radioGroup>`

| Attribute | Required | Notes |
|-----------|----------|-------|
| `id`      | yes      | Output key — set to the selected `<radioButton>`'s `value`. |

Children are `<radioButton>` elements with their own geometry:

```xml
<radioGroup id="side">
  <radioButton x="10" y="10" width="60" height="20" value="P1">Player 1</radioButton>
  <radioButton x="80" y="10" width="60" height="20" value="P2">Player 2</radioButton>
</radioGroup>
```

### `<button>`

Buttons don't write a value to the output; they perform an action. The action depends on `type`.

| Attribute  | Required | Notes |
|------------|----------|-------|
| `type`     | yes      | `reset`, `swap`, `timestamp`, or `setButton`. |
| `id`       | yes      | Internal identifier. |
| `tooltip`  | no       | Hover text. |
| `hotkey`   | no       | Global hotkey to trigger the click. |
| `saveonclick` | no    | `"1"` saves immediately after the click (timestamp / setButton). |

Per-type attributes:

- **`type="reset"`** — clears one or more fields. Required: `reset="id1,id2,..."` (CSV of widget IDs).
- **`type="swap"`** — swaps values between two field sets. Required: `swapSet1="..."` and `swapSet2="..."` (matching CSV lists).
- **`type="timestamp"`** — writes the current time to a paired widget identified by the button's `id`.
- **`type="setButton"`** — forces a widget to a value. Required: `widget="targetId"`, `value="..."`.

Text content is the button label.

```xml
<button type="reset" x="290" y="10" width="40" height="23"
        id="clear1" tooltip="Clear Player 1" reset="pName1,pCountry1">Clear</button>

<button type="swap" x="330" y="40" width="40" height="23"
        id="swap" swapSet1="pName1,pScore1,pCountry1"
        swapSet2="pName2,pScore2,pCountry2">Swap</button>
```

### `<tweet>`

Twitter compose widget.

| Attribute     | Required | Notes |
|---------------|----------|-------|
| `id`          | yes      | Output key prefix. |
| `picPath`     | no       | Subfolder for downloaded media. Defaults to `twitter`. |
| `embedJSON`   | no       | `"1"` embeds the raw tweet JSON in the output. |

### `<challonge>` and `<smashgg>`

Bracket-provider widgets that pull match data from Challonge or smash.gg.

Common attributes (all required unless noted): `id`, `playerOneWidget`, `playerTwoWidget`, `tournamentStageWidget`, `bracketWidget`, `outputType`, `outputFileName`. Optional: `playerOneCountryWidget`, `playerTwoCountryWidget`, `clearWidgets` (CSV of widget IDs to wipe between matches).

Nested stage elements (`<grandFinal>`, `<winnersFinal>`, `<losersFinal>`, …) configure label overrides per bracket stage.

## Tabs

Two ways to use tabs:

**1. Whole layout is tabbed.** Set `tabbed="1"` on `<layout>` and make every child a `<tab>`:

```xml
<layout width="390" height="140" tabbed="1">
  <tab name="Match Info"> ... widgets ... </tab>
  <tab name="Commentary"> ... </tab>
</layout>
```

**2. A tabbed panel inside a non-tabbed layout.** Use a `<tabSet>` with its own geometry:

```xml
<tabSet x="10" y="50" width="370" height="80">
  <tab name="Page 1"> ... </tab>
  <tab name="Page 2"> ... </tab>
</tabSet>
```

`<tab>` attributes:

| Attribute    | Required | Notes |
|--------------|----------|-------|
| `name`       | yes      | Tab label. |
| `scrollable` | no       | `"1"` wraps the tab in a scroll area. |

## `<toolBar>`

A horizontal bar across the top, useful for stream-wide state (event name, round selector). Children are laid out left-to-right; no geometry attributes on the children.

Allowed children: `<label>`, `<comboBox>`, and `<button type="setButton" ...>`.

```xml
<toolBar>
  <label>Event:</label>
  <comboBox id="eventName" editable="1">
    <comboItem>Weekly #1</comboItem>
    <comboItem>Majors</comboItem>
  </comboBox>
</toolBar>
```

## `<cli>`

Run external commands when you hit Save. Variables from any widget can be interpolated with `[$id]` or `[$id.field]` for dataset columns.

```xml
<cli>
  <cmd>notify-send "Match" "[$pName1] vs [$pName2]"</cmd>
  <cmd ignore="pScore1,pScore2">obs-cli scene "MainCam"</cmd>
</cli>
```

`<cmd>` attributes:

| Attribute | Required | Notes |
|-----------|----------|-------|
| `ignore`  | no       | CSV of widget IDs whose changes should *not* trigger this command. |

## Output mapping

When you Save, every widget with an `id` becomes a key in the output:

| Widget       | JSON value                                    |
|--------------|-----------------------------------------------|
| `lineEdit`   | string                                        |
| `spinBox`    | string (the number)                           |
| `checkBox`   | `"1"` or `"0"`                                |
| `comboBox`   | the selected item's `value` (or its text)    |
| `radioGroup` | the selected `<radioButton>`'s `value`       |
| `tweet`      | tweet text (and JSON if `embedJSON="1"`)     |
| `timestamp` button | writes to a paired field of the same `id` |

A top-level `timestamp` key is always added (seconds since epoch of the save). Static `<label>`, `<line>`, and button widgets do not contribute output.

## Tips

- Keep dataset CSVs next to the layout file so relative paths work.
- IDs are also what the WebSocket payload uses — design them so overlay code can consume them directly (`pName1`, `pScore1`, etc., as in the scoreflags example).
- Hotkeys are Windows-only. The string format is whatever Qt's `QKeySequence` accepts (e.g. `"Ctrl+Shift+R"`).
- When validating your file, StreamControl will pop up specific error messages — the validators are exhaustive (`MainWindow::checkLayout` in `StreamControl/mainwindow.cpp`).
