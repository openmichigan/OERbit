<?php
// $Id: onepixelout.admin.inc,v 1.3 2008/10/02 21:16:41 stuartgreenfield Exp $

function onepixelout_admin_form() {

  $saved = _onepixelout_settings();

  $form = array();

  $form['onepixelout_mediaplayer']['autostart'] = array(
    '#type' => 'select',
    '#options' => array('yes' => 'yes', 'no' => 'no'),
    '#default_value' => $saved['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the MP3. (<em>autostart</em>)'),
  );

  $form['onepixelout_mediaplayer']['loop'] = array(
    '#type' => 'select',
    '#options' => array('yes' => 'yes', 'no' => 'no'),
    '#default_value' => $saved['loop'],
    '#title' => t('Loop'),
    '#description' => t('Loop the sound file back to the beginning when done. (<em>loop</em>)'),
  );

  $form['onepixelout_mediaplayer']['map'] = array(
    '#value' => '<img src="http://www.1pixelout.net/wp-content/plugins/audio-player/map.gif" alt="Player Map" />',
  );

  unset($saved['loop']);
  unset($saved['autostart']);

  foreach ($saved AS $key => $color) {
    $form['onepixelout_mediaplayer'][$key] = array(
      '#type' => 'textfield',
      '#default_value' => $color,
      '#size' => 8,
      '#maxlength' => 8,
      '#title' => t($key .' color'),
      '#description' => t('Hexadecimal color of the format 0xRRGGBB'),
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );
  $form['#theme'] = 'system_settings_form';

  return $form;
}

/*
 * Called by onepixelout_admin_form_submit()
 */
function onepixelout_admin_form_submit($form, &$form_state) {

  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  if ($op == t('Reset to defaults')) {
    variable_del('swftools_'. ONEPIXELOUT);
    drupal_set_message(t('The configuration options have been reset to their default values.'));
  } else {
    // Exclude unnecessary elements.
    unset($form_state['values']['submit'], $form_state['values']['reset'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);
    // Store values
    variable_set('swftools_'. ONEPIXELOUT, $form_state['values']);
    drupal_set_message(t('The configuration options have been saved.'));
  }

  // Clear all caches
  drupal_flush_all_caches();

}
