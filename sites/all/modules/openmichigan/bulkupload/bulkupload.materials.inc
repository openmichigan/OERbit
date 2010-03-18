<?php
// $Id$

function bulkupload_create_material($path) {
  global $user;
  $form_state = array();
  $form_state['values'] = array(
    'type' => 'material',
    'uid' => $user->uid,
    'title' => $path,
  );
}
