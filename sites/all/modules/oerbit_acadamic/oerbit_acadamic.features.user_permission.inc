<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_acadamic_user_default_permissions() {
  $permissions = array();

  // Exported permission: create course content
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: create information content
  $permissions['create information content'] = array(
    'name' => 'create information content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: create instructor content
  $permissions['create instructor content'] = array(
    'name' => 'create instructor content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: create material content
  $permissions['create material content'] = array(
    'name' => 'create material content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: create other content
  $permissions['create other content'] = array(
    'name' => 'create other content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: create page content
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: create session content
  $permissions['create session content'] = array(
    'name' => 'create session content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: create story content
  $permissions['create story content'] = array(
    'name' => 'create story content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: create unit content
  $permissions['create unit content'] = array(
    'name' => 'create unit content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any course content
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any information content
  $permissions['delete any information content'] = array(
    'name' => 'delete any information content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any instructor content
  $permissions['delete any instructor content'] = array(
    'name' => 'delete any instructor content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any material content
  $permissions['delete any material content'] = array(
    'name' => 'delete any material content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any other content
  $permissions['delete any other content'] = array(
    'name' => 'delete any other content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any page content
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete any session content
  $permissions['delete any session content'] = array(
    'name' => 'delete any session content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete any story content
  $permissions['delete any story content'] = array(
    'name' => 'delete any story content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete any unit content
  $permissions['delete any unit content'] = array(
    'name' => 'delete any unit content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: delete own course content
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: delete own information content
  $permissions['delete own information content'] = array(
    'name' => 'delete own information content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: delete own instructor content
  $permissions['delete own instructor content'] = array(
    'name' => 'delete own instructor content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete own material content
  $permissions['delete own material content'] = array(
    'name' => 'delete own material content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: delete own other content
  $permissions['delete own other content'] = array(
    'name' => 'delete own other content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: delete own page content
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete own session content
  $permissions['delete own session content'] = array(
    'name' => 'delete own session content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: delete own story content
  $permissions['delete own story content'] = array(
    'name' => 'delete own story content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete own unit content
  $permissions['delete own unit content'] = array(
    'name' => 'delete own unit content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: edit any course content
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any information content
  $permissions['edit any information content'] = array(
    'name' => 'edit any information content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any instructor content
  $permissions['edit any instructor content'] = array(
    'name' => 'edit any instructor content',
    'roles' => array(
      '0' => 'resource manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: edit any material content
  $permissions['edit any material content'] = array(
    'name' => 'edit any material content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any other content
  $permissions['edit any other content'] = array(
    'name' => 'edit any other content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any page content
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any session content
  $permissions['edit any session content'] = array(
    'name' => 'edit any session content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any story content
  $permissions['edit any story content'] = array(
    'name' => 'edit any story content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit any unit content
  $permissions['edit any unit content'] = array(
    'name' => 'edit any unit content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own course content
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own information content
  $permissions['edit own information content'] = array(
    'name' => 'edit own information content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own instructor content
  $permissions['edit own instructor content'] = array(
    'name' => 'edit own instructor content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own material content
  $permissions['edit own material content'] = array(
    'name' => 'edit own material content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own other content
  $permissions['edit own other content'] = array(
    'name' => 'edit own other content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own page content
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own session content
  $permissions['edit own session content'] = array(
    'name' => 'edit own session content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own story content
  $permissions['edit own story content'] = array(
    'name' => 'edit own story content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own unit content
  $permissions['edit own unit content'] = array(
    'name' => 'edit own unit content',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  return $permissions;
}
