<?php
// $Id: swftools.admin.status.inc,v 1.5.2.4 2009/03/28 22:45:19 stuartgreenfield Exp $

// The following message is used several times during iteration loops, so define it once for efficiency
define('SWFTOOLS_STATUS_DESCRIPTION', t('The specified player no longer appears to be available. Check the <a href="@modules">modules page</a> to ensure that the necessary module is enabled, or choose a different player on the <a href="@handling">file handling</a> page.', array('@modules' => url('admin/build/modules'), '@handling' => url('admin/settings/swftools/handling'))));


/**
 * Generate a status report for SWF Tools methods / players / media defaults
 */
function swftools_status() {

  // Pick up definitions for severity levels
  include_once './includes/install.inc';

  // Begin html string to hold output
  $html = t('<p>The following tables show the status of SWF Tools and its supporting modules. This information can help to diagnose an installation that is not working correctly. Warnings indicate an issue that may prevent SWF Tools from performing as expected but are not necessarily an immediate problem. Errors show that there is an issue that will prevent SWF Tools from working.</p>');

  // Get embedding status report
  $html .= _swftools_status_embedding();

  // Get playback and player status report
  $html .= _swftools_status_players();
  
  // Get zlib status
  $html .= _swftools_zlib();

  // Return markup
  return $html;

}


/**
 * Generate a status report for embedding methods
 * Called from swftools_status() and returns markup
 */
function _swftools_status_embedding() {

  // Initialise requirements array
  $requirements = array();

  // Initialise an empty array in position zero - will need this later.
  $requirements[0] = array();

  // Get player directory
  $player_directory = swftools_get_player_path() .'/';

  // Get list of available embedding methods
  $methods = swftools_methods_available(SWFTOOLS_EMBED_METHOD);

  // Retrieve current embedding method and initialise flag to track if we find it later
  $current_method = variable_get(SWFTOOLS_EMBED_METHOD, SWFTOOLS_NOJAVASCRIPT);
  $method_found = FALSE;

  // Iterate through available methods
  if (count($methods)) {
    foreach ($methods AS $method => $info) {

      // If method name is the current method then we found it, and it is available
      if ($info['name'] == $current_method) {
        $current_method = $info['title'];
        $method_found = TRUE;
      }

      // If the method defines a shared file then check that it exists
      if ($info['shared_file']) {

        // If the file doesn't exist then indicate the shared file to be missing
        if (!file_exists($player_directory . $info['shared_file'])) {
          $requirements[] = array(
            'title'       => $info['title'],
            'value'       => t('Missing'),
            'severity'    => ($current_method == $info['title']) ? REQUIREMENT_ERROR : REQUIREMENT_WARNING,
            'description' => t('<a href="@url">Download</a> the required supporting file and upload it to %path.', array('@url' => $info['download'], '%path' => $player_directory . $info['shared_file'])),
          );

          // If the missing file relates to the current method set the default to a warning
          if ($current_method == $info['title']) {
            $requirements[0] = array(
              'severity' => REQUIREMENT_ERROR,
              'description' => t('The required supporting file is not available. See below for more information.'),
            );
          }
        }
        else {
          $requirements[] = array(
            'title'       => $info['title'],
            'value'       => t('OK'),
          );
        }
      }
    }
  }

  // If the specified embedding method was found then set the default entry to show ok
  if ($method_found) {
    $requirements[0] += array(
      'title'    => t('Default method'),
      'value'    => $current_method,
      'severity' => REQUIREMENT_OK,
    );
  }
  else {
    $requirements[0] += array(
      'title'    => t('Default method'),
      'value'    => $current_method,
      'severity' => REQUIREMENT_ERROR,
      'description' => t('This method no longer appears to be available. Check the <a href="@modules">modules page</a> to ensure that the necessary module is enabled, or choose a different embedding method on the <a href="@settings">embedding settings</a> page.', array('@modules' => url('admin/build/modules'), '@settings' => url('admin/settings/swftools/embed'))),
    );
  }

  // Construct output string
  $html = t('<h3>Embedding methods</h3>');
  $html .= t('<p>The current default and available methods are listed in the table below. A warning will be shown if the method is not ready for use, and an error will be shown if the method is not ready <em>and</em> it is currently set as the default embedding method. The default embedding method can be set on the <a href="@settings">embedding settings</a> page.</p>', array('@settings' => url('admin/settings/swftools/embed')));
  $html .= theme('status_report', $requirements);

  // Try to generate some test content
  $html .= _swftools_test_content($requirements[0]['severity'], $requirements[0]['value']);

  return $html;

}


/**
 * Generate a status report for the player modules and media defaults
 * Called from swftools_status() and returns markup
 */
