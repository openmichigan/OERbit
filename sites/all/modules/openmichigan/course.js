/* $Id$ */

/*
 * COPYRIGHT 2011
 *
 * The Regents of the University of Michigan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.
 *
 * You may not use the name of The University of Michigan in any
 * advertising or publicity pertaining to the use of distribution of this software
 * without specific, written prior authorization. If the above copyright notice
 * or any other identification of the University of Michigan is included in any
 * copy of any portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INDIRECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
  });
}

Drupal.behaviors.populateAuthor = function () {
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

