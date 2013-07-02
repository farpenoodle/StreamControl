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
	
	
	public class ScoreBoard_nopips extends MovieClip {
		
		//Set up needed variables. If you need to use more fields add them here.
		var timestampOld:Number;
		var timestamp:Number;
		var pName1:String;
		var pScore1:Number;
		var pName2:String;
		var pScore2:Number;
		var game:String;
			
		var animating:Boolean = false;
		var doUpdate:Boolean = false;
		
		public function ScoreBoard_nopips() {
			// constructor code
			
			FilterShortcuts.init();
			var boardY = board.y;
			board.y=boardY-120;
			board.pName1.text = "";
			board.pName2.text = "";
			board.pScore1.text = "";
			board.pScore2.text = "";
			board.game.text = "";

			loadData();
			
			Tweener.addTween(board, {y:boardY, time:0.8, transition:"easeOut"});
			
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
				pName1 = streamData.elements("pName1");
				pScore1 = streamData.elements("pScore1");
				pName2 = streamData.elements("pName2");
				pScore2 = streamData.elements("pScore2");
				game = streamData.elements("game");
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
			if (board.pName1.text != pName1) {
				animating = true;
				var currX:Number = board.pName1.x;
				Tweener.addTween(board.pName1, {
					x:currX-100,
					alpha:0,
					_Blur_blurX: 10,
					_Blur_quality:1,
					time:0.5,
					transition:"easeIn",
					onComplete: function() {
						board.pName1.text = pName1;
					}
				});
				Tweener.addTween(board.pName1, {
					x:currX,
					alpha:1,
					_Blur_blurX: 0,
					_Blur_quality:1,
					delay:0.5,
					time:0.5,
					transition:"easeOut",onComplete: function() {
						animating = false;
					}
				});
			}
			if (board.pName2.text != pName2) {
				animating = true;
				var currX:Number = board.pName2.x;
				Tweener.addTween(board.pName2, {
					x:currX+100,
					alpha:0,
					_Blur_blurX: 10,
					_Blur_quality:1,
					time:0.5,
					transition:"easeIn",
					onComplete: function() {
						board.pName2.text = pName2;
					}
				});
				Tweener.addTween(board.pName2, {
					x:currX,
					alpha:1,
					_Blur_blurX: 0,
					_Blur_quality:1,
					delay:0.5,
					time:0.5,
					transition:"easeOut",
					onComplete: function() {
						animating = false;
					}
				});
			}

			if (board.pScore1.text != pScore1 || board.pScore1.text == "") {
				animating = true;
				var currY:Number = board.pScore1.y;
				Tweener.addTween(board.pScore1, {
					y:currY-30,
					alpha:0,
					_Blur_blurY: 10,
					_Blur_quality:1,
					time:0.5,
					transition:"easeIn",
					onComplete: function() {
						board.pScore1.text = pScore1;
					}
				});
				Tweener.addTween(board.pScore1, {
					y:currY,
					alpha:1,
					_Blur_blurY: 0,
					_Blur_quality:1,
					delay:0.5,
					time:0.5,
					transition:"easeOut",
					onComplete: function() {
						animating = false;
					}
				});
			}
			
			if (board.pScore2.text != pScore2 || board.pScore1.text == "") {
				animating = true;
				var currY:Number = board.pScore2.y;
				Tweener.addTween(board.pScore2, {
					y:currY-30,
					alpha:0,
					_Blur_blurY: 10,
					_Blur_quality:1,
					time:0.5,
					transition:"easeIn",
					onComplete: function() {
						board.pScore2.text = pScore2;
					}
				});
				Tweener.addTween(board.pScore2, {
					y:currY,
					alpha:1,
					_Blur_blurY: 0,
					_Blur_quality:1,
					delay:0.5,
					time:0.5,
					transition:"easeOut",
					onComplete: function() {
						animating = false;
					}
				});
			}
			
			if (board.game.text != game) {
				animating = true;
				var currY:Number = board.game.y;
				Tweener.addTween(board.game, {
					y:currY-20,
					alpha:0,
					_Blur_blurY: 10,
					_Blur_quality:1,
					time:0.5,
					transition:"easeIn",
					onComplete: function() {
						board.game.text = game;
					}
				});
				Tweener.addTween(board.game, {
					y:currY,
					alpha:1,
					_Blur_blurY: 0,
					_Blur_quality:1,
					delay:0.5,
					time:0.5,
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
