<?php
// $Id: ckeditor.user.inc,v 1.1.2.1 2010/03/04 08:26:41 mephir Exp $
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

function ckeditor_user_delegate($type, $edit, &$user, $category = NULL) {
  if ($type == 'form' && $category == 'account' && user_access('access ckeditor')) {
    module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');

    $profile = ckeditor_user_get_profile($user);
    $toolbar_options = ckeditor_load_toolbar_options();
    $skin_options = ckeditor_load_skin_options();
    $lang_options = ckeditor_load_lang_options();

    // because the settings are saved as strings we need to test for the string 'true'
    if ($profile->settings['allow_user_conf'] == 't') {
      $form['ckeditor'] = array(
        '#type' => 'fieldset',
        '#title' => t('Rich text editor settings'),
        '#weight' => 10,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
      );

      $form['ckeditor']['ckeditor_default'] = array(
        '#type' => 'radios',
        '#title' => t('Default state'),
        '#default_value' => isset($user->ckeditor_default) ? $user->ckeditor_default : (isset($profile->settings['default']) ? $profile->settings['default'] : 'f'),
        '#options' => array(
          't' => t('Enabled'),
          'f' => t('Disabled')
        ),
        '#description' => t('Should rich-text editing be enabled or disabled by default in textarea fields? If disabled, rich text editor may still be enabled using toggle or popup window.'),
      );

      $form['ckeditor']['ckeditor_show_toggle'] = array(
        '#type' => 'radios',
        '#title' => t('Show disable/enable rich text editor toggle'),
        '#default_value' => isset($user->ckeditor_show_toggle) ? $user->ckeditor_show_toggle : (isset($profile->settings['show_toggle']) ? $profile->settings['show_toggle'] : 't'),
        '#options' => array(
          't' => t('Yes'),
          'f' => t('No')
        ),
        '#description' => t('Whether or not to show the disable/enable rich text editor toggle below the textarea. Works only if CKEditor is not running a popup window (see below).'),
      );

      if (user_access('administer ckeditor')) {
        $form['ckeditor']['ckeditor_show_fieldnamehint'] = array(
          '#type' => 'radios',
          '#title' => t('Show field name hint below each rich text editor'),
          '#default_value' => !empty($user->ckeditor_show_fieldnamehint) ? $user->ckeditor_show_fieldnamehint : 't',
          '#options' => array(
            't' => t('Yes'),
            'f' => t('No')
          ),
        );
      }

      $form['ckeditor']['ckeditor_popup'] = array(
        '#type' => 'radios',
        '#title' => t('Use CKEditor in a popup window'),
        '#default_value' => isset($user->ckeditor_popup) ? $user->ckeditor_popup : (isset($profile->settings['popup']) ? $profile->settings['popup'] : 'f'),
        '#options' => array(
          'f' => t('No'),
          't' => t('Yes')
        ),
        '#description' => t('If this option is enabled a link to a popup window will be used instead of a textarea replace.'),
      );

      $form['ckeditor']['ckeditor_skin'] = array(
        '#type' => 'select',
        '#title' => t('Skin'),
        '#default_value' => isset($user->ckeditor_skin) ? $user->ckeditor_skin : (isset($profile->settings['skin']) ? $profile->settings['skin'] : 'default'),
        '#options' => $skin_options,
        '#description' => t('Choose a CKEditor skin.'),
      );

      $form['ckeditor']['ckeditor_toolbar'] = array(
        '#type' => 'select',
        '#title' => t('Toolbar'),
        '#default_value' => isset($user->ckeditor_toolbar) ? $user->ckeditor_toolbar : (isset($profile->settings['toolbar']) ? $profile->settings['toolbar'] : 'default'),
        '#options' => $toolbar_options,
        '#description' => t('Choose a CKEditor toolbar set.'),
      );

      $form['ckeditor']['ckeditor_expand'] = array(
        '#type' => 'select',
        '#title' => t('Start the toolbar expanded'),
        '#default_value' => isset($user->ckeditor_expand) ? $user->ckeditor_expand : (isset($profile->settings['expand']) ? $profile->settings['expand'] : 't'),
        '#options' => array(
          't' => t('Expanded'),
          'f' => t('Collapsed')
        ),
        '#description' => t('The toolbar start expanded or collapsed.'),
      );

      $form['ckeditor']['ckeditor_width'] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#default_value' => isset($user->ckeditor_width) ? $user->ckeditor_width : (isset($profile->settings['width']) ? $profile->settings['width'] : '100%'),
        '#description' => t('Width in pixels or percent.') .' '. t('Example') .': 400 '. t('or') .' 100%.',
        '#size' => 40,
        '#maxlength' => 128,
      );
      
      $form['ckeditor']['ckeditor_lang'] = array(
        '#type' => 'select',
        '#title' => t('Language'),
        '#default_value' => isset($user->ckeditor_lang) ? $user->ckeditor_lang : (isset($profile->settings['lang']) ? $profile->settings['lang'] : 'en'),
        '#options' => $lang_options,
        '#description' => t('The language for the CKEditor interface.')
      );

      $form['ckeditor']['ckeditor_auto_lang'] = array(
        '#type' => 'radios',
        '#title' => t('Auto-detect language'),
        '#default_value' => isset($user->ckeditor_auto_lang) ? $user->ckeditor_auto_lang : (isset($profile->settings['auto_lang']) ? $profile->settings['auto_lang'] : 't'),
        '#options' => array(
          't' => t('Yes'),
          'f' => t('No')
        ),
        '#description' => t('Use auto detect user language feature.')
      );

      return array('ckeditor' => $form);
    }
  }

  if ($type == 'validate') {
    if (isset($edit['ckeditor_default'], $edit['ckeditor_popup']) && $edit['ckeditor_default'] == 't' && $edit['ckeditor_popup'] == 't') {
      form_set_error('ckeditor_popup', t('If CKEditor is enabled by default, popup window must be disabled.'));
    }

    if (isset($edit['ckeditor_show_toggle'], $edit['ckeditor_popup']) && $edit['ckeditor_show_toggle'] == 't' && $edit['ckeditor_popup'] == 't') {
      form_set_error('ckeditor_popup', t('If toggle is enabled, popup window must be disabled.'));
    }

    if (isset($edit['ckeditor_width']) && !preg_match('/^\d+%?$/', $edit['ckeditor_width'])) {
      form_set_error('ckeditor_width', t('Enter valid width.') .' '. t('Example') .': 400 '. t('or') .' 100%.');
    }
  }

  return NULL;
}
