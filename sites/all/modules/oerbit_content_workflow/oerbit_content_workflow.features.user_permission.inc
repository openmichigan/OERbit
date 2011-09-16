<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_content_workflow_user_default_permissions() {
  $permissions = array();

  // Exported permission: access Pending tab
  $permissions['access Pending tab'] = array(
    'name' => 'access Pending tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access workflow summary views
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer rules
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer workflow
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit revisions
  $permissions['edit revisions'] = array(
    'name' => 'edit revisions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: execute Change the author of a post (node_assign_owner_action)
  $permissions['execute Change the author of a post (node_assign_owner_action)'] = array(
    'name' => 'execute Change the author of a post (node_assign_owner_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Change workflow state of post to new state (workflow_select_given_state_action)
  $permissions['execute Change workflow state of post to new state (workflow_select_given_state_action)'] = array(
    'name' => 'execute Change workflow state of post to new state (workflow_select_given_state_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: execute Change workflow state of post to next state (workflow_select_next_state_action)
  $permissions['execute Change workflow state of post to next state (workflow_select_next_state_action)'] = array(
    'name' => 'execute Change workflow state of post to next state (workflow_select_next_state_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: publish revisions
  $permissions['publish revisions'] = array(
    'name' => 'publish revisions',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: schedule workflow transitions
  $permissions['schedule workflow transitions'] = array(
    'name' => 'schedule workflow transitions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: unpublish current revision
  $permissions['unpublish current revision'] = array(
    'name' => 'unpublish current revision',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: view revision status messages
  $permissions['view revision status messages'] = array(
    'name' => 'view revision status messages',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any accessibility_guideline content
  $permissions['view revisions of any accessibility_guideline content'] = array(
    'name' => 'view revisions of any accessibility_guideline content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any accessibility_test content
  $permissions['view revisions of any accessibility_test content'] = array(
    'name' => 'view revisions of any accessibility_test content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any course content
  $permissions['view revisions of any course content'] = array(
    'name' => 'view revisions of any course content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any information content
  $permissions['view revisions of any information content'] = array(
    'name' => 'view revisions of any information content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any instructor content
  $permissions['view revisions of any instructor content'] = array(
    'name' => 'view revisions of any instructor content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any material content
  $permissions['view revisions of any material content'] = array(
    'name' => 'view revisions of any material content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any other content
  $permissions['view revisions of any other content'] = array(
    'name' => 'view revisions of any other content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any page content
  $permissions['view revisions of any page content'] = array(
    'name' => 'view revisions of any page content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any session content
  $permissions['view revisions of any session content'] = array(
    'name' => 'view revisions of any session content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any story content
  $permissions['view revisions of any story content'] = array(
    'name' => 'view revisions of any story content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any unit content
  $permissions['view revisions of any unit content'] = array(
    'name' => 'view revisions of any unit content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of any webform content
  $permissions['view revisions of any webform content'] = array(
    'name' => 'view revisions of any webform content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of own accessibility_guideline content
  $permissions['view revisions of own accessibility_guideline content'] = array(
    'name' => 'view revisions of own accessibility_guideline content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of own accessibility_test content
  $permissions['view revisions of own accessibility_test content'] = array(
    'name' => 'view revisions of own accessibility_test content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of own course content
  $permissions['view revisions of own course content'] = array(
    'name' => 'view revisions of own course content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own information content
  $permissions['view revisions of own information content'] = array(
    'name' => 'view revisions of own information content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own instructor content
  $permissions['view revisions of own instructor content'] = array(
    'name' => 'view revisions of own instructor content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own material content
  $permissions['view revisions of own material content'] = array(
    'name' => 'view revisions of own material content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own other content
  $permissions['view revisions of own other content'] = array(
    'name' => 'view revisions of own other content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own page content
  $permissions['view revisions of own page content'] = array(
    'name' => 'view revisions of own page content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of own session content
  $permissions['view revisions of own session content'] = array(
    'name' => 'view revisions of own session content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own story content
  $permissions['view revisions of own story content'] = array(
    'name' => 'view revisions of own story content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view revisions of own unit content
  $permissions['view revisions of own unit content'] = array(
    'name' => 'view revisions of own unit content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
      '2' => 'unit manager',
    ),
  );

  // Exported permission: view revisions of own webform content
  $permissions['view revisions of own webform content'] = array(
    'name' => 'view revisions of own webform content',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  return $permissions;
}
