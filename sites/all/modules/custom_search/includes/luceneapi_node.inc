<?php

/**
 * @file
 * Path generation for Lucene API Search.
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

function _custom_search_lucenapi_search($variables) {
  $type = 'search/' . variable_get('luceneapi:default_search', 0) . '/' . $variables['keywords'];
  $keys = array();

  if (count($variables['types']) && !in_array('all', $variables['types'])) {
    foreach ($variables['types'] as $t) $keys[] = "type[$t]=$t";
  }

  if (module_exists('taxonomy') && count($variables['terms'])) {
    foreach ($variables['terms'] as $t) $keys[] = "category[$t]=$t";
  }

  $keys = implode('&', $keys);

  return array('path' => $type, 'query' => $keys);
}