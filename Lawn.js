//==============================================================================
//Lawns
//11-15-16
//Todd Gregersen
//==============================================================================
//This is a game based on mowing lawns and avoiding obstacles.
//The lawn and obstacles are generated at the start, then the timer begins.
//Players are given 60 seconds to mow the entire lawn or get as far as they can.
//Mower works in one direction at a time. Obstacles immobilize the mower.
//The lawn will randomly grow as the player plays adding challenge to the game.
//==============================================================================
//==============================================================================
//					Beginning of Code
//==============================================================================
//					Variables
//==============================================================================
var canvas;
var canvasContext;
var canWidth;
var canHeight;

var mX;
var mY;
var initX;
var initY;
var diffX;
var diffY;

var grassWid=canWidth-100;
var grassHt=canHeight-100;
var FRAMESPERSECOND=30;

var btnOneX=0;
var btnOneY=0;
var btnTwoX=50;
var btnTwoY=0;

var max=8;
var min=0;
var moduSize=3;
var mowSzX=50;
var mowSzY=50;
var obMax=1;
var ranInter=1;
var sqHt=200;
var sqWid=200;

var intVar;
var grassX=50;
var grassY=50;
var moduTime=5;
var mower=false;
var obst=false;

var timVar;
var token=0;
var count;
var countEnd;
var endgame=0;
var obCount=0;
var score=0;

var time=0;
var timeMax=60;
var maxT=400;
var minT=15;
var interceptVar;
var dirVec;
var grthVar;

