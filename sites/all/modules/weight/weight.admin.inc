<?php
// $Id: weight.admin.inc,v 1.1.2.2 2009/04/25 16:08:45 nancyw Exp $
/**
 * @file
 * This module uses the sticky column of the node table
 * to add weighting to nodes.
 */

function weight_settings_form() {
  drupal_add_css(drupal_get_path('module', 'weight') .'/weight.css');
  $form = array();
  $types = node_get_types('names');

  $form['weight_range'] = array(
    '#type' => 'select',
    '#title' => t('Node Weight Range'),
    '#default_value' => variable_get('weight_range', 20),
    '#options' => array(5 => 5, 10 => 10, 20 => 20, 30 => 30, 40 => 40, 50 => 50, 60 => 60, 70 => 70, 80 => 80, 90 => 90),
    '#description' => '<p>'. t('This will be the +/- range for node weight.') .'</p>',
    );

  $form['weight_use_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Menu Weight'),
    '#default_value' => variable_get('weight_use_menu', FALSE),
    '#description' => '<p>'. t('If the node has not been weighted, should we use the menu item weight?') .'</p>',
    );

  $form['weight_position'] = array(
    '#type' => 'weight',
    '#delta' => 10,
    '#title' => t('Weight selector position weight'),
    '#default_value' => variable_get('weight_position', 0),
    '#description' => '<p>'. t('This controls where the selection for node weight goes on the node edit form. If the position is 10 and the user has "administer nodes" permission, it will be added into the "Workflow options."') .'</p>',
    );

  $form['weight_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display On'),
    '#default_value' => variable_get('weight_node_types', $types),
    '#options' => $types,
    '#description' => '<p>'. t('Select the content types to be weighted.
      The selected content types will be mass updated to the default weight</p>
      <p><i>Note:</i> Unselecting a node type after having changed weights
      will result in the loss of those weights. You may want to check the
      <a href="@posts_page">content page</a> before unsetting any node types.',
      array('@posts_page' => url('admin/content/node'))
      ) .'</p>',
    );

  $form['weight_default'] = array(
    '#type' => 'weight',
    '#delta' => variable_get('weight_range', 20),
    '#title' => t('Default weight'),
    '#default_value' => variable_get('weight_default', 0),
    '#description' => t('If a new content type is selected, this is the weight that will be assigned to those nodes. If you are also changing the range above, "Save" that change first.'),
    );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    );

  return $form;
}

function weight_settings_form_submit($form, &$form_state) {
  variable_set('weight_range', $form_state['values']['weight_range']);
  variable_set('weight_position', $form_state['values']['weight_position']);
  variable_set('weight_default', $form_state['values']['weight_default']);

  // Check for changes in the list.
  $before = array_filter(variable_get('weight_node_types', array()));
  $after = array_filter($form_state['values']['weight_node_types']);
  $del = array_diff($before, $after);
  $add = array_diff($after, $before);
  // Add weighting to new types.
  if ($add) {
    weight_old_nodes($add);
  }
  // Remove weighting from types taken out of the list.
  if ($del) {
    weight_disable($del);
  }

  variable_set('weight_node_types', $after);

  drupal_set_message(t('Settings updated.'));
}

/**
 * Update the sticky value of existing nodes if they are enabled for weights.
 * This ensures that they will sort correctly.
 */
function weight_old_nodes($weight_node_types = array()) {
  if ($weight_node_types) {
    $temp = new stdClass();
    $temp->node_weight = variable_get('weight_default', 0);
    drupal_set_message(t('Enabling weight for: !types, default weight: !default',
      array('!types' => implode(', ', $weight_node_types), '!default' => $temp->node_weight)));
    // Get default for non-sticky nodes;
    $temp->sticky = 0;
    _weight_encode($temp);
    $not_sticky = $temp->sticky;
    // Get default for sticky nodes;
    $temp->sticky = 1;
    _weight_encode($temp);
    $is_sticky = $temp->sticky;
    $placeholders = db_placeholders($weight_node_types, 'text');

    array_unshift($weight_node_types, $is_sticky);
    db_query("UPDATE {node} SET sticky = %d WHERE sticky = 1 AND type IN ($placeholders)", $weight_node_types);
    $count = db_affected_rows();
    array_shift($weight_node_types);
    array_unshift($weight_node_types, $not_sticky);
    db_query("UPDATE {node} SET sticky = %d WHERE sticky = 0 AND type IN ($placeholders)", $weight_node_types);
    $count += db_affected_rows();
    drupal_set_message(t('@count nodes weight enabled.', array('@count' => $count)));
  }
}

/**
 * Set nodes back to normal sticky values if they are not enabled for weights.
 */
function weight_disable($weight_node_types = array()) {
  if ($weight_node_types) {
    drupal_set_message(t('Disabling weight for: !types', array('!types' => implode(', ', $weight_node_types))));
    $placeholders = db_placeholders($weight_node_types, 'text');
    db_query("UPDATE {node} SET sticky = 1 WHERE sticky > 1 AND type IN ($placeholders)", $weight_node_types);
    $count = db_affected_rows();
    db_query("UPDATE {node} SET sticky = 0 WHERE sticky < 0 AND type IN ($placeholders)", $weight_node_types);
    $count += db_affected_rows();
  }
  else {
    db_query("UPDATE {node} SET sticky = 1 WHERE sticky > 1");
    $count = db_affected_rows();
    db_query("UPDATE {node} SET sticky = 0 WHERE sticky < 0");
    $count += db_affected_rows();
  }
  drupal_set_message(t('@count nodes weight disabled.', array('@count' => $count)));
}
