<?php

/**
 * @file
 * Admin configuration settings for Revisioning.
 */

/**
 * Menu callback for admin settings.
 */
function revisioning_admin_configure() {
  $form['revisioning_view_and_edit_links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure which revision is loaded when clicking on a view or edit link'),
    '#description' => t('This section allows you to configure which revision is loaded when clicking on links for viewing or editing moderated content, that is content for which the check-box <strong>New revision in draft, pending moderation</strong> is ticked on the %link page. If not ticked for this content type, current and latest revisions will be one and the same, so that the options behave identically.',
      array('%link' => 'admin/content/node-type/<type>'))
  );
  $form['revisioning_view_and_edit_links']['revisioning_view_callback'] = array(
    '#type' => 'radios',
    '#title' => t('Links to view content default to'),
    '#options' => array(
      REVISIONING_LOAD_CURRENT => t('displaying the current revision'),
      REVISIONING_LOAD_LATEST  => t('displaying the latest revision (reverts to current revision, if the user is not permitted to view revisions of the content type in question)')),
    '#default_value' => variable_get('revisioning_view_callback', REVISIONING_LOAD_CURRENT),
    '#description' => t('The first option represents default core behaviour.')
  );
  $form['revisioning_view_and_edit_links']['revisioning_edit_callback'] = array(
    '#type' => 'radios',
    '#title' => t('Links to edit content default to'),
    '#options' => array(
      REVISIONING_LOAD_CURRENT => t('editing the current revision'),
      REVISIONING_LOAD_LATEST  => t('editing the latest revision (reverts to current revision, if the user is not permitted to view revisions of the content type in question)')),
    '#default_value' => variable_get('revisioning_edit_callback', REVISIONING_LOAD_CURRENT),
    '#description' => t('The first option represents default core behaviour.')
  );
  return system_settings_form($form);
}