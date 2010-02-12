if (Drupal.jsEnabled) {
  $(document).ready(function() {
    // Beautytips examples shown on Beautytips settings page
    $('#edit-beautytips-styles-default').bt('This is the default style balloon.', {
      positions: ['right'],
      overlap: 0,
      centerPointY: .5,
      centerPointX: .5,
      fill: "rgb(255, 255, 102)", 
      strokeStyle: "#000",
      strokeWidth: 1, 
      spikeLength: 40, 
      spikeGirth: 10, 
      padding: 8, 
      cornerRadius: 10,
      shadow: false, 
      shadowBlur: 3, 
      cssStyles: {}
    });
    $('#edit-beautytips-styles-netflix').bt('This is the netflix style balloon.', {
      positions: ['right'],
      overlap: -8,
      centerPointY: .1,
      centerPointX: .5, 
      padding: 8, 
      spikeGirth: 10, 
      spikeLength: 50, 
      cornerRadius: 10, 
      fill: '#FFF', 
      strokeStyle: '#B9090B', 
      strokeWidth: 1,
      //shadow: true, 
      shadowBlur: 12, 
      cssStyles: {
        fontSize: '12px',
        fontFamily: 'arial,helvetica,sans-serif'
      }
    });
    $('#edit-beautytips-styles-facebook').bt('This is a facebook style balloon.', {
      positions: ['right'],
      overlap: 0,
      centerPointY: .5,
      centerPointX: .5,
      fill: '#F7F7F7', 
      strokeStyle: '#B7B7B7',
      strokeWidth: 1, 
      spikeLength: 40, 
      spikeGirth: 10, 
      padding: 8, 
      cornerRadius: 0,
      shadow: false, 
      shadowBlur: 3, 
      cssStyles: {
        fontFamily: '"lucida grande",tahoma,verdana,arial,sans-serif', 
        fontSize: '11px'
      }
    });
    $('#edit-beautytips-styles-transparent').bt('This balloon is transparent with big white text.', {
      positions: ['right'],
      overlap: 0,
      padding: 20,
      width: 120,
      cornerRadius: 10,
      centerPointY: .5,
      centerPointX: .5,
      spikeLength: 40,
      spikeGirth: 20,
      cornerRadius: 40,
      fill: 'rgba(0, 0, 0, .8)',
      strokeStyle: "#000",
      strokeWidth: 3,
      strokeStyle: '#CC0',
      shadow: false, 
      shadowBlur: 3,
      cssStyles: {color: '#FFF', fontWeight: 'bold'}
    });
    $('#edit-beautytips-styles-big-green').bt('This balloon is green with no border and large text.',{
      width: 300,
      fill: '#00FF4E',
      overlap: 0,
      centerPointY: .5,
      centerPointX: .5,
      strokeWidth: 0,
      spikeLength: 40,
      spikeGirth: 10,
      padding: 20,
      cornerRadius: 15,
      shadow: false, 
      shadowBlur: 3,
      cssStyles: {
        fontFamily: '"lucida grande",tahoma,verdana,arial,sans-serif', 
        fontSize: '14px'
      }
    });
    $('#edit-beautytips-styles-google-maps').bt('This is a Google maps styled balloon.',{
      positions: 'top',
      width: 220,
      overlap: 0,
      centerPointY: .5,
      centerPointX: .9,
      spikeLength: 65,
      spikeGirth: 40,
      padding: 15,
      cornerRadius: 25,
      shadow: false, 
      shadowBlur: 3,
      fill: '#FFF',
      strokeStyle: '#ABABAB',
      strokeWidth: 1,
      cssStyles: {color: 'black',}
    });
 });
}
