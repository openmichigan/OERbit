<?php

/**
 * Implementation of hook_content_default_fields().
 */
function oerbit_acadamic_content_default_fields() {
  $fields = array();

  // Exported field: field_code
  $fields['course-field_code'] = array(
    'field_name' => 'field_code',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-97',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_code][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'URL',
      'weight' => '-97',
      'description' => 'This is the url that will be used for this page.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_content_type
  $fields['course-field_content_type'] = array(
    'field_name' => 'field_content_type',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-100',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'course|Course
resource|Resource',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Content Type',
      'weight' => '-100',
      'description' => 'Select whether this is a course or a resource.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_contributors
  $fields['course-field_contributors'] = array(
    'field_name' => 'field_contributors',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-75',
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_contributors][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contributors',
      'weight' => '-75',
      'description' => 'The names of people that have contributed to this item.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_code
  $fields['course-field_course_code'] = array(
    'field_name' => 'field_course_code',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-98',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_course_code][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Short Title/Course Code',
      'weight' => '-98',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_download_display
  $fields['course-field_course_download_display'] = array(
    'field_name' => 'field_course_download_display',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '29',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Yes|Yes
No|No',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Yes',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Download Button Display',
      'weight' => '29',
      'description' => 'Show the "Download all related materials" button. ',
      'type' => 'optionwidgets_buttons',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_course_featured
  $fields['course-field_course_featured'] = array(
    'field_name' => 'field_course_featured',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '30',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Yes|Yes
No|No',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'No',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Feature on Main page',
      'weight' => '30',
      'description' => 'Feature this content on the main "Find" page.',
      'type' => 'optionwidgets_buttons',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_course_highlights
  $fields['course-field_course_highlights'] = array(
    'field_name' => 'field_course_highlights',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-83',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'other' => 'other',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'information' => 0,
      'material' => 0,
      'session' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_course_reference' => 'field_course_reference',
      'field_parent_unit' => 0,
      'field_course_instructor' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Highlights',
      'weight' => '-81',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_course_image
  $fields['course-field_course_image'] = array(
    'field_name' => 'field_course_image',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-95',
      'parent' => 'group_course_image',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'Thumbnail_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'width300_default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'course_default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '[site-name]',
      'custom_alt' => 1,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => array(
        'filename' => 'default.png',
        'filepath' => 'sites/oer.switchbackcms.com/files/imagefield_default_images/default.png',
        'filemime' => 'image/png',
        'source' => 'default_image_upload',
        'destination' => 'sites/oer.switchbackcms.com/files/imagefield_default_images/default.png',
        'filesize' => 817,
        'uid' => '1',
        'status' => 1,
        'timestamp' => 1267118471,
        'fid' => '9',
      ),
      'use_default_image' => 1,
      'label' => 'Image',
      'weight' => '-95',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_course_image_caption
  $fields['course-field_course_image_caption'] = array(
    'field_name' => 'field_course_image_caption',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-94',
      'parent' => 'group_course_image',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '2',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          'format' => '1',
          '_error_element' => 'default_value_widget][field_course_image_caption][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Image Caption',
      'weight' => '-94',
      'description' => 'Provide license information for the image.',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_information
  $fields['course-field_course_information'] = array(
    'field_name' => 'field_course_information',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-84',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'information' => 'information',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'material' => 0,
      'other' => 0,
      'session' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_course_reference' => 'field_course_reference',
      'field_parent_unit' => 0,
      'field_course_instructor' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Overview - Sliders',
      'weight' => '-82',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_course_instructor
  $fields['course-field_course_instructor'] = array(
    'field_name' => 'field_course_instructor',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '28',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'instructor' => 'instructor',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_course_instructor][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'redirect_after_create' => 1,
      'label' => 'Course Instructor',
      'weight' => '28',
      'description' => 'Start typing in the name of the instructor above. If it doesn\'t exist, it will be created.',
      'type' => 'noderefcreate_autocomplete',
      'module' => 'noderefcreate',
    ),
  );

  // Exported field: field_course_level
  $fields['course-field_course_level'] = array(
    'field_name' => 'field_course_level',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '24',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'undergraduate|Undergraduate
graduate|Graduate
non-credit|Non Credit',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Education Level',
      'weight' => '24',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_course_materials
  $fields['course-field_course_materials'] = array(
    'field_name' => 'field_course_materials',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-82',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'material' => 'material',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'information' => 0,
      'other' => 0,
      'session' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_course_reference' => 'field_course_reference',
      'field_parent_unit' => 0,
      'field_course_instructor' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Material',
      'weight' => '-80',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_course_sessions
  $fields['course-field_course_sessions'] = array(
    'field_name' => 'field_course_sessions',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-81',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'session' => 'session',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'information' => 0,
      'material' => 0,
      'other' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_course_reference' => 'field_course_reference',
      'field_parent_unit' => 0,
      'field_course_instructor' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Session',
      'weight' => '-79',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_course_structure
  $fields['course-field_course_structure'] = array(
    'field_name' => 'field_course_structure',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '25',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_course_structure][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Structure',
      'weight' => '25',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_term
  $fields['course-field_course_term'] = array(
    'field_name' => 'field_course_term',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '26',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Fall
Winter
Spring
Summer',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Academic Term',
      'weight' => '26',
      'description' => 'The term the course was taught in.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_course_year
  $fields['course-field_course_year'] = array(
    'field_name' => 'field_course_year',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '27',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '0',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => 'optional',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'short',
    'widget' => array(
      'default_value' => 'now',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'Y-m-d H:i:s',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-3:+3',
      'label_position' => 'none',
      'label' => 'Academic Year',
      'weight' => '27',
      'description' => 'The year the course was taught in.',
      'type' => 'date_select',
      'module' => 'date',
    ),
  );

  // Exported field: field_creators
  $fields['course-field_creators'] = array(
    'field_name' => 'field_creators',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-76',
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_creators][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Creators',
      'weight' => '-76',
      'description' => 'Persons responsible for creating the content of this item. The principal creator should come first.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_parent_unit
  $fields['course-field_parent_unit'] = array(
    'field_name' => 'field_parent_unit',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '23',
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'unit' => 'unit',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_parent_unit][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Academic Unit',
      'weight' => '23',
      'description' => 'Select the parent <em>academic unit</em>.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_publisher
  $fields['course-field_publisher'] = array(
    'field_name' => 'field_publisher',
    'type_name' => 'course',
    'display_settings' => array(
      'weight' => '-74',
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'Open.Michigan, University of Michigan',
          '_error_element' => 'default_value_widget][field_publisher][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Publisher',
      'weight' => '-74',
      'description' => 'Entity that published the resource.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_content_reference
  $fields['information-field_content_reference'] = array(
    'field_name' => 'field_content_reference',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_material_reference',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'material' => 'material',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Materials Reference',
      'weight' => '-1',
      'description' => 'Check the materials you would like to display with this content. If there are no materials above, you will first need to add materials to this course/resource.',
      'type' => 'nodereference_buttons',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_contributors
  $fields['information-field_contributors'] = array(
    'field_name' => 'field_contributors',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '8',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_contributors][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contributors',
      'weight' => '8',
      'description' => 'The names of people that have contributed to this item.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_reference
  $fields['information-field_course_reference'] = array(
    'field_name' => 'field_course_reference',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_course_information',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_course_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Course',
      'weight' => '-1',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_creators
  $fields['information-field_creators'] = array(
    'field_name' => 'field_creators',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_creators][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Creators',
      'weight' => '7',
      'description' => 'Persons responsible for creating the content of this item. The principal creator should come first.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_publisher
  $fields['information-field_publisher'] = array(
    'field_name' => 'field_publisher',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '9',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'Open.Michigan, University of Michigan',
          '_error_element' => 'default_value_widget][field_publisher][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Publisher',
      'weight' => '9',
      'description' => 'Entity that published the resource.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_section_title
  $fields['information-field_section_title'] = array(
    'field_name' => 'field_section_title',
    'type_name' => 'information',
    'display_settings' => array(
      'weight' => '-99',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'creators|About the Creators
instructions|Instructions
objectives|Learning Objectives
outcomes|Learning Outcomes
reading|Reading List
schedule|Schedule
syllabus|Syllabus
wikiarticles|Wikipedia Articles
eval|Student Evaluations',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Section Title',
      'weight' => '-99',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_email
  $fields['instructor-field_email'] = array(
    'field_name' => 'field_email',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'email',
    'required' => '1',
    'multiple' => '0',
    'module' => 'email',
    'active' => '1',
    'widget' => array(
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'email' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Instructor Email Address',
      'weight' => '-4',
      'description' => 'Not shown to users.',
      'type' => 'email_textfield',
      'module' => 'email',
    ),
  );

  // Exported field: field_image_caption
  $fields['instructor-field_image_caption'] = array(
    'field_name' => 'field_image_caption',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_instr_photo',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '2',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_image_caption][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Image Caption',
      'weight' => '-1',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_instructor_courses
  $fields['instructor-field_instructor_courses'] = array(
    'field_name' => 'field_instructor_courses',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '2',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'instructor' => 0,
      'page' => 0,
      'resource' => 0,
      'story' => 0,
      'other' => FALSE,
      'material' => FALSE,
      'information' => FALSE,
      'session' => FALSE,
      'webform' => FALSE,
    ),
    'referrer_fields' => array(
      'field_course_instructor' => 'field_course_instructor',
      'field_course_academic_unit' => 0,
      'field_unit_parent_unit' => 0,
      'field_parent_unit' => FALSE,
      'field_course_reference' => FALSE,
      'field_content_reference' => FALSE,
      'field_unit_top' => FALSE,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Courses',
      'weight' => '2',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_instructor_image
  $fields['instructor-field_instructor_image'] = array(
    'field_name' => 'field_instructor_image',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => 'group_instr_photo',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '-2',
      'description' => 'Upload the image of the instructor above. The image will show to the left of the content. You will need to scale your image to size before uploading.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_instructor_resources
  $fields['instructor-field_instructor_resources'] = array(
    'field_name' => 'field_instructor_resources',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '3',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'resource' => 'resource',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'other' => FALSE,
      'material' => FALSE,
      'information' => FALSE,
      'session' => FALSE,
      'webform' => FALSE,
    ),
    'referrer_fields' => array(
      'field_resource_instructor' => 'field_resource_instructor',
      'field_course_academic_unit' => 0,
      'field_course_instructor' => 0,
      'field_instructor_academic_unit' => 0,
      'field_unit_parent_unit' => 0,
      'field_parent_unit' => FALSE,
      'field_course_reference' => FALSE,
      'field_content_reference' => FALSE,
      'field_unit_top' => FALSE,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Resources',
      'weight' => '3',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_instructor_unit
  $fields['instructor-field_instructor_unit'] = array(
    'field_name' => 'field_instructor_unit',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '1',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'unit' => 'unit',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'book' => 0,
      'course' => 0,
      'information' => 0,
      'material' => 0,
      'other' => 0,
      'session' => 0,
      'instructor' => 0,
      'page' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_course_instructor' => 'field_course_instructor',
      'field_parent_unit' => 0,
      'field_course_reference' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Academic Units',
      'weight' => '1',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_website
  $fields['instructor-field_website'] = array(
    'field_name' => 'field_website',
    'type_name' => 'instructor',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_instr_info',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => '_blank',
      'rel' => '',
      'class' => '',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'value',
    'title_value' => 'Visit Website',
    'enable_tokens' => 0,
    'validate_url' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Website',
      'weight' => '-1',
      'description' => 'Not shown to users.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_contributors
  $fields['material-field_contributors'] = array(
    'field_name' => 'field_contributors',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_contributors][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contributors',
      'weight' => 0,
      'description' => 'The names of people that have contributed to this item.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_reference
  $fields['material-field_course_reference'] = array(
    'field_name' => 'field_course_reference',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_course_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_course_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Course',
      'weight' => 0,
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_creators
  $fields['material-field_creators'] = array(
    'field_name' => 'field_creators',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_creators][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Creators',
      'weight' => '-1',
      'description' => 'Persons responsible for creating the content of this item. The principal creator should come first.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_file
  $fields['material-field_file'] = array(
    'field_name' => 'field_file',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => 'group_resource',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => '',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'label' => 'File',
      'weight' => '-2',
      'description' => 'Multiple file functionality is provided to allow the same file to be uploaded in different formats. e.g. <em>syllabus.doc</em> and <em>syllabus.pdf</em> contain the same metadata, hence can be grouped together.',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_image
  $fields['material-field_image'] = array(
    'field_name' => 'field_image',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '1',
      'parent' => 'group_resource',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'width300_imagelink',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'width300_imagelink',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '1',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_link
  $fields['material-field_link'] = array(
    'field_name' => 'field_link',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_resource',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => '',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'validate_url' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Link',
      'weight' => '-1',
      'description' => '',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_material_type
  $fields['material-field_material_type'] = array(
    'field_name' => 'field_material_type',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '-100',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'lectures|Lectures
assign|Assignments
exams|Exams
labs|Labs
demos|Demos
data|Data
schedules|Schedules
images|Image Collection
handouts|Handouts
cases|Case Studies
supp-readings|Supplemental Readings
studentnotes|Student Notes
projects|Student Projects
papers|Student Papers
present|Student Presentations
exercises|Exercises
software|Software Applications
misc|Miscellaneous
unknown|Unknown',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Material Type',
      'weight' => '-100',
      'description' => 'This will categorize the material in the above categories',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_publisher
  $fields['material-field_publisher'] = array(
    'field_name' => 'field_publisher',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '1',
      'parent' => 'group_ownership',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'Open.Michigan, University of Michigan',
          '_error_element' => 'default_value_widget][field_publisher][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Publisher',
      'weight' => '1',
      'description' => 'Entity that published the resource.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_resource_type
  $fields['material-field_resource_type'] = array(
    'field_name' => 'field_resource_type',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => 'group_resource',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'file|File
link|Link
image|Image
audio|Audio
video|Video',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Resource Type',
      'weight' => '-3',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_video
  $fields['material-field_video'] = array(
    'field_name' => 'field_video',
    'type_name' => 'material',
    'display_settings' => array(
      'weight' => '2',
      'parent' => 'group_resource',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'video_video',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'video_video',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'emvideo',
    'required' => '0',
    'multiple' => '0',
    'module' => 'emvideo',
    'active' => '1',
    'widget' => array(
      'video_width' => '425',
      'video_height' => '350',
      'video_autoplay' => 0,
      'preview_width' => '425',
      'preview_height' => '350',
      'preview_autoplay' => 0,
      'thumbnail_width' => '120',
      'thumbnail_height' => '90',
      'thumbnail_default_path' => '',
      'thumbnail_link_title' => 'See video',
      'providers' => array(
        'archive' => 0,
        'bliptv' => 0,
        'dailymotion' => 0,
        'google' => 0,
        'guba' => 0,
        'imeem' => 0,
        'lastfm' => 0,
        'livevideo' => 0,
        'metacafe' => 0,
        'myspace' => 0,
        'revver' => 0,
        'sevenload' => 0,
        'spike' => 0,
        'tudou' => 0,
        'twistage' => 0,
        'ustream' => 0,
        'ustreamlive' => 0,
        'vimeo' => 0,
        'voicethread' => 0,
        'yahoomusic' => 0,
        'youtube' => 0,
        'zzz_custom_url' => 0,
      ),
      'default_value' => array(
        '0' => array(
          'embed' => '',
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => '3rd Party Video',
      'weight' => '2',
      'description' => 'Enter the URL for the video. It will be embedded as part of the content.',
      'type' => 'emvideo_textfields',
      'module' => 'emvideo',
    ),
  );

  // Exported field: field_content_reference
  $fields['other-field_content_reference'] = array(
    'field_name' => 'field_content_reference',
    'type_name' => 'other',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => 'group_material_reference',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'material' => 'material',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Materials Reference',
      'weight' => '-2',
      'description' => 'Check the materials you would like to display with this content. If there are no materials above, you will first need to add materials to this course/resource.',
      'type' => 'nodereference_buttons',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_contributors
  $fields['other-field_contributors'] = array(
    'field_name' => 'field_contributors',
    'type_name' => 'other',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_contributors][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contributors',
      'weight' => '7',
      'description' => 'The names of people that have contributed to this item.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_reference
  $fields['other-field_course_reference'] = array(
    'field_name' => 'field_course_reference',
    'type_name' => 'other',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_course_information',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_course_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Course',
      'weight' => 0,
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_creators
  $fields['other-field_creators'] = array(
    'field_name' => 'field_creators',
    'type_name' => 'other',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_creators][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Creators',
      'weight' => '6',
      'description' => 'Persons responsible for creating the content of this item. The principal creator should come first.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_publisher
  $fields['other-field_publisher'] = array(
    'field_name' => 'field_publisher',
    'type_name' => 'other',
    'display_settings' => array(
      'weight' => '8',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'Open.Michigan, University of Michigan',
          '_error_element' => 'default_value_widget][field_publisher][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Publisher',
      'weight' => '8',
      'description' => 'Entity that published the resource.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_page_image
  $fields['page-field_page_image'] = array(
    'field_name' => 'field_page_image',
    'type_name' => 'page',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'Thumbnail_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'width300_default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '[site-name]',
      'custom_alt' => 1,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '-2',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_page_image_caption
  $fields['page-field_page_image_caption'] = array(
    'field_name' => 'field_page_image_caption',
    'type_name' => 'page',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '2',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          'format' => '1',
          '_error_element' => 'default_value_widget][field_page_image_caption][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Image Caption',
      'weight' => '-1',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_content_reference
  $fields['session-field_content_reference'] = array(
    'field_name' => 'field_content_reference',
    'type_name' => 'session',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_material_reference',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'material' => 'material',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Materials Reference',
      'weight' => '-1',
      'description' => 'Check the materials you would like to display with this content. If there are no materials above, you will first need to add materials to this course/resource.',
      'type' => 'nodereference_buttons',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_contributors
  $fields['session-field_contributors'] = array(
    'field_name' => 'field_contributors',
    'type_name' => 'session',
    'display_settings' => array(
      'weight' => '8',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_contributors][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contributors',
      'weight' => '8',
      'description' => 'The names of people that have contributed to this item.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_course_reference
  $fields['session-field_course_reference'] = array(
    'field_name' => 'field_course_reference',
    'type_name' => 'session',
    'display_settings' => array(
      'weight' => '1',
      'parent' => 'group_course_information',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_course_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Course',
      'weight' => '1',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_creators
  $fields['session-field_creators'] = array(
    'field_name' => 'field_creators',
    'type_name' => 'session',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_creators][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Creators',
      'weight' => '7',
      'description' => 'Persons responsible for creating the content of this item. The principal creator should come first.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_publisher
  $fields['session-field_publisher'] = array(
    'field_name' => 'field_publisher',
    'type_name' => 'session',
    'display_settings' => array(
      'weight' => '9',
      'parent' => 'group_ownership',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'Open.Michigan, University of Michigan',
          '_error_element' => 'default_value_widget][field_publisher][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Publisher',
      'weight' => '9',
      'description' => 'Entity that published the resource.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_code
  $fields['unit-field_code'] = array(
    'field_name' => 'field_code',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '-90',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_code][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Code/URL',
      'weight' => '-90',
      'description' => 'Code or identifier for this particular academic unit. This code will be used as part of the URL path.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_parent_unit
  $fields['unit-field_parent_unit'] = array(
    'field_name' => 'field_parent_unit',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '19',
      'parent' => 'group_academic_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'unit' => 'unit',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_parent_unit][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'No, this is not a top level unit. Its parent unit is',
      'weight' => '19',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_unit_courses
  $fields['unit-field_unit_courses'] = array(
    'field_name' => 'field_unit_courses',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '19',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'course' => 'course',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_parent_unit' => 'field_parent_unit',
      'field_course_instructor' => 0,
      'field_course_reference' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Course/Resource',
      'weight' => '19',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_unit_image
  $fields['unit-field_unit_image'] = array(
    'field_name' => 'field_unit_image',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '19',
      'parent' => 'group_academic_image',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'Thumbnail_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'width300_default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '[site-name]',
      'custom_alt' => 1,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image',
      'weight' => '19',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_unit_image_caption
  $fields['unit-field_unit_image_caption'] = array(
    'field_name' => 'field_unit_image_caption',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '20',
      'parent' => 'group_academic_image',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '2',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '<p>&nbsp;</p>',
          '_error_element' => 'default_value_widget][field_unit_image_caption][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Image Caption',
      'weight' => '20',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_unit_instructors
  $fields['unit-field_unit_instructors'] = array(
    'field_name' => 'field_unit_instructors',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '18',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'instructor' => 'instructor',
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'page' => 0,
      'resource' => 0,
      'story' => 0,
      'other' => FALSE,
      'material' => FALSE,
      'information' => FALSE,
      'session' => FALSE,
      'webform' => FALSE,
    ),
    'referrer_fields' => array(
      'field_instructor_academic_unit' => 'field_instructor_academic_unit',
      'field_course_academic_unit' => 0,
      'field_course_instructor' => 0,
      'field_unit_parent_unit' => 0,
      'field_parent_unit' => FALSE,
      'field_course_reference' => FALSE,
      'field_content_reference' => FALSE,
      'field_unit_top' => FALSE,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Instructors',
      'weight' => '18',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_unit_sub_unit
  $fields['unit-field_unit_sub_unit'] = array(
    'field_name' => 'field_unit_sub_unit',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '20',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereferrer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereferrer',
    'active' => '1',
    'referrer_types' => array(
      'unit' => 'unit',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'referrer_fields' => array(
      'field_parent_unit' => 'field_parent_unit',
      'field_course_instructor' => 0,
      'field_course_reference' => 0,
      'field_content_reference' => 0,
      'field_unit_top' => 0,
    ),
    'referrer_nodes_per_page' => '0',
    'referrer_pager_element' => '0',
    'referrer_order' => 'TITLE_ASC',
    'widget' => array(
      'label' => 'Department/Curriculum',
      'weight' => '20',
      'description' => '',
      'type' => 'nodereferrer_list',
      'module' => 'nodereferrer',
    ),
  );

  // Exported field: field_unit_top
  $fields['unit-field_unit_top'] = array(
    'field_name' => 'field_unit_top',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '18',
      'parent' => 'group_academic_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'unit' => 0,
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course' => 0,
      'other' => 0,
      'instructor' => 0,
      'material' => 0,
      'information' => 0,
      'page' => 0,
      'session' => 0,
      'story' => 0,
      'webform' => 0,
    ),
    'advanced_view' => 'top',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Is this a parent unit?',
      'weight' => '18',
      'description' => '',
      'type' => 'nodereference_buttons',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_unit_type
  $fields['unit-field_unit_type'] = array(
    'field_name' => 'field_unit_type',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '16',
      'parent' => 'group_academic_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'college|College
school|School
department|Department
program|Program
library|Library',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Academic Unit Type',
      'weight' => '16',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_website
  $fields['unit-field_website'] = array(
    'field_name' => 'field_website',
    'type_name' => 'unit',
    'display_settings' => array(
      'weight' => '17',
      'parent' => 'group_academic_information',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => '_blank',
      'rel' => '',
      'class' => '',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'value',
    'title_value' => 'Visit Website',
    'enable_tokens' => 0,
    'validate_url' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Website',
      'weight' => '17',
      'description' => 'Add the website address for the school/department. Include http://. For example: http://www.engin.umich.edu/',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('3rd Party Video');
  t('Academic Term');
  t('Academic Unit');
  t('Academic Unit Type');
  t('Academic Units');
  t('Academic Year');
  t('Code/URL');
  t('Content Type');
  t('Contributors');
  t('Course');
  t('Course Instructor');
  t('Course/Resource');
  t('Courses');
  t('Creators');
  t('Department/Curriculum');
  t('Download Button Display');
  t('Education Level');
  t('Feature on Main page');
  t('File');
  t('Highlights');
  t('Image');
  t('Image Caption');
  t('Instructor Email Address');
  t('Instructors');
  t('Is this a parent unit?');
  t('Link');
  t('Material');
  t('Material Type');
  t('Materials Reference');
  t('No, this is not a top level unit. Its parent unit is');
  t('Overview - Sliders');
  t('Publisher');
  t('Resource Type');
  t('Resources');
  t('Section Title');
  t('Session');
  t('Short Title/Course Code');
  t('Structure');
  t('URL');
  t('Website');

  return $fields;
}
