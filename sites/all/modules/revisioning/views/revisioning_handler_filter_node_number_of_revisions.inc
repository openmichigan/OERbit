<?php

/**
 * @file
 *   Views filter override to filter on the number of revisions a node has.
 */

class revisioning_handler_filter_node_number_of_revisions extends views_handler_filter_numeric {

  /**
   * Override the query, in particular the WHERE clause.
   */
  function query() {
    if (empty($this->value)) {
      return;
    }
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $node_table = $this->ensure_my_table();
      $revisions_table = $this->query->ensure_table('node_revisions');
      $pseudo_field = '(SELECT COUNT(vid) FROM {'. $revisions_table ."} WHERE nid=$node_table.nid)";
      $this->{$info[$this->operator]['method']}($pseudo_field);
    }
  }
}