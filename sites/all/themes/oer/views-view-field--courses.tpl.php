<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>

<?php 
/**
 * The conditional below is a hideous hack (to quote a respected 
 * colleague, it is a "sleazy" fix) to assign the ".unpublished" css 
 * class to unpublished courses and resources. If there is a cleaner
 * more idiomatic way to do it, please rip out this hack.
 * 
 * The cryptic "strpos()" call is to check if the $output string
 * starts with "<a" since the "Course(s)" and "Resource(s)" header
 * strings should not be assigned the unpublished class and if you
 * look at the courses view you will see that these header strings
 * are generated using that view.
 * 
 * For further details edit the "courses" view and select
 * "Course List" display from the left navigation. Click on
 * the gear-like button to the right of the "Syle: Unformatted"
 * entry in the "Basic settings" column. You will see that the
 * "Grouping field:" pull down has the 
 * "Content: Content Type (field_content_type)" selected. There
 * is further explanatory text below the pull down. This record
 * grouping is used to generate the "Course(s)" and "Resource(s)"
 * category headings and sorts the rows fetched from the DB into
 * the appropriate group. The "Fields" section in the view editor
 * contains a "Content: Content Default" entry. Click on that to
 * see the configuration of the display for that field. It has
 * the "Exclude from display" option checked and the 
 * "Rewrite the output of this field" option is also checked with
 * the replacement text that prints out the category headings.
 * 
 * Signed, so you know who to blame, Ali Asad Lotia <lotia@umich.edu>
 */
if (isset($row->node_status) && ($row->node_status == 0) && (strpos($output, "a") == 1)) {
  $out_parts = preg_split("/(<a)/", $output, NULL, PREG_SPLIT_DELIM_CAPTURE);
  $output = $out_parts[1] . ' class="unpublished" ' . $out_parts[2];
}
print $output; 
?>
