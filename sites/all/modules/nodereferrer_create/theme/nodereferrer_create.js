$(document).ready(function() {
    var nodereferrer_create_menu_open = false;
    
    // Click on the icon to open drop down
    $('img.nodereferrer-create-down').click(function(event) {
        items = $(this).nextAll('div.nodereferrer-create-items');
        
        if (items.css('display') == 'none') {
          $('div.nodereferrer-create-items').hide();
          $(this).nextAll('div.nodereferrer-create-items').show();
          nodereferrer_create_menu_open = true;
          event.stopPropagation();
        }
    });
    
    // Click on title to open drop down
    $('div.nodereferrer-create-title').click(function(event) {
        items = $(this).nextAll('div.nodereferrer-create-items');
        
        if (items.css('display') == 'none') {
          $('div.nodereferrer-create-items').hide();
          $(this).nextAll('div.nodereferrer-create-items').show();
          nodereferrer_create_menu_open = true;
          event.stopPropagation();
        }
    });
    
    // Don't propagate click on menu items
    $('div.nodereferrer-create-items').click(function(event) {
        event.stopPropagation();
    });
    
    // Handle clicks on body to close drop downs
    $('body').click(function(event) {
        if (nodereferrer_create_menu_open) {
          event.stopPropagation();
          event.preventDefault();
          
          $('div.nodereferrer-create-items').hide();
          nodereferrer_create_menu_open = false;
        }
    });
    
    $('div.nodereferrer-create-items').css('position', 'absolute').toggle();
    $('ul.nodereferrer-create-top-level > li').css('float', 'left');
});
