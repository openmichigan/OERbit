<?php

/**
 * @file
 * Rendering and altering of pages and forms used by Revisioning
 */

/**
 * Implementation of hook_form_alter().
 *
 * Note: for cases where the FORM_ID is known a priori use
 * revisioning_form_FORM_ID_form_alter(), e.g. revisioning_form_node_type_form_alter()
 */
function revisioning_form_alter(&$form, &$form_state, $form_id) {
  // Alter the Create/Edit form
  if (isset($form['#id']) && $form['#id'] == 'node-form') {
    $content_type = $form['type']['#value'];
    // Note that $form_id == $content_type_$form['#id']
    $form['options']['#collapsed'] = FALSE;
    // Only add this tick-box if user has the 'administer nodes' permission
    if (user_access('administer nodes')) {
      $form['revision_information']['revision_moderation'] = array(
        '#title' => t('New revision in draft, pending moderation'),
        '#type' => 'checkbox',
        '#default_value' => node_tools_content_is_moderated($content_type)
      );
    }
    else {
      // Don't show tickbox, just set default on form
      $form['revision_moderation'] = array(
        '#type' => 'value',
        '#value' => node_tools_content_is_moderated($content_type)
      );
    }

    // In addition to node_form_submit() append our own handler to the list.
    $form['buttons']['submit']['#submit'][] = '_revisioning_form_submit';

    // Change the meaning of the 'Delete (all revisions)' button when editing
    // a revision to be the deletion of the viewed revision, rather than the
    // node.
    $nid = $form['#node']->nid;
    $vid = $form['#node']->vid;
    if (isset($form['buttons']['delete']) && user_access('delete revisions') && $vid != node_tools_get_current_node_revision_id($nid)) {
      $form['buttons']['delete']['#value'] =  t('Delete this revision');
      $form['buttons']['delete']['#submit'][] = '_revisioning_delete_submit';
    }
  }
}

/**
 * Implementation of hook_form_FORM_ID_form_alter().
 *
 * On content type edit form, add the "New revision in draft, pending moderation"
 * tick-box and a couple of radio-boxes to select the new revision and
 * auto-publish policies.
 */
