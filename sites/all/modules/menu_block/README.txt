ADDING MENU BLOCKS

    To add new menu blocks, use the "Add menu block" tab (or button) on the
    administer blocks page, admin/build/block. You will then be able to
    configure your menu block before adding it.


CONFIGURING MENU BLOCKS

    When adding or configuring a menu block, several configuration options are
    available:

    Block title
        For menu trees that start with the 1st level, the default block title
        will be the menu name. For menu trees that start with the 2nd level or
        deeper, the default block title will be the title for the parent menu
        item of the specified level.

        For example, if the active menu trail for the Navigation menu is:
        Administer > Site building > Menus > Primary links, then a menu block
        configured to start with the 1st level of the Navigation will display a
        block title of "Navigation". And a menu block configured to start with
        the 3rd level of the Navigation menu will display a block title of
        "Site building".

    Parent item
        First select the menu. Then select the parent item from that menu. The
        tree of links will only contain children of the selected parent item.

    Starting level
        Blocks that start with the 1st level will always be visible. Blocks that
        start with the 2nd level or deeper will only be visible when the trail
        to the active menu item is in the block's tree.

    Make the starting level follow the active menu item
        If the active menu item is deeper than the level specified above, the
        starting level will follow the active menu item. Otherwise, the starting
        level of the tree will remain fixed.

    Maximum depth
        From the starting level, specify the maximum depth of the tree. Blocks
        with a maximum depth of 1 will just be a single un-nested list of links
        with none of those links' children displayed.

    Expand children
        All sub-menus of this menu will be expanded.

    Sort
        Sort each item in the active trail to the top of its level. When used on
        a deep or wide menu tree, the active menu item's children will be easier
        to see when the page is reloaded.


STYLING MENU BLOCKS

    Themers should look at the myriad of classes added to the <div>, <li> and
    <a> elements.

    <div>
        The <div> wrapped around the menu tree has a class for several of the
        configurable options of the block: menu-name-NAME parent-mlid-MLID
        menu-level-LEVEL

    <li>
        The <li> elements of the menu tree can have an extended list of classes
        (compared to standard menu trees): first last menu-mlid-MLID
        has-children active active-trail

    <a>
        The <a> elements of the menu tree can have: active active-trail

    In addition, the wrapper <div> for the block is generated using the
    menu-block-wrapper.tpl.php template. And Menu block provides template
    suggestions of the form menu-block-wrapper-MENUNAME.tpl.php. For example, a
    file in your theme called menu-block-wrapper-primary-links.tpl.php can be
    used to override the <div> for just the primary-links menu blocks.


MENU BLOCK API

    Developers can use the API of this module to create their own menu trees
    outside the confines of blocks. All of the publicly available API functions
    are documented in the menu_block.module file.

    In addition, Menu block implements HOOK_get_menus() to retrieve menu names
    and titles of menus created by a module. See book_get_menus() in
    menu_block.book.inc for an example of this hook.
