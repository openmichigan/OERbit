/* $Id$ */

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $("#edit-field-resource-type-value").ready(function() { material_resource_type(); });
    $("#edit-field-resource-type-value").change(function() { material_resource_type(); });
  });
}

function material_resource_type() {
  $("input[name^='files\[field_file_']").attr("disabled", "disabled");
  $("#field-file-items").hide();
  $("#edit-field-image-0-upload").attr("disabled", "disabled");
  $("#edit-field-image-0-wrapper").hide();
  $("#edit-field-video-0-embed").attr("disabled", "disabled");
  $("#edit-field-video-0-embed-wrapper").hide();
  $("#edit-field-video-0-embed-wrapper + .form-item").hide();
  $("#edit-field-link-0-url").attr("disabled", "disabled");
  $("#edit-field-link-0-url-wrapper").hide();
  switch ($("#edit-field-resource-type-value").val()) {
    case "file":
      $("input[name^='files\[field_file_']").removeAttr("disabled");
      $("#field-file-items").show();
      break;
    case "image":
      $("#edit-field-image-0-upload").removeAttr("disabled");
      $("#edit-field-image-0-wrapper").show();
      break;
    case "video":
      $("#edit-field-video-0-embed").removeAttr("disabled");
      $("#edit-field-video-0-embed-wrapper").show();
      $("#edit-field-video-0-embed-wrapper + .form-item").show();
      break;
    case "link":
      $("#edit-field-link-0-url").removeAttr("disabled");
      $("#edit-field-link-0-url-wrapper").show();
      break;
  }
}
