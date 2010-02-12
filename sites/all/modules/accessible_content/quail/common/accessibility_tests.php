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
*	\defgroup tests Accessibility Tests
*/
/*@{*/


/**
*  OAC # 155
*  Adjacent links with same resource must be combined.
*  If 2 adjacent links have the same destination then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=155
**/


/**
*  OAC # 192
*  There are no adjacent text and image links having the same destination.
*  This objective of this technique is to avoid unnecessary duplication that occurs when adjacent text and iconic versions of a link are contained in a document.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=192
**/

class aAdjacentWithSameResourceShouldBeCombined extends quailTest {
	
	var $default_severity = QUAIL_TEST_SEVERE;
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(trim($a->nextSibling->wholeText) == '')
				$next = $a->nextSibling->nextSibling;
			else
				$next = $a->nextSibling;
			if($next->tagName == 'a') {
				if($a->getAttribute('href') == $next->getAttribute('href'))
					$this->addReport($a);
			}
		}
	}
}


/**
*  OAC # 152
*  Alt text for all img elements used as source anchors is different from the link text.
*  If an image occurs within a link, the Alt text should be different from the link text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=152
**/

class aImgAltNotRepetative extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;


	function check() {
		foreach($this->getAllElements('a') as $a) {
			foreach($a->childNodes as $child) {
				if($child->tagName == 'img') {
					if(trim($a->nodeValue) == trim($child->getAttribute('alt')))
						$this->addReport($child);
				}
			}
		}
	}
}


/**
*  OAC # 169
*  Link text does not begin with \"link to\"" or \""go to\"" (English)."
*  Alt text for images used as links should not begin with \"link to\"" or \""go to\""."
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=169
**/

class aLinkTextDoesNotBeginWithRedundantWord extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $problem_words = array('link to', 'go to');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(!$a->nodeValue) {
				if($a->firstChild->tagName == 'img') {
					$text = $a->firstChild->getAttribute('alt');
				}
			}
			else 
				$text = $a->nodeValue;
			foreach($this->problem_words as $word) {
				if(strpos(trim($text), $word) === 0)
					$this->addReport($a);
			}
		}
	}
}


/**
*  OAC # 123
*  Include non-link, printable characters (surrounded by spaces) between adjacent links.
*  Adjacent links must be separated by printable characters. [Editor's Note - Define adjacent link? Printable characters always?]
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=123
**/

class aLinksAreSeperatedByPrintableCharacters extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->nextSibling->nextSibling->tagName == 'a' && trim($a->nextSibling->wholeText) == '')
				$this->addReport($a);
		}
	}
}



/**
*  OAC # 18
*  Anchor should not open new window without warning.
*  a (anchor) element must not contain a target attribute unless the target attribute value is either _self, _top, or _parent.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=18
**/

class aLinksDontOpenNewWindow extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $allowed_targets = array('_self', '_parent', '_top');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->hasAttribute('target') 
				&& !in_array($a->getAttribute('target'), $this->allowed_targets)) {
					$this->addReport($a);
			}
		}
	}

}


/**
*  OAC # 19
*  Link text is meaningful when read out of context.
*  All a (anchor) elements that contains any text will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=19
**/

class aLinksMakeSenseOutOfContext extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $allowed_targets = array('_self', '_parent', '_top');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(strlen($a->nodeValue) > 1)
				$this->addReport($a);
		}
	}

}


/**
*  OAC # 20
*  Links to multimedia require a text transcript.
*  a (anchor) element must not contain an href attribute value that ends with (case insensitive): .wmv, .mpg, .mov, .ram, .aif.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=20
**/

class aLinksToMultiMediaRequireTranscript extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $extensions = array('wmv', 'mpg', 'mov', 'ram', 'aif');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->hasAttribute('href')) {
				$filename = explode('.', $a->getAttribute('href'));
				$extension = array_pop($filename);
				if(in_array($extension, $this->extensions))
					$this->addReport($a);
			}
		}
	}

}


/**
*  OAC # 17
*  Sound file must have a text transcript.
*  a (anchor) element cannot contain an href attribute value that ends with any of the following (all case insensitive): .wav, .snd, .mp3, .iff, .svx, .sam, .smp, .vce, .vox, .pcm, .aif.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=17
**/

class aLinksToSoundFilesNeedTranscripts extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $extensions = array('wav', 'snd', 'mp3', 'iff', 'svx', 'sam', 'smp', 'vce', 'vox', 'pcm', 'aif');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->hasAttribute('href')) {
				$filename = explode('.', $a->getAttribute('href'));
				$extension = array_pop($filename);
				if(in_array($extension, $this->extensions))
					$this->addReport($a);
			}
		}
	}

}

class aMultimediaTextAlternative extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $extensions = array('wmv', 'wav',  'mpg', 'mov', 'ram', 'aif');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->hasAttribute('href')) {
				$extension = substr($a->getAttribute('href'), 
							 (strrpos($a->getAttribute('href'), '.') + 1), 4);
				if(in_array($extension, $this->extensions))
					$this->addReport($a);
			}
		}
	}
}


/**
*  OAC # 151
*  Each source anchor contains text.
*  a (anchor) element must contain text. The text may occur in the anchor text or in the title attribute of the anchor or in the Alt text of an image used within the anchor.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=151
**/

class aMustContainText extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if((!$a->nodeValue || trim(html_entity_decode($a->nodeValue)) == '')
				&& !$a->hasAttribute('title')) {
				$fail = true;
				$child = true;
				foreach($a->childNodes as $child) {
					if($child->tagName == 'img' && trim($child->getAttribute('alt')) != '')
						$fail = false;
					if($child->nodeValue)
						$fail = false;
				}
				if($fail)
					$this->addReport($a);
			}
		}
	}
}


/**
*  OAC # 164
*  Anchor element must have a title attribute.
*  Each source a (anchor) element must have a title attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=164
**/

class aMustHaveTitle extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(!$a->hasAttribute('title'))
				$this->addReport($a);
		}
	
	}
}


/**
*  OAC # 156
*  Anchor must not use Javascript URL protocol.
*  Anchor elements must not have an href attribute value that starts with "javascript:".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=156
**/

class aMustNotHaveJavascriptHref extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(substr(trim($a->getAttribute('href')), 0, 11) == 'javascript:')
				$this->addReport($a);
		}
	}	
}


/**
*  OAC # 150
*  Suspicious link text.
*  a (anchor) element cannot contain any of the following text (English): \"click here\""
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=150
**/

class aSuspiciousLinkText extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $suspicious = array(
		'click here', 'click', 'more', 'here',
	);

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(in_array(strtolower(trim($a->nodeValue)), $this->suspicious))
				$this->addReport($a);
		}
	
	}
}


/**
*  OAC # 165
*  The title attribute of all source a (anchor) elements describes the link destination.
*  Each source a (anchor) element must have a title attribute that describes the link destination.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=165
**/

class aTitleDescribesDestination extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if($a->hasAttribute('title'))
				$this->addReport($a);
		}
	
	}
}


/**
*  OAC # 132
*  Content must have an address for author.
*  address element must be present.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=132
**/

class addressForAuthor extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;


	function check() {
		foreach($this->getAllElements('address') as $address) {
			foreach($address->childNodes as $child) {
				if($child->tagName == 'a')
						return true;
			}
		}
		$this->addReport(null, null, false);
	}

}


/**
*  OAC # 132
*  Content must have an address for author.
*  address element must be present.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=132
**/


/**
*  OAC # 133
*  address of page author must be valid.
*  This error will be generated for each address element. [Editor's Note: What is a valid address?]
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=133
**/

class addressForAuthorMustBeValid extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;
	
	var $checkDomain = true;

	
	function check() {
		foreach($this->getAllElements('address') as $address) {
			if ($this->validateEmailAddress($address->nodeValue, array('check_domain' => $this->checkDomain)))
				return true;
			foreach($address->childNodes as $child) {
				if($child->tagName == 'a' && substr(strtolower($child->getAttribute('href')), 0, 7) == 'mailto:') {
					if($this->validateEmailAddress(trim(str_replace('mailto:', '', $child->getAttribute('href'))), 
						array('check_domain' => $this->checkDomain)))
							return true;
				
				}
			}
		}
		$this->addReport(null, null, false);
	}


	function validateEmailAddress($email) {
	  // First, we check that there's one @ symbol, 
	  // and that the lengths are right.
	  if (!ereg("^[^@]{1,64}@[^@]{1,255}$", $email)) {
	    // Email invalid because wrong number of characters 
	    // in one section or wrong number of @ symbols.
	    return false;
	  }
	  // Split it into sections to make life easier
	  $email_array = explode("@", $email);
	  $local_array = explode(".", $email_array[0]);
	  for ($i = 0; $i < sizeof($local_array); $i++) {
	    if
	(!ereg("^(([A-Za-z0-9!#$%&'*+/=?^_`{|}~-][A-Za-z0-9!#$%&'*+/=?^_`{|}~\.-]{0,63})|(\"[^(\\|\")]{0,62}\"))$",
	$local_array[$i])) {
	      return false;
	    }
	  }
	  // Check if domain is IP. If not, 
	  // it should be valid domain name
	  if (!ereg("^\[?[0-9\.]+\]?$", $email_array[1])) {
	    $domain_array = explode(".", $email_array[1]);
	    if (sizeof($domain_array) < 2) {
	        return false; // Not enough parts to domain
	    }
	    for ($i = 0; $i < sizeof($domain_array); $i++) {
	      if
	(!ereg("^(([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9])|([A-Za-z0-9]+))$",
	$domain_array[$i])) {
	        return false;
	      }
	    }
	  }
	  return true;
	}

}


/**
*  OAC # 24
*  applet contains a text equivalent in the body of the applet.
*  This error is generated for all applet elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=24
**/

class appletContainsTextEquivalent extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	function check() {
		foreach($this->getAllElements('applet') as $applet) {
			if(trim($applet->nodeValue) == '' || !$applet->nodeValue)
				$this->addReport($applet);

		}
	}

}


/**
*  OAC # 23
*  applet contains a text equivalent in the alt attribute of the applet.
*  Use the alt attribute to label an applet.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=23
**/


/**
*  OAC # 24
*  applet contains a text equivalent in the body of the applet.
*  This error is generated for all applet elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=24
**/

class appletContainsTextEquivalentInAlt extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	
	function check() {
		foreach($this->getAllElements('applet') as $applet) {
			if(!$applet->hasAttribute('alt') || $applet->getAttribute('alt') == '')
				$this->addReport($applet);

		}
	}

}


