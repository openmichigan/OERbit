<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function oerbit_acadamic_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_course_image
  $groups['course-group_course_image'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_course_image',
    'label' => 'Content Image',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-93',
    'fields' => array(
      '0' => 'field_course_image',
      '1' => 'field_course_image_caption',
    ),
  );

  // Exported group: group_course_information
  $groups['course-group_course_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_course_information',
    'label' => 'Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-94',
    'fields' => array(
      '0' => 'field_parent_unit',
      '1' => 'field_course_level',
      '2' => 'field_course_structure',
      '3' => 'field_course_term',
      '4' => 'field_course_year',
    ),
  );

  // Exported group: group_display
  $groups['course-group_display'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_display',
    'label' => 'Display Options',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-91',
    'fields' => array(
      '0' => 'field_course_download_display',
      '1' => 'field_course_featured',
    ),
  );

  // Exported group: group_instructor
  $groups['course-group_instructor'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_instructor',
    'label' => 'Instructor',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-92',
    'fields' => array(
      '0' => 'field_course_instructor',
    ),
  );

  // Exported group: group_ownership
  $groups['course-group_ownership'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_ownership',
    'label' => 'Ownership',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-90',
    'fields' => array(
      '0' => 'field_creators',
      '1' => 'field_contributors',
      '2' => 'field_publisher',
    ),
  );

  // Exported group: group_course_information
  $groups['information-group_course_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'information',
    'group_name' => 'group_course_information',
    'label' => 'Course Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '-95',
    'fields' => array(
      '0' => 'field_course_reference',
    ),
  );

  // Exported group: group_material_reference
  $groups['information-group_material_reference'] = array(
    'group_type' => 'standard',
    'type_name' => 'information',
    'group_name' => 'group_material_reference',
    'label' => 'Materials To Add',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-97',
    'fields' => array(
      '0' => 'field_content_reference',
    ),
  );

  // Exported group: group_ownership
  $groups['information-group_ownership'] = array(
    'group_type' => 'standard',
    'type_name' => 'information',
    'group_name' => 'group_ownership',
    'label' => 'Ownership',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '-96',
    'fields' => array(
      '0' => 'field_creators',
      '1' => 'field_contributors',
      '2' => 'field_publisher',
    ),
  );

  // Exported group: group_instr_info
  $groups['instructor-group_instr_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'instructor',
    'group_name' => 'group_instr_info',
    'label' => 'Instructor Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_website',
    ),
  );

  // Exported group: group_instr_photo
  $groups['instructor-group_instr_photo'] = array(
    'group_type' => 'standard',
    'type_name' => 'instructor',
    'group_name' => 'group_instr_photo',
    'label' => 'Instructor Photo',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-1',
    'fields' => array(
      '0' => 'field_instructor_image',
      '1' => 'field_image_caption',
    ),
  );

  // Exported group: group_course_information
  $groups['material-group_course_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'material',
    'group_name' => 'group_course_information',
    'label' => 'Course Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-96',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-96',
    'fields' => array(
      '0' => 'field_course_reference',
    ),
  );

  // Exported group: group_ownership
  $groups['material-group_ownership'] = array(
    'group_type' => 'standard',
    'type_name' => 'material',
    'group_name' => 'group_ownership',
    'label' => 'Ownership',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-97',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-97',
    'fields' => array(
      '0' => 'field_creators',
      '1' => 'field_contributors',
      '2' => 'field_publisher',
    ),
  );

  // Exported group: group_resource
  $groups['material-group_resource'] = array(
    'group_type' => 'standard',
    'type_name' => 'material',
    'group_name' => 'group_resource',
    'label' => 'Resource',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-98',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-98',
    'fields' => array(
      '0' => 'field_resource_type',
      '1' => 'field_file',
      '2' => 'field_link',
      '3' => 'field_image',
      '4' => 'field_video',
    ),
  );

  // Exported group: group_course_information
  $groups['other-group_course_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'other',
    'group_name' => 'group_course_information',
    'label' => 'Course Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_course_reference',
    ),
  );

  // Exported group: group_material_reference
  $groups['other-group_material_reference'] = array(
    'group_type' => 'standard',
    'type_name' => 'other',
    'group_name' => 'group_material_reference',
    'label' => 'Materials To Add',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-3',
    'fields' => array(
      '0' => 'field_content_reference',
    ),
  );

  // Exported group: group_ownership
  $groups['other-group_ownership'] = array(
    'group_type' => 'standard',
    'type_name' => 'other',
    'group_name' => 'group_ownership',
    'label' => 'Ownership',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '-1',
    'fields' => array(
      '0' => 'field_creators',
      '1' => 'field_contributors',
      '2' => 'field_publisher',
    ),
  );

  // Exported group: group_page_image
  $groups['page-group_page_image'] = array(
    'group_type' => 'standard',
    'type_name' => 'page',
    'group_name' => 'group_page_image',
    'label' => 'Page Image',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-3',
    'fields' => array(
      '0' => 'field_page_image',
      '1' => 'field_page_image_caption',
    ),
  );

  // Exported group: group_course_information
  $groups['session-group_course_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'session',
    'group_name' => 'group_course_information',
    'label' => 'Course Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_course_reference',
    ),
  );

  // Exported group: group_material_reference
  $groups['session-group_material_reference'] = array(
    'group_type' => 'standard',
    'type_name' => 'session',
    'group_name' => 'group_material_reference',
    'label' => 'Materials To Add',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_content_reference',
    ),
  );

  // Exported group: group_ownership
  $groups['session-group_ownership'] = array(
    'group_type' => 'standard',
    'type_name' => 'session',
    'group_name' => 'group_ownership',
    'label' => 'Ownership',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
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
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'hidden',
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_creators',
      '1' => 'field_contributors',
      '2' => 'field_publisher',
    ),
  );

  // Exported group: group_academic_image
  $groups['unit-group_academic_image'] = array(
    'group_type' => 'standard',
    'type_name' => 'unit',
    'group_name' => 'group_academic_image',
    'label' => 'Academic Unit Image',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-60',
    'fields' => array(
      '0' => 'field_unit_image',
      '1' => 'field_unit_image_caption',
    ),
  );

  // Exported group: group_academic_information
  $groups['unit-group_academic_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'unit',
    'group_name' => 'group_academic_information',
    'label' => 'Academic Unit Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-70',
    'fields' => array(
      '0' => 'field_unit_type',
      '1' => 'field_website',
      '2' => 'field_unit_top',
      '3' => 'field_parent_unit',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Academic Unit Image');
  t('Academic Unit Information');
  t('Content Image');
  t('Course Information');
  t('Display Options');
  t('Information');
  t('Instructor');
  t('Instructor Information');
  t('Instructor Photo');
  t('Materials To Add');
  t('Ownership');
  t('Page Image');
  t('Resource');

  return $groups;
}
