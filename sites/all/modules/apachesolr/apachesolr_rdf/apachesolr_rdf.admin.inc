<?php
// $Id: apachesolr_rdf.admin.inc,v 1.1.2.15 2009/11/01 23:31:38 drunkenmonkey Exp $

//
// General
//

/**
 * An overview of the overall status of this module.
 */
function apachesolr_rdf_settings_overview() {
  // Display status info, but only if there are enabled servers
  if (_apachesolr_rdf_servers(TRUE)) {
    $requirements = apachesolr_rdf_requirements('runtime');
    $requirements = $requirements['apachesolr_rdf'];
    if ($requirements['severity'] == REQUIREMENT_ERROR) {
      drupal_set_message("<p>{$requirements['value']}</p>" .
          $requirements['description'], 'error');
    }
    else {
      drupal_set_message($requirements['value']);
    }
  }

  return theme('box', t('Servers'),
          apachesolr_rdf_settings_servers_table() .
          apachesolr_rdf_settings_add_inline('server')) .
      theme('box', t('Indexes'),
          apachesolr_rdf_settings_table('index') .
          apachesolr_rdf_settings_add_inline('index')) .
      theme('box', t('Searches'),
          apachesolr_rdf_settings_table('search') .
          apachesolr_rdf_settings_add_inline('search'));
}

/**
 * Displays a link for adding a new server/index/search.
 */
function apachesolr_rdf_settings_add_inline($type) {
  return '<p>' . l("Add new $type", "admin/settings/apachesolr_rdf/$type/add") .
      '</p>';
}

/**
 * Shows a form for confirming some action.
 */
function apachesolr_rdf_confirm_form(&$form_state, $type, $action, $info) {
  $id = $info['id'];

  $messages = array(
    'server' => array(
      'clear' => array(t("Do you really want to clear this server's index?"),
          t("Search queries on this server won't return the correct results " .
          'until all resources are re-indexed by cron runs. Use this only if ' .
          'false data has accidentally been indexed.'),
          t("Successfully deleted the server's indexed data. Run cron to " .
          're-index data!')),
      'delete' => array(t('Do you really want to delete this server?'),
          t("This will wipe the server's index and delete all associated " .
          'settings, indexes and searches.<br />' .
          '<strong>Use with extreme care!</strong>'),
          t('Successfully deleted the server.')),
    ),
    'index' => array(
      'reindex' => array(t('Do you really want to re-index this data?'),
          t('The revised data will continuously replace the old data. ' .
          'Searches will still return results, but the updated data is only ' .
          'taken into account once cron is run to index the data.'),
          t('Successfully marked the index for re-indexing.')),
      'clear' => array(t("Do you really want to delete this index' data?"),
          t("Search queries on this index won't return the correct results " .
          'until all resources are re-indexed by cron runs. Use this only if ' .
          'false data has accidentally been indexed.'),
          t("Successfully deleted the index' indexed data. Run cron to " .
          're-index data!')),
      'delete' => array(t('Do you really want to delete this index?'),
          t('This will delete the indexed data from the server and all ' .
          'settings associated with this index. Server and search settings ' .
          'will be unaffected.'),
          t('Successfully deleted the index.')),
    ),
    'search' => array(
      'delete' => array(t('Do you really want to delete this search?'),
          t("This will delete this search's path from the menu registry and " .
          'delete all settings associated with this search. Server and index ' .
          'settings will be unaffected.'),
          t('Successfully deleted the search.')),
    ),
  );

  $form = array(
    'type' => array(
      '#type' => 'value',
      '#value' => $type,
    ),
    'action' => array(
      '#type' => 'value',
      '#value' => $action,
    ),
    'id' => array(
      '#type' => 'value',
      '#value' => $id,
    ),
    'message' => array(
      '#type' => 'value',
      '#value' => $messages[$type][$action][2],
    ),
  );
  $desc = "<h3>{$messages[$type][$action][0]}</h3>" .
          "{$messages[$type][$action][1]}";
  return confirm_form($form, $info['name'],
      "admin/settings/apachesolr_rdf/$type/$id", $desc, t('Confirm'),
      t('Cancel'));
}

/**
 * Submit function for apachesolr_rdf_confirm_form().
 */
function apachesolr_rdf_confirm_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  $type = $values['type'];
  $action = $values['action'];
  $id = $values['id'];

  $function = "apachesolr_rdf_{$action}_{$type}";
  if ($function($id)) {
    drupal_set_message($values['message']);
  }
  else {
    drupal_set_message(t('An error has occurred while performing the ' .
      'required action. For details, see the logs.'), 'error');
  }

  $form_state['redirect'] = $action == 'delete'
      ? "admin/settings/apachesolr_rdf"
      : "admin/settings/apachesolr_rdf/$type/$id";
}

/**
 * Returns a page showing information about the specified server/index/search.
 */
