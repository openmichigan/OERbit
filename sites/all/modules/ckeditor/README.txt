$Id: README.txt,v 1.3.2.6 2010/01/14 09:08:11 wwalc Exp $

CONTENTS OF THIS FILE
---------------------

 * Overview
 * Required components
 * More information and license
 * Requirements
 * Installation / Configuration
 * Installation troubleshooting
 * Plugins: Teaser break and Pagebreak
 * Plugins: MediaEmbed
 * Uploading images and files
 * How to install CKFinder
 * Modules: Link to content (EXPERIMENTAL)
 * Setting up filters
 * Upgrading instructions
 * Help & Contribution
 * Credits

Overview
--------
This module allows Drupal to replace textarea fields with the CKEditor.
This HTML text editor brings many of the powerful functions of known
desktop editors like Word to the web. It's relatively lightweight and
doesn't require any kind of installation on the client computer.

Required components
-------------------
To use CKEditor in Drupal, you will need to download the CKEditor
http://ckeditor.com/

More information and licence
----------------------------
CKEditor - The text editor for internet
Copyright (C) 2003-2010 CKSource - Frederico Knabben

Licensed under the terms of the GNU Lesser General Public License:
    http://www.opensource.org/licenses/lgpl-license.php

For further information visit:
    http://ckeditor.com/
    http://drupal.ckeditor.com

