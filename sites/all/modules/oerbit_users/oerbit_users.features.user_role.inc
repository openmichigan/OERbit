<?php

/**
 * Implementation of hook_user_default_roles().
 */
function oerbit_users_user_default_roles() {
  $roles = array();

  // Exported role: anonymous user
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
  );

  // Exported role: authenticated user
  $roles['authenticated user'] = array(
    'name' => 'authenticated user',
  );

  // Exported role: content manager
  $roles['content manager'] = array(
    'name' => 'content manager',
  );

  // Exported role: resource manager
  $roles['resource manager'] = array(
    'name' => 'resource manager',
  );

  // Exported role: site administrator
  $roles['site administrator'] = array(
    'name' => 'site administrator',
  );

  // Exported role: unit manager
  $roles['unit manager'] = array(
    'name' => 'unit manager',
  );

  return $roles;
}
