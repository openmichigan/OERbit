
DESCRIPTION
===========
This modules forces new unpublished content as well as edits to current content
to first go into a queue for review by a moderator/publisher, rather than
immediately becoming "live", i.e. visible to the public.

We took our inspiration from the Revision Moderation module by Angie Byron,
but found that a patch could not implement the deviating functionality our
customers required, which would change the current behaviour of the RM module
and surprise existing users.

In the RM module the permissions to edit and revert/publish content are lumped
together, so that it isn't possible to enforce separation of these
responsibilites by role. This module allows you to assign distinct permissions
for authors (to only create and edit content) and moderator roles (to review,
publish, revert, unpublish and optionally delete content).
No unnessary revisions are created when saving a revision that is pending.
Menu navigation has been altered so that users first pick the desired 
revision before being allowed to view, edit, publish, revert, unpublish or 
delete.
Triggers are provided for the publish, unpublish and revert events.
By taking advantage of the Module Grants module this module integrates better
with the Workflow and Taxonomy Access Control (Lite) modules. This means that
you can easily implement fine-grained content access control based on
categories as well as workflow states. With both Module Grants and Revisioning
installed this all works for both published and unpublished content.
There's also a "publish-pending-revision" action that may be triggered from
a workflow state transition (like "in review"->"publish").
Unlike RM, Revisioning does not require any additional database tables.

INSTALLATION
============
0. Install the Module Grants module. This is a package containing 4 modules.
   Although highly recommended the main module in this package is not required,
   but the Node Tools submodule is. Module Grants Monitor is also recommended,
   although Revisioning features similar functionality through a canned view
   (for which, you'll naturally have to install Views).
1. Optionally install the Diff module if you want to compare revisions and
   highlight the differences.
2. Place the "revisioning" folder in your "sites/all/modules" directory.
   Enable Revisioning under Administer >> Site building >> Modules.

CONFIGURATION
=============
3. Under Administer >> Content >> Content types, click "edit" next to the
   content types for which you wish to enable/disable revisioning. Under
   "Workflow Settings", Default Options, tick both the "Create new revision"
   and "New revision in draft, pending moderation" checkboxes. Also in this
   section UNtick "Published", so that all new content is created in an 
   unpubished state, i.e. invisible to the public.
   "New revision in draft, pending moderation" means that when a user edits and
   saves a piece of content the new revision isn't automatically made current.
   The previous copy remains unchanged and visible to the public until the 
   newer revision is published in its place.
   There is an additional radio-button on the same page that augments the above
   behaviour giving you the option to "Only create a new revision when saving
   content that is not already in draft/pending moderation". This will save you
   some disk space, because until the draft is published all modifications will
   be applied to the same copy, i.e. no new revision is created when one 
   already exists. On the other hand there are situations, for instance with a
   Wiki page with multiple authors editing the same copy, where you do want 
   every Save to create a new draft (revision), so that contributors can
   compare what was changed between saves. The Diff module is a good addition
   to Revisioning for this.
4. Revisioning builds on the Accessible content menu item (if you have enabled
   Module Grants Monitor), adding the "In draft/Pending publication" filter to
   the double row of tabs.
5. Grant to the various roles the view/delete/revert revisions permissions
   (node access section) and the "edit revisions" permission (revisioning
   section). Typically you'd give authors the "view revisions" and
   "edit revisions" permissions, while moderators will get the same as well
   as the "publish/revert revisions" permission. Neither require the 
   "administer nodes" permission, which is a good thing as this gives ordinary
   users excessive rights.

USAGE
=====
You should now be in business. Log in as one of the authors and Create content.
Save. Log out, then log in as a moderator to publish the content via the
Accessile content >> Pending tab (if you installed Module Grants Monitor) or via
the Content summary menu option (if you installed Views). Click on the title of
the post, then open the desired revision by clicking on the date. Check the
content, the press the "Publish this" tab.
Note that up to this point content isn't visible to the public.
Log in as an author again and revise the content. You will notice that upon
saving the new revision, the one visible to the public remains unchanged.
Log in as a moderator again to promote (publish), the revised content to live.
As an alternative to the Accessible content menu item, you may want to activate
the "pending revisions" block. This block is particularly useful for moderators
as it constantly shows the latest content requiring moderator attention in an 
inobtrusive corner of the screen. Configure and enable the block like any other
on the Administer >> Site building >> Blocks page.
You can use this module in combination with TAC or TAC-Lite for fine-grained
access control based on vocabularies (such as "region" or "department")
associated with the various content types. Be aware that any permissions
given in the "node module" section override those granted via TAC/TAC-Lite,
so you probably only want to assign a few creation permissions in the node
module and do the view, update and delete grants via TAC/TAC-Lite.
In addition you may want to install the Workflow module to further segragate
the author and moderator roles via access control based on states such as
"in draft", "in review" and "live". Workflow also allows you to notify users
when state transitions occur (e.g. when a moderator declines or publishes a
submitted revision).
Step-by-step guides on the usage of the Revisioning module in combination
with the TAC-Lite and Workflow modules can be found on the Revisioning project
page http://drupal.org/project/revisioning. 

AUTHOR
======
Rik de Boer, Melbourne, Australia; inspired by the Revision Moderation module.
