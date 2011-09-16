<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function oerbit_metadata_user_default_permissions() {
  $permissions = array();

  // Exported permission: access RDF data
  $permissions['access RDF data'] = array(
    'name' => 'access RDF data',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: administer RDF data
  $permissions['administer RDF data'] = array(
    'name' => 'administer RDF data',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer RDF repositories
  $permissions['administer RDF repositories'] = array(
    'name' => 'administer RDF repositories',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer creative commons
  $permissions['administer creative commons'] = array(
    'name' => 'administer creative commons',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: administer meta tags
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: attach creative commons
  $permissions['attach creative commons'] = array(
    'name' => 'attach creative commons',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: edit Bing Webmaster Center verification meta tag
  $permissions['edit Bing Webmaster Center verification meta tag'] = array(
    'name' => 'edit Bing Webmaster Center verification meta tag',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit Google Webmaster Tools verification meta tag
  $permissions['edit Google Webmaster Tools verification meta tag'] = array(
    'name' => 'edit Google Webmaster Tools verification meta tag',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit Yahoo! Site Explorer verification meta tag
  $permissions['edit Yahoo! Site Explorer verification meta tag'] = array(
    'name' => 'edit Yahoo! Site Explorer verification meta tag',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit canonical URL meta tag
  $permissions['edit canonical URL meta tag'] = array(
    'name' => 'edit canonical URL meta tag',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit location meta tags
  $permissions['edit location meta tags'] = array(
    'name' => 'edit location meta tags',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag ABSTRACT
  $permissions['edit meta tag ABSTRACT'] = array(
    'name' => 'edit meta tag ABSTRACT',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag COPYRIGHT
  $permissions['edit meta tag COPYRIGHT'] = array(
    'name' => 'edit meta tag COPYRIGHT',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag DESCRIPTION
  $permissions['edit meta tag DESCRIPTION'] = array(
    'name' => 'edit meta tag DESCRIPTION',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core CONTRIBUTOR
  $permissions['edit meta tag Dublin Core CONTRIBUTOR'] = array(
    'name' => 'edit meta tag Dublin Core CONTRIBUTOR',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core CREATOR
  $permissions['edit meta tag Dublin Core CREATOR'] = array(
    'name' => 'edit meta tag Dublin Core CREATOR',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core DATE
  $permissions['edit meta tag Dublin Core DATE'] = array(
    'name' => 'edit meta tag Dublin Core DATE',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core DESCRIPTION
  $permissions['edit meta tag Dublin Core DESCRIPTION'] = array(
    'name' => 'edit meta tag Dublin Core DESCRIPTION',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core PUBLISHER
  $permissions['edit meta tag Dublin Core PUBLISHER'] = array(
    'name' => 'edit meta tag Dublin Core PUBLISHER',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag Dublin Core TITLE
  $permissions['edit meta tag Dublin Core TITLE'] = array(
    'name' => 'edit meta tag Dublin Core TITLE',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag KEYWORDS
  $permissions['edit meta tag KEYWORDS'] = array(
    'name' => 'edit meta tag KEYWORDS',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag PICS-LABEL
  $permissions['edit meta tag PICS-LABEL'] = array(
    'name' => 'edit meta tag PICS-LABEL',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag REVISIT-AFTER
  $permissions['edit meta tag REVISIT-AFTER'] = array(
    'name' => 'edit meta tag REVISIT-AFTER',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: edit meta tag ROBOTS
  $permissions['edit meta tag ROBOTS'] = array(
    'name' => 'edit meta tag ROBOTS',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Delete meta tags (nodewords_mass_delete_tags)
  $permissions['execute Delete meta tags (nodewords_mass_delete_tags)'] = array(
    'name' => 'execute Delete meta tags (nodewords_mass_delete_tags)',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: execute Set Creative Commons license (creativecommons_set_license_action)
  $permissions['execute Set Creative Commons license (creativecommons_set_license_action)'] = array(
    'name' => 'execute Set Creative Commons license (creativecommons_set_license_action)',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  // Exported permission: export RDF data
  $permissions['export RDF data'] = array(
    'name' => 'export RDF data',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: export enabled modules
  $permissions['export enabled modules'] = array(
    'name' => 'export enabled modules',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: export site settings
  $permissions['export site settings'] = array(
    'name' => 'export site settings',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'site administrator',
    ),
  );

  // Exported permission: import RDF data
  $permissions['import RDF data'] = array(
    'name' => 'import RDF data',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: import enabled modules
  $permissions['import enabled modules'] = array(
    'name' => 'import enabled modules',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: import site settings
  $permissions['import site settings'] = array(
    'name' => 'import site settings',
    'roles' => array(
      '0' => 'site administrator',
    ),
  );

  // Exported permission: use creative commons user defaults
  $permissions['use creative commons user defaults'] = array(
    'name' => 'use creative commons user defaults',
    'roles' => array(
      '0' => 'content manager',
      '1' => 'resource manager',
      '2' => 'site administrator',
      '3' => 'unit manager',
    ),
  );

  return $permissions;
}
