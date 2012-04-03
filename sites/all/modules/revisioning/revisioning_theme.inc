<?php

/**
 * @file
 * Include file for revisioning.module; deals with all theming aspects.
 */

/**
 * Implementation of hook_theme().
 * Register the theme_hooks() available in this module, with their arguments
 * and default values.
 */
function revisioning_theme() {
  return array(
    'revisioning_revisions_summary' => array(
      'arguments' => array('form' => array()),
    ),
    'revisions_pending_block' => array(
      'arguments' => array('content' => NULL),
      'template' => 'revisions-pending-block', // revisions-pending-block.tpl.php
    ),
    'revisions_summary' => array(
      'arguments' => array('submenu_links' => NULL, 'content' => NULL),
      'template' => 'revisions-summary', // revisions-summary.tpl.php
    ),
  );
}

/**
 * Return revisions summary table data. If the Diff modules is enabled, the
 * object returned includes a column of checkboxes allowing the user to select
 * two revisions for side-by-side comparison.
 *
 * @param $form_state
 * @param $nid, the id of the node
 * @return form containing all data to be themed
 */
function revisioning_revisions_summary($form_state, $nid) {
  $form = array();

  // #type=>'value' form field values will not appear in the HTML. Used to pass
  // the node id to revisioning_revisions_summary_submit() and
  // theme_revisioning_revisions_summary().
  $form['nid'] = array('#type' => 'value', '#value' => $nid);

  $show_taxonomy_terms = module_exists('taxonomy') &&
    (count(taxonomy_get_vocabularies()) > 0) && variable_get("show_taxonomy_terms", TRUE);

  $revisions = _revisioning_get_all_revisions_for_node($nid, $show_taxonomy_terms);

  $revision_ids = array();
  foreach ($revisions as $revision) {
    if (!empty($revision->type)) {
      // This is the current revision, holding publication status and content type
      $content_type = $revision->type;
      $title = $revision->title;
      $published = $revision->status;
    }
    $vid = $revision->vid;
    $revision_ids[$vid] = ''; // no text next to check box
    $base_url = "node/$nid/revisions/$vid";

    // First column: saved date + author
    $first_cell = t('Saved !date by !username',
      array('!date' => l(format_date($revision->timestamp, 'small'), "$base_url/view"),
            '!username' => theme('username', $revision)))
      . (empty($revision->log) ? '' : '<p class="revision-log">'. filter_xss($revision->log) .'</p>');
    $form['info'][$vid] = array('#value' => $first_cell);

    // Third column: term (2nd column is handled below)
    if ($show_taxonomy_terms) {
      $form['term'][$vid] = array('#value' => $revision->term);
    }
  }
  drupal_set_message(format_plural(count($revisions),
    '@publication_status @content_type %title has only one revision',
    '@publication_status @content_type %title has @count revisions.',
    array(
     '@publication_status' => ($published ? t('Published') : t('Unpublished')),
     '@content_type' => $content_type,
     '%title' => $title,
    )
  ));
  if (count($revisions) >= 2 && module_exists('diff')) {
    // Second column: check-boxes to select two revisions to compare
    $id1 = key($revision_ids);
    next($revision_ids);
    $id2 = key($revision_ids);
    $form['tickbox'] = array(
      '#type' => 'checkboxes',
      '#options' => $revision_ids,
      '#default_value' => array($id1, $id2),
      '#required' => TRUE,
    );
    // Submit button
    $form['submit'] = array('#value' => t('Compare'), '#type' => 'submit');
  }
  return $form;
}

/**
 * Validation for input form to select two revisions.
 *
 * @param $form
 * @param $form_state
 * @return void
 */
function revisioning_revisions_summary_validate($form, &$form_state) {
  // Strip out all unchecked boxes
  $form_state['values']['tickbox'] = array_filter($form_state['values']['tickbox']);
  $count = count($form_state['values']['tickbox']);
  if ($count != 2) {
    form_set_error('tickbox', t('Please select 2 revisions rather than !count', array('!count' => $count)));
  }
}

