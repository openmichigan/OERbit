<?php
// $Id: create_referrer.php,v 1.1.2.2 2008/09/09 11:11:13 anselmheaton Exp $

/**
 * hook_menu for the pages to create new referrers
 */
function _nodereferrer_create_create_menu() {
  $items = array();
  
  $items['node/%node/create_referrer/%/%/%'] = array(
    'access callback' => '_nodereferrer_create_create_access',
    'access arguments' => array(1,3,4,5),
    'page callback' => '_nodereferrer_create_create',
    'page arguments' => array(1, 3, 4, 5),
    'type' => MENU_CALLBACK,
  );
  
  return $items;
}

/**
 * Page to add the node ; this generates a node_add_form page
 *
 */
function _nodereferrer_create_create($node, $referrer_field_idx, $referrer_type, $referrence_field_idx) {
  global $user;
  
  drupal_set_title(check_plain($node->title));
  _nodereferrer_create_referrer_signal(array(
    'type'  => $referrer_type,
    'field' => $node->referrers[$referrer_field_idx]['referrence'][$referrer_type][$referrence_field_idx]['field_name'],
    'nid'   => $node->nid,
    'title' => $node->title,
    'add'   => false,
  ));
  
  // Make sure we have the pages we want
  module_load_include('pages.inc', 'node');
    
  //Initialize new node
  $new_node = array('uid' => $user->uid, 'name' => $user->name, 'type' => $referrer_type);
  return drupal_get_form($referrer_type .'_node_form', $new_node);
}

/**
 * Access rights for page to add node
 */
function _nodereferrer_create_create_access($node, $referrer_field_idx, $referrer_type, $referrence_field_idx) {
  return isset($node->referrers[$referrer_field_idx]['referrence'][$referrer_type][$referrence_field_idx]);
}

/**
 * allow nodereferrer_create_add to signal that the node form should be altered
 * @param $set 
 *   an array like ('nid'=>1,'type'=>'page', 'field'=>'name')
 * @return
 *   if no param is passed, return the stored array
 */
function _nodereferrer_create_referrer_signal($set=NULL) {
  static $return;
  if ($set) {
    $return = $set;
  }
  else return $return;
}

/**
 * Alter the node_add form to add our default values
 */
function _nodereferrer_create_referrer_alter(&$form, $form_state, $form_id) {
  if ($signal = _nodereferrer_create_referrer_signal() AND $form_id == $signal['type'].'_node_form') {
    // Add default title if required
    if (variable_get('nodereferrer_create_sync_title', 0) && isset($form['title'])) {
      $form['title']['#default_value'] = $signal['title'];
    }
    
    // Add reference
    if (!$signal['add'] && isset($form[$signal['field']]['#default_value'])) {
      $form[$signal['field']]['#default_value'] = array('nid' => $signal['nid']);
    } else {
      $idx = -1;
      while(isset($form[$signal['field']][$idx+1])) {
        $idx = $idx+1;
      }
      if ($idx >= 0) {
        if (!$signal['add'] && $idx > 0) {
          $idx = $idx - 1;
        }
        $form[$signal['field']][$idx]['#default_value'] = array('nid' => $signal['nid']);
      }
    }
    
    // Syncronise other fields if required
    $list = trim(variable_get('nodereferrer_create_sync_fields', ''));
    if ($list) {
      $list = explode("\n", $list);
      $node = node_load($signal['nid']);
      foreach ($list as $rule) {
        if (!preg_match('/^\s*(.+)\s+:\s+(.+)$/', $rule, $matches)) {
          continue;
        }
        $source = trim($matches[1]);
        $dest   = trim($matches[2]);
        if (!array_key_exists($source, $node)) {
          continue;
        }
        if (!array_key_exists($dest, $form)) {
          continue;
        }
        $form[$dest]['#default_value'] = $node->$source;
      }
    }
  }
}

