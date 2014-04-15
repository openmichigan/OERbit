<?php

/**
 * Image button form.
 */
function _custom_search_default_admin_form($delta = '') {
  if ($delta != '') $delta = 'blocks_' . $delta . '_';

  // Labels & default text.
  $form['search_box'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Search box'),
  );
  $form['search_box']['custom_search_' . $delta . 'label_visibility'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'label_visibility', TRUE),
  );
  $form['search_box']['custom_search_' . $delta . 'label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'label', CUSTOM_SEARCH_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the search box. The default value is "!default".', array('!default' => CUSTOM_SEARCH_LABEL_DEFAULT)),
  );
  $form['search_box']['custom_search_' . $delta . 'text'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box default text'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'text', ''),
    '#description'    => t('This will change the default text inside the search form. Leave blank for no text. This field is blank by default.'),
  );
  $form['search_box']['custom_search_' . $delta . 'size'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box size'),
    '#size'           => 3,
    '#default_value'  => variable_get('custom_search_' . $delta . 'size', CUSTOM_SEARCH_SIZE_DEFAULT),
    '#description'    => t('The default value is "!default".', array('!default' => CUSTOM_SEARCH_SIZE_DEFAULT)),
  );
  $form['search_box']['custom_search_' . $delta . 'max_length'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Search box maximum length'),
    '#size'           => 3,
    '#default_value'  => variable_get('custom_search_' . $delta . 'max_length', CUSTOM_SEARCH_MAX_LENGTH_DEFAULT),
    '#description'    => t('The default value is "!default".', array('!default' => CUSTOM_SEARCH_MAX_LENGTH_DEFAULT)),
    '#required'       => TRUE,
  );

  // Submit button.
  $form['submit_button'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Submit button'),
  );
  $form['submit_button']['custom_search_' . $delta . 'submit_text'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Submit button text'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'submit_text', CUSTOM_SEARCH_SUBMIT_TEXT_DEFAULT),
    '#description'    => t('Enter the text for the submit button. Leave blank to hide it. The default value is "!default".', array('!default' => CUSTOM_SEARCH_SUBMIT_TEXT_DEFAULT)),
  );
  $form['submit_button']['custom_search_' . $delta . 'image_path'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Submit image path'),
    '#description'    => t('The path to the file you would like to use as submit button instead of the default text button.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'image_path', ''),
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
  $form['criteria']['or']['custom_search_' . $delta . 'criteria_or_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_or_display', FALSE),
  );
  $form['criteria']['or']['custom_search_' . $delta . 'criteria_or_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_or_label', CUSTOM_SEARCH_CRITERIA_OR_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_OR_LABEL_DEFAULT)),
  );
  $form['criteria']['phrase'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Phrase'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['criteria']['phrase']['custom_search_' . $delta . 'criteria_phrase_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_phrase_display', FALSE),
  );
  $form['criteria']['phrase']['custom_search_' . $delta . 'criteria_phrase_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_phrase_label', CUSTOM_SEARCH_CRITERIA_PHRASE_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_PHRASE_LABEL_DEFAULT)),
  );
  $form['criteria']['negative'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Negative'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
  $form['criteria']['negative']['custom_search_' . $delta . 'criteria_negative_display'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_negative_display', FALSE),
  );
  $form['criteria']['negative']['custom_search_' . $delta . 'criteria_negative_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'criteria_negative_label', CUSTOM_SEARCH_CRITERIA_NEGATIVE_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for this field. The default value is "!default".', array('!default' => CUSTOM_SEARCH_CRITERIA_NEGATIVE_LABEL_DEFAULT)),
  );

  return $form;
}

/**
 * Content admin form.
 */
function _custom_search_content_admin_form($delta = '') {
  if ($delta != '') $delta = 'blocks_' . $delta . '_';

  $form['content_selector'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Content selector'),
    '#description'  => t('Select the search types to present as search options in the search block. If none is selected, no selector will be displayed. <strong>Note</strong>: if there\'s only one type checked, the selector won\'t be displayed BUT only this type will be searched.'),
  );
  $form['content_selector']['custom_search_' . $delta . 'node_types'] = array(
    '#type'           => 'checkboxes',
    '#title'          => t('Content types'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'node_types', array()),
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
    $form['content_selector']['custom_search_' . $delta . 'other'] = array(
      '#type'           => 'checkboxes',
      '#title'          => t('Other searches'),
      '#default_value'  => variable_get('custom_search_' . $delta . 'other', array()),
      '#options'        => $options,
    );
  }
  $form['content_selector']['custom_search_' . $delta . 'type_selector'] = array(
    '#type'           => 'select',
    '#title'          => t('Selector type'),
    '#options'        => array(
      'select'          => t('Drop-down list'),
      'selectmultiple'  => t('Drop-down list with multiple choices'),
      'radios'          => t('Radio buttons'),
      'checkboxes'      => t('Checkboxes'),
    ),
    '#description'    => t('Choose which selector type to use. Note: content types and other searches cannot be combined in a single search.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'type_selector', 'select'),
  );
  $form['content_selector']['custom_search_' . $delta . 'type_selector_label_visibility'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'type_selector_label_visibility', TRUE),
  );
  $form['content_selector']['custom_search_' . $delta . 'type_selector_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label text'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'type_selector_label', CUSTOM_SEARCH_TYPE_SELECTOR_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the selector. The default value is "!default".', array('!default' => CUSTOM_SEARCH_TYPE_SELECTOR_LABEL_DEFAULT)),
  );
  $form['content_selector']['any'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('-Any-'),
  );
  $form['content_selector']['any']['custom_search_' . $delta . 'type_selector_all'] = array(
    '#type'           => 'textfield',
    '#title'          => t('-Any content type- text'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'type_selector_all', CUSTOM_SEARCH_ALL_TEXT_DEFAULT),
    '#required'       => TRUE,
    '#description'    => t('Enter the text for "any content type" choice. The default value is "!default".', array('!default' => CUSTOM_SEARCH_ALL_TEXT_DEFAULT)),
  );
  $form['content_selector']['any']['custom_search_' . $delta . 'any_restricts'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Choosing -Any- restricts the search to the selected content types.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'any_restricts', FALSE),
    '#description'    => t('If not checked, choosing -Any- will search in all content types.'),
  );
  $form['content_selector']['any']['custom_search_' . $delta . 'any_force'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Force -Any- to be displayed.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'any_force', FALSE),
    '#description'    => t('When only one content type is selected, the default behaviour is to hide the selector. If you need the -Any- option to be displayed, check this.'),
  );

  $form['custom_search_' . $delta . 'node_types_excluded'] = array(
    '#type'           => 'checkboxes',
    '#title'          => t('Content exclusion'),
    '#description'    => t('Select the content types you don\'t want to be displayed as results.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'node_types_excluded', array()),
    '#options'        => node_get_types('names'),
  );

  return $form;
}

