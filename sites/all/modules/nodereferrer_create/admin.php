<?php
// $Id: admin.php,v 1.1.2.3 2008/10/10 13:02:52 anselmheaton Exp $

/**
 * Implementation of hook_menu() for admin pages
 */
function _nodereferrer_create_admin_menu() {
  $items = array();
  
  // Admin page
  $items['admin/settings/ndrfc'] = array(
    'title' => 'Nodereferrer create',
    'description' => 'Lets you create/link items of related content',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('nodereferrer_create_callback_admin'),
    'access arguments' => array('administer nodereferrer create'),
    'type' => MENU_NORMAL_ITEM,
  );
  
  return $items;
}

/**
 * Admin page - set the mode and the content types to alter
 */
function nodereferrer_create_callback_admin() {

  $form = array();
  
  /* Main settings */
  
  $form['nodereferrer_create_show_on_nodereferrer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show menu items for nodereferrer fields'),
    '#description' => t('If this is checked, the create related items will include content linked via nodereferrer fields.'),
    '#default_value' => variable_get('nodereferrer_create_show_on_nodereferrer', 1),
  );
  
  $form['nodereferrer_create_show_on_nodereference'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show menu items for nodereference fields'),
    '#description' => t('If this is checked, the create related items will include content linked via nodereference fields. This does not work for nodereference fields that use views.'),
    '#default_value' => variable_get('nodereferrer_create_show_on_nodereference', 1),
  );
  
  $form['nodereferrer_create_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create the add menu inline when possible'),
    '#description' => t('If this is checked, when the field is displayed on the page then the add menu will be added next to the field'),
    '#default_value' => variable_get('nodereferrer_create_inline', 1),
  );

  $form['nodereferrer_create_javascript'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use a javascript popup rather than a redirect for the local task'),
    '#description' => t('If this is checked, when the local task to create content is clicked, node referrer create will attemp to make the form popup rather than use a redirect.'),
    '#default_value' => variable_get('nodereferrer_create_javascript', 1),
  );
  
  /* Access settings */
  $form['nodereferrer_create_access_group'] = array(
    '#type' => 'fieldset',
    '#collapsible' => true,
    '#collapsed' => true,
    '#title' => t('Access settings'),
  );
  
  $form['nodereferrer_create_access_group']['nodereferrer_create_access_if_local_node'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only show menus if user can edit current node'),
    '#description' => t('By default, Nodereferrer Create will show \'create related content\' menus if the 
                         user has the access rights to create the related content - regardless of the user\'s
                         access rights to the current node. If this is checked, Nodereferrer Create will
                         only show the \'create related content\' menus if the user has the access rights
                         to the related content AND to the current node. This is cosmetic only - the user
                         can always create the related content some other way.'),
    '#default_value' => variable_get('nodereferrer_create_access_if_local_node', 0),
  );
  
  /* Syncronisation settings */
  
  $form['nodereferrer_create_sync_group'] = array(
    '#type' => 'fieldset',
    '#collapsible' => true,
    '#collapsed' => true,
    '#title' => t('Synchronisation settings'),
  );
  
  $form['nodereferrer_create_sync_group']['nodereferrer_create_sync_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Synchronise title'),
    '#description' => t('If this is checked, when creating related content the title will default to that of the current node'),
    '#default_value' => variable_get('nodereferrer_create_sync_title', 0),
  );

  $form['nodereferrer_create_sync_group']['nodereferrer_create_sync_taxonomy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Synchronise taxonomy (not implemented)'),
    '#description' => t('If this is checked, when creating related content the taxonomy will default to that of the current node. This is not currently implemented.'),
    '#default_value' => variable_get('nodereferrer_create_sync_taxonomy', 0),
  );
  
  $form['nodereferrer_create_sync_group']['nodereferrer_create_sync_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Rules to synchronise other fields. Advanced users only.'),
    '#description' => t('This will copy the value of the source field to the default value of the destination field. Note that these are not always formatted in the same way, and as such this may not work. Use with caution. Format is one rule per line as : "source_field : destination_field". For instance to synchronise the title field to a CCK field named "parent_title" you\'d write "title : field_parent_title". Please only use this if you know what you are doing, no support will be given.'),
    '#default_value' => variable_get('nodereferrer_create_sync_fields', ''),
  );
  
  
  /* JS effect settings */
  
  $form['nodereferrer_create_effect_group'] = array(
    '#type' => 'fieldset',
    '#collapsible' => true,
    '#collapsed' => true,
    '#title' => t('Javascritp effect settings'),
  );

  $form['nodereferrer_create_effect_group']['nodereferrer_create_effect'] = array(
    '#type' => 'select',
    '#title' => t('Type of effect to use'),
    '#options' => array('show_hide' => t('Show/Hide'), 'slide' => t('Slide in/out')),
    '#default_value' => variable_get('nodereferrer_create_effect', 'slide'),
  );

  $form['nodereferrer_create_effect_group']['nodereferrer_create_effect_speed'] = array(
    '#type' => 'select',
    '#title' => t('Where applicable, speed of the effect'),
    '#options' => array('normal' => t('Normal'), 'slow' => t('Slow'), 'fast' => t('Fast')),
    '#default_value' => variable_get('nodereferrer_create_effect_speed', 'normal'),
  );
  
  /* Label settings */
  
  $form['nodereferrer_create_labels'] = array(
    '#type' => 'fieldset',
    '#collapsible' => true,
    '#collapsed' => true,
    '#title' => t('Labels'),
  );
  
  $form['nodereferrer_create_labels']['nodereferrer_create_localtask_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Local task label for creating new content'),
    '#default_value' => variable_get('nodereferrer_create_localtask_label', 'Create related content'),
    '#description' => t('This is the label of the local task used to create related content'),
  );
  
  $form['nodereferrer_create_labels']['nodereferrer_create_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for creating new referrers'),
    '#default_value' => variable_get('nodereferrer_create_label', 'Create new @type'),
    '#description' => t('This is the text generated in the menus to create a new referrer'),
  );
  
  $form['nodereferrer_create_labels']['nodereferrer_create_add_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for adding to existing referrers'),
    '#default_value' => variable_get('nodereferrer_create_add_label', 'Add to existing @type'),
    '#description' => t('This is the text generated in the menus to add to an existing referrer'),
  );

  $form['nodereferrer_create_labels']['nodereferrer_create_reference_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for creating a new referrence'),
    '#default_value' => variable_get('nodereferrer_create_reference_label', 'Create new @type'),
    '#description' => t('This is the text generated in the menus to create a new referrence'),
  );

  $form['nodereferrer_create_labels']['nodereferrer_create_reference_label_add'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for adding an existing referrence'),
    '#default_value' => variable_get('nodereferrer_create_reference_label_add', 'Add existing @type'),
    '#description' => t('This is the text generated in the menus to add an existing referrence'),
  );

  $form['nodereferrer_create_labels']['nodereferrer_create_reference_label_single'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for creating a new referrence to replace existing one'),
    '#default_value' => variable_get('nodereferrer_create_reference_label_single', 'Replace with new @type'),
    '#description' => t('This is the text generated in the menus to create a new referrence to replace the existing one'),
  );
        
  $form['nodereferrer_create_labels']['nodereferrer_create_reference_label_add_single'] = array(
    '#type' => 'textfield',
    '#title' => t('Label for replacing referrence with an existing one'),
    '#default_value' => variable_get('nodereferrer_create_reference_label_add_single', 'Replace with existing @type'),
    '#description' => t('This is the text generated in the menus to replace the referrence with an existing one'),
  );
  
  return system_settings_form($form);
}