function revisioning_form_node_type_form_alter(&$form, &$form_state) {
  $form['workflow']['#collapsed'] = FALSE;
  $form['workflow']['node_options']['#options']['revision_moderation'] = t('New revision in draft, pending moderation (requires "Create new revision")');

  $content_type = $form['#node_type']->type;
  $form['workflow']['revisioning'] = array(
    '#type' => 'fieldset',
    '#title' => t('New revision in draft'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['workflow']['revisioning']['new_revisions'] = array(
    '#title' => t('Create new revision'),
    '#type' => 'radios',
    '#options' => array(
      NEW_REVISION_WHEN_NOT_PENDING => t('Only when saving %type content that is not already in draft/pending moderation', array('%type' => $content_type)),
      NEW_REVISION_EVERY_SAVE       => t('Every time %type content is updated, even when saving content in draft/pending moderation', array('%type' => $content_type))),
    '#default_value' => (int)variable_get('new_revisions_'. $content_type, NEW_REVISION_WHEN_NOT_PENDING),
    '#description' => t('Use less disk space and avoid cluttering your revisions list. With the first option ticked, modifications are saved to the same copy (i.e. no additional revisions are created) until the content is published.')
    );
  $form['workflow']['revisioning']['revisioning_auto_publish'] = array(
    '#title' => t('Auto-publish drafts of @this type %type (for moderators)', array(
      '@this' => empty($content_type) ? t('this') : '', '%type' => $content_type)),
    '#type' => 'checkbox',
    '#default_value' => (int)variable_get('revisioning_auto_publish_'. $content_type, FALSE),
    '#description' => t('If this box is ticked and the logged-in user has one of the "publish revisions" permissions, then any draft of @this type %type is published immediately upon saving, without further review.', array(
      '@this' => empty($content_type) ? t('this') : '', '%type' => $content_type))
  );
}

/**
 * Return a confirmation page for publishing a revision.
 */
function revisioning_publish_confirm($form_state, $node) {
  $form['node_id']  = array('#type' => 'value', '#value' => $node->nid);
  $form['title']    = array('#type' => 'value', '#value' => $node->title);
  $form['revision'] = array('#type' => 'value', '#value' => $node->vid);
  $form['type']     = array('#type' => 'value', '#value' => $node->type);
  return confirm_form($form,
    t('Are you sure you want to publish this revision of %title?', array('%title' => $node->title)),
    'node/'. $node->nid .'/revisions',
    t('Publishing this revision will make it visible to the public.'),
    t('Publish'), t('Cancel'));
}

/**
 * Submission handler for the publish_confirm form.
 */
function revisioning_publish_confirm_submit($form, &$form_state) {
  $nid = $form_state['values']['node_id'];
  $vid = $form_state['values']['revision'];
  _revisioning_publish_revision($nid, $vid);
  drupal_set_message(t('Revision has been published.'));

  // [#886384]
  global $base_url;
  $url = $base_url . '/' . drupal_get_path_alias('node/'. $nid);
  cache_clear_all($url, 'cache_page');

  // Redirect to the same page as unpublish and revert
  $form_state['redirect'] = "node/$nid/revisions";
}

/**
 * Return a confirmation page for unpublishing the node.
 */
function revisioning_unpublish_confirm($form_state, $node) {
  $form['node_id'] = array('#type' => 'value', '#value' => $node->nid);
  $form['title']   = array('#type' => 'value', '#value' => $node->title);
  $form['type']    = array('#type' => 'value', '#value' => $node->type);
  return confirm_form($form,
    t('Are you sure you want to unpublish %title?', array('%title' => $node->title)),
    "node/$node->nid/revisions",
    t('Unpublishing will remove this content from public view.'),
    t('Unpublish'), t('Cancel'));
}

/**
 * Submission handler for the unpublish_confirm form.
 */
function revisioning_unpublish_confirm_submit($form, &$form_state) {
  $nid = $form_state['values']['node_id'];
  _revisioning_unpublish_revision($nid);
//$type = $form_state['values']['type']; // machine name, eg. 'story' rather than 'Story'
  $title = $form_state['values']['title'];
  drupal_set_message(t('%title is no longer publicly visible.', array('%title' => $title)));

  // [#886384]
  global $base_url;
  $url = $base_url . '/' . drupal_get_path_alias('node/'. $nid);
  cache_clear_all($url, 'cache_page');

  // Redirect to the same page as publish and revert
  $form_state['redirect'] = "node/$nid/revisions";
}

function revisioning_delete_archived_confirm($form_state, $node) {
  $node->num_archived = revisioning_get_number_of_archived_revisions($node);
  $form['node']  = array('#type' => 'value', '#value' => $node);
  $t = format_plural($node->num_archived,
    'Are you sure you want to delete the archived revision of %title?',
    'Are you sure you want to delete all @count archived revisions of %title?',
    array('%title' => $node->title)
  );
  return confirm_form($form, $t, 'node/' . $node->nid . '/revisions',
    t('This action cannot be undone.'),
    t('Delete archived'), t('Cancel'));
}

/**
 * Submission handler for the delete_archived_confirm form.
 */
function revisioning_delete_archived_confirm_submit($form, &$form_state) {
  $node = $form_state['values']['node'];
  revisioning_delete_archived_revisions($node);
  drupal_set_message(format_plural($node->num_archived, 'One archived revision deleted.', '@count archived revisions deleted.'));
  $form_state['redirect'] = ($node->num_revisions - $node->num_archived > 1)
    ? 'node/' . $node->nid . '/revisions'
    : 'node/' . $node->nid;
}

/**
 * Implementation of hook_form_FORM_ID_alter(), see
 * node.pages.inc/node_revision_revert_confirm()
 */
function revisioning_form_node_revision_revert_confirm_alter(&$form, &$form_state) {
  $node = $form['#node_revision'];
  if (_revisioning_get_number_of_pending_revisions($node->nid) > 0) {
    drupal_set_message(t('There is a pending revision. Are you sure you want to revert to an archived revision?'), 'warning');
  }
  array_unshift($form['#submit'], 'revisioning_revert_confirm_pre_submit');
  $form['#submit'][] = 'revisioning_revert_confirm_post_submit';
}

/**
 * Implementation of hook_form_FORM_ID_alter(), see
 * node.pages.inc/node_revision_delete_confirm()
 *
 * We only add "pre" submit handler, because "post delete" event is already
 * available via hook_nodeapi().
 */
function revisioning_form_node_revision_delete_confirm_alter(&$form, &$form_state) {
  array_unshift($form['#submit'], 'revisioning_revision_delete_confirm_pre_submit');
}

/**
 * Submission "pre" handler for the node_revision_delete_confirm form.
 *
 * Runs BEFORE the existing delete function in node.pages.inc
 */
function revisioning_revision_delete_confirm_pre_submit($form, &$form_state) {
  $node = $form['#node_revision'];
  $return = module_invoke_all('revisionapi', 'pre delete', $node);
  if (in_array(FALSE, $return)) {
    drupal_goto('node/'. $node->nid .'/revisions/'. $node->vid .'/view');
    die;
  }
}

/**
 * Submission "pre" handler the revert_confirm form.
 *
 * Runs BEFORE the existing revert function in node.pages.inc
 */
function revisioning_revert_confirm_pre_submit($form, &$form_state) {
  $node = $form['#node_revision'];
  module_invoke_all('revisionapi', 'pre revert', $node);
}

/**
 * Submission "post" handler for the revert_confirm form.
 *
 * Runs AFTER the existing revert function in node.pages.inc
 *
 * Note:
 * It would be nice if publish and revert were symmetrical operations and that
 * node_revision_revert_confirm_submit didn't save a physical copy of the
 * revision (under a new vid), as this has the side-effect of making all
 * "pending" revisions "archived". This is because the definition of "pending"
 * is: "node_vid > current_vid".
 * It would be better if "pending" relied on a separate flag rather than a field
 * such as vid or timestamp that changes every time a piece of code executes a
 * node_save().
 */
function revisioning_revert_confirm_post_submit($form, &$form_state) {
  $node = $form['#node_revision'];
//_revisioning_publish_node($node->nid); [#611988]
  module_invoke_all('revisionapi', 'post revert', $node);
}


/**
 * Return as a themed table a list of nodes that have pending revisions.
 * access rights of the logged-in user.
 *
 * @param $op
 *   Operation, one of 'view', 'update' or 'delete'.
 * @param $user_filter
 *   One of NO_FILTER, I_CREATED or I_LAST_MODIFIED.
 * @return
 *   themed HTML
 */
function _revisioning_show_pending_nodes($access = 'view', $user_filter = NO_FILTER) {
  $is_moderated = user_access('administer nodes') ? NO_FILTER : TRUE;
  $content_summary = module_grants_monitor_accessible_content_summary($access, NO_FILTER, $user_filter, $is_moderated, TRUE);
  if (user_access('view revision status messages') && strpos($content_summary, 'No content') === FALSE && !user_access('administer nodes')) {
    _revisioning_set_info_message();
  }
  return $content_summary;
}

function _revisioning_set_info_message() {
  if (user_access('publish revisions')) {
    $moderated_types = array();
    foreach (node_get_types() as $type) {
      if (node_tools_content_is_moderated($type->type) &&
        (user_access('view revisions') || user_access('view revisions of any '. $type->type .' content'))) {
        $moderated_types[] = $type->name;
      }
    }
    if (count($moderated_types) > 0) {
      drupal_set_message(t('You have permission to publish revisions of type(s): %moderated_types.',
        array('%moderated_types' => implode(', ', $moderated_types))));
    }
  }
}

/**
 * Handler for the 'Save' button on the edit form.
 *
 * When saving a new revision we shouldn't redirect to "View current", as
 * that's not the one we've saved. However at this stage, via the form, we
 * don't know the vid of the newly created revision, only the vid of the
 * revision we've just edited, so we get latest revision id from the database.
 */
function _revisioning_form_submit($form, &$form_state) {
  $nid = $form['#node']->nid; // Don't use $form_state['nid'], will NOT be empty for a new node
  // Don't redirect when creating new node or when the displayed vid is the current
  if (!empty($nid) && ($vid = revisioning_get_latest_revision_id($nid)) &&
    $vid != node_tools_get_current_node_revision_id($nid)) {
      $form_state['redirect'] = "node/$nid/revisions/$vid/view";
  }
}

/**
 * Handler for the 'Delete this revision' button on the edit form.
 *
 * Redirect to node/%/revisions/%/delete as opposed to node/%/delete
 */
function _revisioning_delete_submit(&$form, &$form_state) {
  $nid = $form['#node']->nid;
  $vid = $form['#node']->vid;
  $form_state['redirect'][0] = "node/$nid/revisions/$vid/delete";
}