Requirements
------------
  - Drupal 6.x
  - PHP 4.3.0 or greater
  - CKEditor 3.1 or greater (http://ckeditor.com/)

Installation / Configuration
-------------------
Note: this instruction assumes that you install CKEditor in
      sites/all/modules directory (recommended).

   1. Unzip the files in the sites/all/modules directory. It should now
      contain a ckeditor directory.
   2. Download CKEditor from http://ckeditor.com/download. Unzip the
      contents of the ckeditor directory in the
      sites/all/modules/ckeditor/ckeditor directory.
      Note: you can skip uploading "_samples" and "_source" folders.
   3. Enable the module as usual from Drupal's admin pages.
   4. Grant permissions for use of CKEditor in
      "Administer > User Management > Permissions"
      Note: to enable the file browser, read also the
            "How to enable the file browser" section.
   5. Under "Administer > Site configuration > CKEditor", adjust
      the ckeditor profiles. In each profile you can choose which textareas
      will be replaced by CKEditor, select default toolbar and configure
      some more advanced settings.
   6. For the Rich Text Editing to work you also need to configure your filters
      for the users that may access Rich Text Editing.
      Either grant those users Full HTML access or use the following tags:
      <a> <p> <span> <div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <map> <area> <hr>
      <br> <br /> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <td> <em> <b> <u> <i> <strong>
      <del> <ins> <sub> <sup> <quote> <blockquote> <pre> <address> <code>
      <cite> <embed> <object> <param> <strike> <caption> <tbody>
      Fore easier usage (copying), all tags are below in one line:
      <a> <p> <span> <div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <map> <area> <hr> <br> <br /> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <td> <em> <b> <u> <i> <strong> <del> <ins> <sub> <sup> <quote> <blockquote> <pre> <address> <code> <cite> <embed> <object> <param> <strike> <caption> <tbody>
      If you're going to use CKEditor with Filtered HTML input format,
      please read also "Setting up filters" section. 
   7. To have a better control over line breaks, you may disable Line break converter
      in the chosen filter (recommended).
   8. Modify the ckeditor.config.js file to custom your needs (optional).
      Configuration options are available here: 
      http://docs.cksource.com/ckeditor_api/symbols/CKEDITOR.config.html
      Developers documentation for CKEditor:
      http://docs.cksource.com/CKEditor_3.x/Developers_Guide
      In ckeditor.config.js you may define your own toolbars with selected buttons.
      WARNING: clear browser's cache after you modify any of the javascript files.
      If you don't do this, you may notice that browser is ignoring all your changes.


Installation troubleshooting
----------------------------
If your CKEditor does not show you must check if all files are
extracted correctly.

The directory /modules/ckeditor/ckeditor/ should have the following files:
ckeditor.js, config.js, contents.css 
and directories: "skins", "themes", "lang", "images"

The correct directory structure is as follows:
modules               <dir>
   ckeditor           <dir>
      ckeditor.module
      ckeditor.admin.inc
      ...
      ckeditor        <dir>
         _source      <dir>
         images       <dir>
         lang         <dir>
         plugins      <dir>
         skins        <dir>
         themes       <dir>
         COPY_HERE.txt
         ckeditor.js
         ...

If you're still having problems, scroll down to the "Help & Contribution" section.

Plugins: Teaser break and Pagebreak
-----------------------------------
By default, CKEditor module comes with two plugins that can handle
teaser break (<!--break-->) and pagebreak (<!--pagebreak-->).
Both plugins are automatically enabled.

   1. To add 'DrupalBreak' and 'DrupalPageBreak' buttons to the toolbar,
      open sites/all/modules/ckeditor/ckeditor.config.js and add them to the toolbar 
      definition (both buttons are enabled in DrupalFiltered and DrupalFull
      toolbars by default).
      The 'DrupalBreak' button will automatically disappear from the toolbar
      on textareas where teaser cannot be created.

   2. Note that the <!--pagebreak--> tag is not supported by default in Drupal.
      You should install the Paging module: http://drupal.org/project/paging
      to enable the <!--pagebreak--> tag support. Please refer to the Paging
      module documentation for detailed installation instructions.
      If you don't install Paging module, the 'DrupalPageBreak' will automatically disappear.

Plugins: MediaEmbed
-------------------
MediaEmbed is a simple plugin that can be helpful when embedding Youtube movies (for example).
To enable it, do the following:

   1. Open /drupal/modules/ckeditor/ckeditor.config.js

   2. Uncomment the following lines (remove "//") in ckeditor.config.js:
      // config.extraPlugins += (config.extraPlugins ? ',mediaembed' : 'mediaembed' );
      // CKEDITOR.plugins.addExternal('mediaembed', Drupal.settings.ckeditor.module_path + '/plugins/mediaembed/');

   3. Add button to the toolbar. The button name is: MediaEmbed. 
      For example if you have a toolbar with an array of buttons defined as follows:

      ['Link','Unlink','Anchor']

      simply add button at the end of array (or somewhere in the middle):

      ['Link','Unlink','MediaEmbed','Anchor']

      (remember about single quotes).

Uploading images and files
--------------------------

There are three ways of uploading files: By using commercial file browser like CKFinder (http://ckfinder.com), 
by using modules like IMCE, WebFM, Image Browser or by using the core upload module.

To select preferred file browser, under "Administer > Site configuration > CKEditor", adjust 
CKEditor profiles. In each profile you can choose which file browser will be used (in "File browser settings" section).
Note: to choose IMCE, WebFM or Image Browser you should install an appropriate Drupal module first.

 How to install CKFinder
------------------------
CKFinder is an AJAX based file manager created by CKEditor developers: http://ckfinder.com/.

   1. Download CKFinder for PHP: http://ckfinder.com/download
   2. Unpack CKFinder to the directory with the CKEditor module (into sites/all/modules/ckeditor/ckfinder)
      The correct directory structure is as follows:

      modules               <dir>
         ckeditor           <dir>
            ckeditor.module
            ckeditor.admin.inc
            ...
            ckfinder        <dir>
               core         <dir>
               ckfinder.php
               config.php
               ...
            ckeditor        <dir>
               _source      <dir>
               images       <dir>
               ckeditor.js
               ...

   3. Grant "allow CKFinder file uploads" permission in "Administer > User Management > Permissions"
      Note: if you don't see such permission then it means that CKEditor didn't find CKFinder
      and you have probably uploaded CKFinder into wrong directory.
   4. Open CKFinder configuration file (sites/all/modules/ckeditor/ckfinder/config.php) and do the following:

      I) remove the CheckAuthentication() function:
        (don't worry, this function is defined in filemanager.config.php, see below)

        function CheckAuthentication()       <- remove it
        {                                    <- remove it
           //WARNING : DO NOT simply...      <- remove it
           ...                               <- remove it
           return false;                     <- remove it
        }                                    <- remove it

      II) add:

        require_once '../../../../includes/filemanager.config.php';

        straight below the following line:

        $baseDir = resolveUrl($baseUrl);

   5. Select CKFinder as preferred file browser in "Administer > Site configuration > CKEditor" 
      (in selected CKEditor profile scroll down to "File browser settings" section).
      In the "File browser settings" section you may also change destination folders for files uploaded with CKFinder.

   6. Locate file named settings.php inside your drupal directory
      (usually sites/default/settings.php) and set $cookie_domain variable to the
      appropiate domain (remember to uncomment that line). If you don't do this,
      CKFinder may show an information that the connector is disabled. 

Modules: Link to content (EXPERIMENTAL)
---------------------------------------
Link to content module can be integrated with CKEditor.
ATTENTION: this module is not yet compatible with CKEditor :(

The unofficial version of Link to content module compatible with CKEditor can be downloaded here:
     http://drupal.ckeditor.com/download/linktocontent-ckeditor-6.x-2.x-dev.zip

Installation:
Follow the instruction from INSTALL.txt attached to the linktocontent module.
Then do the following steps to add Linktocontent button to the CKEditor toolbar:

   1. Open /drupal/modules/ckeditor/ckeditor.config.js

   2. Add buttons to the toolbar. The button names are: LinkToNode, LinkToMenu. 
      For example if you have a toolbar with an array of buttons defined as follows:

      ['Link','Unlink','Anchor']

      simply add those two buttons at the end of array (or somewhere in the middle):

      ['Link','Unlink','LinkToNode','LinkToMenu','Anchor']

      (remember about single quotes).

      Both buttons are enabled in DrupalFiltered and DrupalFull toolbars by default.
      If you don't install linktocontent module, both buttons will automatically disappear from the toolbar. 

Setting up filters
------------------
In "Administer -> Input formats", Filtered HTML is the default filter. 
Due to security reasons, enabling Full HTML is only an option for trusted users.
To take the full advantage of using CKEditor you can extend the list of allowed tags in 
HTML filter that is enabled in Filtered HTML input format.
If you not do this, you may notice that created page looks different after saving it.

Unfortunately, even if you extend the list of allowed tags, there is still one problem: 
Filtered HTML not only strips disallowed tags, but also strips inline style definitions. 
Basically, it means that you are unable to apply different font color, size, family, align images etc. 
using CKEditor out of the box. You can solve this problem by creating another input format, 
that will work in a similar way like Filtered HTML (will only allow specific tags), 
but in a much better way - i.e. it will not strip inline styles that CKEditor is using when 
formatting text or images after the page is saved 
To create such input format, you'll need a so-called filter. Below are listed three 
the most popular modules that provide HTML filter: 

 - WYSIWYG Filter - seems to be the easiest to install, does not require third-party libraries
   http://drupal.org/project/wysiwyg_filter
 - HTML Purifier - the most popular and powerful, although some people claim that it might be a bit slow
   http://drupal.org/project/htmlpurifier
 - htmLawed - another alternative, less popular than both modules above
   http://drupal.org/project/htmLawed

It's up to you which one you decide to use. Just make sure that you'll allow to use only proper 
inline styles, tags and attributes.
See also http://drupal.ckeditor.com/filters for the latest version of this instruction.

Upgrading instructions (migration from FCKeditor)
-------------------------------------------------
   During the installation, CKEditor will check for the existence of FCKeditor module and 
   copy all FCKeditor settings, profiles etc. (to save your time, just disable FCKeditor module 
   during CKEditor installation, if you uninstall FCKeditor module before installing CKEditor, 
   all FCKeditor settings will be deleted from the database and CKEditor will not copy them).
   After installing CKEditor you may uninstall FCKeditor module.

   If both modules are enabled (CKEditor and FCKeditor) you may get javascript errors, if both editors
   will try to attach to the same textarea, be sure that's not a problem if you have problems after upgrading.

   Apart from the information above, installing CKEditor is just like installing a new module,
   so be sure to follow the installation instruction.

Upgrading instructions (CKEditor)
---------------------------------
This instruction assumes that you are upgrading CKEditor module [M] and CKEditor (the editor)[E] at the same time. 
Instructions specific for module upgrades are tagged with [M], steps that must be taken when upgrading CKEditor (the editor) are marked with [E].

   1. [M] Download the latest version of CKEditor module from http://drupal.org/project/ckeditor (it is advised to read release notes before going further).
   2. [E] Download the latest version of CKEditor from http://ckeditor.com/download (it is advised to read "what's new" before going further: http://ckeditor.com/whatsnew).
   3. [M] Back up your database.
   4. [EM] Place the site in "Off-line" mode, to let the database updates run without interruption and avoid displaying errors to end users of the site.
   5. [E] If you are using CKFinder, make sure you'll not delete it, move it into a safe place.
   6. [E] If you have made any changes inside of sites/all/modules/ckeditor/ckeditor.config.js (or sites/all/modules/ckeditor/ckeditor/config.js), write down your changes and add them again after uploading new files (e.g. own toolbar definitions etc.). 
          Try to not make any changes to CKEditor's config.js and add everything to ckeditor.config.js.
   7. Delete old files:
      [EM]* Simply remove modules/ckeditor directory if upgrading both, the editor and the module. 
      [M] If you are upgrading module only, remember to leave the modules/ckeditor/ckeditor directory. 
      [E] When upgrading the editor, remove contents of modules/ckeditor/ckeditor directory only.
      WARNING: if you don't remove old files and just rename ckeditor directory instead e.g. to ckeditor_old, Drupal may use module from the ckeditor_old directory.
   8. [M] Upload CKEditor module (extracted files and folders) to sites/all/modules directory.
   9. [E] Upload CKEditor (extracted files and folders from the ckeditor directory) to sites/modules/ckeditor/ckeditor (i.e. where COPY HERE.txt file exists)
   10. [E] Copy back CKFinder (see step 5)
   11. [E] Apply your modifications to default configuration in ckeditor.config.js file (see step 6).
   12. [M] Run update.php.
   13. [EM] Put the site back online.
   
Help & Contribution
-------------------
If you are looking for more information, have any troubles in configuration or if
you found an issue, please visit the official project page:
  http://drupal.org/project/ckeditor

Having problems? Take a look at the list of common problems when installing CKEditor:
  http://drupal.ckeditor.com/troubleshooting

How to tune up CKEditor to your theme and configure spell checker:
  http://drupal.ckeditor.com/tricks

We would like to encourage you to join our team if you can help in any way.
If you can translate CKEditor module, please use ckeditor.pot file as a template
(located in "translations" directory) and send us the translated file so that we could attach it.
Any help is appreciated.

Credits
-------
 - CKEditor for Drupal is currently maintained by CKEditor team and Jorrit Schippers.
     http://ckeditor.com/

 - CKEditor - The text editor for internet
     Copyright (C) 2003-2009 CKSource - Frederico Knabben
     http://cksource.com/
