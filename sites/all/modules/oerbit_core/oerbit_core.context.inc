<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function oerbit_core_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'homepage';
  $context->description = 'The front page of the site';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-5' => array(
          'module' => 'block',
          'delta' => 5,
          'region' => 'right',
          'weight' => 0,
        ),
        'views-open_blog-block_1' => array(
          'module' => 'views',
          'delta' => 'open_blog-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The front page of the site');
  $export['homepage'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide';
  $context->description = 'This context is always active';
  $context->tag = '';
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
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => 1,
          'region' => 'left',
          'weight' => 0,
        ),
        'menu_block-4' => array(
          'module' => 'menu_block',
          'delta' => 4,
          'region' => 'left',
          'weight' => 1,
        ),
        'block-4' => array(
          'module' => 'block',
          'delta' => 4,
          'region' => 'header',
          'weight' => 0,
        ),
        'menu_block-2' => array(
          'module' => 'menu_block',
          'delta' => 2,
          'region' => 'header',
          'weight' => 1,
        ),
        'search-0' => array(
          'module' => 'search',
          'delta' => 0,
          'region' => 'header',
          'weight' => 2,
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => 1,
          'region' => 'footer',
          'weight' => 0,
        ),
        'block-9' => array(
          'module' => 'block',
          'delta' => 9,
          'region' => 'footer',
          'weight' => 1,
        ),
        'block-2' => array(
          'module' => 'block',
          'delta' => 2,
          'region' => 'footer',
          'weight' => 2,
        ),
        'menu-menu-footerlinks' => array(
          'module' => 'menu',
          'delta' => 'menu-footerlinks',
          'region' => 'footer',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('This context is always active');
  $export['sitewide'] = $context;

  return $export;
}
