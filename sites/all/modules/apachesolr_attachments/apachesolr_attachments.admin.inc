<?php

/**
 * @file
 *   Provides a file attachment search implementation for use with the Apache Solr module
 */

//apachesolr_clear_last_index('apachesolr_attachments');

function apachesolr_attachments_admin_page() {
  $output = '';
  $output .= drupal_get_form('apachesolr_attachments_settings');
  $output .= drupal_get_form('apachesolr_attachments_delete_index_form');
  return $output;
}

/**
 * Displays the Attachment Settings Form.
*/
function apachesolr_attachments_settings() {
  $default = implode(' ', apachesolr_attachments_default_excluded());
  $form['apachesolr_attachment_excluded_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Excluded file extensions'),
    '#default_value' => variable_get('apachesolr_attachment_excluded_extensions', $default),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('File extensions that are excluded from indexing. Separate extensions with a space and do not include the leading dot. Extensions are internally mapped to a MIME type, so it is not necessary to put variations that map to the same type (e.g. tif is sufficient for tif and tiff)'),
  );
  $form['apachesolr_attachments_exclude_types'] = array(
    '#type' => 'radios',
    '#title' => t('Exclude files attached to a node of a type excluded by Apache Solr Search'),
    '#options' => array('0' => t('No'), '1' => t('Yes')),
    '#default_value' => variable_get('apachesolr_attachments_exclude_types', 1),
  );
  $form['apachesolr_attachment_extract_using'] = array(
    '#type' => 'radios',
    '#title' => t('Extract using'),
    '#options' => array(
      'tika' => t('Tika (local java application)'),
      'solr' => t('Solr (remote server)'),
    ),
    '#description' =>  t("Extraction will be faster if run locally using tika."),
    '#default_value' => variable_get('apachesolr_attachment_extract_using', 'tika'),
  );
  $form['apachesolr_attachments_tika_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Tika directory path'),
    '#size' => 80,
    '#maxlength' => 100,
    '#description' =>  t("The full path to the tika directory. All library jars must be in the same directory. If on Windows, use forward slashes in the path."),
    '#default_value' => variable_get('apachesolr_attachments_tika_path', ''),
  );
  $form['apachesolr_attachments_tika_jar'] = array(
    '#type' => 'textfield',
    '#title' => t('Tika jar file'),
    '#size' => 20,
    '#description' =>  t("The name of the tika CLI application jar file, e.g. tika-0.3.jar or tika-app-0.4.jar."),
    '#default_value' => variable_get('apachesolr_attachments_tika_jar', 'tika-0.3.jar'),
  );
  $form['apachesolr_attachments-cron-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['apachesolr_attachments-cron-settings']['apachesolr_attachments_cron_limit'] = array(
    '#type' => 'select',
    '#title' => t('Maximum number of nodes to examine'),
    '#default_value' => variable_get('apachesolr_attachments_cron_limit', 100),
    '#options' => drupal_map_assoc(array(10, 20, 50, 100, 200)),
  );
  $form['apachesolr_attachments-cron-settings']['apachesolr_attachements_cron_time_limit'] = array(
    '#type' => 'select',
    '#title' => t('Maximum time to expend (sec)'),
    '#default_value' => variable_get('apachesolr_attachements_cron_time_limit', 15),
    '#options' => drupal_map_assoc(array(5, 10, 15, 20, 25, 30, 45, 60)),
  );

  $form = system_settings_form($form);
  $form['#validate'][] = 'apachesolr_attachments_settings_validate';
  $form['#submit'][] = 'apachesolr_attachments_settings_submit';
  return $form;
}

function apachesolr_attachments_settings_validate($form, &$form_state) {
  if ($form_state['values']['apachesolr_attachment_extract_using'] == 'tika') {
    $path = realpath($form_state['values']['apachesolr_attachments_tika_path']);
    if (!file_exists($path . '/' . $form_state['values']['apachesolr_attachments_tika_jar'])) {
      form_set_error('apachesolr_attachments_tika_path', t('Tika jar file not found at this path.'));
    }
  }
}

