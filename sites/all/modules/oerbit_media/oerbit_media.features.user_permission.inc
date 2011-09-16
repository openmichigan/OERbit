<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_media_user_default_permissions() {
  $permissions = array();

  // Exported permission: execute Reload Embedded Media Data (emfield_operations_reload)
  $permissions['execute Reload Embedded Media Data (emfield_operations_reload)'] = array(
    'name' => 'execute Reload Embedded Media Data (emfield_operations_reload)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  return $permissions;
}
