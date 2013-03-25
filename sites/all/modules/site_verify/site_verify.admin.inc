<?php
// $Id: site_verify.admin.inc,v 1.14.2.3 2011/02/20 22:38:43 davereid Exp $

function site_verify_list() {
  $engines = site_verify_get_engines();

  $headers = array(
    t('Engine'),
    t('Meta tag'),
    t('File'),
    array('data' => t('Operations'), 'colspan' => 2),
  );
  $rows = array();

  $query = db_query("SELECT svid, engine, file, meta FROM {site_verify}");
  while ($record = db_fetch_object($query)) {
    $row_key = $engines[$record->engine]['key'] . $record->svid;
    $rows[$row_key] = array(
      $engines[$record->engine]['name'],
      $record->meta ? '<span title="' . check_plain(truncate_utf8($record->meta, 48)) . '">' . t('Yes') . '</spam>' : t('No'),
      $record->file ? l($record->file, $record->file) : t('None'),
      l(t('Edit'), "admin/build/site-verify/{$record->svid}/edit"),
      l(t('Delete'), "admin/build/site-verify/{$record->svid}/delete"),
    );
  }
  ksort($rows);

  if (!$rows) {
    $rows[] = array(array(
      'data' => t('No verifications available. <a href="@add">Add verification</a>.', array('@add' => url('admin/build/site-verify/add'))),
      'colspan' => 5,
    ));
  }

  $output = theme('table', $headers, $rows);
  return $output;
}

function site_verify_edit_form(&$form_state, $record = array(), $engine = NULL) {
  if (!isset($form_state['storage']['step'])) {
    $record += array(
      'svid' => NULL,
      'file' => '',
      'file_contents' => t('This is a verification page.'),
      'meta' => '',
      'engine' => $engine,
    );
    $form_state['storage']['record'] = $record;
    $form_state['storage']['step'] = $record['engine'] ? 2 : 1;
  }
  else {
    $record = $form_state['storage']['record'];
  }

  switch ($form_state['storage']['step']) {
    case 1:
      $engines = site_verify_get_engines();
      $options = array();
      foreach ($engines as $key => $engine) {
        $options[$key] = $engine['name'];
      }
      asort($options);

      // Ensure custom is always last.
      if (isset($options['custom'])) {
        $custom = $options['custom'];
        unset($options['custom']);
        $options['custom'] = $custom;
      }

      $form['engine'] = array(
        '#type' => 'select',
        '#title' => t('Search engine'),
        '#options' => $options,
      );
      $form['next'] = array(
        '#type' => 'submit',
        '#value' => t('Next'),
      );
      break;
    case 2:

      $form['svid'] = array(
        '#type' => 'value',
        '#value' => $record['svid'],
      );
      $form['engine'] = array(
        '#type' => 'value',
        '#value' => $record['engine']['key'],
      );
      $form['engine_name'] = array(
        '#type' => 'item',
        '#title' => t('Search engine'),
        '#value' => $record['engine']['name'],
      );
      $form['#engine'] = $record['engine'];

      $form['meta'] = array(
        '#type' => 'textfield',
        '#title' => t('Verification META tag'),
        '#default_value' => $record['meta'],
        '#description' => t('This is the full meta tag provided for verification. Note that this meta tag will only be visible in the source code of your <a href="@frontpage">front page</a>.', array('@front-page' => url('<front>'))),
        '#element_validate' => $record['engine']['meta_validate'],
        '#access' => $record['engine']['meta'],
        '#maxlength' => NULL,
      );

      $form['file_upload'] = array(
        '#type' => 'file',
        '#title' => t('Upload an existing verification file'),
        '#description' => t('If you have been provided with an actual file, you can simply upload the file.'),
        '#access' => $record['engine']['file'],
      );
      $form['file'] = array(
        '#type' => 'textfield',
        '#title' => t('Verification file'),
        '#default_value' => $record['file'],
        '#description' => t('The name of the HTML verification file you were asked to upload.'),
        '#element_validate' => $record['engine']['file_validate'],
        '#access' => $record['engine']['file'],
      );
      $form['file_contents'] = array(
        '#type' => 'textarea',
        '#title' => t('Verification file contents'),
        '#default_value' => $record['file_contents'],
        '#element_validate' => $record['engine']['file_contents_validate'],
        '#wysiwyg' => FALSE,
        '#access' => $record['engine']['file_contents'],
      );
      if (!variable_get('clean_url', 0)) {
        drupal_set_message(t('Using verification files will not work if <a href="@clean-urls">clean URLs</a> are disabled.', array('@clean-urls' => url('admin/settings/clean-url'))), 'error', FALSE);
        $form['file']['#disabled'] = TRUE;
        $form['file_contents']['#disabled'] = TRUE;
        $form['file_upload']['#disabled'] = TRUE;
      }

      if ($record['engine']['file']) {
        $form['#validate'][] = 'site_verify_validate_file';
        $form['#attributes'] = array('enctype' => 'multipart/form-data');
      }

      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 10,
      );
      break;
  }

  $form['cancel'] = array(
    '#value' => l(t('Cancel'), 'admin/build/site-verify'),
    '#weight' => 11,
  );

  return $form;
}