/**
*  OAC # 203
*  applet provides a keyboard mechanism to return focus to the parent window.
*  Ensure that keyboard users do not become trapped in a subset of the content that can only be exited using a mouse or pointing device.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=203
**/

class appletProvidesMechanismToReturnToParent extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;


	var $tag = 'applet';
}

class appletTextEquivalentsGetUpdated extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'applet';

}


/**
*  OAC # 25
*  applet user interface must be accessible.
*  This error is generated for all applet elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=25
**/

class appletUIMustBeAccessible extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'applet';
}


/**
*  OAC # 22
*  All applets do not flicker.
*  This error is generated for all applet elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=22
**/

class appletsDoNotFlicker extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'applet';

}


/**
*  OAC # 21
*  applet should not use color alone.
*  This error is generated for all applet elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=21
**/

class appletsDoneUseColorAlone extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'applet';
}


/**
*  OAC # 63
*  Alt text for all area elements identifies the link destination.
*  Alt text for area element must describe the link destination.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=63
**/

class areaAltIdentifiesDestination extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'area';

}


/**
*  OAC # 168
*  Alt text for all area elements contains all non decorative text in the image area.
*  This error is generated for all area elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=168
**/

class areaAltRefersToText extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'area';
}


/**
*  OAC # 65
*  area should not open new window without warning.
*  area element, target attribute values must contain any one of (case insensitive) _self, _top, _parent.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=65
**/

class areaDontOpenNewWindow extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $allowed_targets = array('_self', '_parent', '_top');
	
	function check() {
		foreach($this->getAllElements('area') as $area) {
			if($area->hasAttribute('target') 
				&& !in_array($area->getAttribute('target'), $this->allowed_targets)) {
					$this->addReport($area);
			}
		}
	}

}


/**
*  OAC # 62
*  All area elements have an alt attribute.
*  area elements must contain a alt attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=62
**/

class areaHasAltValue extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('area') as $area) {
			if(!$area->hasAttribute('alt'))
				$this->addReport($area);
		}
	}

}


/**
*  OAC # 64
*  area link to sound file must have text transcript.
*  area elements must not contain href attribute values that end with (all case insensitive) .wav, .snd, .mp3, .iff, .svx, .sam, .smp, .vce, .vox, .pcm, .aif
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=64
**/

class areaLinksToSoundFile extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $extensions = array('wav', 'snd', 'mp3', 'iff', 'svx', 'sam', 'smp', 'vce', 'vox', 'pcm', 'aif');
	
	function check() {
		foreach($this->getAllElements('area') as $area) {
			if($area->hasAttribute('href')) {
				$filename = explode('.', $area->getAttribute('href'));
				$extension = array_pop($filename);
				if(in_array($extension, $this->extensions))
					$this->addReport($area);
			}
		}
	}

}


/**
*  OAC # 153
*  basefont must not be used.
*  This error is generated for all basefont elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=153
**/

class basefontIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'basefont';
}



/**
*  OAC # 26
*  blink element is not used.
*  This error is generated for all blink elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=26
**/

class blinkIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'blink';

}


/**
*  OAC # 92
*  blockquote must not be used for indentation.
*  This error is generated if any blockquote element is missing a cite attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=92
**/

class blockquoteNotUsedForIndentation extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('blockquote') as $blockquote) {
			if(!$blockquote->hasAttribute('cite'))
				$this->addReport($blockquote);
		}
	}
}


/**
*  OAC # 120
*  Use the blockquote element to mark up block quotations.
*  If body element content is greater than 10 characters (English) then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=120
**/

class blockquoteUseForQuotations extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		$body = $this->getAllelements('body');
		$body = $body[0];
		if(!$body) return false;
		if(strlen($body->nodeValue) > 10)
			$this->addReport(null, null, false);
	
	}

}


/**
*  OAC # 179
*  The luminosity contrast ratio between active link text and background color is at least 5:1.
*  The luminosity contrast ratio between active link text and background color is at least 5:1
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=179
**/

class bodyActiveLinkColorContrast extends bodyColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;

	var $foreground = 'alink';
}




/**
*  OAC # 178
*  The luminosity contrast ratio between link text and background color is at least 5:1.
*  The luminosity contrast ratio between link text and background color is at least 5:1
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=178
**/

class bodyLinkColorContrast extends bodyColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $foreground = 'link';
}


/**
*  OAC # 157
*  Do not use background images.
*  The body element must not contain a background attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=157
**/

class bodyMustNotHaveBackground extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		$body = $this->getAllElements('body');
		if(!$body)
			return false;
		$body = $body[0];
		if($body->hasAttribute('background'))
			$this->addReport(null, null, false);
	}
}


/**
*  OAC # 180
*  The luminosity contrast ratio between visited link text and background color is at least 5:1.
*  The luminosity contrast ratio between visited link text and background color is at least 5:1
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=180
**/

class bodyVisitedLinkColorContrast extends bodyColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $foreground = 'vlink';
}


/**
*  OAC # 107
*  b (bold) element is not used.
*  This error will be generated for all B elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=107
**/

class boldIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'bold';
}


/**
*  OAC # 110
*  All input elements, type of "checkbox", have an explicitly associated label.
*  input element that contains a type attribute value of "checkbox" must have an associated label element. An associated label is one in which the for attribute value of the label element is the same as the id attribute value of the input element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=110
**/

class checkboxHasLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'input';
	
	var $type = 'checkbox';
	
	var $no_type = false;
}


/**
*  OAC # 114
*  All input elements, type of "checkbox", have a label that is positioned close to the control.
*  input element with a type attribute value of "checkbox" must have an associated label element positioned close to it.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=114
**/

class checkboxLabelIsNearby extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'checkbox')
				$this->addReport($input);
			
		}
	}
}


/**
*  OAC # 89
*  Document must be readable when stylesheets are not applied.
*  This error will be generated for each link element that has a rel attribute with a value of "stylesheet".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=89
**/

class cssDocumentMakesSenseStyleTurnedOff extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('link') as $link) {
			if($link->parentNode->tagName == 'head') {
				if($link->getAttribute('rel') == 'stylesheet')
					$this->addReport($link);
			}
		}
	}
}

/**
*	Checks that all color and background elements has stufficient contrast.
*
*/
class cssTextHasContrast extends quailColorTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		$xpath = new DOMXPath($this->dom);
		$entries = $xpath->query('//*');
		foreach($entries as $element) {
			$style = $this->css->getStyle($element);
			if(($style['background'] || $style['background-color']) && $style['color'] && $element->nodeValue) {
				$background = ($style['background-color'])
							   ? $style['background-color']
							   : $style['background'];
				if(!$background) {
					$background = '#ffffff';
				}
				$luminosity = $this->getLuminosity(
								$style['color'],
								$background
								);
				if($luminosity < 5) {
					$this->addReport($element, 'background: '. $background .' fore: '. $style['color'] . ' lum: '. $luminosity, false);
				}
			}
		}	
		
	}

}


/**
*  OAC # 28
*  HTML content has a valid doctype declaration.
*  Each document must contain a valid doctype declaration.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=28
**/

class doctypeProvided extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		if(!$this->dom->doctype->publicId)
			$this->addReport(null, null, false);		
	}

}


/**
*  OAC # 90
*  Abbreviations must be marked with abbr element.
*  If body element content is greater than 10 characters (English) this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=90
**/

class documentAbbrIsUsed extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;
	
	var $acronym_tag = 'abbr';
	
	function check() {
		foreach($this->getAllElements($this->acronym_tag) as $acronym) {
			$predefined[strtoupper(trim($acronym->nodeValue))] = $acronym->getAttribute('title');
		}
		$already_reported = array();
		foreach($this->getAllElements(null, 'text') as $text) {

			$words = explode(' ', $text->nodeValue);
			if(count($words) > 1 && strtoupper($text->nodeValue) != $text->nodeValue) {
				foreach($words as $word) {
					$word = preg_replace("/[^a-zA-Zs]/", "", $word);
					if(strtoupper($word) == $word && strlen($word) > 1 && !$predefined[strtoupper($word)])

						if(!$already_reported[strtoupper($word)]) {
							$this->addReport($text, 'Word "'. $word .'" requires an <code>'. $this->acronym_tag .'</code> tag.');
						}
						$already_reported[strtoupper($word)] = true;
				}
			}
		}
		
	}

}


/**
*  OAC # 91
*  Acronyms must be marked with acronym element.
*  If body element content is greater than 10 characters (English) then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=91
**/

class documentAcronymsHaveElement extends documentAbbrIsUsed {

	var $default_severity = QUAIL_TEST_MODERATE;


	var $acronym_tag = 'acronym';
}


/**
*  OAC # 202
*  All text colors or no text colors are set.
*  If the author specifies that the text must be black, then it may override the settings of the user agent and render a page that has black text (specified by the author) on black background (that was set in the user agent).
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=202
**/

class documentAllColorsAreSet extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
		
	var $color_attributes = array('text', 'bgcolor', 'link', 'alink', 'vlink');
	
	function check() {
		$body = $this->getAllElements('body');
		$body = $body[0];
		if($body) {
			$colors = 0;
			foreach($this->color_attributes as $attribute) {
				if($body->hasAttribute($attribute))
					$colors++;
			}
			if($colors > 0 && $colors < 5)
				$this->addReport(null, null, false);
		}
	}
}



/**
*  OAC # 68
*  Auto-redirect must not be used.
*  meta elements that contain a http-equiv attribute with a value of "refresh" cannot contain a content attribute with a value of (start, case insensitive) "http://".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=68
**/

class documentAutoRedirectNotUsed extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		foreach($this->getAllElements('meta') as $meta) {
			if($meta->getAttribute('http-equiv') == 'refresh' && !$meta->hasAttribute('content'))
				$this->addReport($meta);
		}
	
	}
}


/**
*  OAC # 184
*  The contrast between active link text and background color is greater than WAI ERT color algorithm threshold.
*  The contrast between active link text and background color must be greater than the WAI ERT color algorithm threshold.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=184
**/

class documentColorWaiActiveLinkAlgorithim extends bodyWaiErtColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $foreground = 'alink';
}


/**
*  OAC # 182
*  The contrast between text and background colors is greater than WAI ERT color algorithm threshold.
*  The contrast between text and background color must be greater than the WAI ERT color algorithm threshold.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=182
**/

class documentColorWaiAlgorithim extends bodyWaiErtColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
		
}


/**
*  OAC # 183
*  The contrast between link text and background color is greater than WAI ERT color algorithm threshold.
*  The contrast between link text and background color must be greater than the WAI ERT color algorithm threshold.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=183
**/

class documentColorWaiLinkAlgorithim extends bodyWaiErtColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $foreground = 'link';
}


