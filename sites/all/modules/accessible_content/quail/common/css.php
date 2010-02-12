<?php
/**
*    QUAIL - QUAIL Accessibility Information Library
*    Copyright (C) 2009 Kevin Miller
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	@author Kevin Miller <kemiller@csumb.edu>
*/


/**
*	A helper class to parse the document's CSS so we can run accessibility
*	tests against it.
*/
class quailCSS {
	
	/**
	*	@var object The DOMDocument object of the current document
	*/
	var $dom;
	
	/**
	*	@var string The URI of the current document
	*/
	var $uri;

	/**
	*	@var array An array of all the named elements in the CSS file so we can find them
	*/	
	var $css_index;
	
	/**
	*	@var string The type of request (inherited from the main QUAIL object)
	*/
	var $type;
	
	/**
	*	@var array An array of all the CSS elements and attributes
	*/
	var $css;
	
	/**
	*	@var string Additional CSS information (usually for CMS mode requests)
	*/
	var $css_string;
	
	/**
	*	@var array An array broken into buckets of tag names that includes all DOM elements 
	*		       which have a CSS style applied to them and their associated CSS style.
	*/
	var $dom_index;
	
	
	/**
	*	@var bool Whether or not we are running in CMS mode
	*/
	var $cms_mode;
	
	/**
	*	Class constructor. We are just building and importing variables here and then loading the CSS
	*	@param object $dom The DOMDocument object
	*	@param string $uri The URI of the request
	*	@param string $type The type of request
	*	@param bool $cms_mode Whether we are running in CMS mode
	*	@param array $css_files An array of additional CSS files to load
	*/
	function __construct(&$dom, $uri, $type, $path, $cms_mode = false, $css_files = array()) {
		$this->dom =& $dom;
		$this->type = $type;
		$this->uri = $uri;
		$this->path = $path;
		$this->cms_mode = $cms_mode;
		$this->css_files = $css_files;
		$this->loadCSS();
		$this->buildIndex();
	}
	
	/**
	*	Loads all the CSS files from the document using LINK elements or @import commands
	*/
	function loadCSS() {
		if(count($this->css_files) > 0) {
			$css = $this->css_files;
		}
		else {
			$header_styles = $this->dom->getElementsByTagName('style');
			foreach($header_styles as $header_style) {
				if($header_style->nodeValue) {
					$this->css_string .= $header_style->nodeValue;
				}
			}
			$style_sheets = $this->dom->getElementsByTagName('link');
			
			foreach($style_sheets as $style) {
				
				if(strtolower($style->getAttribute('rel')) == 'stylesheet' &&
					$style->getAttribute('media') != 'print') {
						$css[] = $style->getAttribute('href');
				}
			}
		}
		if(is_array($css)) {
			foreach($css as $sheet) {
				if($this->type == 'uri')
					$this->loadUri($sheet);
				if($this->type == 'file' || $this->type == 'string') 
					$this->loadUri($sheet);
			}
			
		}
		
		$this->formatCSS();
	}
	
	/**
	*	Walk through the entire DOM tree and build the CSS DOM Index
	*/
	private function buildIndex() {
		if(!is_array($this->css))
			return null;
		foreach($this->css as $selector => $style) {	
			$xpath = new DOMXPath($this->dom);
			$entries = @$xpath->query($this->getXpath($selector));
			if($entries->length) {
				foreach($entries as $entry) {
					$this->buildIndexEntry($entry, $style);
				}
			}
		}
		
	}
	
	/**
	*	Adds an index entry to the CSS index by checking that the
	*	tag bucket has been created, and if not, makes it, then
	*	adds styles as appropriate
	*	@param object $entry The DOMNode element that applies to this style
	*	@param array $style An array of style information 
	
	*/
	private function buildIndexEntry($entry, $style) {
		
		if(!is_array($this->dom_index[$entry->tagName])) {
			$this->dom_index[$entry->tagName] = array();
		}
		$never_created = true;
		foreach($this->dom_index[$entry->tagName] as $k => $index_entry) {
			if($index_entry['element'] == $entry) {
				$never_created = false;
				foreach($style as $key => $value) {
					if(!$this->dom_index[$entry->tagName][$k]['style'][$key])
						$this->dom_index[$entry->tagName][$k]['style'][$key] = $value;
				}
			}
		}
		if($never_created) {
			$this->dom_index[$entry->tagName][] = array(
				'element' => $entry,
				'style' => $style);
		}
	}
	
	/**
	*	Interface method for tests to call to lookup the style information for a given DOMNode
	*	@param object $element A DOMElement/DOMNode object
	*	@return array An array of style information (can be empty)
	*/
	public function getStyle($element) {
		
		$style = $this->getNodeStyle($element);
		
		return $this->walkUpTreeForInheritance($element, $style);
	}
	
	/**
	*	Returns the style from the CSS index for a given element by first
	*	looking into its tag bucket then iterating over every item for an
	*	element that matches
	*	@param object The DOMNode/DOMElement object in queryion
	*	@retun array An array of all the style elements that _directly_ apply
	*	 			 to that element (ignoring inheritance)
	*
	*/
	private function getNodeStyle($element) {
		if(is_array($this->dom_index[$element->tagName])) {
			foreach($this->dom_index[$element->tagName] as $css_tag) {
				if($element == $css_tag['element']) {
					return $css_tag['style'];
				}
			}
		}
	}
	
