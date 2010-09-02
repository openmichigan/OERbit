Accessible Content is a early-phase development module. Don't use this on a production site!

INSTALLATION
------------

You MUST download and install the QUAIL accessiblity library before you can install this module. Go to http://code.google.com/p/quail-lib/ and download the latest release. Rename the folder (i.e. "quail-lib-xxx") to "quail" and then move it into the directory "sites/all/libraries" so that the library is available at "sites/all/libraries/quail/quail/quail.php.

Installation is the same as any Drupal module. 

When you first enable this module, it will create two content types: accessibility_guideline and accessibility_test. It will then create roughly 250 accessibility_test nodes, so be prepared. Each node is related to a test supported by QUAIL.

You should probably first create a node of type accessibility_guideline and associate it with a few tests. In the future, we will probably need to provide a set of guidelines to begin with like WCAG 1 and 2, 508, etc.

Each test can be edited to change the tips users get when they get an error.

ENABLING CHECKING
-----------------
You enable accessibility testing on a per-content-type basis. Just go to the edit form for your content type, say, Page, and then look at the options for Accessibility Checks. You can select the guideline to use, whether to prevent people from submitting a node if there are severe errors, and enable/disable checking.

If you have CCK installed, you can also enable or disable checking for text fields within that field's form.

THE BLOCK
---------
There's a block called "Accessibility Overview" that will give stats for the currently viewed node and link to the accessibility overview and highlighted view page. The highlighted view has some accessibility problems itself that I'm trying to work out.

ACCESSIBILITY SERVICE
---------------------
This module lets you expose accessibility checking as a service, so people can submit content and have it run against a predetermined guideline. It requires the 'Services' module.

ACCESSBILITY THEMER
-------------------
This is a little module that lets you set the default guideline to use for checking your themes, and then gives you a floating link in the lower right (for appropriately permission users) to view an entire page's accessibility problems. This is much more useful for development and themeing environments, probably not a good idea to leave this on a production site.

