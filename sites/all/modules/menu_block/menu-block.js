// $Id: menu-block.js,v 1.2 2008/12/01 09:56:56 johnalbin Exp $

$(document).ready( function() {
  $('#edit-parent')
    .html(Drupal.settings.menu_block.parent_options[Drupal.settings.menu_block.menus_default])
    .val(Drupal.settings.menu_block.parent_default)
    .before(Drupal.settings.menu_block.menus);
  $('#edit-parent-menu').change( function() {
    $('#edit-parent')
      .html(Drupal.settings.menu_block.parent_options[$('#edit-parent-menu').val()])
      .val(Drupal.settings.menu_block.parent_default);
  } );
  $('#edit-follow').change( function() {
    if ($('#edit-follow:checked').length) {
      $('#edit-follow-parent-wrapper').slideDown('slow');
    }
    else {
      $('#edit-follow-parent-wrapper').slideUp('slow');
    }
  } );
  if (!$('#edit-follow:checked').length) {
    $('#edit-follow-parent-wrapper').css('display', 'none');
  }
} );
