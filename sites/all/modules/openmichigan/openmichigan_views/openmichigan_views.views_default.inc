<?php

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

/**
 * Implementation of hook_views_default_views().
 */
function openmichigan_views_views_default_views() {
  /*
   * View 'course_versions'
   */
  $view = new view;
  $view->name = 'course_versions';
  $view->description = 'Displays a list of different terms for the same course';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_course_term_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[field_course_term_value] ',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_course_term_value',
      'table' => 'node_data_field_course_term',
      'field' => 'field_course_term_value',
      'relationship' => 'none',
    ),
    'field_course_year_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[field_course_term_value][field_course_year_value]',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => TRUE,
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 1,
      'id' => 'field_course_year_value',
      'table' => 'node_data_field_course_year',
      'field' => 'field_course_year_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[field_course_year_value] ',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'link_to_node_revision' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node_revisions',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'field_course_year_value' => array(
      'order' => 'DESC',
      'delta' => -1,
      'id' => 'field_course_year_value',
      'table' => 'node_data_field_course_year',
      'field' => 'field_course_year_value',
      'relationship' => 'none',
    ),
    'field_course_term_value' => array(
      'order' => 'ASC',
      'delta' => -1,
      'id' => 'field_course_term_value',
      'table' => 'node_data_field_course_term',
      'field' => 'field_course_term_value',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_code_value' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'lower',
      'path_case' => 'lower',
      'transform_dash' => 1,
      'id' => 'field_code_value',
      'table' => 'node_data_field_code',
      'field' => 'field_code_value',
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
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => 'if (arg(0) == \'node\' && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  return $node->field_code[0][\'value\'];
}',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'course' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'other' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'course' => 'course',
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
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Previous Terms');
  $handler->override_option('items_per_page', 999);
  $handler->override_option('offset', 1);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'type' => 'ul',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'field_course_term_value' => 'field_course_term_value',
      'field_course_year_value' => 'field_course_year_value',
      'title' => 'title',
    ),
    'separator' => '-',
    'hide_empty' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  /*
   * View 'courses'
   */
  $view = new view;
  $view->name = 'courses';
  $view->description = 'Courses';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nodereferer_referers' => array(
      'label' => 'Referencing Nodes',
      'required' => 0,
      'referrer_delta' => '-1',
      'referrer_field' => 'field_parent_unit',
      'id' => 'nodereferer_referers',
      'table' => 'node',
      'field' => 'nodereferer_referers',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'title_1' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 1,
      'id' => 'title_1',
      'table' => 'node_revisions',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'title' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'link_to_node_revision' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node_revisions',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'nodereferer_referers',
    ),
    'status' => array(
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
    ),
  ));
  $handler->override_option('sorts', array(
    'weight' => array(
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node_revisions',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'nodereferrer_field' => array(
      'default_action' => 'not found',
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
      'id' => 'nodereferrer_field',
      'table' => 'node',
      'field' => 'nodereferrer_field',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'unit' => 'unit',
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'book' => 0,
        'course' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
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
      'operator' => 'in',
      'fields' => array(
        'field_parent_unit' => 'field_parent_unit',
        'field_course_instructor' => 0,
        'field_course_reference' => 0,
        'field_instructor_academic_unit' => 0,
        'field_unit_top' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'unit' => 'unit',
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
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '6' => 6,
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 0);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => 'title_1',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'title_1' => 'title_1',
      'nodereferrer_type' => 'nodereferrer_type',
    ),
    'separator' => '',
    'hide_empty' => 0,
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('relationships', array());
  $handler->override_option('sorts', array());
  $handler->override_option('arguments', array(
    'field_parent_unit_nid' => array(
      'default_action' => 'not found',
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
      'id' => 'field_parent_unit_nid',
      'table' => 'node_data_field_parent_unit',
      'field' => 'field_parent_unit_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'book' => 0,
        'course' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
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
        'course' => 'course',
        'unit' => 'unit',
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
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => 0,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'node/%/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $views[$view->name] = $view;

  /*
   * View 'feed'
   */
  $view = new view;
  $view->name = 'feed';
  $view->description = 'Site-wide RSS feed';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'course' => 'course',
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
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Open.Michigan - Open Educational Resources');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'build_mode' => 'full',
    'links' => 0,
    'comments' => 0,
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => 1,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $handler = $view->new_display('feed', 'Feed', 'feed_2');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => 0,
    'description' => 'Open.Michigan - Open Educational Resources',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array());
  $handler->override_option('path', 'education/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', 0);
  $handler = $view->new_display('feed', 'RDF', 'feed_3');
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => '',
      'wildcard_substitution' => '',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'node',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '4' => 0,
        '6' => 0,
        '3' => 0,
        '5' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'course' => 0,
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
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('items_per_page', 1);
  $handler->override_option('style_plugin', 'rdf');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => 'Open.Michigan - Open Educational Resources',
    'description_from_mission' => 1,
    'update_period' => '',
    'update_frequency' => '',
    'update_base' => '',
    'format' => 'rdf+json',
  ));
  $handler->override_option('row_plugin', 'node_rdf');
  $handler->override_option('row_options', array(
    'item_length' => 'fulltext',
    'date_timezone' => '',
  ));
  $handler->override_option('path', 'node/%/rdf');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $handler = $view->new_display('feed', 'OCW Feed', 'feed_4');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'course' => 'course',
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
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_content_type_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(
        'course' => 'course',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_content_type_value_many_to_one',
      'table' => 'node_data_field_content_type',
      'field' => 'field_content_type_value_many_to_one',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'reduce_duplicates' => 1,
    ),
  ));
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array());
  $handler->override_option('path', 'ocwfeed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $views[$view->name] = $view;

  /*
   * View 'find'
   */
  $view = new view;
  $view->name = 'find';
  $view->description = 'This is the find view that includes the featured list of items';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_course_image_fid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'Thumbnail_linked',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_course_image_fid',
      'table' => 'node_data_field_course_image',
      'field' => 'field_course_image_fid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'title_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title">[title_1]</span>',
        'make_link' => 1,
        'path' => '',
        'link_class' => 'title',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title_1',
      'table' => 'node_revisions',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '250',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 1,
        'html' => 1,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'view_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:source">[view_node]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => '> more',
      'exclude' => 0,
      'id' => 'view_node',
      'table' => 'node',
      'field' => 'view_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'random' => array(
      'order' => 'ASC',
      'id' => 'random',
      'table' => 'views',
      'field' => 'random',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'field_course_featured_value_many_to_one' => array(
      'operator' => 'and',
      'value' => array(
        'Yes' => 'Yes',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_course_featured_value_many_to_one',
      'table' => 'node_data_field_course_featured',
      'field' => 'field_course_featured_value_many_to_one',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '1' => 1,
      '6' => 6,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Featured Resources');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('items_per_page', 8);
  $handler->override_option('distinct', 1);
  $handler = $view->new_display('block', 'Featured (Users)', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'Featured (Admin)', 'block_2');
  $handler->override_option('filters', array(
    'field_course_featured_value_many_to_one' => array(
      'operator' => 'and',
      'value' => array(
        'Yes' => 'Yes',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_course_featured_value_many_to_one',
      'table' => 'node_data_field_course_featured',
      'field' => 'field_course_featured_value_many_to_one',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '3' => 3,
    ),
  ));
  $handler->override_option('items_per_page', 0);
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  /*
   * View 'highlights'
   */
  $view = new view;
  $view->name = 'highlights';
  $view->description = 'This view displays the highlights for the current course or other information.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'state' => array(
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
      'exclude' => 1,
      'id' => 'state',
      'table' => 'node',
      'field' => 'state',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<h2 property="dc:title" class="[state]">[title]</h2>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="publishedinfo"><strong>Published:</strong> [status]</span><span class="editlink">[[edit_node]]</span><div class="clearfloat"></div>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'other' => 'other',
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
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '6' => 6,
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => 'title',
  ));
  $handler = $view->new_display('node_content', 'Highlights (Users)', 'node_content_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<h2 property="dc:title">[title]</h2>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '1' => 1,
      '6' => 6,
      '5' => 5,
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $handler = $view->new_display('node_content', 'Highlights (Admin)', 'node_content_2');
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'other' => 'other',
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
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'instructor'
   */
  $view = new view;
  $view->name = 'instructor';
  $view->description = 'This view displays the About The Instructor information on the Course Overview page.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'field_course_instructor_nid' => array(
      'label' => 'Course Instructor',
      'required' => 1,
      'delta' => -1,
      'id' => 'field_course_instructor_nid',
      'table' => 'node_data_field_course_instructor',
      'field' => 'field_course_instructor_nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'nothing' => array(
      'label' => '',
      'alter' => array(
        'text' => 'About The Instructor',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 1,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<h3>[title]</h3>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'field_course_instructor_nid',
    ),
    'status' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'field_course_instructor_nid',
    ),
    'edit_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="publishedinfo"><strong>Published:</strong> [status]</span><span class="editlink">[[edit_node]]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'field_course_instructor_nid',
    ),
    'field_image_caption_value' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_image_caption_value',
      'table' => 'node_data_field_image_caption',
      'field' => 'field_image_caption_value',
      'relationship' => 'field_course_instructor_nid',
    ),
    'field_instructor_image_fid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[field_instructor_image_fid] [field_image_caption_value]',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'width200_default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_instructor_image_fid',
      'table' => 'node_data_field_instructor_image',
      'field' => 'field_instructor_image_fid',
      'relationship' => 'field_course_instructor_nid',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'body' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'field_course_instructor_nid',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'node',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'book' => 0,
        'course' => 0,
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
        'instructor' => 'instructor',
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
      'relationship' => 'field_course_instructor_nid',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_plugin', 'views_accordion');
  $handler->override_option('style_options', array(
    'grouping' => 'nothing',
    'use-grouping-header' => 1,
    'start-open' => 0,
    'row-start-open' => '0',
    'keep-one-open' => 0,
    'disable-close-others' => 0,
    'speed' => '0.5',
    'toggle-links' => 0,
    'include-style' => 1,
    'auto-cycle' => 0,
    'auto-cycle-speed' => '5',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
    'hide_empty' => 0,
  ));
  $handler = $view->new_display('node_content', 'Instructors (Users)', 'node_content_1');
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $handler = $view->new_display('page', 'Instructors (Admin)', 'page_1');
  $handler->override_option('relationships', array());
  $handler->override_option('fields', array(
    'field_instructor_image_fid' => array(
      'label' => 'Picture',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'Thumbnail_default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_instructor_image_fid',
      'table' => 'node_data_field_instructor_image',
      'field' => 'field_instructor_image_fid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'title_1' => array(
      'label' => 'Name',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title_1',
      'table' => 'node_revisions',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_email_email' => array(
      'label' => 'Email',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_email_email',
      'table' => 'node_data_field_email',
      'field' => 'field_email_email',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('arguments', array(
    'null' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Manage Instructors',
      'breadcrumb' => 'manage instructors',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'must_not_be' => 0,
      'id' => 'null',
      'table' => 'views',
      'field' => 'null',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '4' => 0,
        '6' => 0,
        '3' => 0,
        '5' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'course' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'other' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'instructor' => 'instructor',
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
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '3' => 3,
    ),
  ));
  $handler->override_option('title', 'Manage Instructors');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'field_instructor_image_fid' => 'field_instructor_image_fid',
      'title_1' => 'title_1',
      'field_email_email' => 'field_email_email',
      'status' => 'status',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'field_instructor_image_fid' => array(
        'separator' => '',
      ),
      'title_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_email_email' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => 'title_1',
  ));
  $handler->override_option('path', 'education/instructors');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  /*
   * View 'materials'
   */
  $view = new view;
  $view->name = 'materials';
  $view->description = 'This view displays the materials for the current course.';
  $view->tag = '';
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
      'delta' => '-1',
      'id' => 'field_file_fid',
      'table' => 'node_data_field_file',
      'field' => 'field_file_fid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'state_1' => array(
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
      'exclude' => 1,
      'id' => 'state_1',
      'table' => 'node',
      'field' => 'state',
      'relationship' => 'none',
    ),
    'markup' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<a href="javascript:scroll(0,0);" class="top-link">Back to top</a>',
      'format' => '3',
      'exclude' => 1,
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
      'relationship' => 'none',
    ),
    'field_material_type_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[markup]<h3 id="[field_material_type_value]" property="dc:type">[field_material_type_value]</h3>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_material_type_value',
      'table' => 'node_data_field_material_type',
      'field' => 'field_material_type_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'title' => array(
      'label' => 'Document Title',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title" class="[state_1]">[title]</span>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_creators_value' => array(
      'label' => 'Creator',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:creator">[field_creators_value]</span>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_creators_value',
      'table' => 'node_data_field_creators',
      'field' => 'field_creators_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_file_fid' => array(
      'label' => 'Download',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '[filepath]',
        'link_class' => '[filemime]',
        'alt' => '[filename]',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_file_fid',
      'table' => 'node_data_field_file',
      'field' => 'field_file_fid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_video_embed' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_video_embed]" target="_blank" class="youtube"><img src="/sites/all/themes/oer/images/icon_youtube.gif" alt="YouTube button" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'video_url',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_video_embed',
      'table' => 'node_data_field_video',
      'field' => 'field_video_embed',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_link_url' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_link_url] " target="_blank" class="external"><img src="/sites/all/themes/oer/images/icon-external.png" alt="External Link - [field_link_url]" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_link_url',
      'table' => 'node_data_field_link',
      'field' => 'field_link_url',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_image_fid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_image_fid]" target="_blank" class="image"><img src="/sites/all/themes/oer/images/icon-image.png" alt="link to image - [field_image_fid]" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'license_uri_1' => array(
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
        'trim' => 1,
        'max_length' => '128',
        'word_boundary' => 1,
        'ellipsis' => 0,
        'strip_tags' => 1,
        'html' => 1,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 0,
      'display_style' => 'full',
      'exclude' => 1,
      'id' => 'license_uri_1',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
      'relationship' => 'none',
    ),
    'license_uri' => array(
      'label' => 'License',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:license" title="[license_uri_1]">[license_uri]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 1,
      'display_style' => 'tiny_icons',
      'exclude' => 0,
      'id' => 'license_uri',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Published',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[status] [[edit_node]]',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
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
      'relationship' => 'none',
    ),
    'weight' => array(
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
    'field_material_type_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(
        'schedules' => 'schedules',
        'lectures' => 'lectures',
        'assign' => 'assign',
        'exams' => 'exams',
        'labs' => 'labs',
        'demos' => 'demos',
        'data' => 'data',
        'images' => 'images',
        'handouts' => 'handouts',
        'cases' => 'cases',
        'supp-readings' => 'supp-readings',
        'studentnotes' => 'studentnotes',
        'projects' => 'projects',
        'papers' => 'papers',
        'present' => 'present',
        'exercises' => 'exercises',
        'software' => 'software',
        'misc' => 'misc',
        'learning' => 'learning',
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
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '1' => 1,
      '6' => 6,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('footer_format', '3');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => 'field_material_type_value',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'state_1' => 'state_1',
      'field_material_type_value' => 'field_material_type_value',
      'title' => 'title',
      'field_creators_value' => 'field_creators_value',
      'field_file_fid' => 'field_file_fid',
      'field_video_embed' => 'field_file_fid',
      'field_link_url' => 'field_file_fid',
      'field_image_fid' => 'field_file_fid',
      'license_uri_1' => 'license_uri_1',
      'license_uri' => 'license_uri',
      'status' => 'status',
      'edit_node' => 'status',
    ),
    'info' => array(
      'state_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_material_type_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_creators_value' => array(
        'separator' => '',
      ),
      'field_file_fid' => array(
        'separator' => '',
      ),
      'field_video_embed' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_link_url' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_image_fid' => array(
        'separator' => '',
      ),
      'license_uri_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'license_uri' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'build_mode' => 'teaser',
    'links' => 0,
    'comments' => 0,
  ));
  $handler = $view->new_display('node_content', 'Materials (Users)', 'node_content_1');
  $handler->override_option('fields', array(
    'markup' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<a href="javascript:scroll(0,0);" class="top-link">Back to top</a>',
      'format' => '3',
      'exclude' => 1,
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_material_type_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '[markup]<h3 id="[field_material_type_value]" property="dc:type">[field_material_type_value]</h3>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_material_type_value',
      'table' => 'node_data_field_material_type',
      'field' => 'field_material_type_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'title' => array(
      'label' => 'Document Title',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title">[title]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_creators_value' => array(
      'label' => 'Creator',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:creator">[field_creators_value]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_creators_value',
      'table' => 'node_data_field_creators',
      'field' => 'field_creators_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_file_fid' => array(
      'label' => 'Download',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '[filepath]',
        'link_class' => '[filemime]',
        'alt' => '[filename]',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_file_fid',
      'table' => 'node_data_field_file',
      'field' => 'field_file_fid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_video_embed' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<a href="[field_video_embed]" target="_blank" class="youtube"><img src="/sites/all/themes/oer/images/icon_youtube.gif" alt="YouTube button" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'video_url',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_video_embed',
      'table' => 'node_data_field_video',
      'field' => 'field_video_embed',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_link_url' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_link_url] " target="_blank" class="external"><img src="/sites/all/themes/oer/images/icon-external.png" alt="External Link - [field_link_url]" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_link_url',
      'table' => 'node_data_field_link',
      'field' => 'field_link_url',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_image_fid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_image_fid]" target="_blank" class="image"><img src="/sites/all/themes/oer/images/icon-image.png" alt="link to image - [field_image_fid]" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'license_uri_1' => array(
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
        'trim' => 1,
        'max_length' => '128',
        'word_boundary' => 1,
        'ellipsis' => 0,
        'strip_tags' => 1,
        'html' => 1,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 0,
      'display_style' => 'full',
      'exclude' => 1,
      'id' => 'license_uri_1',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'license_uri' => array(
      'label' => 'License',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:license" title="[license_uri_1]">[license_uri]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 1,
      'display_style' => 'tiny_icons',
      'exclude' => 0,
      'id' => 'license_uri',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $handler = $view->new_display('node_content', 'Materials (Admin)', 'node_content_2');
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
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '6' => 6,
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => 'field_material_type_value',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'state_1' => 'state_1',
      'markup' => 'markup',
      'field_material_type_value' => 'field_material_type_value',
      'title' => 'title',
      'field_creators_value' => 'field_creators_value',
      'field_file_fid' => 'field_file_fid',
      'field_video_embed' => 'field_file_fid',
      'field_link_url' => 'field_file_fid',
      'field_image_fid' => 'field_file_fid',
      'license_uri_1' => 'license_uri_1',
      'license_uri' => 'license_uri',
      'status' => 'edit_node',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'state_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'markup' => array(
        'separator' => '',
      ),
      'field_material_type_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_creators_value' => array(
        'separator' => '',
      ),
      'field_file_fid' => array(
        'separator' => '',
      ),
      'field_video_embed' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_link_url' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_image_fid' => array(
        'separator' => '',
      ),
      'license_uri_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'license_uri' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => ' ',
      ),
    ),
    'default' => '-1',
    'execution_type' => '1',
    'max_performance' => 0,
    'display_type' => '0',
    'hide_selector' => 0,
    'preserve_selection' => 1,
    'display_result' => 1,
    'merge_single_action' => 1,
    'operations' => array(
      'node_assign_owner_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'workflow_select_given_state_action' => array(
        'selected' => 1,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'workflow_select_next_state_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'revisioning_create_pending_revision_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_delete_node_action' => array(
        'selected' => 1,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'revisioning_delete_archived_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'nodewords_mass_delete_tags-e01bcb289dd404af7b21307f2aa06715' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-a27b9efabcd054685a549378b174ad11' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'system_message_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_ruleset_action_rules_set_1' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_script_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_make_sticky_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_make_unsticky_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-c4d3b28efb86fd703619a50b74d43794' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_fields_action' => array(
        'selected' => 1,
        'skip_confirmation' => 0,
        'label' => '',
        'settings' => array(
          'php_code' => 0,
          'show_tokens' => 0,
          'display_fields' => array(
            '_all_' => '_all_',
          ),
          '_error_element_base' => 'style_options][operations][views_bulk_operations_fields_action][settings][',
        ),
      ),
      'views_bulk_operations_taxonomy_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'views_bulk_operations_argument_selector_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_promote_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-14de7d028b4bffdf2b4a266562ca18ac' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-9c585624b9b3af0b4687d5f97f35e047' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_publish_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'revisioning_publish_latest_revision_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'system_goto_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'emfield_operations_reload' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_unpromote_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-8ce21b08bb8e773d10018b484fe4815e' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_save_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'system_send_email_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'creativecommons_set_license_action' => array(
        'selected' => 1,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_mass_update-0ccad85c1ebe4c9ceada1aa64293b080' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_unpublish_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'node_unpublish_by_keyword_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'auto_nodetitle_operations_update' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
      'pathauto_node_update_alias_multiple-620e193b20ba9caa374fea9ca0ad38f0' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'label' => '',
      ),
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'materials_download_filelist'
   */
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
      'delta' => '-1',
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
        'schedules' => 'schedules',
        'lectures' => 'lectures',
        'assign' => 'assign',
        'exams' => 'exams',
        'labs' => 'labs',
        'demos' => 'demos',
        'data' => 'data',
        'images' => 'images',
        'handouts' => 'handouts',
        'cases' => 'cases',
        'supp-readings' => 'supp-readings',
        'studentnotes' => 'studentnotes',
        'projects' => 'projects',
        'papers' => 'papers',
        'present' => 'present',
        'exercises' => 'exercises',
        'software' => 'software',
        'misc' => 'misc',
        'learning' => 'learning',
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

  /*
   * View 'materials_embed'
   */
  $view = new view;
  $view->name = 'materials_embed';
  $view->description = 'Embed materials views in other views.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Document Title',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'title_1' => array(
      'label' => 'Document Title',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title">[title_1]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title_1',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_creators_value' => array(
      'label' => 'Creator',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:creator">[field_creators_value]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_creators_value',
      'table' => 'node_data_field_creators',
      'field' => 'field_creators_value',
      'relationship' => 'none',
    ),
    'field_file_fid' => array(
      'label' => 'Download',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_file_fid',
      'table' => 'node_data_field_file',
      'field' => 'field_file_fid',
      'relationship' => 'none',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
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
    'field_link_url' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => ' <a href="[field_link_url]" target="_blank" class="external"><img src="/sites/all/themes/oer/images/icon-external.png" alt="External Link - [field_link_url]" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_link_url',
      'table' => 'node_data_field_link',
      'field' => 'field_link_url',
      'relationship' => 'none',
    ),
    'field_video_embed' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => ' <a href="[field_video_embed]" target="_blank" class="youtube"><img src="/sites/all/themes/oer/images/icon_youtube.gif" alt="YouTube button" /></a>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'video_url',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_video_embed',
      'table' => 'node_data_field_video',
      'field' => 'field_video_embed',
      'relationship' => 'none',
    ),
    'license_uri_1' => array(
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
        'trim' => 1,
        'max_length' => '128',
        'word_boundary' => 1,
        'ellipsis' => 0,
        'strip_tags' => 1,
        'html' => 1,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 0,
      'display_style' => 'full',
      'exclude' => 1,
      'id' => 'license_uri_1',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
      'relationship' => 'none',
    ),
    'license_uri' => array(
      'label' => 'License',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:license" title="[license_uri_1]">[license_uri]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 1,
      'display_style' => 'tiny_icons',
      'exclude' => 0,
      'id' => 'license_uri',
      'table' => 'creativecommons_node',
      'field' => 'license_uri',
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
      'relationship' => 'none',
    ),
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'relationship' => 'none',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'not found',
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
      'break_phrase' => 1,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '4' => 0,
        '3' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'book' => 0,
        'course' => 0,
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
      'validate_argument_nid_type' => 'nids',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'field_creators_value' => 'field_creators_value',
      'field_file_fid' => 'field_file_fid',
      'field_image_fid' => 'field_file_fid',
      'field_link_url' => 'field_file_fid',
      'field_video_embed' => 'field_file_fid',
      'license_uri' => 'license_uri',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_creators_value' => array(
        'separator' => '',
      ),
      'field_file_fid' => array(
        'separator' => '',
      ),
      'field_image_fid' => array(
        'separator' => '',
      ),
      'field_link_url' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_video_embed' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'license_uri' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $views[$view->name] = $view;

  /*
   * View 'materials_links'
   */
  $view = new view;
  $view->name = 'materials_links';
  $view->description = 'Jump links for the materials';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_course_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_course_reference_nid',
      'table' => 'node_data_field_course_reference',
      'field' => 'field_course_reference_nid',
      'relationship' => 'none',
    ),
    'field_material_type_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'node/!1/materials#[field_material_type_value]',
        'link_class' => 'jumplink',
        'alt' => '%1 - [field_material_type_value]',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_material_type_value',
      'table' => 'node_data_field_material_type',
      'field' => 'field_material_type_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'nothing' => array(
      'label' => '',
      'alter' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
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
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
    'field_material_type_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(
        'schedules' => 'schedules',
        'lectures' => 'lectures',
        'assign' => 'assign',
        'exams' => 'exams',
        'labs' => 'labs',
        'demos' => 'demos',
        'data' => 'data',
        'images' => 'images',
        'handouts' => 'handouts',
        'cases' => 'cases',
        'supp-readings' => 'supp-readings',
        'studentnotes' => 'studentnotes',
        'projects' => 'projects',
        'papers' => 'papers',
        'present' => 'present',
        'exercises' => 'exercises',
        'software' => 'software',
        'misc' => 'misc',
        'learning' => 'learning',
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
    'grouping' => 'field_material_type_value',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
    'hide_empty' => 0,
  ));
  $handler = $view->new_display('node_content', 'Node content', 'node_content_1');
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'materials_references'
   */
  $view = new view;
  $view->name = 'materials_references';
  $view->description = 'This view displays the list of nodes that a material can reference.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nodereferer_referers' => array(
      'label' => 'Referencing Nodes',
      'required' => 0,
      'referrer_delta' => '-1',
      'referrer_field' => 'field_course_reference',
      'id' => 'nodereferer_referers',
      'table' => 'node',
      'field' => 'nodereferer_referers',
      'relationship' => 'none',
    ),
    'field_file_fid' => array(
      'label' => 'File',
      'required' => 0,
      'delta' => '-1',
      'id' => 'field_file_fid',
      'table' => 'node_data_field_file',
      'field' => 'field_file_fid',
      'relationship' => 'nodereferer_referers',
    ),
    'field_image_fid' => array(
      'label' => 'Image',
      'required' => 0,
      'delta' => -1,
      'id' => 'field_image_fid',
      'table' => 'node_data_field_image',
      'field' => 'field_image_fid',
      'relationship' => 'nodereferer_referers',
    ),
  ));
  $handler->override_option('fields', array(
    'field_resource_type_value' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_resource_type_value',
      'table' => 'node_data_field_resource_type',
      'field' => 'field_resource_type_value',
      'relationship' => 'nodereferer_referers',
    ),
    'created' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'date_format' => 'custom',
      'custom_date_format' => 'F j, Y',
      'exclude' => 1,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'nodereferer_referers',
    ),
    'filename' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_file' => 0,
      'exclude' => 1,
      'id' => 'filename',
      'table' => 'files',
      'field' => 'filename',
      'relationship' => 'field_file_fid',
    ),
    'filename_1' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_file' => 0,
      'exclude' => 1,
      'id' => 'filename_1',
      'table' => 'files',
      'field' => 'filename',
      'relationship' => 'field_image_fid',
    ),
    'title' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'nodereferer_referers',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_resource_type_value' => array(
      'order' => 'ASC',
      'delta' => -1,
      'id' => 'field_resource_type_value',
      'table' => 'node_data_field_resource_type',
      'field' => 'field_resource_type_value',
      'relationship' => 'nodereferer_referers',
    ),
    'created' => array(
      'order' => 'ASC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'nodereferer_referers',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
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
      'default_argument_php' => 'if (arg(0) == \'node\' && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  if ($node->type == \'course\') {
    return $node->nid;
  }
  elseif (!empty($node->field_course_reference[0][\'nid\'])) {
    return $node->field_course_reference[0][\'nid\'];
  }
}',
      'validate_argument_node_type' => array(
        'webform' => 0,
        'accessibility_guideline' => 0,
        'accessibility_test' => 0,
        'course' => 0,
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
      'relationship' => 'nodereferer_referers',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('empty', 'There are no course elements to link this resource to.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_options', array(
    'grouping' => '',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'field_resource_type_value' => 'field_resource_type_value',
      'title' => 'title',
    ),
    'separator' => '-',
    'hide_empty' => 0,
  ));
  $views[$view->name] = $view;

  /*
   * View 'open_blog'
   */
  $view = new view;
  $view->name = 'open_blog';
  $view->description = 'Blog View on the homepage.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'aggregator_item';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'timestamp' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'custom',
      'custom_date_format' => 'F j, Y',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'aggregator_item',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
    'title' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'aggregator_item',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'aggregator_item',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', '<h3 class="shaded"><a href="https://open.umich.edu/blog/">open.blog</a></h3>
<div id="blogPic"><img src="/sites/all/themes/oer/images/blogpic.jpg" alt="CC-BY_NC_SA: Three Gossips by TOJOSAN, Flickr"/></div>
<h4><a href="http://open.umich.edu/blog/feed/"><img src="/sites/all/themes/oer/images/rss.gif" alt="RSS Feed" /></a>&nbsp;&nbsp;Recent Posts</h4>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('items_per_page', 3);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  /*
   * View 'overview'
   */
  $view = new view;
  $view->name = 'overview';
  $view->description = 'This view displays the main course information for the current course.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'state' => array(
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
      'exclude' => 1,
      'id' => 'state',
      'table' => 'node',
      'field' => 'state',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title" class="[state]">[title]</span>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'edit_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="publishedinfo"><strong>Published:</strong> [status]</span><span class="editlink">[[edit_node]]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'markup' => array(
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
    ),
  ));
  $handler->override_option('sorts', array(
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'timestamp' => array(
      'order' => 'ASC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'node_revisions',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'information' => 'information',
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
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
  $handler->override_option('style_plugin', 'views_accordion');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'use-grouping-header' => 0,
    'start-open' => 0,
    'row-start-open' => '0',
    'keep-one-open' => 0,
    'disable-close-others' => 0,
    'speed' => '0.5',
    'toggle-links' => 0,
    'include-style' => 1,
    'auto-cycle' => 0,
    'auto-cycle-speed' => '5',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'field_content_reference_nid' => 'field_content_reference_nid',
    ),
    'separator' => '',
    'hide_empty' => 1,
  ));
  $handler = $view->new_display('node_content', 'Overview (Users)', 'node_content_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title">[title]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'markup' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<a href="javascript:scroll(0,0);" class="top-link">Back to top</a>',
      'format' => '3',
      'exclude' => 0,
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '1' => 1,
      '6' => 6,
      '5' => 5,
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
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
        'course' => 'course',
        'information' => 'information',
        'material' => 'material',
        'other' => 'other',
        'session' => 'session',
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
      'override' => array(
        'button' => 'Use default',
      ),
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
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Open.Michigan Course');
  $handler->override_option('style_plugin', 'oer-rss');
  $handler->override_option('style_options', array(
    'mission_description' => 0,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'teaser',
  ));
  $handler->override_option('path', 'node/%/rss');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array(
    'default' => 0,
    'node_content_1' => 0,
  ));
  $handler->override_option('sitename_title', 0);
  $handler = $view->new_display('node_content', 'Overview (Admin)', 'node_content_2');
  $handler->override_option('fields', array(
    'state' => array(
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
      'exclude' => 1,
      'id' => 'state',
      'table' => 'node',
      'field' => 'state',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:title" class="[state]">[title]</span> <span class="published-state">Published: [status]</span>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="publishedinfo"><strong>Published:</strong> [status]</span><span class="editlink">[[edit_node]]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'markup' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<a href="javascript:scroll(0,0);" class="top-link">Back to top</a>',
      'format' => '3',
      'exclude' => 0,
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'information' => 'information',
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
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '6' => 6,
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'schools_colleges'
   */
  $view = new view;
  $view->name = 'schools_colleges';
  $view->description = 'Schools & Colleges';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'relationship' => 'none',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'unit' => 'unit',
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
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_unit_top_nid' => array(
      'operator' => 'not empty',
      'value' => array(),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_unit_top_nid',
      'table' => 'node_data_field_unit_top',
      'field' => 'field_unit_top_nid',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', '<h1>Open Educational Resources</h1>
  <p>Select a school, college or unit below for resources.</p>
  <?php
  $breadcrumb = array(l(\'Home\', \'<front>\'), l(\'Find\', \'education\'), \'Open Educational Resources\');
  drupal_set_breadcrumb($breadcrumb);
  ?>');
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 0);
  $handler->override_option('items_per_page', 0);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'education/schools-colleges');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'education/schools-colleges/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $views[$view->name] = $view;

  /*
   * View 'sessions'
   */
  $view = new view;
  $view->name = 'sessions';
  $view->description = 'This view displays the session information for the current course.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'state' => array(
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
      'exclude' => 1,
      'id' => 'state',
      'table' => 'node',
      'field' => 'state',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<div class="views-field-title [state]" id="[title]" property="dc:title">[title]</div>',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status' => array(
      'label' => 'Published',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="publishedinfo"><strong>Published:</strong> [status]</span><span class="editlink">[[edit_node]]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
    'field_content_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_content_reference_nid',
      'table' => 'node_data_field_content_reference',
      'field' => 'field_content_reference_nid',
      'relationship' => 'none',
    ),
    'body' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span property="dc:description">[body]</span>',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'markup' => array(
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<a href="javascript:scroll(0,0);" class="top-link">Back to top</a>',
      'format' => '3',
      'exclude' => 0,
      'id' => 'markup',
      'table' => 'customfield',
      'field' => 'markup',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_material_type_value' => array(
      'id' => 'field_material_type_value',
      'table' => 'node_data_field_material_type',
      'field' => 'field_material_type_value',
    ),
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'relationship' => 'none',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'session' => 'session',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => 'title',
  ));
  $handler = $view->new_display('node_content', 'Sessions (Users)', 'node_content_1');
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '1' => 1,
      '6' => 6,
      '5' => 5,
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $handler = $view->new_display('node_content', 'Sessions (Admin)', 'node_content_2');
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'session' => 'session',
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
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '4' => 4,
      '6' => 6,
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'sessions_links'
   */
  $view = new view;
  $view->name = 'sessions_links';
  $view->description = 'Jump links for the sessions';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_course_reference_nid' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_course_reference_nid',
      'table' => 'node_data_field_course_reference',
      'field' => 'field_course_reference_nid',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<h2>[title]</h2>',
        'make_link' => 1,
        'path' => 'node/!1/sessions#[title]',
        'link_class' => 'jumplink',
        'alt' => '%1 - [title]',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'nothing' => array(
      'label' => '',
      'alter' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'weight' => array(
      'order' => 'ASC',
      'id' => 'weight',
      'table' => 'node_weight',
      'field' => 'weight',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_course_reference_nid' => array(
      'default_action' => 'not found',
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
        'book' => 0,
        'information' => 0,
        'instructor' => 0,
        'material' => 0,
        'page' => 0,
        'session' => 0,
        'story' => 0,
        'unit' => 0,
      ),
      'validate_argument_node_access' => 0,
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
        'session' => 'session',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => 'title',
  ));
  $handler = $view->new_display('node_content', 'Node content', 'node_content_1');
  $handler->override_option('types', array(
    'course' => 'course',
  ));
  $handler->override_option('modes', array(
    '0' => 'full',
  ));
  $handler->override_option('argument_mode', 'nid');
  $handler->override_option('default_argument', '');
  $handler->override_option('show_title', 1);
  $views[$view->name] = $view;

  /*
   * View 'top'
   */
  $view = new view;
  $view->name = 'top';
  $view->description = 'Page that all top level academic units will inherit from';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'nothing' => array(
      'label' => '',
      'alter' => array(
        'text' => 'Yes, this academic unit belongs in the top level of the hierarchy.',
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
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
    'title' => array(
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'nid' => array(
      'operator' => '=',
      'value' => array(
        'value' => '253',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('footer_format', '1');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('items_per_page', 1);
  $handler->override_option('row_options', array(
    'inline' => array(
      'nothing' => 'nothing',
      'title' => 'title',
    ),
    'separator' => '',
    'hide_empty' => 1,
  ));
  $views[$view->name] = $view;

  return $views;
}
