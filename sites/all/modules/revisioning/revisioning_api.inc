<?php

/**
 * @file
 * API functions of Revisioning module
 *
 * Reusable functions that do the dirty work.
 */

define('REVISION_ARCHIVED', 0);
define('REVISION_CURRENT', 1);
define('REVISION_PENDING', 2);

/**
 * Some naming conventions
 *
 * Pending:
 *   - revision with (vid > current_vid) of ANY node
 *     OR single revision of UNPUBLISHED node
 * Current, published:
 *   - revision with (vid == current_vid) of PUBLISHED node
 * Archived:
 *   - all other revisions, i.e.
 *     revision with (vid < current_vid) of ANY node
 *     OR revision with (vid == current_vid) of UNPUBLISHED node
 *
 * Note: these will change when Revisioning is going to store revision states
 * independently from vid number (e.g. in different table).
 */

/**
 * Return a single or all possible revision state names.
 *
 * @param $state
 *  optional state id, as defined in revisioning_api.inc
 * @return
 *  if $state is provided, state name. Otherwise, state names array keyed by state id.
 */
function revisioning_revision_states($state = NULL) {
  static $states;
  $states = array(
    REVISION_ARCHIVED => t('Archived'),
    REVISION_CURRENT  => t('Current, published'),
    REVISION_PENDING  => t('Pending'),
  );
  return $state === NULL ? $states : $states[$state];
}

/**
 * Return TRUE when either of the following is true:
 * o the supplied node has at least one revision more recent than the current
 * o the node is not yet published and consists of a single revision
 *
 * Relies on vid, current_revision_id and num_revisions set on the node object,
 * see function node_tools_nodeapi()
 *
 * @param $node
 * @return TRUE, if node is pending according to the above definition
 */
function _revisioning_node_is_pending($node) {
  return ($node->vid > $node->current_revision_id) || (!$node->status && $node->num_revisions == 1);
}

/**
 * Implementation of hook_revisionapi().
 *
 * Act on various revision events.
 *
 * @param $op
 *  Operation
 * @param $node
 *  Node of current operation (loaded with vid of the operation).
 *
 * "Pre" operations can be useful to get values before they are lost or changed,
 * for example, to save a backup of revision before it's deleted.
 * Also, for "pre" operations vetoing mechanics could be implemented, so it
 * would be possible to veto an operation via hook_revisionapi(). For example,
 * when the hook is returning FALSE, operation will be vetoed.
 *
 * @TODO: Add more operations if needed.
 */
function revisioning_revisionapi($op, $node) {
  switch ($op) {
    case 'pre revert':
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_pre_revert', $node);
      }
      break;

    case 'post revert':
      // Invoke the revisioning trigger passing 'revert' as the operation
      if (module_exists('trigger')) {
        module_invoke_all('revisioning', 'revert', $node, $node->vid);
      }
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_post_revert', $node);
      }
      break;

    case 'pre publish':
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_pre_publish', $node);
      }
      break;

    case 'post publish':
      // Invoke the revisioning trigger passing 'publish' as the operation
      if (module_exists('trigger')) {
        module_invoke_all('revisioning', 'publish', $node);
      }
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_post_publish', $node);
      }
      break;

  //case 'pre unpublish':
      // Not implemented: do we really need it ?

    case 'post unpublish':
      // Invoke the revisioning trigger passing 'unpublish' as the operation
      if (module_exists('trigger')) {
        module_invoke_all('revisioning', 'unpublish', $node);
      }
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_post_unpublish', $node);
      }
      break;

    case 'pre delete':
      // Invoke corresponding Rules event
      if (module_exists('rules')) {
        rules_invoke_event('revisioning_pre_delete', $node);
      }
      break;

    case 'post delete':
      break;
  }
}

/**
 * Get the id of the latest revision belonging to a node.
 * @param
 *  $nid, id of the node
 * @return
 *  ID of the latest revision.
 */
function revisioning_get_latest_revision_id($nid) {
  return db_result(db_query('SELECT MAX(vid) FROM {node_revisions} WHERE nid=%d', $nid));
}

