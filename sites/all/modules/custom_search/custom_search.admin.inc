<?php
// $Id: custom_search.admin.inc,v 1.1.2.6 2010/03/28 14:51:45 jdanthinne Exp $

/**
 * @file
 * Admin settings for custom search
 */

/**
 * Implementation of hook_help().
 */
function custom_search_help($path, $arg) {
  switch ($path) {
    case 'admin/settings/custom_search/content':
      $output = t('Select the search types to present as search options in the search block. If none is selected, no selector will be displayed. <strong>Note</strong>: if there\'s only one type checked, the selector won\'t be displayed BUT only this type will be searched.');
      break;
    case 'admin/settings/custom_search/taxonomy':
      $output = t('Select the vocabularies to present as search options in the search block. If none is selected, no selector will be displayed.');
      break;
  }
  return $output;
}

function custom_search_admin() {
  $directory_path = file_directory_path() . '/custom_search';
  file_check_directory($directory_path, FILE_CREATE_DIRECTORY);
  // Check for a new uploaded image.
  if ($file = file_save_upload('custom_search_image', array('file_validate_is_image' => array()))) {
    if (file_copy($file, $directory_path)) {
      $_POST['custom_search_image_path'] = $file->filepath;
    }
  }

  // Labels & default text.
  $form['search_box'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Search box'),
  );
  $form['search_box']['custom_search_label_visibility'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display label'),
    '#default_value'  => variable_get('custom_search_label_visibility', TRUE),
  );
  $form['search_box']['custom_search_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box label'),
    '#default_value'  => variable_get('custom_search_label', CUSTOM_SEARCH_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the search box. The default value is "!default".', array('!default' => CUSTOM_SEARCH_LABEL_DEFAULT)),
  );
  $form['search_box']['custom_search_text'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box default text'),
    '#default_value'  => variable_get('custom_search_text', ''),
    '#description'    => t('This will change the default text inside the search form. Leave blank for no text. This field is blank by default.'),
  );

  // Submit button.
  $form['submit_button'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Submit button'),
  );
  $form['submit_button']['custom_search_submit_text'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Submit button text'),
    '#default_value'  => variable_get('custom_search_submit_text', CUSTOM_SEARCH_SUBMIT_TEXT_DEFAULT),
    '#description'    => t('Enter the text for the submit button. Leave blank to hide it. The default value is "!default".', array('!default' => CUSTOM_SEARCH_SUBMIT_TEXT_DEFAULT)),
  );
  $form['submit_button']['custom_search_image_path'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Submit image path'),
    '#description'    => t('The path to the file you would like to use as submit button instead of the default text button.'),
    '#default_value'  => variable_get('custom_search_image_path', ''),
  );
  $form['submit_button']['custom_search_image'] = array(
    '#type'           => 'file',
    '#title'          => t('Submit image'),
    '#description'    => t('If you don\'t have direct file access to the server, use this field to upload your image.'),
  );

  // Criteria.
  $form['criteria'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Advanced search criteria'),
  );
  $form['criteria']['or'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Or'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['criteria']['or']['custom_search_criteria_or_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_criteria_or_display', FALSE),
  );
  $form['criteria']['or']['custom_search_criteria_or_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_criteria_or_label', CUSTOM_SEARCH_CRITERIA_OR_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_OR_LABEL_DEFAULT)),
  );
  $form['criteria']['phrase'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Phrase'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['criteria']['phrase']['custom_search_criteria_phrase_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_criteria_phrase_display', FALSE),
  );
  $form['criteria']['phrase']['custom_search_criteria_phrase_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_criteria_phrase_label', CUSTOM_SEARCH_CRITERIA_PHRASE_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_PHRASE_LABEL_DEFAULT)),
  );
  $form['criteria']['negative'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Negative'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['criteria']['negative']['custom_search_criteria_negative_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_criteria_negative_display', FALSE),
  );
  $form['criteria']['negative']['custom_search_criteria_negative_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_criteria_negative_label', CUSTOM_SEARCH_CRITERIA_NEGATIVE_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_NEGATIVE_LABEL_DEFAULT)),
  );

  // Ordering.
  $form['order'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Elements ordering'),
  );
  $form['order']['custom_search_order'] = array(
    '#tree'   => TRUE,
    '#theme'  => 'custom_search_sort_form',
  );
  $form['order']['custom_search_order']['search_box'] = array(
    '#title'  => t('Search Box'),
    'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_search_box_weight', -1)),
    '#weight' => variable_get('custom_search_search_box_weight', -1),
  );
  if (count(array_filter(array_merge(variable_get('custom_search_node_types', array()), variable_get('custom_search_other', array()))))) {
    $form['order']['custom_search_order']['content_types'] = array(
      '#title'  => t('Content Types'),
      'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_content_types_weight', 0)),
      '#weight' => variable_get('custom_search_content_types_weight', 0),
    );
  }
  if (module_exists('taxonomy')) {
    $vocabularies = taxonomy_get_vocabularies();
    $w = 1;
    foreach ($vocabularies as $voc) {
      if (variable_get('custom_search_voc' . $voc->vid . '_selector', 'disabled') != 'disabled') {
        $form['order']['custom_search_order']['taxonomy' . $voc->vid] = array(
          '#title'  => t('Taxonomy') . ': ' . $voc->name,
          'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_taxonomy' . $voc->vid . '_weight', $w)),
          '#weight' => variable_get('custom_search_taxonomy' . $voc->vid . '_weight', $w),
        );
        $w++;
      }
    }
  }
  $form['order']['custom_search_order']['criteria_or'] = array(
    '#title'  => t('Advanced search criterion: Or'),
    'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_criteria_or_weight', 7)),
    '#weight' => variable_get('custom_search_criteria_or_weight', 7),
  );
  $form['order']['custom_search_order']['criteria_phrase'] = array(
    '#title'  => t('Advanced search criterion: Phrase'),
    'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_criteria_phrase_weight', 8)),
    '#weight' => variable_get('custom_search_criteria_phrase_weight', 8),
  );
  $form['order']['custom_search_order']['criteria_negative'] = array(
    '#title'  => t('Advanced search criterion: Negative'),
    'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_criteria_negative_weight', 9)),
    '#weight' => variable_get('custom_search_criteria_negative_weight', 9),
  );
  $form['order']['custom_search_order']['submit_button'] = array(
    '#title'  => t('Submit button'),
    'sort'    => array('#type' => 'weight', '#default_value' => variable_get('custom_search_submit_button_weight', 10)),
    '#weight' => variable_get('custom_search_submit_button_weight', 10),
  );

  $form['#attributes'] = array('enctype' => 'multipart/form-data');
  $form['#submit'][] = 'custom_search_admin_submit';
  return system_settings_form($form);
}

