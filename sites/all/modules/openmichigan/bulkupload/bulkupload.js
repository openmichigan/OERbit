// $id$
var imagexremove_url;
var imagesreturnurl;
function postletFinished(){
  var imagexReturn = function (data) {
    var returnHtml = Drupal.parseJson(data);
    $('#imagexthumbs').hide();
    $('#imagexthumbs').html(returnHtml['html']+"<div style=\"clear:both\"></div>");
    $('#imagexthumbs').show();
  }
  $.get(imagesreturnurl, null, imagexReturn);
  if ($('#imagexthumbs').parent().parent().parent().parent().is('.collapsed')) {
    Drupal.toggleFieldset($('#imagexthumbs').parent().parent().parent().parent());
  }
}
function imagexclick(nid){
  var selectedImages = $('#edit-selected-images').val();
  var indexOfNid = selectedImages.indexOf('|'+nid+'|');
  if(indexOfNid>-1){
    // nid is in list remove it
    selectedImages = selectedImages.replace('|'+nid+'|','|');
    $('#imagexthumb-'+nid).css({ border: "solid 2px grey"});
  } else {
    // nid NOT in list add it
    selectedImages += nid+'|';
  }
  $('#edit-selected-images').val(selectedImages);
  if(!imagexremove_url){
    imagexremove_url = $('#imagexremove').attr('href');
  }
  var url_join = '';
  if (imagexremove_url.indexOf('?')>-1){
    url_join = '&';
  } else {
    url_join = '?';
  }
  $('#imagexremove').attr('href',imagexremove_url+url_join+'images='+selectedImages);
  var selectedImagesArray = selectedImages.split("|");
  var numberSelected = selectedImagesArray.length;
  for(i=0;i<numberSelected;i++){
    $('#imagexthumb-'+selectedImagesArray[i]).css({ border: "solid 2px blue"});
  }
}