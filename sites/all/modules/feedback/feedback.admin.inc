<?php
// $Id: feedback.admin.inc,v 1.1.2.1 2010/01/08 16:57:59 sun Exp $

/**
 * @file
 * Administrative functionality for Feedback module.
 */

/**
 * Build a (sortable) form containing a checkbox for each feedback entry.
 */
function feedback_admin_view_form() {
  $form = array();
  $status_headings = array(
    0 => t('Open feedback messages'),
    1 => t('Processed feedback messages'),
  );
  $form['#feedback_header'] = array(
    array(),
    array('data' => t('Location'), 'field' => 'f.location_masked', 'sort' => 'asc'),
    array('data' => t('Date'), 'field' => 'f.timestamp'),
    array('data' => t('User'), 'field' => 'u.name'),
    t('Message'),
  );
  // Hack to prevent pager_query() from issuing PHP notices.
  if (!isset($_GET['page'])) {
    $_GET['page'] = '';
  }
  if (count(explode(',', $_GET['page'])) < 2) {
    $_GET['page'] .= ',0';
  }

  $form['feedback-messages'] = array('#tree' => TRUE);
  foreach (array(0, 1) as $status) {
    $sql = "SELECT f.*, u.name FROM {feedback} f INNER JOIN {users} u ON f.uid = u.uid WHERE f.status = %d";
    $count_query = "SELECT COUNT(fid) FROM {feedback} WHERE status = %d";
    $tablesort = tablesort_sql($form['#feedback_header']);
    $result = pager_query($sql . $tablesort, 50, $status, $count_query, $status);

    $form['feedback-messages'][$status] = array(
      '#type' => 'fieldset',
      '#title' => $status_headings[$status],
      '#collapsible' => TRUE,
      '#collapsed' => $status,
      '#attributes' => array('class' => 'feedback-messages'),
    );
    while ($entry = db_fetch_object($result)) {
      $form['feedback-messages'][$status][$entry->fid] = array(
        '#type' => 'checkbox',
        '#return_value' => 1,
        '#default_value' => FALSE,
      );
      $form['feedback-messages'][$status][$entry->fid]['location'] = array('#value' => l(truncate_utf8($entry->location, 32, FALSE, TRUE), $entry->url));
      $form['feedback-messages'][$status][$entry->fid]['date'] = array('#value' => format_date($entry->timestamp, 'small'));
      $form['feedback-messages'][$status][$entry->fid]['user'] = array('#value' => theme('username', $entry));
      $form['feedback-messages'][$status][$entry->fid]['message'] = array('#value' => feedback_format_message($entry));
    }
  }
  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));
  return $form;
}

/**
 * Output a sortable table containing all feedback entries.
 */
function theme_feedback_admin_view_form(&$form) {
  $output = '';
  foreach (element_children($form['feedback-messages']) as $status) {
    $item = &$form['feedback-messages'][$status];
    if (!isset($item['#type']) || $item['#type'] != 'fieldset') {
      continue;
    }
    // Build the table.
    $rows = array();
    foreach (element_children($item) as $element_entry) {
      $entry = &$item[$element_entry];
      // Render the data first.
      $rows[] = array(
        0,
        drupal_render($entry['location']),
        drupal_render($entry['date']),
        drupal_render($entry['user']),
        drupal_render($entry['message']),
      );
      // Render the checkbox.
      $rows[count($rows) - 1][0] = drupal_render($entry);
    }
    if (empty($rows)) {
      $rows[] = array(array('data' => t('No feedback entries available.'), 'colspan' => 5));
    }
    // Inject the table.
    $item['messages'] = array(
      '#value' => theme('table', $form['#feedback_header'], $rows) . theme('pager', array(), 50, $status),
      '#weight' => -1,
    );
    // Render the fieldset.
    $output .= drupal_render($item);
  }
  // Render internal FAPI and potential extra form elements.
  $output .= drupal_render($form);
  return $output;
}

/**
 * Form submit callback for admin view form.
 */
function feedback_admin_view_form_submit($form, &$form_state) {
  $update = array();
  // Determine feedback entries to update.
  foreach ($form_state['values']['feedback-messages'] as $status => $entries) {
    $entries = array_filter($entries);
    foreach ($entries as $fid => $value) {
      // Lame for now. :(
      $update[$fid] = ($status == 0 ? 1 : 0);
    }
  }
  // Update status of entries in database.
  foreach ($update as $fid => $value) {
    db_query("UPDATE {feedback} SET status = %d WHERE fid = %d", $value, $fid);
  }
}

