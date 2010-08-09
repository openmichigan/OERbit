/**
 * Apply zebra styling to tables embedded within nodes in Drupal. (see Open.Michigan theme, html-elements.css)
 */

$(function() {
	$("table.embeddedTable tr:even").addClass("d0");
});
