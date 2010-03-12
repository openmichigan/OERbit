<?php
// $Id: ckeditor.lib.inc,v 1.1 2009/12/04 20:36:57 wwalc Exp $
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
 * Guess the absolute server path to the document root
 * Usually it should return $_SERVER['DOCUMENT_ROOT']
 *
 * @todo Improve me!!
 * Returns absolute path or false on failure
 *
 * @return string|boolean
 */
function ckeditor_get_document_root_full_path() {
  $found=0;
  $index_dir  = realpath(dirname($_SERVER['SCRIPT_FILENAME'])); // {/dir1/dir2/home/drupal}/index.php
  if (getcwd() == $index_dir) {
    $found++;
  }
  $drupal_dir = base_path();
  $index_dir  = str_replace('\\', "/", $index_dir);
  $drupal_dir = str_replace('\\', "/", $drupal_dir);
  $document_root_dir   = $index_dir .'/'. str_repeat('../', substr_count($drupal_dir, '/')-1);
  $document_root_dir   = realpath($document_root_dir);
  $document_root_dir   = rtrim($document_root_dir, '/\\');
  if ($document_root_dir == $_SERVER['DOCUMENT_ROOT']) {
    $found++;
  }
  $document_root_dir   = str_replace('\\', '/', $document_root_dir);

  if ($document_root_dir != '') {
    $found++;
  }
  if (file_exists($document_root_dir)) {
    $found++;
  }
  if (file_exists($document_root_dir . base_path() .'includes/bootstrap.inc')) {
    $found++;
  }

  if ($found >= 3) {
    return $document_root_dir;
  }
  else{
    return FALSE;
  }
}

/**
 * Emulates the asp Server.mapPath function.
 * Given an url path return the physical directory that it corresponds to.
 *
 * Returns absolute path or false on failure
 *
 * @param string $path
 * @return @return string|boolean
 */
function ckeditor_resolve_url($path) {
  if (function_exists('apache_lookup_uri')) {
    $info = @apache_lookup_uri($path);
    if (!$info) {
      return FALSE;
    }
    return $info->filename . $info->path_info ;
  }

  $document_root = ckeditor_get_document_root_full_path();
  if ($document_root !== FALSE) {
    return $document_root . $path;
  }

  return FALSE;
}

function ckeditor_load_toolbar_options() {
  $arr = array('Basic' => 'Basic', 'Full' => 'Full');
  $module_drupal_path = drupal_get_path('module', 'ckeditor');
  $editor_local_path  = ckeditor_path(TRUE);
  $ckconfig_js = $editor_local_path .'/config.js';
  $ckeditor_config_js = $module_drupal_path .'/ckeditor.config.js';
  if (file_exists($ckconfig_js) && is_readable($ckconfig_js)) {
    $fp = @fopen($ckconfig_js, "r");
    if ($fp) {
      while (!feof($fp)) {
        $line = fgets($fp, 1024);
        $matches = array();
        if (preg_match('/config.toolbar_([a-z0-9_]+)/i', $line, $matches)) {
          $arr[$matches[1]] = drupal_ucfirst($matches[1]);
        }
      }
      fclose($fp);
    }
  }
  if (file_exists($ckeditor_config_js) && is_readable($ckeditor_config_js)) {
    $fp = @fopen($ckeditor_config_js, "r");
    if ($fp) {
      while (!feof($fp)) {
        $line = fgets($fp, 1024);
        $matches = array();
        if (preg_match('/config.toolbar_([a-z0-9_]+)/i', $line, $matches)) {
          $arr[$matches[1]] = drupal_ucfirst($matches[1]);
        }
      }
      fclose($fp);
    }
  }

  //oops, we have no information about toolbars, let's use hardcoded array
  if (empty($arr)) {
    $arr = array(
      'Basic' => 'Basic',
      'Default' => 'Default',
    );
  }
  asort($arr);

  return $arr;
}

function ckeditor_load_skin_options() {
  $arr = array();
  $editor_local_path  = ckeditor_path(TRUE);
  $skin_dir     = $editor_local_path .'/skins';
  if (is_dir($skin_dir)) {
    $dh = @opendir($skin_dir);
    if (FALSE !== $dh) {
      while (($file = readdir($dh)) !== FALSE ) {
        if (in_array($file, array(".", "..", "CVS", ".svn"))) {
          continue;
        }
        if (is_dir($skin_dir . DIRECTORY_SEPARATOR . $file)) {
          $arr[$file] = drupal_ucfirst($file);
        }
      }
      closedir( $dh );
    }
  }

  //oops, we have no information about skins, let's use only default
  if (empty($arr)) {
    $arr = array(
      'kama' => 'Kama',
    );
  }
  asort($arr);

  return $arr;
}

