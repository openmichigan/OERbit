<?php

/**
 * @file
 *
 * Implementation of Embedded Media Field hooks.
 */
define('EMVIDEO_SLIDESHARE_MAIN_URL', 'http://slideshare.net/');
define('EMVIDEO_SLIDESHARE_XML', 'http://www.slideshare.net/api/2/');
define('EMVIDEO_SLIDESHARE_DOMAIN_DEFAULT', 'net');

/**
 * Implementation of hook_<provider>_info()
 */
function emvideo_slideshare_info() {
  return array(
    'provider' => 'slideshare',
    'name' => t('SlideShare'),
    'url' => EMVIDEO_SLIDESHARE_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from <a href="@slideshare" target="_blank">SlideShare</a>.', array('@slideshare' => EMVIDEO_SLIDESHARE_MAIN_URL )),
    'supported_features' => array(
      array(t('Autoplay'), t('No'), ''),
      array(t('RSS Attachment'), t('No'), ''),
      array(t('Thumbnails'), t('Yes'), ''),
    ),
  );
}

/**
 * Implementation of hook_<provider>_settings()
 */
function emvideo_slideshare_settings() {
  $form = array();
  $form['emvideo_slideshare_api_key'] = array(
    '#type' => 'textfield', '#title' => t('API Key'),
    '#default_value' => variable_get('emvideo_slideshare_api_key', ''),
    '#description' => t('Your SlideShare API Key. To obtain one, apply at <a href="http://www.slideshare.net/developers/applyforapi" target="_blank">http://www.slideshare.net/applyforapi</a>.')
  );
  $form['emvideo_slideshare_shared_secret'] = array(
    '#type' => 'textfield', '#title' => t('Shared Secret'),
    '#default_value' => variable_get('emvideo_slideshare_shared_secret', ''),
    '#description' => t('Your SlideShare Shared Secret. To obtain one, apply at <a href="http://www.slideshare.net/developers/applyforapi" target="_blank">http://www.slideshare.net/applyforapi</a>.')
  );

  //  Username and password for future development.
//  $form['emvideo_slideshare_username'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Username'),
//    '#default_value' => variable_get('emvideo_slideshare_username', ''),
//    '#description' => t('Your SlideShare username. Only required for advanced requests.')
//  );
//  $form['emvideo_slideshare_password'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Password'),
//    '#default_value' => variable_get('emvideo_slideshare_password', ''),
//    '#description' => t('Your SlideShare password. Only required for advanced requests.')
//  );
  return $form;
}

/**
 * Parser function for submissions via Emvideo.
 *
 * @param $embed
 *   A URL or WordPress embed code for the slideshow to embed.
 * @return
 *   The slideshow_id of the SlideShare presentation.
 *
 * @todo
 *   Refine the regex used to match URLs so it can pull a URL out of the
 *   regular embed code, or write a condition to pull the slideshow id out
 *   of the embed code.
 */
function emvideo_slideshare_extract($embed) {
  $matches = NULL;
  // WordPress embed code
  if (preg_match('/^\[slideshare id=(\d+)&.+\]/', trim($embed), $matches)) {
    return $matches[1];
  }
  // regular embed code
  if (preg_match('/<object .+http:\/\/static\.slidesharecdn\.com.+<\/object>/', $embed, $matches)) {
    return $matches[0];
  }
  // URL parsing
  elseif (preg_match('/^http:\/\/www.slideshare.net[^#?]+/', trim($embed), $matches)) {

    // Very inefficient - getting the slideshow id from the url
    $api_key = variable_get('emvideo_slideshare_api_key', '');
    $shared_secret = variable_get('emvideo_slideshare_shared_secret', '');

    if ($api_key && $shared_secret) {
      $ts = time();
      $hash = sha1($shared_secret . $ts);
      $args['api_key'] = $api_key;
      $args['ts'] = $ts;
      $args['hash'] = $hash;
      $args['slideshow_url'] = $matches[0];
      $cacheable = FALSE;

      $result = module_invoke('emfield', 'request_xml', 'slideshare', EMVIDEO_SLIDESHARE_XML .'get_slideshow', $args, $cacheable);
      return $result['SLIDESHOW']['ID'][0];
    }
    else {
      drupal_set_message(t('The SlideShare API keys have not been set up, so the presentation cannot be saved. !link',
      array( '!link' => l('Configure the SlideShare settings now.',  'admin/content/emfield/emvideo' ) )),
      'warning');
    }
  }
  else {
    return FALSE;
  }
}

