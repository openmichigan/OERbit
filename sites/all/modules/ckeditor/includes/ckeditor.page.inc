<?php
// $Id: ckeditor.page.inc,v 1.1.2.2 2010/01/14 08:50:08 wwalc Exp $
/**
 * CKEditor - The text editor for Internet - http://ckeditor.com
 * Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * @file
 * CKEditor Module for Drupal 6.x
 *
 * This module allows Drupal to replace textarea fields with CKEditor.
 *
 * This HTML text editor brings to the web many of the powerful functionalities
 * of known desktop editors like Word. It's really  lightweight and doesn't
 * require any kind of installation on the client computer.
 */

function ckeditor_help_delegate($path, $arg) {
  switch ($path) {
    case 'admin/settings/help#description':
      $output = t('Enables the usage of CKEditor (WYSIWYG editor) instead of plain text fields.');
      break;

    case 'admin/settings/ckeditor/edit/%':
    case 'admin/settings/ckeditor/add':
      $output = '<p>'. t('CKEditor is highly configurable. The most commonly used features are listed below. You can also customize CKEditor to your needs by changing the configuration file: %ckeditor_module_config. This is also the only way to define new toolbar sets.',
        array(
          '%ckeditor_module_config' => drupal_get_path('module', 'ckeditor') .'/ckeditor.config.js',
        )) .'</p>';
      $output .= '<p>'. t('It is advised to not edit the configuration file that is distributed with CKEditor: %ckeditor_config_file (%ckeditor_config_path) because you may overwrite it accidentally when you update the editor.',
        array(
          '%ckeditor_config_path' => drupal_get_path('module', 'ckeditor') .'/ckeditor/config.js',
          '%ckeditor_config_file' => 'config.js',
        )) .'</p>';
      break;

    case 'admin/settings/ckeditor/editg':
    case 'admin/settings/ckeditor/add':
      $output = '<p>'. t('The Global Profile allows you to define settings that are common for all profiles. Values defined in other profiles will be appended to the global configuration. This way you can avoid repeating some of the settings that are usually the same in each profile.') .'</p>';
      break;

    case 'admin/settings/ckeditor':
      $output =
        '<p>'. t('The CKEditor module allows Drupal to replace textarea fields with a rich text or !wysiwyg editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.',
          array(
            '!wysiwyg' => '<acronym title="'. t('What You See Is What You Get') .'">'. t('WYSIWYG') .'</acronym>',
          )) .'</p>'.
        '<p>'. t('More information about the editor is located at the !ckeditorlink. A small !userguidelink is available.',
          array(
            '!ckeditorlink' => l(t('CKEditor homepage'), 'http://ckeditor.com'),
            '!userguidelink' => l(t('user guide'), 'http://docs.cksource.com/FCKeditor_2.x/Users_Guide/Quick_Reference'),
          )) .'</p>'.
        '<p>'. t('Profiles can be defined based on user roles. A CKEditor profile can define which pages receive this CKEditor capability, what buttons or themes are enabled for the editor, how the editor is displayed, and a few other editor functions. It is possible also to define the Global Profile that will hold values that will be appended to all other profiles.') .'</p>'.
        '<p>'. t('Lastly, only users with the %accesspermission !permissionlink will be able to use CKEditor.',
          array(
            '%accesspermission' => t('access ckeditor'),
            '!permissionlink' => l(t('permission'), 'admin/user/permissions')
          )) .'</p>';
      break;

    case 'admin/help#ckeditor':
      $output = '<p>'. t('The CKEditor module allows Drupal to replace textarea fields with a rich text or !wysiwyg editor. This editor brings many of the powerful functionalities of known desktop editors like Word to the web. It\'s relatively lightweight and doesn\'t require any kind of installation on the client computer.',
          array(
            '!wysiwyg' => '<acronym title="'. t('What You See Is What You Get') .'">'. t('WYSIWYG') .'</acronym>',
          )) .'</p>';
      $output .= '<p>'. t('More information about the editor is located at the !ckeditorlink. A small !userguidelink is available.',
          array(
            '!ckeditorlink' => l(t('CKEditor homepage'), 'http://ckeditor.com'),
            '!userguidelink' => l(t('user guide'), 'http://docs.cksource.com/FCKeditor_2.x/Users_Guide/Quick_Reference'),
          )) .'</p>'.
      $output .= '<h3>'. t('Configuration') .'</h3>';
      $output .= '<ol>';
      $output .= '<li>'. t('Go to the !ckeditorlink and download the latest version of CKEditor. Then uncompress the contents of the ckeditor directory of the downloaded file to %ckeditordir.',
        array(
          '!ckeditorlink' => l(t('CKEditor homepage'), 'http://ckeditor.com/download'),
          '%ckeditordir' => base_path() . drupal_get_path('module', 'ckeditor') .'/ckeditor/',
        )) .'</li>';
      $output .= '<li>'. t('Enable the module as usual from Drupal\'s admin pages.') .'</li>';
      $output .= '<li>'. t('Grant permissions for use of CKEditor in !adminpath.',
        array(
          '!adminpath' => l(t('Administer') .' > '. t('User management') .' > '. t('Permissions'), 'admin/user/permissions'),
        )) .'</li>';
      $output .= '<li>'. t('Under !adminpath, adjust the ckeditor profiles. In each profile you can choose which textareas will be replaced by CKEditor, select default toolbar and configure some more advanced settings.',
        array(
          '!adminpath' => l(t('Administer') .' > '. t('Site configuration') .' > '. t('CKEditor'), 'admin/settings/ckeditor'),
        )) .'</li>';
      $output .= '<li>'. t('For the Rich Text Editing to work you also need to configure your !filterlink for the users that may access Rich Text Editing. Either grant those users Full HTML access or use the following list of tags in the HTML filter:',
        array(
          '!filterlink' => l(t('filters'), 'admin/settings/filters'),
        )) .
        '<br /><code>'. htmlspecialchars('<a> <p> <span> <div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <map> <area> <hr> <br> <br /> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <td> <em> <b> <u> <i> <strong> <font> <del> <ins> <sub> <sup> <quote> <blockquote> <pre> <address> <code> <cite> <embed> <object> <param> <strike> <caption>') .'</code><br />';
      $output .= t('If you\'re going to use CKEditor with Filtered HTML input format, please read also "Setting up filters" section in !readme',
        array(
        '!readme' => l('README.txt', drupal_get_path('module', 'ckeditor') .'/README.txt')
        )) .'</li>';
      $output .= '<li>'. t('To have a better control over line breaks, you should disable %settingname in the chosen filter (recommended).',
        array(
          '%settingname' => t('Line break converter'),
        )) .'</li>';
      $output .= '<li>'. t('Modify the %ckconfig file to your custom needs (optional). Available configuration settings are available in the !apidocs.',
        array(
          '%ckconfig' => base_path() . drupal_get_path('module', 'ckeditor') .'/ckeditor/ckeditor.config.js',
          '!apidocs' => l(t('API documentation'), 'http://docs.cksource.com/ckeditor_api/symbols/CKEDITOR.config.html')
        )) .'</li>';
      $output .= '</ol>';

      $output .= '<a name="fieldinclexcl"></a>';
      $output .= '<h3>'. t('Defining field inclusion/exclusions') .'</h3>';
      $output .= '<p>'. t('In order to specifically display CKEditor on those text areas on which you need it, the CKEditor module provides a powerfull method to define fields that should be enhanced with CKEditor. The first choice you have to make is whether you want to display CKEditor on all textareas and define a list of exceptions, or if you don\'t want to display CKEditor unless it is specifically enabled. This choice is made in the %settingname setting.',
        array(
          '%settingname' => t('Use inclusion or exclusion mode'),
        )) .'</p>';
      $output .= '<p>'. t('Next, the list of exceptions has to be defined. This list follows a specific syntax: the path to a field is defined by specifying the content type followed by @ character, specifying the path followed by dot and appending the field name at the end. You may decide to not use the content type. The field %fieldname on page %pathname would thus be addressed as %result. You can use wildcards * and ? anywhere in this line. If you have a dot in your field name and it causes problems, you can escape it with a slash (\).',
        array(
          '%fieldname' => 'edit-log',
          '%pathname' => 'node/add/page',
          '%result' => 'node/add/page.edit-log',
        )) .'</p>';

      $output .= '<strong>'. t('Some examples:') .'</strong>';
      $output .= '<ul>';
      $output .= '<li><code>node/add/page</code>: '. t('matches all fields on %pathname', array('%pathname' => 'node/add/page')) .'</li>';
      $output .= '<li><code>*.edit-log</code>: '. t('matches all fields called %fieldname on any page', array('%fieldname' => 'edit-log')) .'</li>';
      $output .= '<li><code>blog@*.edit-body</code>: '. t('matches all fields called %fieldname on pages related to node type %typename', array('%fieldname' => 'edit-body', '%typename' => 'blog')) .'</li>';
      $output .= '<li><code>forum@*.*</code>: '. t('matches all fields on pages related to node type %nodetype', array('%nodetype' => 'forum')) .'</li>';
      $output .= '<li><code>node/add/*</code>: '. t('matches all fields on pages such as %pathname1, %pathname2, etc.', array('%pathname1' => 'node/add/page', '%pathname2' => 'node/add/story')) .'</li>';
      $output .= '<li><code>node/add/*.edit-log</code>: '. t('matches all %fieldname fields on pages such as %pathname1, %pathname2, etc.', array('%fieldname' => 'edit-log', '%pathname1' => 'node/add/page', '%pathname2' => 'node/add/story')) .'</li>';
      $output .= '<li><code>node/add/*.edit-user-*</code>: '. t('matches fields starting with %fieldname on pages starting with %pathname', array('%fieldname' => 'edit-user-', '%pathname' => 'node/add/')) .'</li>';
      $output .= '</ul>';

      $output .= '<h3>'. t('Troubleshooting') .'</h3>';
      $output .= '<p>';
      $output .= t('Take a look at !listlink when installing CKEditor (or check !troubleshooting).',
        array(
          '!listlink' => l(t('the list of common problems'), 'http://drupal.ckeditor.com/troubleshooting'),
          '!troubleshooting' => l('TROUBLESHOOTING.txt', drupal_get_path('module', 'ckeditor') .'/TROUBLESHOOTING.txt')
        ));
      $output .= ' '. t('If you are looking for more information, have any trouble in configuration or if you found an issue, please visit the !officiallink.', array('!officiallink' => l(t('official project page'), 'http://drupal.org/project/ckeditor')));
      $output .= ' '. t('More information about how to tune up CKEditor for your theme can be found !herelink.', array('!herelink' => l(t('here'), 'http://drupal.fckeditor.net/tricks')));
      $output .= '</p>';

      $output .= '<h3>'. t('Uploading images and files') .'</h3>';
      $output .= '<p>'. t('There are three ways for uploading files:') .'</p>';
      $output .= '<ol>';
      $output .= '<li>'. t('By using !ckfinder (commercial).',
        array(
          '!ckfinder' => l(t('CKFinder'), 'http://ckfinder.com'),
        )) .'</li>';
      $output .= '<li>'. t('By using a module like !imcelink, !iblink or !webfmlink.',
        array(
          '!imcelink' => l(t('IMCE'), 'http://drupal.org/project/imce'),
          '!iblink' => l(t('Image Browser'), 'http://drupal.org/project/imagebrowser'),
          '!webfmlink' => l(t('Web File Manager'), 'http://drupal.org/project/webfm'),
        )) .'</li>';
      $output .= '<li>'. t('By using the core upload module.') .'</li>';
      $output .= '</ol>';

      break;
  }
  return !empty($output) ? $output : '';
}

