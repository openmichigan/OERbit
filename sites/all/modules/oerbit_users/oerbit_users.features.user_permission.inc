<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_users_user_default_permissions() {
  $permissions = array();

  // Exported permission: Use PHP input for field settings (dangerous - grant with care)
  $permissions['Use PHP input for field settings (dangerous - grant with care)'] = array(
    'name' => 'Use PHP input for field settings (dangerous - grant with care)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: access All tab
  $permissions['access All tab'] = array(
    'name' => 'access All tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access I Can Edit tab
  $permissions['access I Can Edit tab'] = array(
    'name' => 'access I Can Edit tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access I Can View tab
  $permissions['access I Can View tab'] = array(
    'name' => 'access I Can View tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access I Created tab
  $permissions['access I Created tab'] = array(
    'name' => 'access I Created tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access I Last Modified tab
  $permissions['access I Last Modified tab'] = array(
    'name' => 'access I Last Modified tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access Published tab
  $permissions['access Published tab'] = array(
    'name' => 'access Published tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access Unpublished tab
  $permissions['access Unpublished tab'] = array(
    'name' => 'access Unpublished tab',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access administration menu
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access all views
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: access broken links report
  $permissions['access broken links report'] = array(
    'name' => 'access broken links report',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access ckeditor
  $permissions['access ckeditor'] = array(
    'name' => 'access ckeditor',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'content manager',
      '2' => 'resource manager',
      '3' => 'site administrator',
      '4' => 'unit manager',
    ),
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  // Exported permission: access news feeds
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  // Exported permission: access own broken links report
  $permissions['access own broken links report'] = array(
    'name' => 'access own broken links report',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access own webform submissions
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: access print
  $permissions['access print'] = array(
    'name' => 'access print',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  // Exported permission: access site reports
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: access site-wide contact form
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  // Exported permission: access statistics
  $permissions['access statistics'] = array(
    'name' => 'access statistics',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'content manager',
      '2' => 'resource manager',
      '3' => 'site administrator',
      '4' => 'unit manager',
    ),
  );

  // Exported permission: administer CAPTCHA settings
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer actions
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer blocks
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer ckeditor
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer features
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer files
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer filters
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer flash
  $permissions['administer flash'] = array(
    'name' => 'administer flash',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer google analytics
  $permissions['administer google analytics'] = array(
    'name' => 'administer google analytics',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer imageapi
  $permissions['administer imageapi'] = array(
    'name' => 'administer imageapi',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer imagecache
  $permissions['administer imagecache'] = array(
    'name' => 'administer imagecache',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer imce(execute PHP)
  $permissions['administer imce(execute PHP)'] = array(
    'name' => 'administer imce(execute PHP)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer linkchecker
  $permissions['administer linkchecker'] = array(
    'name' => 'administer linkchecker',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer menu
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer news feeds
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer pathauto
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer print
  $permissions['administer print'] = array(
    'name' => 'administer print',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer redirects
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer site configuration
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer site-wide contact form
  $permissions['administer site-wide contact form'] = array(
    'name' => 'administer site-wide contact form',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer string overrides
  $permissions['administer string overrides'] = array(
    'name' => 'administer string overrides',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer url aliases
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: assign node weight
  $permissions['assign node weight'] = array(
    'name' => 'assign node weight',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: bypass requirement that fields are unique
  $permissions['bypass requirement that fields are unique'] = array(
    'name' => 'bypass requirement that fields are unique',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: change own username
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: create url aliases
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: designate fields as unique
  $permissions['designate fields as unique'] = array(
    'name' => 'designate fields as unique',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: display drupal links
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit link settings
  $permissions['edit link settings'] = array(
    'name' => 'edit link settings',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit own webform submissions
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Ban IP address of current user (user_block_ip_action)
  $permissions['execute Ban IP address of current user (user_block_ip_action)'] = array(
    'name' => 'execute Ban IP address of current user (user_block_ip_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Block current user (user_block_user_action)
  $permissions['execute Block current user (user_block_user_action)'] = array(
    'name' => 'execute Block current user (user_block_user_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Block the selected users (user_user_operations_block)
  $permissions['execute Block the selected users (user_user_operations_block)'] = array(
    'name' => 'execute Block the selected users (user_user_operations_block)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Delete comment (views_bulk_operations_delete_comment_action)
  $permissions['execute Delete comment (views_bulk_operations_delete_comment_action)'] = array(
    'name' => 'execute Delete comment (views_bulk_operations_delete_comment_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Delete node (views_bulk_operations_delete_node_action)
  $permissions['execute Delete node (views_bulk_operations_delete_node_action)'] = array(
    'name' => 'execute Delete node (views_bulk_operations_delete_node_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: execute Delete term (views_bulk_operations_delete_term_action)
  $permissions['execute Delete term (views_bulk_operations_delete_term_action)'] = array(
    'name' => 'execute Delete term (views_bulk_operations_delete_term_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Delete user (views_bulk_operations_delete_user_action)
  $permissions['execute Delete user (views_bulk_operations_delete_user_action)'] = array(
    'name' => 'execute Delete user (views_bulk_operations_delete_user_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: execute Demote from front page (node_mass_update)
  $permissions['execute Demote from front page (node_mass_update)'] = array(
    'name' => 'execute Demote from front page (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Display a message to the user (system_message_action)
  $permissions['execute Display a message to the user (system_message_action)'] = array(
    'name' => 'execute Display a message to the user (system_message_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Execute a VBO programmatically (views_bulk_operations_action)
  $permissions['execute Execute a VBO programmatically (views_bulk_operations_action)'] = array(
    'name' => 'execute Execute a VBO programmatically (views_bulk_operations_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Execute arbitrary PHP script (views_bulk_operations_script_action)
  $permissions['execute Execute arbitrary PHP script (views_bulk_operations_script_action)'] = array(
    'name' => 'execute Execute arbitrary PHP script (views_bulk_operations_script_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Make post sticky (node_make_sticky_action)
  $permissions['execute Make post sticky (node_make_sticky_action)'] = array(
    'name' => 'execute Make post sticky (node_make_sticky_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Make post unsticky (node_make_unsticky_action)
  $permissions['execute Make post unsticky (node_make_unsticky_action)'] = array(
    'name' => 'execute Make post unsticky (node_make_unsticky_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Make sticky (node_mass_update)
  $permissions['execute Make sticky (node_mass_update)'] = array(
    'name' => 'execute Make sticky (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Modify node fields (views_bulk_operations_fields_action)
  $permissions['execute Modify node fields (views_bulk_operations_fields_action)'] = array(
    'name' => 'execute Modify node fields (views_bulk_operations_fields_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: execute Modify node taxonomy terms (views_bulk_operations_taxonomy_action)
  $permissions['execute Modify node taxonomy terms (views_bulk_operations_taxonomy_action)'] = array(
    'name' => 'execute Modify node taxonomy terms (views_bulk_operations_taxonomy_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: execute Modify profile fields (views_bulk_operations_profile_action)
  $permissions['execute Modify profile fields (views_bulk_operations_profile_action)'] = array(
    'name' => 'execute Modify profile fields (views_bulk_operations_profile_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Modify user roles (views_bulk_operations_user_roles_action)
  $permissions['execute Modify user roles (views_bulk_operations_user_roles_action)'] = array(
    'name' => 'execute Modify user roles (views_bulk_operations_user_roles_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: execute Pass objects as arguments to a page (views_bulk_operations_argument_selector_action)
  $permissions['execute Pass objects as arguments to a page (views_bulk_operations_argument_selector_action)'] = array(
    'name' => 'execute Pass objects as arguments to a page (views_bulk_operations_argument_selector_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Promote post to front page (node_promote_action)
  $permissions['execute Promote post to front page (node_promote_action)'] = array(
    'name' => 'execute Promote post to front page (node_promote_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Promote to front page (node_mass_update)
  $permissions['execute Promote to front page (node_mass_update)'] = array(
    'name' => 'execute Promote to front page (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Publish (node_mass_update)
  $permissions['execute Publish (node_mass_update)'] = array(
    'name' => 'execute Publish (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Publish post (node_publish_action)
  $permissions['execute Publish post (node_publish_action)'] = array(
    'name' => 'execute Publish post (node_publish_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Publish the most recent pending revision (revisioning_publish_latest_revision_action)
  $permissions['execute Publish the most recent pending revision (revisioning_publish_latest_revision_action)'] = array(
    'name' => 'execute Publish the most recent pending revision (revisioning_publish_latest_revision_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Redirect to URL (system_goto_action)
  $permissions['execute Redirect to URL (system_goto_action)'] = array(
    'name' => 'execute Redirect to URL (system_goto_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Remove post from front page (node_unpromote_action)
  $permissions['execute Remove post from front page (node_unpromote_action)'] = array(
    'name' => 'execute Remove post from front page (node_unpromote_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Remove stickiness (node_mass_update)
  $permissions['execute Remove stickiness (node_mass_update)'] = array(
    'name' => 'execute Remove stickiness (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Save post (node_save_action)
  $permissions['execute Save post (node_save_action)'] = array(
    'name' => 'execute Save post (node_save_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Send e-mail (system_send_email_action)
  $permissions['execute Send e-mail (system_send_email_action)'] = array(
    'name' => 'execute Send e-mail (system_send_email_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Unblock the selected users (user_user_operations_unblock)
  $permissions['execute Unblock the selected users (user_user_operations_unblock)'] = array(
    'name' => 'execute Unblock the selected users (user_user_operations_unblock)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Unpublish (node_mass_update)
  $permissions['execute Unpublish (node_mass_update)'] = array(
    'name' => 'execute Unpublish (node_mass_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Unpublish post (node_unpublish_action)
  $permissions['execute Unpublish post (node_unpublish_action)'] = array(
    'name' => 'execute Unpublish post (node_unpublish_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Unpublish post containing keyword(s) (node_unpublish_by_keyword_action)
  $permissions['execute Unpublish post containing keyword(s) (node_unpublish_by_keyword_action)'] = array(
    'name' => 'execute Unpublish post containing keyword(s) (node_unpublish_by_keyword_action)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Update URL alias (pathauto_node_update_alias_multiple)
  $permissions['execute Update URL alias (pathauto_node_update_alias_multiple)'] = array(
    'name' => 'execute Update URL alias (pathauto_node_update_alias_multiple)',
    'roles' => array(),
  );

  // Exported permission: execute Update URL alias (pathauto_user_update_alias_multiple)
  $permissions['execute Update URL alias (pathauto_user_update_alias_multiple)'] = array(
    'name' => 'execute Update URL alias (pathauto_user_update_alias_multiple)',
    'roles' => array(),
  );

  // Exported permission: execute Update automatic nodetitles (auto_nodetitle_operations_update)
  $permissions['execute Update automatic nodetitles (auto_nodetitle_operations_update)'] = array(
    'name' => 'execute Update automatic nodetitles (auto_nodetitle_operations_update)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: flush imagecache
  $permissions['flush imagecache'] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: manage features
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: node-specific print configuration
  $permissions['node-specific print configuration'] = array(
    'name' => 'node-specific print configuration',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: notify of path changes
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: opt-in or out of tracking
  $permissions['opt-in or out of tracking'] = array(
    'name' => 'opt-in or out of tracking',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: revert revisions
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: select different theme
  $permissions['select different theme'] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: skip CAPTCHA
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(),
  );

  // Exported permission: upload files
  $permissions['upload files'] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: use PHP for block visibility
  $permissions['use PHP for block visibility'] = array(
    'name' => 'use PHP for block visibility',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: use PHP for link visibility
  $permissions['use PHP for link visibility'] = array(
    'name' => 'use PHP for link visibility',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: use PHP for title patterns
  $permissions['use PHP for title patterns'] = array(
    'name' => 'use PHP for title patterns',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: use PHP for tracking visibility
  $permissions['use PHP for tracking visibility'] = array(
    'name' => 'use PHP for tracking visibility',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: use views exporter
  $permissions['use views exporter'] = array(
    'name' => 'use views exporter',
    'roles' => array(),
  );

  // Exported permission: view advanced help index
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(),
  );

  // Exported permission: view advanced help popup
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(),
  );

  // Exported permission: view advanced help topic
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(),
  );

  // Exported permission: view date repeats
  $permissions['view date repeats'] = array(
    'name' => 'view date repeats',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: view imagecache Preview
  $permissions['view imagecache Preview'] = array(
    'name' => 'view imagecache Preview',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view imagecache Thumbnail
  $permissions['view imagecache Thumbnail'] = array(
    'name' => 'view imagecache Thumbnail',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view imagecache width200
  $permissions['view imagecache width200'] = array(
    'name' => 'view imagecache width200',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view imagecache width300
  $permissions['view imagecache width300'] = array(
    'name' => 'view imagecache width300',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: view post access counter
  $permissions['view post access counter'] = array(
    'name' => 'view post access counter',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: view uploaded files
  $permissions['view uploaded files'] = array(
    'name' => 'view uploaded files',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'content manager',
      '3' => 'resource manager',
      '4' => 'site administrator',
      '5' => 'unit manager',
    ),
  );

  return $permissions;
}
