<?php

/**
 * This update adds a expiry time column to the tokens table.
 */
function _oauth_common_update_6002() {
  $ret = array();

  db_add_field($ret, 'oauth_common_token', 'expires', array(
    'type' => 'int',
    'not null' => TRUE,
    'default' => 0,
    'description' => 'The expiry time for the token, as a Unix timestamp.',
  ));
  db_add_index($ret, 'oauth_common_token', 'expires', array('expires'));
  $ret[] = update_sql("UPDATE {oauth_common_token} SET expires=created+7200 WHERE type='request'");

  return $ret;
}