/**
*  OAC # 185
*  The contrast between visited link text and background color is greater than WAI ERT color algorithm threshold.
*  The contrast between visited link text and background color must be greater than the WAI ERT color algorithm threshold.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=185
**/

class documentColorWaiVisitedLinkAlgorithim extends bodyWaiErtColorContrast {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $foreground = 'vlink';
}


/**
*  OAC # 100
*  Content must be readable when stylesheets are not applied.
*  The first occurrence of any element that contains a style attribute will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=100
**/

class documentContentReadableWithoutStylesheets extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $cms = false;
	
	function check() {
		foreach($this->getAllElements(null, 'text') as $text) {
			if($text->hasAttribute('style')) {
				$this->addReport(null, null, false);
				return false;
			}
		}
	
	}
}


/**
*  OAC # 49
*  Document contains a title element.
*  title element must be present in head section of document.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=49
**/

class documentHasTitleElement extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		
		$element = $this->dom->getElementsByTagName('title');
		if(!$element->item(0))
			$this->addReport(null, null, false);
	
	}
}


/**
*  OAC # 160
*  id attributes must be unique.
*  Each id attribute value must be unique.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=160
**/

class documentIDsMustBeUnique extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
		
	function check() {
		$xpath = new DOMXPath($this->dom);
		$entries = $xpath->query('//*');
		foreach($entries as $element) {
			if($element->hasAttribute('id'))
				$ids[$element->getAttribute('id')][] = $element;
		}	
		if(is_array($ids)) {
			foreach($ids as $id) {
				if(count($id) > 1)
					$this->addReport($id[1]);
			}
		}
	}
}


/**
*  OAC # 48
*  Document has valid language code.
*  html element must have a lang attribute value of valid 2 or 3 letter language code according to ISO specification 639.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=48
**/

class documentLangIsISO639Standard extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		$languages = file(dirname(__FILE__).'/resources/iso639.txt');
		
		$element = $this->dom->getElementsByTagName('html');
		$html = $element->item(0);
		if(!$html)
			return null;
		if($html->hasAttribute('lang'))
			if(in_array(strtolower($html->getAttribute('lang')), $languages))
				$this->addReport(null, null, false);
	
	}
}


/**
*  OAC # 47
*  Document has required lang attribute(s).
*  html element must contain a lang attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=47
**/

class documentLangNotIdentified extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		$element = $this->dom->getElementsByTagName('html');
		$html = $element->item(0);
		if(!$html) return null;
		if(!$html->hasAttribute('lang') || trim($html->getAttribute('lang')) == '')
			$this->addReport(null, null, false);
	
	}
}



/**
*  OAC # 69
*  Meta refresh is not used with a time-out.
*  meta elements that contain a http-equiv attribute with a value of "refresh" cannot contain a content attribute with a value of any number greater than zero.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=69
**/

class documentMetaNotUsedWithTimeout extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		foreach($this->getAllElements('meta') as $meta) {
			if($meta->getAttribute('http-equiv') == 'refresh' && !$meta->getAttribute('content'))
				$this->addReport($meta);
		}
	
	}
}


/**
*  OAC # 191
*  The reading direction of all text is correctly marked.
*  The reading direction of all text is correctly marked.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=191
**/


/**
*  OAC # 211
*  All changes in text direction are marked using the dir attribute.
*  Identify changes in the text direction of text that includes nested directional runs by providing the dir attribute on inline elements. A nested directional run is a run of text that includes mixed directional text, for example, a paragraph in English containing a quoted Hebrew sentence which in turn includes a quotation in French.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=211
**/

class documentReadingDirection extends quailTest {


	var $default_severity = QUAIL_TEST_MODERATE;

	var $cms = false;
	
	var $right_to_left = array('he', 'ar');
	function check() {
		$xpath = new DOMXPath($this->dom);
		$entries = $xpath->query('//*');
		foreach($entries as $element) {
			if(in_array($element->getAttribute('lang'), $this->right_to_left)) {

				if($element->getAttribute('dir') != 'rtl')
				 	$this->addReport($element);
			}
		}			
	}
}


/**
*  OAC # 181
*  Strict doctype is declared.
*  A 'strict' doctype must be declared in the document. This can either be the HTML4.01 or XHTML 1.0 strict doctype.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=181
**/

class documentStrictDocType extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		if(strpos(strtolower($this->dom->doctype->publicId), 'strict') === false
		   && strpos(strtolower($this->dom->doctype->systemId), 'strict') === false) 
			$this->addReport(null, null, false);
	}
}


/**
*  OAC # 53
*  title describes the document.
*  This error is generated for each title element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=53
**/

class documentTitleDescribesDocument extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $cms = false;
	
	function check() {
		$placeholders = file(dirname(__FILE__).'/resources/placeholder.txt');		
		$element = $this->dom->getElementsByTagName('title');
		$title = $element->item(0);
		if($title) {
				$this->addReport($title);
		}
	}
}


/**
*  OAC # 52
*  title is not placeholder text.
*  title element content can not be any one of (case insensitive) \"the title\""
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=52
**/

class documentTitleIsNotPlaceholder extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		$placeholders = file(dirname(__FILE__).'/resources/placeholder.txt');		
		$element = $this->dom->getElementsByTagName('title');
		$title = $element->item(0);
		if($title) {
			if(in_array(strtolower($title->nodeValue), $placeholders))
				$this->addReport(null, null, false);
		}
	}
}


/**
*  OAC # 51
*  title is short.
*  title element content must be less than 150 characters (English).
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=51
**/

class documentTitleIsShort extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	var $cms = false;
	
	function check() {
		
		$element = $this->dom->getElementsByTagName('title');
		$title = $element->item(0);
		if($title) {
			if(strlen($title->nodeValue)> 150)
				$this->addReport(null, null, false);
		}
	}
}


/**
*  OAC # 50
*  title contains text.
*  title element content cannot be empty or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=50
**/

class documentTitleNotEmpty extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		
		$element = $this->dom->getElementsByTagName('title');
		if($element->length > 0) {
			$title = $element->item(0);
			if(trim($title->nodeValue) == '')
				$this->addReport(null, null, false);
		}	
	}
}


/**
*  OAC # 188
*  Document validates to specification.
*  Document must validate to declared doctype.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=188
**/

class documentValidatesToDocType extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		if(!@$this->dom->validate())
			$this->addReport(null, null, false);
	}
}


/**
*  OAC # 201
*  All visual lists are marked.
*  Create lists of related items using list elements appropriate for their purposes.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=201
**/

class documentVisualListsAreMarkedUp extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $list_cues = array('*', '<br>*', '•', '&#8226');
	
	function check() {
		foreach($this->getAllElements(null, 'text') as $text) {
			foreach($this->list_cues as $cue) {
				$first = stripos($text->nodeValue, $cue);
				$second = strripos($text->nodeValue, $cue);
				if($first && $second && $first != $second)
					$this->addReport($text);
			}
		}
	
	}
}


/**
*  OAC # 101
*  Words and phrases not in the document's primary language are marked.
*  If the body element contains more than 10 characters (English) then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=101
**/

class documentWordsNotInLanguageAreMarked extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		$body = $this->getAllElements('body');
		$body = $body[0];
		$words = explode(' ', $body->nodeValue);

		if(count($words) > 10)
			$this->addReport(null, null, false);
	}
}


/**
*  OAC # 143
*  All embed elements have an associated noembed element that contains a text equivalent to the embed element.
*  Provide a text equivalent for the embed element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=143
**/

class embedHasAssociatedNoEmbed extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('embed') as $embed) {
			if($embed->firstChild->tagName != 'noembed' &&
				$embed->nextSibling->tagName != 'noembed')
					$this->addReport($embed);
		
		}
	}
}


/**
*  OAC # 145
*  embed must have alt attribute.
*  embed element must have an alt attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=145
**/

class embedMustHaveAltAttribute extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('embed') as $embed) {
			if(!$embed->hasAttribute('alt'))
					$this->addReport($embed);
		
		}
	}
}


/**
*  OAC # 146
*  embed must not have empty Alt text.
*  embed element cannot have alt attribute value of null ("") or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=146
**/

class embedMustNotHaveEmptyAlt extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('embed') as $embed) {
			if($embed->hasAttribute('alt') && trim($embed->getAttribute('alt')) == '')
					$this->addReport($embed);
		
		}
	}
}


/**
*  OAC # 205
*  embed provides a keyboard mechanism to return focus to the parent window.
*  Ensure that keyboard users do not become trapped in a subset of the content that can only be exited using a mouse or pointing device.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=205
**/

class embedProvidesMechanismToReturnToParent extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'embed';
}


/**
*  OAC # 142
*  Excessive use of emoticons.
*  This error is generated if 4 or more emoticons are detected. [Editor's Note - how are emoticons detected?]
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=142
**/

class emoticonsExcessiveUse extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		$emoticons = file(dirname(__FILE__).'/resources/emoticons.txt', FILE_IGNORE_NEW_LINES);
		$count = 0;
		foreach($this->getAllElements(null, 'text') as $element) {
			if(strlen($element->nodeValue < 2)) {
				$words = explode(' ', $element->nodeValue);
				foreach($words as $word) {
					if(in_array($word, $emoticons)) {
						$count++;
						if($count > 4) {
							$this->addReport(null, null, false);	
							return false;	
						}
					}
				}
			
			}
		}
	
	}
}

class emoticonsMissingAbbr extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		$emoticons = file(dirname(__FILE__).'/resources/emoticons.txt', FILE_IGNORE_NEW_LINES);
		$count = 0;
		foreach($this->getAllElements('abbr') as $abbr) {
			$abbreviated[$abbr->nodeValue] = $abbr->getAttribute('title');
		}
		foreach($this->getAllElements(null, 'text') as $element) {
			if(strlen($element->nodeValue < 2)) {
				$words = explode(' ', $element->nodeValue);
				foreach($words as $word) {
					if(in_array($word, $emoticons)) {
						if(!$abbreviated[$word])
							$this->addReport($element);
					}
				}
			
			}
		}
	
	}
}


/**
*  OAC # 111
*  All input elements, type of "file", have an explicitly associated label.
*  input element that contains a type attribute value of "file" must have an associated label element. An associated label is one in which the for attribute value of the label element is the same as the id attribute value of the input element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=111
**/

class fileHasLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'input';
	
	var $type = 'file';
	
	var $no_type = false;
}


/**
*  OAC # 115
*  All input elements, type of "file", have a label that is positioned close to the control.
*  input element with a type attribute value of "file" must have an associated label element positioned close to it.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=115
**/

