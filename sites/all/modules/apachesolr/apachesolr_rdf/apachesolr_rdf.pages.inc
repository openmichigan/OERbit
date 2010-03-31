<?php
// $Id: apachesolr_rdf.pages.inc,v 1.1.2.21 2009/11/01 23:31:38 drunkenmonkey Exp $

/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for
 * existing permissions.
 */
function apachesolr_rdf_permission_autocomplete($string = '') {
  $matches = array();
  foreach (module_invoke_all('perm') as $perm) {
    if (!$string || strpos($perm, $string) !== FALSE) {
      $matches[$perm] = check_plain($perm);
      if (count($matches) >= 10) {
        break;
      }
    }
  }

  drupal_json($matches);
}

/**
 * Displays a search and/or search results appropriate for the selected
 * schema.
 */
function apachesolr_rdf_show_search($info) {
  $output = '';
  $id = $info['id'];
  drupal_set_title($info['name']);

  if (isset($_GET['filters'])) {
    $_GET['filters'] = _apachesolr_rdf_urldecode($_GET['filters']);
  }

  $keys = apachesolr_rdf_search_keys($id);
  $filters = isset($_GET['filters']) ? $_GET['filters'] : array();
  $sort = isset($_GET['sort']) ? $_GET['sort'] : '';
  $page = isset($_GET['page']) ? $_GET['page'] : 0;
  $output .= drupal_get_form('search_form', '', $keys, "apachesolr_rdf_$id");

  if ($keys || $filters) {
    $execute_search = _apachesolr_rdf_get_schema_function(
        'execute_search', $info['schema']);
    if (!$execute_search) {
      watchdog('Apache Solr RDF', 'No execute_search function found for ' .
          'schema "@schema".', array('@schema' => $info['schema']),
          WATCHDOG_ERROR);
      drupal_set_message(t('@search cannot be used due to an internal error.',
          array('@search' => $info['name'])), 'error');
      drupal_goto('search');
    }

    watchdog('search', "$keys (apachesolr_rdf_$id)", NULL);
    $output .= $execute_search($info, $keys, $filters, $sort,
        $page);
  }

  return $output;
}

/**
 * Submit function for an Apachesolr RDF search.
 */
function apachesolr_rdf_search_submit($form, &$form_state) {
  $v = $form_state['values'];

  $keys= trim($v['keys']);
  if (!empty($v['context'])) {
    $query['filters']['context'][] = $v['context'];
  }
  if (!empty($v['type'])) {
    $query['filters']['type'][] = $v['type'];
  }
  if (!empty($v['predicate_1'])) {
    for ($i = 1; isset($v["predicate_$i"]); ++$i) {
      $p = trim($v["predicate_$i"]);
      $f = trim($v["value_$i"]);
      if ($p && $f) {
        $query['filters'][$p][] = $f;
      }
      else if ($p) {
        $query['filters']['property_object'][] = $p;
      }
      else if ($f) {
        $query['filters']['property_object'][] = $f;
      }
    }
  }

  $path = 'search/apachesolr_rdf_' . $v['apachesolr_rdf_id'];

  if (empty($query)) {
    if (empty($keys)) {
      form_set_error('keys', t('Please enter some keywords.'));
    }
    else {
      $form_state['redirect'] = "$path/$keys";
    }
  }
  else {
    $form_state['redirect'] = array("$path/$keys", $query);
  }
}

//
// Schema functions
//
// - dynamic fields
//

/**
 * Alters the search form by adding advanced RDF search options and telling the
 * form to use the right submit function.
 */
