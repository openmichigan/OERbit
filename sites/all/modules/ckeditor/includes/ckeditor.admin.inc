<?php
// $Id: ckeditor.admin.inc,v 1.2.2.14 2010/03/11 12:39:54 wwalc Exp $
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

/**
 * Main administrative page
 */
function ckeditor_admin_main() {
  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');
  $editor_path = ckeditor_path(TRUE);
  $ckconfig_file = $editor_path .'/config.js';
  if (!_ckeditor_requirements_isinstalled()) {
    drupal_set_message(t('Checking for %filename or %file.', array('%filename' => $ckconfig_file, '%file' => 'sites/all/libraries/ckeditor/ckeditor.js')));
    drupal_set_message(t('The CKEditor component is not installed correctly. Please go to the <a href="!ckeditorlink">CKEditor homepage</a> to download the latest version. After that you must extract the files to %ckeditorpath or %librarypath and make sure that the file %ckeditorfile or %ckeditorlibrary exist. Refer to the <a href="!readme">readme.txt</a> for more information.', array('!ckeditorlink' => url('http://ckeditor.com/download'), '!readme' => url('admin/help/ckeditor'), '%ckeditorpath' => $editor_path, '%ckeditorsubdir' => $editor_path .'/editor', '%ckeditorfile' => $editor_path .'/ckeditor.js', '%ckeditorlibrary' => 'sites/all/libraries/ckeditor/ckeditor.js', '%librarypath' => 'sites/all/libraries/ckeditor')), 'error');
    drupal_set_message(t('If you have CKEditor already installed please edit <a href="!editg">CKEditor Global Profile</a> and update CKEditor path.', array('!editg' => url('admin/settings/ckeditor/editg'))), 'warning');
    return FALSE;
  }

  $access_ckeditor_roles = user_roles(FALSE, 'access ckeditor');
  if (!$access_ckeditor_roles) {
    drupal_set_message(t('There is currently no role with the "access ckeditor" permission. Visit <a href="!acl">permissions</a> administration section.', array('!acl' => url('admin/user/permissions'))), 'warning');
  }
  else {
    $result = db_query_range("SELECT name FROM {ckeditor_settings} WHERE name<>'CKEditor Global Profile'", 0, 1);
    $has_profiles = FALSE;
    //find profile other than Global
    if (($obj = db_fetch_object($result))) {
      $has_profiles = TRUE;
    }

    //find roles with profiles
    $result = db_query("SELECT rid FROM {ckeditor_role}");
    $rids = array();
    while (($obj = db_fetch_object($result))) {
        $rids[] = $obj->rid;
    }
    $rids = array_unique($rids);
    if (!$has_profiles) {
      drupal_set_message(t('No CKEditor profiles found. At this moment, nobody is able to use CKEditor. Create new profile below.'), 'error');
    }
    else {
      //not all roles with access ckeditor has their CKEditor profile assigned
      $diff = array_diff(array_keys($access_ckeditor_roles), $rids);
      if ($diff) {
        $list = "<ul>";
        foreach ($diff as $rid) {
          $list .= "<li>". $access_ckeditor_roles[$rid] ."</li>";
        }
        $list .= "</ul>";
        drupal_set_message(t('Not all roles with <a href="!access">access ckeditor</a> permission are associated with CKEditor profiles. As a result, users having the following roles may be unable to use CKEditor: !list Create new or edit CKEditor profiles below and in the <em>Basic setup</em> section, check "Roles allowed to use this profile".', array('!access' => url('admin/user/permissions'), '!list' => $list)), 'warning');
      }
    }
  }

  return ckeditor_profile_overview();
}

/**
 * Controller for ckeditor profiles.
 */
function ckeditor_profile_overview() {
  $output = '';

  $profiles = ckeditor_profile_load();
  if ($profiles) {
    $access_ckeditor_roles = user_roles(FALSE, 'access ckeditor');
    $header = array(t('Profile'), t('Roles'), t('Operations'));
    foreach ($profiles as $p) {
      $rids = $p->rids;
      if ($p->name !== "CKEditor Global Profile") {
        foreach (array_keys($p->rids) as $rid) {
          if (!isset($access_ckeditor_roles[$rid])) {
            unset($rids[$rid]);
          }
        }
        $rows[] = array(
          array('data' => $p->name, 'valign' => 'top'),
          array('data' => implode("<br />\n", $rids)),
          array('data' =>
            l(t('edit'), 'admin/settings/ckeditor/edit/'. urlencode($p->name)) .' '.
            l(t('clone'), 'admin/settings/ckeditor/clone/'. urlencode($p->name)) .' '.
            l(t('delete'), 'admin/settings/ckeditor/delete/'. urlencode($p->name)), 'valign' => 'top'
          )
        );
      }
    }
    $output .= '<h3>'. t('Profiles') .'</h3>';
    $output .= theme('table', $header, $rows);
    $output .= '<p>'. l(t('Create new profile'), 'admin/settings/ckeditor/add') .'</p>';
  }
  else {
    drupal_set_message(t('No profiles found. Click here to <a href="!create">create a new profile</a>.', array('!create' => url('admin/settings/ckeditor/add'))));
  }

  $rows = array();
  if (!isset($profiles['CKEditor Global Profile'])) {
    drupal_set_message(t('Global profile not found. Click here to <a href="!create">create the global profile</a>.', array('!create' => url('admin/settings/ckeditor/addg'))));
  }
  else {
    $output .= "<h3>". t("Global settings") ."</h3>";
    $rows[] = array(
      array('data' => t('CKEditor Global Profile'), 'valign' => 'top'),
      array('data' => l(t('edit'), 'admin/settings/ckeditor/editg') ." ". l(t('delete'), 'admin/settings/ckeditor/delete/CKEditor Global Profile'), 'valign' => 'top')
    );
    $output .= theme('table', array(t('Profile'), t('Operations')), $rows);
  }
  return $output;
}

/**
 * Clone profile
 */
function ckeditor_admin_profile_clone_form($form_state, $oldprofile) {
  return ckeditor_admin_profile_form($form_state, $oldprofile);
}

function ckeditor_admin_profile_clone_form_validate($form_state, $oldprofile) {
  ckeditor_admin_profile_form_validate($form_state, $oldprofile);
}

