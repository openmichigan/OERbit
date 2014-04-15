;(function($) {

  Drupal.behaviors.custom_search = function (context) {

    if (!Drupal.settings.custom_search.solr) {
      // Check if the search box is not empty on submit
      $('form.search-form', context).submit(function(){
        var box = $(this).find('input.custom-search-box');
        if (box.val() != undefined && (box.val() == '' || box.val() == $(this).find('input.default-text').val())) {
          $(this).find('input.custom-search-box').addClass('error');
          return false;
        }
        // If basic search is hidden, copy or value to the keys
        if ($(this).find('#edit-keys').parents('div.element-invisible').attr('class') == 'element-invisible') {
          $(this).find('#edit-keys').val($(this).find('#edit-or').val());
          $(this).find('#edit-or').val('');
        }
        return true;
      });
    }

    // Search from target
    $('form.search-form').attr('target', Drupal.settings.custom_search.form_target);

    // Clear default text on focus, and put it back on blur. Also displays Popup.
    $('input.custom-search-box', context)
      .blur(function(e){
        var $this = $(this);
        var $parentForm = $this.parents('form');
        if ($this.val() == '') {
          $this.addClass('custom-search-default-value');
          $this.val($parentForm.find('input.default-text').val());
        }
      })
      .bind('click focus', function(e){
        var $this = $(this);
        var $parentForm = $this.parents('form');
        if ($this.val() == $parentForm.find('input.default-text').val()) $this.val('');
        $this.removeClass('custom-search-default-value');
        // check if there's something in the popup and displays it
        var popup = $parentForm.find('fieldset.custom_search-popup');
        if (popup.find('input,select').length && !popup.hasClass('opened')) popup.fadeIn().addClass('opened');
        e.stopPropagation();
      }
    );
    $(document).bind('click focus', function(){
      $('fieldset.custom_search-popup').hide().removeClass('opened');
    });

    // Handle checkboxes
    $('.custom-search-selector input:checkbox', context).each(function(){
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
        for (var i=0; i<types.length; i++) {
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
        for (var i=0; i<terms.length; i++) {
          $('.search-form option[value='+terms[i]+']').attr('selected', true);
        }
      }
    }

    var popup = $('fieldset.custom_search-popup:not(.custom_search-processed)', context).addClass("custom_search-processed");
    popup.click(function(e){
      e.stopPropagation();
    })
    popup.append('<a class="custom_search-popup-close" href="#">' + Drupal.t('Close') + '</a>');
    $('a.custom_search-popup-close').click(function(e){
      $('fieldset.custom_search-popup.opened').hide().removeClass('opened');
      e.preventDefault();
    });

  }

}(jQuery));