function apachesolr_rdf_settings_object_view($type, $info) {
  if ($type == 'server') {
    $server = $info;
  }
  else {
    $server = apachesolr_rdf_server_load($info['server']);
  }
  if ($info['enabled']) {
    $url = _apachesolr_rdf_server_url($server);
    if (apachesolr_rdf_server_status($server['host'], $server['port'],
        $server['path'])) {
      drupal_set_message(t('The server at !url is accessible.',
          array('!url' => l($url, $url))));
    }
    else {
      drupal_set_message(t('The server at !url could not be reached!',
          array('!url' => l($url, $url))), 'error');
    }
  }


  $titles = array(
    'name' => t('Name'),
    'status' => t('Status'),
    'search_path' => t('Path'),
    'description' => t('Description'),
    'url' => t('URL'),
    'context' => t('Context'),
    'cron_limit' => t('Cron Limit'),
    'permission' => t('Permission'),
    'server_name' => t('Server'),
    'schema_name' => t('Schema'),
    'schema_description' => t('Schema description'),
  );

  $schema = apachesolr_rdf_schema_load($info['schema']);
  $info['schema_name'] = $schema['name'];
  $info['schema_description'] = $schema['description'];

  $dest = "admin/settings/apachesolr_rdf/$type/{$info['id']}";
  $enable_link = "$dest/enable";
  $info['status'] = $info['enabled'] ? t('Enabled') : t('Disabled');
  if ($info['enabled']) {
    $info['status'] .= ' (' . l(t('click to disable'), $enable_link,
        array('query' => array('destination' => $dest))) . ')';
  }
  else if ($type == 'server' || $server['enabled']) {
    $info['status'] .= ' (' . l(t('click to enable'), $enable_link,
        array('query' => array('destination' => $dest))) . ')';
  }

  if (!empty($info['description'])) {
    $info['description'] = '<p>' . str_replace("\n", "</p>\n<p>",
          check_plain($info['description'])) . '</p>';
  }

  switch ($type) {
    case 'server':
      $url = _apachesolr_rdf_server_url($server);
      $info['url'] = l($url, $url);
      break;
    case 'search':
      $path = "search/apachesolr_rdf_{$info['id']}";
      $info['search_path'] = l($path, $path);
      $info['server_name'] = l($server['name'],
          "admin/settings/apachesolr_rdf/server/{$server['id']}");
      break;
    case 'index':
      $info['server_name'] = l($server['name'],
          "admin/settings/apachesolr_rdf/server/{$server['id']}");
      $info['context'] = $info['resources']['context'];
      $info['context'] = l($info['context'], $info['context']);
      break;
    default:
      // Wait, what? Well, such things happen, I guess...
      // Just ignore it, it's all in your head...
  }

  $output = "<dl>\n";
  foreach ($titles as $field => $name) {
    if (isset($info[$field])) {
      $output .= "<dt>$name</dt>\n<dd>{$info[$field]}</dd>\n";
    }
  }
  $output .= '</dl>';
  return $output;
}

/**
 * Enables/Disables the specified server/index/search.
 */
function apachesolr_rdf_settings_object_enable($type, $info) {
  $status = $info['enabled'] ? 0 : 1;

  switch ($type) {
    case 'server':
      $plural = 'servers';
      $wildcard = '%d';
      break;
    case 'index':
      $plural = 'indexes';
      $wildcard = '%d';
      break;
    case 'search':
      $plural = 'searches';
      $wildcard = "'%s'";
      break;
    default:
      // No.
  }

  $destination = isset($_GET['destination'])
      ? $_GET['destination'] : 'admin/settings/apachesolr_rdf';

  if (!$status && $type != 'server') {
    // Check if index/search can be enabled
    $server = apachesolr_rdf_server_load($info['server']);
    if (!$server['enabled']) {
      $message = $type == 'index' ? t('The index could not be enabled, since ' .
          'the server it belongs to is still disabled. You have to re-enable ' .
          'the server before enabling the index.') : t('The search could not ' .
          'be enabled, since the server it belongs to is still disabled. You ' .
          'have to re-enable the server before enabling the search.');
      drupal_set_message($message, 'error');
      drupal_goto($destination);
    }
  }
  else if (!$status) {
    db_query('UPDATE {apachesolr_rdf_indexes} SET enabled = 0 ' .
        'WHERE server = %d', $info['id']);
    db_query('UPDATE {apachesolr_rdf_searches} SET enabled = 0 ' .
        'WHERE server = %d', $info['id']);
  }

  if (db_query("UPDATE {apachesolr_rdf_$plural} SET enabled = $status " .
      "WHERE id = $wildcard", $info['id'])) {
    if ($type == 'search') {
      menu_rebuild();
    }
    drupal_set_message(t("The $type was successfully " .
        ($status ? 'enabled' : 'disabled') . '.'));
  }
  else {
    drupal_set_message(t('An error has occurred while saving the changes. ' .
        'For details, see the logs.'), 'error');
  }

  drupal_goto($destination);
}

/**
 * Shows a table of all defined Apache Solr RDF indexes or searches.
 */
// TODO: Add sort functionality?
function apachesolr_rdf_settings_table($type) {
  $header = array(t('Name'), t('Server'), t('Schema'), t('Status'),
      t('Actions'));
  $rows = array();
  $prefix = "admin/settings/apachesolr_rdf/$type";

  $function = "_apachesolr_rdf_{$type}es";
  foreach ($function() as $id => $info) {
    $server = apachesolr_rdf_server_load($info['server']);
    $schema = apachesolr_rdf_schema_load($info['schema']);
    if ($schema) {
      $schema = $schema['name'];
    }
    else {
      $schema = t('Unknown');
    }

    if($info['enabled']) {
      $status = t('Enabled');
      $actions = l(t('Disable'), "$prefix/$id/enable") . ' | ';
    }
    else {
      $status = t('Disabled');
      $server = apachesolr_rdf_server_load($info['server']);
      $actions = $server['enabled']
          ? l(t('Enable'), "$prefix/$id/enable") . ' | '
          : '';
    }

    $actions .= l(t('Edit'), "$prefix/$id/edit") . ' | ';
    if ($type == 'index') {
      $actions .= l(t('Re-Index'), "$prefix/$id/reindex") . ' | ';
      $actions .= l(t('Clear'), "$prefix/$id/clear") . ' | ';
    }
    $actions .= l(t('Delete'), "$prefix/$id/delete");

    $rows[] = array(l($info['name'], "$prefix/$id"), l($server['name'],
        "admin/settings/apachesolr_rdf/server/{$info['server']}"), $schema,
        $status, $actions);
  }

  if (empty($rows)) {
    return '<p>' . t("There are currently no {$type}es defined.") . '</p>';
  }

  return theme('table', $header, $rows);
}

//
// Servers
//

/**
 * Shows a table of all defined Apache Solr RDF servers.
 */
