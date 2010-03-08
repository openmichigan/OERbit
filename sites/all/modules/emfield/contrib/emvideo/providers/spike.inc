<?php
// $Id: spike.inc,v 1.1.2.9 2009/10/29 13:29:51 aaron Exp $

/**
 * @file
 *   This include processes Spike media files for use by emfield.module.
 */

define('EMVIDEO_SPIKE_MAIN_URL', 'http://www.spike.com/');

function emvideo_spike_info() {
  $features = array(
    array(t('Autoplay'), t('No'), t('In the works...')),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('In the works...'), ''),
  );
  return array(
    'provider' => 'spike tv',
    'name' => t('Spike TV'),
    'url' => EMVIDEO_SPIKE_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from <a href="@spike" target="_blank">Spike TV</a>.', array('@spike' => EMVIDEO_SPIKE_MAIN_URL)),
    'supported_features' => $features,
  );
}

function emvideo_spike_settings() {
  $form = array();
  return $form;
}

function emvideo_spike_extract($embed) {
  return array(
    // http://www.spike.com/video/2836119/collection/19459/channel/comedy
    // <embed width="448" height="365" src="http://www.spike.com/efp" quality="high" bgcolor="000000" name="efp" align="middle" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" flashvars="flvbaseclip=2836119&"> </embed> <h1><a href="http://www.spike.com/video/2836119">"I Lost It" with Tom Cruize and Jesus</a></h1><span>Posted Mar 25, 2007</span><p>What happens when Jesus, Abe Lincoln, Tom Cruise, Dustin Hoffman, Buddha and Einstein play a friendly game of poker?</p>
    '@spike\.com/efp"(?:.*)flvbaseclip=([^&]+)@i',
    '@spike\.com/video/([^/&"\?]*)@i',
  );
}

function emvideo_spike_request($embed, $cacheable = TRUE) {
  return NULL;
}

function emvideo_spike_video_link($video_code) {
  return 'http://www.spike.com/video/'. $video_code;
}

function theme_emvideo_spike_flash($embed, $width, $height, $autoplay) {
  // TODO: figure out autoplay...
  //<embed width="448" height="365" src="http://www.spike.com/efp" quality="high" bgcolor="000000" name="efp" align="middle" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" flashvars="flvbaseclip=2952560&"> </embed>
  if ($embed) {
    $autoplay = $autoplay ? ' autoplay="true"' : '';
    $output = '<embed width="'. $width .'" height="'. $height .'" src="http://www.spike.com/efp" quality="high" bgcolor="000000" name="efp" align="middle" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" flashvars="flvbaseclip='. $embed .'"> </embed>';
  }

  return $output;
}

/**
 *  TODO: Is this correct? Using ifilmpro for thumbnails.
 */
function emvideo_spike_thumbnail($field, $item, $formatter, $node, $width, $height) {
  $picturelink = drupal_substr($item['value'], 0, 7);

  return 'http://img1.ifilmpro.com/resize/image/stills/films/resize/istd/'. $picturelink .'.jpg?width='. $width;
}

function emvideo_spike_video($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('emvideo_spike_flash', $embed, $width, $height, $autoplay);
  return $output;
}

function emvideo_spike_preview($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('emvideo_spike_flash', $embed, $width, $height, $autoplay);
  return $output;
}

/**
 * Implementation of hook_emfield_subtheme.
 */
function emvideo_spike_emfield_subtheme() {
  return array(
    'emvideo_spike_flash' => array(
      'arguments' => array('embed' => NULL, 'width' => NULL, 'height' => NULL, 'autoplay' => NULL),
      'file' => 'providers/spike.inc'
    )
  );
}
