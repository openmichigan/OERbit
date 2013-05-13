<?php

/**
 * This update massively refactors the database.
 */
function _oauth_common_update_6300() {
  $ret = array();

  $oauth_common_consumer = _oauth_common_consumer_schema();
  $oauth_common_token = _oauth_common_token_schema();
  $oauth_common_provider_consumer = _oauth_common_provider_consumer_schema();
  $oauth_common_provider_token = _oauth_common_provider_token_schema();

  db_drop_primary_key($ret, 'oauth_common_consumer');
  db_drop_primary_key($ret, 'oauth_common_token');

  db_drop_index($ret, 'oauth_common_token', 'token_key_type');
  db_drop_index($ret, 'oauth_common_token', 'consumer_key');

  db_drop_index($ret, 'oauth_common_nonce', 'timestamp');

  db_add_field($ret, 'oauth_common_consumer', 'csid',     $oauth_common_consumer['fields']['csid'], array('primary key' => array('csid')));
  db_add_field($ret, 'oauth_common_consumer', 'key_hash', $oauth_common_consumer['fields']['key_hash'], array('indexes' => array('key_hash' => array('key_hash'))));

  db_add_field($ret, 'oauth_common_token', 'tid',      $oauth_common_token['fields']['tid'], array('primary key' => array('tid')));  
  db_add_field($ret, 'oauth_common_token', 'csid',     $oauth_common_token['fields']['csid']);
  db_add_field($ret, 'oauth_common_token', 'key_hash', $oauth_common_token['fields']['key_hash'], array('indexes' => array('key_hash' => array('key_hash'))));
  db_add_field($ret, 'oauth_common_token', 'type_new', $oauth_common_token['fields']['type']);

  db_change_field($ret, 'oauth_common_consumer', 'consumer_key', 'consumer_key', $oauth_common_consumer['fields']['consumer_key']);
  db_change_field($ret, 'oauth_common_consumer', 'secret',       'secret',       $oauth_common_consumer['fields']['secret']);

  db_change_field($ret, 'oauth_common_token', 'token_key', 'token_key', $oauth_common_token['fields']['token_key']);
  db_change_field($ret, 'oauth_common_token', 'secret',    'secret',    $oauth_common_token['fields']['secret']);

  db_change_field($ret, 'oauth_common_nonce', 'nonce', 'nonce', array(
    'type'     => 'varchar',
    'length'   => 255,
    'not null' => TRUE
  ));
  db_change_field($ret, 'oauth_common_nonce', 'token', 'token_key', array(
    'type'     => 'varchar',
    'length'   => 32,
    'not null' => TRUE,
  ), array('indexes' => array(
    'timekey' => array('timestamp', 'token_key'),
  )));

  db_create_table($ret, 'oauth_common_provider_consumer', $oauth_common_provider_consumer);
  db_create_table($ret, 'oauth_common_provider_token',    $oauth_common_provider_token);

  $ret[] = update_sql('INSERT INTO {oauth_common_provider_consumer}
      (csid, consumer_key, created, changed, uid, name, context, callback_url)
    SELECT c.csid, c.consumer_key, c.created, c.changed, c.uid, c.name, c.context, c.callback_url
      FROM {oauth_common_consumer} c WHERE c.provider_consumer = 1');
  $ret[] = update_sql('INSERT INTO {oauth_common_provider_token}
      (tid, token_key, created, changed, services, authorized)
    SELECT t.tid, t.token_key, t.created, t.changed, t.services, t.authorized
      FROM {oauth_common_token} t WHERE t.provider_token = 1');

  $ret[] = update_sql("UPDATE {oauth_common_consumer} SET key_hash = SHA1(consumer_key)");
  $ret[] = update_sql("UPDATE {oauth_common_token} SET type_new = (type != 'access'), key_hash = SHA1(token_key)");
  $ret[] = update_sql("UPDATE {oauth_common_token} t, {oauth_common_consumer} c SET t.csid = c.csid WHERE t.consumer_key = c.consumer_key");

  $to_drop = array('provider_consumer', 'created', 'changed', 'uid', 'name', 'context', 'callback_url');
  foreach ($to_drop as $field) {
    db_drop_field($ret, 'oauth_common_consumer', $field);
  }

  $to_drop = array('provider_token', 'type', 'consumer_key', 'created', 'changed', 'services', 'authorized');
  foreach ($to_drop as $field) {
    db_drop_field($ret, 'oauth_common_token', $field);
  }

  db_change_field($ret, 'oauth_common_token', 'type_new', 'type', $oauth_common_token['fields']['type']);

  return $ret;
}
