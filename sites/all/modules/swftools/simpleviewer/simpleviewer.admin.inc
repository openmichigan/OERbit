<?php
// $Id: simpleviewer.admin.inc,v 1.2 2008/09/07 19:42:14 stuartgreenfield Exp $

function simpleviewer_admin_form($flat = FALSE) {

  $form['simpleviewer_miscellaneous'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['simpleviewer_miscellaneous']['simpleviewer_display_title'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('simpleviewer_display_title', 1),
    '#title' => t('Display title'),
    '#description' => t('Whether to display the node title in the flash animation.'),
  );
  $form['simpleviewer_miscellaneous']['simpleviewer_display_album'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('simpleviewer_display_album', 1),
    '#title' => t('Display album name'),
    '#description' => t('Whether to display the album name in the flash animation.'),
  );
  $form['simpleviewer_miscellaneous']['simpleviewer_display_link'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('simpleviewer_display_link', 0),
    '#title' => t('Display download link'),
    '#description' => t('Apart from the node title, also display a clickable link to allow downloading the originally uploaded image.'),
  );
  $form['simpleviewer_dimensions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dimensions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('All dimensions should be given in pixels.'),
  );
  $form['simpleviewer_dimensions']['simpleviewer_swf_width'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_swf_width', 700),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Width of SimpleViewer'),
    '#required' => TRUE,
  );
  $form['simpleviewer_dimensions']['simpleviewer_swf_height'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_swf_height', 600),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Height of SimpleViewer'),
    '#required' => TRUE,
  );
  $form['simpleviewer_dimensions']['simpleviewer_xml_maxImageWidth'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_maxImageWidth', 480),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Width of your largest image in pixels'),
    '#required' => TRUE,
    '#description' => t('Used to determine the best layout for your gallery.'),
  );
  $form['simpleviewer_dimensions']['simpleviewer_xml_maxImageHeight'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_maxImageHeight', 480),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Height of your largest image in pixels'),
    '#required' => TRUE,
    '#description' => t('Used to determine the best layout for your gallery.'),
  );
  $form['simpleviewer_dimensions']['simpleviewer_xml_frameWidth'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_frameWidth', 20),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Width of image frame in pixels'),
    '#required' => TRUE,
  );
  $form['simpleviewer_dimensions']['simpleviewer_xml_stagePadding'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_stagePadding', 40),
    '#size' => 5,
    '#maxlength' => 5,
    '#title' => t('Stage padding'),
    '#description' => t('Distance between image and thumbnails and around gallery edge in pixels.'),
    '#required' => TRUE,
  );
  $form['simpleviewer_colors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Colors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('All colors should be given as hexadecimal rgb-values like \'#FFFFFF\'.'),
  );
  $form['simpleviewer_colors']['simpleviewer_swf_bgcolor'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_swf_bgcolor', '#181818'),
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Background color of flash animation.'),
    '#required' => TRUE,
  );
  $form['simpleviewer_colors']['simpleviewer_swf_wmode'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('simpleviewer_swf_wmode', 0),
    '#title' => t('Tranparency'),
    '#description' => t('Checking this box will make your background transparent. This setting overrides the background color setting.'),
  );
  $form['simpleviewer_colors']['simpleviewer_xml_loader_color'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_loader_color', '#ff0000'),
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Flash loader color'),
    '#description' => t('Color of part of flash animation that says "loading xml data", while loading your gallery.'),
    '#required' => TRUE,
  );
  $form['simpleviewer_colors']['simpleviewer_xml_textColor'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_textColor', '#ffffff'),
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Color of title and caption text.'),
    '#required' => TRUE,
  );
  $form['simpleviewer_colors']['simpleviewer_xml_frameColor'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('simpleviewer_xml_frameColor', '#ffffff'),
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Frame color'),
    '#description' => t('Color of image frame, navigation buttons (on top and hover buttons) and thumbnail frame.'),
    '#required' => TRUE,
  );
  $form['simpleviewer_navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $options_1 = drupal_map_assoc(array(0, 1, 2, 3, 4, 5));
  $options_2 = drupal_map_assoc(array('top', 'bottom', 'left', 'right'));
  $form['simpleviewer_navigation']['simpleviewer_xml_navPosition'] = array(
    '#type' => 'select',
    '#options' => $options_2,
    '#default_value' => variable_get('simpleviewer_xml_navPosition', 'top'),
    '#title' => t('Navigation position'),
    '#description' => t('Position of thumbnails relative to image.'),
  );
  $form['simpleviewer_navigation']['simpleviewer_xml_thumbnailColumns'] = array(
    '#type' => 'select',
    '#options' => $options_1,
    '#default_value' => variable_get('simpleviewer_xml_thumbnailColumns', 4),
    '#title' => t('Thumbnail columns'),
    '#description' => t('Number of thumbnail columns. To disable thumbnails completely set this value to 0'),
  );
  $form['simpleviewer_navigation']['simpleviewer_xml_thumbnailRows'] = array(
    '#type' => 'select',
    '#options' => $options_1,
    '#default_value' => variable_get('simpleviewer_xml_thumbnailRows', 1),
    '#title' => t('Thumbnail rows'),
    '#description' => t('Number of thumbnail rows. To disable thumbnails completely set this value to 0.'),
  );
/*
  $form['miscellaneous']['simpleviewer_rebuild_thumbs'] = array(
    '#type' => 'checkbox',
    '#default_value' => 0,
    '#title' => t('Build thumbnail library'),
    '#description' => t('Normally, you should do this only once, after installing the module. This builds a library of thumbnails based on pre-existing images which reside inside pre-exising galleries. You do not have to repeat this later on: images that are created after installing this module are handled automatically. '),
  );
*/

  if ($flat === TRUE) {
    return array_merge($form['simpleviewer_dimensions'], $form['simpleviewer_colors'], $form['simpleviewer_navigation'], $form['simpleviewer_miscellaneous']);
  }
  else {

    // Clear all caches
    drupal_flush_all_caches();

    return system_settings_form($form);
  }
}
