<?php
// $Id: accessible_content.pages.inc,v 1.1.2.14 2010/07/13 04:52:50 kevee Exp $

/**
*   @file
*   Pages for Accessible Content
*/

/**
*  Form for viewing the accessibility stats of a node.
*
*/
function accessible_content_accessibility_tab_form() {
  drupal_add_css(drupal_get_path('module', 'accessible_content') .'/accessible_content.css');
  $node = menu_get_object();
  $form = array();
  $body = (variable_get($node->type .'_ac_after_filter', 0))
            ? check_markup($node->body)
            : $node->body;
  $results = accessible_content_check_string($body,
                  variable_get($node->type .'_accessibility_guideline_nid', 0),
                  'AccessibleContent',
                  variable_get($node->type .'_ac_ignore_cms_off', 1),
                        variable_get($node->type .'_ac_display_level', 
                        array(QUAIL_TEST_SEVERE => 1, 
                            QUAIL_TEST_MODERATE => 1, 
                            QUAIL_TEST_SUGGESTION => 1)
                        )
            );
  $form = array_merge($form, accessible_content_accessibility_report($results, 'body', 'Node Body'));
  $fields = variable_get('ac_field', array());

  foreach ($fields as $field => $check) {
    if ($check && property_exists($node, $field)) {
      $content_field = content_fields($field);
      if ($content_field['text_processing']) {
        foreach ($node->$field as $k => $field) {
          $results = accessible_content_check_string($field['value'], 
                        variable_get($node->type .'_accessibility_guideline_nid', 0), 
                        'AccessibleContent', 
                        variable_get($node->type .'_ac_ignore_cms_off', 1),
                        variable_get($node->type .'_ac_display_level', 
                        array(QUAIL_TEST_SEVERE => 1, 
                            QUAIL_TEST_MODERATE => 1, 
                            QUAIL_TEST_SUGGESTION => 1)
                        )
              );
          $form = array_merge($form, 
                    accessible_content_accessibility_report($results, $content_field['field_name'] . $k, 
                    $content_field['widget']['label'] . $number,
                    array('field' => $content_field['field_name'], 'delta' => $k) ));  
        }
      }
    }
  }
  if (user_access('manually override tests')) {
    $form['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,
    );
    $form['submit'] = array('#type' => 'submit', '#value' => 'Override tests');
  }
  return $form;
}