// TODO: Add sort functionality?
function apachesolr_rdf_settings_servers_table() {
  $header = array(t('Name'), t('URL'), t('Schema'), t('Status'), t('Actions'));
  $rows = array();
  $prefix = 'admin/settings/apachesolr_rdf/server';

  foreach (_apachesolr_rdf_servers() as $id => $info) {
    $url = _apachesolr_rdf_server_url($info);
    $schema = apachesolr_rdf_schema_load($info['schema']);
    if ($schema) {
      $schema = $schema['name'];
    }
    else {
      $schema = t('Unknown');
    }
    $status = $info['enabled'] ? t('Enabled') : t('Disabled');
    $status_action = $info['enabled']
        ? l(t('Disable'), "$prefix/$id/enable")
        : l(t('Enable'), "$prefix/$id/enable");
    $actions = $status_action . ' | ' .
        l(t('Edit'), "$prefix/$id/edit") . ' | ' .
        l(t('Clear'), "$prefix/$id/clear") . ' | ' .
        l(t('Delete'), "$prefix/$id/delete");
    $rows[] = array(l($info['name'], "$prefix/$id"), l($url, $url), $schema,
        $status, $actions);
  }

  if (empty($rows)) {
    return '<p>' . t('There are currently no servers defined.') . '</p>';
  }

  return theme('table', $header, $rows);
}

/**
 * Displays a two-step form for adding a new Apache Solr RDF server, or a form
 * for editing one, if $info is set.
 */