class fileLabelIsNearby extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'file')
				$this->addReport($input);
			
		}
	}
}


/**
*  OAC # 154
*  font must not be used.
*  This error is generated for all font elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=154
**/

class fontIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $tag = 'font';
}

class formAllowsCheckIfIrreversable extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'form';
}


/**
*  OAC # 212
*  Information deleted using a web page can be recovered.
*  Help users with disabilities avoid serious consequences as the result of a mistake when performing an action that cannot be reversed.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=212
**/

class formDeleteIsReversable extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $watch_words = array('delete', 'remove', 'erase');
	
	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'submit') {
				foreach($this->watch_words as $word) {
					if(strpos(strtolower($input->getAttribute('value')), $word) !== false) 
						$this->addReport($this->getParent($input, 'form', 'body'));
				}				
			}
		}
	}
}


/**
*  OAC # 210
*  Form submission data is presented to the user before final acceptance for all irreversable transactions.
*  Provide users with a way to ensure their input is correct before completing an irreversible transaction.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=210
**/

class formErrorMessageHelpsUser extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'form';
}


/**
*  OAC # 209
*  All form submission error messages provide assistance in correcting the error.
*  Information about the nature and location of the input error is provided in text to enable the users to identify the problem.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=209
**/

class formHasGoodErrorMessage extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'form';
}	


/**
*  OAC # 199
*  All form fields that are required are indicated to the user as required.
*  Ensure that the label for any interactive component within Web content makes the component's purpose clear.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=199
**/

class formWithRequiredLabel extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'form';
}


/**
*  OAC # 190
*  frame element is not used.
*  This error is generated for all frame elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=190
**/

class frameIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'frame';

	var $cms = false;
	
}

/**
*  OAC # 33
*  Relationship between frames must be described.
*  If frameset element contains 3 or more frame elements then frameset element must contain a longdesc attribute that is a valid URL.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=33
**/

class frameRelationshipsMustBeDescribed extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	var $cms = false;
		
	
	function check() {
		foreach($this->getAllElements('frameset') as $frameset) {
		
			if(!$frameset->hasAttribute('longdesc') && $frameset->childNodes->length > 2)
				$this->addReport($frameset);
		}
	}

}


/**
*  OAC # 32
*  The source for each frame is accessible content.
*  frame content should be accessible, like HTML, not just an image.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=32
**/

class frameSrcIsAccessible extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $cms = false;
		
	function check() {
		foreach($this->getAllElements('frame') as $frame) {
			if($frame->hasAttribute('src')) {
				$extension = array_pop(explode('.', $frame->getAttribute('src')));
				if(in_array($extension, $this->image_extensions))
					$this->addReport($frame);
			
			}
		}
	}

}


/**
*  OAC # 31
*  All frame titles identify the purpose or function of the frame.
*  frame title must describe the purpose or function of the frame.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=31
**/

class frameTitlesDescribeFunction extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;	

	var $cms = false;
		
	function check() {
		foreach($this->getAllElements('frame') as $frame) {
			if($frame->hasAttribute('title'))
				$this->addReport($frame);
		}
	}

}


/**
*  OAC # 174
*  All frame titles are not empty.
*  frame title can't be empty.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=174
**/

class frameTitlesNotEmpty extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	function check() {
		foreach($this->getAllElements('frame') as $frame) {
			if(!$frame->hasAttribute('title') || trim($frame->getAttribute('title')) == '')
				$this->addReport($frame);
		}
	}
}


/**
*  OAC # 175
*  All frame titles do not contain placeholder text.
*  frame title should not contain placeholder text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=175
**/

class frameTitlesNotPlaceholder extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $placeholders = array('title', 'frame', 'frame title', 'the title');
	
	function check() {
		foreach($this->getAllElements('frame') as $frame) {
			if(in_array(trim($frame->getAttribute('title')), $this->placeholders))
				$this->addReport($frame);
		}
	}

}


/**
*  OAC # 30
*  All frames have a title attribute.
*  Each frame element must have a title attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=30
**/

class framesHaveATitle extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;	
	
	var $cms = false;
	
	function check() {
		foreach($this->getAllElements('frame') as $frame) {
			if(!$frame->hasAttribute('title'))
				$this->addReport($frame);
		}
	}

}


/**
*  OAC # 189
*  frameset element is not used.
*  This error is generated for all frameset elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=189
**/

class framesetIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
	
	var $tag = 'frameset';
}


/**
*  OAC # 34
*  frameset must have a noframes section.
*  frameset element must contain a noframes section.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=34
**/

class framesetMustHaveNoFramesSection extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $cms = false;
		
	function check() {
		foreach($this->getAllElements('frameset') as $frameset) {
			if(!$this->elementHasChild($frameset, 'noframes'))
				$this->addReport($frameset);
		}
	}

}


/**
*  OAC # 36
*  The header following an h1 is h1 or h2.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=36
**/

class headerH1 extends quailHeaderTest {
	
	var $tag = 'h1';
	
}


/**
*  OAC # 36
*  The header following an h1 is h1 or h2.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=36
**/


/**
*  OAC # 41
*  All h1 elements are not used for formatting.
*  h1 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=41
**/

class headerH1Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'h1';
}


/**
*  OAC # 37
*  The header following an h2 is h1, h2 or h3.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=37
**/

class headerH2 extends quailHeaderTest {
	
	var $tag = 'h2';
	
}


/**
*  OAC # 37
*  The header following an h2 is h1, h2 or h3.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=37
**/


/**
*  OAC # 42
*  All h2 elements are not used for formatting.
*  h2 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=42
**/

class headerH2Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'h2';
}


/**
*  OAC # 38
*  The header following an h3 is h1, h2, h3 or h4.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=38
**/

class headerH3 extends quailHeaderTest {
	
	var $tag = 'h3';
	
}


/**
*  OAC # 38
*  The header following an h3 is h1, h2, h3 or h4.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=38
**/


/**
*  OAC # 43
*  All h3 elements are not used for formatting.
*  h3 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=43
**/

class headerH3Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'h3';
}


/**
*  OAC # 39
*  The header following an h4 is h1, h2, h3, h4 or h5.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=39
**/


/**
*  OAC # 40
*  The header following an h5 is h6 or any header less than h6.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=40
**/

class headerH4 extends quailHeaderTest {
	
	var $tag = 'h4';
	
}


/**
*  OAC # 39
*  The header following an h4 is h1, h2, h3, h4 or h5.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=39
**/


/**
*  OAC # 40
*  The header following an h5 is h6 or any header less than h6.
*  The following header must be equal, one level greater or any level less.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=40
**/


/**
*  OAC # 44
*  All h4 elements are not used for formatting.
*  h4 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=44
**/

class headerH4Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'h4';
}

class headerH5 extends quailHeaderTest {
	
	var $tag = 'h5';
	
}


/**
*  OAC # 45
*  All h5 elements are not used for formatting.
*  h5 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=45
**/

class headerH5Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'h5';
}


/**
*  OAC # 46
*  All h6 elements are not used for formatting.
*  h6 may be used for formatting. Use the proper markup.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=46
**/

class headerH6Format extends quailTagTest{

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'h6';
}


/**
*  OAC # 206
*  Each section of content is marked with a header element.
*  Using the heading elements, h and h1 - h6, to markup the beginning of each section in the content can assist in navigation.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=206
**/

class headersUseToMarkSections extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;
	
	var $non_header_tags = array('strong', 'b', 'em', 'i');
	
	function check() {
		$headers = $this->getAllElements(null, 'header');
		$paragraphs = $this->getAllElements('p');
		if(count($headers) == 0 && count($paragraphs) > 1)
			$this->addReport(null, null, false);
		foreach($paragraphs as $p) {
			if(in_array($p->firstChild->tagName, $this->non_header_tags)
			   || in_array($p->firstChild->nextSibling->tagName, $this->non_header_tags)
			   || in_array($p->previousSibling->tagName, $this->non_header_tags))
				$this->addReport($p);
		}
	}
}


/**
*  OAC # 108
*  i (italic) element is not used.
*  This error will be generated for all i elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=108
**/

class iIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'i';
}


/**
*  OAC # 147
*  iframe must not use longdesc.
*  Iframe element cannot contain a longdesc attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=147
**/

class iframeMustNotHaveLongdesc extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('iframe') as $iframe) {
			if($iframe->hasAttribute('longdesc'))
				$this->addReport($iframe);
		
		}
	}
}


/**
*  OAC # 121
*  All active areas in all server-side image maps have duplicate text links in the document.
*  Any img element that contains ismap attribute will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=121
**/

class imageMapServerSide extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('ismap'))
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 16
*  Alt text for all img elements is the empty string ("") if the image is decorative.
*  Decorative images must have empty string ("") Alt text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=16
**/

class imgAltEmptyForDecorativeImages extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('alt'))
				$this->addReport($img);
		}
	}

}


/**
*  OAC # 15
*  Alt text for all img elements used as source anchors identifies the destination of the link.
*  img element that is contained by an a (anchor) element must have Alt text that identifies the link destination.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=15
**/

class imgAltIdentifiesLinkDestination extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(!$a->nodeValue) {
				foreach($a->childNodes as $child) {
					if($child->tagName == 'img' && $child->hasAttribute('alt'))
						$this->addReport($child);
				}
			}
		}
	
	}
}


/**
*  OAC # 2
*  Alt text is not the same as the filename unless author has confirmed it is correct.
*  img element cannot have alt attribute value that is the same as its src attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=2
**/

class imgAltIsDifferent extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if(trim($img->getAttribute('src')) == trim($img->getAttribute('alt')))
				$this->addReport($img);
		}
	}

}



/**
*  OAC # 11
*  Alt text for all img elements contains all text in the image unless the image text is decorative or appears elsewhere in the document.
*  This error is generated for all img elements that have a width and height greater than 50.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=11
**/

class imgAltIsSameInText extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('alt'))
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 3
*  Image Alt text is short.
*  Image Alt text is short or user must confirm that Alt text is as short as possible.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=3
**/

class imgAltIsTooLong extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('alt') && strlen($img->getAttribute('alt')) > 100) 
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 7
*  Alt text for all img elements used as source anchors is not empty when there is no other text in the anchor.
*  img element cannot have alt attribute value of null or whitespace if the img element is contained by an A element and there is no other link text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=7
**/

class imgAltNotEmptyInAnchor extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(!$a->nodeValue && $a->childNodes) {
				foreach($a->childNodes as $child) {
					if($child->tagName == 'img'
						&& trim($child->getAttribute('alt')) == '')
							$this->addReport($child);
				}
			}
		}
	
	}
}


