<?php
// $Id: weight.views.inc,v 1.2.2.1 2009/01/26 00:28:54 nancyw Exp $
/**
 * @file
 * Views2 support for Weight module.
 */
/**
 * Implementation of hook_views_data()
 */
function weight_views_data() {
  $data['node_weight'] = array(
    'table' => array(
      'group' => t('Weight'),
      'join' => array(
        'node' => array(
          'table' => 'node',
          'left_field' => 'nid',
          'field' => 'nid',
          ),
        ),
      ),
    'weight' => array(
      'real field' => 'sticky',
      'title' => t('Weight'), // The item it appears as on the UI,
      'help' => t('The node weight.'), // The help that appears on the UI,
      'field' => array(
        'handler' => 'weight_handler_field_sticky',
        'click sortable' => TRUE,
        ),
      'filter' => array(
         'handler' => 'views_handler_filter_numeric',
         'label' => t('Weight'),
        ),
      'sort' => array(
        'handler' => 'weight_handler_sort',
        ),
    ),
  );

  return $data;
}


/**
 * Implementation of hook_views_plugins();
 */
function weight_views_plugins() {
  return array(
    'style' => array(
      'weight' => array(
        'title' => t('Weight Changer'),
        'help' => t('Displays rows in a table which allows weight change.  Be sure to add the Weight field and Sort by Weight.'),
        'handler' => 'views_plugin_style_table',
        'parent' => 'table',
        'path' => drupal_get_path('module', 'weight'),
        'theme' => 'weight_view_weight',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
       ),
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function weight_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'weight') /*.'/handlers'*/,
     ),
    'handlers' => array(
      'weight_handler_field_sticky' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'weight_handler_sort' => array(
        'parent' => 'views_handler_sort',
       ),
     ),
   );
}

/**
 * Display a view as a weight changing table.
 */
function theme_weight_view_weight($view, $rows, $type) {
  $result = $view->result;
  $rows = array();

  $options  = $view->style_plugin->options;
  $handler  = $view->style_plugin;

  $fields   = &$view->field;
  $columns  = $handler->sanitize_columns($options['columns'], $fields);

  $active   = !empty($handler->active) ? $handler->active : '';
  $order    = !empty($handler->order) ? $handler->order : 'asc';

  $query    = tablesort_get_querystring();
  if ($query) {
    $query = '&'. $query;
  }
  foreach ($columns as $field => $column) {
    // render the header labels
    if ($field == $column && empty($fields[$field]->options['exclude'])) {
      $label = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
      if (empty($options['info'][$field]['sortable'])) {
        $header[$field] = $label;
      }
      else {
        // @todo -- make this a setting
        $initial = 'asc';

        if ($active == $field && $order == 'asc') {
          $initial = 'desc';
        }

        $image = theme('tablesort_indicator', $initial);
        $title = t('sort by @s', array('@s' => $label));
        $link_options = array(
          'html' => TRUE,
          'attributes' => array('title' => $title),
          'query' => 'order='. urlencode($field) .'&sort='. $initial . $query,
        );
        $header[$field] = l($label . $image, $_GET['q'], $link_options);
      }
    }
 
    // Create a second variable so we can easily find what fields we have and what the
    // CSS classes should be.
    $weight_fields[$field] = views_css_safe($field);
    if ($active == $field) {
      $weight_fields[$field] .= ' active';
    }

    // Render each field into its appropriate column.
    foreach ($result as $num => $row) {
      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
        $field_output = $fields[$field]->theme($row);

        // Don't bother with separators and stuff if the field does not show up.
        if (!isset($field_output) && isset($rows[$num][$column])) {
          continue;
        }
        // Place the field into the column, along with an optional separator.
        if (isset($rows[$num][$column])) {
          if (!empty($options['info'][$column]['separator'])) {
            $rows[$num][$column] .= filter_xss_admin($options['info'][$column]['separator']);
          }
        }
        else {
          $rows[$num][$column] = '';
        }

        $rows[$num][$column] .= $field_output;
      }
    }
  }

  $class = 'views-table-weight';
  if (!empty($options['sticky'])) {
    drupal_add_js('misc/tableheader.js');
    $class .= " sticky-enabled";
  }
  
  // Pass along the nid.

  foreach ($view->result as $count => $item) {
    $rows[$count]['nid_hidden'] = $item->nid;
  } 
  $id = $view->name .'_drag';
  return drupal_get_form('weight_view_weight_form', $header, $rows, $weight_fields, $class, $id);
}

/**
 * Display a view as a weight changing table.
 */
function weight_view_weight_form(&$form_state, $header, $rows, $fields, $class, $id) {
  // Make this form draggable
  drupal_add_tabledrag($id, 'order', 'sibling', 'weight_dragger');

  $form = array('#tree' => TRUE);
  $form['#variables'] = array(
    'header' => $header,
    'class' => $class,
    'fields' => $fields,
    'id' => $id,
    );
  foreach ($rows as $count => $row) {
    if (is_numeric($count)) {
      foreach ($row as $field => $content) {
        $nid = $row['nid_hidden'];
        if (substr($field, 0, 6) == 'weight') {
          $form['rows'][$count][$field] = array(
            '#default_value' => $content,
            '#type' => 'weight',
            '#delta' => variable_get('weight_range', 20),
            );
        }
        elseif ($field != 'nid_hidden') {
          $form['rows'][$count][$field] = array(
            '#value' => $content,
            );
        }
        else {
          $form['rows'][$count][$field] = array(
            '#type' => 'hidden',
            '#value' => $content,
            );
        }
      }
    }  
  }
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

/**
 * Save the changed weights.
 */
function weight_view_weight_form_submit($form, &$form_state) {
  foreach ($form_state['values']['rows'] as $count => $value) {
    $weight = $value['weight'];
    $nid = $value['nid_hidden'];
    $node = node_load($nid);
    if ($node->sticky) {
      $node->sticky = (-1 * $weight) + 100;
    }
    // Unweighted non-sticky nodes will have a value of -100.
    else {
      $node->sticky = (-1 * $weight) - 100;
    }
    db_query("UPDATE {node} SET sticky = %d WHERE nid = %d", $node->sticky, $nid);
  }
  drupal_set_message('Your weight changes have been saved.');
}
