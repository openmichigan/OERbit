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
    $("#edit-field-resource-type-value").ready(function() { material_resource_type(); });
    $("#edit-field-resource-type-value").change(function() { material_resource_type(); });
  });
}

function material_resource_type() {
  $("input[name^='files\[field_file_']").attr("disabled", "disabled");
  $("#field-file-items").hide();
  $("#edit-field-image-0-upload").attr("disabled", "disabled");
  $("#edit-field-image-0-wrapper").hide();
  //$("#edit-field-video-0-embed").attr("disabled", "disabled");
  //$("#edit-field-video-0-embed-wrapper").hide();
  //$("#edit-field-video-0-embed-wrapper + .form-item").hide();
  $("#edit-field-link-0-url").attr("disabled", "disabled");
  $("#edit-field-link-0-url-wrapper").hide();
  switch ($("#edit-field-resource-type-value").val()) {
    case 'file':
      $("input[name^='files\[field_file_']").removeAttr("disabled");
      $("#field-file-items").show();
      break;
    case 'image':
      $("#edit-field-image-0-upload").removeAttr("disabled");
      $("#edit-field-image-0-wrapper").show();
      break;
    //case 'video':
      //$("#edit-field-video-0-embed").removeAttr("disabled");
      //$("#edit-field-video-0-embed-wrapper").show();
      //$("#edit-field-video-0-embed-wrapper + .form-item").show();
      //break;
    case 'link':
      $("#edit-field-link-0-url").removeAttr("disabled");
      $("#edit-field-link-0-url-wrapper").show();
      break;
    case 'audio':
      $("input[name^='files\[field_file_']").removeAttr("disabled");
      $("#field-file-items").show();
      break;
  }
}
