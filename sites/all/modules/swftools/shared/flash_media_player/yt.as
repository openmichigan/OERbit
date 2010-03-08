// Security domains
System.security.allowDomain('*');
System.security.allowInsecureDomain('*');



// Variables
if(!unique) { var unique = 1; }
var ytPlayer:MovieClip = this.createEmptyMovieClip("ytPlayer",this.getNextHighestDepth());
var ytPlayerLoader:MovieClipLoader = new MovieClipLoader();
var ytLocation:String = "http://www.youtube.com/apiplayer";
var _as3_to_as2:LocalConnection = new LocalConnection();
var _as2_to_as3:LocalConnection = new LocalConnection();
_as3_to_as2.allowDomain('*');
_as2_to_as3.allowDomain('*');
var connection:String;
var loadInterval:Number;
var byteInterval:Number;
var timeInterval:Number;
var loaded:Number;
var position:Number;



// Interval handlers
function loadHandler() {
	if (ytPlayer.isPlayerLoaded()) {
		_as2_to_as3.send('AS2_'+unique,"onSwfLoadComplete");
		clearInterval(loadInterval);
		ytPlayer.addEventListener("onStateChange", onPlayerStateChange);
		ytPlayer.addEventListener("onError", onPlayerError);
		ytPlayer.unMute();
	}
};
function byteHandler() {
	var btl = ytPlayer.getVideoBytesLoaded();
	var ttl = ytPlayer.getVideoBytesTotal();
	var off =  ytPlayer.getVideoStartBytes();
	if(ttl > 10 && btl != loaded) {
		loaded = btl;
		_as2_to_as3.send('AS2_'+unique,"onLoadChange",btl,ttl,off);
		if(btl+off >= ttl) {
			clearInterval(byteInterval);
		}
	}
};
function timeHandler() {
	var pos = Math.round(ytPlayer.getCurrentTime()*10)/10;
	var dur = Math.round(ytPlayer.getDuration()*10)/10;
	if(dur > 3) {
		if(pos == position && dur-pos < 10) {
			onPlayerStateChange(0);
		} else {
			_as2_to_as3.send('AS2_'+unique,"onTimeChange",pos,dur);
		}
	}
	position = pos;
};



// Event handlers
function onPlayerStateChange(stt:Number) {
	clearInterval(timeInterval);
	if(stt == 1) {
		timeInterval = setInterval(timeHandler,200);
	} else if (stt == 3) {
		clearInterval(byteInterval);
		byteInterval = setInterval(byteHandler,200);
		timeInterval = setInterval(timeHandler,200);
	}
	_as2_to_as3.send('AS2_'+unique,"onStateChange",stt);
}; 
function onPlayerError(erc:Number) {
	_as2_to_as3.send('AS2_'+unique,"onError",erc);
	clearInterval(timeInterval);
};


// Directive forwards
_as3_to_as2.pauseVideo = function() { ytPlayer.pauseVideo(); };
_as3_to_as2.playVideo = function() { ytPlayer.playVideo(); };
_as3_to_as2.stopVideo = function(){ ytPlayer.stopVideo(); clearInterval(byteInterval); };
_as3_to_as2.loadVideoById = function(id,pos) { ytPlayer.loadVideoById(id,pos); };
_as3_to_as2.setVolume = function(vol) { ytPlayer.setVolume(vol); };
_as3_to_as2.seekTo = function(pos) { ytPlayer.seekTo(pos,true); };
_as3_to_as2.setSize = function(wid,hei) { ytPlayer.setSize(wid,hei); };


// Initialization
_as3_to_as2.connect('AS3_'+unique);
ytPlayerLoaderListener = {}; 
ytPlayerLoaderListener.onLoadInit = function() { loadInterval = setInterval(loadHandler,200); };
ytPlayerLoader.addListener(ytPlayerLoaderListener);
ytPlayerLoader.loadClip(ytLocation,ytPlayer);