/**
 * Submit callback to save the ordering
 */
function custom_search_admin_submit($form, &$form_state) {
  foreach ($form_state['values']['custom_search_order'] as $key => $data) {
    variable_set('custom_search_' . $key . '_weight', $data['sort']);
  }
}

/**
 * Theme the re-ordering form.
 */
function theme_custom_search_sort_form($form) {
  drupal_add_tabledrag('custom-search-sort', 'order', 'sibling', 'sort');
  $header = array(t('Elements'), 'sort');
  foreach (element_children($form) as $key) {
    // Add class to group weight fields for drag and drop.
    $form[$key]['sort']['#attributes']['class'] = 'sort';
    $row = array();
    $row[] = $form[$key]['#title'];
    $row[] = drupal_render($form[$key]['sort']);
    $rows[] = array('data' => $row, 'class' => 'draggable');
  }
  $output = theme('table', $header, $rows, array('id' => 'custom-search-sort'));
  $output .= drupal_render($form);
  return $output;
}

function custom_search_content_admin() {
  $form['custom_search_node_types'] = array(
    '#type'           => 'checkboxes',
    '#title'          => t('Content types'),
    '#default_value'  => variable_get('custom_search_node_types', array()),
    '#options'        => node_get_types('names'),
  );
  // Other searches.
  $options = array();
  foreach (module_implements('search') as $module) {
    if ($module != 'node' && $name = module_invoke($module, 'search', 'name')) {
      $options[$module] = $name;
    }
  }
  if (count($options)) {
    $form['custom_search_other'] = array(
      '#type'           => 'checkboxes',
      '#title'          => t('Other searches'),
      '#default_value'  => variable_get('custom_search_other', array()),
      '#options'        => $options,
    );
  }
  $form['custom_search_type_selector'] = array(
    '#type'           => 'select',
    '#title'          => t('Selector type'),
    '#options'        => array(
      'select'          => t('Drop-down list'),
      'selectmultiple'  => t('Drop-down list with multiple choices'),
      'radios'          => t('Radio buttons'),
      'checkboxes'      => t('Checkboxes'),
    ),
    '#description'    => t('Choose which selector type to use. Note: content types and other searches cannot be combined in a single search.'),
    '#default_value'  => variable_get('custom_search_type_selector', 'select'),
  );
  $form['custom_search_type_selector_label_visibility'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display label'),
    '#default_value'  => variable_get('custom_search_type_selector_label_visibility', TRUE),
  );
  $form['custom_search_type_selector_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label text'),
    '#default_value'  => variable_get('custom_search_type_selector_label', CUSTOM_SEARCH_TYPE_SELECTOR_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the selector. The default value is "!default".', array('!default' => CUSTOM_SEARCH_TYPE_SELECTOR_LABEL_DEFAULT)),
  );
  $form['custom_search_type_selector_all'] = array(
    '#type'           => 'textfield',
    '#title'          => t('-Any content type- text'),
    '#default_value'  => variable_get('custom_search_type_selector_all', CUSTOM_SEARCH_ALL_TEXT_DEFAULT),
    '#required'       => TRUE,
    '#description'    => t('Enter the text for "any content type" choice. The default value is "!default".', array('!default' => CUSTOM_SEARCH_ALL_TEXT_DEFAULT)),
  );

  return system_settings_form($form);
}

