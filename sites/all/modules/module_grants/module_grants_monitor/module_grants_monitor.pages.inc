<?php
// $Id: module_grants_monitor.pages.inc,v 1.2 2010/01/28 01:07:57 rdeboer Exp $

/**
 * @file
 * Rendering of the accessible content summary page and tabs
 */

/**
 * Return as a themed table a content summary of the site filtered by the
 * access rights of the logged-in user.
 *
 * @param $access
 *   one of 'view', 'update' or 'delete'
 * @param $is_published
 *   1 for published-only, 0 for unpublished-only, NO_FILTER for don't care
 * @param $user_filter
 *   One of NO_FILTER, I_CREATED or I_LAST_MODIFIED
 * @param $is_moderated
 *   1 for moderated, 0 for not moderated, NO_FILTER for don't care
 * @param $is_pending
 *   TRUE for in draft/pending, FALSE otherwise
 * @return
 *   themed HTML
 */
function module_grants_monitor_accessible_content_summary($access = 'view', $is_published = -1,
    $user_filter = NO_FILTER, $is_moderated = NO_FILTER, $is_pending = FALSE) {
  global $user;
  $creator_id  = ($user_filter == I_CREATED) ? $user->uid : -1;
  $modifier_id = ($user_filter == I_LAST_MODIFIED) ? $user->uid : -1;
  $nodes = node_tools_get_nodes($access, (int)$is_published, $creator_id, $modifier_id, (int)$is_moderated, $is_pending);
  return theme('module_grants_monitor_nodes_summary', $nodes);
}

/**
 * Theme the passed-in nodes as a table.
 *
 * Uses the following subthemes:
 * o 'table_nodes', falling back to theme.inc/theme_table() if not defined
 * o 'username', i.e. theme.inc/theme_username()
 *
 * @param $nodes
 *   Array of nodes to display.
 * @return
 *   Themed table HTML or a paragraph saying 'No content found.' if the supplied
 *   array is empty.
 *
 * @ingroup themeable
 */
function theme_module_grants_monitor_nodes_summary($nodes) {
  $css_path = drupal_get_path('module', 'module_grants_monitor') .'/module_grants_monitor.css';
  drupal_add_css($css_path, 'module', 'all', FALSE);
  if (!empty($nodes)) {
    // Note the specification of fields doesn't seem to work properly
    // See theme.inc/theme_table(), which uses tablesort.inc/tablesort_header()
    $header = array(
      array('data' => t('Title'), 'field' => 'r.title'),
      array('data' => t('Type'), 'field' => 'n.type'),
      array('data' => t('Creator'), 'field' => 'n.uid'),
      array('data' => t('Last updated'), 'field' => 'timestamp', 'sort' => 'desc'),
      array('data' => t('By'), 'field' => 'r.uid'),
      array('data' => t('Published?'), 'field' => 'status')
    );
    $show_taxonomy_terms = module_exists('taxonomy') &&
      (count(taxonomy_get_vocabularies()) > 0) && variable_get("show_taxonomy_terms", TRUE);
    $show_workflow_state = module_exists('workflow');
    if ($show_taxonomy_terms) {
      $header[] = array('data' => t('Term'), 'field' => 'term');
    }
    if ($show_workflow_state) {
      $header[] = array('data' => t('Workflow state'), 'field' => 'ws.state');
    }
    $rows = array();
    foreach ($nodes as $node) {
      $row = array(
        l($node->title, 'node/'. $node->nid),
        check_plain(node_get_types('name', $node)),
        theme('username', user_load(array('uid' => $node->creator_uid))),
        format_date($node->timestamp),
        theme('username', user_load(array('uid' => $node->uid))),
        $node->status ? t('Yes') : t('No')
      );
      if ($show_taxonomy_terms) {
        $row[] = empty($node->term) ? '' : check_plain($node->term);
      }
      if ($show_workflow_state) {
        $row[] = empty($node->state) ? t('No state') : check_plain($node->state);
      }
      $rows[] = $row;
    }
    $attributes = array('class' => 'table-nodes');
    return theme(array('table_nodes', 'table'), $header, $rows, $attributes, $caption = NULL);
  }
  return '<p>'. t('No content found.') .'</p>';
}

/**
 * Implement (in your own module) the function below if you want to override
 * the default way in which the nodes summary table is displayed.
 * If you do, don't forget to register this theme_hook() via <your_module>_theme()
 * in a manner similar to module_grants_module_theme()
 *
 * @param $header
 * @param $rows
 * @return themed HTML, see for instance /includes/theme.inc/theme_table()
 *
 * @ingroup themeable
 *
function theme_table_nodes($header, $rows) {
}
 */