/**
 * Custom paths admin form.
 */
function _custom_search_custom_paths_admin_form($delta = '') {
  if ($delta != '') $delta = 'blocks_' . $delta . '_';
  $form['custom_search_paths_admin'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Custom search paths'),
    '#collapsed'    => TRUE,
    '#collapsible'  => TRUE,
  );
  $form['custom_search_paths_admin']['custom_search_' . $delta . 'paths_selector'] = array(
    '#type'           => 'select',
    '#title'          => t('Selector type'),
    '#options'        => array(
      'select'          => t('Drop-down list'),
      'radios'          => t('Radio buttons'),
    ),
    '#description'    => t('Choose which selector type to use.'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'paths_selector', 'select'),
  );
  $form['custom_search_paths_admin']['custom_search_' . $delta . 'paths_selector_label_visibility'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Display label'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'paths_selector_label_visibility', TRUE),
  );
  $form['custom_search_paths_admin']['custom_search_' . $delta . 'paths_selector_label'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Label text'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'paths_selector_label', CUSTOM_SEARCH_PATHS_SELECTOR_LABEL_DEFAULT),
    '#description'    => t('Enter the label text for the selector. The default value is "!default".', array('!default' => CUSTOM_SEARCH_PATHS_SELECTOR_LABEL_DEFAULT)),
  );
  $form['custom_search_paths_admin']['custom_search_' . $delta . 'paths'] = array(
    '#type'           => 'textarea',
    '#title'          => t('Paths'),
    '#default_value'  => variable_get('custom_search_' . $delta . 'paths', ''),
    '#rows'           => 3,
    '#description'    => t('If you want to use custom search paths, enter them here in the form <em>path</em>|<em>label</em>, one per line (if only one path is specified, the selector will be hidden). The [key] token will be replaced by what is entered in the search box. Ie: mysearch/[key]|My custom search label.'),
  );
  return $form;
}

/**
 * Ordering admin form
 */
function _custom_search_ordering_admin_form($delta = '') {
  drupal_add_css(drupal_get_path('module', 'custom_search') . '/custom_search.css', 'module');

  if ($delta != '') $delta = 'blocks_' . $delta . '_';
  $form['order'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Elements ordering'),
    '#description'  => t('Order the form elements as you want them to be displayed. If you put elements in the Popup section, they will only appear when the search field is clicked.')
  );
  $form['order']['custom_search_' . $delta . 'order'] = array(
    '#tree'   => TRUE,
    '#theme'  => 'custom_search_sort_form',
  );

  $elements = array(
    'search_box'        => array('title' => t('Search box'), 'default_weight' => -1),
    'criteria_or'       => array('title' => t('Advanced search criterion: Or'), 'default_weight' => 6),
    'criteria_phrase'   => array('title' => t('Advanced search criterion: Phrase'), 'default_weight' => 7),
    'criteria_negative' => array('title' => t('Advanced search criterion: Negative'), 'default_weight' => 8),
    'custom_paths'      => array('title' => t('Custom search paths'), 'default_weight' => 9),
    'submit_button'     => array('title' => t('Submit button'), 'default_weight' => 10),
  );
  if (count(array_filter(array_merge(variable_get('custom_search_' . $delta . 'node_types', array()), variable_get('custom_search_' . $delta . 'other', array())))))
    $elements['content_types'] = array('title' => t('Content Types'), 'default_weight' => 0);

  foreach ($elements as $element => $data) {
    $form['order']['custom_search_' . $delta . 'order'][$element] = array(
      '#title'  => $data['title'],
      '#weight' => variable_get('custom_search_' . $delta . $element . '_weight', $data['default_weight']),
    );
    $form['order']['custom_search_' . $delta . 'order'][$element]['sort'] = array(
      '#type'           => 'weight',
      '#default_value'  => variable_get('custom_search_' . $delta . $element . '_weight', $data['default_weight']),
      '#attributes'     => array('class' => 'sort-select sort-select-' . variable_get('custom_search_' . $delta . $element . '_region', 'block')),
    );
    $form['order']['custom_search_' . $delta . 'order'][$element]['region'] = array(
      '#type'           => 'select',
      '#options'        => array(
        'block' => t('Block'),
        'popup' => t('Popup')
      ),
      '#default_value'  => variable_get('custom_search_' . $delta . $element . '_region', 'block'),
      '#attributes'     => array('class' => 'region-select region-select-' . variable_get('custom_search_' . $delta . $element . '_region', 'block')),
    );
  }
  return $form;
}