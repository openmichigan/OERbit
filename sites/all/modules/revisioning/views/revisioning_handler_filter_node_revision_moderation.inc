<?php
// $Id: revisioning_handler_filter_node_revision_moderation.inc,v 1.2 2010/04/08 01:46:26 rdeboer Exp $

/**
 * @file
 *   Views filter override to filter on whether node is subject to moderation.
 */

define('REVISIONING_MODERATED', 1);
define('REVISIONING_NOT_MODERATED', 0);

class revisioning_handler_filter_node_revision_moderation extends views_handler_filter_in_operator {

  /**
   * Add a where clause to the query.
   */
  function query() {
    if (empty($this->value) || (isset($this->value[0]) && isset($this->value[1]))) {
      return; // don't filter if none or both options are set
    }
    $moderated_content_types = array();
    foreach (revisioning_moderated_content_types() as $moderated_content_type) {
      $moderated_content_types[] = "'$moderated_content_type'";
    }
    $this->ensure_my_table();
    if (empty($moderated_content_types)) {
      if (isset($this->value[0]) && $this->value[0] == REVISIONING_MODERATED) {
        // None of the content types are moderated, so return nothing
        $this->query->add_where($this->options['group'], '1 = 0');
      }
    }
    else {
      $where_clause = $this->table_alias .'.type IN ('. implode(',', $moderated_content_types) .')';
      if (isset($this->value[0]) && $this->value[0] == REVISIONING_NOT_MODERATED) {
        $where_clause = "!($where_clause)";
      }
      if ($this->operator == 'not in') {
        $where_clause = ($where_clause[0] == '!') ? drupal_substr($where_clause, 1) : "!($where_clause)";
      }
      $this->query->add_where($this->options['group'], $where_clause);
    }
  }

  function get_value_options() {
    $this->value_title = t('Moderated');
    $this->value_options =  array(
      REVISIONING_MODERATED => t('Moderated'),
      REVISIONING_NOT_MODERATED => t('Not moderated'));
  }
}