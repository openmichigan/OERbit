<?php

/**
 * @file
 * Creative Commons module theme functions.
 *
 */


/**
 * Site license theming
 */ 
function theme_creativecommons_site_license($cc) {
  $output = "\n<!--Creative Commons Site License-->\n";

  // HTML output
  $output .= $cc->get_html(TRUE);

  // Additional text
  if ($additional_text = variable_get('creativecommons_site_license_additional_text', '')) {
    $output .= '<br/>'. $additional_text;
  }

  // RDF output
  if ($cc->has_license() && variable_get('creativecommons_rdf', TRUE)) {
    $output .= "\n<!-- ". $cc->get_rdf() ." -->\n";
  }

  $output .= "<!--/Creative Commons Site License-->\n";

  return $output;
}

/**
 * Node license theming
 */ 
function theme_creativecommons_node_license($node) {

  return $node->cc->get_html();
}
 
