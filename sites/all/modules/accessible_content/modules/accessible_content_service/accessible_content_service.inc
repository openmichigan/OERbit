<?php // $Id: accessible_content_service.inc,v 1.1.2.1 2009/12/15 17:51:44 kevee Exp $

/**
*  @file Contains all the callbacks for service methods
*/

/**
*  The service callback for checking a string
*  @param $html The HTML string to cehck
*  @param $guideline_nid The node ID of the guideline to use
*  @return array An array of Quail results
*/
function accessible_content_service_check($html, $guideline_nid) {
  $results = accessible_content_check_string($html, $guideline_nid);
  return $results;
}

/**
*  Returns a list of all the guidelines offered by this site
*  @return array An array of guideline nodes
*/
function accessible_content_service_get_guidelines() {
  $results = db_query('SELECT nid FROM {node} WHERE type = "accessibility_guideline" AND status = 1');
  $guidelines = array();
  while ($guideline = db_fetch_object($results)) {
    $guideline = node_load($guideline->nid);
    $guidelines[$guideline->nid] = array('id' => $guideline->nid,
                       'title' => $guideline->title,
                       'tests' => $guideline->accessibility_tests,
                       );
  }
  return $guidelines;
}

/*
*  Returns a list of all the tests offered by this site
*  @return array An array of guideline nodes
*/
function accessible_content_service_get_tests() {
  $results = db_query('SELECT nid FROM {node} WHERE type = "accessibility_test" AND status = 1');
  $tests = array();
  while ($test = db_fetch_object($results)) {
    $test = node_load($test->nid);
    $tests[$test->nid] = array('id' => $test->nid,
                       'title' => $test->title,
                       'body' => $test->body,
                       'quail_function' => $test->ac_function_name,
                       'severity' => $test->severity,
                       );
  }
  return $tests;
}