/**
 * Get the id of the user who last edited the supplied node, ie. the author
 * of the latest revision.
 * This is irrespective of whether this latest revision is pending or not,
 * unless TRUE is specified for the second argument, in which case the uid
 * of the creator of the current revision (published or not) is returned.
 *
 * @param $nid
 *  The id of the node whose most recent editor id is to be returned.
 * @param $current
 *  Whether the uid of the current or very latest revision should be returned.
 * @return
 *  A single number being the user id (uid).
 */
function revisioning_get_last_editor($nid, $current = FALSE) {
  $sql = ($current)
    ? "SELECT vid FROM {node} WHERE nid = %d"
    : "SELECT MAX(vid) FROM {node_revisions} WHERE nid = %d";
  $vid = db_result(db_query($sql, $nid));
  return db_result(db_query("SELECT uid FROM {node_revisions} WHERE vid = %d", $vid));
}

/**
 * Revert node to selected revision without changing its publication status.
 *
 * @param $node
 *  Target $node object (loaded with target revision) or nid of target node
 * @param $vid
 *  Optional vid of revision to revert to, if provided $node must not be an object.
 */
function _revisioning_revertpublish_revision(&$node, $vid = NULL) {
  $node_revision = is_object($node) ? $node : node_load($node, $vid);
  $return = module_invoke_all('revisionapi', 'pre revert', $node_revision);
  if (in_array(FALSE, $return)) {
    drupal_goto('node/'. $node_revision->nid .'/revisions/'. $node_revision->vid .'/view');
    die;
  }
  _revisioning_revert_revision($node_revision);
  module_invoke_all('revisionapi', 'post revert', $node_revision);
}

/**
 * Revert node to selected revision without publishing it.
 *
 * This is same as node_revision_revert_confirm_submit() in node_pages.inc,
 * except it doesn't put any messages on screen.
 *
 * @param $node
 *  Target $node object (loaded with target revision) or nid of target node
 * @param $vid
 *  optional vid of revision to revert to, if provided $node is not an object.
 */
function _revisioning_revert_revision(&$node, $vid = NULL) {
  $node_revision = is_object($node) ? $node : node_load($node, $vid);
  $node_revision->revision = 1;
  $node_revision->log = t('Copy of the revision from %date.', array('%date' => format_date($node_revision->revision_timestamp)));
  if (module_exists('taxonomy')) {
    $node_revision->taxonomy = array_keys($node_revision->taxonomy);
  }
  node_save($node_revision);
  watchdog('content', '@type: reverted %title revision %revision.', array('@type' => $node_revision->type, '%title' => $node_revision->title, '%revision' => $node_revision->vid));
}

/**
 * Publish node, without calling node_save().
 * @obsolete
 *  This function is no longer used. Use _revisioning_publish_revision().
 *
 * @param $node
 *  Target $node object or nid of target node
 * @param $clear_cache
 *   Whether to clear the cache afterwards or not. Clearing the cache on every
 *   node during bulk operations can be time-consuming.
 *
function _revisioning_publish_node($node, $clear_cache = TRUE) {
  if (is_numeric($node)) {
    $node = node_load($node);
  }
  db_query("UPDATE {node} SET status=1 WHERE nid=%d", $node->nid);
  // Let other modules know there was an update on the node, just like
  // node_save() does.
  $node->status = 1;
  node_invoke_nodeapi($node, 'update');
  // Update the node access table for this node.
  node_access_acquire_grants($node);
  if ($clear_cache) {
    cache_clear_all();
  }
}
 */

/**
 * Unpublish node, without calling node_save().
 *
 * @param $node
 *  Target $node object or nid.
 * @param $clear_cache
 *   Whether to clear the cache afterwards or not. Clearing the cache on every
 *   node during bulk operations can be time-consuming.
 */
