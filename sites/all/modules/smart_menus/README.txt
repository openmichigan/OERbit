$Id: README.txt,v 1.3 2009/11/10 01:48:40 rdeboer Exp $

SMART MENUS, SMART TABS
=======================
The Smart menus and Smart tabs modules make the Drupal experience just that
little bit more convenient. The two modules give menus and tabs a memory, so
that when you revisit a page, your previous tab or menu choice is already
pre-selected for you. Not only will this save you numerous clicks, it will
almost feel like the system senses where you'd like to go, making the
experience more intuitive. No longer will you have to retrace your clicks to
get back to where you wanted to stay or waste clicks to escape from Drupal's
rigid default selections. Instead you'll find that Smart menus and Smart tabs
create default selections naturally, based on your personal click patterns as
they evolve during the session.
Once you've used these modules for a while you won't notice they're there...
but you'll miss them when they're gone.

The Smart menus module auto-expands menus  and submenus up to a depth that is
set by the administrator on the Smart menus configuration page. The default
maximum auto-expansion depth is 9, equal to Drupal's maximum number of menu
levels. This setting applies to anonymous users and is also the default for
the authenticated roles. However, every authenticated user can set their
personal depth on their My account page. A depth of zero may be entered to
switch the feature off. 
Smart menus can be configured to operate on any or all of Drupal's standard
menus (navigation, primary-links, secondary-links), as well as on any custom
menu you may want to define. Configuration is as a normal block, i.e. on the
Site building >> Blocks page, where you will now find Smart versions of the
aforementioned blocks for your consideration.
Note that Smart menu blocks can be configured to be invisible. This comes in
handy when you want the Smart menus magic to happen on menus rendered by
other contributed modules, such as Administartion menu, SimpleMenu, Nice menus
or Block menu.

The Smart tabs module enhances what Drupal calls menu local tasks, more 
commonly known as tabs. When a page features a row of tabs, Smart tabs will
remember the tab you selected the last time you visited that page. When a page
has two rows of tabs and the secondary row is the same or almost the same for
each of the primary tabs, Smart tabs is extra smart: when you click on a new
primary tab, Smart tabs will carry the secondary tab selection across with it.
This again saves you a click and avoids the confusion arising from Drupal's 
normal behaviour, which is to always pre-select Drupal's cast in stone
default, rather than the one that makes sense. A good example of this feature
in action can be found in Module Grants.
As with Smart menus, the Smart tabs administrator may override smart behaviour
for selected pages or groups of pages. Authenticated users may opt out of
Smart tabs via their My account pages.

To make the specification of page exclusion lists for Smart menus and Smart
tabs even easier, it is highly recommended to use URL aliases as much as 
possible, i.e. to enable the core Path module.

INSTALLATION
============
As with any other module download and extract the tar-ball in your 
sites/all/modules folder. Visit the Site building >> Modules page, tick the
Smart menus and Smart tabs checkboxes ans press Save.
For Smart menus to work you need to replace your existing content and
navigation blocks by their Smart counterparts, see Site building >> Blocks.
Generally neither of the modules will require any further configuration.
The available options on the Site configuration pages are self-explanatory.

AUTHOR
======
Rik de Boer, Melbourne, Australia. First released for Drupal 6.x, July 2009.
