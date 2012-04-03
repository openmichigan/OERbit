<?php
/**
 * @file
 *   View elements for Revisioning Scheduler, in particular vid, uid and
 *   scheduled publication date. Also defines joins to node and user tables.
 */

function revisioning_scheduler_views_data() {

  $data['revisioning_scheduler']['table']['group'] = t('Revisioning Scheduler');
  $data['revisioning_scheduler']['table']['base'] = array(
    'field' => 'revision_nid',
    'title' => t('Revisioning'),
  );

  $data['revisioning_scheduler']['revision_nid'] = array(
    'title' => t('nid'),
    'field' => array(
      'views_handler_field',
      'click sortable' => FALSE,
    ),
  );

  $data['revisioning_scheduler']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'revision_nid'
    ),
    'node' => array(
      'left_field' => 'vid',
      'field' => 'revision_vid',
    ),
    'user' => array(
      'left_field' => 'uid',
      'field' => 'revision_uid',
    ),
    'help' => t('Scheduled revision publishing'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node'),
    )
  );

  $data['revisioning_scheduler']['revision_vid'] = array(
    'title' => t('Version'),
    'help' => t('node.vid'),
    'field' => array(
      'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'relationship' => array(
      'base' => 'node_revisions',
      'field' => 'vid',
      'handler' => 'views_handler_relationship',
      'label' => t('Revision'),
    )
  );

  $data['revisioning_scheduler']['revision_uid'] = array(
    'title' => t('Revision Author'),
    'help' => t('User ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
       'handler' => 'views_handler_filter_integer',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Revision Author'),
    )
  );

  $data['revisioning_scheduler']['revision_date'] = array(
    'title' => t('Date'),
    'help' => t('Scheduled Publication Date'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    )
  );

  return $data;
}