/**
 * Validation callback; save the uploaded file and check file name uniqueness.
 */
function site_verify_validate_file(&$form, &$form_state) {
  $values = &$form_state['values'];

  // Import the uploaded verification file.
  if ($file = file_save_upload('file_upload', array(), FALSE, FILE_EXISTS_REPLACE)) {
    $contents = @file_get_contents($file->filepath);
    file_delete($file->filepath);
    if ($contents === FALSE) {
      drupal_set_message(t('The verification file import failed, because the file %filename could not be read.', array('%filename' => $file->filename)), 'error');
    }
    else {
      $values['file'] = $file->filename;
      $values['file_contents'] = $contents;
      //drupal_set_message(t('The verification file <a href="@filename">@filename</a> was successfully imported.', array('@filename' => $file->filename)));
    }
  }

  if ($values['file']) {
    $existing_file = db_result(db_query("SELECT svid FROM {site_verify} WHERE LOWER(file) = LOWER('%s') AND svid <> %d", $values['file'], $values['svid']));
    if ($existing_file) {
      form_set_error('file', t('The file %filename is already being used in another verification.', array('%filename' => $values['file'])));
    }
  }
}

/**
 * Submission callback; send form to the next step or save the verification.
 */
function site_verify_edit_form_submit(&$form, &$form_state) {
  if ($form_state['storage']['step'] == 1) {
    // Send the form to step 2 (verification details).
    $form_state['storage']['record']['engine'] = site_verify_engine_load($form_state['values']['engine']);
    $form_state['storage']['step']++;
    $form_state['rebuild'] = TRUE;
  }
  else {
    // Save the verification to the database.
    if ($form_state['values']['svid']) {
      drupal_write_record('site_verify', $form_state['values'], array('svid'));
    }
    else {
      drupal_write_record('site_verify', $form_state['values']);
    }

    drupal_set_message(t('Verification saved.'));
    $form_state['storage'] = $form_state['rebuild'] = FALSE;
    $form_state['redirect'] = 'admin/build/site-verify';

    // The menu needs to be rebuilt if the page URL has changed or reset.
    variable_set('menu_rebuild_needed', TRUE);

    // Also clear front page caches.
    cache_clear_all(url('<front>', array('absolute' => TRUE)), 'cache_page');
    cache_clear_all(url(variable_get('site_frontpage', 'node'), array('absolute' => TRUE)), 'cache_page');
  }
}

function site_verify_delete_form($form_state, $record) {
  $form['record'] = array(
    '#type' => 'value',
    '#value' => $record,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete the site verification for %engine?', array('%engine' => $record['engine']['name'])),
    'admin/build/site-verify',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function site_verify_delete_form_submit($form, &$form_state) {
  $record = $form_state['values']['record'];
  db_query("DELETE FROM {site_verify} WHERE svid = %d", $record['svid']);
  drupal_set_message(t('Verification for %engine has been deleted.', array('%engine' => $record['engine']['name'])));
  watchdog('site_verify', 'Verification for %engine deleted.', array('%engine' => $record['engine']['name']), WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/build/site-verify';
}

function site_verify_validate_meta_google($element, &$form_state) {
  $value = strtolower(trim($element['#value']));
  if ($value != '' && !preg_match('%\A<meta name="verify-v1" content="[\S]+" />\Z%', $value)) {
    form_error($element, t('Invalid verification meta tag.'));
  }
}

function site_verify_validate_page_google($element, &$form_state) {
  $value = strtolower(trim($element['#value']));
  if ($value != '' && !preg_match('%\Agoogle[\da-f]+\.html\Z%', $value)) {
    form_error($element, t('Invalid verification file.'));
  }
}
