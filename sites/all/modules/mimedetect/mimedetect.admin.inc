<?php

function mimedetect_settings() {
  // Check if fileinfo is available so we don't present the file options if
  // they can't use them
  if (extension_loaded('fileinfo')) {
    $form['file'] = array(
      '#value' => t("The MimeDetect module is using PHP's fileinfo extension to detect MIME types. There are no settings for the extension.")
    );
  }
  else {
    $form['file'] = array(
      '#type' => 'fieldset',
      '#title' => t("UNIX 'file' command"),
    );
    $form['file']['mimedetect_enable_file_binary'] = array(
      '#type' => 'checkbox',
      '#title' => t("Use UNIX 'file' command to detect mime type?"),
      '#description' => t("The UNIX 'file' command will be used for mime detection only if the PHP Fileinfo extension is not installed or fails to load."),
      '#default_value' => variable_get('mimedetect_enable_file_binary', FALSE),
    );
    $form['file']['mimedetect_file_binary'] = array(
      '#type' => 'textfield',
      '#title' => t("Path to the 'file' command"),
      '#description' => t("The path to the executable 'file' binary."),
      '#default_value' => variable_get('mimedetect_file_binary','/usr/bin/file'),
    );
    $form = system_settings_form($form);
  }
  return $form;
}

function mimedetect_settings_validate($form_id, &$form_state) {
  // Test file binary settings.
  if ($form_state['values']['mimedetect_enable_file_binary']) {
    if (empty($form_state['values']['mimedetect_file_binary'])) {
      form_set_error('mimedetect_file_binary', t("You must specify the path to the 'file' binary if it is enabled."));
    }
    if (!is_executable($form_state['values']['mimedetect_file_binary'])) {
      if (!file_exists($form_state['values']['mimedetect_file_binary'])) {
        form_set_error('mimedetect_file_binary', t("The path %path does not exist or is not readable by your webserver.", array('%path' => $form_state['values']['mimedetect_file_binary'])));
      }
      else {
        form_set_error('mimedetect_file_binary', t("%path is not executable by your webserver.", array('%path' => $form_state['values']['mimedetect_file_binary'])));
      }
    }
  }
}