/**
*  Form submit action for the overriding of tests.
*/
function accessible_content_accessibility_tab_form_submit($form, $form_state) {
  $node = menu_get_object();
  $results['body'] = accessible_content_check_string($node->body,
                     variable_get($node->type .'_accessibility_guideline_nid', 0),
                     'AccessibleContent',
                     variable_get($node->type .'_ac_ignore_cms_off', 1));
  $fields = variable_get('ac_field', array());

  foreach ($fields as $field => $check) {
    if ($check && property_exists($node, $field)) {
      $content_field = content_fields($field);
      if ($content_field['text_processing']) {
        foreach ($node->$field as $k => $field) {
          $number = (count($node->field) > 1)
            ? ' #'. ($k+1)
            : '';
          $results[$content_field['field_name']] = accessible_content_check_string($field['value'],
                        variable_get($node->type .'_accessibility_guideline_nid', 0),
                        'AccessibleContent',
                        variable_get($node->type .'_ac_ignore_cms_off', 1));

        }
      }
    }
  }
  foreach ($results as $part => $result) {
    foreach ($result as $severity => $result) {
      foreach ($result as $testname => $errors) {
        if ($form_state['clicked_button']['#post']['override'][$part][$testname]) {
          accessible_content_override_test($node->nid, $testname, $errors, $part);
        }
        elseif (accessible_content_test_is_overriden($node->nid, $testname, $errors, $part)) {
          accessible_content_remove_override($node->nid, $testname, $errors, $part);
        }
      }
    }
  }
  _accessible_content_remove_overriden_tests($node->nid, $results);
  $node->accessibility_results = $results;
  node_save($node);
  drupal_set_message(t('The selected tests have been overridden'));
  drupal_goto('node/'. $form_state['values']['nid'] .'/accessibility');
}
/**
*  The demonstration or "highlight" tab
*
*/
function accessible_content_accessibility_demo_tab($nid) {
  drupal_set_title('Highlighted errors');
  drupal_add_css(drupal_get_path('module', 'accessible_content') .'/accessible_content.css');
  if (module_exists('beautytips')) {
    $area_label = _accessible_content_get_beautytips_area_label();
    $options['ac_demo_view'] = array(
      $area_label => '.highlight-link',
      'ajaxPath' => array(0 => "$(this).attr('href') + '/accessibility/tip'", 1 => '#node-tip'),
      'trigger' => array(0 => 'mouseover', 1 => 'click'),
      'width' => 350,
    );
    beautytips_add_beautytips($options);
  }

  global $base_url;
  accessible_content_include_library();
  $test_nid = arg(4);
  $node = menu_get_object();
  $reporter = ($_GET['reporter'] == 'html')
  			  ? 'codeHighlight'
  			  : 'AccessibleContentHighlight';
  
  if (arg(5)) {
    //A field name was passed as argument 5, check that CCK field
    $field = arg(5);
    if (property_exists($node, $field)) {
      //If there is a argument 6, that is treated as the field number for multi-value fields
      $field = $node->$field;
      $text = (arg(6))
              ? $field[intval(arg(6))]['value']
              : $field[0]['value'];
  }
  //ERROR, the field doesn't exist in this node... do something!
  }
  else {
    $text = node_view($node, FALSE, TRUE, FALSE);
  }
  $quail = new quail($text, 'accessible_content', 'string', $reporter);
  $quail->setOption('cms_mode', variable_get($node->type .'_ac_ignore_cms_off', 1));
  if ($test_nid) {
    $test = node_load(arg(4));
    $quail->runCheck(array('ac_module_test' => $test));
  }
  else {
    $guideline = node_load(variable_get($node->type .'_accessibility_guideline_nid', 0));
    $quail->runCheck(array('ac_module_guideline' => $guideline,
                        'display_level' => variable_get($node->type .'_ac_display_level', 
                        array(QUAIL_TEST_SEVERE => 1, 
                            QUAIL_TEST_MODERATE => 1, 
                            QUAIL_TEST_SUGGESTION => 1)
                        )
                )
              );
  }
  return '<div id="highlight-html">'. $quail->getReport(array('image_url' => array(
          QUAIL_TEST_SEVERE => $base_url .'/'.
            variable_get('ac_ui_icon_severe',
              drupal_get_path('module', 'accessible_content') .'/images/test-demo-severe.png'),
          QUAIL_TEST_MODERATE => $base_url .'/'.
            variable_get('ac_ui_icon_moderate',
              drupal_get_path('module', 'accessible_content') .'/images/test-demo-moderate.png'),
          QUAIL_TEST_SUGGESTION => $base_url .'/'.
            variable_get('ac_ui_icon_suggestion',
              drupal_get_path('module', 'accessible_content') .'/images/test-demo-suggestion.png'),
              ),
              'highlight_classes' => array(
                QUAIL_TEST_SEVERE => variable_get('ac_ui_class_severe', 'accessibility-error-severe'),
                QUAIL_TEST_MODERATE => variable_get('ac_ui_class_moderate', 'accessibility-error-moderate'),
                QUAIL_TEST_SUGGESTION => variable_get('ac_ui_class_severe', 'accessibility-error-suggestion'),
              ),
          )) .
          '</div>';
}

/**
*  Provides an easily-parseable view of a test node for the beauty tips used on the highlight pages
*
*/
function accessible_content_accessibility_beauty_tip($node) {
  return '<div id="node-tip" class="node"><h2 class="title">'.
          $node->title .'</h2><div class="content">'.
          node_teaser($node->body) .'</div></div>';
}