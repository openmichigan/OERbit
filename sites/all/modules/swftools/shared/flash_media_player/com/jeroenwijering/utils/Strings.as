package com.jeroenwijering.utils {


/**
* This class groups a couple of commonly used string operations.
**/
public class Strings {


	/** 
	* Unescape a string and filter "asfunction" occurences ( can be used for XSS exploits).
	* 
	* @param str	The string to decode.
	* @return 		The decoded string.
	**/
	public static function decode(str:String):String {
		if(str.indexOf('asfunction') == -1) {
			return unescape(str);
		} else {
			return '';
		}
	};


	/** 
	* Convert a number to a digital-clock like string. 
	*
	* @param nbr	The number of seconds.
	* @return		A MN:SS string.
	**/
	public static function digits(nbr:Number):String {
		var min:Number = Math.floor(nbr/60);
		var sec:Number = Math.floor(nbr%60);
		var str:String = Strings.zero(min)+':'+Strings.zero(sec);
		return str;
	};


	/**
	* Convert a time-representing string to a number.
	* 
	* @param str	The input string. Supported are 00:03:00.1 / 03:00.1 / 180.1s / 3.2m / 3.2h
	* @return		The number of seconds.
	**/
	public static function seconds(str:String):Number {
		str = str.replace(',','.');
		var arr:Array = str.split(':');
		var sec:Number = 0;
		if (str.substr(-1) == 's') {
			sec = Number(str.substr(0,str.length-1));
		} else if (str.substr(-1) == 'm') {
			sec = Number(str.substr(0,str.length-1)) * 60;
		} else if(str.substr(-1) == 'h') {
			sec = Number(str.substr(0,str.length-1)) *3600;
		} else if(arr.length > 1) {
			sec = Number(arr[arr.length-1]);
			sec += Number(arr[arr.length-2]) * 60;
			if(arr.length == 3) {
				sec += Number(arr[arr.length-3]) *3600;
			}
		} else {
			sec = Number(str);
		}
		return sec;
	};


	/**
	* Basic serialization: string representations of booleans and numbers are returned typed;
	* strings are returned urldecoded.
	*
	* @param val	String value to serialize.
	* @return		The original value in the correct primitive type.
	**/
	public static function serialize(val:String):Object {
		if(val == null) {
			return null;
		} else if (val == 'true') {
			return true;
		} else if (val == 'false') {
			return false;
		} else if (isNaN(Number(val)) || val.length > 5) {
			return val;
		} else {
			return Number(val);
		}
	};


	/**
	* Strip HTML tags and linebreaks off a string.
	*
	* @param str	The string to clean up.
	* @return		The clean string.
	**/
	public static function strip(str:String):String {
		var tmp:Array = str.split("\n");
		str = tmp.join("");
		tmp = str.split("\r");
		str = tmp.join("");
		var idx:Number = str.indexOf("<");
		while(idx != -1) {
			var end:Number = str.indexOf(">",idx+1);
			end == -1 ? end = str.length-1: null;
			str = str.substr(0,idx)+" "+str.substr(end+1,str.length);
			idx = str.indexOf("<",idx);
		}
		return str;
	};


	/** 
	* Add a leading zero to a number.
	* 
	* @param nbr	The number to convert. Can be 0 to 99.
	* @ return		A string representation with possible leading 0.
	**/
	public static function zero(nbr:Number):String {
		if(nbr < 10) {
			return '0'+nbr;
		} else {
			return ''+nbr;
		}
	};


}


}