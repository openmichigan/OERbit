<?php

/**
 * @file
 * Webform module file component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_file() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'mandatory' => 0,
    'pid' => 0,
    'weight' => 0,
    'extra' => array(
      'filtering' => array(
        'types' => array('gif', 'jpg', 'png'),
        'addextensions' => '',
        'size' => 800,
      ),
      'savelocation' => '',
      'width' => '',
      'title_display' => 0,
      'description' => '',
      'attributes' => array(),
      'private' => FALSE,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_file() {
  return array(
    'webform_edit_file_extensions' => array(
      'arguments' => array('element' => NULL),
      'file' => 'components/file.inc',
    ),
    'webform_render_file' => array(
      'arguments' => array('element' => NULL),
      'file' => 'components/file.inc',
    ),
    'webform_display_file' => array(
      'arguments' => array('element' => NULL),
      'file' => 'components/file.inc',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_file($component) {
    $form = array();

    $form['validation']['size'] = array(
      '#type' => 'textfield',
      '#title' => t('Max upload size'),
      '#default_value' => $component['extra']['filtering']['size'],
      '#description' => t('Enter the max file size a user may upload (in KB).'),
      '#size' => 10,
      '#field_suffix' => t('KB'),
      '#parents' => array('extra', 'filtering', 'size'),
      '#element_validate' => array('_webform_edit_file_size_validate'),
      '#weight' => 1,
    );

    $form['validation']['extensions'] = array(
      '#element_validate' => array('_webform_edit_file_extensions_validate'),
      '#parents' => array('extra', 'filtering'),
      '#theme' => 'webform_edit_file_extensions',
      '#title' => t('Allowed file extensions'),
      '#weight' => 2,
    );

    // Find the list of all currently valid extensions.
    $current_types = isset($component['extra']['filtering']['types']) ? $component['extra']['filtering']['types'] : array();

    $types = array('gif', 'jpg', 'png');
    $form['validation']['extensions']['types']['webimages'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Web images'),
      '#options' => drupal_map_assoc($types),
      '#default_value' => array_intersect($current_types, $types),
    );

    $types = array('bmp', 'eps', 'tif', 'pict', 'psd');
    $form['validation']['extensions']['types']['desktopimages'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Desktop images'),
      '#options' => drupal_map_assoc($types),
      '#default_value' => array_intersect($current_types, $types),
    );

    $types = array('txt', 'rtf', 'html', 'odf', 'pdf', 'doc', 'docx', 'ppt', 'pptx', 'xls', 'xlsx', 'xml');
    $form['validation']['extensions']['types']['documents'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Documents'),
      '#options' => drupal_map_assoc($types),
      '#default_value' => array_intersect($current_types, $types),
    );

    $types = array('avi', 'mov', 'mp3', 'ogg', 'wav');
    $form['validation']['extensions']['types']['media'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Media'),
      '#options' => drupal_map_assoc($types),
      '#default_value' => array_intersect($current_types, $types),
    );

    $types = array('bz2', 'dmg', 'gz', 'jar', 'rar', 'sit', 'tar', 'zip');
    $form['validation']['extensions']['types']['archives'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Archives'),
      '#options' => drupal_map_assoc($types),
      '#default_value' => array_intersect($current_types, $types),
    );

    $form['validation']['extensions']['addextensions'] = array(
      '#type' => 'textfield',
      '#title' => t('Additional extensions'),
      '#default_value' => $component['extra']['filtering']['addextensions'],
      '#description' => t('Enter a list of additional file extensions for this upload field, separated by commas.<br /> Entered extensions will be appended to checked items above.'),
      '#size' => 20,
      '#weight' => 3,
    );

    $form['extra']['savelocation'] = array(
      '#type' => 'textfield',
      '#title' => t('Upload directory'),
      '#default_value' => $component['extra']['savelocation'],
      '#description' => t('Webform uploads are always saved in the site files directory. You may optionally specify a subfolder to store your files.'),
      '#weight' => 3,
      '#field_prefix' => file_directory_path() . '/webform/',
      '#element_validate' => array('_webform_edit_file_check_directory'),
      '#after_build' => array('_webform_edit_file_check_directory'),
    );
    $form['display']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $component['extra']['width'],
      '#description' => t('Width of the file field.') . ' ' . t('Leaving blank will use the default size.'),
      '#size' => 5,
      '#maxlength' => 10,
      '#weight' => 4,
      '#parents' => array('extra', 'width')
    );
    return $form;
}

/**
 * A Form API element validate function to check filesize is numeric.
 */