function ckeditor_load_lang_options() {
  $arr = array();
  $editor_local_path  = ckeditor_path(TRUE);
  $lang_dir     = $editor_local_path .'/editor/lang';
  if (is_dir($lang_dir)) {
    $dh = @opendir($lang_dir);
    if (FALSE !== $dh ) {
      while (($file = readdir($dh)) !== FALSE) {
        if (in_array($file, array(".", "..", "CVS", ".svn"))) {
          continue;
        }
        $matches = array();
        if (is_file($lang_dir . DIRECTORY_SEPARATOR . $file) && preg_match('/^(.*?)\.js$/', $file, $matches)) {
          $lang = $matches[1];
          $arr[$lang] = drupal_strtoupper($lang);
        }
      }
      closedir( $dh );
    }
  }

  //oops, we have no information about languages, let's use those available in CKEditor 2.4.3
  if (empty($arr)) {
    $arr = array(
      'af' => 'Afrikaans',
      'ar' => 'Arabic',
      'bg' => 'Bulgarian',
      'bn' => 'Bengali/Bangla',
      'bs' => 'Bosnian',
      'ca' => 'Catalan',
      'cs' => 'Czech',
      'da' => 'Danish',
      'de' => 'German',
      'el' => 'Greek',
      'en' => 'English',
      'en-au' => 'English (Australia)',
      'en-ca' => 'English (Canadian)',
      'en-uk' => 'English (United Kingdom)',
      'eo' => 'Esperanto',
      'es' => 'Spanish',
      'et' => 'Estonian',
      'eu' => 'Basque',
      'fa' => 'Persian',
      'fi' => 'Finnish',
      'fo' => 'Faroese',
      'fr' => 'French',
      'gl' => 'Galician',
      'he' => 'Hebrew',
      'hi' => 'Hindi',
      'hr' => 'Croatian',
      'hu' => 'Hungarian',
      'it' => 'Italian',
      'ja' => 'Japanese',
      'km' => 'Khmer',
      'ko' => 'Korean',
      'lt' => 'Lithuanian',
      'lv' => 'Latvian',
      'mn' => 'Mongolian',
      'ms' => 'Malay',
      'nb' => 'Norwegian Bokmal',
      'nl' => 'Dutch',
      'no' => 'Norwegian',
      'pl' => 'Polish',
      'pt' => 'Portuguese (Portugal)',
      'pt-br' => 'Portuguese (Brazil)',
      'ro' => 'Romanian',
      'ru' => 'Russian',
      'sk' => 'Slovak',
      'sl' => 'Slovenian',
      'sr' => 'Serbian (Cyrillic)',
      'sr-latn' => 'Serbian (Latin)',
      'sv' => 'Swedish',
      'th' => 'Thai',
      'tr' => 'Turkish',
      'uk' => 'Ukrainian',
      'vi' => 'Vietnamese',
      'zh' => 'Chinese Traditional',
      'zh-cn' => 'Chinese Simplified',
    );
  }

  asort($arr);

  return $arr;
}

function ckeditor_user_get_setting($user, $profile, $setting) {
  $default = array(
    'default' => 't',
    'show_toggle' => 't',
    'popup' => 'f',
    'skin' => 'kama',
    'toolbar' => 'default',
    'expand' => 't',
    'width' => '100%',
    'lang' => 'en',
    'auto_lang' => 't',
  );

  if ($profile->settings['allow_user_conf']) {
    $status = isset($user->{'ckeditor_'. $setting}) ? $user->{'ckeditor_'. $setting} : (isset($profile->settings[$setting]) ? $profile->settings[$setting] : $default[$setting]);
  }
  else {
    $status = isset($profile->settings[$setting]) ? $profile->settings[$setting] : $default[$setting];
  }

  return $status;
}

