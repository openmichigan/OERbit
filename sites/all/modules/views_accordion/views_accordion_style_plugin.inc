<?php
// $Id: views_accordion_style_plugin.inc,v 1.1.2.14 2009/11/03 18:52:03 manuelgarcia Exp $
/**
 * @file
 * Provide an accordion style plugin for Views. This file is autoloaded by views.
 */

/**
  * Implementation of views_plugin_style().
  */
class views_accordion_style_plugin extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['use-grouping-header'] = array('default' => 0);
    $options['keep-one-open'] = array('default' => 0);
    $options['disable-close-others'] = array('default' => 0);
    $options['speed'] = array('default' => 0.5);
    $options['start-open'] = array('default' => 1);
    $options['row-start-open'] = array('default' => 0);
    $options['toggle-links'] = array('default' => 0);
    $options['include-style'] = array('default' => 1);
    $options['auto-cycle'] = array('default' => 0);
    $options['auto-cycle-speed'] = array('default' => 5);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['grouping']['#prefix'] = '<div class="form-item">'. t('<strong>IMPORTANT:</strong> The <em>first field</em> in order of appearance <em>will</em> be the one used as the "header" or "trigger" of the accordion action.') .'</div>';
     // available valid options for grouping (used for use-grouping-header #dependency)
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      $options[] = $field;
    }
    // Find out how many items the display is currently configured to show (row-start-open)
    $maxitems = $this->display->handler->get_option('items_per_page');
    $maxitems = ($maxitems == 0) ? 10 : $maxitems;  // if items_per_page is set to unlimitted (0), 10 rows will be what the user gets to choose from.

    // Setup our array of options for choosing which row should start opened (row-start-open)
    $rsopen_options = array();
    for ($i = 1; $i <= $maxitems; $i++){
      $rsopen_options[] = t('Row ') . $i;
    }

    $form['use-grouping-header'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the group header as the Accordion header'),
      '#default_value' => $this->options['use-grouping-header'],
      '#description' => t('If checked, the Group\'s header will be used to open/close the accordion.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-grouping' => $options),
    );
    $form['start-open'] = array(
      '#type' => 'checkbox',
      '#title' => t('Start with a row opened'),
      '#default_value' => $this->options['start-open'],
      '#description' => t('Whether or not you would like the accordion to start with a row opened. If checked, you will be able to choose which row to be opened at start.'),
    );
    $form['row-start-open'] = array(
      '#type' => 'select',
      '#title' => t('Row to display opened on start'),
      '#default_value' => $this->options['row-start-open'],
      '#description' => t('Choose which row should start opened when the accordion first loads. Uncheck "<em>Start with a row opened</em>" to start with all rows closed.'),
      '#options' => $rsopen_options,
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-start-open' => array(TRUE)),
    );
    $form['keep-one-open'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allways keep one item opened'),
      '#default_value' => $this->options['keep-one-open'],
      '#description' => t('If you check this on, when the user clicks on an opened item, it will not close.'),
    );
    $form['disable-close-others'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable auto-closing of opened accordion items'),
      '#default_value' => $this->options['disable-close-others'],
      '#description' => t('If you check this on, when the user opens an item, it will not close the already opened items.'),
    );

    $form['speed'] = array(
      '#type' => 'textfield',
      '#title' => t('Transition time'),
      '#size' => 5,
      '#maxlength' => 5,
      '#default_value' => $this->options['speed'],
      '#field_suffix' => t('Seconds'),
      '#required' => TRUE,
      '#element_validate' => array('accordion_speed_validate'),
      '#description' => t('The time in seconds to open-close sections. The value <em>must be higher than 0</em>. If you would like it to be instanteneous, enter 0.001. Do not use commas in this field.'),
    );
    $form['toggle-links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display <em>Open All</em> - <em>Close All</em> links'),
      '#default_value' => $this->options['toggle-links'],
      '#description' => t('Whether or not to have links that toggle all content opened/closed. Note that these will NOT display if <em>Auto cycle</em> is on.'),
    );
    $form['include-style'] = array(
      '#type' => 'checkbox',
      '#title' => t("Use the module's default styling"),
      '#default_value' => $this->options['include-style'],
      '#description' => t("If you disable this, the file in the module's directory <em>views-accordion.css</em> will not be loaded"),
    );
    $form['auto-cycle'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto cycle through the items'),
      '#default_value' => $this->options['auto-cycle'],
      '#description' => t('Whether or not you would like the accordion to cycle through each item automaticaly.'),
    );
    $form['auto-cycle-speed'] = array(
      '#type' => 'textfield',
      '#title' => t('Cycle transition time'),
      '#size' => 5,
      '#maxlength' => 5,
      '#default_value' => $this->options['auto-cycle-speed'],
      '#field_suffix' => t('Seconds'),
      '#required' => FALSE,
      '#element_validate' => array('accordion_speed_validate'),
      '#description' => t('The time in seconds it will wait before opening the next item. This <strong>will be added to the Transition time you entered above</strong>'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-auto-cycle' => array(TRUE)),
    );
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $output = parent::render();

    // dpm($this->display->handler->get_option('fields')); // for dev-troubleshooting
    // Preparing the js variables and adding the js to our display
    // we do it here so we dont have it run once every group
    drupal_add_js(drupal_get_path('module', 'views_accordion') .'/views-accordion.js');
    $view_settings['keeponeopen'] = $this->options['keep-one-open'];
    $view_settings['startopen'] = $this->options['start-open'];
    $view_settings['rowstartopen'] = $this->options['row-start-open'];
    $view_settings['speed'] = check_plain($this->options['speed']) * 1000;
    $view_settings['disablecloseothers'] = $this->options['disable-close-others'];
    $view_settings['grouping'] =  $this->options['grouping'] ? 1 : 0;
    $view_settings['togglelinks'] = $this->options['toggle-links'];
    $view_settings['autocycle'] = $this->options['auto-cycle'];
    $view_settings['autocyclespeed'] = check_plain($this->options['auto-cycle-speed']) * 1000;
    $view_settings['display'] =  'views-accordion-'. $this->view->name .'-'. $this->view->current_display;
    $view_settings['usegroupheader'] = $view_settings['grouping'] ? $this->options['use-grouping-header'] : 0;
    $view_id = 'views-accordion-'. $this->view->name .'-'. $this->view->current_display;

    if ($view_settings['usegroupheader'] == 1) {
      $view_settings['header'] = 'h3.'. $view_id;
    }
    // Used to get the first field to be used as the accordion header
    if ($view_settings['usegroupheader'] == 0) {
      $i = 0;
      foreach ($this->view->field as $id => $value) {
        if (($i == 0) && ($value->options['exclude'] == 0)) {
          $view_settings['header'] = 'views-field-'. str_replace('_' , '-' , $id);
          $i++;
        }
      }
    }
    drupal_add_js(array('views_accordion' => array($view_id => $view_settings)), 'setting');

    return $output;
  }
}

/**
  * Validates the options entered
  */
function accordion_speed_validate($element, &$form_state) {
  /* must be numeric value */
  if(!is_numeric($element['#value'])) {
    form_error($element, ('<em>'. ($element['#title'] . t('</em> must be a <em>numberic</em> value.'))));
  }

  /* dont allow commas */
  if (strstr($element['#value'], ',')) {
    form_error($element, t('Please use a "." instead of a "," in the <em>') . $element['#title'] . t('</em> field.'));
  }

  /* must be higher than 0 */
  if ($element['#value'] <= 0) {
    form_error($element, ('<em>'. ($element['#title'] . t('</em> must be a <em>number</em> higher than 0.<br />If you would like it to be instanteneous, enter 0.001'))));
  }
}
