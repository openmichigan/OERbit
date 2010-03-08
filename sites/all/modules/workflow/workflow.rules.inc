<?php
// $Id: workflow.rules.inc,v 1.1.2.1 2010/02/19 22:30:31 jvandyk Exp $

/**
 * @file
 * Rules integration for the Workflow module
 */

/**
 * Implementation of hook_rules_event_info().
 */
function workflow_rules_event_info() {
  $events = array(
    'workflow_state_changed' => array(
      'label' => t('Workflow state has changed'),
      'module' => 'Workflow',
      'arguments' =>  workflow_events_workflow_arguments(),
    ),
    'workflow_comment_added' => array(
      'label' => t('Workflow comment was added'),
      'module' => 'Workflow',
      'arguments' =>  workflow_events_workflow_arguments(),
      'description' => t('New workflow comment was added, but the workflow state did not change.'),
    ),
  );
  return $events;
}

/**
 * Returns arguments for a workflow event.
 */
function workflow_events_workflow_arguments() {
  return array(
    'node' => array('type' => 'node', 'label' => t('Updated content')),
    'old_state' => array('type' => 'workflow_state', 'label' => t('Old workflow state')),
    'new_state' => array('type' => 'workflow_state', 'label' => t('New workflow state')),
    'author' => array('type' => 'user', 'label' => t('Content author'), 'handler' => 'rules_events_argument_node_author'),
  ) + rules_events_global_user_argument();
}

/**
 * Implementation of hook_condition_info().
 */
function workflow_rules_condition_info() {
  return array(
    'workflow_check_transition' => array(
      'label' => t('Check workflow transition'),
      'arguments' => array(
        'old_state' => array('type' => 'workflow_state', 'label' => t('Old workflow state')),
        'new_state' => array('type' => 'workflow_state', 'label' => t('New workflow state')),
      ),
      'help' => t('Evaluates to TRUE, if the workflow being updated is moved from state A to state B'),
      'module' => 'Workflow',
    ),
  );
}

/**
 * Condition implementation: check state transition. 
 */
function workflow_check_transition($old_state, $new_state, $settings) {
  if (in_array('ANY', $settings['from_state'])) {
    if (in_array('ANY', $settings['to_state'])) {
      return TRUE;
    }
    return in_array($new_state, $settings['to_state']);
  }
  if (in_array('ANY', $settings['to_state'])) {
    return in_array($old_state, $settings['from_state']);
  }
  return  in_array($old_state, $settings['from_state']) &&  in_array($new_state, $settings['to_state']);
}

/**
 * Implementation of hook_rules_action_info_alter().
 */
function workflow_rules_action_info_alter(&$actions) {
  $actions['rules_core_workflow_select_next_state_action']['module'] = 'Workflow';
  $actions['rules_core_workflow_select_given_state_action']['module'] = 'Workflow';
}

/**
 * Implementation of hook_rules_data_type_info().
 */
function workflow_rules_data_type_info() {
  return array(
    'workflow_state' => array(
      'label' => t('Workflow state'),
      'class' => 'rules_data_type',
      'savable' => FALSE,
      'identifiable' => TRUE,
      'uses_input_form' => FALSE,
      'token type' => FALSE, 
      'module' => 'Workflow',
    ),
  );
}

