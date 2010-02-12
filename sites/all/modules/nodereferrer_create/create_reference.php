<?php
// $Id: create_reference.php,v 1.1.2.2 2008/09/09 11:11:13 anselmheaton Exp $

/**
 * hook_menu for the pages to create new referrers
 */
function _nodereferrer_create_create_reference_menu() {
  $items = array();
  
  $items['node/%node/create_reference/%/%'] = array(
    'access callback' => '_nodereferrer_create_create_reference_access',
    'access arguments' => array(1,3,4),
    'page callback' => '_nodereferrer_create_create_reference',
    'page arguments' => array(1, 3, 4),
    'type' => MENU_CALLBACK,
  );
  
  return $items;
}

/**
 * Page to add the node ; this generates a node_add_form page
 *
 */
function _nodereferrer_create_create_reference($node, $reference_field_idx, $reference_type) {
  global $user;
  
  drupal_set_title(check_plain($node->title));
  
  _nodereferrer_create_reference_signal(array(
    'type' => $reference_type,
    'nid' => $node->nid,
    'title' => $node->title,
  ));
  
  // Make sure we have the pages we want
  module_load_include('pages.inc', 'node');
    
  //Initialize new node
  $form_id = $reference_type .'_node_form';
  $new_node = array('uid' => $user->uid, 'name' => $user->name, 'type' => $reference_type);
  
  $form = _nodereferrer_create_get_form($form_id, $new_node);
  if (!isset($_SESSION['nodereferrer_create'])) {
    $_SESSION['nodereferrer_create'] = array();
  }
  $_SESSION['nodereferrer_create'][] = array(
    'form_build_id' => $form['form_build_id'],
    'nid' => $node->nid,
    'reference_field_idx' => $reference_field_idx
  );
  
  return $form['form'];
}

/**
 * Access rights for page to add node
 */
function _nodereferrer_create_create_reference_access($node, $reference_field_idx, $reference_type) {
  return !empty($node->reference_fields[$reference_field_idx]['referenceable_types'][$reference_type]);
}

/**
 * hook_nodeapi insert
 *
 */
function _nodereferrer_create_reference_insert(&$node) {
  if (!isset($_SESSION['nodereferrer_create'])) {
    return;
  }
  foreach ($_SESSION['nodereferrer_create'] as $i => $a) {
    if ($a['form_build_id'] == $node->form_build_id) {
      $source_node = node_load($a['nid']);
      $field = $source_node->reference_fields[$a['reference_field_idx']]['field_name'];
      $multiple = $source_node->reference_fields[$a['reference_field_idx']]['multiple'] == 1;
      
      $subst =& $source_node->$field;
      if ($subst[0]['nid'] === null || !$multiple) {
        $subst[0]['nid'] = $node->nid;
      } else {
        $subst[] = array('nid' => $node->nid);
      }
      node_save($source_node);
      
      unset($_SESSION['nodereferrer_create'][$i]);
      return;
    }
  }
}

/**
 * allow nodereferrer_create_add to signal that the node form should be altered
 * @param $set 
 *   an array like ('nid'=>1,'type'=>'page', 'field'=>'name')
 * @return
 *   if no param is passed, return the stored array
 */
function _nodereferrer_create_reference_signal($set=NULL) {
  static $return;
  if ($set) {
    $return = $set;
  }
  else return $return;
}

/**
 * Alter the node_add form to add our default values
 */
function _nodereferrer_create_reference_alter(&$form, $form_state, $form_id) {
  if ($signal = _nodereferrer_create_reference_signal() AND $form_id == $signal['type'].'_node_form') {
    // Add default title if required
    if (variable_get('nodereferrer_create_sync_title', 0) && isset($form['title'])) {
      $form['title']['#default_value'] = $signal['title'];
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
        $source = $matches[1];
        $dest   = $matches[2];
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