function _webform_edit_file_size_validate($element) {
  if (!empty($element['#value'])) {
    if (!is_numeric($element['#value']) || intval($element['#value']) != $element['#value']) {
      form_error($element, t('Max upload size must be a number in KB.'));
    }
  }
}

/**
 * A Form API after build and validate function.
 *
 * Ensure that the destination directory exists and is writable.
 */
function _webform_edit_file_check_directory($element) {
  $base_dir = file_directory_path() . '/webform';
  $base_success = file_check_directory($base_dir, FILE_CREATE_DIRECTORY);

  $destination_dir = $base_dir . '/' . $element['#value'];

  // Sanity check input to prevent use parent (../) directories.
  if (preg_match('/\.\.[\/\\\]/', $destination_dir . '/')) {
    form_error($element, t('The save directory %directory is not valid.', array('%directory' => $destination_dir)));
  }
  else {
    // Try to make the directory recursively before calling file_check_directory().
    // This may be removed in D7, as recusive is the default there.
    @mkdir($destination_dir, 0775, TRUE);
    $destination_success = file_check_directory($destination_dir, FILE_CREATE_DIRECTORY);

    if (!$base_success || !$destination_success) {
      form_error($element, t('The save directory %directory could not be created. Check that the webform files directory is writtable.', array('%directory' => $destination_dir)));
    }
  }

  return $element;
}

/**
 * A Form API element validate function.
 *
 * Change the submitted values of the component so that all filtering extensions
 * are saved as a single array.
 */
function _webform_edit_file_extensions_validate($element, &$form_state) {
  // Predefined types.
  $extensions = array();
  foreach (element_children($element['types']) as $category) {
    foreach (array_keys($element['types'][$category]['#value']) as $extension) {
      if ($element['types'][$category][$extension]['#value']) {
        $extensions[] = $extension;
      }
    }
  }

  // Additional types.
  $additional_extensions = explode(',', $element['addextensions']['#value']);
  foreach ($additional_extensions as $extension) {
    $clean_extension = drupal_strtolower(trim($extension));
    if (!empty($clean_extension) && !in_array($clean_extension, $extensions)) {
      $extensions[] = $clean_extension;
    }
  }

  form_set_value($element['types'], $extensions, $form_state);
}

/**
 * Output the list of allowed extensions as checkboxes.
 */
