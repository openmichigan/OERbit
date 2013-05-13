<?php

/**
 * This update turns the contexts into ctools-manageable entities and migrates
 * the authorization levels into the new contexts table.
 */
function _oauth_common_update_6200() {
  $ret = array();

  $contexts = array();

  db_create_table($ret, 'oauth_common_context', _oauth_common_oauth_common_context_6200());

  // Fetch the authorization levels and create contexts from them
  $res = db_query("SELECT * FROM {oauth_authorization_levels}");
  while ($l = db_fetch_array($res)) {
    $name = $l['name'];
    $context = $l['context'];
    unset($l['name'], $l['context']);
    if (!isset($contexts[$name])) {
      $contexts[$name] = oauth_common_context_new();
      $contexts[$name]->name = $name;
      $contexts[$name]->title = $name;
    }
    $contexts[$context]['authorization_levels'][$name] = $l;
  }
  foreach ($contexts as $context) {
    oauth_common_context_save($context);
  }

  // Change all the oauth_common_token indexes and keys to take provider_token
  // into account.
  db_drop_primary_key(&$ret, 'oauth_common_token');
  db_drop_index(&$ret, 'oauth_common_token', 'token_key_type');
  db_drop_index(&$ret, 'oauth_common_token', 'consumer_key');

  db_add_primary_key(&$ret, 'oauth_common_token', array('token_key', 'provider_token'));
  db_add_index(&$ret, 'oauth_common_token', 'token_key_type', array('token_key', 'provider_token', 'type'));
  db_add_index(&$ret, 'oauth_common_token', 'consumer_key', array('consumer_key', 'provider_token'));

  db_drop_table($ret, 'oauth_authorization_levels');

  return $ret;
}

function _oauth_common_oauth_common_context_6200() {
  return array(
    'description' => 'Stores contexts for OAuth common',
    'export' => array(
      'identifier'      => 'context',
      'export callback' => 'oauth_common_context_export',
      'list callback'   => 'oauth_common_context_list',
      'key'             => 'name',
    ),
    'fields' => array(
      'cid' => array(
        'type'        => 'serial',
        'description' => 'Primary ID field for the table. Not used for anything except internal lookups.',
        'not null'    => TRUE,
        'no export'   => TRUE,
      ),
      'name' => array(
        'description' => 'The computer-readable name of the context.',
        'type'        => 'varchar',
        'length'      => 32,
        'not null'    => TRUE,
      ),
      'title' => array(
        'description' => 'The localizable title of the authorization context.',
        'type'        => 'varchar',
        'length'      => 100,
        'not null'    => TRUE,
      ),
      'authorization_options' => array(
        'description'    => 'Authorization options.',
        'type'           => 'text',
        'size'           => 'big',
        'not null'       => TRUE,
        'serialize'      => TRUE,
        'object default' => array(),
      ),
      'authorization_levels' => array(
        'description'    => 'Authorization levels for the context.',
        'type'           => 'text',
        'size'           => 'big',
        'not null'       => TRUE,
        'serialize'      => TRUE,
        'object default' => array(),
      ),
    ),
    'primary key' => array('cid'),
    'unique keys' => array(
      'context' => array('name'),
    ),
  );
}
