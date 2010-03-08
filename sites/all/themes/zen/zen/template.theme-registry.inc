<?php
// $Id: template.theme-registry.inc,v 1.7.2.6 2009/10/24 11:30:15 johnalbin Exp $

/**
 * @file
 * Contains infrequently used theme registry build functions.
 */

/**
 * Implements HOOK_theme().
 *
 * We are simply using this hook as a convenient time to do some related work.
 */
function _zen_theme(&$existing, $type, $theme, $path) {
  // Compute the conditional stylesheets.
  if (!module_exists('conditional_styles')) {
    include_once './' . _zen_path() . '/template.conditional-styles.inc';
    // _conditional_styles_theme() only needs to be run once.
    if ($theme == 'zen') {
      _conditional_styles_theme($existing, $type, $theme, $path);
    }
  }

  // Since we are rebuilding the theme registry and the theme settings' default
  // values may have changed, make sure they are saved in the database properly.
  zen_theme_get_default_settings($theme);

  // If we are auto-rebuilding the theme registry, warn about the feature.
  // Always display the warning in the admin section, otherwise limit to three
  // warnings per hour.
  if (function_exists('user_access') && user_access('administer site configuration') && theme_get_setting('zen_rebuild_registry') && $theme == $GLOBALS['theme'] && (arg(0) == 'admin' || flood_is_allowed($GLOBALS['theme'] . '_rebuild_registry_warning', 3))) {
    flood_register_event($GLOBALS['theme'] . '_rebuild_registry_warning');
    drupal_set_message(t('For easier theme development, the theme registry is being rebuilt on every page request. It is <em>extremely</em> important to <a href="!link">turn off this feature</a> on production websites.', array('!link' => url('admin/build/themes/settings/' . $GLOBALS['theme']))), 'warning', FALSE);
  }

  // Return nothing.
  return array();
}

/**
 * Return the theme settings' default values from the .info and save them into the database.
 *
 * @param $theme
 *   The name of theme.
 */
function zen_theme_get_default_settings($theme) {
  $themes = list_themes();

  // Get the default values from the .info file.
  $defaults = !empty($themes[$theme]->info['settings']) ? $themes[$theme]->info['settings'] : array();

  if (!empty($defaults)) {
    // Merge the defaults with the theme settings saved in the database.
    $settings = array_merge($defaults, variable_get('theme_'. $theme .'_settings', array()));
    // Save the settings back to the database.
    variable_set('theme_'. $theme .'_settings', $settings);
    // If the active theme has been loaded, force refresh of Drupal internals.
    if (!empty($GLOBALS['theme_key'])) {
      theme_get_setting('', TRUE);
    }
  }

  // Return the default settings.
  return $defaults;
}