function apachesolr_attachments_settings_submit($form, &$form_state) {
  // Delete this so it's rebuilt.
  variable_del('apachesolr_attachment_excluded_mime');
  drupal_set_message(t('If you changed the allowed file extensions, you may need to delete and re-index all attachments.'));
}

/**
 * Create a form for deleting the contents of the Solr index.
 */
function apachesolr_attachments_delete_index_form() {
  $form = array();
  $form['markup'] = array(
    '#prefix' => '<h3>',
    '#value' => t('Index and cache controls'),
    '#suffix' => '</h3>',
  );
  $form['reindex'] = array(
    '#type' => 'submit',
    '#value' => t('Re-index all files'),
    '#submit' => array('apachesolr_attachments_reindex_submit'),
  );
  $form['reindex-desc'] = array(
    '#type' => 'item',
    '#description' => t('Re-indexing will add all file text to the index again (overwriting the index), but existing text in the index will remain searchable.'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete files from index'),
    '#submit' => array('apachesolr_attachments_delete_index_submit'),
  );
  $form['delete-desc'] = array(
    '#type' => 'item',
    '#description' => t('Deletes all of the files in the Solr index and reindexes them.  This may be needed if you have changed the allowed file extensions,if your index is corrupt, or if you have installed a new schema.xml.'),
  );
  $form['clear-cache'] = array(
    '#type' => 'submit',
    '#value' => t('Delete cached file text'),
    '#submit' => array('apachesolr_attachments_delete_cache_submit'),
  );
  $form['cache-desc'] = array(
    '#type' => 'item',
    '#description' => t('Deletes the local cache of extacted text from files. This will cause slower performance when reindexing since text must be re-extracted.'),
  );
  return $form;
}

/**
 * Submit function for the "Re-index all content" button
 * @see apachesolr_delete_index_form()
 *
 */
function apachesolr_attachments_reindex_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/settings/apachesolr/attachments/confirm/reindex';
}

function apachesolr_attachments_delete_index_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/settings/apachesolr/attachments/confirm/delete';
}

function apachesolr_attachments_delete_cache_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/settings/apachesolr/attachments/confirm/clear-cache';
}

function apachesolr_attachments_confirm($form_state, $operation) {
  $form = array();
  $form['operation'] = array(
    '#type' => 'value',
    '#value' => $operation,
  );
  switch ($operation) {
    case 'reindex':
      $text = t('Are you sure you want to re-index the text of all file attachments?');
      break;
    case 'delete':
      $text = t('Are you sure you want to delete and re-index the text of all file attachments?');
      break;
    case 'clear-cache':
      $text = t('Are you sure you want to delete the cache of extracted text from file attachments?');
      break;
  }
  return confirm_form($form, $text, 'admin/settings/apachesolr/attachments', NULL, t('Confirm'), t('Cancel'));
}

function apachesolr_attachments_confirm_submit($form, &$form_state) {
  switch ($form_state['values']['operation']) {
    case 'delete':
      if (apachesolr_attachments_delete_index()) {
        drupal_set_message(t('File text has been deleted from the Apache Solr index. You must now <a href="!url">run cron</a> until all files have been re-indexed.', array('!url' => url('admin/reports/status/run-cron', array('query' => array('destination' => 'admin/settings/apachesolr/index'))))));
      }
      else {
        if (module_exists('dblog')) {
          drupal_set_message(t('Could not delete file text from the Apache Solr index. Check <a href="!url">recent log messages</a>.', array('!url' => url('admin/reports/dblog'))));
        }
        else {
          drupal_set_message(t('Could not delete file text from the Apache Solr index.'));
        }
      }
      break;
    case 'reindex':
      apachesolr_clear_last_index('apachesolr_attachments');
      drupal_set_message(t('All file attachments will be re-indexed.'));
      break;
    case 'clear-cache':
      db_query("DELETE FROM {apachesolr_attachments_files} WHERE removed = 0");
      drupal_set_message(t('The local cache of extracted text has been deleted.'));
      break;
  }
  $form_state['redirect'] = 'admin/settings/apachesolr/attachments';
}

