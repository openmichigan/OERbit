<?php
// $Id: menu_block.pages.inc,v 1.15 2008/12/04 04:35:34 johnalbin Exp $

/**
 * @file
 * Provides infrequently used pages for menu_block.
 */

/**
 * Implements hook_help().
 */
function _menu_block_help($path, $arg) {
  $output = '';
  switch ($path) {
    case 'admin/build/block':
      $output = '<p>' . t('Use the <a href="@url">add menu block page</a> to create a customizable menu block. You will then be able to configure your menu block before adding it.', array('@url' => url('admin/build/block/add-menu-block'))) . '</p>';
      if (module_exists('help')) {
        $output .= theme('more_help_link', url('admin/help/menu_block'));
      }
      break;

    case 'admin/build/block/configure':
    case 'admin/build/block/add-menu-block':
      if (module_exists('help')) {
        $output = '<p>' . t('To learn more about configuring menu blocks, see <a href="@url">menu block’s detailed help</a>.', array('@url' => url('admin/help/menu_block'))) . '</p>';
      }
      break;

    case 'admin/help#menu_block':
      $output =
        '<h3>' . t('Adding menu blocks') . '</h3>'
      . '<p>' . t('To add new menu blocks, use the "Add menu block" tab (or button) on the <a href="@url">administer blocks page</a>. You will then be able to configure your menu block before adding it.', array('@url' => url('admin/build/block'))) . '</p>'
      . '<h3>' . t('Configuring menu blocks') . '</h3>'
      . '<p>' . t('When adding or configuring a menu block, several configuration options are available:') . '</p>'
      . '<dl>'
      . '<dt><strong>' . t('Block title') . '</strong></dt>'
      . '<dd>' . t('For menu trees that start with the 1st level, the default block title will be the menu name. For menu trees that start with the 2nd level or deeper, the default block title will be the title for the parent menu item of the specified level.')
      . '<p>' . t('For example, if the active menu trail for the Navigation menu is: Administer › Site building › Menus › Primary links, then a menu block configured to start with the 1st level of the Navigation will display a block title of “Navigation”. And a menu block configured to start with the 3rd level of the Navigation menu will display a block title of “Site building”.') . '</p></dd>'
      . '<dt><strong>' . t('Parent item') . '</strong></dt>'
      . '<dd>' . t('First select the menu. Then select the parent item from that menu. The tree of links will only contain children of the selected parent item.') . '</dd>'
      . '<dt><strong>' . t('Starting level') . '</strong></dt>'
      . '<dd>' . t('Blocks that start with the 1st level will always be visible. Blocks that start with the 2nd level or deeper will only be visible when the trail to the active menu item is in the block’s tree.') . '</dd>'
      . '<dt><strong>' . t('Make the starting level follow the active menu item') . '</strong></dt>'
      . '<dd>' . t('If the active menu item is deeper than the level specified above, the starting level will follow the active menu item. Otherwise, the starting level of the tree will remain fixed.') . '</dd>'
      . '<dt><strong>' . t('Maximum depth') . '</strong></dt>'
      . '<dd>' . t('From the starting level, specify the maximum depth of the tree. Blocks with a maximum depth of 1 will just be a single un-nested list of links with none of those links’ children displayed.') . '</dd>'
      . '<dt><strong>' . t('Expand children') . '</strong></dt>'
      . '<dd>' . t('All sub-menus of this menu will be expanded.') . '</dd>'
      . '<dt><strong>' . t('Sort') . '</strong></dt>'
      . '<dd>' . t('Sort each item in the active trail to the top of its level. When used on a deep or wide menu tree, the active menu item’s children will be easier to see when the page is reloaded.') . '</dd>'
      . '</dl>'
      . '<h3>' . t('Styling menu blocks') . '</h3>'
      . '<p>' . t('Themers should look at the myriad of classes added to the %div, %li and %a elements.', array('%div' => '<div>', '%li' => '<li>', '%a' => '<a>')) . '</p>'
      . '<dl>'
      . '<dt>' . theme('placeholder', '<div>') . '</dt>'
      . '<dd>' . t('The %div wrapped around the menu tree has a class for several of the configurable options of the block: %class.', array('%div' => '<div>', '%class' => 'menu-name-NAME parent-mlid-MLID menu-level-LEVEL')) . '</dd>'
      . '<dt>' . theme('placeholder', '<li>') . '</dt>'
      . '<dd>' . t('The %li elements of the menu tree can have an extended list of classes (compared to standard menu trees): %class.', array('%li' => '<li>', '%class' => 'first last menu-mlid-MLID has-children active active-trail')) . '</dd>'
      . '<dt>' . theme('placeholder', '<a>') . '</dt>'
      . '<dd>' . t('The %a elements of the menu tree can have: %class.', array('%a' => '<a>', '%class' => 'active active-trail')) . '</dd>'
      . '</dl>'
      . '<p>' . t('In addition, the wrapper %div for the block is generated using the %template_default template. And Menu block provides template suggestions of the form %template_suggestion. For example, a file in your theme called %template_example can be used to override the %div for just the primary-links menu blocks.', array('%div' => '<div>', '%template_default' => 'menu-block-wrapper.tpl.php', '%template_suggestion' => 'menu-block-wrapper-MENUNAME.tpl.php', '%template_example' => 'menu-block-wrapper-primary-links.tpl.php')) . '</p>'
      . '<h3>' . t('Menu block API') . '</h3>'
      . '<p>' . t('Developers can use the API of this module to create their own menu trees outside the confines of blocks. All of the publicly available API functions are documented in the menu_block.module file.') . '</p>'
      . '<p>' . t('In addition, Menu block implements HOOK_get_menus() to retrieve menu names and titles of menus created by a module. See book_get_menus() in menu_block.book.inc for an example of this hook.') . '</p>';
      break;
  }
  return $output;
}