	/**
	*	A helper function to walk up the DOM tree to the end to build an array
	*	of styles.
	*	@param object $element The DOMNode object to walk up from
	*	@param array $style The current style built for the node
	*	@return array The array of the DOM element, altered if it was overruled through css inheritance
	*/
	private function walkUpTreeForInheritance($element, $style) {
		while($element->parentNode->tagName) {
			$element = $element->parentNode;
			$parent_style = $this->getNodeStyle($element);
			
			if(is_array($parent_style)) {
				foreach($parent_style as $k => $v) {
					if(!isset($style[$k])) {
						$style[$k] = $v;
					}
				}
				/*if($element->hasAttribute('bgcolor') && !$style['background-color'] && !$style['background']) {
					$style['background-color'] = $element->getAttribute('bgcolor');
				}*/
			}
		}
		return $style;
	}
	
	/**
	*	Loads a CSS file from a URI
	*	@param string $rel The URI of the CSS file
	*/
	private function loadUri($rel) {
		
		if(strpos($rel, 'http://') !== false || strpos($rel, 'https://') !== false)
			$uri = $rel;
		else
			$uri = substr($this->uri, 0, strrpos($this->uri, '/')) .'/'.$rel;
		
		$this->css_string .= @file_get_contents($uri);
		
	}
	
	/**
	*	Adds a CSS element to the current index
	*	@param string $key The CSS key for the element
	*	@param string $codestr The styles for the CSS Element
	*/
	private function addSelector($key, $codestr) {
		$key = strtolower($key);
		$codestr = strtolower($codestr);
		if(!isset($this->css[$key])) {
			$this->css[$key] = array();
		}
		$codes = explode(";",$codestr);
		$this->addIndexEntry($key, $codes);
		if(count($codes) > 0) {
			foreach($codes as $code) {
				$code = trim($code);
				$explode = explode(":",$code,2);
				if(count($explode) > 1) {
					list($codekey, $codevalue) = $explode;
					if(strlen($codekey) > 0) {
						$this->css[$key][trim($codekey)] = trim($codevalue);
						$this->addIndexEntry($key, $codestr);
					}
				}
			}
		}
	}

	/**
	*	Adds an index entry for the given key
	*	@param string $key The CSS key
	*/	
	private function addIndexEntry($selector, $style) {
		$select = $this->parseSelector($selector);

		$bucket = $select[0][count($select[0]) - 1];
		if(strpos($bucket, '#') !== false) {
			$sup = 'id';
		}
		elseif(strpos($bucket, '.') !== false) {
			$sup = 'class';
		}
		else {
			$sup = 'tag';
		}
		$this->css_index[$sup][$bucket][$selector] = array('selector' => $select, 'style' => $style);
	}

	/**
	* 	Formats the CSS to be ready to import into an array of styles
	*	@return bool Whether there were elements imported or not
	*/	
	private function formatCSS() {
		// Remove comments
		$str = preg_replace("/\/\*(.*)?\*\//Usi", "", $this->css_string);
		// Parse this damn csscode
		$parts = explode("}",$str);
		if(count($parts) > 0) {
			foreach($parts as $part) {
				list($keystr,$codestr) = explode("{",$part);
				$keys = explode(",",trim($keystr));
				if(count($keys) > 0) {
					foreach($keys as $key) {
						if(strlen($key) > 0) {
							$key = str_replace("\n", "", $key);
							$key = str_replace("\\", "", $key);
							$this->addSelector($key, trim($codestr));
						}
					}
				}
			}
		}
		return (count($this->css) > 0);
	}
	
	/**
	*	Converts a CSS selector to an Xpath query
	*	@param string $selector The selector to convert
	*	@return string An Xpath query string
	*/
	private function getXpath($selector) {
		$query = $this->parseSelector($selector);

		$xpath = '//';
		foreach($query[0] as $k => $q) {
			if($q == ' ' && $k)
				$xpath .= '//';
			elseif($q == '>' && $k)
				$xpath .= '/';
			elseif(substr($q, 0, 1) == '#') 
				$xpath .= '[ @id = "'. str_replace('#', '', $q) .'" ]';
	
			elseif(substr($q, 0, 1) == '.') 
				$xpath .= '[ @class = "'. str_replace('.', '', $q) .'" ]';
			else
				$xpath .= trim($q);
		}
		return str_replace('//[ @', '//*[ @', $xpath);
	}
	
	/**
	*	Checks that a string is really a regular character
	*	@param string $char The character
	*	@return bool Whether the string is a character
	*/
	private function isChar($char) {
		return extension_loaded('mbstring')
			? mb_eregi('\w', $char)
			: preg_match('@\w@', $char);
	}
	