/**
*  OAC # 6
*  Alt text for all img elements is not placeholder text unless author has confirmed it is correct.
*  img element cannot have alt attribute value of "nbsp" or "spacer".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=6
**/

class imgAltNotPlaceHolder extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $placeholders = array('nbsp', '&nbsp;', 'spacer', 'image', 'img', 'photo');
	
	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('alt')) {
				if(in_array($img->getAttribute('alt'), $this->placeholders) || ord($img->getAttribute('alt')) == 194) {
					$this->addReport($img);
				}
				elseif(preg_match("/^([0-9]*)(k|kb|mb|k bytes|k byte)?$/", strtolower($img->getAttribute('alt')))) {
					$this->addReport($img);
				}
			}
		}
	
	}
}


/**
*  OAC # 10
*  All img elements have associated images that do not flicker.
*  This error is generated for all img elements that contain a src attribute value that ends with ".gif" (case insensitive). and have a width and height larger than 25.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=10
**/

class imgGifNoFlicker extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $gif_control_extension = "/21f904[0-9a-f]{2}([0-9a-f]{4})[0-9a-f]{2}00/";
	
	function check() {
		foreach($this->getAllElements('img') as $img) {
			
			if(substr($img->getAttribute('src'), -4, 4) == '.gif') {
				$file = $this->getImageContent($this->getPath($img->getAttribute('src')));
				if($file) {
					  $file = bin2hex($file);
					
					  // sum all frame delays
					  $total_delay = 0;
					  preg_match_all($this->gif_control_extension, $file, $matches);
					  foreach ($matches[1] as $match) {
					    // convert little-endian hex unsigned ints to decimals
					    $delay = hexdec(substr($match,-2) . substr($match, 0, 2));
					    if ($delay == 0) $delay = 1;
					    $total_delay += $delay;
					  }
					
					  // delays are stored as hundredths of a second, lets convert to seconds
					  
					 
					 if($total_delay > 0)
					 	$this->addReport($img);
				}
			}
		}
	
	}
	
	function getImageContent($image) {
		if(strpos($image, '://') == false) {
			return @file_get_contents($image);
		}
		if(function_exists('curl')) {
			$curl = new curl_init($image);
			curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
			$result = curl_exec($curl);
			return $result;
		}
		return false;
	}
}



/**
*  OAC # 1
*  All img elements have an alt attribute.
*  All img elements must have an alt attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=1
**/

class imgHasAlt extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	/**
	*	@var int The OAC test Number
	*/
	var $oac_test = 1;

	/**
	*	@var int The test severity
	*/	
	var $severity = QUAIL_TEST_SEVERE;
	
	/**
	*	The check method of this test. We are iterating through all img
	*	elements and tagging any without an ALT attribute.
	*/
	function check() {
		foreach($this->getAllElements('img') as $img) {
			if(!$img->hasAttribute('alt'))
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 8
*  A long description is used for each img element that does not have Alt text conveying the same information as the image.
*  img element must contain a longdesc attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=8
**/

class imgHasLongDesc extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('longdesc')) {
				$this->addReport($img);
					
			}
		}
	
	}
}



/**
*  OAC # 5
*  Important images should not have spacer Alt text.
*  img element cannot have alt attribute value of whitespace if WIDTH and HEIGHT attribute values are both greater than 25.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=5
**/

class imgImportantNoSpacerAlt extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('src') && $img->hasAttribute('alt') && trim($img->getAttribute('alt')) == '') {
				if($img->getAttribute('width') > 25 || $img->getAttribute('height') > 25) {
					$this->addReport($img);
				}
				elseif(function_exists('gd_info') && (!$img->hasAttribute('width') || !$img->hasAttribute('height'))) {
					$img_file = @getimagesize($this->getPath($img->getAttribute('src')));
					if($img_file) {
						if($img_file[0] > 25 || $img_file[0] > 25)
							$this->addReport($img);
					}
				}
			}

		}
	
	}
}



/**
*  OAC # 13
*  All links in all client side image-maps are duplicated within the document.
*  img element must not contain a usemap attribute unless all links in the MAP are duplicated within the document. The MAP element is referred by the USEMAP element's usemap attribute. Links within MAP are referred by area elements href attribute contained by MAP element. [Editor's Note - can duplicate links appear anywhere within content or must they be part of a link group?]
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=13
**/

class imgMapAreasHaveDuplicateLink extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $placeholders = array('nbsp', '&nbsp;', 'spacer', 'image', 'img', 'photo', ' ');
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			$all_links[$a->getAttribute('href')] = $a->getAttribute('href');
		}
		$maps = $this->getElementsByAttribute('map', 'name', true);
		
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('usemap')) {
				$usemap = $img->getAttribute('usemap');
				if(substr($usemap, 0, 1) == '#')
					$key = substr($usemap, -(strlen($usemap) - 1), (strlen($usemap) - 1));
				else
					$key = $usemap;
				foreach($maps[$key]->childNodes as $child) {
					if($child->tagName == 'area') {
						
						if(!$all_links[$child->getAttribute('href')])
							$this->addReport($img);
					}
				}
			
			
			}
		}
	
	}
}



/**
*  OAC # 9
*  All img elements that have a longdesc attribute also have an associated 'd-link'.
*  img element that contains a longdesc attribute must have a following d-link. A d-link must consist of an A element that contains only the text "d" or "D". The A element must have an href attribute that is a valid URL and is the same as the img element's longdesc attribute. The d-link must immediately follow the img element, separated only by whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=9
**/

class imgNeedsLongDescWDlink extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('longdesc')) {
				$next = $this->getNextElement($img);
				
				if($next->tagName != 'a') 
					$this->addReport($img);
				else {
					
					if(((strtolower($next->nodeValue) != '[d]' && strtolower($next->nodeValue) != 'd') )
						|| $next->getAttribute('href') != $img->getAttribute('longdesc')) {
							$this->addReport($img);
					}
				}
					
			}
		}
	
	}
}



/**
*  OAC # 4
*  Non-Decorative images must have Alt text.
*  img element cannot have alt attribute value of null ("") if WIDTH and HEIGHT attribute values are both greater than 25.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=4
**/

class imgNonDecorativeHasAlt extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('src') && 
				($img->hasAttribute('alt') && html_entity_decode((trim($img->getAttribute('alt')))) == '')) {
				$this->addReport($img);
				
			}
		}
	
	}
}



/**
*  OAC # 14
*  For all img elements, text does not refer to the image by color alone.
*  This error is generated for all img elements that have a width and height greater than 100.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=14
**/

class imgNotReferredToByColorAlone extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('alt'))
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 170
*  Server-side image maps are not used except when image map regions cannot be defined using an available geometric shape.
*  A server-side image map should only be used when a client-side image map can not be used.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=170
**/

class imgServerSideMapNotUsed extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('ismap'))
				$this->addReport($img);
		}
	}
}


/**
*  OAC # 140
*  All img elements do not contain a title attribute.
*  img element must not contain the title attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=140
**/

class imgShouldNotHaveTitle extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('title'))
				$this->addReport($img);
		}
	
	}
}



/**
*  OAC # 12
*  All img elements with an ismap attribute have a valid usemap attribute.
*  img element may not contain an ismap attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=12
**/

class imgWithMapHasUseMap extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	function check() {
		foreach($this->getAllElements('img') as $img) {
			if($img->hasAttribute('ismap') && !$img->hasAttribute('usemap'))
				$this->addReport($img);
		}
	
	}
}


/**
*  OAC # 124
*  All img elements with images containing math expressions have equivalent MathML markup.
*  This error is generated for all img elements that have a width and height greater than 100.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=124
**/

class imgWithMathShouldHaveMathEquivalent extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('img') as $img) {
			if(($img->getAttribute('width') > 100 
				|| $img->getAttribute('height') > 100 )
				&& $img->nextSibling->tagName != 'math')
					$this->addReport($img);
		
		}
	}
}


/**
*  OAC # 130
*  All input elements, type of "checkbox", have a valid tab index.
*  input element that contains a type attribute value of "checkbox" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=130
**/

class inputCheckboxHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;
	var $tag = 'input';
	
	var $type = 'checkbox';
}


/**
*  OAC # 200
*  All checkbox groups are marked using fieldset and legend elements.
*  form element content must contain both fieldset and legend elements if there are related checkbox buttons.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=200
**/

class inputCheckboxRequiresFieldset extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'checkbox') {
				if(!$this->getParent($input, 'fieldset', 'body'))
					$this->addReport($input);
				
			}
		}
	}
}



/**
*  OAC # 54
*  input should not use color alone.
*  All input elements, except those with a type of "hidden", will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=54
**/

class inputDoesNotUseColorAlone extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') != 'hidden')
				$this->addReport($input);
		}
	}

}


/**
*  OAC # 193
*  All input elements, except those with with a type attribute value of "image", do not have an alt attribute.
*  The input element is used to create many kinds of form controls. Although the HTML DTD permits the alt attribute on all of these, it should be used only on image submit buttons. User agent support for this attribute on other types of form controls is not well defined, and other mechanisms are used to label these controls.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=193
**/

class inputElementsDontHaveAlt extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') != 'image' && $input->hasAttribute('alt'))
				$this->addReport($input);
		}
	}
}


/**
*  OAC # 131
*  All input elements, type of "file", have a valid tab index.
*  input element that contains a type attribute value of "file" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=131
**/

class inputFileHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;
	var $tag = 'input';
	
	var $type = 'file';
}



/**
*  OAC # 57
*  Alt text for all input elements with a type attribute value of "image" identifies the purpose or function of the image.
*  input element with type of "image" must have Alt text that identifies the purpose or function of the image.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=57
**/

class inputImageAltIdentifiesPurpose extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image')
				$this->addReport($input);
		}
	}

}



/**
*  OAC # 59
*  Image used in input element - Alt text should not be the same as the filename.
*  input elements cannot have alt attribute values that are the same as their src attribute values.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=59
**/

class inputImageAltIsNotFileName extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image' 
				&& strtolower($input->getAttribute('alt')) == strtolower($input->getAttribute('src')))
					$this->addReport($input);
		}
	}

}



/**
*  OAC # 60
*  Image used in input element - Alt text should not be placeholder text.
*  input elements cannot have alt attribute values that are (case insensitive) (exactly) \"image\""
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=60
**/

class inputImageAltIsNotPlaceholder extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $placeholders = array('nbsp', '&nbsp;', 'input', 'spacer', 'image', 'img', 'photo', ' ');
	
	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image') {
				if(in_array($input->getAttribute('alt'), $this->placeholders) || ord($input->getAttribute('alt')) == 194) {
					$this->addReport($input);
				}
				elseif(preg_match("/^([0-9]*)(k|kb|mb|k bytes|k byte)?$/", strtolower($input->getAttribute('alt')))) {
					$this->addReport($input);
				}
			}
		}
	
	}
}


