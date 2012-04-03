<?php

/**
 * @file
 * Administrative page callbacks for the linkchecker module.
 */

function linkchecker_admin_settings_form(&$form_state) {

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );
  $form['settings']['linkchecker_scan_nodetypes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Scan node types for links'),
    '#default_value' => variable_get('linkchecker_scan_nodetypes', array()),
    '#options' => array_map('check_plain', node_get_types('names')),
    '#description' => t('Enable link checking for the selected node type(s).'),
  );

  $comment_dependencies = '<div class="admin-dependencies">';
  $comment_dependencies .= t('Depends on: !dependencies', array('!dependencies' => (module_exists('comment') ? t('@module (<span class="admin-enabled">enabled</span>)', array('@module' => 'Comment')) : t('@module (<span class="admin-disabled">disabled</span>)', array('@module' => 'Comment')))));
  $comment_dependencies .= '</div>';

  $form['settings']['linkchecker_scan_comments'] = array(
    '#default_value' => variable_get('linkchecker_scan_comments', 0),
    '#type' => 'checkbox',
    '#title' => t('Scan comments for links'),
    '#description' => t('Enable this checkbox if links in comments of the above selected node type(s) should be checked.') . $comment_dependencies,
    '#disabled' => module_exists('comment') ? FALSE : TRUE,
  );
  $form['settings']['linkchecker_scan_blocks'] = array(
    '#default_value' => variable_get('linkchecker_scan_blocks', 0),
    '#type' => 'checkbox',
    '#title' => t('Scan blocks for links'),
    '#description' => t('Enable this checkbox if links in blocks should be checked.'),
  );
  $form['settings']['linkchecker_fqdn_only'] = array(
    '#type' => 'select',
    '#title' => t('What type of links should be checked?'),
    '#description' => t('A full qualified link (http://example.com/foo/bar) to a page is considered external, whereas an absolute (/foo/bar) or relative link (node/123) without a domain is considered internal.'),
    '#default_value' => variable_get('linkchecker_fqdn_only', 1),
    '#options' => array(
      '0' => t('Internal and external'),
      '1' => t('External only (http://example.com/foo/bar)'),
      '2' => t('Internal only (node/123)'),
    ),
  );

  $form['tag'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link extraction'),
    '#collapsible' => FALSE,
  );
  $form['tag']['linkchecker_extract_from_a'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_a', 1),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;a&gt;</code> and <code>&lt;area&gt;</code> tags'),
    '#description' => t('Enable this checkbox if normal hyperlinks should be extracted. The anchor element defines a hyperlink, the named target destination for a hyperlink, or both. The area element defines a hot-spot region on an image, and associates it with a hypertext link.'),
  );
  $form['tag']['linkchecker_extract_from_audio'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_audio', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;audio&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in audio tags should be extracted. The audio element is used to embed audio content.'),
  );
  $form['tag']['linkchecker_extract_from_embed'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_embed', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;embed&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in embed tags should be extracted. This is an obsolete and non-standard element that was used for embedding plugins in past and should no longer used in modern websites.'),
  );
  $form['tag']['linkchecker_extract_from_iframe'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_iframe', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;iframe&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in iframe tags should be extracted. The iframe element is used to embed another HTML page into a page.'),
  );
  $form['tag']['linkchecker_extract_from_img'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_img', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;img&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in image tags should be extracted. The img element is used to add images to the content.'),
  );
  $form['tag']['linkchecker_extract_from_object'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_object', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;object&gt;</code> and <code>&lt;param&gt;</code> tags'),
    '#description' => t('Enable this checkbox if multimedia and other links in object and their param tags should be extracted. The object tag is used for flash, java, quicktime and other applets.'),
  );
  $form['tag']['linkchecker_extract_from_source'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_source', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;source&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in source tags should be extracted. The source element is used to specify multiple media resources for audio and video elements.'),
  );
  $form['tag']['linkchecker_extract_from_video'] = array(
    '#default_value' => variable_get('linkchecker_extract_from_video', 0),
    '#type' => 'checkbox',
    '#title' => t('Extract links in <code>&lt;video&gt;</code> tags'),
    '#description' => t('Enable this checkbox if links in video tags should be extracted. The video element is used to embed video content.'),
  );

  // Get all filters available on the system.
  $filters = filter_list_all();
  $filter_options = array();
  foreach ($filters as $filter) {
    $name = $filter->module . '/' . $filter->delta;
    if (in_array($name, explode('|', LINKCHECKER_DEFAULT_FILTER_BLACKLIST))) {
      $filter_options[$name] = t('!title <span class="form-required">(Recommended)</span>', array('!title' => $filter->name));
    }
    else {
      $filter_options[$name] = $filter->name;
    }
  }
  $form['tag']['linkchecker_filter_blacklist'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Filters disabled for link extraction'),
    '#default_value' => variable_get('linkchecker_filter_blacklist', explode('|', LINKCHECKER_DEFAULT_FILTER_BLACKLIST)),
    '#options' => $filter_options,
    '#description' => t('If a filter has been enabled for an input format it runs first and afterwards the link extraction. This helps the link checker module to find all links normally created by custom filters (e.g. Markdown filter, Bbcode). All filters used as an inline references (e.g. Weblink filter <code>[link: id]</code>) to other content and filters only wasting processing time (e.g. Line break converter) should be disabled. This setting does not have any effect on how content is shown on a page. This feature optimizes the internal link extraction process for link checker and prevents false alarms about broken links in content not having the real data of a link.'),
  );

  $form['check'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check settings'),
    // '#description' => t('For simultaneous link checks it is highly recommended to install the <a href="@curl">cURL</a> library. This may be <strong>necessary</strong> on larger sites with very many links, but may still improve (speed up), link checking performance on smaller sites.', array('@curl' => 'http://www.php.net/manual/en/book.curl.php')),
    '#collapsible' => FALSE,
  );
  $form['check']['linkchecker_check_useragent'] = array(
    '#type' => 'select',
    '#title' => t('User-Agent'),
    '#description' => t('Defines the user agent that will be used for checking links on remote sites. If someone blocks the standard Drupal user agent you can try with a more common browser.'),
    '#default_value' => variable_get('linkchecker_check_useragent', 'Drupal (+http://drupal.org/)'),
    '#options' => array(
      'Drupal (+http://drupal.org/)' => 'Drupal (+http://drupal.org/)',
      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1;)' => 'Windows XP / Internet Explorer 7.0',
      'Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.9.0.5) Gecko/2008120122 Firefox/3.0.5' => 'Windows XP / Mozilla Firefox 3.0.5',
      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0;)' => 'Windows Vista / Internet Explorer 7.0',
      'Mozilla/5.0 (Windows; U; Windows NT 6.0; de; rv:1.9.0.5) Gecko/2008120122 Firefox/3.0.5' => 'Windows Vista / Mozilla Firefox 3.0.5',
    ),
  );