function apachesolr_rdf_settings_server_edit(&$form_state, $info = FALSE) {
  if (!$info && empty($form_state['storage']['schema'])) {
    // First step of adding a server
    $options = array();
    foreach (_apachesolr_rdf_schemas() as $id => $info) {
      $options[$id] = $info['name'];
    }
    asort($options);

    $form['schema'] = array(
      '#type' => 'select',
      '#title' => t('Schema'),
      '#description' => t('The schema used by the Solr server and, hence, ' .
          'the method that should be used for indexing and searching. ' .
          'This setting cannot be changed afterwards!'),
      '#options' => $options,
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
    );

    return $form;
  }

  $schema_id = $info ? $info['schema'] : $form_state['storage']['schema'];
  $schema = apachesolr_rdf_schema_load($schema_id);

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('Determines the status of this server, and all ' .
        'associated indexes and searches.') .
        ($info && !$info['enabled'] ?
            ' ' . t('Note that if you re-enable this server, associated ' .
            "indexes and searches won't be enabled automatically!") : ''),
    '#default_value' => $info ? $info['enabled'] : TRUE,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A human-readable name for this server. Will default ' .
        'to an URL representation.'),
    '#default_value' => $info ? $info['name'] : '',
    '#maxlength' => 100,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t("A description of this server's purpose."),
    '#default_value' => $info ? $info['description'] : '',
  );
  $form['server_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server information'),
    '#description' => t('The information for contacting the server. These ' .
        'settings cannot be edited after the server was added!'),
    '#collapsible' => TRUE,
    '#collapsed' => (boolean) $info,
    'host' => array(
      '#type' => 'textfield',
      '#title' => t('Host'),
      '#description' => t("The Solr server's host name, e.g. \"example.com\"."),
      '#default_value' => $info ? $info['host'] : 'localhost',
      '#maxlength' => 50,
      '#disabled' => (boolean) $info,
      '#required' => !$info,
    ),
    'port' => array(
      '#type' => 'textfield',
      '#title' => t('Port'),
      '#description' => t("The Solr server's port number. The default for " .
          'the Solr example application is 8983.'),
      '#default_value' => $info ? $info['port'] : '8983',
      '#disabled' => (boolean) $info,
      '#required' => !$info,
    ),
    'path' => array(
      '#type' => 'textfield',
      '#title' => t('Path'),
      '#description' => t('The path on the host on which Solr can be ' .
          'contacted. The default for the Solr example application is ' .
          '"/solr".'),
      '#default_value' => $info ? $info['path'] : '/solr',
      '#maxlength' => 40,
      '#disabled' => (boolean) $info,
      '#required' => !$info,
    ),
  );
  $form['schema'] = array(
    '#type' => 'value',
    '#value' => $info ? $info['schema'] : $form_state['storage']['schema'],
  );
  $form['schema_info'] = array(
    '#type' => 'item',
    '#title' => t('Schema'),
    '#value' => '<strong>' . $schema['name'] . '</strong><br />' .
        $schema['description'],
  );

  $schema_arguments_form = _apachesolr_rdf_get_schema_function(
      'schema_arguments_form', $schema_id);
  if ($schema_arguments_form) {
    // If there is a schema_arguments_form function, add the sub-form returned
    // by that function.
    $schema_args = $schema_arguments_form($form_state, $info, 'schema_args');
    if ($schema_args) {
      $form['schema_args'] = array(
        '#type' => 'fieldset',
        '#title' => t('Schema settings'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
      );
      $form['schema_args'] += $schema_args;
    }
  }

  $form['action'] = array(
    '#type' => 'value',
    '#value' => $info ? 'edit' : 'add',
  );
  if ($info) {
    $form['id'] = array(
      '#type' => 'value',
      '#value' => $info['id'],
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $info ? t('Save changes') : t('Add server'),
  );

  return $form;
}

/**
 * Validation function for apachesolr_rdf_settings_server_edit().
 */
function apachesolr_rdf_settings_server_edit_validate($form, &$form_state) {
  if (!$form_state['submitted']) {
    return;
  }

  $values = $form_state['values'];
  if (!isset($values['action'])) {
    // We are at step 1 of adding a server, nothing to validate.
    return;
  }
  if ($values['action'] == 'add') {
    // Since the host information is immutable, we only have to check it when
    // adding a new server.
    $host = $values['host'];
    $port = $values['port'];
    $path = $values['path'];
    if (((string) ((int) $port)) != $port || $port < 0 || $port > 65535) {
      form_set_error('port',
          t('The port has to be an integer between 0 and 65535!'));
    }
    if (db_result(db_query('SELECT id FROM {apachesolr_rdf_servers} WHERE ' .
        "host = '%s' AND port = %d AND path = '%s'", $host, $port, $path))) {
      form_set_error('host', t('The server with the url @url is already ' .
          'defined! You have to specify a yet unused server.',
          array('@url' => _apachesolr_rdf_server_url($values))));
    }
  }

  if (!empty($form['schema_args'])) {
    $schema = $values['schema'];
    $schema_argument_form = _apachesolr_rdf_get_schema_function(
        'schema_arguments_form', $schema);
    $schema_argument_form_validate = "{$schema_argument_form}_validate";
    if (function_exists($schema_argument_form_validate)) {
      $schema_argument_form_validate($form['schema_args'],
          $values['schema_args'], 'schema_args][');
    }
  }
}

/**
 * Submit function for apachesolr_rdf_settings_server_edit().
 */
function apachesolr_rdf_settings_server_edit_submit($form, &$form_state) {
  $values = $form_state['values'];
  unset($form_state['storage']);

  if (!isset($values['action'])) {
    // We are submitting step 1 of adding a server
    $form_state['storage']['schema'] = $values['schema'];
    $form_state['rebuild'] = TRUE;
    return;
  }

  if (empty($values['name'])) {
    $values['name'] = _apachesolr_rdf_server_url(
        $values);
  }
  extract($values, EXTR_PREFIX_ALL, 'val');

  if (isset($val_schema_args)) {
    $schema_argument_form = _apachesolr_rdf_get_schema_function(
        'schema_arguments_form', $val_schema);
    $schema_argument_form_submit = "{$schema_argument_form}_submit";
    if (function_exists($schema_argument_form_submit)) {
      $val_schema_args = $schema_argument_form_submit($val_schema_args);
    }
  }
  else {
    $val_schema_args = array();
  }

  if (isset($val_description) && trim($val_description)) {
    $desc = "'" . db_escape_string($val_description) . "'";
  }
  else {
    $desc = 'NULL';
  }

  $path_prefix = 'admin/settings/apachesolr_rdf/server';
  if ($values['action'] == 'add') {
    // Add the server
    if (! db_query('INSERT INTO {apachesolr_rdf_servers} (id, name, ' .
        'description, host, port, path, schema_id, schema_args, enabled) ' .
        "VALUES (NULL, '%s', $desc, '%s', %d, '%s', '%s', '%s', %d)", $val_name,
        $val_host, $val_port, $val_path, $val_schema,
        serialize($val_schema_args), $val_enabled)) {
      drupal_set_message(t('An error has occurred while adding the server. ' .
          'For details, see the logs.'), 'error');
      $form_state['rebuild'] = TRUE;
      return;
    }

    drupal_set_message(t('The server was successfully added.'));
    $id = db_last_insert_id('apachesolr_rdf_servers', 'id');
    $form_state['redirect'] = "$path_prefix/$id";
    return;
  }

  // We're editing the server
  $server_old = apachesolr_rdf_server_load($val_id);
  if (! db_query('UPDATE {apachesolr_rdf_servers} SET ' .
      "name = '%s', description = $desc, schema_args = '%s', enabled = %d " .
      'WHERE id = %d', $val_name, serialize($val_schema_args), $val_enabled,
      $val_id)) {
    drupal_set_message(t('An error has occurred while saving the changes. ' .
        'For details, see the logs.'), 'error');
    $form_state['rebuild'] = TRUE;
    return;
  }

  // If server was disabled, cascade the change to related indexes and searches
  if ($server_old['enabled'] && !$val_enabled) {
    db_query('UPDATE {apachesolr_rdf_indexes} SET enabled = 0 ' .
        'WHERE server = %d', $val_id);
    db_query('UPDATE {apachesolr_rdf_searches} SET enabled = 0 ' .
        'WHERE server = %d', $val_id);
  }

  $form_state['redirect'] = "$path_prefix/$val_id";
  drupal_set_message(t('The changes were successfully saved.'));
}

//
// Indexes
//

/**
 * Displays a two-step form for adding a new Apache Solr RDF index, or a form
 * for editing one, if $info is set.
 */
function apachesolr_rdf_settings_index_edit(&$form_state, $info = FALSE) {
  if (!$info && empty($form_state['storage']['server'])) {
    // First step of adding an index
    $options = array();
    foreach (_apachesolr_rdf_servers() as $id => $info) {
      $options[$id] = $info['name'];
    }
    asort($options);

    if (empty($options)) {
      drupal_set_message(t('There is no Apache Solr RDF server defined, yet. ' .
          'You have to <a href="@url">create one</a> first!', array('@url'
          => url('admin/settings/apachesolr_rdf/server/add'))), 'error');
      return;
    }

    $form['server'] = array(
      '#type' => 'select',
      '#title' => t('Server'),
      '#description' => t("The server this index' data will be stored on. " .
          'This setting cannot be changed afterwards!'),
      '#options' => $options,
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
    );

    return $form;
  }

  $server = apachesolr_rdf_server_load(
      $info ? $info['server'] : $form_state['storage']['server']);
  $schema = apachesolr_rdf_schema_load($server['schema']);

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('Determines the status of this index.') .
        (!$server['enabled'] ?
            ' ' . t("Since the server of this index isn't enabled, you " .
            'cannot enable this index now.') : ''),
    '#default_value' => $info ? $info['enabled'] : $server['enabled'],
    '#disabled' => !$server['enabled'],
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A human-readable name for this index. Will default ' .
        'to "Index #x".'),
    '#default_value' => $info ? $info['name'] : '',
    '#maxlength' => 50,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t("A description of this index' purpose."),
    '#default_value' => $info ? $info['description'] : '',
  );

  // This can be arbitrarily extended, as long as the changes are considered
  // when indexing
  $contexts[''] = '-' . t('Select one') . '-';
  $contexts += drupal_map_assoc(rdf_get_contexts());
  $form['context'] = array(
    '#type' => 'select',
    '#options' => $contexts,
    '#title' => t('Context'),
    '#description' => t('Specify the context the resources of which should ' .
        'be indexed.') . ($info ? ' ' . t('After changing this setting, you ' .
        'should <a href="@url">clear this index</a>.', array('@url' =>
        url("admin/settings/apachesolr_rdf/index/{$info['id']}/clear"))) : ''),
    '#default_value' => $info ? $info['resources']['context'] : '',
    '#required' => TRUE,
  );

  $form['cron_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Cron limit'),
    '#description' => t('The maximum number of resources indexed in one cron ' .
        'run for this index.'),
    '#default_value' => $info ? $info['cron_limit'] : '50',
    '#required' => TRUE,
  );

  $index_options_form = _apachesolr_rdf_get_schema_function(
      'index_options_form', $server['schema']);
  if ($index_options_form) {
    $index_options = $index_options_form($form_state, $info);
    if ($index_options) {
      $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Additional options'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
      );
      $form['options'] += $index_options;
    }
  }

  $form['action'] = array(
    '#type' => 'value',
    '#value' => $info ? 'edit' : 'add',
  );
  $form['server'] = array(
    '#type' => 'value',
    '#value' => $server['id'],
  );
  $form['schema'] = array(
    '#type' => 'value',
    '#value' => $server['schema'],
  );
  if ($info) {
    $form['id'] = array(
      '#type' => 'value',
      '#value' => $info['id'],
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $info ? t('Save changes') : t('Add index'),
  );

  return $form;
}

