<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function openmichigan_content_types_imagecache_default_presets() {
  $items = array(
    'Thumbnail' => array(
      'presetname' => 'Thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '100',
            'height' => '100',
          ),
        ),
      ),
    ),
    'width300' => array(
      'presetname' => 'width300',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '300',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function openmichigan_content_types_node_info() {
  $items = array(
    'course' => array(
      'name' => t('Course/Resource'),
      'module' => 'features',
      'description' => t('A <em>course</em> belong to a specific <em>school</em> or <em>college</em> and may contain multiple <em>resource</em>s.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'information' => array(
      'name' => t('Overview Slider'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'instructor' => array(
      'name' => t('Instructor'),
      'module' => 'features',
      'description' => t('An <em>instructor</em> contains information on the person that supplies all the information for a <em>course</em>.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '1',
      'body_label' => t('Bio'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'material' => array(
      'name' => t('Material'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'other' => array(
      'name' => t('Highlights'),
      'module' => 'features',
      'description' => t('Content type associated with a course. This content type is flexible in the title of the tab and what content is added.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'session' => array(
      'name' => t('Sessions'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'unit' => array(
      'name' => t('Academic Unit/Department/Curriculum'),
      'module' => 'features',
      'description' => t('An <em>academic unit</em> focuses on a specific area of education. It can also contain other <em>academic units</em> as part of it. Examples are College of Engineering, School of Information, or Department of Chemistry.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
