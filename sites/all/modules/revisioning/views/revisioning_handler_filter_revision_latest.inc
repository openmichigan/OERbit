<?php
/**
 * @file
 *   Views filter override to filter on revision recency, i.e. whether this is
 *   the latest revision of a node or not.
 */

class revisioning_handler_filter_revision_latest extends views_handler_filter_boolean_operator {
  /**
   * Override the query, in particular the WHERE clause.
   */
  function query() {
    $revisions_table = $this->ensure_my_table();
    $node_table = $this->query->ensure_table('node');

    $max_vid_subquery = "SELECT MAX(vid) FROM {". $revisions_table ."} WHERE $revisions_table.nid=$node_table.nid";
    // The subquery selects the maximum vid for a given nid
    // This is guaranteed to be the latest revision, because vids are assigned
    // chronologically.
    $where_clause =  ($this->value == 1)
      ? "$revisions_table.vid =($max_vid_subquery)"
      : "$revisions_table.vid!=($max_vid_subquery)";
    $this->query->add_where($this->options['group'], $where_clause);
  }

}