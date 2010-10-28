<?php
// $Id: blocks404.active.inc,v 1.6 2010/03/25 18:43:43 johnalbin Exp $

/**
 * Helper function for our hook_form_alter().
 *
 * We need this to be able to submit any forms from the error pages, otherwise
 * the form POSTs to the error page and the form is not processed.
 */
function _blocks404_form_alter(&$form, $form_state, $form_id) {
  // drupal_not_found() sets $_GET['q'] to the site_404 variable, but the
  // $_REQUEST['q'] variable is not affected.
  $original_query = $_REQUEST['q'];

  // Form actions that POST to the 404 page won't work properly.
  if ($form['#action'] == url(BLOCKS404_PAGE) || $form['#action'] == url($original_query) || $form_id == 'user_login_block' || $form['#action'] == url(BLOCKS404_PAGE, array('query' => 'destination=' . $original_query))) {
    $form['#action'] = url('<front>');
  }

  // Form actions that redirect back to the 404 page aren't good either.
  elseif (strpos($form['#action'], 'destination=' . urlencode($original_query)) !== FALSE) {
    // Deconstruct the URL.
    list(, $path) = explode($GLOBALS['base_path'], $form['#action']);
    list($path, $query) = explode('?', $path);
    $query = explode('&', $query);
    if (($pos = array_search('destination=' . urlencode($original_query), $query)) !== FALSE) {
      // Remove the broken redirection.
      unset($query[$pos]);
      // Reconstruct the URL.
      $form['#action'] = url($path, array('query' => $query));
    }
  }
}