/**
 * AJAX callback - XSS filter
 */
function ckeditor_filter_xss() {
  $GLOBALS['devel_shutdown'] = FALSE;

  if (!isset($_POST['text']) || !is_string($_POST['text']) || !is_array($_POST['filters'])) {
    exit;
  }

  $text = $_POST['text'];
  $text = strtr($text, array('<!--' => '__COMMENT__START__', '-->' => '__COMMENT__END__'));

  foreach ($_POST['filters'] as $module_delta) {
    $module = strtok($module_delta, "/");
    $delta = strtok("/");
    $format = strtok("/");

    if (!module_hook($module, 'filter')) {
      continue;
    }

    //built-in filter module, a special case where we would like to strip XSS and nothing more
    if ($module == 'filter' && $delta == 0) {
      preg_match_all("|</?([a-z][a-z0-9]*)(?:\b[^>]*)>|i", $text, $matches);
      if ($matches[1]) {
        $tags = array_unique($matches[1]);
        $text = filter_xss($text, $tags);
      }
    }
    else {
      $text = module_invoke($module, 'filter', 'process', $delta, $format, $text);
    }
  }

  $text = strtr($text, array('__COMMENT__START__' => '<!--', '__COMMENT__END__' => '-->'));

  echo $text;
  exit;
}
