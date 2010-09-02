$Id: README.txt,v 1.9 2010/05/06 03:30:20 rdeboer Exp $

DESCRIPTION
===========
This module gets around two quirks in the 6.x core Node module.
Currently the Node module:
- causes access grants to be ignored for unpublished content;
- ORs together access grants coming from multiple modules; this results
  in content being made accessible by one module when access had already
  been restricted by another, which is undesirable in most cases.

The module ensures that access grants are tested for unpublished content just
as they are for published content, so that using the Workflow module (or any
other module that uses the node_access table) you can implement workflows that
deal effectively with content moving from author via moderator to publisher 
BEFORE it is published (which is where it's needed most, once content is 
visible for all to see, it's a bit late to start a publication workflow
process!).
Using Taxonomy Access Control (or -Lite) you can restrict access to content
to user-defined "vocabularies" such as departments or regions. With Module
Grants this will work for unpublished content just as it does for published
content.
Moreover when Workflow and TAC or (TAC-Lite) are used together this module
makes sure that the combination exhibits the expected behaviour: access is
granted to content only when it is in the correct state AND of the appropriate
vocabulary "term" (such as department, country, etc.).
The module_grants module achieves this by AND-ing rather than OR-ing the grants.

Module Grants comes bundled with Module Grants Monitor (optional), which
provides users with a new menu item, "Accessible Content" that shows a list of
all content accessible to the logged-in user based on the permissions and
access grants as determined by enabled modules. This list may be filtered using
a double row of tabs residing at the top of the page, see point 3a below.

INSTALLATION AND CONFIGURATION
==============================
1. Place the "module_grants" folder in your "sites/all/modules" directory.
2. Under Administer >> Site building >> Modules, enable Module Grants and
   optionally Module Grants Monitor (recommended).
3a Visit Administer >> User management >> Permissions. Make sure that roles
   that are meant to be able to view unpublished and not yet published content
   have one of the following permissions:
   o "view revisions" (section "node module"), or
   o "view any|all <content-type> content" (section "revisioning module", if
   Revisioning installed).
   Make sure that the role of anonymous user does NOT have any of the above
   permissions.
3b There's usually no need to tick "administer nodes" for any role, which is
   good because "administer nodes" equates to almost god-like powers that you
   wouldn't normally give to normal users.
4. If required, install and enable as many modules for content access control
   as you need for your situation. Typical examples are Taxonomy Access Control
   (or use TAC Lite) and Workflow.
5. Optional, but highly recommended, especially when using Revisioning. Under
   Administer >> User management >> Permissions, section "module_grants_monitor
   module" select for each role which filtering tab they will get to use. The
   permissions, which are in alphabetical rahter than logical order, relate to
   two rows of tabs that appear on the 'Accessible content' page.
   The first row of up to 4 tabs filter content the logged-in user
     created,
     modified, 
     can edit,
     can view
   The second row of up to 3 tabs further filter content according to it being
     published,
     unpublished (includes previously published as well as not yet published)
     either ("all", that is: no additional filtering)

   NOTE 1: you must tick at least one permission box for each of the 2 rows
   NOTE 2: these tick boxes only determine whether the role in question gets
   to see the tabs, they do not in any way affect access to content. So in
   that sense you can safely tick any or all of the tab boxes for all
   authenticated users. However you may not want to confuse certain roles
   with too many tabs and too much output.

USAGE
=====
Module Grants Monitor creates a new navigation menu item, 'Accessible content'
visible to the administrator and to roles to which the administrator granted
access as per the above section, point 5. The content shown under 'Accessible
content' reflects the access grants given by modules installed on your system
to the current user.

You can use Module Grants in combination with TAC or TAC-Lite for fine-grained
access control based on vocabularies (such as "department") assigned to the
various content types. You can then create department-specific roles (eg
Sports Author, Music Author) and enforce that these roles can only access
content belonging to their departments, whether it's published or not.
Create your grants "schemes" on this page: Administer >> User management >>
Access control by taxonmy.
In addition you may want to install the Workflow module to further segragate
roles (eg author and moderator) via access control based on states such as
"in draft", "in review" and "published". See Administer >> Site building >>
Workflow.
The module makes sure that access to content is given only when BOTH the
TAC (Lite) and the Workflow Access modules grant it (as opposed to one OR
the other).

This module also works well with the Revisioning module for creating effective
publication workflows operating on published as well as unpublished content
revisions. 
See the Revisioning project page at http://drupal.org/project/revisioning
for three step-by-step tutorials.

Be aware that any permissions given in the "node module" section override the
access grants given by the Workflow and TAC-Lite modules, so you probably only
want to assign a few creation permissions in the node module and grant 
view, update and delete via TAC/TAC-Lite and/or Workflow.

Additional configuration options are found at Administer >> Site configuration
>> Module Grants.

API
===
Module Grants features one hook, hook_user_node_access($revision_op, $node),
which module developers may implement to alter or add to the behaviour of
Module Grants as it determines whether access to a supplied node or revision
should be granted using the requested operation.
See the module_grants.api.php file.

AUTHOR
======
Rik de Boer, Melbourne, Australia.
