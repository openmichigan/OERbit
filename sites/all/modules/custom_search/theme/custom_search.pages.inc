<?php

/**
 * @file
 * User page callbacks for the custom_search module.
 */

/*
 * Presents links to filter the search results.
 */
function custom_search_preprocess_search_results(&$variables) {
  if ($variables['type'] == 'node') {
    $variables['filter_position'] = variable_get('custom_search_filter', 'disabled');
    // save # of results for collapsing advanced search
    $GLOBALS['custom_search_nb_results'] = count($variables['results']);
    // generate the filter
    if (user_access('use custom search') && $variables['filter_position'] != 'disabled') {
      // Get search words (minus type:node_type)
      $keys = search_get_keys();
      if (strpos($keys, 'type:') !== FALSE) {
        $keys = drupal_substr($keys, 0, strpos($keys, 'type:')-1);
      }
      // Get Custom Search authorized types
      $searchable_node_types = variable_get('custom_search_node_types', array());
      $searchable_node_types = array_keys(array_filter($searchable_node_types, 'custom_search_filter_array'));
      if (!count($searchable_node_types)) $searchable_node_types = array_keys(node_get_types('names'));
      $node_types = db_query("SELECT type, name FROM {node_type} WHERE type IN (" . db_placeholders($searchable_node_types, 'varchar') . ")", $searchable_node_types);
      // Build menu
      $items = array();
      $items[] = l(variable_get('custom_search_type_selector_all', CUSTOM_SEARCH_ALL_TEXT_DEFAULT), 'search/node/' . $keys);
      while ($node_type = db_fetch_array($node_types)) {
        // count # of results per type
        $nbresults = 0;
        foreach ($variables['results'] as $result) {
          if ($result['node']->type == $node_type['type']) $nbresults++;
        }
        if ($nbresults) $items[] = l($node_type['name'], 'search/node/' . $keys . ' type:' . $node_type['type']);
      }
      if (!isset($variables['filter-title'])) {
        $variables['filter-title'] = filter_xss(variable_get('custom_search_filter_label', CUSTOM_SEARCH_FILTER_LABEL_DEFAULT));
      }
      if (count($items) > 2) $variables['filter'] = theme('item_list', $items, $variables['filter-title']);
    }
  }
}

/*
 * Customisation of the results info.
 */
function custom_search_preprocess_search_result(&$variables) {
  // used to identify the correct info string
  $comment_str = preg_replace("/[0-9] (\b[a-z]*\b).*/", "$1", t('1 comment'));
  $attachment_str = preg_replace("/@*[a-z0-9]* (\b[a-z]*\b).*/", "$1", t('1 attachment'));

  $infos = array();
  if (isset($variables['info_split'])) {
    foreach ($variables['info_split'] as $key => $info) {
      if (!is_numeric($key)) {
        if (variable_get('custom_search_results_info_' . $key, TRUE)) array_push($infos, $info);
      }
      else {
        if (variable_get('custom_search_results_info_comment', TRUE) && !empty($comment_str) && strpos($info, $comment_str) !== FALSE) array_push($infos, $info);
        if (variable_get('custom_search_results_info_upload', TRUE) && !empty($attachment_str) && strpos($info, $attachment_str) !== FALSE) array_push($infos, $info);
      }
    }
  }
  $variables['info'] = implode(' - ', $infos);
}