/**
 * Validation function for apachesolr_rdf_settings_index_edit().
 */
function apachesolr_rdf_settings_index_edit_validate($form, &$form_state) {
  $values = $form_state['values'];

  if (!isset($values['action'])) {
    // We are at step 1 of adding an index, nothing to validate.
    return;
  }

  $context_exists = FALSE;
  foreach (rdf_get_contexts() as $context) {
    if ($context == $values['context']) {
      $context_exists = TRUE;
      break;
    }
  }
  if (!$context_exists) {
    form_set_error('context', t('The context @context is unknown to the ' .
        'RDF module. Please specify a valid context URI!',
        array('@context' => $values['context'])));
  }

  $cl = $values['cron_limit'];
  if (((string) ((int) $cl)) != $cl || $cl <= 0) {
    form_set_error('cron_limit', t('The cron limit has to be a positive ' .
        'integer.'));
  }

  if (isset($form['options'])) {
    $index_options_form = _apachesolr_rdf_get_schema_function(
        'index_options_form', $values['schema']);
    $index_options_form_validate = "{$index_options_form}_validate";
    if (function_exists($index_options_form_validate)) {
      $index_options_form_validate($form['options'],
          $values['options'], 'options][');
    }
  }
}

/**
 * Submit function for apachesolr_rdf_settings_index_edit().
 */
function apachesolr_rdf_settings_index_edit_submit($form, &$form_state) {
  $values = $form_state['values'];
  unset($form_state['storage']);

  if (!isset($values['action'])) {
    // We are submitting step 1 of adding an index
    $form_state['storage']['server'] = $values['server'];
    $form_state['rebuild'] = TRUE;
    return;
  }

  if (empty($values['name'])) {
    $id = isset($values['id']) ? $values['id'] :
        db_result(db_query('SELECT MAX(id) FROM {apachesolr_rdf_indexes}')) + 1;
    $values['name'] = "Index #$id";
  }
  extract($values, EXTR_PREFIX_ALL, 'val');

  if (isset($val_options)) {
    $schema_argument_form = _apachesolr_rdf_get_schema_function(
        'index_options_form', $val_schema);
    $index_options_form_submit = "{$index_options_form}_submit";
    if (function_exists($index_options_form_submit)) {
      $val_options = $index_options_form_submit($form['options'], $val_options);
    }
  }
  else {
    $val_options = array();
  }

  if (isset($val_description) && trim($val_description)) {
    $desc = "'" . db_escape_string($val_description) . "'";
  }
  else {
    $desc = 'NULL';
  }

  $resources = array('context' => $val_context);

  $path_prefix = 'admin/settings/apachesolr_rdf/index';
  if ($values['action'] == 'add') {
    // Add the index
    if (! db_query('INSERT INTO {apachesolr_rdf_indexes} (id, name, ' .
        'description, server, resources, cron_limit, options, enabled) ' .
        "VALUES (NULL, '%s', $desc, %d, '%s', %d, '%s', %d)", $val_name,
        $val_server, serialize($resources), $val_cron_limit,
        serialize($val_options), $val_enabled)) {
      drupal_set_message(t('An error has occurred while adding the index. ' .
          'For details, see the logs.'), 'error');
      $form_state['rebuild'] = TRUE;
      return;
    }

    $id = db_last_insert_id('apachesolr_rdf_indexes', 'id');

    // Add data for the index to the resources table
    $values['id'] = $id;
    $values['resources'] = $resources;
    $values['options'] = $val_options;
    apachesolr_rdf_update_index_data($values, NULL, TRUE);

    drupal_set_message(t('The index was successfully added.'));
    $form_state['redirect'] = "$path_prefix/$id";
    return;
  }

  // We're editing the index
  if (! db_query('UPDATE {apachesolr_rdf_indexes} SET ' .
      "name = '%s', description = $desc, resources = '%s', cron_limit = %d, " .
      "options = '%s', enabled = %d WHERE id = %d", $val_name,
      serialize($resources), $val_cron_limit, serialize($val_options),
      $val_enabled, $values['id'])) {
    drupal_set_message(t('An error has occurred while saving the changes. ' .
        'For details, see the logs.'), 'error');
    $form_state['rebuild'] = TRUE;
    return;
  }

  $form_state['redirect'] = "$path_prefix/{$values['id']}";
  drupal_set_message(t('The changes were successfully saved.'));
}

//
// Searches
//

/**
 * Displays a two-step form for adding a new Apache Solr RDF search, or a form
 * for editing one, if $info is set.
 */