/**
 * Implementation of hook_<provider>_request()
 */
function emvideo_slideshare_request($embed, $cacheable = TRUE) {
  /**
   * If we save the wrong data, or change the way we store the data -- which is
   * possible since we store the id and not the full URL -- we can always
   * reload the slideshow by running the function emfield_reload($nid)
   */
  $api_key = variable_get('emvideo_slideshare_api_key', '');
  $shared_secret = variable_get('emvideo_slideshare_shared_secret', '');

  if ($api_key && $shared_secret) {
    $ts = time();
    $hash = sha1($shared_secret . $ts);
//    $username = variable_get('emvideo_slideshare_username', '');
//    $password = variable_get('emvideo_slideshare_password', '');
    watchdog('slideshare', 'embed contains ' . $embed, array(), WATCHDOG_NOTICE);
    $args['api_key'] = $api_key;
    $args['ts'] = $ts;
    $args['hash'] = $hash;
    $args['slideshow_id'] = $embed;
    $cacheable = FALSE;

    $result = module_invoke('emfield', 'request_xml', 'slideshare', EMVIDEO_SLIDESHARE_XML .'get_slideshow', $args, $cacheable);
    return $result;
  }
  else {
    watchdog('slideshare', 'The SlideShare API keys have not been set up. <a href="@url">Configure the SlideShare settings now.</a>', array('@url' => url('admin/content/emfield/emvideo')), WATCHDOG_WARNING);
    return array();
  }
}

/**
 * Implementation of hook_<provider>_video_link()
 */
function emvideo_slideshare_video_link($video_code) {
  //  return 'http://video.slideshare.'. variable_get('emvideo_slideshare_domain', EMVIDEO_SLIDESHARE_DOMAIN_DEFAULT) .'/videoplay?docid='. $video_code;
  return NULL;
}

/**
 * Implementation of hook_<provider>_data()
 */
function emvideo_slideshare_data($field, $item) {
  $result = emvideo_slideshare_request($item['value']);
  return $result['SLIDESHOW'];
}

/**
 * Implementation of hook_<provider>_thumbnail()
 */
function emvideo_slideshare_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return $item['data']['THUMBNAILURL'][0];
}

/**
 * Implementation of hook_<provider>_video()
 */
function emvideo_slideshare_video($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('slideshare_flash', $embed, $width, $height, $field, $item, $node, $autoplay);
  return $output;
}

/**
 * Implementation of hook_<provider>_preview()
 */
function emvideo_slideshare_preview($embed, $width, $height, $field, $item, $node, $autoplay) {
  $output = theme('slideshare_flash', $embed, $width, $height, $field, $item, $node, $autoplay);
  return $output;
}

/**
 *  Implement hook_emvideo_PROVIDER_content_generate().
 */
function emvideo_slideshare_content_generate() {
  return array(
    'http://www.slideshare.net/merlinofchaos/the-chaos-tools-suite',
    'http://www.slideshare.net/eaton/drupal-deployment-presentation',
    'http://www.slideshare.net/laurascott/grok-drupal-7-theming-2011-feb-update',
    'http://www.slideshare.net/mortendk1/developer-vs-designer',
    'http://www.slideshare.net/fourkitchens/dont-design-websites-design-web-systems-badcamp-2011',
    'http://www.slideshare.net/timoreilly/drupalcon-keynote-open-source-and-open-data-in-the-age-of-the-cloud',
    'http://www.slideshare.net/volacci/how-to-build-a-successful-drupal-business',
    'http://www.slideshare.net/walkah/why-i-hate-drupal',
    'http://www.slideshare.net/davexoxide/drupal-blocks-vs-context-vs-panels',
    'http://www.slideshare.net/exove/exove-drupalcamp-kalle20100527',
    'http://www.slideshare.net/ultimike/45-modules-in-45-minutes-the-best-modules-youre-not-using',
  );
}
