<?php

/**
 * @file
 * Path generation for Apache Solr Search.
 *
 * Available vars:
 * $orginal_keywords: user input
 * $types: content types (machine names[])
 * $terms: taxonomy terms (tids[])
 * $keys: complete search phrase, as core would have done it
 *
 * To return:
 * the complete search path
 *
 */

function _custom_search_apachesolr_search($variables) {
  $type = 'search/apachesolr_search/' . $variables['keywords'];
  $keys = array();

  if (count($variables['types']) && !in_array('all', $variables['types'])) $keys[] = 'type:' . implode('%20type:', $variables['types']);

  if (module_exists('taxonomy') && count($variables['terms'])) $keys[] = 'tid:' . implode('%20tid:', $variables['terms']);

  $keys = 'filters=' . implode('%20', $keys);

  return array('path' => $type, 'query' => $keys);
}