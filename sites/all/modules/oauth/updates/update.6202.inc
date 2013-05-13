<?php

/**
 * This update allows for longer consumer secrets.
 */
function _oauth_common_update_6202() {
  $ret = array();

  db_change_field($ret, 'oauth_common_consumer', 'consumer_key', 'consumer_key', array(
    'description' => t('Consumer key.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));

  db_change_field($ret, 'oauth_common_consumer', 'secret', 'secret', array(
    'description' => t('Consumer secret.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));

  db_change_field($ret, 'oauth_common_token', 'secret', 'secret', array(
    'description' => t('Consumer secret.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));

  db_change_field($ret, 'oauth_common_token', 'token_key', 'token_key', array(
    'description' => t('Token key.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));

  db_change_field($ret, 'oauth_common_token', 'consumer_key', 'consumer_key', array(
    'description' => t('Consumer key from {oauth_common_consumer}.consumer_key.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));

  return $ret;
}
