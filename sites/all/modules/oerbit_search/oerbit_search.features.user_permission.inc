<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_search_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer search
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  return $permissions;
}