/**
 * Submit two selected revisions to Diff module.
 *
 * @param $form
 * @param $form_state
 * @return void
 */
function revisioning_revisions_summary_submit($form, &$form_state) {
  $selected_vids = $form_state['values']['tickbox'];
  $vid1 = key($selected_vids);
  next($selected_vids);
  $vid2 = key($selected_vids);
  drupal_get_messages(); // clear existing msgs
  drupal_set_message(
    t('Comparing revision #!revision2 against revision #!revision1',
    array('!revision2' => $vid2, '!revision1' => $vid1)));
  $destination = '';
  if (isset($_REQUEST['destination'])) {
    $destination = drupal_get_destination();
    unset($_REQUEST['destination']);
  }
  $nid = $form_state['values']['nid'];
  $form_state['redirect'] = array("node/$nid/revisions/view/$vid2/$vid1", $destination);
}

/**
 * Theme the supplied form.
 *
 * Uses the following subthemes:
 * o 'table_revisions', falling back to theme.inc/theme_table() if not defined
 * o 'placeholder' (to display current revision status)
 * o 'username'
 * Uses the following style-classes (see revisioning.css)
 * o 'table-revisions'
 * o 'revision-current' and 'published'
 * o 'revision-pending'
 * @param $form
 * @return unknown_type
 */
function theme_revisioning_revisions_summary($form) {

  // Need node info, fortunately node_load() employs a cache so is efficient
  $node = node_load($form['nid']['#value']);

  $css_path = drupal_get_path('module', 'revisioning') .'/revisioning.css';
  drupal_add_css($css_path, 'module', 'all', FALSE);

  // Set up the table rows
  $rows = array();
  $revision_ids = element_children($form['info']);

  $show_diff = count($revision_ids) >= 2 && module_exists('diff');
  $show_taxonomy_terms = module_exists('taxonomy') &&
    (count(taxonomy_get_vocabularies()) > 0) && variable_get("show_taxonomy_terms", TRUE);

  // Set up the table header
  $header = array(t('Revision'));
  if ($show_diff) {
    $header[] = array('data' => drupal_render($form['submit']), 'class' => 'form-submit');
  }
  if ($show_taxonomy_terms) {
    $header[] = t('Term');
  }
  $header[] = t('Status');

  $is_initial_unpublished_draft = !$node->status && (count($revision_ids) == 1);
  foreach ($revision_ids as $vid) {
    $row = array();
    // Revision info
    $row[] = drupal_render($form['info'][$vid]);
    // Compare checkbox
    if ($show_diff) {
      $row[] = array('data' => drupal_render($form['tickbox'][$vid]));
    }
    // Term
    if ($show_taxonomy_terms) {
      $row[] = filter_xss(drupal_render($form['term'][$vid]));
    }
    // Publication status
    $is_current = ($vid == $node->vid);
    $is_pending = ($vid > $node->vid) || $is_initial_unpublished_draft;
    if ($is_pending) {
      $row[] = array('data' => t('in draft/pending publication'));
    }
    else {
      $row[] = array('data' => $is_current && $node->status ? theme('placeholder', t('current revision (published)')) : t('archived'));
    }
    // Apply css
    $row_style = $is_current ? 'revision-current' : ($is_pending ? 'revision-pending' : NULL);
    if ($is_current && $node->status) {
      $row_style .= ' published';
    }
    $rows[] = array('data' => $row, 'class' => $row_style);
  }
  $attributes = array('class' => 'table-revisions');
  $content = theme(array('table_revisions', 'table'), $header, $rows, $attributes, $caption = NULL);
  $submenu_links = _revisioning_generate_node_links_according_to_permissions($node);
  return theme(array('revisions_summary'), $submenu_links, $content) . drupal_render($form);
}