function ckeditor_admin_profile_clone_form_submit($form, &$form_state) {
  $edit =& $form_state['values'];
  drupal_set_message(t('Your CKEditor profile has been created.'));
  $settings = ckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {ckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  ckeditor_rebuild_selectors($edit['name']);
  if (!empty($edit['rids'])) {
    foreach (array_keys($edit['rids']) as $rid) {
      if ($edit['rids'][$rid]!=0) {
        db_query("INSERT INTO {ckeditor_role} (name, rid) VALUES ('%s', %d)", $edit['name'], $rid);
      }
    }
  }
  $form_state['redirect'] = 'admin/settings/ckeditor';
}

/**
 * Form builder for a normal profile
 */
function ckeditor_admin_profile_form($form_state, $profile = NULL) {
  global $theme;
  if ($profile != NULL) {
    $form['_profile'] = array(
      '#type' => 'value',
      '#value' => $profile,
    );
  }
  else {
    $profile = new stdClass();
  }

  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');

  $toolbar_options = ckeditor_load_toolbar_options();
  $skin_options = ckeditor_load_skin_options();
  $lang_options = ckeditor_load_lang_options();

  // Only display the roles that currently don't have a ckeditor profile. One
  // profile per role.
  $orig_roles = user_roles(FALSE, 'access ckeditor');
  $roles = $orig_roles;

  if (!empty($profile->rids) && !user_roles(FALSE, 'access ckeditor')) {
    drupal_set_message(t('You haven\'t assigned "access ckeditor" <a href="!permissions">permissions</a> yet. It is recommended to assign the "access ckeditor" <a href="!permissions">permissions</a> before updating CKEditor profiles.', array('!permissions' => url('admin/user/permissions'))), 'warning');
  }

  if (empty($profile->name)) {
    $result = db_query("SELECT DISTINCT(rid) FROM {ckeditor_role}");
    while (($data = db_fetch_object($result))) {
      if ((empty($profile->rids) || !in_array($data->rid, array_keys((array) $profile->rids))) && !form_get_errors()) {
        unset($roles[$data->rid]);
      }
    }
    if (count($orig_roles) != count($roles)) {
      drupal_set_message(t('Not all user roles are shown since they already have ckeditor profiles. You must first unassign profiles in order to add them to a new one.'));
    }
  }

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  if (arg(3) == 'clone') {
    //load all profiles to check their names
    $profiles = ckeditor_profile_load();
    $oldname = $profile->name;
    $maxsize=128;   //default max name length

    $res=array();
    $pat = "/^(.*?)_([0-9]+)$/";
    if (preg_match($pat, $oldname, $res)) {     // oldname like 'name_nr'
      $name=$res[1];
      $num=$res[2]+1;
    }
    else{
      $name=$oldname;
      $num=2;
    }

    $newname=substr($name, 0, $maxsize-3) .'_'. $num;   // +limit
    while (isset($profiles[$newname])) {            //find next free number
      $num++;
      $newname=substr($name, 0, $maxsize-3) .'_'. $num;

    }
    //dont clone rids
    $profile->settings['rids']=array();
    $profile->rids=array();
  }
  else {
    $newname = $profile->name;
  }

  $form['basic']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile name'),
    '#default_value' => !empty($profile->name) ? $newname : '',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('Enter a name for this profile. This name is only visible within the ckeditor administration page.'),
    '#required' => TRUE
  );

  $form['basic']['rids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles allowed to use this profile'),
    '#default_value' => !empty($profile->rids) ? array_keys((array) $profile->rids) : array(),
    '#options' => $roles,
    '#description' =>  t('Only roles with "access ckeditor" permission will be shown here. If no role is available, make sure that you have assigned the "access ckeditor" <a href="!permission">permission</a>.', array('!permission' => url('admin/user/permissions'))),
    '#required' => TRUE
  );

  $form['basic']['allow_user_conf'] = array(
    '#type' => 'radios',
    '#title' => t('Allow users to customize CKEditor appearance'),
    '#default_value' => !empty($profile->settings['allow_user_conf']) ? $profile->settings['allow_user_conf'] : 'f',
    '#options' => array(
      'f' => t('No'),
      't' => t('Yes')
    ),
    '#description' => t('If allowed, users will be able to override the "Editor appearance" by visiting their profile page.'),
  );

  $form['security'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security'),
    '#description' => '<p>'. t('The CKEditor security system protects you from executing malicious code that is already in your database. In plain text areas database content is harmless because it is not executed, but the CKEditor WYSIWYG editor evaluates HTML like a web browser and content needs to be filtered before it is loaded.') .'</p>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $all = filter_list_all();

  $form['security']['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security filters'),
    '#description' => t('Please choose carefully all filters that protect your content (probably not all filters listed below are security filters).'),
    '#tree' => TRUE,
  );

  //don't bother administrator with filters that definitely are not security filters
  $modules_with_filters_to_skip = array('amazon_filter', 'asy', 'bbcode', 'biblio', 'blockquote', 'bookpost', 'chessboard', 'citation_filter', 'codefilter', 'collapse_text', 'contextlinks', 'coolfilter', 'dialectic', 'dript', 'dme', 'drutex', 'embedfilter', 'ext_link_page', 'extlink', 'elf', 'flickr', 'flickrstickr', 'footnotes', 'formdefaults', 'freelinking', 'gallery', 'geogebra', 'geshifilter', 'gotwo', 'googtube', 'gotcha', 'gtspam', 'hidden_content', 'img_assist', 'image_filter', 'imagebrowser', 'inlinetags', 'insert_view', 'insertframe', 'insertnode', 'interwiki', 'jlightbox', 'jsmath', 'language_sections', 'link_node', 'lootz', 'markdown', 'marksmarty', 'mobile_codes', 'mykml', 'nofollowlist', 'oagwt', 'paging', 'pathfilter', 'pearwiki_filter', 'php', 'pirate', 'reptag', 'scrippet', 'scripturefilter', 'signwriter', 'slideshowpro', 'smartlinebreakconverter', 'smartypants', 'smileys', 'spamspan', 'spam_tokens', 'spoiler', 'table_altrow', 'tablemanager', 'tableofcontents', 'textile', 'tooltips', 'twikifilter', 'typogrify', 'unwrap', 'urlclass', 'urlicon', 'url_replace_filter', 'username_highlighter', 'video_filter', 'quote');

  if (!isset($profile->settings['ss'])) {
    $profile->settings['filters']['filter/0'] = 1;
  }

  foreach ($all as $id => $filter) {
    if (in_array(strtolower($filter->module), $modules_with_filters_to_skip)) {
      continue;
    }
    //skip line break converter and email -> link
    if ($filter->module == 'filter' && in_array($filter->delta, array(1, 2))) {
      continue;
    }
    $form['security']['filters'][$id] = array(
      '#type' => 'checkbox',
      '#title' => $filter->name,
      '#default_value' => !empty($profile->settings['filters'][$id]),
      '#description' => module_invoke($filter->module, 'filter', 'description', $filter->delta),
    );
  }

  $form['security']['ss'] = array(
    '#type' => 'radios',
    '#title' => t('Security settings'),
    '#default_value' => isset($profile->settings['ss']) ? $profile->settings['ss'] : '2',
    '#options' => array(
      '2' => t('Always run security filters for CKEditor.'),
      '1' => t('Run security filters only when CKEditor is set to start automatically.'),
    ),
    '#description' => t('There are two ways of starting CKEditor: automatically and manually (via toggle or in a popup). If you decide to apply security filters only when CKEditor starts automatically, you will not be protected when toggling manually from plain text area to CKEditor or when using CKEditor in a popup mode. So choose this option only, if you can detect various attacks (mainly XSS) by yourself just by looking at the HTML code.'),
  );

  $form['ckeditor_exclude_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('The following settings are combined with the visibility settings of the global profile.'),
  );

  $form['ckeditor_exclude_settings']['min_rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum rows'),
    '#default_value' => !empty($profile->settings['min_rows']) ? $profile->settings['min_rows'] : '5',
    '#description' => t("CKEditor will be triggered if the textarea has more rows than entered here. Enter '1' if you do not want to use this feature."),
  );

  $form['ckeditor_exclude_settings']['excl_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Use inclusion or exclusion mode'),
    '#default_value' => (empty($profile->settings['excl_mode']) || in_array($profile->settings['excl_mode'], array(0, 2))) ? 0 : 1,
    '#options' => array(
      '0' => t('Exclude'),
      '1' => t('Include')
    ),
    '#description' => t('Choose the way of disabling/enabling CKEditor on selected fields/paths (see below). Use exclude to disable CKEditor on selected fields/paths. Use include if you want to load CKEditor only on selected paths/fields.'),
  );

  /**
   * get excluded fields - so we can have normal textareas too
   * split the phrase by any number of commas or space characters,
   * which include " ", \r, \t, \n and \f
   */
  $form['ckeditor_exclude_settings']['excl'] = array(
    '#type' => 'textarea',
    '#title' => t('Fields to exclude/include'),
    '#cols' => 60,
    '#rows' => 5,
    '#prefix' => '<div style="margin-left:20px">',
    '#suffix' => '</div>',
    '#default_value' => !empty($profile->settings['excl']) ? $profile->settings['excl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to enable or disable CKEditor.') .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Short instruction is available below.', array('!helppagelink' => url('admin/help/ckeditor', array('fragment' => 'fieldinclexcl')))) .' <ul><li>'. t('Path structure: <strong>content_type@path.element_id</strong>') .'</li><li>'. t('The following wildcards are available: "*", "?".') .'</li><li>'. t('Content type is optional. You may even specify only path or field id.') .'</li><li>'. t('Examples:') .'<ul><li><em>blog@*.edit-body</em> - '. t('matches all fields of type "blog" called edit-body, on any page.') .'<li><em>node/add/*.edit-user-*</em> - '. t('matches fields starting with "edit-user-" on pages starting with "node/add/') .'</li></ul></li></ul>',
    '#wysiwyg' => FALSE,
  );

  $form['ckeditor_exclude_settings']['simple_incl'] = array(
    '#type' => 'textarea',
    '#title' => t('Force simplified toolbar on the following fields'),
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => !empty($profile->settings['simple_incl']) ? $profile->settings['simple_incl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to force the simplified toolbar (!name).', array('!name' => CKEDITOR_FORCE_SIMPLE_TOOLBAR_NAME)) .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Take a look at the exclusion settings (above) for short instruction.', array('!helppagelink' => url('admin/help/ckeditor', array('fragment' => 'fieldinclexcl')))),
    '#wysiwyg' => FALSE,
  );

  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Editor appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['appearance']['default'] = array(
    '#type' => 'radios',
    '#title' => t('Default state'),
    '#default_value' => !empty($profile->settings['default']) ? $profile->settings['default'] : 't',
    '#options' => array(
      't' => t('Enabled'),
      'f' => t('Disabled')
    ),
    '#description' => t('Default editor state. If disabled, rich text editor may still be enabled using toggle or popup window.'),
  );

  $form['appearance']['show_toggle'] = array(
    '#type' => 'radios',
    '#title' => t('Show disable/enable rich text editor toggle'),
    '#default_value' => !empty($profile->settings['show_toggle']) ? $profile->settings['show_toggle'] : 't',
    '#options' => array(
      't' => t('Show'),
      'f' => t('Hide')
    ),
    '#description' => t('Whether or not to show the disable/enable rich text editor toggle below the textarea. Works only if CKEditor is not running in a popup window (see below).'),
  );

  $form['appearance']['popup'] = array(
    '#type' => 'radios',
    '#title' => t('Use CKEditor in a popup window'),
    '#default_value' => !empty($profile->settings['popup']) ? $profile->settings['popup'] : 'f',
    '#options' => array(
      'f' => t('No'),
      't' => t('Yes')
    ),
    '#description' => t('If this option is enabled a link to a popup window will be used instead of a textarea replace.'),
  );

  $form['appearance']['skin'] = array(
    '#type' => 'select',
    '#title' => t('Skin'),
    '#default_value' => !empty($profile->settings['skin']) ? $profile->settings['skin'] : 'default',
    '#options' => $skin_options,
    '#description' => t('Choose a default skin.'),
  );

  $ui_colors = array(
  "default" => t('CKEditor default'),
  "custom" => t('Select manually')
  );
  if (function_exists('color_get_palette')) {
    // apparently $theme is not initialized (?)
    if (empty($theme)) {
      init_theme();
    }
    $palette = @color_get_palette($theme, FALSE); //[#652274]
    $color_palette['default'] = '#D3D3D3';
    if (!empty($palette)) {
      if (!empty($palette['base'])) {
        $color_palette['color_base'] = $palette['base'];
        $ui_colors["color_base"] = t('Color module: base');
      }
      if (!empty($palette['top'])) {
        $color_palette['color_top'] = $palette['top'];
        $ui_colors["color_top"] = t('Color module: top');
      }
      if (!empty($palette['bottom'])) {
        $color_palette['color_bottom'] = $palette['bottom'];
        $ui_colors["color_bottom"] = t('Color module: bottom');
      }
    }
    drupal_add_js(array('ckeditor_uicolor' => $color_palette), 'setting');
  }

  $editor_path = ckeditor_path(FALSE);
  $module_drupal_path = drupal_get_path('module', 'ckeditor');
  drupal_add_js($module_drupal_path .'/includes/ckeditor.admin.js');
  drupal_set_html_head('<script type="text/javascript" src="'. $editor_path .'/ckeditor.js?I"></script>');

  $form['appearance']['uicolor'] = array(
    '#type' => 'select',
    '#title' => t('User Interface color'),
    '#default_value' => !empty($profile->settings['uicolor']) ? $profile->settings['uicolor'] : 'default',
    '#options' => $ui_colors,
    '#description' => t('Works only with "!skin" skin.',
      array(
        '!skin' => 'Kama'
      )),
    );
  $form['appearance']['uicolor_textarea'] = array(
    '#type' => 'textarea',
    '#title' => '',
    '#default_value' => 'Click on the <strong>UI Color Picker</strong> button to set your color preferences.',
    '#attributes' => array('style' => 'display:none', 'class' => 'ckeditor_ui_demo'),
    '#resizable' => FALSE,
    '#wysiwyg' => FALSE
  );
  $form['appearance']['uicolor_user'] = array(
    '#type' => 'hidden',
    '#default_value' => !empty($profile->settings['uicolor_user']) ? $profile->settings['uicolor_user'] : 'default',
  );

  $form['appearance']['toolbar'] = array(
    '#type' => 'select',
    '#title' => t('Toolbar'),
    '#default_value' => !empty($profile->settings['toolbar']) ? $profile->settings['toolbar'] : 'default',
    '#options' => $toolbar_options,
    '#description' => t('Choose a default toolbar set. To define new toolbar, edit "ckeditor.config.js" located in "!module_path".', array('!module_path' => drupal_get_path('module', 'ckeditor'))),
  );

  $form['appearance']['expand'] = array(
    '#type' => 'radios',
    '#title' => t('Start the toolbar expanded'),
    '#default_value' => !empty($profile->settings['expand']) ? $profile->settings['expand'] : 't',
    '#options' => array(
      't' => t('Expanded'),
      'f' => t('Collapsed')
    ),
    '#description' => t('The toolbar start expanded or collapsed.'),
  );

  $form['appearance']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => !empty($profile->settings['width']) ? $profile->settings['width'] : '100%',
    '#description' => t("Width in pixels or percent. Example: 400 or 100%."),
    '#size' => 40,
    '#maxlength' => 128,
  );

  $form['appearance']['lang'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#default_value' => !empty($profile->settings['lang']) ? $profile->settings['lang'] : 'en',
    '#options' => $lang_options,
    '#description' => t('The language for the CKEditor interface.')
  );

  $form['appearance']['auto_lang'] = array(
    '#type' => 'radios',
    '#title' => t('Auto-detect language'),
    '#default_value' => !empty($profile->settings['auto_lang']) ? $profile->settings['auto_lang'] : 't',
    '#options' => array(
      't' => t('Enabled'),
      'f' => t('Disabled')
    ),
    '#description' => t('Use auto detect user language feature.')
  );

  $form['appearance']['language_direction'] = array(
    '#type' => 'select',
    '#title' => t('Language Direction'),
    '#default_value' => !empty($profile->settings['language_direction']) ? $profile->settings['language_direction'] : 'default',
    '#options' => array(
      'default' => t('Get from current locale (default)'),
      'ltr' => t('Left-To-Right'),// language (like English)
      'rtl' => t('Right-To-Left') // languages (like Arabic)
    ),
    '#description' => t('Choose language direction used in the editing area. Even when CKEditor auto detects user language and adjusts it\'s user interface, the editing area is not automatically changed into LTR or RTL mode. To be able to type LTR (like English) and RTL (like Arabic, Hebrew, Persian) content at the same time, please take a look at the <b>Styles</b> combo and <b>Language: RTL</b>, <b>Language: LTR</b> styles available there. Note: this combo box is not available in the default toolbar, the <b>Styles</b> button needs to be added to the toolbar in ckeditor.config.js.')
  );

  $form['output'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cleanup and output'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['output']['enter_mode'] = array(
    '#type' => 'select',
    '#title' => t('Enter mode'),
    '#default_value' => !empty($profile->settings['enter_mode']) ? $profile->settings['enter_mode'] : 'p',
    '#options' => array(
      'p' => '<p>',
      'br' => '<br>',
      'div' => '<div>'
    ),
    '#description' => t('Set which tag CKEditor should use when [Enter] key is pressed.')
  );

  $form['output']['shift_enter_mode'] = array(
    '#type' => 'select',
    '#title' => t('Shift + Enter mode'),
    '#default_value' => !empty($profile->settings['shift_enter_mode']) ? $profile->settings['shift_enter_mode'] : 'br',
    '#options' => array(
      'p' => '<p>',
      'br' => '<br>',
      'div' => '<div>'
    ),
    '#description' => t('Set which tag CKEditor should use when [Shift] + [Enter] is pressed.')
  );

  $form['output']['font_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Font formats'),
    '#default_value' => !empty($profile->settings['font_format']) ? $profile->settings['font_format'] : 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
    '#size' => 40,
    '#maxlength' => 250,
    '#description' => t('Semicolon separated list of HTML font formats. Allowed values are: p;div;pre;address;h1;h2;h3;h4;h5;h6'),
  );

  if (!empty($profile->settings['formatting']['custom_formatting_options']))
  foreach( $profile->settings['formatting']['custom_formatting_options'] as $k => $v ) {
    if ($v === 0) {
      unset($profile->settings['formatting']['custom_formatting_options'][$k]);
    }
  }

  $form['output']['custom_formatting'] = array(
    '#type' => 'radios',
    '#title' => t('Use custom formatting options'),
    '#default_value' => !empty($profile->settings['custom_formatting']) ? $profile->settings['custom_formatting'] : 'f',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No'),
    ),
  );

  $form['output']['formatting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom formatting options'),
    '#tree' => TRUE,
  );

  $form['output']['formatting']['custom_formatting_options'] = array(
    '#type' => 'checkboxes',
    '#default_value' => !empty($profile->settings['formatting']['custom_formatting_options']) ? array_keys((array) $profile->settings['formatting']['custom_formatting_options']) : array('indent' => 'indent', 'breakBeforeOpen' => 'breakBeforeOpen', 'breakAfterOpen' => 'breakAfterOpen', 'breakAfterClose' => 'breakAfterClose'),
    '#options' => array(
      'indent' => t('indent the element contents'),
      'breakBeforeOpen' => t('break line before the opener tag'),
      'breakAfterOpen' => t('break line after the opener tag'),
      'breakBeforeClose' => t('break line before the closer tag'),
      'breakAfterClose' => t('break line after the closer tag'),
      'pre_indent' => t('indent the &lt;pre&gt; element contents'),
    ),
  );

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $form['css']['css_mode'] = array(
    '#type' => 'select',
    '#title' => t('Editor CSS'),
    '#default_value' => !empty($profile->settings['css_mode']) ? $profile->settings['css_mode'] : 'theme',
    '#options' => array(
      'theme' => t('Use theme css'),
      'self' => t('Define css'),
      'none' => t('CKEditor default')
    ),
    '#description' => t('Defines the CSS to be used in the editor area.<br />Use theme css - load style.css from current site theme.<br/>Define css - enter path for css file below.<br />CKEditor default - uses default CSS from editor.')
  );

  $form['css']['css_path'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS path'),
    '#default_value' => !empty($profile->settings['css_path']) ? $profile->settings['css_path'] : "",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Enter path to CSS file (Example: !example1) or a list of css files separated by a comma (Example: !example2). Make sure to select "Define css" above.',
      array(
        '!example1' => '"css/editor.css"',
        '!example2' => '"/themes/garland/style.css,http://example.com/style.css"',
      )) .
      '<br />'.
      t('Available placeholders:!h - host name (!host).!t - path to theme (!theme).',
        array(
        '!h' => '<br /><strong>%h</strong>',
        '!t' => '<br /><strong>%t</strong>',
        '!host' => base_path(),
        '!theme' => base_path() . path_to_theme() .'/'
        ))
  );

  $form['css']['css_style'] = array(
    '#type' => 'select',
    '#title' => t('Predefined styles'),
    '#default_value' => !empty($profile->settings['css_style']) ? $profile->settings['css_style'] : 'theme',
    '#options' => array(
      'theme' => t('Use theme ckeditor.styles.js'),
      'self' => t('Define path to ckeditor.styles.js'),
      'default' => t('CKEditor default')
    ),
    '#description' => t('Define the location of "ckeditor.styles.js" file. It is used by the "Style" dropdown list available in the default toolbar. Copy "!ckeditor.styles.js" inside your theme directory ("!theme") and adjust it to your needs.', array('!ckeditor.styles.js' => ckeditor_path(TRUE) .'/ckeditor.styles.js', '!theme' => path_to_theme() .'/ckeditor.styles.js'))
  );

  $form['css']['styles_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Predefined styles path'),
    '#default_value' => !empty($profile->settings['styles_path']) ? $profile->settings['styles_path'] : "",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Enter path to a file with predefined styles (Example: "!example1"). Be sure to select "define path to ckeditor.styles.js" above.',
      array(
        '!example1' => '/ckeditor.styles.js'
      )) .
      '<br />'.
      t('Available placeholders:!h - host name (!host).!t - path to theme (!theme).!m - path to CKEditor module (!module).',
      array(
        '!h' => '<br /><strong>%h</strong>',
        '!t' => '<br /><strong>%t</strong>',
        '!m' => '<br /><strong>%m</strong>',
        '!host' => base_path(),
        '!theme' => base_path() . path_to_theme() .'/',
        '!module' => drupal_get_path('module', 'ckeditor'))
      )
  );

  $form['ckeditor_upload_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('File browser settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Set file browser settings. A file browser will allow you to explore the files contained on the server and embed them as links, images or flash movies. CKEditor is compatible with contributed modules like <a href="!imce">IMCE</a>, <a href="!ib">Image Browser</a> or <a href="!webfm">Web File Manager</a>. CKEditor can be also integrated with <a href="!ckfinder">CKFinder</a>.', array('!imce' => url('http://drupal.org/project/imce'), '!ib' => url('http://drupal.org/project/imagebrowser'), '!webfm' => url('http://drupal.org/project/webfm'), '!readme' => url('admin/help/ckeditor'), '!ckfinder' => url('http://ckfinder.com')))
  );

  $filebrowsers = array(
    'none' => t('None'),
    'ckfinder' => t('CKFinder'),
  );

  $filebrowsers_dialogs = array(
    '' => t('Same as in Link dialog'),
    'ckfinder' => t('CKFinder'),
  );

  if (module_exists('imce')) {
    $filebrowsers['imce'] = t('IMCE');
    $filebrowsers_dialogs['imce'] = t('IMCE');
  }

  if (module_exists('tinybrowser')) {
    $filebrowsers['tinybrowser'] = t('TinyBrowser');
    $filebrowsers_dialogs['tinybrowser'] = t('TinyBrowser');
  }

  if (module_exists('imagebrowser')) {
    $filebrowsers['ib'] = t('Image Browser');
    $filebrowsers_dialogs['ib'] = t('Image Browser');
  }

  if (module_exists('webfm_popup')) {
    $filebrowsers['webfm'] = t('Web File Manager');
    $filebrowsers_dialogs['webfm'] = t('Web File Manager');
  }

  $form['ckeditor_upload_settings']['filebrowser'] = array(
    '#type' => 'select',
    '#title' => t('File browser type (Link dialog)'),
    '#default_value' => !empty($profile->settings['filebrowser']) ? $profile->settings['filebrowser'] : 'none',
    '#options' => $filebrowsers,
    '#description' => t('Select the file browser that you would like to use to upload files.'),
  );

  $form['ckeditor_upload_settings']['filebrowser_image'] = array(
    '#type' => 'select',
    '#title' => t('File browser type (Image dialog)'),
    '#default_value' => !empty($profile->settings['filebrowser_image']) ? $profile->settings['filebrowser_image'] : 'none',
    '#options' => $filebrowsers_dialogs,
    '#description' => t('Select the file browser that you would like to use to upload images.'),
  );

  $form['ckeditor_upload_settings']['filebrowser_flash'] = array(
    '#type' => 'select',
    '#title' => t('File browser type (Flash dialog)'),
    '#default_value' => !empty($profile->settings['filebrowser_flash']) ? $profile->settings['filebrowser_flash'] : 'none',
    '#options' => $filebrowsers_dialogs,
    '#description' => t('Select the file browser that you would like to use to upload flash movies.'),
  );

  $current_user_files_path = empty($profile->settings['UserFilesPath']) ? "" : strtr($profile->settings['UserFilesPath'], array("%f" => file_directory_path(), "%u" => "UID", "%b" => base_path(), "%n" => "UNAME"));
  $current_user_files_absolute_path = empty($profile->settings['UserFilesAbsolutePath']) ? "" : strtr($profile->settings['UserFilesAbsolutePath'], array("%f" => file_directory_path(), "%u" => "UID", "%b" => base_path(), "%d" => $_SERVER['DOCUMENT_ROOT'], "%n" => "UNAME"));

  $form['ckeditor_upload_settings']['UserFilesPath'] = array(
    '#type' => 'textfield',
    '#prefix' => '<fieldset><legend>' . t('CKFinder settings') .'</legend>',
    '#title' => t('Path to uploaded files'),
    '#default_value' => !empty($profile->settings['UserFilesPath']) ? $profile->settings['UserFilesPath'] : "%b%f/",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('Path to uploaded files relative to the document root.') .
      '<br />'.
      t('Available placeholders:!b - base URL path of the Drupal installation (!base).!f - Drupal file system path where the files are stored (!files).!u - User ID.!n - Username.<br />Current path: !path',
        array(
          '!n' => '<br /><strong>%n</strong>',
          '!u' => '<br /><strong>%u</strong>',
          '!f' => '<br/><strong>%f</strong>',
          '!b' => '<br/><strong>%b</strong>',
          '!path' => $current_user_files_path,
          '!files' => file_directory_path(),
          '!base' => base_path()
        ))
  );

  $form['ckeditor_upload_settings']['UserFilesAbsolutePath'] = array(
    '#type' => 'textfield',
    '#title' => t('Absolute path to uploaded files'),
    '#default_value' => !empty($profile->settings['UserFilesAbsolutePath']) ? $profile->settings['UserFilesAbsolutePath'] : "%d%b%f/",
    '#size' => 40,
    '#maxlength' => 255,
    '#suffix' => '</fieldset>',
    '#description' => t('The path to the local directory (in the server) which points to the path defined above. If empty, CKEditor will try to discover the right path.') .
      '<br />'.
      t('Available placeholders:!d - server path to document root (!root).!b - base URL path of the Drupal installation (!base).!f - Drupal file system path where the files are stored (!files).!u - User ID.!n - Username.<br />Current path: !path',
        array(
          '!u' => '<br /><strong>%u</strong>',
          '!n' => '<br /><strong>%n</strong>',
          '!d' => '<br/><strong>%d</strong>',
          '!b' => '<br /><strong>%b</strong>',
          '!f' => '<br/><strong>%f</strong>',
          '!path' => $current_user_files_absolute_path,
          '!files' => file_directory_path(),
          '!base' => base_path(),
          '!root' => $_SERVER['DOCUMENT_ROOT']
        ))
  );

  if (variable_get('file_downloads', '') == FILE_DOWNLOADS_PRIVATE) {
    $form['ckeditor_upload_settings']['UserFilesPath']['#description'] = t('Setting relative path to uploaded files has been disabled because private downloads are enabled and this path is calculated automatically. To change the location of uploaded files in the private file system, edit the <a href="!url">CKEditor Global Profile</a>.', array('!url' => url('admin/settings/ckeditor/editg')));
    $form['ckeditor_upload_settings']['UserFilesPath']['#disabled'] = TRUE;
    $form['ckeditor_upload_settings']['UserFilesAbsolutePath']['#description'] = t('Setting path to uploaded files has been disabled because private downloads are enabled and this path is calculated automatically.To change the location of uploaded files in the private file system, edit the <a href="!url">CKEditor Global Profile</a>.', array('!global' => url('admin/settings/ckeditor/editg')));
    $form['ckeditor_upload_settings']['UserFilesAbsolutePath']['#disabled'] = TRUE;
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['ckeditor_load_method'] = array(
    '#type' => 'select',
    '#title' => t('Load method'),
    '#default_value' => !empty($profile->settings['ckeditor_load_method']) ? $profile->settings['ckeditor_load_method'] : 'ckeditor.js',
    '#options' => _ckeditor_load_methods(),
    '#description' => t('Select the load method of CKEditor. If ckeditor_basic.js is used, only a small file is initially loaded and the rest part of the editor is loaded later (see "Load timeout"). This might be handy if CKEditor is disabled by default.'),
  );
  $form['advanced']['ckeditor_load_time_out'] = array(
    '#type' => 'textfield',
    '#title' => t('Load timeout'),
    '#default_value' => !empty($profile->settings['ckeditor_load_time_out']) ? $profile->settings['ckeditor_load_time_out'] : "0",
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t('The time to wait (in seconds) to load the full editor code after the page load, if the "ckeditor_basic.js" file is used. If set to zero, the editor is loaded on demand.'),
  );
  $form['advanced']['forcePasteAsPlainText'] = array(
    '#type' => 'select',
    '#title' => t('Force pasting as plain text'),
    '#default_value' => !empty($profile->settings['forcePasteAsPlainText']) ? $profile->settings['forcePasteAsPlainText'] : "f",
    '#options' => array(
      't' => t('Enabled'),
      'f' => t('Disabled')
      ),
      '#description' => t('If enabled, HTML content will be automatically changed to plain text when pasting.'),
  );
  $form['advanced']['theme_config_js'] = array(
    '#type' => 'radios',
    '#title' => t('Load ckeditor.config.js from theme path'),
    '#default_value' => !empty($profile->settings['theme_config_js']) ? $profile->settings['theme_config_js'] : 'f',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('When set to "true" the editor will try to load the ckeditor.config.js file from theme directory.'),
  );
  $form['advanced']['js_conf'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom javascript configuration'),
    '#default_value' => !empty($profile->settings['js_conf']) ? $profile->settings['js_conf'] : "",
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('To change CKEditor configuration globally, you should modify the config file: "!ckeditor_config". Sometimes it is required to change the CKEditor configuration for a single profile only. Use this box to define settings that are unique for this profile. Available options are listed in the <a href="!docs">CKEditor documentation</a>. Add the following code snippet to change available fonts in combo boxes in CKEditor: <pre>@code</pre><strong>Warning</strong>: If you make something wrong here, CKEditor may fail to load.', array('!ckeditor_config' => drupal_get_path('module', 'ckeditor') ."/ckeditor.config.js", '!docs' => 'http://docs.cksource.com/ckeditor_api/symbols/CKEDITOR.config.html', '@code' => "fontSize_sizes = '16/16px;24/24px;48/48px;'\nfont_names = 'Arial;Times New Roman;Verdana'")),
    '#wysiwyg' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  return $form;
}

/**
 * Profile validation.
 */
function ckeditor_admin_profile_form_validate($form, &$form_state) {
  $edit =& $form_state['values'];

  //include mode and all other fields are empty, invalid
  if ($edit['excl_mode'] == 1 && empty($edit['excl'])) {
    form_set_error('excl_mode', t('Include mode selected, but no paths given. Enter at least one path where CKEditor should appear.'));
  }
  else {
    ckeditor_admin_profile_validate_fieldpaths('excl', $edit['excl']);
  }

  ckeditor_admin_profile_validate_fieldpaths('simple_incl', $edit['simple_incl']);

  if (!preg_match('/^\d+$/', trim($edit['min_rows']))) {
    form_set_error('min_rows', t('Minimum rows must be a valid number.'));
  }

  if ($edit['default'] == 't' && $edit['popup'] == 't') {
    form_set_error('popup', t('If CKEditor is enabled by default, popup window must be disabled.'));
  }

  if ($edit['show_toggle'] == 't' && $edit['popup'] == 't') {
    form_set_error('popup', t('If toggle is enabled, popup window must be disabled.'));
  }

  if (!$edit['name']) {
    form_set_error('name', t('You must give a profile name.'));
  }
  elseif ($edit['name'] == 'CKEditor Global Profile') {
    form_set_error('name', t('This profile name is reserved. Please choose a different name.'));
  }
  elseif (!isset($edit['_profile']) || ($edit['_profile']->name != $edit['name'])) {
    $result = ckeditor_profile_load($edit['name']);
    if (!empty($result)) {
      form_set_error('name', t('The profile name must be unique. A profile with this name already exists.'));
    }
  }

  if (!preg_match('/^\d+%?$/', $edit['width'])) {
    form_set_error('width', t('Enter valid width. Example: 400 or 100%.'));
  }

  if (!empty($edit['css_path'])) {
    if ($edit['css_mode'] != 'self') {
      form_set_error('css_path', t('CSS path is not empty. Please set the "Editor CSS" option to "define css" mode.'));
    }
    elseif (FALSE !== strpos($edit['css_path'], '"')) {
      form_set_error('css_path', t('Double quotes are not allowed in CSS path.'));
    }
    elseif (substr($edit['css_path'], 0, 1) == "'" && substr($edit['css_path'], -1) == "'") {
      form_set_error('css_path', t('Enter valid path, do not surround it with quotes.'));
    }
  }

  if (!empty($edit['styles_path'])) {
    if ($edit['css_style'] != 'self') {
      form_set_error('styles_path', t('Path to predefined styles is not empty. Please set the "Predefined styles" option to "define path to ckeditor.styles.js" mode.'));
    }
    elseif (FALSE !== strpos($edit['styles_path'], '"')) {
      form_set_error('styles_path', t('Double quotes are not allowed in path.'));
    }
    elseif (substr($edit['styles_path'], 0, 1) == "'" && substr($edit['styles_path'], -1) == "'") {
      form_set_error('styles_path', t('Enter valid path, do not surround it with quotes.'));
    }
  }

  if (!empty($edit['font_format'])) {
    if (!preg_match("/^((p|div|pre|address|h1|h2|h3|h4|h5|h6);)*(p|div|pre|address|h1|h2|h3|h4|h5|h6)$/", $edit['font_format'])) {
      form_set_error('font_format', t('Enter valid, semicolon separated, list of HTML font formats (no semicolon at the end of list expected).'));
    }
  }

  if (variable_get('file_downloads', '') !== FILE_DOWNLOADS_PRIVATE) {
    if (!empty($edit['UserFilesAbsolutePath']) && empty($edit['UserFilesPath'])) {
      form_set_error('UserFilesPath', t('Path to uploaded files is required.'));
    }
    if (!empty($edit['UserFilesPath']) && empty($edit['UserFilesAbsolutePath'])) {
      form_set_error('UserFilesPath', t('Absolute path to uploaded files is required.'));
    }
  }
  $load_methods=_ckeditor_load_methods();
  if (!isset($load_methods[$edit['ckeditor_load_method']])) {
    form_set_error('ckeditor_load_method', t('Set valid load method.'));
  }
  if (!preg_match('#\d+#', $edit['ckeditor_load_time_out'])) {
    form_set_error('ckeditor_load_time_out', t('Enter valid load timeout in seconds.'));
  }
}

function ckeditor_admin_profile_form_submit($form, &$form_state) {
  $edit =& $form_state['values'];

  if (isset($edit['_profile'])) {
    db_query("DELETE FROM {ckeditor_settings} WHERE name = '%s'", $edit['_profile']->name);
    db_query("DELETE FROM {ckeditor_role} WHERE name = '%s'", $edit['_profile']->name);
    drupal_set_message(t('Your CKEditor profile has been updated.'));
  }
  else {
    drupal_set_message(t('Your CKEditor profile has been created.'));
  }

  $settings = ckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {ckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  ckeditor_rebuild_selectors($edit['name']);
  if (!empty($edit['rids'])) {
    foreach (array_keys($edit['rids']) as $rid) {
      if ($edit['rids'][$rid]!=0) {
        db_query("INSERT INTO {ckeditor_role} (name, rid) VALUES ('%s', %d)", $edit['name'], $rid);
      }
    }
  }

  $form_state['redirect'] = 'admin/settings/ckeditor';
}

function ckeditor_admin_global_profile_form($form_state, $mode = 'add') {
  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');
  if ($mode == 'edit') {
    $profile = ckeditor_profile_load('CKEditor Global Profile');

    $form['_profile'] = array(
      '#type' => 'value',
      '#value' => $profile,
    );
  }
  else {
    $profile = new stdClass();
  }

  if ($mode == 'add') {
    $data = ckeditor_profile_load('CKEditor Global Profile');
    if (!empty($data)) {
      drupal_set_message(t('Global profile already exist. Only one global profile is allowed.'), 'error');
      drupal_not_found();
    }

    $btn = t('Create global profile');
  }
  else {
    $btn = t('Update global profile');
  }

  $form['common'] = array(
    '#type' => 'fieldset',
    '#title' => t('Main setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );

  $roles = ckeditor_sorted_roles();
  $rids = $rtext = array();
  foreach ($roles as $rid => $name) {
    $rids[] = $rid;
    $rtext[] = '<strong>'. $rid .' - </strong>'. $name;
  }
  $form['common']['rank'] = array(
    '#type' => 'textfield',
    '#title' => t('Role precedence'),
    '#default_value' => implode('>', $rids),
    '#description' => t('A user having <strong>multiple roles</strong> gets the permissions of the highest one. Sort role IDs according to their <strong>precedence from higher to lower</strong> by putting > in between.'),
  );
  if ($rids) {
    $form['common']['rank']['#description'] .= '<br />'. t('Here is the id-name pairs of roles having access to CKEditor:') .'<div>'. implode('<br />', $rtext) .'</div>';
  }
  else {
    $form['common']['rank']['#description'] .= '<br />'. t('You haven\'t assigned the "access ckeditor" <a href="!permissions">permissions</a> yet.', array('!permissions' => url('admin/user/permissions')));
  }

  $form['ckeditor_exclude_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('The following settings are combined with the visibility settings of the specific profile.'),
  );

  $form['ckeditor_exclude_settings']['excl_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Use inclusion or exclusion mode'),
    '#default_value' => (empty($profile->settings['excl_mode']) || in_array($profile->settings['excl_mode'], array(0, 2))) ? 0 : 1,
    '#options' => array(
      '0' => t('Exclude'),
      '1' => t('Include')
    ),
    '#description' => t('Choose the way of disabling/enabling CKEditor on selected fields/paths (see below). Use exclude to disable CKEditor on selected fields/paths. Use include if you want to load CKEditor only on selected paths/fields.'),
  );
  /**
   * get excluded fields - so we can have normal textareas too
   * split the phrase by any number of commas or space characters,
   * which include " ", \r, \t, \n and \f
   */
  $form['ckeditor_exclude_settings']['excl'] = array(
    '#type' => 'textarea',
    '#title' => t('Fields to exclude/include'),
    '#cols' => 60,
    '#rows' => 5,
    '#prefix' => '<div style="margin-left:20px">',
    '#suffix' => '</div>',
    '#default_value' => !empty($profile->settings['excl']) ? $profile->settings['excl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to enable or disable CKEditor.') .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Short instruction is available below.', array('!helppagelink' => url('admin/help/ckeditor', array('fragment' => 'fieldinclexcl')))) .' <ul><li>'. t('Path structure: <strong>content_type@path.element_id</strong>') .'</li><li>'. t('The following wildcards are available: "*", "?".') .'</li><li>'. t('Content type is optional. You may even specify only path or field id.') .'</li><li>'. t('Examples:') .'<ul><li><em>blog@*.edit-body</em> - '. t('matches all fields of type "blog" called edit-body, on any page.') .'<li><em>node/add/*.edit-user-*</em> - '. t('matches fields starting with "edit-user-" on pages starting with "node/add/') .'</li></ul></li></ul>',
    '#wysiwyg' => FALSE,
  );

  $form['ckeditor_exclude_settings']['simple_incl'] = array(
    '#type' => 'textarea',
    '#title' => t('Force simplified toolbar on the following fields'),
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => !empty($profile->settings['simple_incl']) ? $profile->settings['simple_incl'] : '',
    '#description' => t('Enter the paths to the textarea fields on which you want to force the simplified toolbar (!name).', array('!name' => CKEDITOR_FORCE_SIMPLE_TOOLBAR_NAME)) .' '. t('Please see the <a href="!helppagelink">help page</a> for more information about defining field names. Take a look at the exclusion settings (above) for short instruction.', array('!helppagelink' => url('admin/help/ckeditor', array('fragment' => 'fieldinclexcl')))),
    '#wysiwyg' => FALSE,
  );

  $form['ckeditor_advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $module_drupal_path = drupal_get_path('module', 'ckeditor');

  $form['ckeditor_advanced_settings']['ckeditor_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to CKEditor'),
    '#default_value' =>  !empty($profile->settings['ckeditor_path']) ? $profile->settings['ckeditor_path'] : '%m/ckeditor',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('Path to CKEditor (the HTML editor, downloaded from <a href="!ckeditorcom">ckeditor.com</a>) relative to the document root.') .
      '<br />'.
      t('Available placeholders:!b - base URL path of the Drupal installation (!base).!m - base URL path where CKEditor module is stored (!files).<br />Current path: !path',
      array(
        '!b' => '<br /><strong>%b</strong>',
        '!m' => '<br /><strong>%m</strong>',
        '!path' => ckeditor_path(FALSE),
        '!base' => base_path(),
        '!files' => base_path() . $module_drupal_path ,
        '!ckeditorcom' => 'http://ckeditor.com/download'
     )),
    '#required' => TRUE
  );

  $form['ckeditor_advanced_settings']['ckeditor_local_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Local path to CKEditor'),
    '#default_value' =>  isset($profile->settings['ckeditor_local_path'])?$profile->settings['ckeditor_local_path']:'',
    '#size' => 40,
    '#maxlength' => 128,
    '#description' => t('The path to the local directory (on the server) which points to the path defined above. Enter either an absolute server path or path relative to "index.php". If empty, CKEditor module will try to find the right path.<br />Current path: !path', array('!path' => ckeditor_path(TRUE))),
  );

  $form['ckeditor_advanced_settings']['show_fieldnamehint'] = array(
    '#type' => 'radios',
    '#title' => t('Show field name hint below each rich text editor'),
    '#default_value' => !empty($profile->settings['show_fieldnamehint']) ? $profile->settings['show_fieldnamehint'] : 't',
    '#options' => array(
      't' => t('Yes'),
      'f' => t('No')
    ),
    '#description' => t('This only applies for users with "administer ckeditor" permissions.'),
  );

  if (variable_get('file_downloads', '') == FILE_DOWNLOADS_PRIVATE) {
    $current_private_dir = !empty($profile->settings['private_dir']) ? $profile->settings['private_dir'] : '';
    $form['ckeditor_advanced_settings']['private_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Location of files uploaded with CKEditor in the private folder'),
      '#default_value' => !empty($profile->settings['private_dir']) ? $profile->settings['private_dir'] : '',
      '#size' => 40,
      '#maxlength' => 255,
      '#description' => t('The path relative to the location of the private directory where CKEditor should store uploaded files.') . '<br />' . t('<strong>Warning:</strong> CKEditor does not implement any kind of access protection on files available in this location. All files stored in the directory defined above might be accessible by unauthenticated users if there is no information about the file in the Drupal\'s database.') . '<br />' . t('System path to the private folder is: !system_path.', array('!system_path' => realpath(file_directory_path()) . DIRECTORY_SEPARATOR)) . '<br />' . t('Available wildcard characters:') . '<br/><strong>%u</strong> - ' . t('User ID') . '<br /><strong>%n</strong> - ' . t('Username') . '<br />' . t('Current path: !path', array('!path' => $current_private_dir . ' (' . file_create_path($current_private_dir) . ')')),
    );
  }
  if (function_exists('linktocontent_node_menu') && function_exists('pathfilter_filter')) {
    $form['ckeditor_advanced_settings']['linktoc'] = array(
    '#type' => 'select',
    '#options' => array('p' => t('Link to paths only'), 'n' => t('Link using internal: links'), 'pn' => t('Allow user to select between paths and internal links')),
    '#title' => t('Path Filter & Link To Content integration'),
    '#default_value' => empty($profile->settings['linktoc']) ? 'p' : $profile->settings['linktoc'],
    '#description' => t('With !plink extension it is possible to use internal: links. By default !link extension is linking to nodes using paths.', array('!plink' => l(t('Path Filter'), 'http://drupal.org/project/pathfilter'), '!link' => l(t('Link To Content'), 'http://drupal.org/project/linktocontent'))),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $btn
  );

  return $form;
}

function ckeditor_admin_global_profile_form_validate($form, &$form_state) {
  $edit =& $form_state['values'];

  //include mode and all other fields are empty, invalid
  if ($edit['excl_mode'] == 1 && empty($edit['excl'])) {
    form_set_error('excl_mode', t('Include mode selected, but no paths given. Enter at least one path where CKEditor should appear.'));
  }
  else {
    ckeditor_admin_profile_validate_fieldpaths('excl', $edit['excl']);
  }

  ckeditor_admin_profile_validate_fieldpaths('simple_incl', $edit['simple_incl']);
}

function ckeditor_admin_global_profile_form_submit($form, &$form_state) {
  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');
  $edit =& $form_state['values'];
  $edit['name'] = 'CKEditor Global Profile';

  if (isset($edit['rank'])) {
    $edit['rank'] = explode('>', str_replace(' ', '', $edit['rank']));
  }

  if (isset($edit['_profile'])) {
    db_query("DELETE FROM {ckeditor_settings} WHERE name = '%s'", $edit['_profile']->name);
    db_query("DELETE FROM {ckeditor_role} WHERE name = '%s'", $edit['_profile']->name);
  }

  //strip whitespaces
  if (empty($edit['ckeditor_local_path'])) {
    $edit['ckeditor_local_path'] = '';
  }
  else {
    $edit['ckeditor_local_path'] = trim($edit['ckeditor_local_path']);
  }

  //strip slash from the end
  if (empty($edit['ckeditor_path'])) {
    $edit['ckeditor_path'] = '';
  }
  $edit['ckeditor_path'] = trim(rtrim($edit['ckeditor_path'], "/"));
  if ($edit['ckeditor_path'] && 0 !== strpos($edit['ckeditor_path'], "/") && 0 !== strpos($edit['ckeditor_path'], "%")) {
    //ensure that slash is at the beginning
    $edit['ckeditor_path'] = "/". $edit['ckeditor_path'];
  }
  //no slash at the end
  $edit['ckeditor_local_path'] = trim(rtrim($edit['ckeditor_local_path'], "/"));

  $settings = ckeditor_admin_values_to_settings($edit);
  db_query("INSERT INTO {ckeditor_settings} (name, settings) VALUES ('%s', '%s')", $edit['name'], $settings);
  ckeditor_rebuild_selectors($edit['name']);

  drupal_set_message(t('CKEditor global profile has been saved.'));
  $form_state['redirect'] = 'admin/settings/ckeditor';
}

/**
 * Converts an array of form values to a serialized array that does not
 * contain Drupal Form API values
 */
function ckeditor_admin_values_to_settings($values) {
  unset($values['name'], $values['rids'], $values['_profile'], $values['op'], $values['submit'], $values['form_build_id'], $values['form_token'], $values['form_id']);
  return serialize($values);
}

function ckeditor_admin_profile_validate_fieldpaths($fieldname, $paths) {
  $myerrors = array();

  $rules = preg_split('/[\s,]+/', $paths);

  foreach ($rules as $rule) {
    $rule = trim($rule);
    if (!empty($rule) && strpos($rule, '.') === FALSE && strpos($rule, '/') === FALSE && strpos($rule, '-') === FALSE) {
      $myerrors[] = t('Rule %rule is ambiguous: please append .* if %rule is a path or prepend *. if %rule is a field', array('%rule' => $rule));
    }
  }

  if (!empty($myerrors)) {
    form_set_error($fieldname, implode('<br/>', $myerrors));
  }
}

function ckeditor_admin_profile_delete_form($form_state, $profile) {
  $form = array();

  $form['_profile'] = array(
    '#type' => 'value',
    '#value' => $profile,
  );

  $form['question'] = array(
    '#type' => 'item',
    '#value' => t('Are you sure that you want to delete the CKEditor profile %profile?', array('%profile' => $profile->name)),
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#id' => 'delete',
    '#value' => t('Delete'),
  );

  $form['back'] = array(
    '#type' => 'submit',
    '#id' => 'back',
    '#value' => t('Cancel'),
  );

  return $form;
}

function ckeditor_admin_profile_delete_form_submit($form, &$form_state) {
  $v =& $form_state['values'];

  if ($form_state['clicked_button']['#id'] == 'delete') {
    ckeditor_profile_delete($v['_profile']->name);
    drupal_set_message(t('Deleted CKEditor profile.'));
  }

  $form_state['redirect'] = 'admin/settings/ckeditor';
}

/**
 * Rebuilds the regular expression that is used to match the inclusion/exclusion rules
 * and the simplified toolbar rules
 *
 * @param string $name Name of the profile to process. If omitted, all profiles are rebuilt
 */
function ckeditor_rebuild_selectors($name = NULL) {
  if ($name == NULL) {
    $result = db_query("SELECT * FROM {ckeditor_settings}");
  }
  else {
    $result = db_query("SELECT * FROM {ckeditor_settings} WHERE name = '%s'", $name);
  }

  while (($data = db_fetch_object($result))) {
    if ($data->settings) {
      $settings = unserialize($data->settings);
      // [#654626]
      if (!isset($settings['excl'])) {
        $settings['excl'] = '';
      }
      if (!isset($settings['simple_incl'])) {
        $settings['simple_incl'] = '';
      }

      foreach (array('excl', 'simple_incl') as $var) {
        $settings[$var .'_regex'] = '';
        $rules = preg_split('/[\s,]+/', $settings[$var]);
        $regex = array();

        if (!empty($rules)) {
          foreach ($rules as $rule) {
            if (!empty($rule)) {
              $rule = ckeditor_parse_rule($rule);
              $regex[] = '(?:'. ckeditor_rule_to_regex($rule) .')';
            }
          }

          if (!empty($regex)) {
            $settings[$var .'_regex'] = '#'. implode('|', $regex) .'#';
          }
        }
      }

      db_query("UPDATE {ckeditor_settings} SET settings='%s' WHERE name='%s'", serialize($settings), $data->name);
    }
  }
}

function ckeditor_rule_create($nodetype = '*', $path = '*', $fieldname = '*') {
  $rule = new stdClass();
  $rule->nodetype = $nodetype;
  $rule->path = $path;
  $rule->field = $fieldname;

  return $rule;
}

function ckeditor_parse_rule($rule) {
  $ruleobj = new stdClass();

  $atpos = strpos($rule, '@');
  if ($atpos !== FALSE) {
    $ruleobj->nodetype = substr($rule, 0, $atpos);
    $rule = substr($rule, $atpos + 1);
  }
  else {
    $ruleobj->nodetype = '*';
  }

  $dotpos = strpos($rule, '.');
  if ($dotpos === FALSE) {
    if (strpos($rule, '/') === FALSE && strpos($rule, '-') !== FALSE) {
      // assume it's a field
      $ruleobj->path = '*';
      $ruleobj->field = $rule;
    }
    elseif (strpos($rule, '/') !== FALSE) {
      // assume it's a path
      $ruleobj->path = $rule;
      $ruleobj->field = '*';
    }
    else {
      return NULL;
    }
  }
  else {
    $ruleobj->path = substr($rule, 0, $dotpos);
    $ruleobj->field = str_replace('\.', '.', substr($rule, $dotpos + 1));
  }

  return $ruleobj;
}

function ckeditor_rule_to_regex($rule) {
  static $replace = array('\*' => '.*', '\?' => '.');

  $field = str_replace('.', '\.', $rule->field);
  $regex = '^'. preg_quote($rule->nodetype, '#') .'@'. preg_quote($rule->path, '#') .'\.'. preg_quote($field, '#') .'$';
  $regex = strtr($regex, $replace);

  return $regex;
}

function ckeditor_rule_to_string($rule) {
  $field = str_replace('.', '\.', $rule->field);
  $rulestr = '';
  if ($rule->nodetype != '*') {
    $rulestr .= $rule->nodetype .'@';
  }
  return $rulestr . $rule->path .'.'. $field;
}

/**
 * Remove a profile from the database.
 */
function ckeditor_profile_delete($name) {
  db_query("DELETE FROM {ckeditor_settings} WHERE name = '%s'", $name);
  db_query("DELETE FROM {ckeditor_role} WHERE name = '%s'", $name);
}

function _ckeditor_load_methods() {
  module_load_include('module', 'ckeditor');
  $result = array('ckeditor.js' => 'ckeditor.js');
  if (file_exists(ckeditor_path(TRUE) . '/ckeditor_basic.js')) {
    $result['ckeditor_basic.js'] = 'ckeditor_basic.js';
  }
  if (file_exists(ckeditor_path(TRUE) . '/ckeditor_source.js')) {
    $result['ckeditor_source.js'] =  'ckeditor_source.js (' . t('for developers only') . ')';
  }
  return $result;
}