/* For now it's better to guess this value from max_execution_time.
   $form['check']['linkchecker_check_links_max'] = array(
    '#type' => 'select',
    '#title' => t('Check number of links per cron run'),
    '#description' => t('Defines the number of links that will be checked per cron run. The possible setting hardly depends on your PHP timeout value and remote servers speed and may increased if <a href="@curl">cURL</a> is installed and use simultaneous request checking. All cron jobs may fail, if this setting is too high!', array('@curl' => 'http://www.php.net/manual/en/book.curl.php')),
    '#default_value' => variable_get('linkchecker_check_links_max', 10),
    '#options' => drupal_map_assoc(array(5, 10, 25, 50, 100, 200, 250, 300, 350, 400, 450, 500, 750, 1000)),
  ); */
  $form['check']['linkchecker_check_links_interval'] = array(
    '#type' => 'select',
    '#title' => t('Check interval for links'),
    '#description' => t('This interval setting defines how often cron will re-check the status of links.'),
    '#default_value' => variable_get('linkchecker_check_links_interval', 2419200),
    '#options' => drupal_map_assoc(array(86400, 172800, 259200, 604800, 1209600, 2419200, 4838400), 'format_interval'),
  );
  $form['check']['linkchecker_disable_link_check_for_urls'] = array(
    '#default_value' => variable_get('linkchecker_disable_link_check_for_urls', LINKCHECKER_RESERVED_DOCUMENTATION_DOMAINS),
    '#type' => 'textarea',
    '#title' => t('Do not check the link status of links containing these URLs'),
    '#description' => t('By default this list contains the domain names reserved for use in documentation and not available for registration. See <a href="@rfc-2606">RFC 2606</a>, Section 3 for more information. URLs on this list are still extracted, but the link setting <em>Check link status</em> becomes automatically disabled to prevent false alarms. If you change this list you need to clear all link data and re-analyze your content. Otherwise this setting will only affect new links added after the configuration change.', array('@rfc-2606' => 'http://www.rfc-editor.org/rfc/rfc2606.txt')),
    '#wysiwyg' => FALSE,
  );

  $form['error'] = array(
    '#type' => 'fieldset',
    '#title' => t('Error handling'),
    '#description' => t('Defines error handling and custom actions to be executed if specific HTTP requests are failing.'),
    '#collapsible' => FALSE,
  );
  $form['error']['linkchecker_action_status_code_301'] = array(
    '#title' => t('Update permanently moved links'),
    '#description' => t('If enabled, outdated links in content providing a status <em>Moved Permanently</em> (status code 301) are automatically updated to the most recent URL. If used, it is recommended to use a value of <em>three</em> to make sure this is not only a temporarily change. This feature trust sites to provide a valid permanent redirect. A new node revision is automatically created on link updates if <em>create new revision</em> is enabled in the <a href="@node_types">node type</a> workflow settings. It is recommended to create new revisions for all link checker enabled node types. Link updates are nevertheless always logged in <a href="@dblog">recent log entries</a>.', array('@dblog' => url('admin/reports/dblog'), '@node_types' => url('admin/content/types'))),
    '#type' => 'select',
    '#default_value' => variable_get('linkchecker_action_status_code_301', 0),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('After one failed check'),
      2 => t('After two failed checks'),
      3 => t('After three failed checks'),
      5 => t('After five failed checks'),
      10 => t('After ten failed checks'),
    ),
  );
  $form['error']['linkchecker_action_status_code_404'] = array(
    '#title' => t('Unpublish node on file not found error'),
    '#description' => t('If enabled, a node with one or more broken links (status code 404) will be unpublished and moved to moderation queue for review after the number of specified checks failed. If used, it is recommended to use a value of <em>three</em> to make sure this is not only a temporarily error.'),
    '#type' => 'select',
    '#default_value' => variable_get('linkchecker_action_status_code_404', 0),
    '#options' => array(
      0 => t('Disabled'),
      1 => t('After one file not found error'),
      2 => t('After two file not found errors'),
      3 => t('After three file not found errors'),
      5 => t('After five file not found errors'),
      10 => t('After ten file not found errors'),
    ),
  );
  $form['error']['linkchecker_ignore_response_codes'] = array(
    '#default_value' => variable_get('linkchecker_ignore_response_codes', "200\n206\n302\n304\n401\n403"),
    '#type' => 'textarea',
    '#title' => t("Don't treat these response codes as errors"),
    '#description' => t('One HTTP status code per line, e.g. 403.'),
    '#wysiwyg' => FALSE,
  );

  // Buttons are only required for testing and debugging reasons.
  $description = '<p>' . t('These actions will either clear all link checker tables in the database and/or analyze all selected node types, blocks and cck fields (see settings above) for new/updated/removed links. Normally there is no need to press one of these buttons. Use this only for immediate cleanup tasks and to force a full re-build of the links to be checked in the linkchecker tables. Keep in mind that all custom link settings will be lost if you clear link data!') . '</p>';
  $description .= '<p>' . t('<strong>Note</strong>: These functions ONLY collect the links, they do not evaluate the HTTP response codes, this will be done during normal cron runs.') . '</p>';

  $form['clear'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maintenance'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['clear']['linkchecker_analyze'] = array(
    '#type' => 'submit',
    '#value' => t('Reanalyze content for links'),
    '#submit' => array('linkchecker_analyze_links_submit'),
  );
  $form['clear']['linkchecker_clear_analyze'] = array(
    '#type' => 'submit',
    '#value' => t('Clear link data and analyze content for links'),
    '#submit' => array('linkchecker_clear_analyze_links_submit'),
  );

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );

  return $form;
}