	/**
	*	Parses a CSS selector into an array of rules.
	*	@param string $query The CSS Selector query
	*	@return arran An array of the CSS Selector parsed into rule segments
	*/
	private function parseSelector($query) {
		// clean spaces
		// TODO include this inside parsing ?
		$query = trim(
			preg_replace('@\s+@', ' ',
				preg_replace('@\s*(>|\\+|~)\s*@', '\\1', $query)
			)
		);
		$queries = array(array());
		if (! $query)
			return $queries;
		$return =& $queries[0];
		$specialChars = array('>',' ');
//		$specialCharsMapping = array('/' => '>');
		$specialCharsMapping = array();
		$strlen = mb_strlen($query);
		$classChars = array('.', '-');
		$pseudoChars = array('-');
		$tagChars = array('*', '|', '-');
		// split multibyte string
		// http://code.google.com/p/phpquery/issues/detail?id=76
		$_query = array();
		for ($i=0; $i<$strlen; $i++)
			$_query[] = mb_substr($query, $i, 1);
		$query = $_query;
		// it works, but i dont like it...
		$i = 0;
		while( $i < $strlen) {
			$c = $query[$i];
			$tmp = '';
			// TAG
			if ($this->isChar($c) || in_array($c, $tagChars)) {
				while(isset($query[$i])
					&& ($this->isChar($query[$i]) || in_array($query[$i], $tagChars))) {
					$tmp .= $query[$i];
					$i++;
				}
				$return[] = $tmp;
			// IDs
			} else if ( $c == '#') {
				$i++;
				while( isset($query[$i]) && ($this->isChar($query[$i]) || $query[$i] == '-')) {
					$tmp .= $query[$i];
					$i++;
				}
				$return[] = '#'.$tmp;
			// SPECIAL CHARS
			} else if (in_array($c, $specialChars)) {
				$return[] = $c;
				$i++;
			// MAPPED SPECIAL MULTICHARS
//			} else if ( $c.$query[$i+1] == '//') {
//				$return[] = ' ';
//				$i = $i+2;
			// MAPPED SPECIAL CHARS
			} else if ( isset($specialCharsMapping[$c])) {
				$return[] = $specialCharsMapping[$c];
				$i++;
			// COMMA
			} else if ( $c == ',') {
				$queries[] = array();
				$return =& $queries[ count($queries)-1 ];
				$i++;
				while( isset($query[$i]) && $query[$i] == ' ')
					$i++;
			// CLASSES
			} else if ($c == '.') {
				while( isset($query[$i]) && ($this->isChar($query[$i]) || in_array($query[$i], $classChars))) {
					$tmp .= $query[$i];
					$i++;
				}
				$return[] = $tmp;
			// ~ General Sibling Selector
			} else if ($c == '~') {
				$spaceAllowed = true;
				$tmp .= $query[$i++];
				while( isset($query[$i])
					&& ($this->isChar($query[$i])
						|| in_array($query[$i], $classChars)
						|| $query[$i] == '*'
						|| ($query[$i] == ' ' && $spaceAllowed)
					)) {
					if ($query[$i] != ' ')
						$spaceAllowed = false;
					$tmp .= $query[$i];
					$i++;
				}
				$return[] = $tmp;
			// + Adjacent sibling selectors
			} else if ($c == '+') {
				$spaceAllowed = true;
				$tmp .= $query[$i++];
				while( isset($query[$i])
					&& ($this->isChar($query[$i])
						|| in_array($query[$i], $classChars)
						|| $query[$i] == '*'
						|| ($spaceAllowed && $query[$i] == ' ')
					)) {
					if ($query[$i] != ' ')
						$spaceAllowed = false;
					$tmp .= $query[$i];
					$i++;
				}
				$return[] = $tmp;
			// ATTRS
			} else if ($c == '[') {
				$stack = 1;
				$tmp .= $c;
				while( isset($query[++$i])) {
					$tmp .= $query[$i];
					if ( $query[$i] == '[') {
						$stack++;
					} else if ( $query[$i] == ']') {
						$stack--;
						if (! $stack )
							break;
					}
				}
				$return[] = $tmp;
				$i++;
			// PSEUDO CLASSES
			} else if ($c == ':') {
				$stack = 1;
				$tmp .= $query[$i++];
				while( isset($query[$i]) && ($this->isChar($query[$i]) || in_array($query[$i], $pseudoChars))) {
					$tmp .= $query[$i];
					$i++;
				}
				// with arguments ?
				if ( isset($query[$i]) && $query[$i] == '(') {
					$tmp .= $query[$i];
					$stack = 1;
					while( isset($query[++$i])) {
						$tmp .= $query[$i];
						if ( $query[$i] == '(') {
							$stack++;
						} else if ( $query[$i] == ')') {
							$stack--;
							if (! $stack )
								break;
						}
					}
					$return[] = $tmp;
					$i++;
				} else {
					$return[] = $tmp;
				}
			} else {
				$i++;
			}
		}
		foreach($queries as $k => $q) {
			if (isset($q[0])) {
				if (isset($q[0][0]) && $q[0][0] == ':')
					array_unshift($queries[$k], '*');
				if ($q[0] != '>')
					array_unshift($queries[$k], ' ');
			}
		}
		return $queries;
	}
	
}
