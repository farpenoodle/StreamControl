The first thing you need to do before using this if you are using the SWF overlay with XSplit is to copy the GoSquared folder to your XSplit directory. Which is in general "C:\Program Files (x86)\SplitMediaLabs\XSplit"

After that, load scoreflags.xml as the layout file under StreamControl configuration.

(If you're using OBS remember to change the XSplit directory under configuration to where you extracted the SWF or HTML overlays.)

There are two versions of the HTML overlays, one uses the CreateJS framework to draw onto a Canvas element for the scoreboard and the other uses plain CSS with JQuery and a tweening library to draw the scoreboard. The Canvas version will look better but it might be easier for some to use their web design knowledge to construct overlays.

Hopefully these files will give people ideas on how to leverage StreamControl to easily manage their overlays.

Uses Sansation: http://www.dafont.com/sansation.font