<?php // $Id: accessible_content.blocks.inc,v 1.1.2.3 2010/01/09 19:38:37 kevee Exp $

/**
*   @file
*   Block callbacks for Accessible Content
*/

/**
*  Retrieves accessibility totals for the currently viewed node.
*  @return array An array as outlined in hook_block
*/
function accessible_content_block_node_overview() {
  $node = menu_get_object();
  if (variable_get($node->type .'_ac_enable', 0) && user_access('view accessibility information')) {
    if (!is_array($node->accessibility_totals)) {
      return array('subject' => t('Accessibility Overview'), 
                   'content' => t('No accessibility information available'));
    }
    drupal_add_css(drupal_get_path('module', 'accessible_content') .'/accessible_content.css');
    $list = array();
    foreach ($node->accessibility_totals as $type => $total) {
      $total = ($total) ? $total : 0;
      $list[] = '<span class="ac-label ac-'. $type .'">'. ucfirst($type)
          .': <span class="ac-block-total">'. $total .'</span></span>';
    }
    $list [] = l('View Detailed Information', 'node/'. $node->nid .'/accessibility');
    $list [] = l('Highlight Issues', 'node/'. $node->nid .'/accessibility/highlight');
    return array('subject' => t('Accessibility Overview'), 'content' => theme('item_list', $list));
  }
}