<?php
// $Id: module_grants.pages.inc,v 1.1 2010/01/27 06:29:59 rdeboer Exp $

/**
 * @file
 * Rendering of pages used by Module Grants.
 * Node deletion is overridden here, as node_delete calls node_access(), which
 * it shouldn't when module_grants_node_access() is at work.
 */

/**
 * Menu callback attached to 'node/%node/delete'.
 * Ask for confirmation before proceeding with node deletion.
 */
function module_grants_node_delete_confirm(&$form_state, $node) {
  $nid = $node->nid;
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $nid,
  );
  $cancel_page = "node/$nid";
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $node->title)),
    isset($_GET['destination']) ? $_GET['destination'] : $cancel_page,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Initiate node deletion and set the redirection page.
 */
function module_grants_node_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    _module_grants_node_delete($form_state['values']['nid']);
  }
  if (module_exists('module_grants_monitor') && user_tools_user_any_access(module_grants_monitor_perm())) {
    $form_state['redirect'] = 'accessible-content';
  }
  else {
    $form_state['redirect'] = '<front>';
  }
}
