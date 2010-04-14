<?php
// $Id: revisioning.views.inc,v 1.3 2010/03/22 01:20:34 rdeboer Exp $

/**
 * @file
 *  Declare new node and node_revisions fields and filters.
 */

/**
 * Implementation of hook_views_data().
 *
 * Ommitted, we're altering existing groups, not creating a new one.
 *
function revisioning_views_data() {
}
 */

/**
 * Implementation of hook_views_data_alter().
 *
 * We define a pseudo-field 'state' (values: pending, current, archived) for
 * both node and node_revisions tables.
 */
function revisioning_views_data_alter(&$data) {

  $data['node']['state'] = array(
    'title' => t('State'),
    'help' => t('One of: pending, current, archived'),
    'field' => array(
      'handler' => 'revisioning_handler_field_node_state',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'revisioning_handler_filter_node_state',
    )
    // Cannot support sort as 'state' cannot be expressed as ORDER BY clause
  );
  $data['node']['number_of_revisions'] = array(
    'title' => t('Revisions'),
    'help' => t('Number of revisions.'),
    'field' => array(
      'handler' => 'revisioning_handler_field_node_number_of_revisions',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'revisioning_handler_filter_node_number_of_revisions',
    ),
    // Cannot support sort as 'number of revisions' cannot be expressed as ORDER BY clause
  );
  $data['node']['revision_moderation'] = array(
    'title' => t('Revision moderation'),
    'help' => t('Whether the node is subject to revision moderation.'),
    'field' => array(
      'handler' => 'revisioning_handler_field_node_revision_moderation',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'revisioning_handler_filter_node_revision_moderation',
    ),
    // Cannot support sort as this flag cannot be expressed as ORDER BY clause
  );
  $data['node_revisions']['title']['help'] = t('The title of the revision.');
  $data['node_revisions']['state'] = array(
    'title' => t('State'),
    'help' => t('One of: pending, current, archived'),
    'field' => array(
      'handler' => 'revisioning_handler_field_revision_state',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'revisioning_handler_filter_revision_state',
    )
    // Cannot support sort as 'state' cannot be expressed as ORDER BY clause
  );
}

/**
 * Implementation of hook_views_handlers().
 *
 * Register all of the handlers (fields and filters) used in Revisioning views.
 */
function revisioning_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'revisioning') .'/views',
    ),
    'handlers' => array(
      'revisioning_handler_field_node_state' => array('parent' => 'views_handler_field'),
      'revisioning_handler_field_revision_state' => array('parent' => 'views_handler_field'),
      'revisioning_handler_field_node_number_of_revisions' => array('parent' => 'views_handler_field'),
      'revisioning_handler_field_node_revision_moderation' => array('parent' => 'views_handler_field'),
      'revisioning_handler_filter_node_state' => array('parent' => 'views_handler_filter_in_operator'),
      'revisioning_handler_filter_node_number_of_revisions' => array('parent' => 'views_handler_filter_numeric'),
      'revisioning_handler_filter_node_revision_moderation' => array('parent' => 'views_handler_filter_in_operator'),
      'revisioning_handler_filter_revision_state' => array('parent' => 'views_handler_filter_in_operator'),
    )
  );
}