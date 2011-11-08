<?php

/**
 * Implementation of hook_strongarm().
 */
function oerbit_search_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_cron_limit';
  $strongarm->value = '200';
  $export['apachesolr_cron_limit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_enabled_facets';
  $strongarm->value = array(
    'apachesolr_search' => array(),
    'apachesolr_facetbuilder' => array(),
    'oer_tweaks' => array(
      'oer_tweaks_cc' => 'sm_oer_cc',
      'oer_tweaks_creator' => 'sm_oer_creator',
      'oer_tweaks_instructor' => 'sm_oer_instructor',
      'oer_tweaks_main' => 'sm_oer_main',
    ),
  );
  $export['apachesolr_enabled_facets'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_failure';
  $strongarm->value = 'show_no_results';
  $export['apachesolr_failure'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_host';
  $strongarm->value = 'oer.switchbackcms.com';
  $export['apachesolr_host'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_last_optimize';
  $strongarm->value = 1316039642;
  $export['apachesolr_last_optimize'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_mlt_blocks';
  $strongarm->value = array(
    'mlt-001' => array(
      'name' => 'More like this',
      'num_results' => '5',
      'mlt_fl' => array(
        'title' => 'title',
        'taxonomy_names' => 'taxonomy_names',
      ),
      'mlt_mintf' => '1',
      'mlt_mindf' => '1',
      'mlt_minwl' => '3',
      'mlt_maxwl' => '15',
      'mlt_maxqt' => '20',
    ),
  );
  $export['apachesolr_mlt_blocks'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_path';
  $strongarm->value = '/solr';
  $export['apachesolr_path'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_port';
  $strongarm->value = '8983';
  $export['apachesolr_port'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_read_only';
  $strongarm->value = '0';
  $export['apachesolr_read_only'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_rows';
  $strongarm->value = '10';
  $export['apachesolr_rows'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_default_previous';
  $strongarm->value = '1';
  $export['apachesolr_search_default_previous'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_excluded_types';
  $strongarm->value = array(
    'accessibility_guideline' => 'accessibility_guideline',
    'accessibility_test' => 'accessibility_test',
    'information' => 'information',
    'unit' => 0,
    'course' => 0,
    'other' => 0,
    'instructor' => 0,
    'material' => 0,
    'page' => 0,
    'session' => 0,
    'story' => 0,
    'webform' => 0,
  );
  $export['apachesolr_search_excluded_types'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_make_default';
  $strongarm->value = '1';
  $export['apachesolr_search_make_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_query_fields';
  $strongarm->value = array(
    'body' => '1.0',
    'changed' => '0',
    'comment_count' => '0',
    'created' => '0',
    'entity' => '0',
    'hash' => '0',
    'id' => '0',
    'im_vid_4' => '0',
    'language' => '0',
    'last_comment_or_change' => '0',
    'moderate' => '0',
    'name' => '0',
    'nid' => '0',
    'nodeaccess_all' => '0',
    'nodeaccess_d491c34dd635_all' => '0',
    'path' => '0',
    'path_alias' => '0',
    'promote' => '0',
    'site' => '0',
    'sm_cck_field_course_level' => '0',
    'sm_vid_Keywords' => '0',
    'sname' => '0',
    'sort_name' => '0',
    'sort_ss_cck_field_content_type' => '0',
    'sort_ss_cck_field_course_download_display' => '0',
    'sort_ss_cck_field_course_featured' => '0',
    'sort_ss_cck_field_course_term' => '0',
    'sort_ss_cck_field_section_title' => '0',
    'sort_ss_cck_field_unit_type' => '0',
    'sort_title' => '0',
    'spell' => '0',
    'ss_cck_field_content_type' => '0',
    'ss_cck_field_course_download_display' => '0',
    'ss_cck_field_course_featured' => '0',
    'ss_cck_field_course_term' => '0',
    'ss_cck_field_section_title' => '0',
    'ss_cck_field_unit_type' => '0',
    'status' => '0',
    'sticky' => '0',
    'tags_a' => '0',
    'tags_h1' => '5.0',
    'tags_h2_h3' => '3.0',
    'tags_h4_h5_h6' => '2.0',
    'tags_inline' => '1.0',
    'taxonomy_names' => '2.0',
    'tid' => '0',
    'timestamp' => '0',
    'title' => '5.0',
    'tnid' => '0',
    'translate' => '0',
    'ts_vid_4_names' => '1.0',
    'type' => '0',
    'type_name' => '0',
    'uid' => '0',
    'url' => '0',
    'vid' => '0',
  );
  $export['apachesolr_search_query_fields'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_spellcheck';
  $strongarm->value = 1;
  $export['apachesolr_search_spellcheck'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_taxonomy_links';
  $strongarm->value = '1';
  $export['apachesolr_search_taxonomy_links'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_taxonomy_previous';
  $strongarm->value = '1';
  $export['apachesolr_search_taxonomy_previous'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_type_boosts';
  $strongarm->value = array(
    'unit' => '0',
    'accessibility_guideline' => '0',
    'accessibility_test' => '0',
    'course' => '0',
    'other' => '0',
    'instructor' => '0',
    'material' => '0',
    'information' => '0',
    'page' => '0',
    'session' => '0',
    'story' => '0',
    'webform' => '0',
  );
  $export['apachesolr_search_type_boosts'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_set_nodeapi_messages';
  $strongarm->value = '1';
  $export['apachesolr_set_nodeapi_messages'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_site_hash';
  $strongarm->value = 'qmlay5';
  $export['apachesolr_site_hash'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_box_default';
  $strongarm->value = '';
  $export['custom_search_box_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_box_image_path';
  $strongarm->value = 'sites/all/themes/oer/images/go.gif';
  $export['custom_search_box_image_path'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_box_label';
  $strongarm->value = 'search';
  $export['custom_search_box_label'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_box_submit_button';
  $strongarm->value = 'submit';
  $export['custom_search_box_submit_button'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_box_submit_text';
  $strongarm->value = 'Go';
  $export['custom_search_box_submit_text'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_image';
  $strongarm->value = '';
  $export['custom_search_image'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_order';
  $strongarm->value = array(
    'search_box' => array(
      'sort' => '-1',
    ),
    'content_types' => array(
      'sort' => '0',
    ),
    'criteria_or' => array(
      'sort' => '7',
    ),
    'criteria_phrase' => array(
      'sort' => '8',
    ),
    'criteria_negative' => array(
      'sort' => '9',
    ),
    'custom_paths' => array(
      'sort' => '9',
    ),
    'submit_button' => array(
      'sort' => '10',
    ),
  );
  $export['custom_search_order'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_cron_limit';
  $strongarm->value = '100';
  $export['search_cron_limit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_type_node_types';
  $strongarm->value = array(
    'course' => 'course',
    'instructor' => 'instructor',
    'unit' => 0,
    'accessibility_guideline' => 0,
    'accessibility_test' => 0,
    'book' => 0,
    'page' => 0,
    'resource' => 0,
    'story' => 0,
    'webform' => 0,
  );
  $export['search_type_node_types'] = $strongarm;

  return $export;
}
