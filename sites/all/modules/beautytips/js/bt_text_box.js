Drupal.behaviors.bt_text_box = function() {
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
    }
  }
  var selector = ['bt_text_field', 'bt_text_area'];
  for (var i = 0; i < selector.length; i++) {
    $(Drupal.settings.beautytips[selector[i]]['area']).each(function() {
      var description = $(this).next('.description').hide().html();
      if (description) {
        $(this).bt(description, {
          trigger: Drupal.settings.beautytips[selector[i]]['trigger'],
          positions: Drupal.settings.beautytips[selector[i]]['positions'],
          width: Drupal.settings.beautytips[selector[i]]['width']
        });
      }
    });
  }  
}