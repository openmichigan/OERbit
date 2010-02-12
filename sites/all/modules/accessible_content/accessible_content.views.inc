<?php
// $Id: accessible_content.views.inc,v 1.1.2.1 2010/01/08 21:25:46 kevee Exp $
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
  return $data;
}