function _revisioning_unpublish_node($node, $clear_cache = TRUE) {
  if (is_numeric($node)) {
    $node = node_load($node);
  }
  db_query("UPDATE {node} SET status=0 WHERE nid=%d", $node->nid);
  // Let other modules know there was an update on the node, just like
  // node_save() does.
  $node->status = 0;
  $node->bypass_nodeapi = TRUE; // avoid revisioning_nodeapi() doing stuff
  $node->pathauto_perform_alias = FALSE; // avoid pathauto_nodeapi() doing stuff
  node_invoke_nodeapi($node, 'update');
  // Update the node access table for this node.
  node_access_acquire_grants($node);

  if ($clear_cache) {
    cache_clear_all();
  }
}

/**
 * Delete selected revision of node, provided it's not current.
 *
 * This is same as node_revision_delete_confirm_submit() in node_pages.inc,
 * except it doesn't put any messages on the screen. This way it becomes
 * reusable (eg. in actions).
 * Since we are calling nodeapi as in node_revision_delete_confirm_submit(), we
 * invoke our "post delete" revisionapi hook in nodeapi. This way revisionapi
 * hooks work the same way both with "delete revision" submit handler and when
 * this function is called, and we don't invoke revisionapi "post delete" hook
 * twice.
 *
 * @param $node
 *  Target $node object (loaded with target revision) or nid of target node
 * @param $vid
 *  optional vid of revision to delete, if provided $node is not object.
 *
 * @TODO: Insert check to prevent deletion of current revision of node.
 */
function _revisioning_delete_revision(&$node, $vid = NULL) {
  $node_revision = is_object($node) ? $node : node_load($node, $vid);
  module_invoke_all('revisionapi', 'pre delete', $node_revision);
  db_query("DELETE FROM {node_revisions} WHERE nid = %d AND vid = %d", $node_revision->nid, $node_revision->vid);
  node_invoke_nodeapi($node_revision, 'delete revision');
  watchdog('content', '@type: deleted %title revision %revision.', array('@type' => $node_revision->type, '%title' => $node_revision->title, '%revision' => $node_revision->vid));
}

/**
 * Unpublish revision (i.e. the node).
 *
 * Note that no check is made as to whether the initiating user has permission
 * to unpublish this node.
 *
 * @param $node
 *  Target $node object or nid of target node
 */
function _revisioning_unpublish_revision(&$node) {
  $node_revision = is_object($node) ? $node : node_load($node);
  module_invoke_all('revisionapi', 'pre unpublish', $node_revision);
  _revisioning_unpublish_node($node_revision);
  watchdog('content', 'Unpublished @type %title', array('@type' => $node_revision->type, '%title' => $node_revision->title), WATCHDOG_NOTICE, l(t('view'), "node/$node_revision->nid"));
  module_invoke_all('revisionapi', 'post unpublish', $node_revision);
}

/**
 * Make the supplied revision of the node current and publish it.
 * It is the caller's responsibility to provide proper revision.
 * Note that no check is made as to whether the initiating user has permission
 * to publish this revision.
 *
 * @param $node
 *  Target $node object (loaded with target revision) or nid of target node
 * @param $vid
 *  optional vid of revision to make current, if provided $node is not object.
 * @param $clear_cache
 *   Whether to clear the cache afterwards or not. Clearing the cache on every
 *   node during bulk operations can be time-consuming.
 */
function _revisioning_publish_revision(&$node, $vid = NULL, $clear_cache = TRUE) {
  $node_revision = is_object($node) ? $node : node_load($node, $vid);
  $return = module_invoke_all('revisionapi', 'pre publish', $node_revision);
  if (in_array(FALSE, $return)) {
    drupal_goto('node/'. $node_revision->nid .'/revisions/'. $node_revision->vid .'/view');
    die;
  }
  // Update node table, making sure the "published" (ie. status) flag is set
  db_query("UPDATE {node} SET vid=%d, title='%s', status=1 WHERE nid=%d", $node_revision->vid, $node_revision->title, $node_revision->nid);
  if ($clear_cache) {
    cache_clear_all();
  }
  $node_revision->status = 1;
  $node_revision->bypass_nodeapi = TRUE; // avoid revisioning_nodeapi() doing stuff
  $node_revision->pathauto_perform_alias = FALSE; // avoid pathauto_nodeapi() doing stuff
  node_invoke_nodeapi($node_revision, 'update');
  // Update the node access table for this node.
  node_access_acquire_grants($node_revision);

  watchdog('content', 'Published rev #%revision of @type %title', array('@type' => $node_revision->type, '%title' => $node_revision->title, '%revision' => $node_revision->vid), WATCHDOG_NOTICE, l(t('view'), "node/$node_revision->nid/revisions/$node_revision->vid/view"));
  module_invoke_all('revisionapi', 'post publish', $node_revision);
}

