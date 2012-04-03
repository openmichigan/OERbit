<?php

/**
 * @file
 *  Handler for the 'Node: last edited by' field.
 */

class revisioning_handler_field_node_last_editor extends views_handler_field {

  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
  }

  function access() {
    return user_access('access content');
  }

  function query() {
    // Not calling parent::query() as it will treat 'last_editor' as a real db field.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $nid = $values->{$this->aliases['nid']};
    $uid = revisioning_get_last_editor($nid, FALSE);
    $account = user_load($uid);
    return $account->name;
  }
}
