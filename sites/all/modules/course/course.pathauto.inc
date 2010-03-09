<?php
// $Id$

/**
 * Implementation of hook_pathauto() for course aliases.
 */
function course_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'course';
      $settings['token_type'] = 'node';
      $settings['groupheader'] = t('Course path settings');
      $settings['patterndescr'] = t('Pattern for course page paths');
      $settings['patterndefault'] = t('');
      $settings['patternitems'] = array(
        'overview' => t('Pattern for course overview'),
        'sessions' => t('Pattern for course sessions'),
        'materials' => t('Patern for course materials'),
        'rss' => t('Pattern for course RSS Feed'),
        'rdf' => t('Pattern for course RDF'),
      );
      $patterns = token_get_list('node');
      foreach ($patterns as $type => $pattern_set) {
        if ($type != 'global') {
          foreach ($pattern_set as $pattern => $description) {
            $settings['placeholders']['['. $pattern .']'] = $description;
          }
        }
      }
      return (object) $settings;
    default:
      break;
  }
}

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
        $overview = 'node/' . $node->nid . '/overview';
        $sessions = 'node/' . $node->nid . '/sessions';
        $materials = 'node/' . $node->nid . '/materials';
        $rss = 'node/' . $node->nid . '/rss';
        $rdf = 'node/' . $node->nid . '/rdf';
        $placeholders = pathauto_get_placeholders('node', $node);
        pathauto_create_alias('course', $op, $placeholders, $overview, $node->nid, 'overview');
        pathauto_create_alias('course', $op, $placeholders, $sessions, $node->nid, 'sessions');
        pathauto_create_alias('course', $op, $placeholders, $materials, $node->nid, 'materials');
        pathauto_create_alias('course', $op, $placeholders, $rss, $node->nid, 'rss');
        pathauto_create_alias('course', $op, $placeholders, $rdf, $node->nid, 'rdf');
      }
      break;
    case 'delete':
      if (module_exists('path')) {
        path_set_alias('node/' . $node->nid . '/overview');
        path_set_alias('node/' . $node->nid . '/sessions');
        path_set_alias('node/' . $node->nid . '/materials');
        path_set_alias('node/' . $node->nid . '/rss');
        path_set_alias('node/' . $node->nid . '/rdf');
      }
      break;
  }
}