/**
 * Find the most recent pending revision, make it current, unless it already is
 * and publish node.
 * Note that no check is made as to whether the initiating user has permission
 * to publish this node.
 *
 * @param $node
 *   The node object whose latest pending revision is to be published
 * @return
 *   TRUE if operation was successful, FALSE if there is no pending revision to
 *   publish
 */
function _revisioning_publish_latest_revision(&$node) {
  // Get latest pending revision or take the current provided it's UNpublished
  $latest_pending = array_shift(_revisioning_get_pending_revisions($node->nid));
  if (!$latest_pending) {
    if (!$node->status && $node->is_current) {
      _revisioning_publish_revision($node);
      return TRUE;
    }
  }
  else {
    _revisioning_publish_revision($node->nid, $latest_pending->vid);
    return TRUE;
  }
  return FALSE;
}

/**
 * Return a count of the number of revisions newer than the supplied vid.
 *
 * @param $vid
 *  The reference vid.
 * @param $nid
 *  The id of the node.
 * @return
 *  integer
 */
function _revisioning_get_number_of_revisions_newer_than($vid, $nid) {
  return db_result(db_query("SELECT COUNT(*) FROM {node} n INNER JOIN {node_revisions} r ON n.nid=r.nid WHERE (r.vid>%d AND n.nid=%d)", $vid, $nid));
}

/**
 * Return a count of the number of revisions newer than the current revision.
 *
 * @param $nid
 *  The id of the node.
 * @return
 *  integer
 */
function _revisioning_get_number_of_pending_revisions($nid) {
  return db_result(db_query("SELECT COUNT(*) FROM {node} n INNER JOIN {node_revisions} r ON n.nid=r.nid WHERE (r.vid>n.vid AND n.nid=%d)", $nid));
}

/**
 * Get the number of archived revisions belonging to a node.
 * @param
 *  $nid, id of the node
 * @return
 *  A count representing the number of archived revisions for the node
 *  Returns zero if there is only one (i.e. the current) revision.
 */
function revisioning_get_number_of_archived_revisions($node) {
  return db_result(db_query('SELECT COUNT(vid) FROM {node_revisions} WHERE nid = %d AND vid < %d', $node->nid, $node->current_revision_id));
}

/**
 * Delete all revisions with a vid less than the current.
 */
function revisioning_delete_archived_revisions($node) {
  return db_query('DELETE FROM {node_revisions} WHERE nid = %d AND vid < %d', $node->nid, $node->current_revision_id);
}

/**
 * Retrieve a list of revisions with a vid greater than the current.
 *
 * @param $nid
 *  The node id to retrieve.
 * @return
 *  An array of revisions (latest first), each containing vid, title and
 *  content type.
 */
function _revisioning_get_pending_revisions($nid) {
  $sql = "SELECT r.vid, r.title, n.type FROM {node} n INNER JOIN {node_revisions} r ON n.nid=r.nid WHERE (r.vid>n.vid AND n.nid=%d) ORDER BY r.vid DESC";
  $result = db_query($sql, $nid);
  $revisions = array();
  while ($revision = db_fetch_object($result)) {
    $revisions[$revision->vid] = $revision;
  }
  return $revisions;
}

/**
 * Retrieve a list of all revisions (archive, current, pending) belonging to
 * the supplied node.
 *
 * @param $nid
 *  The node id to retrieve.
 * @param $include_taxonomy_terms
 *  Whether to also retrieve the taxonomy terms for each revision
 * @return
 *  An array of revision objects, each with published flag, log message, vid,
 *  title, timestamp and name of user that created the revision
 */
