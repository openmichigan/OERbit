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
/** \addtogroup reporters */
/*@{*/
/**
*	A static reporter. Generates a list of errors which do not pass and their severity.
*	This is just a demonstration of what you can do with a reporter.
*/

class reportStatic extends quailReporter {
	
	/**
	*	Generates a static list of errors within a div.
	*	@return string A fully-formatted report
	*/
	function getReport() {
		foreach($this->guideline->getReport() as $testname => $test) {
			if(count($test) > 0) {
				$severity = $this->guideline->getSeverity($testname);
				$translation = $this->guideline->getTranslation($testname);
				$output .= '<div><h3>'. $translation['title'] .'</h3><div>'. $translation['description'] .'</div>';
				if(is_array($test)) {
					foreach($test as $k => $problem) {
						if(is_object($problem))
							$output .= '<p><strong>'.($k+1).'</strong><pre>'. htmlentities($problem->getHtml()) .'</pre></p>';
						
					}
				}
				$output .='</p>';
				switch($severity) {
					case QUAIL_TEST_SEVERE:
						$output .= 'Severe error';
						break;
					case QUAIL_TEST_MODERATE:
						$output .= 'Moderate error';
						break;
					case QUAIL_TEST_SUGGESTION:
						$output .= 'Suggestion';
						break;
				}
				$output .='</p></div>';
			}
		}
		return $output;
	}
}
/*@}*/