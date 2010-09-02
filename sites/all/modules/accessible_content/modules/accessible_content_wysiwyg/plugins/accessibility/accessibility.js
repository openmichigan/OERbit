// $Id: 

Drupal.wysiwyg.plugins['accessibility'] = {

  /**
   * Return whether the passed node belongs to this plugin.
   */
  isNode: function(node) {

  },

  /**
   * Execute the button.
   */
  invoke: function(data, settings, instanceId) {
    if (data.format == 'html') {
      if(!data.content) {
      	alert('You must first select the text you wish to check.');
      }
      else {
        $.post(Drupal.settings.basePath + 'accessibility/check',
          { html : data.content, guideline : nodeGuideline},
          function(data) {
            accessWin = window.open('', 'accessWin',  '');
            accessWin.document.writeln(data);
            accessWin.document.close();
        });
      }
    }

  },

  attach: function(content, settings, instanceId) {
    return content;
  },

  detach: function(content, settings, instanceId) {
    return content;
  },

};
