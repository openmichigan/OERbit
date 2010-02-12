<?php



class TestOfCSSTests extends UnitTestCase {
 
 function getTest($file, $test) {
 		$filename = 'testfiles/css/'. $file;
        $quail = new quail($filename, 'wcag1a', 'file');

		$quail->runCheck();
		return $quail->getTest($test); 	
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
}


$tests = &new TestOfCSSTests();
$tests->run(new HtmlReporter());
//die();