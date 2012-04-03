<?php

/**
 * @file
 *   Views filter override to filter on revision state, i.e. pending, archived, current.
 */

class revisioning_handler_filter_revision_state extends views_handler_filter_in_operator {

  /**
   * Override the query, in particular the WHERE clause.
   */
  function query() {
    if (empty($this->value)) {
      return;
    }
    $revisions_table = $this->ensure_my_table();
    $node_table = $this->query->ensure_table('node');

    $subclauses = array();
    foreach ($this->value as $state_code) {
      switch ($state_code) {

        case REVISION_ARCHIVED:
          $subclauses[] = "($revisions_table.vid<$node_table.vid)";
          break;
        case REVISION_CURRENT:
          $subclauses[] = "($revisions_table.vid=$node_table.vid AND $node_table.status=1)";
          break;
        case REVISION_PENDING:
          $subclauses[] = "($revisions_table.vid>$node_table.vid OR ($node_table.status=0 AND (SELECT COUNT(vid) FROM {". $revisions_table ."} WHERE nid=$node_table.nid)=1))";
          break;
      }
    }
    if (!empty($subclauses)) {
      $where_clause = implode(' OR ', $subclauses);
      if ($this->operator == 'not in') {
        $where_clause = 'not '. $where_clause;
      }
      $this->query->add_where($this->options['group'], $where_clause);
    }
  }

  function get_value_options() {
    $this->value_title = t('Revision state');
    $this->value_options = revisioning_revision_states();
  }
}