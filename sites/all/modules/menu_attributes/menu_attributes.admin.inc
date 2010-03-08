<?php
// $Id: menu_attributes.admin.inc,v 1.1 2009/04/20 23:00:50 schoonzie Exp $

/**
 * @file
 * Creates the admin settings form for the Menu Attributes module.
 */

/**
 * Form builder function for module settings.
 */
function menu_attributes_admin() {
  
  // ID Attribute
  $form['menu_attributes_id'] = array(
    '#type' => 'fieldset',
    '#title' => t('ID Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_id']['menu_attributes_id_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the ID attribute'),
    '#default_value' => variable_get('menu_attributes_id_enable', 1)
  );

  // Name Attrinute
  $form['menu_attributes_name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_name']['menu_attributes_name_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Name attribute'),
    '#default_value' => variable_get('menu_attributes_name_enable', 1)
  );
  $form['menu_attributes_name']['menu_attributes_name_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Name Attribute Default'),
    '#default_value' => variable_get('menu_attributes_name_default', NULL),
    '#required' => FALSE
  );

  // Target Attribute
  $form['menu_attributes_target'] = array(
    '#type' => 'fieldset',
    '#title' => t('Target Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_target']['menu_attributes_target_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Target attribute'),
    '#default_value' => variable_get('menu_attributes_target_enable', 1)
  );
  $form['menu_attributes_target']['menu_attributes_target_default'] = array(
    '#type' => 'select',
    '#title' => t('Target Attribute Default'),
    '#default_value' => variable_get('menu_attributes_target_default', NULL),
    '#options' => array(
      '' => '<none> (i.e. same window)',
      '_blank' => 'New Window (_blank)',
      '_top' => 'Top Window (_top)',
      '_self' => 'Same Window (_self)',
      '_parent' => 'Parent Window (_parent)',
    ),
    '#required' => FALSE,
  );

  // Rel Attribute
  $form['menu_attributes_rel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rel Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_rel']['menu_attributes_rel_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Rel attribute'),
    '#default_value' => variable_get('menu_attributes_rel_enable', 1)
  );
  $form['menu_attributes_rel']['menu_attributes_rel_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Rel Attribute Default'),
    '#default_value' => variable_get('menu_attributes_rel_default', NULL),
    '#required' => FALSE
  );

  // Class Attribute
  $form['menu_attributes_class'] = array(
    '#type' => 'fieldset',
    '#title' => t('Class Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_class']['menu_attributes_class_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Class attribute'),
    '#default_value' => variable_get('menu_attributes_class_enable', 1)
  );
  $form['menu_attributes_class']['menu_attributes_class_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Class Attribute Default'),
    '#default_value' => variable_get('menu_attributes_class_default', NULL),
    '#required' => FALSE
  );

  // Style Attribute
  $form['menu_attributes_style'] = array(
    '#type' => 'fieldset',
    '#title' => t('Style Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_style']['menu_attributes_style_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Style attribute'),
    '#default_value' => variable_get('menu_attributes_style_enable', 1)
  );
  $form['menu_attributes_style']['menu_attributes_style_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Style Attribute Default'),
    '#default_value' => variable_get('menu_attributes_style_default', NULL),
    '#required' => FALSE
  );

  // Accesskey Attribute
  $form['menu_attributes_accesskey'] = array(
    '#type' => 'fieldset',
    '#title' => t('Accesskey Attribute'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['menu_attributes_accesskey']['menu_attributes_accesskey_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable setting the Accesskey attribute'),
    '#default_value' => variable_get('menu_attributes_accesskey_enable', 1)
  );
  $form['menu_attributes_accesskey']['menu_attributes_accesskey_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Accesskey Attribute Default'),
    '#default_value' => variable_get('menu_attributes_accesskey_default', NULL),
    '#required' => FALSE
  );

  $form = system_settings_form($form);

  return $form;
}
