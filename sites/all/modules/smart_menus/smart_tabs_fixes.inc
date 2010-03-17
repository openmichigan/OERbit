<?php
// $Id: smart_tabs_fixes.inc,v 1.6 2010/03/09 01:55:21 rdeboer Exp $

/**
 * @file
 *  Contains hooks and workarounds for themes and URLs that Smart tabs can't
 *  play nicely with by default, usually because a developer has deviated from
 *  the conventions.
 *
 *  Fixed themes include:
 *  o Garland and its subthemes, eg Minelli
 *
 *  Fixed URLs include:
 *  o admin/build/trigger/<type>, used to always redirect to admin/build/trigger/node
 *  o node/%/revisions, used to redirect to node/%/revisions/list then produce error
 *  o
 */

/**
 * Implementation of hook_registry_alter().
 *
 * @param $registry
 * @return void
 */
function smart_tabs_theme_registry_alter(&$registry) {
  if (!variable_get('smart_tabs_theme_override', TRUE)) {
    _st_debug_info(t("Smart tabs is now <strong>not</strong> overriding the 'menu_local_tasks' theme hook. If you want Smart tabs behaviour you must implement either <em>yourtheme</em>_menu_local_tasks() or phptemplate_menu_local_tasks()."));
  }
  elseif (!in_array('themes/garland', $registry['menu_local_tasks']['theme paths'])) {
    // For any theme other than Garland, override the theme hook for
    // menu_local_tasks().
    // A straightforward way to do this is by implementing ENGINENAME_hook(),
    // e.g. have phptemplate_menu_local_tasks() return
    // theme_menu_local_tasks_smart_tabs().
    // However this approach may clash with certain themes, like Garland,
    // which already implement ENGINENAME_menu_local_tasks().
    // This is why we poke directly into the registry.
    // Expect the menu_local_tasks theme hook to be either
    // 'theme_menu_local_tasks' or 'BASETHEMENAME_menu_local_tasks', e.g.
    // 'zen_menu_local_tasks'.
    $menu_local_tasks_function = $registry['menu_local_tasks']['function'];
    if (strpos($menu_local_tasks_function, '_menu_local_tasks') > 0) {
      _st_debug_info(t("Smart tabs is overriding !function_name() with theme_menu_local_tasks_smart_tabs()",
        array('!function_name' => $menu_local_tasks_function)));
      $registry['menu_local_tasks'] = array(
        'function' => 'theme_menu_local_tasks_smart_tabs')
        + $registry['menu_local_tasks'];
    }
  }
// ------------------------- Smart fix for Garland theme ----------------------
  else {
    // themes/garland/template.php overrides theming of menu_local_tasks()
    // by having phptemplate_menu_local_tasks() return menu_primary_local_tasks().
    // Need to correct Garland to use menu_primary_local_tasks_smart_tabs() instead.
    if ($registry['menu_local_tasks']['function'] == 'phptemplate_menu_local_tasks') {
      $registry['menu_local_tasks'] = array('function' => 'menu_primary_local_tasks_smart_tabs')
        + $registry['menu_local_tasks'];
    }
    // themes/garland/template.php furher overrides theming of menu_local_tasks()
    // in phptemplate_preprocess_page() via this assignment:
    //   $vars['tabs2'] = menu_secondary_local_tasks();
    // Need to get Garland to call menu_secondary_local_tasks_smart_tabs() instead.
    if (in_array('themes/garland', $registry['page']['theme paths'])) {
      $index = array_search('phptemplate_preprocess_page', $registry['page']['preprocess functions']);
      if ($index !== FALSE) {
        $registry['page']['preprocess functions'][$index] = '_garland_preprocess_page_smart_tabs';
      }
    }
  }
}

function _garland_preprocess_page_smart_tabs(&$variables) {
  $variables['tabs2'] = menu_secondary_local_tasks_smart_tabs();
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

// ---------- Smart fix for admin/build/trigger, node/%node/revisions ---------
/**
 * Implementation of hook_menu_alter().
 */
function smart_tabs_menu_alter(&$items) {
  if (module_exists('diff') && !module_exists('revisioning')) {
    // node/%/revisions redirects to node/%/revisions/list then produces error:
    // "Missing argument 1 for diff_diffs_overview(), in diff.module line ..."
    unset($items['node/%node/revisions/list']);
  }
  if (module_exists('trigger')) {
    // Get around the redirection to admin/build/trigger/node that is hard-coded
    // in trigger.admin.inc/trigger_assign()
    $items['admin/build/trigger']['page callback'] = '_trigger_assign_fixed';
    $items['admin/build/trigger']['page arguments'] = array();
  }
  if (module_exists('webform')) {
    // Webform module doesn't explicitly state the file for the Configuration tab callback, node_page_edit()
    // Not required when 'node/*/edit/components*' is on exclusion list.
    // $items['node/%webform_menu/edit/configuration']['file'] = '../../../../modules/node/node.pages.inc';
  }
}

/**
 * Build the form that allows users to assign actions to hooks.
 *
 * @param $type
 *   Name of hook.
 * @return
 *   HTML form.
 */
function _trigger_assign_fixed($type = NULL) {
  $type = _smart_tabs_leaf($_SESSION['active-tabs']['admin/build/trigger']);
  // If no type is specified default to node actions, since they're most common.
  if (empty($type)) {
    drupal_goto('admin/build/trigger/node');
  }
  return trigger_assign($type);
}

// ----------------------------------------------------------------------------
