<?php

/**
 * Implementation of hook_strongarm().
 */
function oerbit_accessibility_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_book';
  $strongarm->value = 0;
  $export['ac_after_filter_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_course';
  $strongarm->value = 1;
  $export['ac_after_filter_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_information';
  $strongarm->value = 1;
  $export['ac_after_filter_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_instructor';
  $strongarm->value = 1;
  $export['ac_after_filter_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_material';
  $strongarm->value = 1;
  $export['ac_after_filter_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_other';
  $strongarm->value = 1;
  $export['ac_after_filter_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_page';
  $strongarm->value = 1;
  $export['ac_after_filter_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_resource';
  $strongarm->value = 1;
  $export['ac_after_filter_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_session';
  $strongarm->value = 1;
  $export['ac_after_filter_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_story';
  $strongarm->value = 1;
  $export['ac_after_filter_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_unit';
  $strongarm->value = 1;
  $export['ac_after_filter_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_after_filter_webform';
  $strongarm->value = 0;
  $export['ac_after_filter_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_book';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_course';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_information';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_instructor';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_material';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_other';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_page';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_resource';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_session';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_story';
  $strongarm->value = array(
    0 => 1,
    1 => 2,
    2 => 3,
  );
  $export['ac_display_level_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_unit';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_display_level_webform';
  $strongarm->value = array(
    0 => 1,
  );
  $export['ac_display_level_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_book';
  $strongarm->value = 0;
  $export['ac_enabled_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_course';
  $strongarm->value = 1;
  $export['ac_enabled_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_information';
  $strongarm->value = 1;
  $export['ac_enabled_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_instructor';
  $strongarm->value = 1;
  $export['ac_enabled_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_material';
  $strongarm->value = 1;
  $export['ac_enabled_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_other';
  $strongarm->value = 1;
  $export['ac_enabled_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_page';
  $strongarm->value = 1;
  $export['ac_enabled_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_resource';
  $strongarm->value = 1;
  $export['ac_enabled_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_session';
  $strongarm->value = 1;
  $export['ac_enabled_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_story';
  $strongarm->value = 1;
  $export['ac_enabled_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_unit';
  $strongarm->value = 1;
  $export['ac_enabled_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_enabled_webform';
  $strongarm->value = 0;
  $export['ac_enabled_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_error_display';
  $strongarm->value = 1;
  $export['ac_error_display'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_book';
  $strongarm->value = 0;
  $export['ac_fail_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_course';
  $strongarm->value = 0;
  $export['ac_fail_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_information';
  $strongarm->value = 0;
  $export['ac_fail_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_instructor';
  $strongarm->value = 0;
  $export['ac_fail_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_material';
  $strongarm->value = 0;
  $export['ac_fail_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_other';
  $strongarm->value = 0;
  $export['ac_fail_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_page';
  $strongarm->value = 0;
  $export['ac_fail_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_resource';
  $strongarm->value = 0;
  $export['ac_fail_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_session';
  $strongarm->value = 0;
  $export['ac_fail_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_story';
  $strongarm->value = 0;
  $export['ac_fail_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_unit';
  $strongarm->value = 0;
  $export['ac_fail_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_fail_webform';
  $strongarm->value = 0;
  $export['ac_fail_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_field';
  $strongarm->value = array(
    'field_course_academic_unit' => 0,
    'field_unit_courses' => 0,
    'field_unit_parent_unit' => 0,
    'field_unit_sub_unit' => 0,
    'field_unit_image' => 1,
    'field_course_image' => 1,
    'field_instructor_image' => 1,
    'field_course_instructor' => 0,
    'field_instructor_courses' => 0,
    'field_instructor_academic_unit' => 0,
    'field_unit_instructors' => 0,
    'field_resource_instructor' => 0,
    'field_instructor_resources' => 0,
    'field_resource_file' => 0,
    'field_resource_course' => 0,
    'field_course_resources' => 0,
    'field_resource_image' => 0,
    'field_course_term' => 0,
    'field_course_year' => 0,
    'field_resource_section_title' => 0,
    'field_course_id' => 0,
    'field_course_title' => 0,
    'field_unit_type' => 1,
    'field_page_image' => 0,
    'field_page_image_caption' => 0,
    'field_course_reference' => 0,
    'field_file' => 1,
    'field_section_title' => 0,
    'field_course_information' => 0,
    'field_block' => 0,
    'field_unit_top' => 0,
    'field_academic_unit' => 0,
    'field_title' => 0,
    'field_code' => 0,
    'field_course_structure' => 0,
    'field_course_level' => 0,
    'field_material_type' => 0,
    'field_session_sequence' => 0,
    'field_course_sessions' => 0,
    'field_course_material' => 0,
    'field_video' => 0,
    'field_course_image_caption' => 1,
    'field_unit_image_caption' => 1,
    'field_unit_website' => 0,
    'field_course_materials' => 0,
    'field_website' => 1,
    'field_parent_unit' => 0,
    'field_course_download_display' => 0,
    'field_course_featured' => 0,
    'field_material_author' => 1,
    'field_link' => 1,
    'field_content_reference' => 0,
    'field_image' => 1,
    'field_course_highlights' => 0,
    'field_contributors' => 1,
    'field_creators' => 1,
    'field_resource_type' => 0,
    'field_email_address' => 0,
    'field_email' => 0,
    'field_instructor_unit' => 0,
    'field_publisher' => 0,
    'field_content_type' => 0,
    'field_course_code' => 0,
    'field_audio' => 0,
    'field_image_3' => 0,
    'field_image_caption' => 1,
  );
  $export['ac_field'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_book';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_course';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_information';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_instructor';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_material';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_other';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_page';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_resource';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_session';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_story';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_unit';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ignore_cms_off_webform';
  $strongarm->value = 1;
  $export['ac_ignore_cms_off_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_test_plugin_files';
  $strongarm->value = array();
  $export['ac_test_plugin_files'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_themer_sitewide_guideline';
  $strongarm->value = '213';
  $export['ac_themer_sitewide_guideline'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_class_moderate';
  $strongarm->value = 'accessibility-error-moderate';
  $export['ac_ui_class_moderate'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_class_severe';
  $strongarm->value = 'accessibility-error-severe';
  $export['ac_ui_class_severe'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_class_suggestion';
  $strongarm->value = 'accessibility-error-suggestion';
  $export['ac_ui_class_suggestion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_icon_moderate';
  $strongarm->value = 'sites/all/modules/accessible_content/images/test-demo-moderate.png';
  $export['ac_ui_icon_moderate'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_icon_severe';
  $strongarm->value = 'sites/all/modules/accessible_content/images/test-demo-severe.png';
  $export['ac_ui_icon_severe'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ac_ui_icon_suggestion';
  $strongarm->value = 'sites/all/modules/accessible_content/images/test-demo-suggestion.png';
  $export['ac_ui_icon_suggestion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_book';
  $strongarm->value = '213';
  $export['accessibility_guideline_book'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_course';
  $strongarm->value = '213';
  $export['accessibility_guideline_course'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_information';
  $strongarm->value = '213';
  $export['accessibility_guideline_information'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_instructor';
  $strongarm->value = '213';
  $export['accessibility_guideline_instructor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_material';
  $strongarm->value = '213';
  $export['accessibility_guideline_material'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_other';
  $strongarm->value = '213';
  $export['accessibility_guideline_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_page';
  $strongarm->value = '213';
  $export['accessibility_guideline_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_resource';
  $strongarm->value = '213';
  $export['accessibility_guideline_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_session';
  $strongarm->value = '213';
  $export['accessibility_guideline_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_story';
  $strongarm->value = '213';
  $export['accessibility_guideline_story'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_unit';
  $strongarm->value = '213';
  $export['accessibility_guideline_unit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_guideline_webform';
  $strongarm->value = '213';
  $export['accessibility_guideline_webform'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_ac_after_filter';
  $strongarm->value = 1;
  $export['course_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 0,
    3 => 0,
  );
  $export['course_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_ac_enable';
  $strongarm->value = 1;
  $export['course_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_ac_fail';
  $strongarm->value = 0;
  $export['course_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['course_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'course_accessibility_guideline_nid';
  $strongarm->value = '213';
  $export['course_accessibility_guideline_nid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_ac_after_filter';
  $strongarm->value = 1;
  $export['information_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 0,
    3 => 0,
  );
  $export['information_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_ac_enable';
  $strongarm->value = 1;
  $export['information_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_ac_fail';
  $strongarm->value = 0;
  $export['information_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['information_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'information_accessibility_guideline_nid';
  $strongarm->value = '213';
  $export['information_accessibility_guideline_nid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_ac_after_filter';
  $strongarm->value = 1;
  $export['material_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 0,
    3 => 0,
  );
  $export['material_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_ac_enable';
  $strongarm->value = 1;
  $export['material_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_ac_fail';
  $strongarm->value = 0;
  $export['material_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['material_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'material_accessibility_guideline_nid';
  $strongarm->value = '213';
  $export['material_accessibility_guideline_nid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_ac_after_filter';
  $strongarm->value = 1;
  $export['page_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 0,
    3 => 0,
  );
  $export['page_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_ac_enable';
  $strongarm->value = 1;
  $export['page_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_ac_fail';
  $strongarm->value = 0;
  $export['page_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['page_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_accessibility_guideline_nid';
  $strongarm->value = '213';
  $export['page_accessibility_guideline_nid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'story_ac_after_filter';
  $strongarm->value = 1;
  $export['story_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'story_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 2,
    3 => 3,
  );
  $export['story_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'story_ac_enable';
  $strongarm->value = 1;
  $export['story_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'story_ac_fail';
  $strongarm->value = 0;
  $export['story_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'story_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['story_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_ac_after_filter';
  $strongarm->value = 1;
  $export['unit_ac_after_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_ac_display_level';
  $strongarm->value = array(
    1 => 1,
    2 => 0,
    3 => 0,
  );
  $export['unit_ac_display_level'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_ac_enable';
  $strongarm->value = 1;
  $export['unit_ac_enable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_ac_fail';
  $strongarm->value = 0;
  $export['unit_ac_fail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_ac_ignore_cms_off';
  $strongarm->value = 1;
  $export['unit_ac_ignore_cms_off'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unit_accessibility_guideline_nid';
  $strongarm->value = '213';
  $export['unit_accessibility_guideline_nid'] = $strongarm;

  return $export;
}
