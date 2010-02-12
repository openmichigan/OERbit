<?php // $Id: accessibility.inc,v 1.1.2.2 2010/01/08 20:06:04 kevee Exp $

/*
*  @file The WYSIWYG Plugin
*/

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function accessible_content_wysiwyg_accessibility_plugin() {
  $plugins['accessibility'] = array(
    'title' => t('Check Accessibility'),
    'vendor url' => 'http://drupal.org/project/accessible_content',
    'icon file' => 'accessibility.gif',
    'icon title' => t('Check accessibility of selected content'),
    'settings' => array(),
  );
  return $plugins;
}

