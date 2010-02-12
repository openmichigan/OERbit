<?php
// $Id: linkchecker.pages.inc,v 1.1.2.20 2009/11/22 14:09:45 hass Exp $

/**
 * @file
 * User page callbacks for the linkchecker module.
 */

/**
 * Menu callback for general reporting.
 */
function linkchecker_admin_report_page() {

  $ignore_response_codes = preg_split('/(\r\n?|\n)/', variable_get('linkchecker_ignore_response_codes', "200\n302\n304\n401\n403"));

  // Search for broken links in nodes and comments and blocks of all users.
  // TODO: Try to make subselect result smaller.
  $links_report_sql = "SELECT ll.*
    FROM {linkchecker_links} ll
    INNER JOIN (
      SELECT lid FROM (
        SELECT DISTINCT lid FROM {linkchecker_boxes}
        UNION
        SELECT DISTINCT lid FROM {linkchecker_comments}
        UNION
        SELECT DISTINCT lid FROM {linkchecker_nodes}
      ) q1
    ) q2 ON q2.lid = ll.lid
    WHERE ll.last_checked <> %d AND ll.status = %d AND ll.code NOT IN (" . db_placeholders($ignore_response_codes, 'int') . ")";

  // Build the array variable with all parameters for the pager_query.
  $links_report_parameters = array_merge(array(0, 1), $ignore_response_codes);

  return _linkchecker_report_page($links_report_sql, $links_report_parameters);
}

/**
 * Menu callback for author specific reporting.
 */
function linkchecker_user_report_page($account) {
  drupal_set_title(check_plain($account->name));

  $ignore_response_codes = preg_split('/(\r\n?|\n)/', variable_get('linkchecker_ignore_response_codes', "200\n302\n304\n401\n403"));

  // Search for broken links in nodes and comments of the current user.
  if (module_exists('comment') && variable_get('linkchecker_scan_comments', 0)) {
    $links_report_sql = "SELECT ll.*
      FROM {linkchecker_links} ll
      INNER JOIN (
        SELECT lid FROM (
          SELECT DISTINCT ll.lid
          FROM {node} n
          INNER JOIN {node_revisions} r ON r.vid = n.vid
          INNER JOIN {linkchecker_nodes} ln ON ln.nid = n.nid
          INNER JOIN {linkchecker_links} ll ON ll.lid = ln.lid AND ll.last_checked <> %d AND ll.status = %d AND ll.code NOT IN (" . db_placeholders($ignore_response_codes, 'int') . ")
          WHERE n.uid = %d OR r.uid = %d
          UNION
          SELECT DISTINCT ll.lid
          FROM {comments} c
          INNER JOIN {linkchecker_comments} lc ON lc.cid = c.cid
          INNER JOIN {linkchecker_links} ll ON ll.lid = lc.lid AND ll.last_checked <> %d AND ll.status = %d AND ll.code NOT IN (" . db_placeholders($ignore_response_codes, 'int') . ")
          WHERE c.uid = %d
        ) q1
      ) q2 ON q2.lid = ll.lid";

    // Build the array variable with all parameters for the pager_query with comment module enabled.
    $links_report_parameters = array_merge(array(0, 1), $ignore_response_codes, array($account->uid, $account->uid, 0, 1), $ignore_response_codes, array($account->uid));
  }
  else {
    // Search for broken links in nodes of the current user.
    $links_report_sql = "SELECT ll.*
      FROM {linkchecker_links} ll
      INNER JOIN (
        SELECT lid FROM (
          SELECT DISTINCT ll.lid
          FROM {node} n
          INNER JOIN {node_revisions} r ON r.vid = n.vid
          INNER JOIN {linkchecker_nodes} ln ON ln.nid = n.nid
          INNER JOIN {linkchecker_links} ll ON ll.lid = ln.lid AND ll.last_checked <> %d AND ll.status = %d AND ll.code NOT IN (" . db_placeholders($ignore_response_codes, 'int') . ")
          WHERE n.uid = %d OR r.uid = %d
        ) q1
      ) q2 ON q2.lid = ll.lid";

    // Build the array variable with all parameters for the pager_query with comment module disabled.
    $links_report_parameters = array_merge(array(0, 1), $ignore_response_codes, array($account->uid, $account->uid));
  }

  return _linkchecker_report_page($links_report_sql, $links_report_parameters, $account);
}

