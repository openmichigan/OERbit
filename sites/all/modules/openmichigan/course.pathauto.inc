<?php
// $Id$

/**
 * Update path aliases for the course page.
 */
function course_pathauto_alias(&$node, $op) {
  switch ($op) {
    case 'insert':
    case 'update':
    case 'bulkupdate':
      if (module_exists('pathauto')) {
        module_load_include('inc', 'pathauto');
        $alias = 'node/' . $node->nid;
        $placeholders = pathauto_get_placeholders('node', $node);
        pathauto_create_alias('course', $op, $placeholders, $alias . '/overview', $node->nid, 'overview');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/sessions', $node->nid, 'sessions');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/materials', $node->nid, 'materials');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/highlights', $node->nid, 'highlights');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/rss', $node->nid, 'rss');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/rdf', $node->nid, 'rdf');
      }
      break;
    case 'delete':
      if (module_exists('pathauto')) {
        module_load_include('inc', 'pathauto');
        path_set_alias('node/' . $node->nid . '/overview');
        path_set_alias('node/' . $node->nid . '/sessions');
        path_set_alias('node/' . $node->nid . '/materials');
        path_set_alias('node/' . $node->nid . '/highlights');
        path_set_alias('node/' . $node->nid . '/rss');
        path_set_alias('node/' . $node->nid . '/rdf');
      }
      break;
  }
}
