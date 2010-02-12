<?php // $Id: accessible_content.admin.inc,v 1.1.2.1 2010/01/09 20:42:28 kevee Exp $

/**
*  @file The administration forms
*/


/**
*  The administration form
*/
function accessible_content_admin_form() {
  $form = array();
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $error_types = array('severe', 'moderate', 'suggestion');

  $form['ac_error_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display tests even if there are no errors'),
    '#description' => t('If checked, this will display even tests in reports which had no errors.'),
    '#default_value' => variable_get('ac_error_display', 0),
  );

  $form['ac_user_interface'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Interface'),
  );
  foreach ($error_types as $type) {
    $form['ac_user_interface']['ac_'. $type] = array(
      '#type' => 'fieldset',
      '#title' => t('!type Errors', array('!type' => ucfirst($type))),
      '#collapsible' => TRUE,
    );

    $form['ac_user_interface']['ac_'. $type]['ac_preview_'. $type] = array(
    '#value' => theme('image',
            variable_get('ac_ui_icon_'. $type,
                drupal_get_path('module', 'accessible_content')
                .'/images/test-demo-'. $type .'.png'),
                t('Preview of an icon for !type errors', array('!type' => $type))),
    );

    $form['ac_user_interface']['ac_'. $type]['ac_ui_icon_'. $type] = array(
      '#type' => 'textfield',
      '#title' => t('Path to icon for !type errors', array('!type' => $type)),
      '#description' => t('When viewing highlighted errors, apply this class to !type errors.', array('!type' => $type)),
      '#default_value' => variable_get('ac_ui_icon_'. $type, drupal_get_path('module', 'accessible_content') .'/images/test-demo-'. $type .'.png'),
    );

    $form['ac_user_interface']['ac_'. $type]['ac_icon_upload_'. $type] = array(
      '#type' => 'file',
      '#title' => t('Upload a custom icon for !type errors', array('!type' => $type)),
      '#size' => 40,
    );

    $form['ac_user_interface']['ac_'. $type]['ac_ui_class_'. $type] = array(
      '#type' => 'textfield',
      '#title' => t('Class to apply to !type errors', array('!type' => $type)),
      '#description' => t('When viewing highlighted errors, apply this class to !type errors.', array('!type' => $type)),
      '#default_value' => variable_get('ac_ui_class_'. $type, 'accessibility-error-'. $type),
    );

  }
  $form['submit'] = array('#type' => 'submit', '#value' => 'Save Settings');
  return $form;
}

/**
*  The form submit action for the admin form
*/
function accessible_content_admin_form_submit($form, $form_state) {
  $error_types = array('severe', 'moderate', 'suggestion');
  file_check_directory(file_create_path('accessible_content'), FILE_CREATE_DIRECTORY);
  variable_set('ac_error_display', $form_state['values']['ac_error_display']);
  foreach ($error_types as $type) {
    $file = file_save_upload('ac_icon_upload_'. $type, array(), file_create_path('accessible_content'));
    if ($file) {
      variable_set('ac_ui_icon_'. $type, $file->filepath);
  }
  else {
    variable_set('ac_ui_icon_'. $type, $form_state['values']['ac_ui_icon_'. $type]);
  }
  variable_set('ac_ui_class_'. $type, $form_state['values']['ac_ui_class_'. $type]);
  }
}

/**
*  The form for checking existing content in the admin section
*/
function accessible_content_admin_check_form() {
  $form = array();
  
  $types = array();
  
  foreach (node_get_types() as $type => $info) {
    if (variable_get($type .'_ac_enable', 0)) {
      $types[$type] = $info->name;
    }
  }
  
  $form['instructions'] = array(
    '#value' => t('Use this form to check content that has not been run through accessibility testing. Content is usually only checked for accessibility when the node is created or updated, so this page lets you update batches of content that already exist'),
  );
  
  $form['node_type'] = array(
    '#type' => 'radios',
    '#title' => t('The type of node to check'),
    '#options' => $types,
    '#required' => TRUE,
  );
  
  $form['submit'] = array('#type' => 'submit', '#value' => t('Check content'));
  
  return $form;
}

/**
*  Form submit action for the admin check form. This generates a progress bar
*
*/
function accessible_content_admin_check_form_submit($form, &$form_state) {
  $nodes = db_query('SELECT n.nid, n.title FROM {node} n WHERE n.nid NOT IN '.
             '(SELECT act.nid FROM {accessible_content_node_totals} act '.
           'LEFT JOIN {node} n2 ON n2.nid = act.nid WHERE n2.type = "%s") '.
           'AND n.type = "%s" ORDER BY n.nid',
           $form_state['values']['node_type'],
           $form_state['values']['node_type']);
  $operations = array();
  while ($node = db_fetch_object($nodes)) {
    $operations[] = array('accessible_content_admin_check_node', array($node->nid));
  }
  if (count($operations) == 0) {
    drupal_set_message('All nodes of this type have already been checked for accessibility');
    return NULL;
  }
  $batch = array(
    'title' => t('Checking existing '. check_plain($form_state['values']['node_type']) .' content'),
    'operations' => $operations,
    'finished' => 'accessible_content_admin_check_form_batch_completed',
    'file' => drupal_get_path('module', 'accessible_content') .'/accessible_content.admin.inc',
  );
  batch_set($batch);
  $form_state['redirect'] = 'admin/settings/accessible_content/check';
}

/**
*  Batch callback for checking existing content
*/
function accessible_content_admin_check_form_batch_completed($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One post checked for accessibility.', '@count post checked for accessibility.');
  }
  else {
    $message = t('An error occurred while checking existing content');
  }
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  foreach ($results as $result) {
    $items[] = t('Checked node %title.', array('%title' => $result));
  }
  $_SESSION['ac_batch_results'] = $items;
}

/**
*  Batch operation to check the content of a node
*/
function accessible_content_admin_check_node($nid, &$context) {
  $node = node_load($nid, NULL, TRUE);
  $context['message'] = 'Processing '. $node->title;
  $context['results'][] = $node->nid .' : '. $node->title;
  $fields = variable_get('ac_field', array());
  $body = (variable_get($node->type .'_ac_after_filter', 0))
          ? check_markup($node->body)
          : $node->body;
  $results['body'] = accessible_content_check_string($body,
        variable_get($node->type .'_accessibility_guideline_nid', 0),
        'AccessibleContent',
        variable_get($node->type .'_ac_ignore_cms_off', 1)
        );
  _accessible_content_node_form_submit_error($results, 'Body', $node->type);
  foreach ($fields as $fieldname => $check) {
    if ($check && property_exists($node, $fieldname)) {
      $content_field = content_fields($fieldname);
      if ($content_field['text_processing']) {
        foreach ($node->$fieldname as $k => $field) {
          $results[$fieldname] = accessible_content_check_string($field['value'],
                        variable_get($node->type .'_accessibility_guideline_nid', 0),
                        'AccessibleContent',
                        variable_get($node->type .'_ac_ignore_cms_off', 1));
        }
      }
    }
  }
  $node->accessibility_results = $results;
  node_save($node);
}