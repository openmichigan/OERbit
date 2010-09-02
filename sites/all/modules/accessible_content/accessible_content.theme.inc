<?php
// $Id: accessible_content.theme.inc,v 1.1.2.6 2010/04/12 02:01:57 kevee Exp $

/**
*   @file
*   Themes for Accessible Content
*/

/**
*  Theme function to format a single error reported
*  @param array $error An array as returned by the class AccessibleContentReporter
*/
function theme_accessible_content_report_error($error, $field = NULL, $highlight = TRUE) {
  $node = menu_get_object();
  $list = '';
  if (is_array($error['problems'])) {
    $items = array();
    foreach ($error['problems'] as $label => $problem) {
      if ($label == 'pass' && $problem === FALSE) {
        $items[] = '<strong>'. t('Test failed') .'</strong>';
      }
      elseif (is_int($label)) {
        $items[] = $problem['element'];
      }
    }
    $list = theme('item_list', $items);
  }
  $field_url = ($field['field'])
           ? '/'. $field['field'] .'/'. $field['delta']
           : '';

  if (count($items) > 0) {
    $output =  '<div class="ac-test ac-test-error">';
    $output .= theme('image',
             drupal_get_path('module', 'accessible_content')   .'/images/error.png',
                t('Test Failed'), t('Test Failed'));
    $output .= '<span class="highlight">';
    if ($highlight) {
      $output .= l('Highlight Problems',
           'node/'. $node->nid .'/accessibility/highlight/'. $error['node']->nid . $field_url);
    }
     $output .= '</span><h4>'. l($error['node']->title, 'node/'. $error['node']->nid) .'</h4>';
    $output .= $list .'</div>';
  }
  elseif (variable_get('ac_error_display', 0)) {
    $output  = '<div class="ac-test ac-test-ok">';
    $output .= theme('image',
            drupal_get_path('module', 'accessible_content') .'/images/ok.png',
                  t('Test Passed'), t('Test Passed'));
    $output .= '<span class="highlight">';
    if ($highlight) {
      $output .= l('Highlight Problems',
             'node/'. $node->nid .'/accessibility/highlight/'. $error['node']->nid);
  }
     $output .= '</span> <h4>'. l($error['node']->title, 'node/'. $error['node']->nid) .'</h4></div>';
  }
  return $output;
}
