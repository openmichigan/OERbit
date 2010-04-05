/* $Id$ */

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $("#edit-field-course-code-0-value").change(function() {
      if ($("#edit-field-content-type-value option:selected").val() == 'course') {
        var url = $("#edit-field-course-code-0-value").val().toLowerCase().replace(/ /g, '-');
        $("#edit-field-code-0-value").val(url);
      }
    });
    $("#edit-title").change(function() {
      if ($("#edit-field-content-type-value option:selected").val() == 'resource') {
        var url = $("#edit-title").val().toLowerCase().replace(/ /g, '-');
        $("#edit-field-code-0-value").val(url);
      }
    });
    $("#edit-field-content-type-value").change(function() {
      $("#edit-field-course-code-0-value").trigger('change');
      $("#edit-title").trigger('change');
    });
    $("#edit-field-creators-0-value").blur(function() { course_populate_author(); });
  });
}

function course_populate_author() {
  $("#edit-creativecommons-metadata-attributionName").val($("#edit-field-creators-0-value").val());
  $("#edit-creativecommons-metadata-creator").val($("#edit-field-creators-0-value").val());
}
