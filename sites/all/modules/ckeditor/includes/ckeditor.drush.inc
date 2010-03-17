<?php
// $Id: ckeditor.drush.inc,v 1.1.2.2 2010/03/10 10:26:38 mephir Exp $

/**
 * @file
 * Drush integration for the ckeditor module.
 */

/**
 * Implements hook_drush_command().
 */
function ckeditor_drush_command() {
  $items['ckeditor-download'] = array(
    'callback' => 'ckeditor_drush_download',
    'description' => dt('Downloads the required CKEditor library from svn.fckeditor.net.'),
    'arguments' => array(
      'path' => dt('Optional. A path to the download folder. If omitted Drush will use the default location (sites/all/libraries/ckeditor).'),
    ),
  );
  return $items;
}

/**
 * Downloads
 */
function ckeditor_drush_download() {
  $args = func_get_args();
  if ($args[0]) {
    $path = $args[0];
  }
  else {
    $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/sites/all/libraries/ckeditor';
  }

  if (drush_shell_exec('svn checkout http://svn.fckeditor.net/CKEditor/releases/stable/ ' . $path)) {
    drush_log(dt('CKEditor has been downloaded to @path.', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download the CKEditor to @path.', array('@path' => $path)), 'error');
  }
}

/**
 * Implements drush_MODULE_post_COMMAND().
 */
function drush_ckeditor_post_enable() {
  $modules = func_get_args();
  if (in_array('ckeditor', $modules)) {
    ckeditor_drush_download();
  }
}
