Drupal.behaviors.beautytips = function() {
  jQuery.bt.defaults.closeWhenOthersOpen = true;
  // Set default css settings as chosen in BeautyTips settings
  if ( Drupal.settings.beautytips_defaults['css_list'].length > 0) {
    for (var j = 0; j < Drupal.settings.beautytips_defaults['css_list'].length; j++) {
      jQuery.bt.defaults.cssStyles[Drupal.settings.beautytips_defaults['css_list'][0]] = Drupal.settings.beautytips_defaults['cssStyles'][Drupal.settings.beautytips_defaults['css_list'][0]];
    }
  }
  // Defaults based on which style was chosen in BeautyTips Settings
  if (Drupal.settings.beautytips_defaults['list'].length > 0) {
    for (var i = 0; i < Drupal.settings.beautytips_defaults['list'].length; i++) {
      jQuery.bt.defaults[Drupal.settings.beautytips_defaults['list'][i]] = Drupal.settings.beautytips_defaults[Drupal.settings.beautytips_defaults['list'][i]];
    }
  }
  for (var key in Drupal.settings.beautytips) {
    if (!Drupal.settings.beautytips[key]['additionalJavascript']) {
      // Build array of options that were passed to beautytips_add_beautyips
      var bt_options = new Array();
      if (Drupal.settings.beautytips[key]['list']) {
        for ( var k = 0; k < Drupal.settings.beautytips[key]['list'].length; k++) {
          bt_options[Drupal.settings.beautytips[key]['list'][k]] = Drupal.settings.beautytips[key][Drupal.settings.beautytips[key]['list'][k]];
        }
      }
      if (Drupal.settings.beautytips[key]['text']) {
        $(Drupal.settings.beautytips[key]['area']).each(function() {
          $(this).bt(Drupal.settings.beautytips[key]['text'], bt_options);
        });
      }
      else if (Drupal.settings.beautytips[key]['ajaxPath']) {
        $(Drupal.settings.beautytips[key]['area']).each(function() {
          $(this).bt(bt_options);
        });
      }
      else {
        $(Drupal.settings.beautytips[key]['area']).each(function() {
          $(this).bt(bt_options);
        });
      }
      bt_options.length=0;
    }
  }
}