function apachesolr_rdf_search_form_alter_dynamic(
    &$form, &$form_state, $id, $schema_args) {
  $form['#submit'] = array('apachesolr_rdf_search_submit');

  $advanced = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Search'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($_GET['filters'])
        && !isset($form_state['post']['more_properties']),
  );
  $contexts[''] = '-' . t('All') . '-';
  $contexts += drupal_map_assoc(rdf_get_contexts());
  $advanced['context'] = array(
    '#type' => 'select',
    '#options' => $contexts,
    '#title' => t('Context'),
    '#default_value' => isset($_GET['filters']['context'][0])
        ? $_GET['filters']['context'][0] : '',
  );

  $properties_number = !empty($form_state['post']['properties_number'])
      ? $form_state['post']['properties_number'] : 1;
  if (isset($form_state['post']['more_properties'])) {
    ++$properties_number;
  }
  $properties = array(
    '#type' => 'fieldset',
    '#title' => t('Properties'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
  );
  $properties['properties_number'] = array(
    '#type' => 'hidden',
    '#value' => $properties_number,
  );
  $properties['predicate_0'] = array(
    '#type' => 'textfield',
    '#value' => t('Predicate'),
    '#size' => 30,
    '#disabled' => TRUE,
  );
  $properties['value_0'] = array(
    '#type' => 'textfield',
    '#value' => t('Value'),
    '#size' => 30,
    '#disabled' => TRUE,
    '#suffix' => '<br />',
  );
  for ($i = 1; $i <= $properties_number; ++$i) {
    $properties["predicate_$i"] = array(
      '#type' => 'textfield',
      '#size' => 30,
    );
    $properties["value_$i"] = array(
      '#type' => 'textfield',
      '#size' => 30,
      '#suffix' => '<br />',
    );
  }
  $properties['more_properties'] = array(
    '#type' => 'button',
    '#name' => 'more_properties',
    '#value' => t('Add row'),
  );
  if(isset($_GET['filters'])) {
    $i = 1;
    foreach ($_GET['filters'] as $p => $values) {
      if ($p == 'context') {
        continue;
      }
      foreach ($values as $v) {
        $properties["predicate_$i"]['#default_value'] = $p;
        $properties["value_$i"]['#default_value'] = $v;
        ++$i;
      }
    }
  }

  $advanced['properties'] = $properties;

  $advanced['advanced_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['advanced'] = $advanced;
}

/**
 * Executes a search using the "dynamic fields" schema.
 */
function apachesolr_rdf_execute_search_dynamic($info, $keys, $filters, $sort,
    $page) {
  // Get server information
  $server = apachesolr_rdf_server_load($info['server']);

  // Get solr object
  $solr = apachesolr_get_solr($server['host'], $server['port'],
      $server['path']);

  // Build filter string
  $filterarr = array();
  $fields = _apachesolr_rdf_get_dynamic_fields($server);
  $std_fields = drupal_map_assoc(array('id', 'uri', 'index', 'context',
      'property_object', 'text'));

  foreach ($filters as $field => $values) {
    // "Correct" single-value $values
    if (!is_array($values)) {
      $values = array($values);
    }

    if (!empty($fields[$field])) {
      apachesolr_rdf_dynamic_add_search_field($filterarr, $field,
          $fields[$field], $values, $solr);
    }
    else if (!empty($std_fields[$field])) {
      // Pass-through existing standard fields like "uri"
      $value = implode('" "', array_map(array($solr, 'escapePhrase'), $values));
      $filterarr[] = "$field:(\"$value\")";
    }
    else {
      // Fall back to property_object field & assume $field to be predicate URI
      foreach ($values as $value) {
        $field = $solr->escapePhrase($field);
        $value = $solr->escapePhrase($value);
        if (empty($info['schema_args']['property_object'])) {
          $filterarr[] = "\"$field\" \"$value\"";
        }
        else {
          $filterarr[] = "property_object:\"$field $value\"";
        }
      }
    }
  }

  $filterstring = implode(' ', $filterarr);
  if (!empty($info['options']['filter'])) {
    $filterstring .= ' (' . $info['options']['filter'] . ')';
  }

  $keys = $solr->escape(trim($keys));
  $keys = trim($keys ? "$keys $filterstring" : $filterstring);
  if (!$keys) {
    $keys = '*:*';
  }

  // Set parameters
  $fl = 'uri,context';
  $wanted_preds = drupal_map_assoc(array(APACHESOLR_RDF_LABEL,
      APACHESOLR_RDF_COMMENT, APACHESOLR_RDF_TYPE));
  foreach ($fields as $id => $field) {
    if (isset($wanted_preds[$field['uri']])) {
      $fl .= ",tm_{$id}";
      if ($field['type'] == 'resource') {
        $fl .= ",sm_{$id}";
      }
    }
  }
  $params = array(
    'fl' => $fl,
    'rows' => variable_get('apachesolr_rows', 10),
    'facet' => 'true',
    'facet.mincount' => 1,
    'facet.sort' => 'true'
  );
  $params['start'] = $page * $params['rows'];

  try {
    // Search and render results
    $response = $solr->search($keys, $params['start'],
        $params['rows'], $params);
    return apachesolr_rdf_render_response_dynamic
        ($info, $response, $keys, $params);
  }
  catch (Exception $e) {
    watchdog('Apache Solr RDF', check_plain($e->getMessage()), NULL,
        WATCHDOG_ERROR);
    drupal_set_message(t('@name cannot be used due to an internal error.',
        array('@name' => $info['name'])), 'error');
    return;
  }
}

/**
 * Adds terms for searching a field for given values to the query array.
 */
function apachesolr_rdf_dynamic_add_search_field(&$query, $id, $info, $values,
    $solr) {
  $types = array(
    'text' => 't',
    'string' => 's',
    'integer' => 'si',
    'float' => 'sf',
    'boolean' => 'b',
    'date' => 'si',
  );
  $mv = empty($info['multiValued']) ? 's' : 'm';
  $t = $info['type'];
  if (isset($types[$t])) {
    $field = $types[$t] . "{$mv}_$id";
  }
  switch ($t) {
    case 'text':
    case 'string':
      $query[] = "$field:(\"" . implode('" "',
          array_map(array($solr, 'escapePhrase'), $values)) . '")';
      break;

    case 'boolean':
      foreach ($values as $v) {
        $v = trim($v);
        $v = $v && strtolower($v) != 'false' ? 'true' : 'false';
        $query[] = "$field:$v";
      }
      break;

    case 'date':
    case 'integer':
    case 'float':
      foreach ($values as $v) {
        if (is_array($v)) {
          // Complicated code to do a range query if either $v['min'] or
          // $v['max'] (or both) is/are set
          if (!isset($v['min']) && !isset($v['max'])) {
            watchdog('Apache Solr RDF', 'Unrecognized range query format: @arr',
                array('@arr' => print_r($v, TRUE)), WATCHDOG_WARNING);
            continue;
          }
          if ($t == 'date') {
            array_map('strtotime', $v);
          }
          if (isset($v['min'])) {
            $min = trim($v['min']);
            $min = $t == 'float' ? (float) $min : (int) $min;
          }
          else {
            $min = '*';
          }
          if (isset($v['max'])) {
            $max = trim($v['min']);
            $max = $t == 'float' ? (float) $max : (int) $max;
          }
          else {
            $max = '*';
          }
          $query[] = "$field:[$min TO $max]";
          continue;
        }
        if($t == 'float') {
          $v = (float) trim($v);
        }
        else {
          if ($t == 'date') {
            $v = strtotime($v);
          }
          $v = (int) trim($v);
        }
        $query[] = "$field:$v";
      }
      break;

    case 'resource':
      foreach ($values as $v) {
        $v = '"' . $solr->escapePhrase($v) . '"';
        $query[] = "(s{$mv}_$id:$v OR t{$mv}_$id:$v)";
      }
      break;

    default:
      // It has to be a type defined by a hook
      $f = _apachesolr_rdf_get_dynamic_type_function('add_to_query', $t);
      if ($f) {
        $f($query, $id, $info, $values, $solr);
      }
      else {
        watchdog('Apache Solr RDF', 'Unknown datatype: @type.',
            array('@type' => $t), WATCHDOG_WARNING);
      }
  }
}

/**
 * Renders a search response of the "dynamic fields" schema.
 */
function apachesolr_rdf_render_response_dynamic
    ($info, $response, $keys, $params) {
  // Pager query to get a pager output
  $total = $response->response->numFound;
  if (!$total) {
    return theme('box', t('Your search yielded no results'),
        search_help('search#noresults', drupal_help_arg()));
  }
  pager_query("SELECT %d", $params['rows'], 0, NULL, $total);

  $results = array();
  $fields = _apachesolr_rdf_get_dynamic_fields(
      apachesolr_rdf_server_load($info['server']));
  $type_f = array_shift(_apachesolr_rdf_get_dynamic_fields_by_uri(
      $fields, APACHESOLR_RDF_TYPE));
  $label_f = array_shift(_apachesolr_rdf_get_dynamic_fields_by_uri(
      $fields, APACHESOLR_RDF_LABEL));
  $comment_f = array_shift(_apachesolr_rdf_get_dynamic_fields_by_uri(
      $fields, APACHESOLR_RDF_COMMENT));

  foreach ($response->response->docs as $doc) {
    $results[] = array(
      'link' => $doc->uri,
      'type' => $type_f ? t('Type: ') .
          _apachesolr_rdf_dynamic_field_extract($doc, $type_f['id']) : FALSE,
      'title' => $label_f ?
          _apachesolr_rdf_dynamic_field_extract($doc, $label_f['id']) : FALSE,
      'snippet' => $comment_f ?
          _apachesolr_rdf_dynamic_field_extract($doc, $comment_f['id']) : FALSE,
    );
  }

  return theme('box', t('Search results'), theme('search_results', $results,
      "apachesolr_rdf_{$info['id']}"));
}

/**
 * Extracts a field's value from a response document.
 */
function _apachesolr_rdf_dynamic_field_extract($doc, $field) {
  foreach ($doc as $k => $v) {
    if (strpos($k, "_$field") !== FALSE) {
      if (is_array($v)) {
        return implode(', ', $v);
      }
      return $v;
    }
  }
  return FALSE;
}

//
// - text data
//

/**
 * Alters the search form by adding advanced RDF search options and telling the
 * form to use the right submit function.
 */
function apachesolr_rdf_search_form_alter_text_data(
    &$form, &$form_state, $id, $schema_args) {
  $form['#submit'] = array('apachesolr_rdf_search_submit');

  $advanced = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Search'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($_GET['filters']),
  );
  $contexts[''] = '-' . t('All') . '-';
  $contexts += drupal_map_assoc(rdf_get_contexts());
  $advanced['context'] = array(
    '#type' => 'select',
    '#options' => $contexts,
    '#title' => t('Context'),
    '#default_value' => isset($_GET['filters']['context'][0])
        ? $_GET['filters']['context'][0] : '',
  );
  $advanced['type'] = array(
    '#type' => 'textfield',
    '#maxlength' => 255,
    '#title' => t('Type'),
    '#default_value' => isset($_GET['filters']['type'][0])
        ? $_GET['filters']['type'][0] : '',
  );

  $advanced['advanced_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['advanced'] = $advanced;
}

/**
 * Executes a search using the "text data" schema.
 */
function apachesolr_rdf_execute_search_text_data($info, $keys, $filters, $sort,
    $page) {
  // Get server information
  $server = apachesolr_rdf_server_load($info['server']);

  // Get solr object
  $solr = apachesolr_get_solr($server['host'], $server['port'],
      $server['path']);

  // Build filter string
  $filterarr = array();
  foreach ($filters as $field => $values) {
    $value = '"' . implode('" "',
        array_map(array($solr, 'escapePhrase'), $values)) . '"';
    $field = $solr->escape($field);
    $filterarr[] = "$field:($value)";
  }
  $filterstring = implode(' ', $filterarr);

  $keys = $solr->escape(trim($keys));
  $keys = trim($keys ? "$keys $filterstring" : $filterstring);
  if (!$keys) {
    $keys = '*:*';
  }

  // Set parameters
  $params = array(
    'fl' => 'uri,context,type,property,text',
    'rows' => variable_get('apachesolr_rows', 10),
    'facet' => 'true',
    'facet.mincount' => 1,
    'facet.sort' => 'true'
  );
  $params['start'] = $page * $params['rows'];

  try {
    // Search and render results
    $response = $solr->search($keys, $params['start'],
        $params['rows'], $params);
    return apachesolr_rdf_render_response_text_data
        ($info, $response, $keys, $params);
  }
  catch (Exception $e) {
    watchdog('Apache Solr RDF', check_plain($e->getMessage()), NULL,
        WATCHDOG_ERROR);
    return;
  }
}

/**
 * Renders a search response of the "text data" schema.
 */
function apachesolr_rdf_render_response_text_data
    ($info, $response, $keys, $params) {
  // Pager query to get a pager output
  $total = $response->response->numFound;
  if (!$total) {
    return theme('box', t('Your search yielded no results'),
        search_help('search#noresults', drupal_help_arg()));
  }
  pager_query("SELECT %d", $params['rows'], 0, NULL, $total);

  $results = array();
  foreach ($response->response->docs as $doc) {
    $type = is_array($doc->type) ? implode(', ', $doc->type) : $doc->type;
    $label = $comment = FALSE;
    $prop_count = count($doc->property);
    for ($i = 0; $i < $prop_count; ++$i) {
      if ($doc->property[$i] == APACHESOLR_RDF_LABEL) {
        $label = $doc->text[$i];
      }
      else if ($doc->property[$i] == APACHESOLR_RDF_COMMENT) {
        $comment = $doc->text[$i];
      }
      // When we've found all desired fields, stop looking.
      if ($label && $comment) {
        break;
      }
    }
    $results[] = array(
      'link' => $doc->uri,
      'type' => $type,
      'title' => $label ? $label : $doc->uri,
      'snippet' => $comment,
    );
  }

  return theme('box', t('Search results'), theme('search_results', $results,
      "apachesolr_rdf_{$info['id']}"));
}

/**
 * Decodes '%2F' to '/'. Necessary because of a bug in
 * drupal_query_string_encode().
 *
 * NOTE: This leads to bugs when a URI literally contains "%2F" or the like. But
 * nothing we can do about it, as long as drupal_query_string_encode() remains.
 */
function _apachesolr_rdf_urldecode($array) {
  if (!is_array($array)) {
    return str_replace(array('%2F', '%26', '%23'), array('/', '&', '#'),
        $array);
  }

  $ret = array();

  foreach ($array as $key => $value) {
    $key = _apachesolr_rdf_urldecode($key);
    $value = _apachesolr_rdf_urldecode($value);
    $ret[$key] = $value;
  }

  return $ret;
}