function _revisioning_get_all_revisions_for_node($nid, $include_taxonomy_terms = FALSE) {
  $sql_select = 'SELECT n.type, n.status, r.vid, r.title, r.log, r.uid, r.timestamp, u.name';
  $sql_from   = ' FROM {node_revisions} r LEFT JOIN {node} n ON n.vid=r.vid INNER JOIN {users} u ON u.uid=r.uid';
  $sql_where  = ' WHERE r.nid=%d ORDER BY r.vid DESC';
  if ($include_taxonomy_terms) {
    $sql_select .= ', td.name AS term';
    $sql_from .= ' LEFT JOIN {term_node} tn ON r.vid=tn.vid LEFT JOIN {term_data} td ON tn.tid=td.tid';
    $sql_where .= ', term ASC';
  }
  $sql = $sql_select . $sql_from . $sql_where;
  $result = db_query($sql, $nid);
  $revisions = array();
  while ($revision = db_fetch_object($result)) {
    if (empty($revisions[$revision->vid])) {
      $revisions[$revision->vid] = $revision;
    }
    elseif ($include_taxonomy_terms) {
      // If a revision has more than one taxonomy term, these will be returned
      // by the query as seperate objects differing only in their term fields.
      $existing_revision = $revisions[$revision->vid];
      $existing_revision->term .= '/'. $revision->term;
    }
  }
  return $revisions;
}

/**
 * Return revision type of the supplied node.
 *
 * @param &$node
 *  Node object to check
 * @return
 *  Revision type
 */
function _revisioning_revision_is(&$node) {
  if ($node->is_pending) {
    return REVISION_PENDING;
  }
  return ($node->is_current && $node->status) ? REVISION_CURRENT : REVISION_ARCHIVED;
}

/**
 * Return a string with details about the node that is about to be displayed.
 *
 * Called from revisioning_nodeapi().
 *
 * @param $node
 *  The node that is about to be viewed
 * @return
 *  A translatable message containing details about the node
 */
function _revisioning_node_info_msg($node) {
  // Get username for the revision, not the creator of the node
  $revision_author = user_load($node->revision_uid);
  $placeholder_data = array(
    '@content_type' => $node->type,
    '%title' => $node->title,
    '!author' => theme('username', $revision_author),
    '@date' => format_date($node->revision_timestamp, 'small'),
  );
  $revision_type = _revisioning_revision_is($node);
  switch ($revision_type) {
    case REVISION_PENDING:
      return t('Displaying <em>pending</em> revision of @content_type %title, last modified by !author on @date', $placeholder_data);

    case REVISION_CURRENT:
      return t('Displaying <em>current, published</em> revision of @content_type %title, last modified by !author on @date', $placeholder_data);

    case REVISION_ARCHIVED:
      return t('Displaying <em>archived</em> revision of @content_type %title, last modified by !author on @date', $placeholder_data);
  }
}

/**
 * Return TRUE only if the user account has ALL of the supplied permissions.
 *
 * @param $permissions
 *  An array of permissions (strings)
 * @param $account
 *  The user account object. Defaults to the current user if omitted.
 * @return bool
 */
function revisioning_user_all_access($permissions, $account = NULL) {
  foreach ($permissions as $permission) {
    if (!user_access($permission, $account)) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Return an array of names of content types that are subject to moderation.
 *
 * @return array of strings, may be empty
 */
function revisioning_moderated_content_types() {
  $moderated_content_types = array();
  foreach (node_get_types() as $type) {
    $content_type = check_plain($type->type);
    if (node_tools_content_is_moderated($content_type)) {
      $moderated_content_types[] = $content_type;
    }
  }
  return $moderated_content_types;
}

/**
 * Return the id of the user who created the revision by the supplied vid.
 */
function revisioning_get_revision_uid($vid) {
  return db_result(db_query('SELECT uid FROM {node_revisions} WHERE vid = %d', $vid));
}