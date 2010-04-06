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
        // Update aliases for the latest version of this course
        $query = db_query("SELECT DISTINCT(nid) FROM {content_type_course} WHERE field_course_code_value='%s' ORDER BY field_course_year_value DESC, field_course_term_value ASC", $node->field_course_code[0]['value']);
        $latest = db_fetch_object($query);
        $previous = db_fetch_object($query);
        if ($latest->nid == $node->nid) {
          // Revert the aliases for the previous version
          if (!empty($previous) && $previous->nid != $latest->nid) {
            $previous = node_load($previous->nid);
            $prev_placeholders = pathauto_get_placeholders('node', $previous);
            $src = 'node/' . $previous->nid;
            path_set_alias($src);
            path_set_alias($src . '/overview');
            path_set_alias($src . '/sessions');
            path_set_alias($src . '/materials');
            path_set_alias($src . '/highlights');
            path_set_alias($src . '/rss');
            path_set_alias($src . '/rdf');
            pathauto_create_alias('node', $op, $prev_placeholders, $src, $previous->nid, 'course');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/overview', $previous->nid, 'overview');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/sessions', $previous->nid, 'sessions');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/materials', $previous->nid, 'materials');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/highlights', $previous->nid, 'highlights');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/rss', $previous->nid, 'rss');
            pathauto_create_alias('course', $op, $prev_placeholders, $src . '/rdf', $previous->nid, 'rdf');
          }
          // Add the aliases for the latest version
          path_set_alias($alias);
          path_set_alias($alias . '/overview');
          path_set_alias($alias . '/sessions');
          path_set_alias($alias . '/materials');
          path_set_alias($alias . '/highlights');
          path_set_alias($alias . '/rss');
          path_set_alias($alias . '/rdf');
          pathauto_create_alias('course', $op, $placeholders, $alias, $node->nid, 'latest_course');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/overview', $node->nid, 'latest_overview');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/sessions', $node->nid, 'latest_sessions');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/materials', $node->nid, 'latest_materials');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/highlights', $node->nid, 'latest_highlights');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/rss', $node->nid, 'latest_rss');
          pathauto_create_alias('course', $op, $placeholders, $alias . '/rdf', $node->nid, 'latest_rdf');
        }
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
        // Revert paths to previous version
        $latest = db_fetch_object(db_query("SELECT DISTINCT(nid) AS nid FROM {content_type_course} WHERE field_course_code_value='%s' AND nid <> %d ORDER BY field_course_year_value DESC, field_course_term_value ASC", $node->field_course_code[0]['value'], $node->nid));
        if (!empty($latest->nid)) {
          $latest = node_load($latest->nid);
          $alias = 'node/' . $latest->nid;
          path_set_alias($alias);
          path_set_alias($alias . '/overview');
          path_set_alias($alias . '/sessions');
          path_set_alias($alias . '/materials');
          path_set_alias($alias . '/highlights');
          path_set_alias($alias . '/rss');
          path_set_alias($alias . '/rdf');
          $placeholders = pathauto_get_placeholders('node', $latest);
          pathauto_create_alias('course', 'update', $placeholders, $alias, $latest->nid, 'latest_course');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/overview', $latest->nid, 'latest_overview');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/sessions', $latest->nid, 'latest_sessions');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/materials', $latest->nid, 'latest_materials');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/highlights', $latest->nid, 'latest_highlights');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/rss', $latest->nid, 'latest_rss');
          pathauto_create_alias('course', 'update', $placeholders, $alias . '/rdf', $latest->nid, 'latest_rdf');
        }
      }
      break;
  }
}
