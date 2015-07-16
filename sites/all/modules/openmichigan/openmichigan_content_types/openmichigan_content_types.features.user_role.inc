<?php

/**
 * Implementation of hook_user_default_roles().
 */
function openmichigan_content_types_user_default_roles() {
  $roles = array();

  // Exported role: content manager
  $roles['content manager'] = array(
    'name' => 'content manager',
  );

  // Exported role: manager
  $roles['manager'] = array(
    'name' => 'manager',
  );

  // Exported role: resource manager
  $roles['resource manager'] = array(
    'name' => 'resource manager',
  );

  // Exported role: unit manager
  $roles['unit manager'] = array(
    'name' => 'unit manager',
  );

  return $roles;
}
