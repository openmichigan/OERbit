<?php

/**
 * This update makes it possible for consumers to store tokens in the common
 * token table. It also adds the possibility to add consumer-consumers to the
 * common consumer table.
 *
 * NB: There is a weakness in the current implementation that prevents a site
 *     from acting as a consumer of itself. That would result in hitting a
 *     unique constraint in the db as the token key is the primary key. /Hugo
 */
function _oauth_common_update_6003() {
  $ret = array();

  db_add_field($ret, 'oauth_common_token', 'provider_token', array(
    'description' => t('Whether this is a consumer or a provider token'),
    'type' => 'int',
    'size' => 'tiny',
    'unsigned' => TRUE,
    'not null' => TRUE,
    'default' => 1,
  ));

  db_add_field($ret, 'oauth_common_consumer', 'provider_consumer', array(
    'description' => t('Whether this is a provider consumer or a consumer consumer'),
    'type' => 'int',
    'size' => 'tiny',
    'unsigned' => TRUE,
    'not null' => TRUE,
    'default' => 1,
  ));

  return $ret;
}
