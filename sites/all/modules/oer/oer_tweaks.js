
Drupal.behaviors.userLogin = function () {
  $('#edit-name').focus();
}

//togg
Drupal.behaviors.BlockOerTweaks = function (context) {
  $('a#togg-link:not(.togg-processed)', context).addClass('togg-processed').each(function () {
    $(this).click(function() {
      var text = $(this).text();
      $(this).text(text == 'Hide search tools'? 'Show Search Tools' : 'Hide search tools');
      $("div#block-oer_tweaks-1").toggle(400);
      $("div#block-oer_tweaks-2").toggle(400);
      $("div#block-oer_tweaks-3").toggle(400);
      $("div#block-apachesolr-sort").toggle(400);
      return false;
    });
  });
};

