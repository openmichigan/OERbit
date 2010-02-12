<?php
// $Id: helper.php,v 1.1.2.2 2008/09/24 14:11:32 anselmheaton Exp $

/**
 * This function returns true if we should use javascript effects.
 * It checkes for the javascript setting in the admin page,
 * and for the has_js drupal cookie
 */
function _nodereferrer_use_js() {
  if (empty($_COOKIE['has_js'])) {
    return false;
  }
  
  return (boolean)variable_get('nodereferrer_create_javascript', 1);
}

/**
 * Helper function : given a node, return the list of fields of type
 * nodereference the current user is allowed to edit.
 * Nodereference view fields that use views aren't supported
 * yet, and so are not returned by this function.
 */
function _nodereferrer_create_get_reference_fields($node) {
  $list = array();
  
  if (!variable_get('nodereferrer_create_show_on_nodereference', 1)
      || !node_access('update', $node)) {
    return $list;
  }
  
  $type = content_types($node->type);
  foreach ($type['fields'] as $field) {
    if ($field['type'] == 'nodereference' && $field['advanced_view'] == '--') {
      $list[] = $field;
    }
  }
  
  return $list;
}

/**
 * Helper function : given a node, return the list of referrers the
 * current user is allowed to create as an array defining :
 *
 * 'name' : Name of the referrer field
 * 'field' : Details of the referer field
 * 'referrence' : Detail of the reference field
 *
 */
function _nodereferrer_create_get_referrers($node) {
  $list = array();

  if (!variable_get('nodereferrer_create_show_on_nodereferrer', 1)) {
    return $list;
  }
  
  $type = content_types($node->type);
  
  foreach($type['fields'] as $name => $field) {
    if ($field['type'] != 'nodereferrer' || 
        /*$field['widget']['type'] != 'nodereferrer_create_list' ||*/
        !is_array($field['referrer_types'])) {
      continue;
    }
    
    foreach(array_filter($field['referrer_types']) as $reftype) {
      if (!node_access('create', $reftype)) {
        continue;
      }
      
      $with_field = array();
      foreach(array_filter($field['referrer_fields']) as $reffield) {
        $cf = content_fields($reffield, $reftype);
        if ($cf) {
          $with_field[$reftype][] = $cf;
        }
      }
      
      if (count($with_field) == 0) {
        continue;
      }
      
      $list[] = array(
        'name'  => substr($name, strlen('field_')),
        'field' => $field,
        'referrence' => $with_field,
      );
    }
  }
  
  return $list;
}

/**
 * Helper function : returns true if we should alter this node
 */

function _nodereferrer_create_alter_node($node) {
  return true;
}

/**
 * This is a re-implementation of drupal_get_form, which returns the form_build_id along with the rendred form
 */
function _nodereferrer_create_get_form($form_id) {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);

  $args = func_get_args();
  $cacheable = FALSE;

  if (isset($_SESSION['batch_form_state'])) {
    // We've been redirected here after a batch processing : the form has
    // already been processed, so we grab the post-process $form_state value
    // and move on to form display. See _batch_finished() function.
    $form_state = $_SESSION['batch_form_state'];
    unset($_SESSION['batch_form_state']);
  }
  else {
    // If the incoming $_POST contains a form_build_id, we'll check the
    // cache for a copy of the form in question. If it's there, we don't
    // have to rebuild the form to proceed. In addition, if there is stored
    // form_state data from a previous step, we'll retrieve it so it can
    // be passed on to the form processing code.
    if (isset($_POST['form_id']) && $_POST['form_id'] == $form_id && !empty($_POST['form_build_id'])) {
      $form = form_get_cache($_POST['form_build_id'], $form_state);
    }

    // If the previous bit of code didn't result in a populated $form
    // object, we're hitting the form for the first time and we need
    // to build it from scratch.
    if (!isset($form)) {
      $form_state['post'] = $_POST;
      // Use a copy of the function's arguments for manipulation
      $args_temp = $args;
      $args_temp[0] = &$form_state;
      array_unshift($args_temp, $form_id);

      $form = call_user_func_array('drupal_retrieve_form', $args_temp);
      $form_build_id = 'form-'. md5(mt_rand());
      $form['#build_id'] = $form_build_id;
      drupal_prepare_form($form_id, $form, $form_state);
      // Store a copy of the unprocessed form for caching and indicate that it
      // is cacheable if #cache will be set.
      $original_form = $form;
      $cacheable = TRUE;
      unset($form_state['post']);
    }
    $form['#post'] = $_POST;

    // Now that we know we have a form, we'll process it (validating,
    // submitting, and handling the results returned by its submission
    // handlers. Submit handlers accumulate data in the form_state by
    // altering the $form_state variable, which is passed into them by
    // reference.
    drupal_process_form($form_id, $form, $form_state);
    if ($cacheable && !empty($form['#cache'])) {
      // Caching is done past drupal_process_form so #process callbacks can
      // set #cache. By not sending the form state, we avoid storing
      // $form_state['storage'].
      form_set_cache($form_build_id, $original_form, NULL);
    }
  }

  // Most simple, single-step forms will be finished by this point --
  // drupal_process_form() usually redirects to another page (or to
  // a 'fresh' copy of the form) once processing is complete. If one
  // of the form's handlers has set $form_state['redirect'] to FALSE,
  // the form will simply be re-rendered with the values still in its
  // fields.
  //
  // If $form_state['storage'] or $form_state['rebuild'] have been
  // set by any submit or validate handlers, however, we know that
  // we're in a complex multi-part process of some sort and the form's
  // workflow is NOT complete. We need to construct a fresh copy of
  // the form, passing in the latest $form_state in addition to any
  // other variables passed into drupal_get_form().

  if (!empty($form_state['rebuild']) || !empty($form_state['storage'])) {
    $form = drupal_rebuild_form($form_id, $form_state, $args);
  }

  // If we haven't redirected to a new location by now, we want to
  // render whatever form array is currently in hand.
  return array(
    'form_build_id' => $form['#build_id'],
    'form' => drupal_render_form($form_id, $form)
  );
}
?>
