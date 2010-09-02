<?php
// $Id: module_grants.admin.inc,v 1.3 2010/04/30 01:20:30 rdeboer Exp $

/**
 * @file
 * Admin configuration settings for Module Grants.
 */

/**
 * Menu callback for admin settings.
 */
function module_grants_admin_configure() {
  $access_modules = array();
  foreach (module_implements('node_grants') as $module) {
    $access_modules[] = $module;
  }

  $form['module_grants_multiple_modules'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure behaviour when multiple content access modules are enabled'),
    '#description' => t('The following content access modules are currently enabled: %modules.',
      array('%modules' => empty($access_modules) ? 'none' : implode(',', $access_modules)))
  );
  $form['module_grants_multiple_modules']['module_grants_lenient'] = array(
    '#type' => 'checkbox',
    '#title' => t('Interpret absence of access grants as a "don\'t care", rather than a "deny access".'),
    '#default_value' => variable_get('module_grants_lenient', TRUE),
    '#description' => t('Only applies when two or more content access modules are enabled and one of the modules makes no statement about a node that is about to be accessed. If this box is checked, then a content access module saying nothing (via the node_access table) about the node in question will be deemed to be ok with the user having access to it. If not checked (i.e. "strict"), then a module saying nothing will be taken as a "deny access".')
  );
  $form['module_grants_multiple_modules']['module_grants_OR_modules'] = array(
    '#type' => 'checkbox',
    '#title' => t('OR rather than AND the access grants from multiple modules, i.e. behave like core does (for published content).'),
    '#default_value' => variable_get('module_grants_OR_modules', FALSE),
    '#description' => t('Note that normally core behaviour is <strong>not</strong> what you want -- it is the reason Module Grants was written in the first place.')
  );
  $form['show_taxonomy_terms'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add a taxonomy <strong>Term</strong> column to the accessible content summary, if applicable.'),
    '#default_value' => variable_get('show_taxonomy_terms', TRUE),
    '#description' => t('This column will only be shown if the <em>Taxonomy</em> module has been enabled <em>and</em> vocabularies have been defined.')
  );
  return system_settings_form($form);
}