function apachesolr_attachments_delete_index() {
  try {
    $solr = apachesolr_get_solr();
    $solr->deleteByQuery("entity:file AND hash:". apachesolr_site_hash());
    $solr->commit();
    apachesolr_index_updated(time());
    apachesolr_clear_last_index('apachesolr_attachments');
    return TRUE;
  }
  catch (Exception $e) {
    // Shortened project name because the watchdog limits type to 16 characters.
    watchdog('ApacheSolrAttach', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
  }
  return FALSE;
}

/**
 * Indexing-related functions
 */

/**
 * Callback for apachesolr_index_nodes().
 *
 * Adds a document for each indexable file attachment for the given node ID.
 */
function apachesolr_attachments_add_documents(&$documents, $nid, $namespace = 'apachesolr_attachments') {
  $node = node_load($nid, NULL, TRUE);
  if (!empty($node->nid)) {

    $hash = apachesolr_site_hash();

    // Let any module exclude this node from the index.
    $build_document = TRUE;
    foreach (module_implements('apachesolr_node_exclude') as $module) {
      $exclude = module_invoke($module, 'apachesolr_node_exclude', $node, $namespace);
      if (!empty($exclude)) {
        $build_document = FALSE;
      }
    }

    if ($build_document) {
      // Since there is no notification for an attachment being unassociated with a
      // node (but that action will trigger it to be indexed again), we check for
      // fids that were added before but no longer present on this node.

      $fids = array();
      $result = db_query("SELECT fid FROM {apachesolr_attachments_files} WHERE nid = %d", $node->nid);
      while ($row = db_fetch_array($result)) {
        $fids[$row['fid']] = $row['fid'];
      }

      $files = apachesolr_attachments_get_indexable_files($node);

      // Find deleted files.
      $missing_fids = array_diff_key($fids, $files);
      if ($missing_fids) {
        db_query("UPDATE {apachesolr_attachments_files} SET removed = 1 WHERE fid IN (". db_placeholders($missing_fids) .")", $missing_fids);
      }
      $new_files = array_diff_key($files, $fids);
      // Add new files.
      foreach ($new_files as $file) {
        db_query("INSERT INTO {apachesolr_attachments_files} (fid, nid, removed, sha1) VALUES (%d, %d, 0, '')", $file->fid, $node->nid);
      }
      foreach ($files as $file) {
        $text = apachesolr_attachments_get_attachment_text($file);

        if ($text) {
          $document = new Apache_Solr_Document();
          // A single file might be attached to multiple nodes.
          $document->id = apachesolr_document_id($file->fid .'-'. $node->nid, 'file');
          $document->url = file_create_url($file->filepath);
          $document->path = $file->filepath;
          $document->hash = $hash;
          $document->entity = 'file';
          $document->site = url(NULL, array('absolute' => TRUE));
          $document->nid = $node->nid;
          $document->title = $file->filename;
          $document->created = apachesolr_date_iso($file->timestamp);
          $document->changed = $document->created;
          $document->status = $node->status;
          $document->sticky = $node->sticky;
          $document->promote = $node->promote;
          $document->uid = $node->uid;
          $document->name = $node->name;
          if (empty($node->language)) {
            // 'und' is the language-neutral code in Drupal 7.
            $document->language = 'und';
          }
          else {
            $document->language = $node->language;
          }
          $document->body = $file->filename .' '. apachesolr_clean_text($file->description) .' '. $text;

          $document->ss_filemime = $file->filemime;
          $document->ss_file_node_title = apachesolr_clean_text($node->title);
          $document->ss_file_node_url = url('node/' . $node->nid, array('absolute' => TRUE));

          apachesolr_add_taxonomy_to_document($document, $node);

          // Let modules add to the document.
          foreach (module_implements('apachesolr_update_index') as $module) {
            $function = $module .'_apachesolr_update_index';
            $function($document, $node, $namespace);
          }
          drupal_alter('apachesolr_attachment_index', $document, $node, $file, $namespace);

          $documents[] = $document;
        }
        else {
          // Shortened project name because the watchdog limits type to 16 characters.
          watchdog('ApacheSolrAttach', 'Could not extract any indexable text from %filepath', array('%filepath' => $file->filepath), WATCHDOG_WARNING);
        }
      }
    }
  }
}

/**
 * Return all non-excluded file attachments for a particular node
 */
function apachesolr_attachments_get_indexable_files($node) {
  $files = array();

  if(!empty($node->files)) {
    $files = $node->files;
  }

  $fields = apachesolr_attachments_get_cck_file_fields();
  foreach ($fields as $field) {
    if(!empty($node->$field)) {
      $files = array_merge($files, $node->$field);
    }
  }
  $file_list = array();
  foreach ($files as $file) {
    // Some are arrays others are objects, treat them all as objects
    $file = (object) $file;
    // Some filefield-enabled nodes show up with an emtpy file array.
    if (!empty($file->fid) && apachesolr_attachments_allowed_mime($file->filemime)) {
      if (isset($file->data['description']) && !isset($file->description)) {
        $file->description = $file->data['description'];
      }
      $file_list[$file->fid] = $file;
    }
  }
  return $file_list;
}

function apachesolr_attachments_default_excluded() {
  $default = array('aif', 'art', 'avi', 'bmp', 'gif', 'ico', 'jpg', 'mov', 'mp3', 'mp4', 'mpg', 'oga', 'ogv', 'png', 'psd', 'ra', 'ram', 'rgb', 'tif',);
  return $default;
}

function apachesolr_attachments_allowed_mime($filemime) {

  $excluded = variable_get('apachesolr_attachment_excluded_mime', FALSE);
  if ($excluded === FALSE) {
    // Build the list of excluded MIME types.
    $excluded = array();
    $extensions = variable_get('apachesolr_attachment_excluded_extensions', FALSE);
    if ($extensions !== FALSE) {
      $extensions = explode(' ', $extensions);
    }
    else {
      $extensions = apachesolr_attachments_default_excluded();
    }
    foreach ($extensions as $ext) {
      $ext = trim($ext);
      if ($ext) {
        $mime = file_get_mimetype('dummy.' . $ext);
        $excluded[$mime] = 1;
      }
    }
    variable_set('apachesolr_attachment_excluded_mime', $excluded);
  }
  return empty($excluded[$filemime]);
}

/**
 * Return all CCK fields that are of type 'file'
 */
function apachesolr_attachments_get_cck_file_fields() {
  $file_fields = array();
  if(module_exists('filefield')) {
    $fields = content_fields();
    foreach($fields as $key => $values){
      if($values['type'] == 'filefield') {
        $file_fields[] = $key;
      }
    }
  }
  return $file_fields;
}

/**
 * Parse the attachment getting just the raw text.
 *
 * @throws Exception
 */
function apachesolr_attachments_get_attachment_text($file) {
  // Any down-side to using realpath()?
  $filepath = realpath($file->filepath);
  // Check that we have a valid filepath.
  if (!($filepath) || !is_file($filepath)) {
    return FALSE;
  }

  // No need to use java for plain text files.
  if ($file->filemime == 'text/plain' || $file->filemime == 'text/x-diff') {
    $text = file_get_contents($filepath);
    // TODO - try to detect encoding and convert to UTF-8.
    // Strip bad control characters.
    $text = iconv("UTF-8", "UTF-8//IGNORE", $text);
    $text = trim(apachesolr_clean_text($text));
    return $text;
  }

  $sha1 = sha1_file($filepath);
  if ($sha1 === FALSE) {
    return FALSE;
  }

  $cached = db_fetch_array(db_query("SELECT * FROM {apachesolr_attachments_files} WHERE fid = %d", $file->fid));

  if (!is_null($cached['body']) && ($cached['sha1'] == $sha1)) {
    // No need to re-extract.
    return $cached['body'];
  }

  if (variable_get('apachesolr_attachment_extract_using', 'tika') == 'tika') {
    $text = apachesolr_attachments_extract_using_tika($filepath);
  }
  else {
    // Extract using Solr.
    try {
      list($text, $metadata) = apachesolr_attachments_extract_using_solr($filepath);
    }
    catch (Exception $e) {
      // Exceptions from Solr may be transient, or indicate a problem with a specific file.
      // Shortened project name because the watchdog limits type to 16 characters.
      watchdog('ApacheSolrAttach', "Exception occured sending %filepath to Solr\n!message", array('%filepath' => $file->filepath, '!message' => nl2br(check_plain($e->getMessage()))), WATCHDOG_ERROR);
      return '';
    }
  }
  // Strip bad control characters.
  $text = iconv("UTF-8", "UTF-8//IGNORE", $text);
  $text = trim(apachesolr_clean_text($text));
  // Save the extracted, cleaned text to the DB.
  db_query("UPDATE {apachesolr_attachments_files} SET sha1 = '%s', body = '%s' WHERE fid = %d", $sha1, $text, $file->fid);

  return $text;
}

/**
 * For a file path, try to extract text using a local tika jar.
 *
 * @throws Exception
 */
function apachesolr_attachments_extract_using_tika($filepath) {
  $tika_path = realpath(variable_get('apachesolr_attachments_tika_path', ''));

  $tika = realpath($tika_path .'/'. variable_get('apachesolr_attachments_tika_jar', 'tika-0.3.jar'));
  if (!($tika) || !is_file($tika)) {
    throw new Exception(t('Invalid path or filename for tika application jar.'));
  }

  $java = variable_get('apachesolr_attachments_java', 'java');
  // By default force UTF-8 output.
  $java_opts = ' ' . variable_get('apachesolr_attachments_java_opts', '-Dfile.encoding=UTF8');
  $cmd = escapeshellcmd($java . $java_opts) .' -cp '. escapeshellarg($tika_path) .' -jar '. escapeshellarg($tika) .' -t '. escapeshellarg($filepath);

  // Add a work-around for a MAMP bug + java 1.5.
  if (strpos(ini_get('extension_dir'), 'MAMP/')) {
    $cmd = 'export DYLD_LIBRARY_PATH=""; '. $cmd;
  }

  return shell_exec($cmd);
}

/**
 * For a file path, try to extract text using Solr 1.4.
 *
 * @throws Exception
 */
function apachesolr_attachments_extract_using_solr($filepath) {
  // Extract using Solr.
  // We allow Solr to throw exceptions - they will be caught
  // by apachesolr.module.
  $solr = apachesolr_get_solr();
  $filename = basename($filepath);
  $params = array(
    'resource.name' => $filename,
    'extractFormat' => 'text', // Matches the -t command for the tika CLI app.
  );
  // Construct a multi-part form-data POST body in $data.
  $boundary = '--' . md5(uniqid(time()));
  $data = "--{$boundary}\r\n";
  // The 'filename' used here becomes the property name in the response.
  $data .= 'Content-Disposition: form-data; name="file"; filename="extracted"';
  $data .= "\r\nContent-Type: application/octet-stream\r\n\r\n";
  $data .= file_get_contents($filepath);
  $data .= "\r\n--{$boundary}--\r\n";
  $headers = array('Content-Type' => 'multipart/form-data; boundary=' . $boundary);
  $response = $solr->makeServletRequest(EXTRACTING_SERVLET, $params, 'POST', $headers, $data);
  return array($response->extracted, $response->extracted_metadata);
}