function apachesolr_rdf_settings_search_edit(&$form_state, $info = FALSE) {
  if (!$info && empty($form_state['storage']['server'])) {
    // First step of adding a search
    $options = array();
    foreach (_apachesolr_rdf_servers() as $id => $info) {
      $options[$id] = $info['name'];
    }
    asort($options);

    if (empty($options)) {
      drupal_set_message(t('There is no Apache Solr RDF server defined, yet. ' .
          'You have to <a href="@url">create one</a> first!', array('@url'
          => url('admin/settings/apachesolr_rdf/server/add'))), 'error');
      return;
    }

    $form['server'] = array(
      '#type' => 'select',
      '#title' => t('Server'),
      '#description' => t("The server this search's data will be stored on. " .
          'This setting cannot be changed afterwards!'),
      '#options' => $options,
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
    );

    return $form;
  }

  $server = apachesolr_rdf_server_load(
      $info ? $info['server'] : $form_state['storage']['server']);
  $schema = apachesolr_rdf_schema_load($server['schema']);

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('Determines the status of this search.') .
        (!$server['enabled'] ?
            ' ' . t("Since the server of this search isn't enabled, you " .
            'cannot enable this search now.') : ''),
    '#default_value' => $info ? $info['enabled'] : $server['enabled'],
    '#disabled' => !$server['enabled'],
  );
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('ID'),
    '#description' => t('A unique ID for this search, used internally and ' .
        'for creating the path to the search. Must consist only of ' .
        'alphanumeric characters and underscores ("_").'),
    '#default_value' => $info ? $info['id'] : '',
    '#maxlength' => 30,
    '#required' => TRUE,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A human-readable name for this search. Will default ' .
        'to the ID.'),
    '#default_value' => $info ? $info['name'] : '',
    '#maxlength' => 50,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t("A description of this search's purpose which will " .
        'be displayed on the search page.'),
    '#default_value' => $info ? $info['description'] : '',
  );
  $form['permission'] = array(
    '#type' => 'textfield',
    '#title' => t('Permission'),
    '#description' => t('The permission necessary to use this search.'),
    '#default_value' => $info ? $info['permission'] : 'access RDF data',
    '#maxlength' => 100,
    '#required' => TRUE,
    '#autocomplete_path' => 'apachesolr_rdf/autocomplete/permission',
  );

  $search_options_form = _apachesolr_rdf_get_schema_function(
      'search_options_form', $server['schema']);
  if ($search_options_form) {
    $search_options = $search_options_form($form_state, $info);
    if ($search_options) {
      $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Additional options'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
      );
      $form['options'] += $search_options;
    }
  }

  $form['action'] = array(
    '#type' => 'value',
    '#value' => $info ? 'edit' : 'add',
  );
  $form['server'] = array(
    '#type' => 'value',
    '#value' => $server['id'],
  );
  $form['schema'] = array(
    '#type' => 'value',
    '#value' => $server['schema'],
  );
  if ($info) {
    $form['old_id'] = array(
      '#type' => 'value',
      '#value' => $info['id'],
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $info ? t('Save changes') : t('Add search'),
  );

  return $form;
}

/**
 * Validation function for apachesolr_rdf_settings_search_edit().
 */
function apachesolr_rdf_settings_search_edit_validate($form, &$form_state) {
  $values = $form_state['values'];

  if (!isset($values['action'])) {
    // We are at step 1 of adding a search, nothing to validate.
    return;
  }

  if (isset($values['old_id']) && $values['id'] == $values['old_id']) {
    // Don't need to check the id
  }
  else if ($values['id'] == 'add') {
    form_set_error('id', t('You cannot use "add" as search id.'));
  }
  else if (db_result(db_query('SELECT id FROM {apachesolr_rdf_searches} ' .
      "WHERE id = '%s'", $values['id']))) {
    form_set_error('id', t("The ID \"{$values['id']}\" is " .
        'already in use! Please specify a new one!'));
  }
  else if (urlencode($values['id']) != $values['id']) {
    form_set_error('id', t('The ID may only contain alphanumeric characters ' .
        'and underscores (_)!'));
  }

  $perm_exists = FALSE;
  foreach (module_invoke_all('perm') as $perm) {
    if ($perm == $values['permission']) {
      $perm_exists = TRUE;
      break;
    }
  }
  if (!$perm_exists) {
    form_set_error('permission', t('The permission "@perm" does not exist! ' .
        'Please specify an existing permission!',
        array('@perm' => $values['permission'])));
  }

  if (isset($form['options'])) {
    $search_options_form = _apachesolr_rdf_get_schema_function(
        'search_options_form', $values['schema']);
    $search_options_form_validate = "{$search_options_form}_validate";
    if (function_exists($search_options_form_validate)) {
      $search_options_form_validate($form['options'],
          $values['options'], 'options][');
    }
  }
}

/**
 * Submit function for apachesolr_rdf_settings_search_edit().
 */
