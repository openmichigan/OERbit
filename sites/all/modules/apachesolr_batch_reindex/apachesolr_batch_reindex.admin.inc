<?php
// $Id: apachesolr_search.admin.inc,v 1.1.2.15 2009/04/30 18:00:00 pwolanin Exp $

/**
 * @file
 *   Administrative settings for searching.
 */

/**
 * Menu callback - the settings form.
 */
function apachesolr_batch_reindex_settings_page() {
  $output = drupal_get_form('apachesolr_batch_reindex_settings_form');
  return $output;
}

function apachesolr_batch_reindex_settings_form() {
  $form = array();
  $form['markup'] = array(
    '#prefix' => '<h3>',
    '#value' => t('Search Index Controls'),
    '#suffix' => '</h3>',
  );
  $form['reindex'] = array(
    '#type' => 'submit',
    '#value' => t('Batch reindex'),
    '#submit' => array('apachesolr_batch_reindex_submit'),
  );
  $form['reindex-desc'] = array(
    '#type' => 'item',
    '#description' => t('Re-indexing will add all content to the index again (overwriting the index), but existing content in the index will remain searchable. This reindexing process uses the Batch API.'),
  );
  return $form;
}

/**
 * Submit function for the 'Re-index all content' button.
 *
 * @see apachesolr_delete_index_form()
 */
function apachesolr_batch_reindex_submit($form, &$form_state) {
  batch_apachesolr_reindex();
}