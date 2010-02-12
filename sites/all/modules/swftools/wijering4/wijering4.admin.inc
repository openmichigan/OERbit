<?php
// $Id: wijering4.admin.inc,v 1.3.2.1 2009/04/21 22:01:11 stuartgreenfield Exp $

function wijering4_admin_form() {

  $saved_settings = _wijering4_settings(WIJERING4_MEDIAPLAYER);

  // Flatten settings for convenience
  $saved = array();
  foreach ($saved_settings AS $category => $vars) {
    $saved = array_merge($saved, $vars);
  }
  $options = _wijering4_options();

  $form = array();

  $form['wijering4_mediaplayer']['basic'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Basic'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering4_mediaplayer']['basic']['playlistsize'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['playlistsize'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Playlist size'),
    '#description' => t('Leave blank for default. (<em>playlistsize</em>)'),
  );
  $form['wijering4_mediaplayer']['basic']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['height'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Height'),
    '#description' => t('Leave blank for default. (<em>height</em>)'),
  );
  $form['wijering4_mediaplayer']['basic']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['width'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Width'),
    '#description' => t('Leave blank for default. (<em>width</em>)'),
  );
  $form['wijering4_mediaplayer']['color'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Color'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering4_mediaplayer']['color']['backcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['backcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>backcolor</em>)'),
  );
  $form['wijering4_mediaplayer']['color']['frontcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['frontcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>frontcolor</em>)'),
  );
  $form['wijering4_mediaplayer']['color']['lightcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['lightcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Rollover color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>lightcolor</em>)'),
  );
  $form['wijering4_mediaplayer']['color']['screencolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['screencolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Screen color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>screencolor</em>)'),
  );
  $form['wijering4_mediaplayer']['appearance'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering4_mediaplayer']['appearance']['skin'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['skin'],
    '#title' => t('Skin URL'),
    '#description' => t('Full url to a skin for the player. (<em>skin</em>)'),
  );
  /**
  $form['wijering4_mediaplayer']['appearance']['displaywidth'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['displaywidth'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Display width'),
    '#description' => t('Setting this will result in controls along the side and override "Display width". (<em>displaywidth</em>)'),
  );
  **/
  $form['wijering4_mediaplayer']['appearance']['logo'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['logo'],
    '#title' => t('Logo URL'),
    '#description' => t('Full url to logo for a watermark, use PNG files for best results. (<em>logo</em>)'),
  );
  $form['wijering4_mediaplayer']['appearance']['overstretch'] = array(
    '#type' => 'select',
    '#default_value' => $saved['overstretch'],
    '#title' => t('Overstretch'),
    '#options' => $options['overstretch'],
    '#description' => t('Defines how to stretch images to fit the display. (<em>overstretch</em>)'),
  );
  $form['wijering4_mediaplayer']['appearance']['controlbar'] = array(
    '#type' => 'select',
    '#default_value' => $saved['controlbar'],
    '#title' => t('Control bar position'),
    '#options' => $options['controlbar'],
    '#description' => t('Defines where to position the control bar. (<em>controlbar</em>)'),
  );
  $form['wijering4_mediaplayer']['appearance']['playlist'] = array(
    '#type' => 'select',
    '#default_value' => $saved['playlist'],
    '#title' => t('Playlist position'),
    '#options' => $options['playlist'],
    '#description' => t('Defines where to position the playlist. (<em>playlist</em>)'),
  );
  $form['wijering4_mediaplayer']['playback'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Playback'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering4_mediaplayer']['playback']['autostart'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the media. (<em>autostart</em>)'),
  );
  $form['wijering4_mediaplayer']['playback']['bufferlength'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['bufferlength'],
    '#size' => 5,
    '#maxlength' => 2,
    '#title' => t('Buffer length'),
    '#description' => t('Number of seconds of buffering before playing file. (<em>bufferlength</em>)'),
  );
  $form['wijering4_mediaplayer']['playback']['displayclick'] = array(
    '#type' => 'select',
    '#default_value' => $saved['displayclick'],
    '#title' => t('Display click'),
    '#options' => $options['displayclick'],
    '#description' => t('Action to take when the player is clicked. (<em>displayclick</em>)'),
  );
  $form['wijering4_mediaplayer']['playback']['repeat'] = array(
    '#type' => 'select',
    '#default_value' => $saved['repeat'],
    '#title' => t('Repeat'),
    '#options' => $options['repeat'],
    '#description' => t('Set whether the media repeats after completion. (<em>repeat</em>)'),
  );
  $form['wijering4_mediaplayer']['playback']['shuffle'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['shuffle'],
    '#title' => t('Shuffle'),
    '#description' => t('Shuffle media randomly. (<em>shuffle</em>)'),
  );
  $form['wijering4_mediaplayer']['playback']['volume'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['volume'],
    '#size' => 8,
    '#maxlength' => 3,
    '#title' => t('Volume'),
    '#description' => t('Starting volume of the player. (<em>volume</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Interaction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering4_mediaplayer']['interaction']['captions'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['captions'],
    '#title' => t('Captions URL'),
    '#description' => t('Full url used to an external textfile with captions. (<em>captions</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction']['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['link'],
    '#title' => t('Link URL'),
    '#description' => t('Web address linked to logo watermark. (<em>link</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction']['linktarget'] = array(
    '#type' => 'select',
    '#default_value' => $saved['linktarget'],
    '#options' => $options['linktarget'],
    '#title' => t('Link target'),
    '#description' => t('Target of "Link URL". (<em>linktarget</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction']['streamscript'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['streamscript'],
    '#title' => t('Streaming script URL'),
    '#description' => t('Full url to \'fake\' streaming script. (<em>streamscript</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction']['type'] = array(
    '#type' => 'select',
    '#options' => $options['type'],
    '#default_value' => $saved['type'],
    '#title' => t('File type'),
    '#description' => t('Specify a default filetype, the default setting will auto-detect. (<em>type</em>)'),
  );
  $form['wijering4_mediaplayer']['interaction']['fullscreen'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['fullscreen'],
    '#title' => t('Allow use of fullscreen'),
    '#description' => t('Determine whether to allow fullscreen functionality. (<em>usefullscreen</em>).<br /><em>Allow full screen mode</em> must also be enabled on the SWF Tools embedding settings page.'),
  );

  $form['wijering4_mediaplayer']['accessibility'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Accessibility'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['wijering4_mediaplayer']['accessibility']['accessible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved['accessible'],
    '#title' => t('Make the player accessible'),
    '#description' => t('If this option is enabled then accessible links will be put below the player to allow it to be controlled using a keyboard or other input device.'),
  );

  $form['wijering4_mediaplayer']['accessibility']['accessible_visible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved['accessible_visible'],
    '#title' => t('Make the accessible controls visible'),
    '#description' => t('If this option is enabled then accessible links will be visible on the page. If this option is cleared then the links will be hidden, but still accessible to devices such as screen readers.'),
  );
  
  
 $form['#tree'] = TRUE;

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'), '#submit' => array('swftools_admin_form_submit') );
  $form['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults'), '#submit' => array('swftools_admin_form_submit') );
  $form['#theme'] = 'system_settings_form';

  return $form;

}