function _linkchecker_report_page($links_report_sql, $links_report_parameters = NULL, $account = NULL) {

  $links_unchecked = db_result(db_query('SELECT COUNT(1) FROM {linkchecker_links} WHERE last_checked = %d', 0));
  if ($links_unchecked > 0) {
    $links_all = db_result(db_query('SELECT COUNT(1) FROM {linkchecker_links}'));
    drupal_set_message(format_plural($links_unchecked,
      'There is 1 unchecked link of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      'There are @count unchecked links of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      array('@links_all' => $links_all)), 'warning');
  }

  $header = array(
    array('data' => t('URL'), 'field' => 'url', 'sort' => 'desc'),
    array('data' => t('Response'), 'field' => 'code', 'sort' => 'desc'),
    array('data' => t('Error'), 'field' => 'error'),
    array('data' => t('Operations')),
  );

  $result = pager_query($links_report_sql . tablesort_sql($header), 50, 0, NULL, $links_report_parameters);

  // Evaluate permission once for performance reasons.
  $access_edit_link_settings = user_access('edit link settings');
  $access_administer_blocks = user_access('administer blocks');
  $access_administer_redirects = user_access('administer redirects');

  $rows = array();
  while ($link = db_fetch_object($result)) {
    $links = array();

    // Show links to link settings.
    if ($access_edit_link_settings) {
      $links[] = l(t('Edit link settings'), 'linkchecker/' . $link->lid . '/edit', array('query' => drupal_get_destination()));
    }

    // Show link to nodes having this broken link.
    if (!empty($account)) {
      $nodes = db_query('SELECT ln.nid
        FROM {linkchecker_nodes} ln
        INNER JOIN {node} n ON n.nid = ln.nid
        INNER JOIN {node_revisions} r ON r.vid = n.vid
        WHERE ln.lid = %d AND (n.uid = %d OR r.uid = %d)', $link->lid, $account->uid, $account->uid);
    }
    else {
      $nodes = db_query('SELECT nid FROM {linkchecker_nodes} WHERE lid = %d', $link->lid);
    }
    while ($node = db_fetch_object($nodes)) {
      $links[] = l(t('Edit node @node', array('@node' => $node->nid)), 'node/' . $node->nid . '/edit', array('query' => drupal_get_destination()));
    }

    // Show link to comments having this broken link.
    if (!empty($account) && module_exists('comment') && variable_get('linkchecker_scan_comments', 0)) {
      $comments = db_query('SELECT lc.cid
        FROM {linkchecker_comments} lc
        INNER JOIN {comments} c ON c.cid = lc.cid
        WHERE lc.lid = %d AND c.uid = %d', $link->lid, $account->uid);
    }
    else {
      $comments = db_query('SELECT cid FROM {linkchecker_comments} WHERE lid = %d', $link->lid);
    }
    while ($comment = db_fetch_object($comments)) {
      $links[] = l(t('Edit comment @comment', array('@comment' => $comment->cid)), 'comment/edit/' . $comment->cid, array('query' => drupal_get_destination()));
    }

    // Show link to blocks having this broken link.
    if ($access_administer_blocks) {
      $boxes = db_query('SELECT bid FROM {linkchecker_boxes} WHERE lid = %d', $link->lid);
      while ($box = db_fetch_object($boxes)) {
        $links[] = l(t('Edit block @block', array('@block' => $box->bid)), 'admin/build/block/configure/block/' . $box->bid, array('query' => drupal_get_destination()));
      }
    }

    // Show link to redirect this broken internal link.
    if (module_exists('path_redirect') && $access_administer_redirects && _linkchecker_is_internal_url($link)) {
      $links[] = l(t('Create redirection'), 'admin/build/path-redirect/add', array('query' => array('src' => $link->internal)));
    }

    // Create table data for output. Use inline styles to prevent extra CSS file.
    $rows[] = array(
      l(_filter_url_trim($link->url, 40), $link->url),
      $link->code,
      check_plain($link->error),
      theme('item_list', $links),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No broken links have been found.'), 'colspan' => count($header)));
  }

  $output  = theme('table', $header, $rows);
  $output .= theme('pager', NULL, 3000, 0);
  return $output;
}

function linkchecker_link_edit_form(&$form_state, $link) {

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => FALSE,
    '#description' => t('The link <a href="@url">@url</a> has been checked lastly at @last_checked and failed @fail_count times.', array('@url' => $link['url'], '@fail_count' => $link['fail_count'], '@last_checked' => format_date($link['last_checked'])))
  );

  $form['settings']['lid'] = array('#type' => 'hidden', '#value' => $link['lid']);
  $form['settings']['url'] = array('#type' => 'hidden', '#value' => $link['url']);

  $form['settings']['method'] = array(
    '#type' => 'select',
    '#title' => t('Select request method'),
    '#default_value' => $link['method'],
    '#options' => array(
      'HEAD' => t('HEAD'),
      'GET' => t('GET'),
    ),
    '#description' => t('Select the request method used for link checks of this link. If you encounter issues like status code 500 errors with the HEAD request method you should try the GET request method before ignoring a link.'),
  );

  $form['settings']['status'] = array(
    '#default_value' => $link['status'],
    '#type' => 'checkbox',
    '#title' => t('Check link status'),
    '#description' => t("Disable this checkbox if you don't like to get informed any longer about this broken link. Use this setting only as the very last option if there is no other way to solve a failed link check."),
  );

  $form['maintenance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maintenance'),
    '#collapsible' => FALSE,
  );

  $form['maintenance']['recheck'] = array(
    '#default_value' => 0,
    '#type' => 'checkbox',
    '#title' => t('Re-check link status on next cron run'),
    '#description' => t('Enable this checkbox if you need an immediate re-check of the link and cannot wait until the next scheduled check at @date.', array('@date' => format_date($link['last_checked'] + variable_get('linkchecker_check_links_interval', 2419200)))),
  );

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults'));

  return $form;
}

function linkchecker_link_edit_form_submit($form, &$form_state) {
  // Force asap link re-check.
  if ($form_state['values']['recheck']) {
    db_query("UPDATE {linkchecker_links} SET last_checked = %d WHERE lid = %d", 0, $form_state['values']['lid']);
    drupal_set_message(t('The link %url will be checked again on the next cron run.', array('%url' => $form_state['values']['url'])));
  }

  if ($form_state['values']['method'] != $form['settings']['method']['#default_value']) {
    // Update settings and reset statistics for a quick re-check.
    db_query("UPDATE {linkchecker_links} SET method = '%s', fail_count = %d, last_checked = %d, status = %d WHERE lid = %d", $form_state['values']['method'], 0, 0, $form_state['values']['status'], $form_state['values']['lid']);
    drupal_set_message(t('The link settings for %url have been saved and the fail counter has been reset.', array('%url' => $form_state['values']['url'])));
  }
  else {
    // Update setting only.
    db_query("UPDATE {linkchecker_links} SET method = '%s', status = %d WHERE lid = %d", $form_state['values']['method'], $form_state['values']['status'], $form_state['values']['lid']);
    drupal_set_message(t('The link settings for %url have been saved.', array('%url' => $form_state['values']['url'])));
  }
}

function _linkchecker_is_internal_url(&$link) {
  global $base_url;

  if (strpos($link->url, $base_url) === 0) {
    $link->internal = trim(substr($link->url, strlen($base_url)), " \t\r\n\0\\/");
    return TRUE;
  }
}
