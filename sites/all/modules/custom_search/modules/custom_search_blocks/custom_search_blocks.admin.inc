<?php
// $Id: custom_search_blocks.admin.inc,v 1.1.2.3 2010/05/02 14:55:31 jdanthinne Exp $

/**
 * @file
 * Admin settings for custom search
 */

/**
 * Implementation of hook_help().
 */
function custom_search_blocks_help($path, $arg) {
  switch ($path) {
    case 'admin/settings/custom_search/blocks':
      $output = t('If you want additional blocks by content type, enable them here. Then go to the <a href="@link">block page</a> to place them in a region.', array('@link' => url('admin/build/block')));
    break;
  }
  return $output;
}

function custom_search_blocks_admin() {
  $form['custom_search_blocks_number'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Number of blocks'),
    '#size'           => 2,
    '#default_value'  => variable_get('custom_search_blocks_number', 1),
  );
  return system_settings_form($form);
}