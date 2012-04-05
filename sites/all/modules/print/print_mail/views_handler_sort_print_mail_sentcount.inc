<?php

/**
 * @file
 * Views sort handler for the print_mail module
 *
 * Extend the default sort handler.
 * Add a relationship with custom join to print's emailed counter
 */
class views_handler_sort_print_mail_sentcount extends views_handler_sort {
  function query() {
    $table = 'print_mail_page_counter';
    $join = new views_join;
    $join->construct($table, NULL, "CONCAT('node/', node.nid)", 'path', NULL, 'LEFT');
    $alias = $this->query->add_relationship($table, $join, 'node');
    $this->query->add_orderby($table, 'sentcount', $this->options['order']);
  }
}