/**
*  OAC # 58
*  Alt text for all input elements with a type attribute value of "image" is less than 100 characters (English) or the user has confirmed that the Alt text is as short as possible.
*  input elements must have alt attribute value of less than 100 characters (English).
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=58
**/

class inputImageAltIsShort extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image' && strlen($input->getAttribute('alt')) > 100)
				$this->addReport($input);
		}
	}

}


/**
*  OAC # 166
*  Alt text for all input elements with a type attribute value of "image" does not use the words "submit" or "button" (English).
*  Alt text for form submit buttons must not use the words "submit" or "button".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=166
**/

class inputImageAltNotRedundant extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $problem_words = array('submit', 'button');

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image') {
				foreach($this->problem_words as $word) {
					if(strpos($input->getAttribute('alt'), $word) !== false)
							$this->addReport($input);
				}
			}
		}
	}
}


/**
*  OAC # 56
*  All input elements with a type attribute value of "image" have an alt attribute.
*  input element with type of "image" must have an alt attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=56
**/

class inputImageHasAlt extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image' 
					&& (trim($input->getAttribute('alt')) == '' || !$input->hasAttribute('alt')))
				$this->addReport($input);
		}
	}

}


/**
*  OAC # 167
*  Alt text for all input elements with a type attribute value of "image" contains all non decorative text in the image.
*  This error is generated for all input elements that have a type of "image".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=167
**/

class inputImageNotDecorative extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'image')
				$this->addReport($input);
		}
	}
}


/**
*  OAC # 129
*  All input elements, type of "password", have a valid tab index.
*  input element that contains a type attribute value of "password" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=129
**/

class inputPasswordHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;
	var $tag = 'input';
	
	var $type = 'password';
}


/**
*  OAC # 128
*  All input elements, type of "radio", have a valid tab index.
*  input element that contains a type attribute value of "radio" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=128
**/

class inputRadioHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;
	var $tag = 'input';
	
	var $type = 'radio';
}


/**
*  OAC # 207
*  All input elements, type of "submit", have a valid tab index.
*  input element that contains a type attribute value of "submit" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=207
**/

class inputSubmitHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;
	var $tag = 'input';
	
	var $type = 'submit';
}


/**
*  OAC # 55
*  All input elements, type of "text", have an explicitly associated label.
*  input element that contains a type attribute value of "text" must have an associated label element. An associated label is one in which the for attribute value of the label element is the same as the id attribute value of the input element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=55
**/

class inputTextHasLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $tag = 'input';
	
	var $type = 'text';
	
	var $no_type = false;
}


/**
*  OAC # 127
*  All input elements, type of "text", have a valid tab index.
*  input element that contains a type attribute value of "text" must have a tabindex attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=127
**/

class inputTextHasTabIndex extends inputTabIndex {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'input';
	
	var $type = 'text';
}



/**
*  OAC # 61
*  input element, type of "text", must have default text.
*  input elements that have a type attribute value of "text" must also contain a value attribute that contains text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=61
**/

class inputTextHasValue extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'text' && !$input->hasAttribute('value'))
				$this->addReport($input);	
			
		}
	
	}
}


/**
*  OAC # 117
*  input control, type of "text", must have valid default text.
*  input element with a type of "text" cannot contain a VALUE attribute that is empty or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=117
**/

class inputTextValueNotEmpty extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	function check() {
		foreach($this->getAllElements('input') as $input) {
			if(!$input->hasAttribute('value') || trim($input->getAttribute('value')) == '')
					$this->addReport($input);
			
		}
	}
}


/**
*  OAC # 161
*  All label elements do not contain input elements.
*  label elements should not contain input elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=161
**/

class labelDoesNotContainInput extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('label') as $label) {
			if($this->elementHasChild($label, 'input') || $this->elementHasChild($label, 'textarea'))
				$this->addReport($label);
		}
	}
}


/**
*  OAC # 162
*  Each input element has only one associated label.
*  input element must have only one associated label element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=162
**/

class labelMustBeUnique extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	function check() {
		foreach($this->getAllElements('label') as $label) {
			if($label->hasAttribute('for'))
				$labels[$label->getAttribute('for')][] = $label;
		}
		if(is_array($labels)) {
			foreach($labels as $label) {
				if(count($label) > 1)
					$this->addReport($label[1]);
			}
		}
	}
}


/**
*  OAC # 163
*  Each label associated with an input element contains text.
*  Label must contain some text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=163
**/

class labelMustNotBeEmpty extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('label') as $label) {
			if(trim($label->nodeValue) == '') {
				$fail = true;
				foreach($label->childNodes as $child) {
					if($child->tagName == 'img' && trim($child->getAttribute('alt')) != '')
						$fail = false;
				}
				if($fail)
					$this->addReport($label);
				
			}
		}
	}
}


/**
*  OAC # 171
*  legend text describes the group of choices.
*  The legend must describe the group of choices.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=171
**/

class legendDescribesListOfChoices extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'legend';
}


/**
*  OAC # 172
*  legend text is not empty or whitespace.
*  The legend must describe the group of choices.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=172
**/

class legendTextNotEmpty extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('legend') as $legend) {
			if(!$legend->nodeValue || trim($legend->nodeValue) == '')
				$this->addReport($legend);
		}
	}
}


/**
*  OAC # 173
*  legend text is not placeholder text.
*  The legend must describe the group of choices.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=173
**/

class legendTextNotPlaceholder extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $placeholders = array('&nbsp;', ' ', 'legend');
	
	function check() {
		foreach($this->getAllElements('legend') as $legend) {
			if(in_array(trim($legend->nodeValue), $this->placeholders))
				$this->addReport($legend);
		}
	}

}

class liDontUseImageForBullet extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATe;

	function check() {
		foreach($this->getAllElements('li') as $li) {
			if(trim($li->nodeValue) != '' && $li->firstChild->tagName == 'img')
				$this->addReport($li);
		}
	
	}
}


/**
*  OAC # 135
*  Document should use LINK for alternate content.
*  head element must contain a link element with a rel attribute value that equals "alternate" and a href attribute value that is a valid URL.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=135
**/

class linkUsedForAlternateContent extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		$head = $this->getAllElements('head');
		$head = $head[0];
		foreach($head->childNodes as $child) {
			if($child->tagName == 'link' && $child->getAttribute('rel') == 'alternate')
				return true;
		}
		$this->addReport(null, null, false);
	}
}




/**
*  OAC # 134
*  Document uses link element to describe navigation if it is within a collection.
*  The link element can provide metadata about the position of an HTML page within a set of Web units or can assist in locating content with a set of Web units.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=134
**/

class linkUsedToDescribeNavigation extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		$head = $this->getAllElements('head');
		$head = $head[0];
		if($head->childNodes) {
			foreach($head->childNodes as $child) {
				if($child->tagName == 'link' && $child->getAttribute('rel') != 'stylesheet')
					return true;
			}
			$this->addReport(null, null, false);
		}
	}
}


/**
*  OAC # 78
*  List items must not be used to format text.
*  OL element should not contain only one LI element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=78
**/

class listNotUsedForFormatting extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements(array('ul', 'ol')) as $list) {
			$li_count = 0;
			foreach($list->childNodes as $child) {
				if($child->tagName == 'li')
					$li_count++;
			}
			if($li_count < 2)
				$this->addReport($list);
		}
	
	}
}


/**
*  OAC # 66
*  marquee element is not used.
*  This error will be generated for each marquee element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=66
**/

class marqueeIsNotUsed extends quailTagTest {

	var $default_severity = QUAIL_TEST_SEVERE;
	
	var $tag = 'marquee';

}


/**
*  OAC # 67
*  menu items should not be used to format text.
*  menu element must contain one LI element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=67
**/

class menuNotUsedToFormatText extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('menu') as $menu) {
			$list_items = 0;
			foreach($menu->childNodes as $child) {
				if($child->tagName == 'li')
					$list_items++;
			}
			if($list_items == 1)
				$this->addReport($menu);
		}
	
	}
}


/**
*  OAC # 144
*  noembed must have equivalent content.
*  This error is generated for each noembed element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=144
**/

class noembedHasEquivalentContent extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'noembed';
}



/**
*  OAC # 35
*  NOFRAMES section must contain text equivalent of FRAMES section.
*  This error is generated for each NOFRAMES element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=35
**/

class noframesSectionMustHaveTextEquivalent extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;
	
	
	function check() {
		foreach($this->getAllElements('frameset') as $frameset) {
			if(!$this->elementHasChild($frameset, 'noframes'))
				$this->addReport($frameset);
		}
		foreach($this->getAllElements('noframes') as $noframes) {
			$this->addReport($noframes);
		}
	}

}


/**
*  OAC # 72
*  Content must be usable when object are disabled.
*  If an object element contains a codebase attribute then the codebase attribute value must be null or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=72
**/

class objectContentUsableWhenDisabled extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}



/**
*  OAC # 29
*  All objects do not flicker.
*  This error is generated for all object elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=29
**/

class objectDoesNotFlicker extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';

}


/**
*  OAC # 70
*  object must not use color alone.
*  This error is generated for every applet element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=70
**/

class objectDoesNotUseColorAlone extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}


/**
*  OAC # 73
*  object user interface must be accessible.
*  If an object element contains a codebase attribute then the codebase attribute value must be null or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=73
**/

class objectInterfaceIsAccessible extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}



/**
*  OAC # 74
*  object link to multimedia file must have text transcript.
*  object element cannot contain type attribute value of "video".
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=74
**/

class objectLinkToMultimediaHasTextTranscript extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if($object->getAttribute('type') == 'video')
				$this->addReport($object);
			
		}
	}

}


/**
*  OAC # 77
*  All objects contain a text equivalent of the object.
*  object element must contain a text equivalent for the object in case the object can't be rendered.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=77
**/

class objectMustContainText extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if(!$object->nodeValue || trim($object->nodeValue) == '')
				$this->addReport($object);
		
		}
	}
}


/**
*  OAC # 158
*  Use the embed element within the object element.
*  Each object element must contain an embed element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=158
**/

class objectMustHaveEmbed extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if(!$this->elementHasChild($object, 'embed'))
				$this->addReport($object);
		}
	}
}


/**
*  OAC # 75
*  object must have a title.
*  object element must contain a title attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=75
**/

class objectMustHaveTitle extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if(!$object->hasAttribute('title'))
				$this->addReport($object);
			
		}
	}

}




