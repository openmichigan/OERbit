<?php

/**
 * This update adds the concept of contexts for consumers and authorization levels.
 * Also adding a couple of indexes that make sense when oauth_common is
 * acting as a consumer of other services.
 */
function _oauth_common_update_6100() {
  $ret = array();

  db_add_index($ret, 'oauth_common_token', 'consumer', array('consumer_key', 'type', 'provider_token'));

  db_drop_index($ret, 'oauth_common_consumer_token', 'token_key_type');
  db_drop_field($ret, 'oauth_common_consumer_token', 'type');
  db_add_field($ret, 'oauth_common_consumer_token', 'provider_url', array(
    'description' => t('The url to the provider.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
  ));
  db_add_field($ret, 'oauth_common_consumer_token', 'access_endpoint', array(
    'description' => t('The endpoint to fetch the access token.'),
    'type'        => 'varchar',
    'length'      => 255,
    'not null'    => TRUE,
    'default'     => '',
  ));

  db_add_field($ret, 'oauth_authorization_levels', 'context', array(
    'description' => t('The context for the authorization level.'),
    'type'        => 'varchar',
    'length'      => 32,
    'not null'    => TRUE,
    'default'     => 'default',
  ));

  db_add_field($ret, 'oauth_authorization_levels', 'weight', array(
    'type' => 'int',
    'not null' => TRUE,
    'default' => 0,
    'description' => 'Determines the order that the authorization levels will be displayed in.',
  ));

  db_add_field($ret, 'oauth_authorization_levels', 'enabled', array(
    'type' => 'int',
    'size' => 'tiny',
    'unsigned' => TRUE,
    'not null' => TRUE,
    'default' => 1,
    'description' => 'Whether the authorization level is enabled or disabled.',
  ));

  db_drop_primary_key($ret, 'oauth_authorization_levels');
  db_add_primary_key($ret, 'oauth_authorization_levels', array('name', 'context'));

  db_add_field($ret, 'oauth_common_consumer', 'context', array(
    'description' => t('The application context.'),
    'type'        => 'varchar',
    'length'      => 32,
    'not null'    => TRUE,
    'default'     => 'default',
  ));

  return $ret;
}
