<?php
// $Id: flowplayer3.admin.inc,v 1.13.2.8 2009/04/18 23:30:52 stuartgreenfield Exp $

/**
 * Menu callback for the FlowPlayer3 settings form.
 */
function flowplayer3_admin_settings() {
  
  // Retrieve combination of default and saved settings
  $saved_settings = _flowplayer3_settings();

  // Retrieve options needed to populate select elements
  $options = _flowplayer3_options();

  // Initialise array to hold form
  $form = array();

  // Add color scheme form
  $form['color'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Color scheme'),
    '#weight' => -1,
    '#attributes' => array('id' => 'flowplayer3_scheme_form'),
    '#theme' => 'flowplayer3_scheme_form',
  );
  $form['color'] += flowplayer3_scheme_form($form_state);
  
  // Player path
  $form['flowplayer3_files'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Player and plugin files'),
  );

  $form['flowplayer3_files']['flowplayer3_mediaplayer_file'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('flowplayer3_mediaplayer_file', FLOWPLAYER3_MEDIAPLAYER_FILE),
    '#title' => t('Player file'),
    '#description' => t('Specify the name of the player file - with FlowPlayer 3 this typically changes with each new release.'),
    '#size' => 30,
  );
  
  $form['flowplayer3_files']['flowplayer3_mediaplayer_stream_plugin'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('flowplayer3_mediaplayer_stream_plugin', FLOWPLAYER3_MEDIAPLAYER_STREAM_PLUGIN),
    '#title' => t('RTMP streaming plugin'),
    '#description' => t('Specify the name of the rtmp streaming plugin.'),
    '#size' => 30,
  );

  $form['flowplayer3_files']['flowplayer3_product_key'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('flowplayer3_product_key', ''),
    '#title' => t('Product key'),
    '#description' => t('Enter your product key if you are using the commercial version of FlowPlayer 3.'),
    '#size' => 30,
  );
  
  // Initialise tree from this point forward as want to store arrays
  $form[FLOWPLAYER3_MEDIAPLAYER]['#tree'] = TRUE;
 
  // Clip settings
  $form[FLOWPLAYER3_MEDIAPLAYER]['clip'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Overall clip properties'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['autoPlay'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['clip']['autoPlay'],
    '#title' => t('Auto play'),
    '#description' => t('Flag indicating whether the player should start playback immediately upon loading.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['autoBuffering'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['clip']['autoBuffering'],
    '#title' => t('Auto buffering'),
    '#description' => t('Flag indicating whether loading of clip into player\'s memory should begin straight away. '),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['scaling'] = array(
    '#type' => 'select',
    '#options' => $options['scaling'],
    '#default_value' => $saved_settings['clip']['scaling'],
    '#title' => t('Scaling'),
    '#description' => t('Specify how the clip should be scaled.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['start'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['start'],
    '#title' => t('Start'),
    '#description' => t('Specify start point for playback (only works with a streaming server). Streaming support not yet in place for SWF Tools.'),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['duration'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['duration'],
    '#title' => t('Duration'),
    '#description' => t('The time (in seconds) for which a video clip should be played until playback ceases.'),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['accelerated'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['clip']['accelerated'],
    '#title' => t('Acceleration'),
    '#description' => t('Flag indicating whether Flash 9 (and above) hardware-accelerated full screen mode should be used.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['bufferLength'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['bufferLength'],
    '#title' => t('Buffer length'),
    '#description' => t('The amount of video data (in seconds) which should be loaded into Flowplayer\'s memory in advance of playback commencing. '),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['provider'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['provider'],
    '#title' => t('Provider'),
    '#description' => t('Not sure if this will be support in this module. Need to investigate.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['fadeInSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['fadeInSpeed'],
    '#title' => t('Fade in speed'),
    '#description' => t('Time in milliseconds to fade from zero to full opacity upon commencement of video playback.'),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['fadeOutSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['fadeOutSpeed'],
    '#title' => t('Fade out speed'),
    '#description' => t('Time in milliseconds to fade from full to zero opacity upon completion of video playback.'),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['linkUrl'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['linkUrl'],
    '#title' => t('Link url'),
    '#description' => t('The URL to direct users to when clicking the video screen.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['linkWindow'] = array(
    '#type' => 'select',
    '#options' => $options['linkWindow'],
    '#default_value' => $saved_settings['clip']['linkWindow'],
    '#title' => t('Link window'),
    '#description' => t('Setting which defines where URL defined by linkUrl property is opened.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['live'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['clip']['live'],
    '#title' => t('Live'),
    '#description' => t('RTMP streaming servers support live streaming, which means that it is possible to setup a video camera or other live video source to stream live video data to Flowplayer. If you have an RTMP server which is providing a live video stream, you should set this property to true. Streaming support not yet in place for SWF Tools.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['clip']['cuePointMultiplier'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['cuePointMultiplier'],
    '#title' => t('Cue point multiplier'),
    '#description' => t('The times of embedded cuepoints are multiplied by this value before being used. Some encoding tools embed cuepoints in seconds but Flowplayer processes cuepoints in milliseconds. Note that the times are also rounded to the nearest 100 milliseconds. For example, if a file has a cuepoint at 5.535 seconds, the cuepoint is fired at 5500 milliseconds (assuming the default multiplier value of 1000).'),
    '#size' => 8,
  );

  // Control bar settings
  $form[FLOWPLAYER3_MEDIAPLAYER]['controls'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Controlbar properties'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['backgroundGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['backgroundGradient'],
    '#title' => t('Background gradient'),
    '#description' => t('Gradient setting for the controlbar background.'),
  );
  
  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['progressGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['progressGradient'],
    '#title' => t('Progress gradient'),
    '#description' => t('Gradient setting for the progress bar.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['bufferGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['bufferGradient'],
    '#title' => t('Buffer gradient'),
    '#description' => t('Gradient setting for the buffer.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['sliderGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['sliderGradient'],
    '#title' => t('Slider gradient'),
    '#description' => t('Gradient setting for the sliders.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['autoHide'] = array(
    '#type' => 'select',
    '#options' => $options['autoHide'],
    '#default_value' => $saved_settings['controls']['autoHide'],
    '#title' => t('Hide control bar'),
    '#description' => t('Specifies whether the controlbar should be hidden when the user is not actively using the player.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['play'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['play'],
    '#title' => t('Play button'),
    '#description' => t('Should the play/pause button be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['volume'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['volume'],
    '#title' => t('Volume button'),
    '#description' => t('Should the volume control be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['mute'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['mute'],
    '#title' => t('Mute button'),
    '#description' => t('Should the mute button be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['time'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['time'],
    '#title' => t('Time display'),
    '#description' => t('Should the time display be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['stop'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['stop'],
    '#title' => t('Stop button'),
    '#description' => t('Should the stop button be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['playlist'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['playlist'],
    '#title' => t('Playlist buttons'),
    '#description' => t('Should the playlist buttons be visible. These buttons will allow navigation through the playlist entries that have been configured for the player. These buttons are always hidden if there are less than two entries in the playlist.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['fullscreen'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['fullscreen'],
    '#title' => t('Fullscreen button'),
    '#description' => t('Should the fullscreen button be visible?'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['controls']['scrubber'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['scrubber'],
    '#title' => t('Scrubber'),
    '#description' => t('The scrubber is a well known nickname for the timeline/playhead combination. This specifies whether it should be visible.'),
  );

  // Canvas settings
  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Canvas properties'),
  );
  
  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
    '#size' => 8,
  );
  
  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
    '#size' => 8,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['backgroundImage'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['backgroundImage'],
    '#title' => t('Background image'),
    '#description' => t('The absolute or relative path to the image that should be used as the background to this plugin. Supported formats are GIF, JPEG and PNG. The syntax is similar to CSS in that you must enclose your path inside a url() wrapper.'),
    '#size' => 24,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['backgroundRepeat'] = array(
    '#type' => 'select',
    '#options' => $options['backgroundRepeat'],
    '#default_value' => $saved_settings['canvas']['backgroundRepeat'],
    '#title' => t('Background repeat'),
    '#description' => t('Default is "repeat", which makes the background image repeat both horizontally and vertically. "no-repeat" displays the background image only once from the top left-hand corner.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['backgroundGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['canvas']['backgroundGradient'],
    '#title' => t('Background gradient'),
    '#description' => t('Gradient setting for the canvas.'),
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['border'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['border'],
    '#title' => t('Border'),
    '#description' => t('Draws a border around a plugin\'s edges. The syntax follows the CSS standard: width style color. For example: "1px solid #cccccc". The only supported style currently is "solid", but the width and colour can be set to any valid value.'),
    '#size' => 24,
  );

  $form[FLOWPLAYER3_MEDIAPLAYER]['canvas']['borderRadius'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['borderRadius'],
    '#title' => t('Border radius'),
    '#description' => t('Specifies the amount of rounding for each corner. Larger values mean more rounding.'),
    '#size' => 8,
  );

  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'flowplayer3_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Options used to populate the select elements of the form above
 * Collect them here to make them easier to find and adjust!
 */
function _flowplayer3_options() {
  $options['bool'] = array('true' => 'true', 'false' => 'false');
  $options['linkWindow'] = array('_blank' => '_blank', '_parent' => '_parent', '_self' => '_self', '_top' => '_top');
  $options['scaling'] = array('fit' => 'fit', 'half' => 'half', 'orig' => 'orig', 'scale' => 'scale');
  $options['gradient'] = array('none' => 'none', 'low' => 'low', 'medium' => 'medium', 'high' => 'high');
  $options['autoHide'] = array('never' => 'never', 'always' => 'always', 'fullscreen' => 'fullscreen');
  $options['backgroundRepeat'] = array('no-repeat' => 'no-repeat', 'repeat' => 'repeat');
  return $options;
}


/**
 * Retrieve the color scheme information for FlowPlayer3 styling.
 * 
 * @return
 *   An array of data defining color information and names for each preset style.  
 */
function flowplayer3_get_info() {

  // Cache $info
  static $info;
  
  // If $info is populated, return it
  if (isset($info)) {
    return $info;
  }
  
  // Gather $info
  $path = drupal_get_path('module', 'flowplayer3');
  $file = $path . '/flowplayer3.colorschemes.inc';
  include $file;
  return $info;
}


/**
 * Helper function to retrieve the color palette for a particular style.
 * 
 * @param $default
 *   Optional parameter (default false). If false or omitted returns the
 *   current palette, if true returns the default palette.
 * @return
 *   An array of key/value pairs - the key defines the componenent and the
 *   value defines the color.
 */
function flowplayer3_get_palette($default = false) {

  // Define palette properties
  $fields = array(
    'backgroundColor',
    'controlbarbackgroundColor',
    'timeColor',
    'durationColor',
    'progressColor',
    'bufferColor',
    'sliderColor',
    'buttonColor',
    'buttonOverColor',
  );

  // Get the theme information
  $info = flowplayer3_get_info();

  // Get the keys (strings of colors) from the available schemes
  $keys = array_keys($info['schemes']);
  
  // Exploded the first (default) string in an array
  foreach (explode(',', array_shift($keys)) as $k => $scheme) {
    // Build a palette
    $palette[$fields[$k]] = $scheme;
  }
    
  // If default is required, return it, otherwise load palette variable
  return $default ? $palette : variable_get('flowplayer3_palette', $palette);
}


/**
 * Helper function to produce the color scheme form for the flowplayer
 */
function flowplayer3_scheme_form(&$form_state) {
  
  // Get path to the flowplayer3 module
  $base = drupal_get_path('module', 'flowplayer3');

  // Add Farbtastic color picker
  drupal_add_css('misc/farbtastic/farbtastic.css');
  drupal_add_js('misc/farbtastic/farbtastic.js');

  // Add custom CSS/JS
  drupal_add_css($base . '/flowplayer3.colorpicker.css');
  drupal_add_js($base . '/flowplayer3.colorpicker.js');
  drupal_add_js(array('color' => array(
    'reference' => flowplayer3_get_palette(true)
  )), 'setting');

  // Get info about the current theme color scheme
  $info = flowplayer3_get_info();
  
  // See if we're using a predefined scheme
  // The variable is empty if using the default, or an array of key/value pairs otherwise
  $current = implode(',', variable_get('flowplayer3_palette', array()));

  // Note: we use the original theme when the default scheme is chosen.
  $current = isset($info['schemes'][$current]) ? $current : ($current == '' ? reset($info['schemes']) : '');

  // Add custom to scheme selector options
  $info['schemes'][''] = t('Custom');
  
  // Add scheme selector to form (the value is a comma separated string of hex colors)
  $form['flowplayer3_scheme'] = array(
    '#type' => 'select',
    '#title' => t('Color set'),
    '#options' => $info['schemes'],
    '#default_value' => $current,
  );

  // Get current palette as an array
  $palette = flowplayer3_get_palette();
  
  // Build an array of titles to be used for each palette element
  $names = array(
    'backgroundColor' => array(
      '#title' => t('Background color'),
    ),
    'controlbarbackgroundColor' => array(
      '#title' => t('Control bar background color'),
    ),
    'timeColor' => array(
      '#title' => t('Elapsed time font color'),
    ),
    'durationColor' => array(
      '#title' => t('Total time font color'),
    ),
    'progressColor' => array(
      '#title' => t('Progress bar color'),
    ),
    'bufferColor' => array(
      '#title' => t('Buffer color'),
    ),
    'sliderColor' => array(
      '#title' => t('Slider color'),
    ),
    'buttonColor' => array(
      '#title' => t('Button color'),
    ),
    'buttonOverColor' => array(
      '#title' => t('Button over color'),
    ),
  );
  
  // Form elements to be part of a tree
  $form['flowplayer3_palette']['#tree'] = true;
  
  // Cycle through each palette element
  foreach ($palette as $name => $value) {
    $form['flowplayer3_palette'][$name] = array(
      '#type' => 'textfield',
      '#title' => $names[$name]['#title'],
      '#default_value' => $value,
      '#size' => 8,
    );
  }

  // Return the form
  return $form;
}


/**
 * Theme the FlowPlayer3 color settings for the admin form.
 */
function theme_flowplayer3_scheme_form($form) {

  $output = '';

  // Wrapper
  $output .= '<div class="color-form clear-block">';

  // Color schemes
  $output .= drupal_render($form['flowplayer3_scheme']);

  // Palette
  $output .= '<div id="palette" class="clear-block">';
  foreach (element_children($form['flowplayer3_palette']) as $name) {
    $output .= drupal_render($form['flowplayer3_palette'][$name]);
  }
  $output .= '</div>';
  
  // Close wrapper
  $output .= '</div>';

  return $output;
}


/**
 * Flush all caches when new FlowPlayer3 settings are stored.
 */
function flowplayer3_admin_settings_submit($form, &$form_state) {

  // Flush all caches so new players appear
  drupal_flush_all_caches();
  
}
