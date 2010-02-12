// $Id: README.txt,v 1.12 2007/10/29 16:38:28 add1sun Exp $

NICE MENUS MODULE - CSS DROPDOWNS
---------------------------------

Currently maintained by: Addison Berry (add1sun) http://drupal.org/user/65088/contact

Orginally created by: Jake Gordon (jakeg) http://drupal.org/user/15674/contact and http://www.jakeg.co.uk/

This module should make it easy to add dropdown menus, using CSS-only in capable browsers (Firefox, Opera, Safari, etc) and with additional Javascript for lesser browsers (IE).

Nice menus should work with all of the latest browsers but please report any bugs, feature requests, etc at: http://drupal.org/project/issues/nice_menus.


Installation
------------
1. Copy nice_modules folder to your sites/all/modules directory.
2. At Administer --> Site building -> Modules (admin/build/modules) enable the module.
3. Configure the module settings at Administer -> Site configuration -> Nice Menus (admin/settings/nice_menus).
4. Configure the Nice Menus block(s) at Administer -> Site building -> Blocks (admin/build/block), setting the source menu and menu style, etc.
5. Return to the blocks page and enable the nice menus block(s), e.g. 'Nice Menu 1 (Nice Menu)' by putting it in a region.
6. See below sections on Customization and Advanced Theming as well as the handbook page (http://drupal.org/node/185543) for more tips.

Upgrade
-------
Please read the UPGRADE.txt file for upgrade information.

Features
--------
* Up to 10 menus - through settings you can configure the number of 'nice menus'
* Horizontal menus or vertical menus popping right or left
* Simple default styling which can be overridden using your own stylesheet

Issues
------

* Because this module tries to be as Javascript light as possible, various wishlist features cannot be added that are nor supported by CSS only.
* The menus may not work perfectly with all themes. Try Nice Menus out with the default Garland or Bluemarine first to check it works there (it should) before filing a bug report or trying to write a patch for other themes.
* Track bugs at http://drupal.org/project/issues/nice_menus?categories=bug
* Try adding .block-nice_menus {position: relative;} or .block-nice_menus {position: absolute;} to a stylesheet which may fix some issues.
* General issues with gaps between menu items in some custom themes.

Customization
-------------
The module includes a default CSS layout file (nice_menus_default.css) which is loaded for all pages.  If you don't like the default layout, it is suggested that you create a separate customized CSS file, and replace the default CSS file at Administer -> Themes -> Configure -> Global settings -> "Path to custom nice menus CSS file". This ensures smooth future upgrades as no editing of the module files is necessary. NOTE: you should not edit the regular nice_menus.css file since this contains the "logic" that makes Nice Menus work.

A good starting point for your custom file is to make a copy of the default file, then edit it to taste. Here are some common customization examples for your own stylesheet:

Make hovered links white with a black background:

  ul.nice-menu li a:hover { 
    color: white; 
    background: black;
  }

Make the link to the current page that you're on black with yellow text:

  ul.nice-menu li a.active { 
    color: yellow; 
    background: black;
  }

Get rid of all borders:

  ul.nice-menu,
  ul.nice-menu ul,
  ul.nice-menu li {
    border: 0;
  }

Get rid of the borders and background colour for all top-level menu items:

  ul.nice-menu,
  ul.nice-menu ul,
  ul.nice-menu li {
    border: 0;
    background: none;
  }

  ul.nice-menu-right li.menuparent,
  ul.nice-menu-right li li.menuparent { 
    background: url('arrow-right.png') right center no-repeat; 
  }

  li.menuparent li, li.menuparent ul {
    background: #eee;
  }

Have a nice menu stick right at the top of the page e.g. for an admin menu:

  #block-nice_menus-1 {
    position: absolute;
    top: 0;
    left: 0;
  }

In Firefox, as above but where the menu doesn't move as you scroll down the page:

  #block-nice_menus-1 {
    position: fixed;
    top: 0;
    left: 0;
  }

That should get you started.  Really this is just about knowing your CSS and styling it the way you want it.

Advanced theming
----------------
If you're creating or modifying your own theme, you can integrate nice menus more deeply by making use of these functions:
theme_nice_menu() -- themes any menu tree as a nice menu.
theme_nice_menu_primary_links() -- themes your primary links as a nice menu.

If you really know what you're doing, you can probably even customize the menu tree in creative ways, as those functions allow you to pass in a custom menu tree.