/**
 * Implement (in your own module) the function below if you want to override
 * the way in which the Revisions table is constructed.
 * If you do, don't forget to register this theme_hook() via <your_module>_theme()
 * in a manner similar to revisioning_theme() in this file.
 *
 * @param $header
 * @param $rows
 * @return themed HTML, see for instance /includes/theme.inc/theme_table() and
 *         diff.module/theme_diff_table()
 *
 * @ingroup themeable
 *
function theme_table_revisions($header, $rows) {
}
 */

/**
 * Theme the revisions summary of the supplied node.
 *
 * @param $node
 *   Node whose revisions to display
 * @return
 *   Themed table HTML
 *
 * @ingroup themeable
 */
function _theme_revisions_summary(&$node) {
  drupal_set_title(t('Revisions for %title', array('%title' => $node->title)));
  return drupal_get_form('revisioning_revisions_summary', $node->nid);
}

function _theme_revisions_pending_block($nodes) {
  $max_num_shown = variable_get('revisioning_block_num_pending', 5);
  $nodes_to_display = array_slice($nodes, 0, $max_num_shown);
  $links = array();
  foreach ($nodes_to_display as $node) {
    $vid = revisioning_get_latest_revision_id($node->nid);
    $links[] = l($node->title, "node/$node->nid/revisions/$vid/view");
  }
  $css_path = drupal_get_path('module', 'revisioning') .'/revisioning.css';
  drupal_add_css($css_path, 'module', 'all', FALSE); // also loads /revisioning-rtl.css
  $block = array();
  $title_link = trim(variable_get('revisioning_content_summary_page', ''));
  if (empty($title_link)) {
    if (module_exists('module_grants_monitor') && user_tools_user_any_access(module_grants_monitor_perm())) {
      $title_link = 'accessible-content';
    }
    else {
      $title_link = 'admin/content/node';
    }
  }
  $block['subject'] = l(t('!num_revisions pending',
    array('!num_revisions' => format_plural(count($nodes), '1 revision', '@count revisions'))),
    $title_link);
  $block['content'] = theme('item_list', $links);
  return $block;
}


/**
 * Return an array of hyperlinks representing the operations the logged-in user
 * is allowed to perform on the supplied node.
 *
 * @param $node
 * @param $link_type
 *   The type of link, e.g. MENU_IS_LOCAL_TASK, may affect the rendering via
 *   theme('menu_item_link'), if overridden (eg zen_theme_menu_item_link()).
 * @return array of themed hyperlinks
 */
function _revisioning_generate_node_links_according_to_permissions($node, $link_type = 0) {
  $nid = $node->nid;
  $links = array();
  if (_revisioning_node_revision_access('publish revisions', $node)) {
    $link['title'] = t('Publish');
    $link['href'] = "node/$nid/revisions/$node->vid/publish";
  //$link['localized_options']['query'] = drupal_get_destination();
    $links[] = $link;
  }
  elseif (_revisioning_node_revision_access('unpublish current revision', $node)) {
    $link['title'] = t('Unpublish current revision');
    $link['href'] = "node/$nid/unpublish";
  //$link['localized_options']['query'] = drupal_get_destination();
    $links[] = $link;
  }
  if (_revisioning_node_revision_access('delete archived revisions', $node)) {
    $num_archived = revisioning_get_number_of_archived_revisions($node);
    if ($num_archived > 0) {
      $link['title'] = t('Delete archived');
      $link['href'] = "node/$nid/revisions/delete-archived";
      $links[] = $link;
    }
  }
  if (_revisioning_node_revision_access('delete node', $node)) {
    $link['title'] = // avoiding format_plural [#557050]
      ($node->num_revisions == 1)
      ? t('Delete')
      : ($node->num_revisions == 2 ? t('Delete both revisions') : t('Delete all @count revisions', array('@count' => $node->num_revisions)));
    $link['href'] = "node/$nid/delete";
  //$link['localized_options']['query'] = '';
    $links[] = $link;
  }
  $themed_links = array();
  foreach ($links as $link) {
    $link['type'] = $link_type;
    $themed_links[] = theme('menu_item_link', $link);
  }
  return $themed_links;
}