function _swftools_status_players() {

  // Initialise requirements array for players and playback defaults
  $player_requirements = array();
  $playback_defaults = array();

  // Get player directory
  $player_directory = swftools_get_player_path() .'/';

  // Build an array of player methods
  $types = array(
    SWFTOOLS_FLV_DISPLAY => 'Single flv',
    SWFTOOLS_FLV_DISPLAY_LIST => 'List of flvs',
    SWFTOOLS_MP3_DISPLAY => 'Single mp3',
    SWFTOOLS_MP3_DISPLAY_LIST => 'List of mp3s',
    SWFTOOLS_MEDIA_DISPLAY_LIST => 'List of mixed media',
    SWFTOOLS_SWF_DISPLAY => 'Single swf',
    SWFTOOLS_IMAGE_DISPLAY_LIST => 'List of images',
  );

  // Iterate each method type
  foreach ($types as $type => $description) {

    // Obtain list of players that support the given method type
    $methods = swftools_methods_available($type);

    // Get the current default player for this type and store it in the player defaults array
    // To start with we assume it is missing, until we find the player module in a moment
    $playback_defaults[$type] = array(
      'title' => $types[$type],
      'value' => swftools_get_player($type),
      'description' => SWFTOOLS_STATUS_DESCRIPTION,
      'severity' => REQUIREMENT_ERROR,
    );

    // Reset 0 to text string none and clear warning - we assume playback of this type isn't required
    if (!$playback_defaults[$type]['value']) {
      $playback_defaults[$type]['value'] = t('None');
      $playback_defaults[$type]['severity'] = REQUIREMENT_OK;
      $playback_defaults[$type]['description'] = '';
    }

    // If methods were returned for this type
    if (count($methods)) {

      // Iterate through the available methods for this type
      foreach ($methods as $method => $player) {

        // Did we already process this player?
        if (!isset($player_requirements[$player['title']])) {

          // If this player file doesn't exist set a warning, otherwise set ok
          if (!file_exists($player_directory . $player['shared_file'])) {
            $player_requirements[$player['title']] = array(
              'title'    => $player['title'],
              'value'    => t('Missing'),
              'description' => t('<a href="@url">Download</a> the required supporting file and upload it to %path.', array('@url' => $player['download'], '%path' => $player_directory . $player['shared_file'])),
              'severity' => REQUIREMENT_WARNING,
            );
          }
          else {
            $player_requirements[$player['title']] = array(
              'title'    => $player['title'],
              'value'    => t('OK'),
              'severity' => REQUIREMENT_OK,
            );
          }
        }

        // Is the current default method for this media type the method we currently have?
        if ($playback_defaults[$type]['value'] == $method) {

          // If yes, set name of this player as the value
          $playback_defaults[$type]['value'] = $player['title'];

          // Set the rest of the data for this player according to the status of the player file
          if ($player_requirements[$player['title']]['severity'] == REQUIREMENT_OK) {
            $playback_defaults[$type]['severity'] = REQUIREMENT_OK;
            $playback_defaults[$type]['description'] = '';
          } 
          else {
            $playback_defaults[$type]['severity'] = REQUIREMENT_ERROR;
            $playback_defaults[$type]['description'] = $player_requirements[$player['title']]['description'];
            $player_requirements[$player['title']]['severity'] = REQUIREMENT_ERROR;
          }
        }
      }
    }
  }

  // Sort list of players by name, since we used their title as the key
  asort($player_requirements);

  // Generate the output string and return it
  $html = t('<h3>Playback defaults</h3>');
  $html .= t('<p>The table below shows the default methods that have been assigned to different types of media. An error indicates that a player has been specified but the supporting player file is not available, or the method cannot be found. Default playback methods can be configured on the <a href="@handling">file handling settings</a> page.</p>', array( '@handling' => url('admin/settings/swftools/handling')));
  $html .= theme('status_report', $playback_defaults);

  $html .= t('<h3>Players</h3>');
  $html .= t('<p>This table shows which media players are currently enabled and ready for use. A warning is shown if the required supporting file is not available, and an error is shown if the supporting file is not available <em>and</em> the method is currently set as a playback default for any media type.</p>');
  $html .= theme('status_report', $player_requirements);

  return $html;

}


function _swftools_test_content($severity, $method) {

  // Generate the output string and return it
  $html = t('<h3>Test content</h3>');

  if ($severity == REQUIREMENT_ERROR) {
    $html .= t('<p>SWF Tools cannot currently generate test content as the chosen embedding method is not available. Refer to the table above for assistance in fixing the problem.</p>');
  }
  else {
    // Build file path to the test file
    $file = url(drupal_get_path('module', 'swftools') .'/shared/swftools_test_file.swf', array('absolute' => TRUE));

    $html .= t('<p>SWF Tools is now trying to generate some flash content using the currrently configured embedding method (%current). If you can see an animation below then SWF Tools appears to be installed correctly.</p>', array('%current' => $method));
    $html .= swf($file, array('params' => array ('height' => 150, 'width' => 150)));
    $html .= t('<p> If the animation does not appear then check that your browser has the necessary Flash plug-in, and that JavaScript is enabled (if required). Also try clearing your browser\'s cache.</p>');
  }

  return $html;
}

/**
 * Check for presence of the zlib library
 * 
 * @return
 *   Markup string for inclusion in report
 */
function _swftools_zlib() {
  
  $has_zlib = extension_loaded('zlib');
  
  $requirements['swftools'] = array(
    'title' => t('Zlib library'),
    'description' => '',
    'value' => $has_zlib ? t('Enabled') : t('Not installed'),
    'severity' => $has_zlib ? REQUIREMENT_OK : REQUIREMENT_WARNING,
  );
  
  // Generate the output string and return it
  $html = t('<h3>Zlib library</h3>');
  $html .= t('<p>SWF Tools requires the <a href="@url">zlib library</a> in order to automatically determine the dimensions of compressed swf files. If this library is not installed then SWF Tools will work but you may have to specify the size of swf content when it is produced, otherwise the content may not appear in some browsers.</p>', array('@url' => 'http://www.php.net/zlib'));
  $html .= theme('status_report', $requirements);

  return $html;
  
}
