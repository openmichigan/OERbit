<?php
// $Id: zip_download.views_default.inc,v 1.2 2010/04/08 01:46:06 rdeboer Exp $

/**
 * @file
 *  View which returns paths to all files attached to resource.
 */

/**
 * Implementation of hook_views_default_views().
 */
function zip_download_views_default_views() {
	$view = new view;
	$view->name = 'materials_download_filelist';
	$view->description = 'List of files to download';
	$view->tag = 'materials';
	$view->view_php = '';
	$view->base_table = 'node';
	$view->is_cacheable = FALSE;
	$view->api_version = 2;
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	$handler = $view->new_display('default', 'Defaults', 'default');
	$handler->override_option('relationships', array(
	  'field_file_fid' => array(
		'label' => 'File',
		'required' => 0,
		'delta' => '0',
		'id' => 'field_file_fid',
		'table' => 'node_data_field_file',
		'field' => 'field_file_fid',
		'relationship' => 'none',
	  ),
	));
	$handler->override_option('fields', array(
	  'filepath' => array(
		'label' => '',
		'alter' => array(
		  'alter_text' => 0,
		  'text' => '',
		  'make_link' => 0,
		  'path' => '',
		  'link_class' => '',
		  'alt' => '',
		  'prefix' => '',
		  'suffix' => '',
		  'target' => '',
		  'help' => '',
		  'trim' => 0,
		  'max_length' => '',
		  'word_boundary' => 1,
		  'ellipsis' => 1,
		  'html' => 0,
		  'strip_tags' => 1,
		),
		'empty' => '',
		'hide_empty' => 1,
		'empty_zero' => 0,
		'link_to_file' => 0,
		'exclude' => 0,
		'id' => 'filepath',
		'table' => 'files',
		'field' => 'filepath',
		'relationship' => 'field_file_fid',
	  ),
	  'field_image_fid' => array(
		'label' => '',
		'alter' => array(
		  'alter_text' => 0,
		  'text' => '',
		  'make_link' => 0,
		  'path' => '',
		  'link_class' => '',
		  'alt' => '',
		  'prefix' => '',
		  'suffix' => '',
		  'target' => '',
		  'help' => '',
		  'trim' => 0,
		  'max_length' => '',
		  'word_boundary' => 1,
		  'ellipsis' => 1,
		  'html' => 0,
		  'strip_tags' => 1,
		),
		'empty' => '',
		'hide_empty' => 0,
		'empty_zero' => 0,
		'link_to_node' => 0,
		'label_type' => 'none',
		'format' => 'path_plain',
		'multiple' => array(
		  'group' => TRUE,
		  'multiple_number' => '',
		  'multiple_from' => '',
		  'multiple_reversed' => FALSE,
		),
		'exclude' => 0,
		'id' => 'field_image_fid',
		'table' => 'node_data_field_image',
		'field' => 'field_image_fid',
		'relationship' => 'none',
	  ),
	));
	$handler->override_option('sorts', array(
	  'field_material_type_value' => array(
		'order' => 'ASC',
		'delta' => -1,
		'id' => 'field_material_type_value',
		'table' => 'node_data_field_material_type',
		'field' => 'field_material_type_value',
		'override' => array(
		  'button' => 'Override',
		),
		'relationship' => 'none',
	  ),
	));
	$handler->override_option('arguments', array(
	  'field_course_reference_nid' => array(
		'default_action' => 'empty',
		'style_plugin' => 'default_summary',
		'style_options' => array(),
		'wildcard' => 'all',
		'wildcard_substitution' => 'All',
		'title' => '',
		'breadcrumb' => '',
		'default_argument_type' => 'fixed',
		'default_argument' => '',
		'validate_type' => 'node',
		'validate_fail' => 'not found',
		'break_phrase' => 0,
		'not' => 0,
		'id' => 'field_course_reference_nid',
		'table' => 'node_data_field_course_reference',
		'field' => 'field_course_reference_nid',
		'validate_user_argument_type' => 'uid',
		'validate_user_roles' => array(
		  '2' => 0,
		  '4' => 0,
		  '6' => 0,
		  '3' => 0,
		  '5' => 0,
		),
		'relationship' => 'none',
		'default_options_div_prefix' => '',
		'default_argument_user' => 0,
		'default_argument_fixed' => '',
		'default_argument_php' => '',
		'validate_argument_node_type' => array(
		  'course' => 'course',
		  'webform' => 0,
		  'accessibility_guideline' => 0,
		  'accessibility_test' => 0,
		  'information' => 0,
		  'instructor' => 0,
		  'material' => 0,
		  'other' => 0,
		  'page' => 0,
		  'session' => 0,
		  'story' => 0,
		  'unit' => 0,
		),
		'validate_argument_node_access' => 1,
		'validate_argument_nid_type' => 'nid',
		'validate_argument_vocabulary' => array(
		  '4' => 0,
		),
		'validate_argument_type' => 'tid',
		'validate_argument_transform' => 0,
		'validate_user_restrict_roles' => 0,
		'validate_argument_php' => '',
	  ),
	));
	$handler->override_option('filters', array(
	  'type' => array(
		'operator' => 'in',
		'value' => array(
		  'material' => 'material',
		),
		'group' => '0',
		'exposed' => FALSE,
		'expose' => array(
		  'operator' => FALSE,
		  'label' => '',
		),
		'id' => 'type',
		'table' => 'node',
		'field' => 'type',
		'relationship' => 'none',
	  ),
	  'status_extra' => array(
		'operator' => '=',
		'value' => '',
		'group' => '0',
		'exposed' => FALSE,
		'expose' => array(
		  'operator' => FALSE,
		  'label' => '',
		),
		'id' => 'status_extra',
		'table' => 'node',
		'field' => 'status_extra',
		'relationship' => 'none',
	  ),
	  'field_material_type_value_many_to_one' => array(
		'operator' => 'or',
		'value' => array(
		  'lectures' => 'lectures',
		  'assign' => 'assign',
		  'exams' => 'exams',
		  'labs' => 'labs',
		  'demos' => 'demos',
		  'images' => 'images',
		  'handouts' => 'handouts',
		  'supp-readings' => 'supp-readings',
		  'projects' => 'projects',
		  'papers' => 'papers',
		  'present' => 'present',
		  'excercises' => 'excercises',
		),
		'group' => '0',
		'exposed' => FALSE,
		'expose' => array(
		  'operator' => FALSE,
		  'label' => '',
		),
		'id' => 'field_material_type_value_many_to_one',
		'table' => 'node_data_field_material_type',
		'field' => 'field_material_type_value_many_to_one',
		'relationship' => 'none',
		'reduce_duplicates' => 0,
	  ),
	));
	$handler->override_option('access', array(
	  'type' => 'none',
	));
	$handler->override_option('cache', array(
	  'type' => 'none',
	));
	$handler->override_option('use_ajax', TRUE);
	$handler->override_option('items_per_page', 0);
	$handler->override_option('distinct', 0);
	$handler->override_option('style_options', array(
	  'grouping' => '',
	));
	$handler->override_option('row_options', array(
	  'inline' => array(
		'filepath' => 'filepath',
	  ),
	  'separator' => '',
	  'hide_empty' => 0,
	));
	
  	$views[$view->name] = $view;
  	return $views;
}