function ckeditor_user_get_profile($user, $element_id = NULL) {
  $rids = array();

  // Since ckeditor_profile_load() makes a db hit, only call it when we're pretty sure
  // we're gonna render ckeditor.
  $sorted_roles = ckeditor_sorted_roles();
  foreach (array_keys($sorted_roles) as $rid) {
    if (isset($user->roles[$rid])) {
      $rids[] = $rid;
    }
  }

  if ($user->uid == 1 && !sizeof($rids)) {
    $r = db_fetch_object(db_query_range("SELECT r.rid FROM {ckeditor_role} r ORDER BY r.rid DESC", 1));
    $rids[] = $r->rid;
  }

  $profile_names = array();
  if (sizeof($rids)) {
    $result = db_query("SELECT r.rid, s.name FROM {ckeditor_settings} s INNER JOIN {ckeditor_role} r ON r.name = s.name WHERE r.rid IN (". implode(",", $rids) .")");
    while (($row = db_fetch_array($result))) {
      if (!isset($profile_names[$row['rid']])) {
        $profile_names[$row['rid']] = array();
      }
      array_push($profile_names[$row['rid']], $row['name']);
    }
  }

  foreach ($rids as $rid) {
    if (!empty($profile_names[$rid])) {
      foreach ($profile_names[$rid] as $profile_name) {
        $profile = ckeditor_profile_load($profile_name);

        $conf = $profile->settings;
        $enabled = ckeditor_is_enabled(empty($conf['excl_mode']) ? '0' : $conf['excl_mode'], empty($conf['excl_regex']) ? '' : $conf['excl_regex'], $element_id, $_GET['q']);

        if ($enabled) {
          return $profile;
        }
      }
    }
  }

  return FALSE;
}

/**
 * sort roles according to precedence settings. previously sorted roles are followed by latest added roles.
 */
function ckeditor_sorted_roles($clear = FALSE) {
  static $order;
  if (isset($order) && $clear !== TRUE) {
    return $order;
  }
  $order = array();
  $roles = user_roles(0, 'access ckeditor');

  $result = db_query("SELECT settings FROM {ckeditor_settings} WHERE name='CKEditor Global Profile'");
  $data = db_fetch_object($result);
  if (!empty($data->settings)) {
    $settings = unserialize($data->settings);
    if (isset($settings['rank']) && !empty($settings['rank']))
    foreach ($settings['rank'] as $rid) {
      if (isset($roles[$rid])) {
        $order[$rid] = $roles[$rid];
        unset($roles[$rid]);
      }
    }
  }
  krsort($roles);//sort the remaining unsorted roles by id, descending.
  $order += $roles;
  return $order;
}

/**
 * @param int $excl_mode 1/include, exclude otherwise
 * @param string $excl_regex paths (drupal paths with ids attached)
 * @param string $element_id current ID
 * @param string $get_q current path
 *
 * @return boolean
 *    returns true if CKEditor is enabled
 */
function ckeditor_is_enabled($excl_mode, $excl_regex, $element_id, $get_q) {
  $front = variable_get('site_frontpage', 'node');
  $excl_regex = str_replace('<front>', $front, $excl_regex);
  $nodetype = ckeditor_get_nodetype($get_q);
  $element_id = str_replace('.', '\.', $element_id);

  $match = !empty($excl_regex) && preg_match($excl_regex, $nodetype .'@'. $get_q .'.'. $element_id);

  return ($excl_mode == '0' xor $match);
}

function _ckeditor_script_path() {
  $jspath = FALSE;
  $module_path=drupal_get_path('module', 'ckeditor');

  if (file_exists($module_path . '/ckeditor/ckeditor.js')) {
    $jspath='%m/ckeditor';
  }
  elseif (file_exists($module_path . '/ckeditor/ckeditor/ckeditor.js')) {
    $jspath='%m/ckeditor/ckeditor';
  }
  elseif (file_exists('sites/all/libraries/ckeditor/ckeditor.js')) {
    $jspath='%b/sites/all/libraries/ckeditor';
  }
  return $jspath;
}

/**
 * Determines whether the CKEditor sources are present
 *
 * It checks if ckeditor.js is present.
 *
 * This function is used by ckeditor_requirements()
 *
 * @return boolean True if CKEditor is installed
 */
function _ckeditor_requirements_isinstalled() {
  $editor_path = ckeditor_path(TRUE);
  $jspath = $editor_path .'/ckeditor.js';
  $jsp=file_exists($jspath);
  if (!$jsp && ($editor_path = _ckeditor_script_path())) {
    $result = db_query("SELECT name, settings FROM {ckeditor_settings} WHERE name = 'CKEditor Global Profile'");
    if ($rs=db_fetch_array($result)) {
      $rs['settings']=unserialize($rs['settings']);
      $rs['settings']['ckeditor_path']=$editor_path;
      $rs['settings']=serialize($rs['settings']);
      db_query("UPDATE {ckeditor_settings} SET settings='%s' WHERE name = 'CKEditor Global Profile'", $rs['settings']);
      $jsp=TRUE;
      ckeditor_path(TRUE, TRUE);
    }
  }
  return $jsp;
}
