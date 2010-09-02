<?php

class TestOfQuailTests extends UnitTestCase {
 
	function getTest($file, $test) {
		$name = explode('-', $file);
		
		$filename = 'testfiles/quail/'. $file;
		 $quail = new quail($filename, 'wcag1a', 'file');
		$quail->runCheck();
		
		return $quail->getTest($test);
	}
	
	function test_svgContainsTitle() {
		$results = $this->getTest('svgContainsTitle-fail.html', 'svgContainsTitle');
		$this->assertTrue($results[0]->element->tagName == 'svg');
		$results = $this->getTest('svgContainsTitle-pass.html', 'svgContainsTitle');
		$this->assertTrue(count($results) == 0);
	}
	function test_cssTextHasContrast() {
		$results = $this->getTest('cssContrast.html', 'cssTextHasContrast');
		$this->assertTrue($results[0]->element->tagName == 'p');
	}
	
	function test_complexCssTextHasContrast() {
		$results = $this->getTest('cssContrast2.html', 'cssTextHasContrast');
		$this->assertTrue($results[0]->element->tagName == 'p');
	}
	
	function test_cssTextContrastWithColorConversion() {
		$results = $this->getTest('cssContrast3.html', 'cssTextHasContrast');
		$this->assertTrue($results[0]->element->tagName == 'div');
		
	}
	
	function test_cssTextContrastWithComplexBackground() {
		$results = $this->getTest('cssContrast4.html', 'cssTextHasContrast');
		$this->assertTrue($results[0]->element->tagName == 'pre');
		
	}
	function test_cssTextContrastWithInlineAndIncludedFiles() {
		$results = $this->getTest('cssContrast5.html', 'cssTextHasContrast');
		$this->assertTrue($results[0]->element->tagName == 'pre');
		
	}
	function test_videoProvidesCaptions() {
		$results = $this->getTest('videoTestFail.html', 'videoProvidesCaptions');
		$this->assertTrue($results[0]->element->tagName == 'video');
		
	}
	
	function test_videosEmbeddedOrLinkedNeedCaptions() {
		$results = $this->getTest('videosEmbeddedOrLinkedNeedCaptions-fail.html',
								  'videosEmbeddedOrLinkedNeedCaptions');
		$this->assertTrue($results[0]->element->tagName == 'a');
	
		$results = $this->getTest('videosEmbeddedOrLinkedNeedCaptions-pass.html', 
								  'videosEmbeddedOrLinkedNeedCaptions');
		$this->assertTrue(count($results[0]) == 0);
	
	}
	
	function test_documentIsWrittenClearly() {
		$results = $this->getTest('documentIsWrittenClearly-fail.html', 'documentIsWrittenClearly');
		$this->assertTrue($results[0]->element->tagName == 'p');
	
		$results = $this->getTest('documentIsWrittenClearly-pass.html', 'documentIsWrittenClearly');
		$this->assertTrue(count($results[0]) == 0);

		$results = $this->getTest('documentIsWrittenClearly-pass-2.html', 'documentIsWrittenClearly');
		$this->assertTrue(count($results[0]) == 0);
	
	} 

}

$tests = &new TestOfQuailTests();
$tests->run(new HtmlReporter());