function linkchecker_admin_settings_form_validate($form, &$form_state) {
  $form_state['values']['linkchecker_disable_link_check_for_urls'] = trim($form_state['values']['linkchecker_disable_link_check_for_urls']);
  $form_state['values']['linkchecker_ignore_response_codes'] = trim($form_state['values']['linkchecker_ignore_response_codes']);
  $ignore_response_codes = preg_split('/(\r\n?|\n)/', $form_state['values']['linkchecker_ignore_response_codes']);
  foreach ($ignore_response_codes as $ignore_response_code) {
    if (!_linkchecker_isvalid_response_code($ignore_response_code)) {
      form_set_error('linkchecker_ignore_response_codes', t('Invalid response code %code found.', array('%code' => $ignore_response_code)));
    }
  }

  // Prevent the removal of RFC documentation domains. This are the official and
  // reserved documentation domains and not "example" hostnames!
  $linkchecker_disable_link_check_for_urls = array_filter(preg_split('/(\r\n?|\n)/', $form_state['values']['linkchecker_disable_link_check_for_urls']));
  $form_state['values']['linkchecker_disable_link_check_for_urls'] = implode("\n", array_unique(array_merge(explode("\n", LINKCHECKER_RESERVED_DOCUMENTATION_DOMAINS), $linkchecker_disable_link_check_for_urls)));
}

