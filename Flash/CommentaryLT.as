/**********************************************************************************

Copyright (c) 2012, Tan Yu Sheng
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************************/

package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.display.StageScaleMode;
	import flash.display.StageAlign;
	import caurina.transitions.*;
	import caurina.transitions.properties.FilterShortcuts;
	import flash.filters.*;
	import flash.net.URLRequest;
	import flash.net.URLLoader;
	import flash.xml.XMLDocument;
	import flash.text.TextField;
	
	
	public class CommentaryLT extends MovieClip {
		
		//Set up needed variables. If you need to use more fields add them here.
		var timestampOld:Number;
		var timestamp:Number;
		var cTitle1:String;
		var cTitle2:String;
		
		var animating:Boolean = false;
		var doUpdate:Boolean = false;
		
		public function CommentaryLT() {
			// constructor code
			
			FilterShortcuts.init();
			var boardX = board.x
			board.x = boardX-850;
			board.cTitle1.alpha=0;
			board.cTitle2.alpha=0;
			
			Tweener.addTween(board, {x:boardX, time:0.8, transition:"easeOut"});
			
			//Set up poller. Loading from the xml file every 250ms seems like a decent choice. Feel free to make it higher or lower.
			var poller:Timer = new Timer(250);
			poller.addEventListener(TimerEvent.TIMER, pollHandler);
			poller.start();
		}
		
		public function loadData() {
			var xmlLoader:URLLoader = new URLLoader();
			xmlLoader.addEventListener(Event.COMPLETE, dataLoaded);
			xmlLoader.load(new URLRequest("streamcontrol.xml"));
			
			function dataLoaded(e:Event):void {
				//Set values from XML. Add the values you need from the XML file here as well.
				var streamData:XML = new XML(e.target.data);
				cTitle1 = streamData.elements("cTitle1");
				cTitle2 = streamData.elements("cTitle2");
				timestampOld = timestamp;
				timestamp = streamData.elements("timestamp");
			}
		
		}
		
		/* Should probably make this part more robust. 
		But it seems to work fine for the most part.
		Haven't run into problems in use so far. 
		Especially since polling rate isn't too fast.*/
		
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
		
		public function updateBoard() {
			if (board.cTitle1.text != cTitle1) {
				animating = true;
				var currX:Number = board.cTitle1.x;
				Tweener.addTween(board.cTitle1, {
					x:currX-300,
					alpha:0,
					_Blur_blurX: 10,
					_Blur_quality:1,
					time:0.3,
					transition:"easeIn",
					onComplete: function() {
						board.cTitle1.text = cTitle1;
					}
				});
				Tweener.addTween(board.cTitle1, {
					x:currX,
					alpha:1,
					_Blur_blurX: 0,
					_Blur_quality:1, 
					delay:0.3, 
					time:0.3, 
					transition:"easeOut",
					onComplete: function() {
						animating = false;
					}
				});
			}
			if (board.cTitle2.text != cTitle2) {
				animating = true;
				var currX:Number = board.cTitle2.x;
				Tweener.addTween(board.cTitle2, {
					x:currX-300,
					alpha:0,
					_Blur_blurX: 10,
					_Blur_quality:1,
					time:0.3,
					delay:0.3,
					transition:"easeIn",
					onComplete: function() {
						board.cTitle2.text = cTitle2;
					}
				});
				Tweener.addTween(board.cTitle2, {
					x:currX,
					alpha:1,
					_Blur_blurX: 0,
					_Blur_quality:1,
					delay:0.6,
					time:0.3,
					transition:"easeOut",
					onComplete: function() {
						animating = false;
					}
				});
			}
			
			doUpdate = false;
		}
		
	}
	
}
