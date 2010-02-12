<?php
// $Id: imagerotator.admin.inc,v 1.2.2.1 2009/04/22 21:39:33 stuartgreenfield Exp $

function imagerotator_admin_form() {

  $options = _imagerotator_options();

  $form = array();

 // Image Rotator

  $saved_settings = _imagerotator_settings(WIJERING_IMAGEROTATOR);
  // Flatten settings for convenience
  $saved = array();
  foreach ($saved_settings AS $category => $vars) {
    $saved = array_merge($saved, $vars);
  }

  $form['wijering_imagerotator']['basic'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Basic'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_imagerotator']['basic']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['height'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Height'),
    '#description' => t('Leave blank for default. (<em>height</em>)'),
  );
  $form['wijering_imagerotator']['basic']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['width'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Width'),
    '#description' => t('Leave blank for default. (<em>width</em>)'),
  );
  $form['wijering_imagerotator']['color'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Color'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_imagerotator']['color']['backcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['backcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>backcolor</em>)'),
  );
  $form['wijering_imagerotator']['color']['frontcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['frontcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>frontcolor</em>)'),
  );
  $form['wijering_imagerotator']['color']['lightcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['lightcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Rollover color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>lightcolor</em>)'),
  );
  $form['wijering_imagerotator']['appearance'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_imagerotator']['appearance']['logo'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['logo'],
    '#title' => t('Logo URL'),
    '#description' => t('Full url to logo for a watermark, use PNG files for best results. (<em>logo</em>)'),
  );
  $form['wijering_imagerotator']['appearance']['overstretch'] = array(
    '#type' => 'select',
    '#default_value' => $saved['overstretch'],
    '#title' => t('Overstretch'),
    '#options' => $options['overstretch'],
    '#description' => t('Defines how to stretch images to fit the display. (<em>overstretch</em>)'),
  );
  $form['wijering_imagerotator']['appearance']['showicons'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['showicons'],
    '#title' => t('Show icons'),
    '#description' => t('Show status icons in display. (<em>showicons</em>)'),
  );
  $form['wijering_imagerotator']['appearance']['shownavigation'] = array(
    '#type' => 'select',
    '#default_value' => $saved['shownavigation'],
    '#options' => $options['bool'],
    '#title' => t('Show navigation'),
    '#description' => t('If false then all navigation controls are hidden. (<em>shownavigation</em>)'),
  );
  $form['wijering_imagerotator']['appearance']['transition'] = array(
    '#type' => 'select',
    '#default_value' => $saved['transition'],
    '#options' => $options['transition'],
    '#title' => t('Transition effect'),
    '#description' => t('The way the photos change from one to another. (<em>transition</em>)'),
  );
  
  $form['wijering_imagerotator']['playback'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Playback'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['wijering_imagerotator']['playback']['rotatetime'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['rotatetime'],
    '#size' => 5,
    '#maxlength' => 3,
    '#title' => t('Rotate time'),
    '#description' => t('Number of seconds between image rotations. (<em>rotatetime</em>)'),
  );
  $form['wijering_imagerotator']['playback']['shuffle'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['shuffle'],
    '#title' => t('Shuffle'),
    '#description' => t('Shuffle media randomly. (<em>shuffle</em>)'),
  );
  $form['wijering_imagerotator']['interaction'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Interaction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['wijering_imagerotator']['interaction']['enablejs'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['enablejs'],
    '#title' => t('Enable javascript'),
    '#description' => t('Enable javascript interaction with the flash player. (<em>enablejs</em>)'),
  );
  $form['wijering_imagerotator']['interaction']['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['link'],
    '#title' => t('Link URL'),
    '#description' => t('Web address linked to logo watermark. (<em>link</em>)'),
  );
  $form['wijering_imagerotator']['interaction']['linkfromdisplay'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved['linkfromdisplay'],
    '#title' => t('Link from display'),
    '#description' => t('Link "Link URL" but with the whole display as the click area. (<em>linkfromdisplay</em>)'),
  );
  $form['wijering_imagerotator']['interaction']['linktarget'] = array(
    '#type' => 'select',
    '#default_value' => $saved['linktarget'],
    '#options' => $options['linktarget'],
    '#title' => t('Link target'),
    '#description' => t('Target of "Link URL". (<em>linktarget</em>)'),
  );

  $form['#tree'] = TRUE;

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'), '#submit' => array('swftools_admin_form_submit') );
  $form['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );
  $form['#theme'] = 'system_settings_form';

  return $form;

}
