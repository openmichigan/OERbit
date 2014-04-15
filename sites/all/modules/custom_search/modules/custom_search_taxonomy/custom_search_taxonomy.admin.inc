<?php

/**
 * @file
 * Admin settings for custom search taxonomy
 */

/**
 * Implementation of hook_help().
 */
function custom_search_taxonomy_help($path, $arg) {
  switch ($path) {
    case 'admin/settings/custom_search/taxonomy':
      $output = t('Select the vocabularies to present as search options in the search block. If none is selected, no selector will be displayed.');
    break;
  }
  return $output;
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
      if (module_exists('hs_taxonomy')) $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector']['#options']['hierarchical_select'] = t('Hierarchical selector');
      $form[$voc->name]['custom_search_voc' . $voc->vid . '_selector_depth'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Depth'),
        '#size'           => 2,
        '#default_value'  => variable_get('custom_search_voc' . $voc->vid . '_selector_depth', 0),
        '#description'    => t('Define the maximum depth of terms being displayed. The default value is "0" which disables the limit.'),
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
