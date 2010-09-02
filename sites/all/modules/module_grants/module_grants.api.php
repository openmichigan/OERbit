<?php
// $Id: module_grants.api.php,v 1.2 2010/05/06 03:29:35 rdeboer Exp $

/**
 * @file
 *  Hooks provided by the Module Grants module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Called from module_grants_node_revision_access() this hook allows
 * contributed modules to either deny access to the supplied node or to
 * state which node operation the user must be allowed to execute to access
 * the node via the supplied revision operation.
 *
 * If implemented this function should return either FALSE (meaning deny
 * access to the node for this revision_op) or a required node operation (ie.
 * 'view', 'update', 'delete'). This node operation is passed to
 * module_grants_node_access(), which returns a boolean indicating whether
 * access is granted or not.
 * The Revisioning module takes advantage of this hook to combine its
 * revision-related user permissions with proper access control, as provided by
 * Module Grants.
 *
 * @param $revision_op
 * @param $node
 * @return
 *   either FALSE or the node operation required to access the node, i.e.
 *   'view', 'update' or 'delete'
 */
function hook_user_node_access($revision_op, $node) {
  switch ($revision_op) {
    case 'view revision list':
      return user_access('view revisions') ? 'view' : FALSE;

    case 'edit revisions':
      return user_access('edit revisions') ? 'update' : FALSE;
  }
  return 'view';
}

/**
 * @} End of "addtogroup hooks".
 */