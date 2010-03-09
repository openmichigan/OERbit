<?php
// $Id$

function path_breadcrumb_admin_settings(&$form_state) {
  $form = array();
  $types = node_get_types();
  $options = array();
  foreach ($types as $key => $value) {
    $options[$value->type] = $value->name;
  }
  asort($options);
  $form['path_breadcrumb_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#description' => t('Mark the node types that will use this type of breadcrumb'),
    '#options' => $options,
    '#default_value' => variable_get('path_breadcrumb_types', array()),
  );
  $form['path_breadcrumb_first'] = array(
    '#type' => 'textfield',
    '#title' => t('First node'),
    '#description' => t('Enter a static value for the first element of the breadcrumb. If omitted, the title will be used'),
    '#default_value' => variable_get('path_breadcrumb_first', ''),
  );
  $form['path_breadcrumb_current'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include current node'),
    '#description' => t('Mark whether to include the current node as part of the breadcrumb'),
    '#default_value' => variable_get('path_breadcrumb_current', 0),
  );
  $form['path_breadcrumb_current_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link current node'),
    '#description' => t('Mark whether the current node will link to itself in the breadcrumb.'),
    '#default_value' => variable_get('path_breadcrumb_current_link', 0),
  );
  return system_settings_form($form);
}
