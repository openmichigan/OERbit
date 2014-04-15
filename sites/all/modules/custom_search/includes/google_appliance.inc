<?php

/**
 * @file
 * Path generation for Google Appliance Search.
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

function _custom_search_google_appliance_search($variables) {
  $type = variable_get('google_appliance_default_search_path', 'google-appliance');
  return array('path' => $type . '/' . $variables['keys'], 'query' => '');
}