function custom_search_taxonomy_admin() {
  $vocabularies = taxonomy_get_vocabularies();
  if (count($vocabularies)) {
    $options = array();
    foreach ($vocabularies as $voc) {
      $form[$voc->name] = array(
        '#type'         => 'fieldset',
        '#title'        => $voc->name,
        '#collapsible'  => TRUE,
        '#collapsed'    => (variable_get('custom_search_voc' . $voc->vid . '_selector', 'disabled') == 'disabled') ? TRUE : FALSE,
      );
      $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector'] = array(
        '#type'           => 'select',
        '#title'          => t('Selector type'),
        '#options'        => array(
          'disabled'        => t('Disabled'),
          'select'          => t('Drop-down list'),
          'selectmultiple'  => t('Drop-down list with multiple choices'),
          'radios'          => t('Radio buttons'),
          'checkboxes'      => t('Checkboxes'),
        ),
        '#description'    => t('Choose which selector type to use.'),
        '#default_value'  => variable_get('custom_search_voc' . $voc->vid . '_selector', 'disabled'),
      );
      $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector_label_visibility'] = array(
        '#type'           => 'checkbox',
        '#title'          => t('Display label'),
        '#default_value'  => variable_get('custom_search_voc' . $voc->vid . '_selector_label_visibility', TRUE),
      );
      $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector_label'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Label text'),
        '#default_value'  => variable_get('custom_search_voc' . $voc->vid . '_selector_label', $voc->name),
        '#description'    => t('Enter the label text for the selector. The default value is "!default".', array('!default' => $voc->name)),
      );
      $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector_all'] = array(
        '#type'           => 'textfield',
        '#title'          => t('-Any- text'),
        '#default_value'  => variable_get('custom_search_voc' . $voc->vid . '_selector_all', CUSTOM_SEARCH_ALL_TEXT_DEFAULT),
        '#required'       => TRUE,
        '#description'    => t('Enter the text for "any term" choice. The default value is "!default".', array('!default' => CUSTOM_SEARCH_ALL_TEXT_DEFAULT)),
      );
    }
  }
  return system_settings_form($form);
}

function custom_search_results_admin() {

  $form['search_form'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Search form'),
  );
  $form['search_form']['custom_search_results_search'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display basic search'),
    '#default_value'  => variable_get('custom_search_results_search', TRUE),
  );
  $form['search_form']['custom_search_results_advanced_search'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display advanced search'),
    '#default_value'  => variable_get('custom_search_results_advanced_search', TRUE),
  );
  $form['filter'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Filter'),
    '#description'  => t('Add links to filter the results by content type.'),
  );
  $form['filter']['custom_search_filter'] = array(
    '#type'           => 'select',
    '#title'          => t('Position'),
    '#options'        => array(
      'disabled'  => t('Disabled'),
      'above'     => t('Above results'),
      'below'     => t('Below results'),
    ),
    '#default_value'  => variable_get('custom_search_filter', 'disabled'),
  );
  $form['filter']['custom_search_filter_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label text'),
    '#default_value'  => variable_get('custom_search_filter_label', CUSTOM_SEARCH_FILTER_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the list. The default value is "!default".', array('!default' => CUSTOM_SEARCH_FILTER_LABEL_DEFAULT)),
  );

  return system_settings_form($form);
}