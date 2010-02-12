<?php
// $Id: add_to_referrer.php,v 1.1.2.5 2008/10/20 12:01:39 anselmheaton Exp $

/**
 * Implementation of hook_menu() for the add to referrer page
 */
function _nodereferrer_create_add_menu() {
  $items = array();
  
  $items['node/%node/add_referrer/%/%/%'] = array(
    'access callback' => '_nodereferrer_create_add_access',
    'access arguments' => array(1,3,4,5),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('_nodereferrer_create_add_form', 1, 3, 4,5),
    'type' => MENU_CALLBACK,
  );
  
  // Callback for autocomplete when selecting referrers to add to
  $items['nodereferrer_create/autocomplete/%'] = array(
    'access callback' => '_nodereferrer_create_autocomplete_access',
    'access arguments' => array(2),
    'page callback' => '_nodereferrer_create_autocomplete',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
  );
  
  return $items;
}

/**
 * Access rights for page to add  to existing node
 */
function _nodereferrer_create_add_access($node, $referrer_field_idx, $referrer_type, $referrence_field_idx) {
  return isset($node->referrers[$referrer_field_idx]['referrence'][$referrer_type][$referrence_field_idx]);
}

/**
 * Form to add to existing node
 *
 */
function _nodereferrer_create_add_form($form_state, $node, $referrer_field_idx, $referrer_type, $referrence_field_idx) {
  $form = array();
  
  $type = content_types($referrer_type);
  
  $form['referrence'] = array(
    '#type' => 'textfield',
    '#title' => t('Select @content_type you want to add @title to', 
      array('@content_type' => $type['name'], '@title' => $node->title)),
    '#autocomplete_path' => 'nodereferrer_create/autocomplete/'.$referrer_type,
    '#default_value' => '',
    '#maxlength' => 1024, // A Drupal title is maximum 255 chars ; but the autocomplete can be the result of a view.
  );
  
  $form['submit'] = array(
    '#name' => 'add',
    '#type' => 'submit',
    '#value' => t('Add',
      array('@title' => $node->title, '@content_type' => $type['name'])),
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
function _nodereferrer_create_add_form_validate($form, &$form_state) {
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
function _nodereferrer_create_add_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#name'] != 'add') {
    drupal_set_message(t('The operation was cancelled'));
    drupal_goto('node/'.arg(1));
  }
  
  $append_node = node_load($form_state['values']['referrence']);
  
  // Make sure the user is allowed to do this
  if (!node_access('update', $append_node)) {
    drupal_set_message(t('You do not have rights to update this node'));
    drupal_goto('node/'.arg(1));
    return;
  }
  
  $current_node = node_load(arg(1));
  
  $field = $current_node->referrers[arg(3)]['referrence'][arg(4)][arg(5)]['field_name'];
  array_push($append_node->$field, array('nid' => $current_node->nid));
  
  // Save, and ensure the changes are noticed
  node_save($append_node);
  cache_clear_all();
  
  drupal_set_message(t('The node was added'));
  drupal_goto('node/'.arg(1));
}

/**
 * Auto complete function for the form to add to an existing node
 */
function _nodereferrer_create_autocomplete($type, $filter) {
  $matches = array();
  
  // Only query nodes where we have update rights
  $update_where = _node_access_where_sql('update', 'ndrfc_node_access');
  if ($update_where) {
    $update_where = '('.$update_where.') AND ';
  }
  $res = db_query("
    SELECT node.nid 
      FROM {node} AS node
    INNER JOIN {node_access} AS ndrfc_node_access ON ndrfc_node_access.nid = node.nid
    WHERE $update_where
          type='%s' AND title LIKE '%%%s%%'
  ", $type, $filter);
  
  while ($nid = db_fetch_object($res)) {
    $node = node_load($nid->nid);
    $matches[$node->title.' [nid:'.$node->nid.']'] = $node->title;
  }
  
  drupal_json($matches);
}

/**
 * Access rights for the auto complete
 */
function _nodereferrer_create_autocomplete_access($type) {
  return true;
}