function linkchecker_admin_settings_form_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  // Re-scan items, if node types or comment or block selection have been changed.
  $additional_nodetypes_selected = array_diff($form_state['values']['linkchecker_scan_nodetypes'], $form['settings']['linkchecker_scan_nodetypes']['#default_value']);
  if (!empty($additional_nodetypes_selected) || $form_state['values']['linkchecker_scan_comments'] > $form['settings']['linkchecker_scan_comments']['#default_value']) {
    $node_types = array_keys(array_filter($form_state['values']['linkchecker_scan_nodetypes']));

    // If one or more node types have been selected.
    if (!empty($node_types)) {
      module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
      batch_set(_linkchecker_batch_import_nodes($node_types));

      // If comment scanning of node types has been selected.
      if ($form_state['values']['linkchecker_scan_comments'] > $form['settings']['linkchecker_scan_comments']['#default_value']) {
        batch_set(_linkchecker_batch_import_comments($node_types));
      }
    }
  }

  // If block scanning has been selected.
  if ($form_state['values']['linkchecker_scan_blocks'] > $form['settings']['linkchecker_scan_blocks']['#default_value']) {
    module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
    batch_set(_linkchecker_batch_import_boxes());
  }
}

/**
 * Submit callback; Analyze all node types, boxes and cck fields.
 */
function linkchecker_analyze_links_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  // Start batch and analyze all nodes.
  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types)) {
    module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
    batch_set(_linkchecker_batch_import_nodes($node_types));
    if (variable_get('linkchecker_scan_comments', 0)) {
      batch_set(_linkchecker_batch_import_comments($node_types));
    }
  }

  if (variable_get('linkchecker_scan_blocks', 0)) {
    module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
    batch_set(_linkchecker_batch_import_boxes());
  }
}

/**
 * Submit callback; Clear link data and analyze all node types, boxes and cck fields.
 */
function linkchecker_clear_analyze_links_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  unset($form_state['values']['linkchecker_analyze'], $form_state['values']['linkchecker_clear_analyze']);

  // Save form settings.
  system_settings_form_submit($form, $form_state);

  db_query("TRUNCATE TABLE {linkchecker_nodes}");
  db_query("TRUNCATE TABLE {linkchecker_comments}");
  db_query("TRUNCATE TABLE {linkchecker_boxes}");
  db_query("TRUNCATE TABLE {linkchecker_links}");

  // Start batch and analyze all nodes.
  $node_types = array_keys(array_filter(variable_get('linkchecker_scan_nodetypes', array())));
  if (!empty($node_types)) {
    module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
    batch_set(_linkchecker_batch_import_nodes($node_types));
    if (variable_get('linkchecker_scan_comments', 0)) {
      batch_set(_linkchecker_batch_import_comments($node_types));
    }
  }

  if (variable_get('linkchecker_scan_blocks', 0)) {
    module_load_include('inc', 'linkchecker', '/includes/linkchecker.batch');
    batch_set(_linkchecker_batch_import_boxes());
  }
}
