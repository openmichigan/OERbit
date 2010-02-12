<?php
// $Id: add_reference.php,v 1.1.2.4 2008/10/20 12:01:39 anselmheaton Exp $

/**
 * Implementation of hook_menu() for the add to referrer page
 */
function _nodereferrer_create_add_reference_menu() {
  $items = array();
  
  $items['node/%node/add_reference/%/%'] = array(
    'access callback' => '_nodereferrer_create_add_reference_access',
    'access arguments' => array(1,3,4),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('_nodereferrer_create_add_reference_form', 1, 3, 4),
    'type' => MENU_CALLBACK,
  );
  
  return $items;
}

/**
 * Access rights for page to add  to existing node
 */
function _nodereferrer_create_add_reference_access($node, $reference_field_idx, $reference_type) {
  return !empty($node->reference_fields[$reference_field_idx]['referenceable_types'][$reference_type]);
}

/**
 * Form to add to existing node
 *
 */
function _nodereferrer_create_add_reference_form($form_state, $node, $reference_field_idx, $reference_type) {
  $form = array();
  
  $multiple = $node->reference_fields[$reference_field_idx]['multiple'] == 1;
  $field_name = $node->reference_fields[$reference_field_idx]['field_name'];
  $type = content_types($reference_type);
  
  if ($multiple) {
    $form['referrence'] = array(
      '#type' => 'textfield',
      '#title' => t('Select @content_type you want to add to @title', 
        array('@content_type' => $type['name'], '@title' => $node->title)),
      '#autocomplete_path' => 'nodereference/autocomplete/'.$field_name,
      '#default_value' => '',
      '#maxlength' => 1024, // A Drupal title is maximum 255 chars ; but the autocomplete can be the result of a view.
    );
  } else {
    $form['referrence'] = array(
      '#type' => 'textfield',
      '#title' => t('Select @content_type you want to use for @title. This will replace the existing value.', 
        array('@content_type' => $type['name'], '@title' => $node->title)),
      '#autocomplete_path' => 'nodereference/autocomplete/'.$field_name,
      '#default_value' => '',
      '#maxlength' => 1024, // A Drupal title is maximum 255 chars ; but the autocomplete can be the result of a view.
    );
  }
  
  $form['submit'] = array(
    '#name' => 'add',
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  $form['cancel'] = array(
    '#name' => 'cancel',
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );
  
  return $form;
}

/**
 * Validate the from to add to an existing node
 */
function _nodereferrer_create_add_reference_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#name'] == 'add') {
    $title = trim($form_state['values']['referrence']);
    if (!$title) {
      form_set_error('referrence', t('Please select a value'));
    } else {
      if (preg_match('/\[nid:(\d+)\]\s*$/', $title, $matches)) {
        if (!($node = node_load(intval($matches[1])))) {
          form_set_error('referrence', t('Unkown value @text', array('@text' => $title)));
        } else {
          $form_state['values']['referrence'] = $node->nid;
        }
      } else {
        if (!($node = node_load(array('title' => $title)))) {
          form_set_error('referrence', t('Unknown value @text', array('@text' => $title)));
        } else {
          $form_state['values']['referrence'] = $node->nid;
        }
      }
    }
  }
}

/**
 * Submit the form to add to an existing node
 */
function _nodereferrer_create_add_reference_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#name'] != 'add') {
    drupal_set_message(t('The operation was cancelled'));
    drupal_goto('node/'.arg(1));
    return;
  }
  
  $append_node = node_load($form_state['values']['referrence']);
  $current_node = node_load(arg(1));
  
  // Make sure the user is allowed to do this.
  if (!node_access('update', $current_node)) {
    drupal_set_message(t('You do not have rights to update this node'));
    drupal_goto('node/'.arg(1));
    return;
  }
  
  $field_name = $current_node->reference_fields[arg(3)]['field_name'];

  $field_array =& $current_node->$field_name;
  $multiple = $current_node->reference_fields[arg(3)]['multiple'] == 1;
  
  if ($field_array[0]['nid']=== null || !$multiple) {
    $field_array[0]['nid'] = $append_node->nid;
  } else {
    $field_array[] = array('nid' => $append_node->nid);
  }
  
  // Save, and ensure the changes are noticed
  node_save($current_node);
  cache_clear_all();
  
  drupal_set_message(t('The node was added'));
  drupal_goto('node/'.arg(1));
}

