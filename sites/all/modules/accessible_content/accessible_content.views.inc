<?php
// $Id: accessible_content.views.inc,v 1.1.2.6 2010/06/10 22:19:05 kevee Exp $
/**
*  @file
*  Views integration
*/

/**
*  Implementation of hook_views_data()
*/
function accessible_content_views_data() {
  $data['accessible_content_node_totals']['table']['group'] = t('Accessibility');
  $data['accessible_content_node_totals']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['accessible_content_node_totals']['severe_total'] = array(
    'title' => t('Severe Totals'),
    'help' => t('The total number of tests which failed that were considered severe errors'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['accessible_content_node_totals']['moderate_total'] = array(
    'title' => t('Moderate totals'),
    'help' => t('The total number of tests which failed that were considered moderate errors'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['accessible_content_node_totals']['suggestion_total'] = array(
    'title' => t('Suggestion totals'),
    'help' => t('The total number of tests which failed that were considered suggestions'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['accessible_content_node_test']['table']['group'] = t('Accessibility Test');
  $data['accessible_content_node_test']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['accessible_content_node_test']['test_name'] = array(
    'title' => t('Test Class Name'),
    'help' => t('The name of the class that powers this test'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['accessible_content_node_test']['severity'] = array(
    'title' => t('Severity level'),
    'help' => t('A level from 1 (severe) to 3 (suggestion)'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return $data;
}
