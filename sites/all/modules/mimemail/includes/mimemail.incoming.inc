<?php

/**
 * @file
 * Functions that handle inbound messages to Mime Mail.
 */

/**
 * Receive messages POSTed from an external source.
 *
 * This function enables messages to be sent via POST or some other RFC822
 * source input (e.g. directly from a mail server).
 *
 * @return
 *   The POSTed message.
 */
function mimemail_post() {
  if (!isset($_POST['token']) || empty($_POST['token'])) {
    return drupal_access_denied();
  }

  if (isset($_POST['message']) && !empty($_POST['message'])) {
    $key = variable_get('mimemail_key', drupal_random_key());
    $hash = hash_hmac('sha1', $_POST['message'], $key);
    if ($hash != $_POST['token']) {
      watchdog('access denied', 'Authentication error for POST e-mail', WATCHDOG_WARNING);
      return drupal_access_denied();
    }
    else {
      return mimemail_incoming($_POST['message']);
    }
  }

  return drupal_access_denied();
}

/**
 * Parses an externally received message.
 *
 * @param $message
 *   The message to parse.
 */
function mimemail_incoming($message) {
  require_once dirname(__FILE__) .'/mimemail.inc';
  $mail = mimemail_parse($message);

  foreach (module_implements('mimemail_incoming_alter') as $module) {
    call_user_func_array($module .'_mimemail_incoming_alter', $mail);
  }

  module_invoke_all('mimemail_incoming', $mail);
}
