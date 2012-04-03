<?php

/**
 * @file
 *  Handler for the 'Node: revision moderation' field.
 */
class revisioning_handler_field_node_revision_moderation extends views_handler_field {

  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function access() {
    return user_access('access content');
  }

  function query() {
    // Not calling parent::query() as it will treat 'number of revisions' as
    // a real db field.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $content_type = $values->{$this->aliases['type']};
    $moderated = node_tools_content_is_moderated($content_type);
    return $moderated ? t('Yes') : ''; // not returning 'No' to allow special tricks with empty field
  }
}
