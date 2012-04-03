<?php

/**
 * @file
 *  Handler for the 'Node revision: state' field.
 */
class revisioning_handler_field_revision_state extends views_handler_field {

  function construct() {
    parent::construct();
    // Collect additional data required prior to rendering
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['vid'] = 'vid';
    $this->additional_fields['published'] = array('table' => 'node', 'field' => 'status');
    $this->additional_fields['current_vid']  = array('table' => 'node', 'field' => 'vid');
  }

  function access() {
    return user_access('view revisions');
  }

  function query() {
    // Not calling parent::query() as it will treat 'state' as a real db field.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Note that $values contains:
   *   o node_revisions_nid (parent node id)
   *   o node_revisions_vid (revision id)
   *   o node_status (published flag)
   *   o node_vid (current revision id)
   */
  function render($values) {
    $nid = $values->{$this->aliases['nid']};
    $vid = $values->{$this->aliases['vid']};
    $published = $values->{$this->aliases['published']};
    $current_vid = $values->{$this->aliases['current_vid']};
    $is_initial_unpublished_draft = !$published && (node_tools_get_number_of_revisions($nid) == 1);
    $is_pending = ($vid > $current_vid) || $is_initial_unpublished_draft;
    $state_code = $is_pending ? REVISION_PENDING : ($vid == $current_vid ? REVISION_CURRENT : REVISION_ARCHIVED);
    $description = revisioning_revision_states($state_code);
    return $description;
  }
}