function apachesolr_rdf_settings_search_edit_submit($form, &$form_state) {
  $values = $form_state['values'];
  unset($form_state['storage']);

  if (!isset($values['action'])) {
    // We are submitting step 1 of adding a search
    $form_state['storage']['server'] = $values['server'];
    $form_state['rebuild'] = TRUE;
    return;
  }

  if (empty($values['name'])) {
    $values['name'] = $values['id'];
  }
  extract($values, EXTR_PREFIX_ALL, 'val');

  if (isset($val_options)) {
    $search_options_form = _apachesolr_rdf_get_schema_function(
        'search_options_form', $val_schema);
    $search_options_form_submit = "{$search_options_form}_submit";
    if (function_exists($search_options_form_submit)) {
      $val_options = $search_options_form_submit($form['options'], $val_options);
    }
  }
  else {
    $val_options = array();
  }

  if (isset($val_description) && trim($val_description)) {
    $desc = "'" . db_escape_string($val_description) . "'";
  }
  else {
    $desc = 'NULL';
  }

  $path_prefix = 'admin/settings/apachesolr_rdf/search';
  if ($values['action'] == 'add') {
    // Add the search
    if (! db_query('INSERT INTO {apachesolr_rdf_searches} (id, name, ' .
        'description, server, options, permission, enabled) VALUES ' .
        "('%s', '%s', $desc, '%s', '%s', '%s', %d)", $val_id, $val_name,
        $val_server, serialize($val_options), $val_permission, $val_enabled)) {
      drupal_set_message(t('An error has occurred while adding the search. ' .
          'For details, see the logs.'), 'error');
      $form_state['rebuild'] = TRUE;
      return;
    }

    menu_rebuild();
    drupal_set_message(t('The search was successfully added.'));
    $form_state['redirect'] = "$path_prefix/$val_id";
    return;
  }

  // We're editing the search
  if (! db_query('UPDATE {apachesolr_rdf_searches} SET ' .
      "id = '%s', name = '%s', description = $desc, options = '%s', " .
      "permission = '%s', enabled = %d WHERE id = '%s'",
      $val_id, $val_name, serialize($val_options), $val_permission,
      $val_enabled, $val_old_id)) {
    drupal_set_message(t('An error has occurred while saving the changes. ' .
        'For details, see the logs.'), 'error');
    $form_state['rebuild'] = TRUE;
    return;
  }

  if (db_affected_rows() > 0) {
    menu_rebuild();
  }
  $form_state['redirect'] = "$path_prefix/$val_id";
  drupal_set_message(t('The changes were successfully saved.'));
}

/**
 * Returns a form for additional search options.
 */
function apachesolr_rdf_search_options_form($form_state, $info) {
  $form['filter'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional filter'),
    '#description' => t('A filter query that will be appended as a filter to ' .
        'every query with this search.'),
    '#default_value' => $info ? $info['options']['filter'] : '',
  );

  return $form;
}

/**
 * Validation function for apachesolr_rdf_search_options_form().
 */
function apachesolr_rdf_search_options_form_validate(
    $form, $form_state, $prefix) {
  // Not used at the moment, but here to demonstrate the concept.
  // e.g.: form_set_error($prefix . 'filter', t('Something wrong!'));
}

/**
 * Submit function for apachesolr_rdf_search_options_form().
 */
function apachesolr_rdf_search_options_form_submit($form, $values) {
  // Since no processing is done, this would be unnecessary, but it's here for
  // demonstration.
  return $values;
}

/**
 * Displays a sub-form for specifying schema arguments for a server with the
 * "dynamic fields" schema.
 */
function apachesolr_rdf_schema_arguments_form_dynamic(
    $form_state, $info, $parent) {
  $form['#description'] = t('Changes here will only take effect when data is ' .
      'indexed. They will not affect existing index data.');

  $form['text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include "text" field'),
    '#description' => t('Include a field (named "text") in the index that ' .
        'contains all text data, for easy fulltext searches. If the field ' .
        'would be unused, disable it here to save space and indexing time.'),
    '#default_value' => $info ? $info['schema_args']['text'] : TRUE,
  );
  $form['property_object'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include "property_object" field'),
    '#description' => t('Include a field (named "property_object") in the ' .
        'index that allows for searching the (exact) values of arbitrary ' .
        'predicates. If the field would be unused, disable it here to save ' .
        'space and indexing time.'),
    '#default_value' => $info ? $info['schema_args']['property_object'] : TRUE,
  );

  if (!$info) {
    $form['fields'] = array(
      '#type' => 'item',
      '#title' => t('Dynamic fields'),
      '#description' => t('<p>Define the predicates that should be mapped to ' .
          'dynamic fields at this server.</p>' .
          '<p>These can only be defined after the server is created.</p>'),
    );
    return $form;
  }

  $form['fields'] = array(
    '#type' => 'item',
    '#title' => t('Dynamic fields'),
    '#description' => t('<p>Define the predicates that should be mapped to ' .
        'dynamic fields at this server.</p>' .
        '<p><strong>Changes will only take effect after data is re-indexed.' .
        '</strong></p>'),
  );
  $header = array(t('ID'), t('Name'), t('URI'), t('Type'), t('Facets'),
      t('Multi-valued'));
  $rows = array();
  $url_base = "admin/settings/apachesolr_rdf/server/$info[id]/dynamic_field/";
  foreach (_apachesolr_rdf_get_dynamic_fields($info) as $id => $field) {
    $url = $url_base . $id;
    $rows[] = array(l($id, $url), l($field['name'], $url),
        l($field['uri'], $url), l($field['type'], $url),
        l($field['facet'] ? t('yes') : t('no'), $url),
        l($field['multiValued'] ? t('yes') : t('no'), $url));
  }
  if ($rows) {
    $form['fields']['#value'] = theme('table', $header, $rows);
  }
  else {
    $form['fields']['#value'] = '<p>' . t('There are currently no dynamic ' .
        'fields defined for this server.') . '</p>';
    $form['fields']['#value'] .=
        '<p>' . l(t('Add default fields (rdf:type, rdfs:label, rdfs:comment)'),
        $url_base . 'defaults') . '</p>';
  }
  $form['fields']['#value'] .=
      '<p>' . l(t('Add new field'), $url_base . 'add') . '</p>';

  return $form;
}

/**
 * Submit function for apachesolr_rdf_schema_arguments_form_dynamic().
 */
function apachesolr_rdf_schema_arguments_form_dynamic_submit(
    $values) {
  return array(
    'text' => !empty($values['text']),
    'property_object' => !empty($values['property_object']),
  );
}

/**
 * Form function for creating or editing dynamic fields.
 */
