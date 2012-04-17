<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function oerbit_acadamic_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'education_section';
  $context->description = 'Visible within the education path, including the /education landing page.';
  $context->tag = 'education';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'education' => 'education',
        'education/*' => 'education/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'course-course-feed' => array(
          'module' => 'course',
          'delta' => 'course-feed',
          'region' => 'content_top',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Visible within the education path, including the /education landing page.');
  t('education');
  $export['education_section'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'education_section_course';
  $context->description = 'Visible within the education path, but does not include the /education landing page.';
  $context->tag = 'education';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'education/*' => 'education/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-16' => array(
          'module' => 'block',
          'delta' => 16,
          'region' => 'course_nav',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Visible within the education path, but does not include the /education landing page.');
  t('education');
  $export['education_section_course'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'education_section_nonrecursive';
  $context->description = 'Visible on the education path but not on subpaths';
  $context->tag = 'education';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'education' => 'education',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-7' => array(
          'module' => 'block',
          'delta' => 7,
          'region' => 'content_bottom',
          'weight' => 0,
        ),
        'views-find-block_1' => array(
          'module' => 'views',
          'delta' => 'find-block_1',
          'region' => 'content_bottom',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Visible on the education path but not on subpaths');
  t('education');
  $export['education_section_nonrecursive'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'education_section_nonrecursive_roles';
  $context->description = 'Visible on the education path but not on subpaths, only to certain roles';
  $context->tag = 'education';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'education' => 'education',
      ),
    ),
    'user' => array(
      'values' => array(
        'site administrator' => 'site administrator',
        'unit manager' => 'unit manager',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Visible on the education path but not on subpaths, only to certain roles');
  t('education');
  $export['education_section_nonrecursive_roles'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'not_homepage';
  $context->description = 'All pages except the homepage';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
        '~/search*' => '~/search*',
        '~search/*' => '~search/*',
        '~search' => '~search',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'navigation-navigation' => array(
          'module' => 'navigation',
          'delta' => 'navigation',
          'region' => 'left',
          'weight' => 0,
        ),
        'block-12' => array(
          'module' => 'block',
          'delta' => 12,
          'region' => 'content_top',
          'weight' => 0,
        ),
        'print-0' => array(
          'module' => 'print',
          'delta' => 0,
          'region' => 'content_top',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('All pages except the homepage');
  t('homepage');
  $export['not_homepage'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'not_homepage_roles';
  $context->description = 'All pages except the homepage, only to content manager and site administrator roles';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'user' => array(
      'values' => array(
        'content manager' => 'content manager',
        'site administrator' => 'site administrator',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'revisioning-0' => array(
          'module' => 'revisioning',
          'delta' => 0,
          'region' => 'left',
          'weight' => 0,
        ),
        'block-15' => array(
          'module' => 'block',
          'delta' => 15,
          'region' => 'left',
          'weight' => 1,
        ),
        'hierarchical_permissions-hierarchical-permissions' => array(
          'module' => 'hierarchical_permissions',
          'delta' => 'hierarchical-permissions',
          'region' => 'left',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('All pages except the homepage, only to content manager and site administrator roles');
  t('homepage');
  $export['not_homepage_roles'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide_course';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'course-course-navigation' => array(
          'module' => 'course',
          'delta' => 'course-navigation',
          'region' => 'course_nav',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['sitewide_course'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide_course_version';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-course_versions-block_1' => array(
          'module' => 'views',
          'delta' => 'course_versions-block_1',
          'region' => 'left',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['sitewide_course_version'] = $context;

  return $export;
}