function theme_webform_edit_file_extensions($element) {
  drupal_add_js(drupal_get_path('module', 'webform') . '/js/webform-admin.js');
  drupal_add_css(drupal_get_path('module', 'webform') . '/css/webform-admin.css');

  // Format the components into a table.
  $rows = array();
  foreach (element_children($element['types']) as $filtergroup) {
    $row = array();
    $first_row = count($rows);
    if ($element['types'][$filtergroup]['#type'] == 'checkboxes') {
      $select_link = ' <a href="#" class="webform-select-link webform-select-link-' . $filtergroup . '">(' . t('select') . ')</a>';
      $row[] = $element['types'][$filtergroup]['#title'];
      $element['types'][$filtergroup]['#title'] = NULL;
      $row[] = array('data' => $select_link, 'width' => 40);
      $row[] = array('data' => drupal_render($element['types'][$filtergroup]), 'class' => 'webform-file-extensions webform-select-group-' . $filtergroup);
      $rows[] = array('data' => $row);
      unset($element['types'][$filtergroup]);
    }
  }

  // Add the row for additional types.
  $row = array();
  $title = $element['addextensions']['#title'];
  $element['addextensions']['#title'] = NULL;
  $row[] = array('data' => $title, 'colspan' => 2);
  $row[] = drupal_render($element['addextensions']);
  $rows[] = $row;

  $header = array(array('data' => t('Category'), 'colspan' => '2'), array('data' => t('Types')));

  // Create the table inside the form.
  $table = theme('table', $header, $rows, array('class' => 'webform-file-extensions'));
  $element['types']['table'] = array(
    '#value' => theme('form_element', $element, $table),
  );

  return drupal_render($element);
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_file($component, $value = NULL, $filter = TRUE) {
  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;

  // Normally every file component is given a unique ID based on its key.
  if (isset($component['nid'])) {
    $node = node_load($component['nid']);
    $form_key = implode('_', webform_component_parent_keys($node, $component));
  }
  // If being used as a default though, we don't yet have a form key.
  else {
    $form_key = 'default';
  }

  $element[$form_key] = array(
    '#type' => 'file',
    '#title' => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    //'#required' => $component['mandatory'], // Drupal core bug with required file uploads.
    '#description' => $filter ? _webform_filter_descriptions($component['extra']['description'], $node) : $component['extra']['description'],
    '#attributes' => $component['extra']['attributes'],
    '#tree' => FALSE, // file_check_upload assumes a flat $_FILES structure.
    '#element_validate' => array(
      '_webform_validate_file',
      '_webform_required_file',  // Custom required routine.
    ),
    '#pre_render' => array('webform_element_title_display'),
    '#translatable' => array('title', 'description'),
    '#webform_component' => $component,
  );
  $element['#webform_required'] = $component['mandatory'];
  $element['#webform_form_key'] = $form_key;
  $element['#weight'] = $component['weight'];
  $element['#theme'] = 'webform_render_file';
  $element['#title_display'] = $element[$form_key]['#title_display'];
  $element['#theme_wrappers'] = array('webform_element_wrapper');
  $element['#post_render'] = array('webform_element_wrapper');

  // Change the 'width' option to the correct 'size' option.
  if ($component['extra']['width'] > 0) {
    $element[$form_key]['#size'] = $component['extra']['width'];
  }

  // Add a hidden element to store the FID for new files.
  $element['_fid'] = array(
    '#type' => 'hidden',
    '#default_value' => '',
  );

  // Add a hidden element to store the FID for existing files.
  $element['_old'] = array(
    '#type' => 'hidden',
    '#value' => isset($value[0]) ? $value[0] : NULL,
  );

  return $element;
}

/**
 * Render a File component.
 */
function theme_webform_render_file($element) {
  // Add information about the existing file, if any.
  if (isset($element['#default_value'])) {
    $element['_fid']['#value'] = $element['#default_value'];
  }
  $value = $element['_fid']['#value'] ? $element['_fid']['#value'] : $element['_old']['#value'];

  if ($value && ($file = webform_get_file($value))) {
    $firstchild = array_shift(element_children($element));
    $element[$firstchild]['#suffix'] = ' ' . l(t('Download @filename', array('@filename' => webform_file_name($file->filepath))), webform_file_url($file->filepath)) . (isset($element['#suffix']) ? $element['#suffix'] : '');
    $element[$firstchild]['#description'] = '<div class="webform-newfile-message">' . t('Uploading a new file will replace the current file.') . '</div>' . (isset($element[$firstchild]['#description']) ? $element[$firstchild]['#description'] : '');
  }

  // Add the required asterisk.
  if ($element['#webform_required']) {
    $element[$element['#webform_form_key']]['#required'] = TRUE;
  }

  $output = '';
  foreach (element_children($element) as $key) {
    $output .= drupal_render($element[$key]);
  }
  return $output;
}

/**
 * A Form API element validate function.
 *
 * Fix Drupal core's handling of required file fields.
 */
function _webform_required_file($element, $form_state) {
  $component = $element['#webform_component'];
  $parents = $element['#array_parents'];
  array_pop($parents);
  $form_key = implode('_', $parents);

  // Do not validate requiredness on back or draft button.
  if (isset($form_state['clicked_button']['#validate']) && empty($form_state['clicked_button']['#validate'])) {
    return;
  }

  // Check if a value is already set in the hidden field.
  $values = $form_state['values'];
  $key = array_shift($parents);
  $found = FALSE;
  while (isset($values[$key])) {
    if (isset($values[$key])) {
      $values = $values[$key];
      $found = TRUE;
    }
    else {
      $found = FALSE;
    }
    $key = array_shift($parents);
  }

  if (!$found || (empty($values['_fid']) && empty($values['_old']))) {
    if (empty($_FILES['files']['name'][$form_key]) && $component['mandatory']) {
      form_error($element, t('%field field is required.', array('%field' => $component['name'])));
    }
  }
}

/**
 * A Form API element validate function.
 *
 * Ensure that the uploaded file matches the specified file types.
 */
function _webform_validate_file($element, &$form_state) {
  $component = $element['#webform_component'];
  $form_key = implode('_', $element['#parents']);

  if (empty($_FILES['files']['name'][$form_key])) {
    return;
  }

  // Build a human readable list of extensions:
  $extensions = $component['extra']['filtering']['types'];
  $extension_list = '';
  if (count($extensions) > 1) {
    for ($n = 0; $n < count($extensions) - 1; $n++) {
      $extension_list .= $extensions[$n] . ', ';
    }
    $extension_list .= 'or ' . $extensions[count($extensions) - 1];
  }
  elseif (!empty($extensions)) {
    $extension_list = $extensions[0];
  }

  if (in_array('jpg', $extensions)) {
    $extensions[] = 'jpeg';
  }

  $strrpos = function_exists('mb_strrpos') ? 'mb_strrpos' : 'strrpos';
  $dot = $strrpos($_FILES['files']['name'][$form_key], '.');
  $extension = drupal_strtolower(drupal_substr($_FILES['files']['name'][$form_key], $dot+1));
  $file_error = FALSE;
  if (!empty($extensions) && !in_array($extension, $extensions)) {
    form_error($element, t("Files with the '%ext' extension are not allowed, please upload a file with a %exts extension.", array('%ext' => $extension, '%exts' => $extension_list)));
    $file_error = TRUE;
  }

  // Now let's check the file size (limit is set in KB).
  if ($_FILES['files']['size'][$form_key] > $component['extra']['filtering']['size'] * 1024) {
    form_error($element, t("The file '%filename' is too large (%filesize KB). Please upload a file %maxsize KB or smaller.", array('%filename' => $_FILES['files']['name'][$form_key], '%filesize' => (int) ($_FILES['files']['size'][$form_key]/1024), '%maxsize' => $component['extra']['filtering']['size'])));
    $file_error = TRUE;
  }

  // Save the file to a temporary location.
  if (!$file_error) {
    $upload_dir = file_directory_path() . '/webform/' . $component['extra']['savelocation'];
    if (file_check_directory($upload_dir, FILE_CREATE_DIRECTORY)) {
      $file = file_save_upload($form_key, array(), $upload_dir);
      if ($file) {
        @chmod($file->filepath, 0664);

        // Set the hidden field value.
        $parents = $element['#array_parents'];
        array_pop($parents);
        $parents[] = '_fid';
        form_set_value(array('#parents' => $parents), $file->fid, $form_state);
      }
      else {
        drupal_set_message(t('The uploaded file %filename was unable to be saved. The destination directory may not be writable.', array('%filename' => $file->filename)), 'error');
      }
    }
    else {
      drupal_set_message(t('The uploaded file was unable to be saved. The destination directory does not exist.'), 'error');
    }
  }
}

/**
 * Implements _webform_submit_component().
 */
function _webform_submit_file($component, $value) {

  if ($value['_fid'] && ($file = webform_get_file($value['_fid']))) {
    // Save any new files permanently.
    file_set_status($file, FILE_STATUS_PERMANENT);

    // Delete any previous files.
    if ($value['_old'] && $value['_old'] != $value['_fid'] && ($existing = webform_get_file($value['_old']))) {
      file_delete($existing->filepath);
      db_query("DELETE FROM {files} WHERE fid = %d", $existing->fid);
    }

    $value = $file->fid;
  }
  else {
    $value = $value['_old'] ? $value['_old'] : NULL;
  }

  return $value;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_file($component, $value, $format = 'html') {
  $fid = isset($value[0]) ? $value[0] : NULL;
  return array(
    '#title' => $component['name'],
    '#value' => $fid ? webform_get_file($fid) : NULL,
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_file',
    '#theme_wrappers' => $format == 'html' ? array('webform_element', 'webform_element_wrapper') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#format' => $format,
    '#translatable' => array('title'),
  );
}

/**
 * Format the output of text data for this component
 */
function theme_webform_display_file($element) {
  $file = $element['#value'];
  $url = !empty($file) ? webform_file_url($file->filepath) : t('no upload');
  return !empty($file) ? ($element['#format'] == 'text' ? $url : l($file->filename, $url)) : ' ';
}

/**
 * Implements _webform_delete_component().
 */
function _webform_delete_file($component, $value) {
  // Delete an individual submission file.
  if (!empty($value[0]) && ($file = webform_get_file($value[0]))) {
    unlink($file->filepath);
    db_query("DELETE FROM {files} WHERE fid = '%d'", $file->fid);
  }
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_file($component, $sids = array()) {
  $placeholders = count($sids) ? array_fill(0, count($sids), "'%s'") : array();
  $sidfilter = count($sids) ? " AND sid in (" . implode(",", $placeholders) . ")" : "";
  $query = 'SELECT data ' .
    ' FROM {webform_submitted_data} ' .
    ' WHERE nid = %d ' .
    ' AND cid = %d' . $sidfilter;
  $nonblanks = 0;
  $sizetotal = 0;
  $submissions = 0;

  $result = db_query($query, array_merge(array($component['nid'], $component['cid']), $sids));
  while ($data = db_fetch_array($result)) {
    $file = webform_get_file($data['data']);
    if (isset($file->filesize)) {
      $nonblanks++;
      $sizetotal += $file->filesize;
    }
    $submissions++;
  }

  $rows[0] = array(t('Left Blank'), ($submissions - $nonblanks));
  $rows[1] = array(t('User uploaded file'), $nonblanks);
  $rows[2] = array(t('Average uploaded file size'), ($sizetotal != 0 ? (int) (($sizetotal/$nonblanks)/1024) . ' KB' : '0'));
  return $rows;
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_file($component, $value) {
  $output = '';
  $file = webform_get_file($value[0]);
  if (!empty($file->fid)) {
    $output = '<a href="' . webform_file_url($file->filepath) . '">' . check_plain(webform_file_name($file->filepath)) . '</a>';
    $output .= ' (' . (int) ($file->filesize/1024) . ' KB)';
  }
  return $output;
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_file($component, $export_options) {
  $header = array();
  // Two columns in header.
  $header[0] = array('', '');
  $header[1] = array($component['name'], '');
  $header[2] = array(t('Name'), t('Filesize (KB)'));
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_file($component, $export_options, $value) {
  $file = webform_get_file($value[0]);
  return empty($file->filename) ? array('', '') : array(webform_file_url($file->filepath), (int) ($file->filesize/1024));
}

/**
 * Helper function to create proper file names for uploaded file.
 */
function webform_file_name($filepath) {
  if (!empty($filepath)) {
    $info = pathinfo($filepath);
    $file_name = $info['basename'];
  }
  return isset($file_name) ? $file_name : '';
}

/**
 * Helper function to create proper URLs for uploaded file.
 */
function webform_file_url($filepath) {
  if (!empty($filepath)) {
    $info = pathinfo($filepath);
    switch (variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC)) {
      case FILE_DOWNLOADS_PUBLIC:
        $path = $info['dirname'] . '/' . rawurlencode($info['basename']);
        break;
      case FILE_DOWNLOADS_PRIVATE:
        // Private file paths must not be encoded as they are run through url()
        // which performs the file encoding.
        $path = $info['dirname'] . '/' . $info['basename'];
        break;
    }
    $file_url = file_create_url($path);
  }
  return isset($file_url) ? $file_url : '';
}

/**
 * Helper function to load a file from the database.
 */
function webform_get_file($fid) {
  static $files;

  if (!isset($files[$fid])) {
    if (empty($fid)) {
      $files[$fid] = FALSE;
    }
    else {
      $files[$fid] = db_fetch_object(db_query("SELECT * FROM {files} WHERE fid = %d", $fid));
    }
  }

  return $files[$fid];
}

/**
 * Implements _webform_attachments_component().
 */
function _webform_attachments_file($component, $value) {
  $file = (array) webform_get_file($value[0]);
  $files = array($file);
  return $files;
}