function apachesolr_rdf_dynamic_field_edit(&$form_state, $server,
    $id = NULL) {
  if ($id) {
    $info = _apachesolr_rdf_get_dynamic_fields($server);
    if (!isset($info[$id])) {
      unset($info);
      unset($id);
    }
    else {
      $info = $info[$id];
    }
  }
  $form['warning']['#value'] = '<p><strong>' . ($id ? t('Please keep in mind ' .
      'that changes here will only take effect when new data is indexed (or ' .
      'old one re-indexed).') : t('Please keep in mind that old data will be ' .
      'unaffected by the new field, until it is re-indexed.')) .
      '</strong></p>';

  if ($id) {
    $form['delete_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Delete field'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => FALSE,
      'delete_check' => array(
        '#type' => 'checkbox',
        '#title' => t('Really delete this field?'),
        '#description' => t('Check this if you want to delete this field.'),
      ),
      'delete' => array(
        '#type' => 'submit',
        '#value' => t('Delete field'),
      ),
    );
  }

  $form['server_info'] = array(
    '#type' => 'item',
    '#title' => t('Server'),
    '#value' => l($server['name'],
        "admin/settings/apachesolr_rdf/server/{$server['id']}"),
  );
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Field ID'),
    '#description' => t('The unique identifier for the field, which is e.g. ' .
        'used in queries.'),
    '#maxlength' => 50,
    '#default_value' => $id ? $id : '',
    '#required' => TRUE,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A human-readable name for this search.'),
    '#maxlength' => 50,
    '#default_value' => $id ? $info['name'] : '',
  );
  $form['uri'] = array(
    '#type' => 'textfield',
    '#title' => t('URI'),
    '#description' => t('The URI of the predicate that should be mapped to ' .
        'this field.'),
    '#maxlength' => 100,
    '#default_value' => $id ? $info['uri'] : '',
    '#required' => TRUE,
  );

  $types = module_invoke_all('apachesolr_rdf_dynamic_datatypes');
  $options[''] = '-' . t('Select a data type') . '-';
  foreach ($types as $type => $data) {
    $options[$type] = $data['name'];
  }
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t("The field's data type."),
    '#options' => $options,
    '#default_value' => $id ? $info['type'] : '',
    '#required' => TRUE,
  );
  // TODO: Shiny AHAH magic for displaying type description

  $form['facet'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable facets'),
    '#description' => t('Sets whether facets are enabled for this field.'),
    '#default_value' => $id ? $info['facet'] : FALSE,
  );
  $form['multiValued'] = array(
    '#type' => 'checkbox',
    '#title' => t('Has multiple values'),
    '#description' => t('If set, a resource may have multiple values for ' .
        'this field.'),
    '#default_value' => $id ? $info['multiValued'] : TRUE,
  );


  $form['server'] = array(
    '#type' => 'value',
    '#value' => $server['id'],
  );
  $form['old_id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $id ? t('Save changes') : t('Add field'),
  );

  return $form;
}

/**
 * Validation function for apachesolr_rdf_dynamic_field_edit.
 */
function apachesolr_rdf_dynamic_field_edit_validate($form, &$form_state) {
  $v = $form_state['values'];
  if ($v['op'] == t('Delete field')) {
    if (!$v['delete_check']) {
      form_set_error('delete_check', t('Checkbox has to be checked for field' .
          'to be deleted.'));
    }
  }
  else if ($v['id'] != $v['old_id']) {
    $fields = _apachesolr_rdf_get_dynamic_fields(
        apachesolr_rdf_server_load($v['server']));
    if (isset($fields[$v['id']])) {
      form_set_error('id', t('The specified field id is already in use for ' .
          'this server.'));
    }
  }
}

/**
 * Submit function for apachesolr_rdf_dynamic_field_edit.
 */
function apachesolr_rdf_dynamic_field_edit_submit($form, &$form_state) {
  $v = $form_state['values'];
  $server = apachesolr_rdf_server_load($v['server']);

  if ($v['op'] == t('Delete field')) {
    db_query('DELETE FROM {apachesolr_rdf_dynamic_fields} WHERE server = %d ' .
        "AND id = '%s'", $v['server'], $v['old_id']);
  }
  else if ($v['old_id']) {
    db_query("UPDATE {apachesolr_rdf_dynamic_fields} SET id = '%s', " .
        "name = '%s', uri = '%s', type = '%s', facet = %d, multiValued = %d " .
        "WHERE id = '%s' AND server = %d", $v['id'], $v['name'], $v['uri'],
        $v['type'], $v['facet'], $v['multiValued'], $v['old_id'], $v['server']);
  }
  else {
    db_query('INSERT INTO {apachesolr_rdf_dynamic_fields} (server, id, name, ' .
        "uri, type, facet, multiValued) VALUES (%d, '%s', '%s', '%s', '%s', " .
        '%d, %d)', $v['server'], $v['id'], $v['name'], $v['uri'], $v['type'],
        $v['facet'], $v['multiValued']);
  }

  _apachesolr_rdf_get_dynamic_fields($server, TRUE);

  $form_state['redirect'] = url("admin/settings/apachesolr_rdf/server/" .
      "{$v['server']}/edit", array('fragment' =>
          'edit-schema-args-property-object', 'absolute' => TRUE));
}

/**
 * Page handler for adding default fields to a server.
 */
function apachesolr_rdf_dynamic_field_defaults($server) {
  $id = $server['id'];

  db_query('INSERT INTO {apachesolr_rdf_dynamic_fields} (server, id, name, ' .
        "uri, type, facet, multiValued) VALUES (%d, 'type', '%s', '%s', " .
        "'resource', 0, 1)", $id, t('Type'), APACHESOLR_RDF_TYPE);
  db_query('INSERT INTO {apachesolr_rdf_dynamic_fields} (server, id, name, ' .
        "uri, type, facet, multiValued) VALUES (%d, 'label', '%s', '%s', " .
        "'text', 0, 1)", $id, t('Label'), APACHESOLR_RDF_LABEL);
  db_query('INSERT INTO {apachesolr_rdf_dynamic_fields} (server, id, name, ' .
        "uri, type, facet, multiValued) VALUES (%d, 'comment', '%s', '%s', " .
        "'text', 0, 1)", $id, t('Comment'), APACHESOLR_RDF_COMMENT);

  drupal_goto("admin/settings/apachesolr_rdf/server/$id/edit", NULL,
      'edit-schema-args-property-object');
}
