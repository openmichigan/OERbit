<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function oerbit_core_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: primary-links
  $menus['primary-links'] = array(
    'menu_name' => 'primary-links',
    'title' => 'Primary links',
    'description' => 'Primary links are often used at the theme layer to show the major sections of a site. A typical representation for primary links would be tabs along the top.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Primary links');
  t('Primary links are often used at the theme layer to show the major sections of a site. A typical representation for primary links would be tabs along the top.');


  return $menus;
}
