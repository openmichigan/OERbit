<?php   // $Id: accessible_content.quail.inc,v 1.1.2.20 2010/08/06 23:59:36 kevee Exp $

/**
*   @file
*   Custom guideline class and reporter class for the accessible_content
*   module.
*/

class Accessible_contentGuideline extends quailGuideline{

  var $tests = array();
  
  /**
  *  An override of the default 'run' method which loads node information about the guidelin's tests
  */
  function run($arg = NULL) {
    $this->loadModuleTests();
    if ($arg['ac_module_guideline']) {
      $guideline = $arg['ac_module_guideline'];
      foreach ($guideline->accessibility_tests as $test_nid => $title) {
        $result = db_query('SELECT nid, test_name, severity FROM {accessible_content_node_test} WHERE nid = %d', $test_nid);
        $test = db_fetch_object($result);
        $severity = ($test->severity)
          ? $test->severity
          : 2;
        if ($arg['display_level'][$severity]) {
        $this->tests[$test->test_name] = array(
          'severity' => $severity,
          'nid' => $test->nid,
          'translation' => $title,
        );
    }
      }
    }
    if ($arg['ac_module_test']) {
      $this->tests[$arg['ac_module_test']->ac_function_name] = array(
                        'severity' => $arg['ac_module_test']->severity,
                        'nid' => $arg['ac_module_test']->nid,
                        'translation' => $arg['ac_module_test']->title,
                      );
    }
    unset($arg['ac_module_guideline']);
    parent::run($arg);
  }
  
  /**
  * A helper function to load all the modules which implement the accessible_content_test hook
  */
  private function loadModuleTests() {
    $tests = module_invoke_all('accessible_content_test');
    foreach ($tests as $test) {
      if ($test['file']) {
        require_once($test['file']);
      }
    }
  }
  
  /**
  *  We are overriding the default loadTranslations which uses files and is not needed here.
  */
  function loadTranslations() {

  }

  /**
  *  A helper function to get a node.
  *  @param string The test name
  *  @return object A full Drupal node object
  */
  function getNode($test) {
    return node_load($this->tests[$test]['nid']);
  }

  /**
  *  Returns the test translation
  */
  function getTranslation($test) {
    return $this->tests[$test]['translation'];
  }


}


/**
*  An array reporter that simply returns an unformatted and nested PHP array of
*  tests and report objects
*/

class reportAccessibleContent extends quailReporter {

  /**
  *  Generates a static list of errors within a div.
  *  @return array A nested array of tests and problems with Report Item objects
  */
  function getReport() {
    if (!is_object($this->guideline)) {
      return array();
    }
    $results = $this->guideline->getReport();
    if (!is_array($results))
      return array();
    foreach ($results as $testname => $test) {
      $severity = $this->guideline->getSeverity($testname);
      $output[$severity][$testname]['severity'] = $severity;
      $output[$severity][$testname]['title'] =  $this->translation[$testname];
      $output[$severity][$testname]['body'] = $this->guideline->getTranslation($testname);
      if (method_exists($this->guideline, 'getNode')) {
        $output[$severity][$testname]['node'] = $this->guideline->getNode($testname);
      }
      if (is_array($test)) {
        foreach ($test as $k => $problem) {
          if (is_object($problem)) {
            $output[$severity]['total']++;
            $output[$severity][$testname]['problems'][$k]['element'] =  htmlentities($problem->getHtml());
            $output[$severity][$testname]['problems'][$k]['line'] =  $problem->getLine();
            if ($problem->message) {
              $output[$severity][$testname]['problems']['message'] = $problem->message;
            }
            $output[$severity][$testname]['problems']['pass'] = $problem->pass;
          }
        }
      }
    }
    return $output;
  }
}

/**
*
*
*/
require_once('sites/all/libraries/quail/quail/reporters/reporter.demo.php');
class reportAccessibleContentHighlight extends reportDemo {

  /**
  *  @var array An array of the classnames to be associated with items
  */
  var $classnames = array(QUAIL_TEST_SEVERE => 'quail_severe',
              QUAIL_TEST_MODERATE => 'quail_moderate',
              QUAIL_TEST_SUGGESTION => 'quail_suggestion',
              );

  /**
  *  The getReport method - we iterate through every test item and
  *  add additional attributes to build the report UI.
  *  @return string A fully-formed HTML document.
  */
  function getReport() {
    if (!is_object($this->guideline)) {
      return array();
    }
    $problems = $this->guideline->getReport();
    if (is_array($problems)) {
      foreach ($problems as $testname => $test) {
        if ((!isset($this->options->display_level) || $this->options->display_level >= $test['severity']) && is_array($test)) {
          foreach ($test as $k => $problem) {
            if (is_object($problem) && property_exists($problem, 'element') && is_object($problem->element)) {
              
              $problem->element->removeAttribute('quail_style_index');
              $existing = $problem->element->getAttribute('class');
              $problem->element->setAttribute('class',
                $existing .' '. $this->options->highlight_classes[$test['severity']]);
              if ($this->options->image_url) {
                $test_node = $this->guideline->getNode($testname);
                $link = $this->dom->createElement('a');
                $link = $problem->element->parentNode->insertBefore($link, $problem->element);
                $link->setAttribute('class', 'highlight-link');
                $link->setAttribute('href', base_path() .'node/'. $test_node->nid);
                $link->setAttribute('title', $test_node->title);
                $image = $this->dom->createElement('img');
                $image = $link->appendChild($image);
                $image->setAttribute('alt', $testname);
                if ($problem->message) {
                  $image->setAttribute('title', $problem->message);
                }
                $image->setAttribute('src', $this->options->image_url[$test['severity']]);

              }
              //$problem->nodeValue .= $this->guideline->getSeverity($k);
            }
          }
        }
      }
    }

    return $this->dom->saveHTML();
  }

}