var spots = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
//==============================================================================
//					Functions
//==============================================================================
function handleMousePos(evt){
	var rect = canvas.getBoundingClientRect();
	var root = document.documentElement;
	var mouseX = evt.clientX - rect.left - root.scrollLeft;
	var mouseY = evt.clientY - rect.top - root.scrollTop;
	return{
		x:mouseX,
		y:mouseY
	};
}
//==============================================================================
function handlemousedown(){
	if(mower==false){
		mower=true;
	}
	interceptVar=setInterval(calcIntercept, 10);
	//if(endgame == 0){drawAll();}
}
//==============================================================================
function handlemouseup(){
	clearInterval(interceptVar);
	token=0;
	count=0;
	if(mower==true){
		mower=false;
	}
	obst=false;
	//if(endgame == 0){drawAll();}
}
//==============================================================================
window.onload = function(){
	canvas = document.getElementById('lawnCanvas');
	canvasContext = canvas.getContext('2d');

	canWidth = canvas.scrollWidth;
	canHeight = canvas.scrollHeight;

	drawAll();

	beginGame();
	timVar=setInterval(timer,1000);
	intVar=setInterval(gameTime,1000/FRAMESPERSECOND);
	grthVar=setInterval(function(){
			if(time%moduTime==0){
				randomGrowth();
			}
		},ranInter);	

	canvas.addEventListener('mousedown', function(){
			initY=mY;
			initX=mX;
			handlemousedown();
		}, false);
	canvas.addEventListener('mouseup', handlemouseup, false);
	canvas.addEventListener('mousemove',
		function(evt){
			var mousePos = handleMousePos(evt);
			mX=mousePos.x;
			mY=mousePos.y;
		});
}
//==============================================================================
function calcIntercept(){
	diffX=Math.abs(initX-mX);
	diffY=Math.abs(initY-mY);
	var inX;
	var inY;
	if(diffX>diffY && count==0){token=1; count=1;}
	if(diffY>diffX && count==0){token=2; count=1;}
	if(token==1){
		dirVec=0;
		inX=Math.floor((initY-50)/sqWid);
		inY=Math.floor((mX-50)/sqHt);
	}
	if(token==2){
		dirVec=1;
		inX=Math.floor((mY-50)/sqWid);
		inY=Math.floor((initX-50)/sqHt);
	}
	var inI=inX+(inY*moduSize);
	if(spots[inI]==1){
		spots[inI]=0;
		score++;
	}
	if(spots[inI]==2){
		obst=true;
	}
}
//==============================================================================
function timer(){
	if(time != timeMax){
		time++;
	}
}
//==============================================================================
function beginGame(){
	randomBoard();
	for(i=0;i<moduTime;i++){
		randomGrowth();
	}
	for(i=0;i<obMax;i++){	
		randomObstacle();
	}
}
//==============================================================================
function gameTime(){
	endGame();
	drawAll();
	if(endgame != 0){
		clearInterval(intVar);
		clearInterval(timVar);
		clearInterval(grthVar);
	}	
}
//==============================================================================
function endGame(){
	countEnd=0;
	for(i=0;i<max;i++){
		if(spots[i]==0){
			countEnd++;
		}
	}
	if(time==timeMax){
		endgame=1;
	}else if(countEnd==(max-obCount)){
		endgame=2;
	}
}
//==============================================================================
function randomBoard(){
	var sqTemp=Math.floor(Math.random()*(12-2)+2);
	ranInter=Math.floor(Math.random()*(maxT-minT)+minT)
	max=(sqTemp*sqTemp)-1;
	min=0;
	moduSize=sqTemp;
	obMax=Math.floor(Math.random()*(sqTemp-1)+1)
	sqHt=600/sqTemp;
	sqWid=600/sqTemp;
	mowSzX=Math.floor(sqWid/4);
	mowSzY=Math.floor(sqHt/4);
}
//==============================================================================
function randomObstacle(){
	var temp=Math.floor(Math.random()*(max-min)+min);
	spots[temp]=2;
	obCount++;
}
//==============================================================================
function randomGrowth(){
	var temp=Math.floor(Math.random()*(max-min)+min);
	if(spots[temp]!=2){
		spots[temp]=1;
	}
}
//==============================================================================
function drawAll(){
	drawRect(0, 0, canWidth, canHeight, '#bfbfbf');
	drawRect(((canWidth-20)/2),10,60,26,'Black');
	canvasContext.fillStyle = 'white';
	canvasContext.fillText(time, (canWidth/2), 20);
	canvasContext.fillText("Time", ((canWidth/2)+15), 20);
	canvasContext.fillText(score, (canWidth/2), 32);
	canvasContext.fillText("Score", ((canWidth/2)+15), 32);
	drawRect(grassX,grassY,(canWidth-(grassX*2)),(canHeight-(grassY*2)),'#009933');
	var divTemp=0;
	var modTemp=0;

	for(i=0;i<max;i++){
		if(spots[i]==1){
			if(i>0){
				divTemp=Math.floor(i/moduSize);
				modTemp=Math.floor(i%moduSize);
			}else{
				divTemp=0;
				modTemp=0;
			}
			drawRect((grassX+(divTemp*sqWid)),(grassY+(modTemp*sqHt)),sqWid,sqHt,'#006600');
		}
		if(spots[i]==2){
			if(i>0){
				divTemp=Math.floor(i/moduSize);
				modTemp=Math.floor(i%moduSize);
			}else{
				divTemp=0;
				modTemp=0;
			}
			drawRect((grassX+(divTemp*sqWid)),(grassY+(modTemp*sqHt)),sqWid,sqHt,'#0000ff');
		}
	}
	if(mower==true){
		var H;
		var I;
		var J;
		if(obst==false){
			if(dirVec==0){
				H=(mX-(mowSzX/2));
				I=(initY-(mowSzY/2));
				J=1;
				drawRect(H,I,mowSzX,mowSzY,'Red');
				var r=Math.random*(500-100)+1;
				setTimeout(function(){drawChaff(H,I,J);},r);
			}
			if(dirVec==1){
				H=(initX-(mowSzX/2));
				I=(mY-(mowSzY/2));
				J=2;
				drawRect(H,I,mowSzX,mowSzY,'Red');
				var r=Math.random*(500-100)+1;
				setTimeout(function(){drawChaff(H,I,J);},r);
			}
		}
	}
	if(endgame == 1){
		canvasContext.fillStyle='Black';
		canvasContext.font="50px Arial";
		canvasContext.fillText("OUT OF TIME!",(canWidth/2),(canHeight/2));
		canvasContext.fillText("Score: "+score,(canWidth/2)+45,(canHeight/2)+45);
	}
	if(endgame == 2){
		canvasContext.fillStyle='Black';
		canvasContext.font="50px Arial";
		canvasContext.fillText("FINISHED!",(canWidth/2),(canHeight/2));
		canvasContext.fillText("Score: "+score,(canWidth/2)+45,(canHeight/2)+45);
	}
}
//==============================================================================
function drawRect(x, y, rwidth, rheight, colorRect){
	canvasContext.fillStyle = colorRect;
	canvasContext.fillRect(x,y,rwidth,rheight);
}
//==============================================================================
function drawChaff(H,I,J){	
	var m=Math.random()*(5-1)+1;
	var n=Math.random()*(5-1)+1;
	var o=Math.random()*(5-1)+1;
	var p=3;
	var q=Math.random()*(40-20)+20;
	var s=Math.random()*(60-40)+40;
	var t=Math.random()*(20-1)+1;
	//drawRect((H-((m*p))),(I-((m*p))),6,6,'#66ff33');
	//drawRect((H+(mowSzX+(m*p))),(I-((m*p))),6,6,'#66ff33');
	if(J==1){
		drawRect((H-t-((m*p))),(I+(mowSzY+(m*p))),6,6,'#66ff33');
		drawRect((H-q-(((m+n)*p))),(I+(mowSzY+((m+n)*p))),6,6,'#66ff33');
		drawRect((H-s-(((m+o)*p))),(I+(mowSzY+((m+o)*p))),6,6,'#66ff33');
	}
	if(J==2){
		drawRect((H+t+(mowSzX+(m*p))),(I+(mowSzY+(m*p))),6,6,'#66ff33');
		drawRect((H+q+(mowSzX+((m+n)*p))),(I+(mowSzY+((m+n)*p))),6,6,'#66ff33');
		drawRect((H+s+(mowSzX+((m+o)*p))),(I+(mowSzY+((m+o)*p))),6,6,'#66ff33');
	}
}
//==============================================================================
//					End of Code
//==============================================================================
//==============================================================================