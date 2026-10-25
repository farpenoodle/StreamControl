scoreflags_ws — WebSocket fork of the scoreflags overlays.

Instead of polling streamcontrol.xml from disk, these overlays connect to StreamControl's
built-in WebSocket server and receive the current JSON payload:
  * Once, immediately on connect (snapshot of the current state).
  * Again every time the user hits Save in StreamControl (broadcast to all clients).

Setup
-----
1. In StreamControl, open Configuration and enable the WebSocket option.
   Set the port (default 41236) and save.
2. Load scoreflags.xml as the layout file.
3. Open ScoreBoard-createjs.html or ScoreBoard-jstween.html in a browser
   (or as a browser source in OBS).
   - If StreamControl is on a different machine, edit the WS_URL constant at the
     top of the <script> block to point at "ws://<host>:<port>".
4. Hit Save in StreamControl to push updates to every connected overlay.

The HTML pages reconnect automatically if the connection drops.

Two versions of the HTML overlays are included, one uses the CreateJS framework
to draw onto a Canvas element for the scoreboard and the other uses plain CSS
with JQuery and a tweening library to draw the scoreboard. The Canvas version
will look better but it might be easier for some to use their web design
knowledge to construct overlays.

Uses Sansation: http://www.dafont.com/sansation.font
