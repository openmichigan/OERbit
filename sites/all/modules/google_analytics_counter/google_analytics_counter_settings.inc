<?php

function google_analytics_counter_admin() {

  $form['google_analytics_counter_api_refresh'] = array(
      '#type' => 'textfield',
      '#title' => t('Period of fresh data retrieval from GA API'),
      '#default_value' => variable_get('google_analytics_counter_api_refresh', '6'),
      '#size' => 3,
      '#maxlength' => 3,
      '#description' => t('The number of Google Analytics API requests may not exceed daily <a href="http://code.google.com/apis/analytics/docs/gdata/gdataDeveloperGuide.html#quota" target="_blank">quotas</a> per website (not per Google Account). During the period you set here Drupal will deliver cached (or extrapolated) values. Recommended value: 6 (<u>hours</u>).'),
  );

  $form['google_analytics_counter_extrapolation'] = array(
      '#type' => 'checkbox',
      '#title' => t('Extrapolate current page view count'),
      '#default_value' => variable_get('google_analytics_counter_extrapolation', '1'),
      //'#options' => array(0,1),
      '#description' => t("In between the live API requests, values are served from cache. Check this if you want to increase the confirmed count by an expected value based on the average of all page views from the past. Recommended."),
  );

  $form['google_analytics_counter_api_dayquota'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum GA API requests per day'),
      '#default_value' => variable_get('google_analytics_counter_api_dayquota', '10000'),
      '#size' => 9,
      '#maxlength' => 9,
      '#description' => t('This is simply the daily limit of requests per website set by Google Analytics API. You don\'t need to change this value until Google relaxes their quota policy. Current value: 10000. It is reasonable to expect that Google will increase this low number sooner rather than later, so watch the <a href="http://code.google.com/apis/analytics/docs/gdata/gdataDeveloperGuide.html#quota">quota</a> page for changes.'),
  );

  $form['google_analytics_counter_concurrency'] = array(
      '#type' => 'textfield',
      '#title' => t('Concurrent GA API request buffer period'),
      '#default_value' => variable_get('google_analytics_counter_concurrency', '1'),
      '#size' => 3,
      '#maxlength' => 3,
      '#description' => t('Google Analytics API should not be queried too frequently (see <a href="https://developers.google.com/analytics/devguides/reporting/core/v3/#quota_policy" target="_blank">current quotas</a>). During this period Drupal will refrain from querying the API. It acts as a buffer guarding against simultaneous API requests (e.g. if you clear caches and reload a lot of pages at once). The value here should not be less than 1 (<u>second</u>).'),
  );

  $form['google_analytics_counter_ajax_refresh'] = array(
      '#type' => 'textfield',
      '#title' => t('Period of the counter value AJAX refresh'),
      '#default_value' => variable_get('google_analytics_counter_ajax_refresh', ''),
      '#size' => 6,
      '#maxlength' => 6,
      '#description' => t("After initial display, the counter value can be refreshed using AJAX calls directly on the web page. Set the delay, in seconds, of this refresh. Note that too frequent refresh may overload your server. If you want to use the automatic refresh, be careful about values lower than 60 (<u>seconds</u>). To disable the refresh, set an empty value (or set it to 0)."),
  );

  $form['google_analytics_counter_update_node_counter'] = array(
      '#type' => 'checkbox',
      '#title' => t('Update Drupal node counter'),
      '#default_value' => variable_get('google_analytics_counter_update_node_counter', '0'),
      //'#options' => array(0,1),
      '#description' => t("Replaces Drupal's own count of node (and only node!) page views by the counts fetched from Google Analytics. Note that this count is not extrapolated or refreshed automatically. However, it is particularly useful if you need to show / sort by the counter values in Views. Additionally, if you have the core Drupal module 'Statistics' enabled, the page views will on node pages (usually at the bottom of the content area)."),
  );

  $form['google_analytics_counter_debug'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display debug info in tooltip'),
      '#default_value' => GOOGLE_ANALYTICS_COUNTER_DEBUG,
      //'#options' => array(0,1),
      '#description' => t("Check this if you want to display detail information about the data. Useful for debugging."),
  );

  return system_settings_form($form);
}