/**
*  OAC # 76
*  object must have a valid title.
*  object element must not have a title attribute with value of null or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=76
**/

class objectMustHaveValidTitle extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $placeholders = array('nbsp', '&nbsp;', 'object', 'an object', 'spacer', 'image', 'img', 'photo', ' ');

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if($object->hasAttribute('title')) {
				if(trim($object->getAttribute('title')) == '')
					$this->addReport($object);
				elseif(!in_array(trim(strtolower($object->getAttribute('title'))), $this->placeholders))
					$this->addReport($object);
			}
		}
	}

}


/**
*  OAC # 204
*  object provides a keyboard mechanism to return focus to the parent window.
*  Ensure that keyboard users do not become trapped in a subset of the content that can only be exited using a mouse or pointing device.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=204
**/

class objectProvidesMechanismToReturnToParent extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	var $tag = 'object';
}


/**
*  OAC # 141
*  object may require a long description.
*  This error is generated for every object element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=141
**/

class objectShouldHaveLongDescription extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}


/**
*  OAC # 71
*  Text equivalents for object should be updated if object changes.
*  If an object element contains a codebase attribute then the codebase attribute value must be null or whitespace.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=71
**/

class objectTextUpdatesWhenObjectChanges extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}


/**
*  OAC # 119
*  Content must be usable when objects are disabled.
*  If object element contains a CLASSid attribute and any text then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=119
**/

class objectUIMustBeAccessible extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'object';
}


/**
*  OAC # 118
*  Text equivalents for object should be updated if object changes.
*  If object element contains a CLASSid attribute and any text then this error will be generated.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=118
**/

class objectWithClassIDHasNoText extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('object') as $object) {
			if($object->nodeValue && $object->hasAttribute('classid'))
				$this->addReport($object);
		
		}
	}
}


/**
*  OAC # 79
*  All p elements are not used as headers.
*  All p element content must not be marked with either b, i, u, strong, font, em.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=79
**/

class pNotUsedAsHeader extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $head_tags = array('strong', 'span', 'em', 'font', 'i', 'b', 'u');
	
	function check() {
		foreach($this->getAllElements('p') as $p) {
			if(($p->nodeValue == $p->firstChild->nodeValue)
				&& in_array($p->firstChild->tagName, $this->head_tags))
				$this->addReport($p);
		}
	}
}


/**
*  OAC # 109
*  All input elements, type of "password", have an explicitly associated label.
*  input element that contains a type attribute value of "password" must have an associated label element. An associated label is one in which the for attribute value of the label element is the same as the id attribute value of the input element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=109
**/

class passwordHasLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'input';
	
	var $type = 'password';
	
	var $no_type = false;
}


/**
*  OAC # 113
*  All input elements, type of "password", have a label that is positioned close to the control.
*  input element with a type attribute value of "password" must have an associated label element positioned close to it.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=113
**/

class passwordLabelIsNearby extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'password')
				$this->addReport($input);
			
		}
	}
}


/**
*  OAC # 139
*  pre element should not be used to create tabular layout.
*  This error is generated for each pre element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=139
**/

class preShouldNotBeUsedForTabularLayout extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('pre') as $pre) {
			$rows = preg_split('/[\n\r]+/', $pre->nodeValue);
			if(count($rows) > 1)
				$this->addReport($pre);
		}
	
	}
}


/**
*  OAC # 112
*  All input elements, type of "radio", have an explicitly associated label.
*  input element that contains a type attribute value of "radio" must have an associated label element. An associated label is one in which the for attribute value of the label element is the same as the id attribute value of the input element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=112
**/

class radioHasLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'input';
	
	var $type = 'radio';
	
	var $no_type = false;
}


/**
*  OAC # 116
*  All input elements, type of "radio", have a label that is positioned close to the control.
*  input element with a type attribute value of "radio" must have an associated label element positioned close to it.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=116
**/

class radioLabelIsNearby extends quailTest {

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'radio')
				$this->addReport($input);
			
		}
	}
}



/**
*  OAC # 148
*  All radio button groups are marked using fieldset and legend elements.
*  form element content must contain both fieldset and legend elements if there are related radio buttons.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=148
**/

class radioMarkedWithFieldgroupAndLegend extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('input') as $input) {
			if($input->getAttribute('type') == 'radio') {
				$radios[$input->getAttribute('name')][] = $input;
			}
		}
		if(is_array($radios)) {
			foreach($radios as $radio) {
				if(count($radio > 1)) {
					if(!$this->getParent($radio[0], 'fieldset', 'body'))
						$this->addReport($radio[0]);
				}
			}
		}
	}
}

/**
*	@todo This should really only fire once and shouldn't extend quailTagTest
*/

/**
*  OAC # 82
*  Content must be accessible when script is disabled.
*  This error will be generated for all script elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=82
**/

class scriptContentAccessibleWithScriptsTurnedOff extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'script';
}


/**
*  OAC # 84
*  script must have a noscript section.
*  script elements that occur within the body must be followed by a noscript section.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=84
**/

class scriptInBodyMustHaveNoscript extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('script') as $script) {
			if($script->nextSibling->tagName != 'noscript' 
				&& $script->parentNode->tagName != 'head')
					$this->addReport($script);
		
		}
	}

}


/**
*  OAC # 93
*  All onclick event handlers have an associated onkeypress event handler.
*  Any element that contains an onclick attribute must also contain an onkeypress attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=93
**/

class scriptOnclickRequiresOnKeypress extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $click_value = 'onclick';
	
	var $key_value = 'onkeypress';
	
	function check() {
		foreach($this->getAllElements(array_keys(htmlElements::$html_elements)) as $element) {
			if(($element->hasAttribute($this->click_value)) && !$element->hasAttribute($this->key_value))
				$this->addReport($element);
		}
	}

}


/**
*  OAC # 94
*  All ondblclick event handlers have corresponding keyboard-specific functions.
*  Any element that contains an ondblclick  attribute will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=94
**/

class scriptOndblclickRequiresOnKeypress extends scriptOnclickRequiresOnKeypress {

	var $click_value = 'ondblclick';
}


/**
*  OAC # 95
*  All onmousedown event handlers have an associated onkeydown event handler.
*  Any element that contains an onmousedown attribute must also contain an onkeydown attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=95
**/

class scriptOnmousedownRequiresOnKeypress extends scriptOnclickRequiresOnKeypress {

	var $click_value = 'onmousedown';
	
	var $key_value = 'onkeydown';
}


/**
*  OAC # 96
*  All onmousemove event handlers have corresponding keyboard-specific functions.
*  Any element that contains an onmousemove attribute will generate this error.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=96
**/

class scriptOnmousemove extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $click_value = 'onmousemove';
	
	var $key_value = 'onkeypress';
	
	function check() {
		foreach($this->getAllElements(array_keys(htmlElements::$html_elements)) as $element) {
			if(($element->hasAttribute($this->click_value)))
				$this->addReport($element);
		}
	}

}


/**
*  OAC # 97
*  All onmouseout event handlers have an associated onblur event handler.
*  Any element that contains an onmouseout attribute must also contain an onblur attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=97
**/

class scriptOnmouseoutHasOnmouseblur extends scriptOnclickRequiresOnKeypress {

	var $click_value = 'onmouseout';
	
	var $key_value = 'onblur';
}



/**
*  OAC # 98
*  All onmouseover event handlers have an associated onfocus event handler.
*  Any element that contains an onmouseover attribute must also contain an onfocus attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=98
**/

class scriptOnmouseoverHasOnfocus extends scriptOnclickRequiresOnKeypress {

	var $click_value = 'onmouseover';
	
	var $key_value = 'onfocus';
}



/**
*  OAC # 99
*  All onmouseup event handlers have an associated onkeyup event handler.
*  Any element that contains an onmouseup attribute must also contain an onkeyup attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=99
**/

class scriptOnmouseupHasOnkeyup extends scriptOnclickRequiresOnKeypress {

	var $click_value = 'onmouseup';
	
	var $key_value = 'onkeyup';
}


/**
*  OAC # 83
*  User interface for script must be accessible.
*  This error will be generated for all script elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=83
**/

class scriptUIMustBeAccessible extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'script';
}


/**
*  OAC # 81
*  script should not cause screen flicker.
*  This error will be generated for all script elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=81
**/

class scriptsDoNotFlicker extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'script';
}


/**
*  OAC # 80
*  Color alone should not be used in the script.
*  This error will be generated for all script elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=80
**/

class scriptsDoNotUseColorAlone extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'script';
}


/**
*  OAC # 86
*  All select elements do not cause an extreme change in context.
*  select element cannot contain onchange attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=86
**/

class selectDoesNotChangeContext extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('select') as $select) {
			if($select->hasAttribute('onchange'))
				$this->addReport($select);
		
		}
	}
}


/**
*  OAC # 85
*  All select elements have an explicitly associated label.
*  select element must have an associated label element. A label element is associated with the select element if the for attribute value of the label is the same as the id attribute of the select element.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=85
**/

class selectHasAssociatedLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'select';
	
	var $no_type = true;
}


/**
*  OAC # 149
*  All select elements containing a large number options also contain optgroup elements.
*  select element content that contains 4 or more option elements must contain at least 2 optgroup elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=149
**/

class selectWithOptionsHasOptgroup extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('select') as $select) {
			$options = 0;
			foreach($select->childNodes as $child) {
				if($child->tagName == 'option')
					$options++;
			}
			if($options >= 4)
				$this->addReport($select);
		}
	}
}


/**
*  OAC # 159
*  Sites must have a site map.
*  Each site must have a site map.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=159
**/

class siteMap extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;
	
	var $cms = false;
	
	function check() {
		foreach($this->getAllElements('a') as $a) {
			if(strtolower(trim($a->nodeValue)) == 'site map')
				return true;
		}
		$this->addReport(null, null, false);
	}
}


/**
*  OAC # 27
*  A "skip to content" link appears on all pages with blocks of material prior to the main document.
*  Provide a mechanism to bypass blocks of material that are repeated on multiple Web units.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=27
**/

class skipToContentLinkProvided extends quailTest {
	
	var $cms = false;
	
	var $default_severity = QUAIL_TEST_MODERATE;
	
	var $search_words = array('navigation', 'skip', 'content');
	
