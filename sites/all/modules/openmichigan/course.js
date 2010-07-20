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
    $("#edit-field-creators-1-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-2-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-3-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-4-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-5-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-6-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-7-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-8-value").blur(function() { course_populate_author(); });
    $("#edit-field-creators-9-value").blur(function() { course_populate_author(); });
  });
}

function course_populate_author() {
  var author = $("#edit-field-creators-0-value").val();
  if ($("#edit-field-creators-1-value").val()) { author = author + ', ' + $("#edit-field-creators-1-value").val(); }
  if ($("#edit-field-creators-2-value").val()) { author = author + ', ' + $("#edit-field-creators-2-value").val(); }
  if ($("#edit-field-creators-3-value").val()) { author = author + ', ' + $("#edit-field-creators-3-value").val(); }
  if ($("#edit-field-creators-4-value").val()) { author = author + ', ' + $("#edit-field-creators-4-value").val(); }
  if ($("#edit-field-creators-5-value").val()) { author = author + ', ' + $("#edit-field-creators-5-value").val(); }
  if ($("#edit-field-creators-6-value").val()) { author = author + ', ' + $("#edit-field-creators-6-value").val(); }
  if ($("#edit-field-creators-7-value").val()) { author = author + ', ' + $("#edit-field-creators-7-value").val(); }
  if ($("#edit-field-creators-8-value").val()) { author = author + ', ' + $("#edit-field-creators-8-value").val(); }
  if ($("#edit-field-creators-9-value").val()) { author = author + ', ' + $("#edit-field-creators-9-value").val(); }
  $("#edit-creativecommons-metadata-attributionName").val(author);
  $("#edit-creativecommons-metadata-creator").val(author);
}

