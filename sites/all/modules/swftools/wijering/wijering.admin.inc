<?php
// $Id: wijering.admin.inc,v 1.3 2009/02/17 23:12:01 stuartgreenfield Exp $

function wijering_admin_form() {

  $saved_settings = _wijering_settings(WIJERING_MEDIAPLAYER);
  // Flatten settings for convenience
  $saved = array();
  foreach ($saved_settings AS $category => $vars) {
    $saved = array_merge($saved, $vars);
  }
  $options = _wijering_options();

  $form = array();

  $form['wijering_mediaplayer']['basic'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Basic'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_mediaplayer']['basic']['displayheight'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['displayheight'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Display height'),
    '#description' => t('Leave blank for default which will respond to the available height of the player. (<em>displayheight</em>)'),
  );
  $form['wijering_mediaplayer']['basic']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['height'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Height'),
    '#description' => t('Leave blank for default. (<em>height</em>)'),
  );
  $form['wijering_mediaplayer']['basic']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['width'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Width'),
    '#description' => t('Leave blank for default. (<em>width</em>)'),
  );
  $form['wijering_mediaplayer']['color'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Color'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_mediaplayer']['color']['backcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['backcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>backcolor</em>)'),
  );
  $form['wijering_mediaplayer']['color']['frontcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['frontcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>frontcolor</em>)'),
  );
  $form['wijering_mediaplayer']['color']['lightcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['lightcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Rollover color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>lightcolor</em>)'),
  );
  $form['wijering_mediaplayer']['appearance'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_mediaplayer']['appearance']['autoscroll'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['autoscroll'],
    '#title' => t('Autoscroll'),
    '#description' => t('Provide a scrollbar or autoscroll with mouse movements. (<em>autoscroll</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['displaywidth'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['displaywidth'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Display width'),
    '#description' => t('Setting this will result in controls along the side and override "Display width". (<em>displaywidth</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['largecontrols'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['largecontrols'],
    '#title' => t('Large controls'),
    '#description' => t('Double the size of the controls. (<em>largecontrols</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['logo'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['logo'],
    '#title' => t('Logo URL'),
    '#description' => t('Full url to logo for a watermark, use PNG files for best results. (<em>logo</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['overstretch'] = array(
    '#type' => 'select',
    '#default_value' => $saved['overstretch'],
    '#title' => t('Overstretch'),
    '#options' => $options['overstretch'],
    '#description' => t('Defines how to stretch images to fit the display. (<em>overstretch</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['showdigits'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['showdigits'],
    '#title' => t('Show digits'),
    '#description' => t('Show or hide the elasped/total time. (<em>showdigits</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['showeq'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['showeq'],
    '#title' => t('Show equalizer'),
    '#description' => t('Nice and fake graphic equalizer. (<em>showeq</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['showicons'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['showicons'],
    '#title' => t('Show icons'),
    '#description' => t('Show status icons in display. (<em>showicons</em>)'),
  );
  $form['wijering_mediaplayer']['appearance']['thumbsinplaylist'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['thumbsinplaylist'],
    '#title' => t('Show thumbs in playlist'),
    '#description' => t('Show item by item thumbnails passed by xml playlist. (<em>thumbsinplaylist</em>)'),
  );
  $form['wijering_mediaplayer']['playback'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Playback'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_mediaplayer']['playback']['autostart'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the media. (<em>autostart</em>)'),
  );
  $form['wijering_mediaplayer']['playback']['bufferlength'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['bufferlength'],
    '#size' => 5,
    '#maxlength' => 2,
    '#title' => t('Buffer length'),
    '#description' => t('Number of seconds of buffering before playing file. (<em>bufferlength</em>)'),
  );
  $form['wijering_mediaplayer']['playback']['repeat'] = array(
    '#type' => 'select',
    '#default_value' => $saved['repeat'],
    '#title' => t('Repeat'),
    '#options' => $options['repeat'],
    '#description' => t('Set whether the media repeats after completion. (<em>repeat</em>)'),
  );
  $form['wijering_mediaplayer']['playback']['rotatetime'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['rotatetime'],
    '#size' => 5,
    '#maxlength' => 3,
    '#title' => t('Rotate time'),
    '#description' => t('Number of seconds between image rotations. (<em>rotatetime</em>)'),
  );
  $form['wijering_mediaplayer']['playback']['shuffle'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['shuffle'],
    '#title' => t('Shuffle'),
    '#description' => t('Shuffle media randomly. (<em>shuffle</em>)'),
  );
  $form['wijering_mediaplayer']['playback']['volume'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['volume'],
    '#size' => 8,
    '#maxlength' => 3,
    '#title' => t('Volume'),
    '#description' => t('Starting volume of the player. (<em>volume</em>)'),
  );
  $form['wijering_mediaplayer']['interaction'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Interaction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_mediaplayer']['interaction']['callback'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['callback'],
    '#title' => t('Callback URL'),
    '#description' => t('Full url used to pass statistics back to a server. (<em>callback</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['captions'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['captions'],
    '#title' => t('Captions URL'),
    '#description' => t('Full url used to an external textfile with captions. (<em>captions</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['enablejs'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['enablejs'],
    '#title' => t('Enable javascript'),
    '#description' => t('Enable javascript interaction with the flash player. (<em>enablejs</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['fsbuttonlink'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['fsbuttonlink'],
    '#title' => t('Fullscreen button link'),
    '#description' => t('Full url link to an alternative page, assuming the player supports full screen play. (<em>fsbuttonlink</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['link'],
    '#title' => t('Link URL'),
    '#description' => t('Web address linked to logo watermark. (<em>link</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['linkfromdisplay'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['linkfromdisplay'],
    '#title' => t('Link from display'),
    '#description' => t('Link "Link URL" but with the whole display as the click area. (<em>linkfromdisplay</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['linktarget'] = array(
    '#type' => 'select',
    '#default_value' => $saved['linktarget'],
    '#options' => $options['linktarget'],
    '#title' => t('Link target'),
    '#description' => t('Target of "Link URL". (<em>linktarget</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['streamscript'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['streamscript'],
    '#title' => t('Streaming script URL'),
    '#description' => t('Full url to \'fake\' streaming script. (<em>streamscript</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['type'] = array(
    '#type' => 'textfield',
    '#size' => 8,
    '#maxlength' => 5,
    '#default_value' => $saved['type'],
    '#title' => t('File type'),
    '#description' => t('Specify a default filename extension, rarely required. (<em>type</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['usecaptions'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['usecaptions'],
    '#title' => t('Use captions'),
    '#description' => t('Determine whether to show captions. (<em>usecaptions</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['usefullscreen'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['usefullscreen'],
    '#title' => t('Use fullscreen'),
    '#description' => t('Determine whether to allow fullscreen functionality. (<em>usefullscreen</em>)'),
  );
  $form['wijering_mediaplayer']['interaction']['usekeys'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['usekeys'],
    '#title' => t('Use keys'),
    '#description' => t('Determine whether to allow interaction with the keyboard. (<em>usekeys</em>)'),
  );

  $form['#tree'] = TRUE;

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'), '#submit' => array('swftools_admin_form_submit') );
  $form['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults'), '#submit' => array('swftools_admin_form_submit') );
  $form['#theme'] = 'system_settings_form';

  return $form;

}
