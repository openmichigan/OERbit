<?php
// $Id: deepblue.inc,v 1.1.2.7 2009/11/19 16:34:58 aaron Exp $

/**
 * @file
 *   Provide support for the Tudou provider to the emfield.module.
 */

define('EMVIDEO_DEEPBLUE_MAIN_URL', 'http://deepblue.lib.umich.edu/');

/**
 * hook emvideo_PROVIDER_info
 * this returns information relevant to a specific 3rd party video provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function emvideo_deepblue_info() {
  $features = array(
    array(t('Autoplay'), t('No'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), t('')),
  );
  return array(
    'provider' => 'deepblue',
    'name' => t('Deepblue'),
    'url' => EMVIDEO_DEEPBLUE_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from <a href="@deepblue" target="_blank">Deepblue</a>.', array('@deepblue' => EMVIDEO_DEEPBLUE_MAIN_URL)),
    'supported_features' => $features,
  );
}

/**
 * hook emvideo_PROVIDER_settings
 * this should return a subform to be added to the emvideo_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['deepblue'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function emvideo_deepblue_settings() {
  $form = array();
  return $form;
}

/**
 * hook emvideo_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the video code to be used
 *   if the hook tests the code itself, it should return either the string of the video code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function emvideo_deepblue_extract($embed = '') {
  // http://deepblue.lib.umich.edu/programs/view/uprLNXyEGpc/
  // <object width="400" height="300"><param name="movie" value="http://deepblue.lib.umich.edu/v/uprLNXyEGpc"></param><param name="allowScriptAccess" value="always"></param><param name="wmode" value="transparent"></param><embed src="http://deepblue.lib.umich.edu/v/uprLNXyEGpc" type="application/x-shockwave-flash" width="400" height="300" allowFullScreen="true" wmode="transparent" allowScriptAccess="always"></embed></object>
  return array(
    '@deepblue\.lib\.umich\.edu/handle/.*/([^"\&/]+)@i',
  );
}

/**
 * hook emvideo_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function emvideo_deepblue_embedded_link($video_code) {
  return 'http://deepblue.lib.umich.edu/handle/2027.42/'. $video_code;
}

/**
 * the embedded flash displaying the deepblue video
 */
function theme_emvideo_deepblue_flash($embed, $width, $height, $autoplay) {
  if ($embed) {
    $output .= "
      <object width=\"$width\" height=\"$height\">
        <param name=\"movie\" value=\"http://deepblue.lib.umich.edu/v/$embed\"></param>
        <param name=\"allowScriptAccess\" value=\"always\"></param>
        <param name=\"wmode\" value=\"transparent\"></param>
        <embed src=\"http://deepblue.lib.umich.edu/v/$embed\" type=\"application/x-shockwave-flash\" width=\"$width\" height=\"$height\" allowFullScreen=\"true\" wmode=\"transparent\" allowScriptAccess=\"always\"></embed>
        </object>
    ";
  }
  return $output;
}

/**
 * hook emvideo_PROVIDER_thumbnail
 * returns the external url for a thumbnail of a specific video
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things
 *  @param $field
 *    the field of the requesting node
 *  @param $item
 *    the actual content of the field from the requesting node
 *  @return
 *    a URL pointing to the thumbnail
 */
function emvideo_deepblue_thumbnail($field, $item, $formatter, $node, $width, $height) {
}

/**
 * hook emvideo_PROVIDER_video
 * this actually displays the full/normal-sized video we want, usually on the default page view
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_deepblue_video($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('emvideo_deepblue_flash', $embed, $width, $height, $autoplay);
  return $output;
}

/**
 * hook emvideo_PROVIDER_video
 * this actually displays the preview-sized video we want, commonly for the teaser
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_deepblue_preview($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('emvideo_deepblue_flash', $embed, $width, $height, $autoplay);
  return $output;
}

function emvideo_deepblue_emfield_subtheme() {
  return array(
    'emvideo_deepblue_flash' => array(
      'arguments' => array('embed' => NULL, 'width' => NULL, 'height' => NULL, 'autoplay' => NULL),
      'file' => 'providers/deepblue.inc'
    )
  );
}
