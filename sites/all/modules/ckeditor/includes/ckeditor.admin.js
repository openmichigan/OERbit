/*
Copyright (c) 2003-2012, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/
$(document).ready(function() {
  if ($('#edit-uicolor-textarea').length) {
    if (typeof(CKEDITOR) == "undefined")
        return;

    CKEDITOR.on( 'dialogDefinition', function( ev )
    {
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;

        if ( dialogName == 'uicolor' )
        {
        // Get a reference to the configBox and hide it (cannot be removed).
        var configBox = dialogDefinition.getContents( 'tab1' ).get( 'configBox' );
        configBox.style = 'display:none';
        }
    });
    $('#edit-uicolor-textarea').show();

    Drupal.ckeditorUiColorOnChange = function() {
        var color = CKEDITOR.instances["edit-uicolor-textarea"].getUiColor();
        $("#edit-uicolor").val("custom");
        if (typeof(color) != "undefined") {
        if (color == "default"){
            $("#edit-uicolor").val("default");
        }
        $('#edit-uicolor-user').val(color);
        }
    };

    CKEDITOR.replace("edit-uicolor-textarea",
    {
        extraPlugins : 'uicolor',
        height: 60,
        uiColor: $('#edit-uicolor-user').val() || '#D3D3D3',
        width: 400,
        toolbar : [[ 'Bold', 'Italic', '-', 'NumberedList', 'BulletedList'],[ 'UIColor' ]],
        on:
        {
        focus : Drupal.ckeditorUiColorOnChange,
        blur : Drupal.ckeditorUiColorOnChange
        }
    });

    $("#edit-uicolor").bind("change", function() {
        if (typeof(Drupal.settings.ckeditor_uicolor) != "undefined") {
        CKEDITOR.instances["edit-uicolor-textarea"].setUiColor(Drupal.settings.ckeditor_uicolor[$(this).val()]);
        }
        if ($(this).val() != "custom") {
        $('#edit-uicolor-user').val("");
        }
        else {
        var color = CKEDITOR.instances["edit-uicolor-textarea"].getUiColor();
        if (typeof(color) != "undefined") {
            $('#edit-uicolor-user').val(color);
        }
        }
    });
  }
  $(".cke_load_toolbar").click(function() {
    var buttons = eval('Drupal.settings.'+$(this).attr("id"));
    var text = "[\n";
    for(i in buttons) {
      if (typeof buttons[i] == 'string'){
        text = text + "    '/',\n";
      }
      else {
        text = text + "    [";
        max = buttons[i].length - 1;
        rows = buttons.length - 1;
        for (j in buttons[i]) {
          if (j < max){
            text = text + "'" + buttons[i][j] + "',";
          } else {
            text = text + "'" + buttons[i][j] + "'";
          }
        }
        if (i < rows){
          text = text + "],\n";
        } else {
          text = text + "]\n";
        }
      }
    }

    text = text + "]";
    text = text.replace(/\['\/'\]/g,"'/'");
    $("#edit-toolbar").attr('value',text);
    if (Drupal.settings.ckeditor_toolbar_wizard == 't'){
      Drupal.ckeditorToolbarReload();
    }
    return false;
  });

  if (Drupal.settings.ckeditor_toolbar_wizard == 'f'){
    $("form#ckeditor-admin-profile-form textarea#edit-toolbar, form#ckeditor-admin-profile-form #edit-toolbar + .grippie, form#ckeditor-admin-global-profile-form textarea#edit-toolbar, form#ckeditor-admin-global-profile-form #edit-toolbar + .grippie").show();
  }
});
