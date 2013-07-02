package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
    import flash.events.IOErrorEvent; 
	import flash.display.Bitmap;
	import caurina.transitions.*;
	import caurina.transitions.properties.FilterShortcuts;
	import flash.filters.*;
	import flash.net.URLRequest;
	import flash.net.URLLoader;
	import flash.xml.XMLDocument;
	import flash.text.TextField;
	import flash.display.Loader;
	import isoCountries;
	
	
	public class ScoreBoard extends MovieClip {
		
		var timestampOld:Number;
		var timestamp:Number;
		var pName1:String;
		var pScore1:Number;
		var pName2:String;
		var pScore2:Number;
		var pCountry1:String;
		var pCountry2:String;
		var oldCountry1:String = "";
		var oldCountry2:String = "";
		var mText3:String;
		
		
		var animating:Boolean = false;
		var doUpdate:Boolean = false;
		
		public function ScoreBoard() {
			// constructor code
			
			
			FilterShortcuts.init();
			board.y=-100;
			board.pName1.text = "";
			board.pName2.text = "";
			board.pScore1.text = "";
			board.pScore2.text = "";
			board.pFlag1.alpha = 0;
			board.pFlag2.alpha = 0;
			board.mText3.text = "";
			loadData();
			
			Tweener.addTween(board, {y:0, time:0.8, transition:"easeOut"});
			var poller:Timer = new Timer(250);
			poller.addEventListener(TimerEvent.TIMER, pollHandler);
			poller.start();
		}
		
		function pollHandler(evt:TimerEvent):void
		{
		  loadData();
		  if (timestamp != timestampOld) {
			  doUpdate = true;
		  }
		  if (!animating && doUpdate) {
			  updateBoard();
		  }
		}
		
		public function loadData() {
			var xmlLoader:URLLoader = new URLLoader();
			xmlLoader.addEventListener(Event.COMPLETE, dataLoaded);
			xmlLoader.load(new URLRequest("streamcontrol.xml"));
			
			function dataLoaded(e:Event):void {
				var streamData:XML = new XML(e.target.data);
				pName1 = streamData.elements("pName1");
				pScore1 = streamData.elements("pScore1");
				pName2 = streamData.elements("pName2");
				pScore2 = streamData.elements("pScore2");
				pCountry1 = getCountry(streamData.elements("pCountry1"));
				pCountry2 = getCountry(streamData.elements("pCountry2"));
				mText3 = streamData.elements("mText3");
				timestampOld = timestamp;
				timestamp = streamData.elements("timestamp");
			}
		
		}
		
		public function loadflag1() {
			var flagloader1:Loader = new Loader();
			flagloader1.contentLoaderInfo.addEventListener(Event.COMPLETE, flag1LoaderReady);
			flagloader1.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, flag1noFlag);
			
			var flag1Request:URLRequest = new URLRequest("GoSquared/cropped/iso/64shiny/"+ pCountry1 +".png");
			flagloader1.load(flag1Request);
			
			oldCountry1 = pCountry1;
			
			function flag1LoaderReady(e:Event) {     
				var image:Bitmap = Bitmap(flagloader1.content);
				image.smoothing=true;
				while (board.pFlag1.numChildren > 0) {
    				board.pFlag1.removeChildAt(0);
				}
				board.pFlag1.addChild(image);
				board.pFlag1.width = 43;
				board.pFlag1.height = 28;
				Tweener.addTween(board.pFlag1, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			function flag1noFlag(e:Event) {
				var unknownFlag:unknown = new unknown;
				var image:Bitmap = new Bitmap(unknownFlag);
				image.smoothing=true;
				while (board.pFlag1.numChildren > 0) {
    				board.pFlag1.removeChildAt(0);
				}
				board.pFlag1.addChild(image);
				board.pFlag1.width = 43;
				board.pFlag1.height = 28;
				Tweener.addTween(board.pFlag1, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
		}
		
		public function loadflag2() {
			var flagloader2:Loader = new Loader();
			flagloader2.contentLoaderInfo.addEventListener(Event.COMPLETE, flag2LoaderReady);
			flagloader2.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, flag2noFlag);
			
			var flag2Request:URLRequest = new URLRequest("GoSquared/cropped/iso/64shiny/"+ pCountry2 +".png");
			flagloader2.load(flag2Request);
			
			oldCountry2 = pCountry2;
			
			function flag2LoaderReady(e:Event) {
				var image:Bitmap = Bitmap(flagloader2.content);
				image.smoothing=true;
				while (board.pFlag2.numChildren > 0) {
    				board.pFlag2.removeChildAt(0);
				}
				board.pFlag2.addChild(image);
				board.pFlag2.width = 43;
				board.pFlag2.height = 28;
				Tweener.addTween(board.pFlag2, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			function flag2noFlag(e:Event) {
				var unknownFlag:unknown = new unknown;
				var image:Bitmap = new Bitmap(unknownFlag);
				image.smoothing=true;
				while (board.pFlag2.numChildren > 0) {
    				board.pFlag2.removeChildAt(0);
				}
				board.pFlag2.addChild(image);
				board.pFlag2.width = 43;
				board.pFlag2.height = 28;
				Tweener.addTween(board.pFlag2, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
		}
		
		public function updateBoard() {
			
			if (board.pName1.text != pName1) {
				animating = true;
				var currX:Number = board.pName1.x;
				Tweener.addTween(board.pName1, {x:currX+100,alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {board.pName1.text = pName1;}});
				Tweener.addTween(board.pName1, {x:currX,alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			if (board.pName2.text != pName2) {
				animating = true;
				var currX:Number = board.pName2.x;
				Tweener.addTween(board.pName2, {x:currX-100,alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {board.pName2.text = pName2;}});
				Tweener.addTween(board.pName2, {x:currX,alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			
			if (board.mText3.text != mText3) {
				animating = true;
				var currY:Number = board.mText3.y;
				Tweener.addTween(board.mText3, {y:currY-20,alpha:0,_Blur_blurY: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {board.mText3.text = mText3;}});
				Tweener.addTween(board.mText3, {y:currY,alpha:1,_Blur_blurY: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			
			if (oldCountry1 != pCountry1 || board.pFlag1.alpha == 0) {
				animating = true;
				Tweener.addTween(board.pFlag1, {alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {loadflag1();}});
				
			}
			
						
			if (oldCountry2 != pCountry2 || board.pFlag2.alpha == 0) {
				animating = true;
				Tweener.addTween(board.pFlag2, {alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {loadflag2();}});
				
			}
			
			if (board.pScore1.text != pScore1.toString()) {
				animating = true;
				Tweener.addTween(board.pScore1, {alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {board.pScore1.text = pScore1.toString();}});
				Tweener.addTween(board.pScore1, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			if (board.pScore2.text != pScore2.toString()) {
				animating = true;
				Tweener.addTween(board.pScore2, {alpha:0,_Blur_blurX: 10,_Blur_quality:1, time:0.5, transition:"easeIn",onComplete: function() {board.pScore2.text = pScore2.toString();}});
				Tweener.addTween(board.pScore2, {alpha:1,_Blur_blurX: 0,_Blur_quality:1, delay:0.5, time:0.5, transition:"easeOut",onComplete: function(){animating = false;}});
			}
			
			
			
			doUpdate = false;
		}
		
		public function getCountry (country:String):String {
				
				var count = isoCountries.findCountryByName(country);
				if (count == "")
					count = isoCountries.findCountryByCode(country);
				if (count == "")
					count = "unknown";
				
				return count;
			
		}
		
		
	}

	
}
