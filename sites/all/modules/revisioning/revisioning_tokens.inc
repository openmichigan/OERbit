<?php

/**
 * @file
 * Add tokens pertaining to the Revisioning module.
 *
 * For examples see the Token module, files token/token_<module>.inc
 *
 * Added to the set are the following, which are not provided by token_node.inc
 *   vid: Node revision ID
 *   revision-title: Revision title
 *   revision-author-uid: Revision author's user id
 *   revision-author-name: Revision author's user name
 *   revision-author-name-raw: Revision author's user name -- aw user input.
 *   revision-author-mail: Revision author's e-mail
 *   revision-author-mail-raw: Revision author's e-mail -- raw user input.
 *
 * @ingroup token
 */

/**
 * Implementation of hook_token_list().
 */
function revisioning_token_list($type = 'all') {
  if ($type == 'node' || $type == 'all') {
    $tokens = array();
    $tokens['node']['vid'] = t('Node revision ID');
    $tokens['node']['revision-title'] = t('Revision title');
    $tokens['node']['revision-log'] = t('Revision log message');
    $tokens['node']['revision-author-uid'] = t("Revision author's user id");
    $tokens['node']['revision-author-name'] = t("Revision author's user name");
    $tokens['node']['revision-author-name-raw'] = t("Revision author's user name. WARNING - raw user input.");
    $tokens['node']['revision-author-mail'] = t("Revision author's e-mail");
    $tokens['node']['revision-author-mail-raw'] = t("Revision author's e-mail. WARNING - raw user input.");
    return $tokens;
  }
}

/**
 * Implementation of hook_token_values().
 */
function revisioning_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'node':
      $values['vid'] = $object->vid;
      $values['revision-title'] = $object->title;
      $values['revision-log'] = $object->log;
      if (empty($object->revision_uid)) { // Can happen in Rules context
        $object->revision_uid = revisioning_get_revision_uid($object->vid);
      }
      _set_revision_author_values($object->revision_uid, $values);
      break;

    case 'op':
      switch ($object) {
        case 'publish':
        case 'revert':
        case 'unpublish':
          $nid = arg(1);
          $revision = node_load($nid, node_tools_get_current_node_revision_id($nid));
          $values['vid'] = $revision->vid;
          $values['revision-title'] = $revision->title;
          $values['revision-log'] = $revision->log;
          _set_revision_author_values($revision->revision_uid, $values);
      }
      break;
  }
  return $values;
}

function _set_revision_author_values($uid, &$values) {
  $account = db_fetch_object(db_query('SELECT name, mail FROM {users} WHERE uid=%d', $uid));
  $values['revision-author-uid'] = $uid;
  $values['revision-author-name'] = check_plain($account->name);
  $values['revision-author-name-raw'] = $account->name;
  $values['revision-author-mail'] = check_plain($account->mail);
  $values['revision-author-mail-raw'] = $account->mail;
}
