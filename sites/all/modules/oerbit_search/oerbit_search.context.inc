<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function oerbit_search_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'search_facets';
  $context->description = '';
  $context->tag = 'search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'search*' => 'search*',
        'search/*' => 'search/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'oer_tweaks-0' => array(
          'module' => 'oer_tweaks',
          'delta' => 0,
          'region' => 'left',
          'weight' => 0,
        ),
        'oer_tweaks-1' => array(
          'module' => 'oer_tweaks',
          'delta' => 1,
          'region' => 'left',
          'weight' => 1,
        ),
        'oer_tweaks-2' => array(
          'module' => 'oer_tweaks',
          'delta' => 2,
          'region' => 'left',
          'weight' => 2,
        ),
        'oer_tweaks-3' => array(
          'module' => 'oer_tweaks',
          'delta' => 3,
          'region' => 'left',
          'weight' => 3,
        ),
        'apachesolr-sort' => array(
          'module' => 'apachesolr',
          'delta' => 'sort',
          'region' => 'left',
          'weight' => 4,
        ),
        'oer_tweaks-4' => array(
          'module' => 'oer_tweaks',
          'delta' => 4,
          'region' => 'left',
          'weight' => 5,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('search');
  $export['search_facets'] = $context;

  return $export;
}
