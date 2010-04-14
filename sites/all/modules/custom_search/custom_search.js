// $Id: custom_search.js,v 1.1.2.2 2010/03/17 16:13:42 jdanthinne Exp $

Drupal.behaviors.custom_search = function (context) {

  // Check if the search box is not empty on submit
  $('#search-block-form,#search-theme-form')
    .submit(function(){
      var box = $(this).find('input:text');
      if (box.val() == '' || box.val() == Drupal.settings.custom_search[$(this).attr('id') + "_default_value"]) {
        $(this).find('input:text').addClass('error');
        return false;
      }
      return true;
    }
  );

  // Clear default text on focus, and put it back on blur.
  $('#edit-search-block-form-1,#edit-search-theme-form-1')
    .blur(function(){
      if ($(this).val() == '') {
        $(this).addClass('custom-search-default-value');
        $(this).val(Drupal.settings.custom_search[$(this).parents('form').attr('id') + "_default_value"]);
      }
    })
    .focus(function(){
      if ($(this).val() == Drupal.settings.custom_search[$(this).parents('form').attr('id') + "_default_value"]) $(this).val('');
      $(this).removeClass('custom-search-default-value');
    }
  );

  // Handle checkboxes
  $('.custom-search-selector input:checkbox').each(function(){
    var el = $(this);
    if (el.val() == 'c-all') {
      el.change(function(){
        $(this).parents('.custom-search-selector').find('input:checkbox[value!=c-all]').attr('checked', false);
      });
    }
    else {
      if (el.val().substr(0,2) == 'c-') {
        el.change(function(){
          $('.custom-search-selector input:checkbox').each(function(){
            if ($(this).val().substr(0,2) == 'o-') $(this).attr('checked', false);
          });
          $(this).parents('.custom-search-selector').find('input:checkbox[value=c-all]').attr('checked', false);
        });
      } else {
        el.change(function(){
          $(this).parents('.custom-search-selector').find('input:checkbox[value!='+el.val()+']').attr('checked', false);
        });
      }
    }
  });

  // Reselect types and terms in advanced search
  var edit_keys = $('#edit-keys').val();
  if(edit_keys) {
    // types
    var pos = edit_keys.indexOf('type:');
    if (pos) {
      var pos2 = edit_keys.indexOf(' ',pos);
      if (pos2==-1) pos2 = edit_keys.length;
      var types = edit_keys.substring(pos+5,pos2);
      types = types.split(',');
      for (var i in types) {
        $('.search-form input:checkbox[value='+types[i]+']').attr('checked', true);
      }
    }
    // terms
    var pos = edit_keys.indexOf('category:');
    if (pos) {
      var pos2 = edit_keys.indexOf(' ',pos);
      if (pos2==-1) pos2 = edit_keys.length;
      var terms = edit_keys.substring(pos+9,pos2);
      terms = terms.split(',');
      for (var i in terms) {
        $('.search-form option[value='+terms[i]+']').attr('selected', true);
      }
    }
  }

}