	function check() {
		$first_link = $this->getAllElements('a');
		if(!$first_link) {
			$this->addReport(null, null, false);
			return null;
		}
		$a = $first_link[0];
		
		if(substr($a->getAttribute('href'), 0, 1) == '#') {
			
			$link_text = explode(' ', strtolower($a->nodeValue));
			if(!in_array($this->search_words, $link_text)) {
				$report = true;
				foreach($a->childNodes as $child) {
					if(method_exists($child, 'hasAttribute')) {
						if($child->hasAttribute('alt')) {
							$alt = explode(' ', strtolower($child->getAttribute('alt') . $child->nodeValue));
							foreach($this->search_words as $word) {
								if(in_array($word, $alt)) {
									$report = false;
								}
							}
						}
					}
				}
				if($report) {
					$this->addReport(null, null, false);
				}
			}
		
		}
		else
			$this->addReport(null, null, false);

	}

} 


/**
*  OAC # 208
*  The tab order specified by tabindex attributes follows a logical order.
*  Provide a logical tab order when the default tab order does not suffice.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=208
**/

class tabIndexFollowsLogicalOrder extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;
	
	function check() {
		$index = 0;
		foreach($this->getAllElements(null, 'form') as $form) {
			if(is_numeric($form->getAttribute('tabindex'))
				&& intval($form->getAttribute('tabindex')) != $index + 1)
					$this->addReport($form);
			$index++;
		}
	}
}


/**
*  OAC # 195
*  Table captions identify the table.
*  If the table has a caption then the caption must identify the table.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=195
**/

class tableCaptionIdentifiesTable extends quailTagTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	var $tag = 'caption';
}


/**
*  OAC # 102
*  All complex data tables have a summary.
*  The summary is useful when the table has a complex structure (for example, when there are several sets of row or column headers, or when there are multiple groups of columns or rows). The summary may also be helpful for simple data tables that contain many columns or rows of data.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=102
**/

class tableComplexHasSummary extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if(!$table->hasAttribute('summary') && $table->firstChild->tagName != 'caption') {
				$this->addReport($table);
			
			
			}
		}
	
	}
}


/**
*  OAC # 125
*  All data tables contain th elements.
*  Data tables must have th elements while layout tables can not have th elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=125
**/

class tableDataShouldHaveTh extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if(!$this->isData($table))
				$this->addReport($table);
		
		}
	
	}

}


/**
*  OAC # 138
*  Substitutes for table header labels must be terse.
*  abbr attribute value on th element must be less than 20 characters (English).
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=138
**/

class tableHeaderLabelMustBeTerse extends quailTableTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			foreach($table->childNodes as $child) {
				if($child->tagName == 'tr') {
					foreach($child->childNodes as $td) {
						if($td->tagName == 'th') {
							if(strlen($td->getAttribute('abbr')) > 20)
								$this->addReport($td);
						
						}
					}
				}
			}
			
		}
	
	}
}


/**
*  OAC # 186
*  Use thead to group repeated table headers, tfoot for repeated table footers, and tbody for other groups of rows.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=186
**/

class tableIsGrouped extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if(!$this->elementHasChild($table, 'thead') 
					|| !$this->elementHasChild($table, 'tbody') 
					|| !$this->elementHasChild($table, 'tfoot')) {
				$rows = 0;
				foreach($table->childNodes as $child) {
					if($child->tagName == 'tr')
						$rows ++;
				}
				if($rows > 4)
					$this->addReport($table);
			}		
		}
	
	}
}


/**
*  OAC # 126
*  All layout tables do not contain th elements.
*  Data tables must have th elements while layout tables can not have th elements.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=126
**/

class tableLayoutDataShouldNotHaveTh extends quailTableTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($this->isData($table))
				$this->addReport($table);
		
		}
	
	}

}


/**
*  OAC # 106
*  All layout tables do not contain caption elements.
*  table element content cannot contain a caption element if it's a layout table.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=106
**/

class tableLayoutHasNoCaption extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($this->elementHasChild($table, 'caption')) {
				$first_row = true;
				foreach($table->childNodes as $child) {
					if($child->tagName == 'tr' && $first_row) {
						if(!$this->elementHasChild($child, 'th'))
							$this->addReport($table);
						$first_row = false;
					}
				}
			}
		}
	
	}
}


/**
*  OAC # 105
*  All layout tables have an empty summary attribute or no summary attribute.
*  The table element, summary attribute for all layout tables contains no printable characters or is absent.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=105
**/

class tableLayoutHasNoSummary extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($table->hasAttribute('summary') && strlen(trim($table->getAttribute('summary'))) > 1) {
				$first_row = true;
				foreach($table->childNodes as $child) {
					if($child->tagName == 'tr' && $first_row) {
						if(!$this->elementHasChild($child, 'th'))
							$this->addReport($table);
						$first_row = false;
					}
				}
			}
		}
	
	}
}


/**
*  OAC # 122
*  All layout tables make sense when linearized.
*  This error is generated for all layout tables.  If the table contains th elements then it is a data table. If the table does not contain th elements then it is a layout table.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=122
**/

class tableLayoutMakesSenseLinearized extends quailTableTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if(!$this->isData($table))
				$this->addReport($table);
		
		}
	
	}

}


/**
*  OAC # 176
*  All data table summaries describe navigation and structure of the table.
*  The table summary can't be garbage text.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=176
**/

class tableSummaryDescribesTable extends quailTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($table->hasAttribute('summary'))
				$this->addReport($table);
		}
	}
}



/**
*  OAC # 196
*  Table summaries do not duplicate the table captions.
*  The summary and the caption must be different. Caption identifies the table. Summary describes the table contents.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=196
**/

class tableSummaryDoesNotDuplicateCaption extends quailTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($this->elementHasChild($table, 'caption') && $table->hasAttribute('summary')) {
				foreach($table->childNodes as $child) {
					if($child->tagName == 'caption')
						$caption = $child;
				}
				if(strtolower(trim($caption->nodeValue)) == 
						strtolower(trim($table->getAttribute('summary'))) ) 
				 $this->addReport($table);
				
			}
		}
	}
}


/**
*  OAC # 103
*  All data table summaries contain text.
*  table element cannot contain an empty summary attribute if it's a data table.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=103
**/

class tableSummaryIsEmpty extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($table->hasAttribute('summary') && trim($table->getAttribute('summary')) == '') {
				$this->addReport($table);
			
			
			}
		}
	
	}
}


/**
*  OAC # 104
*  All data table summaries are greater than 10 printable characters (English).
*  table element, summary attribute value must be greater than 10 characters (English) if it's a data table.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=104
**/

class tableSummaryIsSufficient extends quailTableTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($table->hasAttribute('summary') && strlen(trim($table->getAttribute('summary'))) < 11) {
				$this->addReport($table);
			
			
			}
		}
	
	}
}


/**
*  OAC # 187
*  Use colgroup and col elements to group columns.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=187
**/

class tableUseColGroup extends quailTableTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($this->isData($table)) {
				if(!$this->elementHasChild($table, 'colgroup') && !$this->elementHasChild($table, 'col'))
					$this->addReport($table);
			}
		}
	
	}
}


/**
*  OAC # 137
*  Long table header labels require terse substitutes.
*  th element content must be less than 20 characters (English) if th element does not contain abbr attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=137
**/

class tableUsesAbbreviationForHeader extends quailTableTest {

	var $default_severity = QUAIL_TEST_SUGGESTION;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			foreach($table->childNodes as $child) {
				if($child->tagName == 'tr') {
					foreach($child->childNodes as $td) {
						if($td->tagName == 'th') {
							if(strlen($td->nodeValue) > 20 && !$td->hasAttribute('abbr'))
								$this->addReport($table);
						
						}
					}
				}
			}
			
		}
	
	}
}


/**
*  OAC # 136
*  All data tables contain a caption unless the table is identified within the document.
*  Tables must be identified by a caption unless they are identified within the document.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=136
**/

class tableUsesCaption extends quailTableTest {

	var $default_severity = QUAIL_TEST_SEVERE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($table->firstChild->tagName != 'caption')
				$this->addReport($table);
			
		}
	
	}
}


/**
*  OAC # 197
*  Data tables that contain both row and column headers use the scope attribute to identify cells.
*  The scope attribute may be used to clarify the scope of any cell used as a header.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=197
**/

class tableWithBothHeadersUseScope extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			$fail = false;
			foreach($table->childNodes as $child) {
				if($child->tagName == 'tr') {
					if($child->firstChild->tagName == 'td') {
						if(!$child->firstChild->hasAttribute('scope'))
							$fail = true;
					}
					else {
						foreach($child->childNodes as $td) {
							if($td->tagName == 'th' && !$td->hasAttribute('scope'))
								$fail = true;
						}
					}
				}
			}
			if($fail)
				$this->addReport($table);
		}
	}
}


/**
*  OAC # 198
*  Data tables that contain more than one row/column of headers use the id and headers attributes to identify cells.
*  id and headers attributes allow screen readers to speak the headers associated with each data cell when the relationships are too complex to be identified using the th element alone or the th element with the scope attribute.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=198
**/

class tableWithMoreHeadersUseID extends quailTableTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements('table') as $table) {
			if($this->isData($table)) {
				
				$row = 0;
				$multi_headers = false;
				foreach($table->childNodes as $child) {
					if($child->tagName == 'tr') {
						$row ++;
						foreach($child->childNodes as $cell) {
							if($cell->tagName == 'th') {
								$th[] = $cell;
								if($row > 1) 
									$multi_headers = true;	
							}
								
						}
					}
				}
				if($multi_headers) {
					$fail = false;
					foreach($th as $cell) {
						if(!$cell->hasAttribute('id'))
							$fail = true;
					}
					if($fail)
						$this->addReport($table);
				} 
				
			}
		}
	}
}


/**
*  OAC # 194
*  Table markup is used for all tabular information.
*  The objective of this technique is to present tabular information in a way that preserves relationships within the information even when users cannot see the table or the presentation format is changed.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=194
**/

class tabularDataIsInTable extends quailTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	function check() {
		foreach($this->getAllElements(null, 'text') as $text) {
			if(strpos($text->nodeValue, "\t") !== false || $text->tagName == 'pre')
				$this->addReport($text);
		}
	}
}


/**
*  OAC # 87
*  All textarea elements have an explicitly associated label.
*  All textarea elements must have an explicitly associated label.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=87
**/

class textareaHasAssociatedLabel extends inputHasLabel {

	var $default_severity = QUAIL_TEST_SEVERE;

	var $tag = 'textarea';
	
	var $no_type = true;
}


/**
*  OAC # 88
*  All textarea elements have a label that is positioned close to control.
*  textarea element must have an associated label element that is positioned close to it.
*  @link http://checker.atrc.utoronto.ca/servlet/ShowCheck?lang=eng&check=88
**/

class textareaLabelPositionedClose extends quailTagTest {

	var $default_severity = QUAIL_TEST_MODERATE;

	var $tag = 'textarea';
}

/*@}*/