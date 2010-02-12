<?php

/**
*	An array reporter that simply returns an unformatted and nested PHP array of 
*	tests and report objects
*/

class reportArray extends quailReporter {
	
	/**
	*	Generates a static list of errors within a div.
	*	@return array A nested array of tests and problems with Report Item objects
	*/
	function getReport() {
		$results = $this->guideline->getReport();
		if(!is_array($results))
			return null;
		foreach($results as $testname => $test) {
			$translation = $this->guideline->getTranslation($testname);
			$output[$testname]['severity'] = $this->guideline->getSeverity($testname);
			$output[$testname]['title'] =  $translation['title'];
			$output[$testname]['body'] = $translation['description']
			foreach($test as $k => $problem) {
				if(is_object($problem)) {
					$output[$testname]['problems'][$k]['element'] =  htmlentities($problem->getHtml());
					$output[$testname]['problems'][$k]['line'] =  $problem->getLine();
					if($problem->message) {
						$output[$testname]['problems']['message'] = $problem->message;
					}
					$output[$testname]['problems']['pass'] = $problem->pass;
				}
			}
		}
		return $output;
	}
}