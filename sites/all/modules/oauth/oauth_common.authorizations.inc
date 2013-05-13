<?php

/**
 * @file
 * Functions related to a user's authorization section
 */

function oauth_common_page_user_authorizations($account) {
  $header = array(
    array('data' => t('Application'), 'class' => "oauth-common-authorization-application"),
    array('data' => t('Key'),         'class' => "oauth-common-authorization-key"),
    array('data' => t('Created'),     'class' => "oauth-common-authorization-created"),
    array('data' => t('Expires'),     'class' => "oauth-common-authorization-expires"),
    array('data' => t('Operations'),  'class' => "oauth-common-authorization-operations"),
  );

  $access_tokens = oauth_common_get_user_provider_tokens($account->uid);
  $rows = array();

  foreach ($access_tokens as $token) {
    $consumer = $token->consumer;

    $data = array(
      'application' => array(
        'data'  => check_plain($consumer->name),
        'class' => "oauth-common-authorization-application",
      ),
      'key' => array(
        'data'  => substr($token->key, 0, 6) . '...',
        'class' => "oauth-common-authorization-key",
      ),
      'created' => array(
        'data'  => format_date($token->created),
        'class' => "oauth-common-authorization-created",
      ),
    );
    $operations = array();

    $operations[] = array(
      'title' => t('Edit'),
      'href'  => sprintf('user/%d/oauth/authorizations/%s', $account->uid, $token->key),
      'query' => array('destination' => $_GET['q']),
    );

    $operations[] = array(
      'title' => t('Delete'),
      'href'  => sprintf('user/%d/oauth/authorizations/%s', $account->uid, $token->key) . '/delete',
      'query' => array('destination' => $_GET['q']),
    );

    $data['expires'] = array(
      'data'  => $token->expires ? format_date($token->expires) : t('Never'),
      'class' => "oauth-common-authorization-expires",
    );

    $rows[] = array(
      'data' => $data + array(
        'operations' => array(
          'data'  => theme('links', $operations),
          'class' => "oauth-common-authorization-operations",
        ),
      ),
    );
  }

  $table = theme('table', $header, $rows, array('id' => "oauth-common-list-authorization"));

  return $table;
}

function oauth_common_authorization_add($consumer) {
  $token = new DrupalOAuthToken(user_password(32), user_password(32), $consumer, array(
    'uid' => $account->uid,
  ));
  return drupal_get_form('oauth_common_form_authorization', $token);
}

function oauth_common_form_authorization($form_state, $token) {
  $form = array();

  $consumer = $token->consumer;
  $context = oauth_common_context_load($consumer->context);

  drupal_set_title(t('Authorization for @app', array('@app' => $consumer->name)));

  $form['token_object'] = array(
    '#type' => 'value',
    '#value' => $token,
  );

  $form['authorized'] = array(
    '#type' => 'checkbox',
    '#title' => t('Authorized'),
    '#default_value' => $token->authorized,
  );

  $form['created'] = array(
    '#type' => 'item',
    '#title' => t('Created'),
    '#value' => format_date($token->created),
  );

  $form['changed'] = array(
    '#type' => 'item',
    '#title' => t('Changed'),
    '#value' => format_date($token->changed),
  );

  $form['key'] = array(
    '#type' => 'item',
    '#title' => t('Key'),
    '#value' => $token->key,
  );

  if ($token->in_database) {
    $form['secret'] = array(
      '#type' => 'item',
      '#prefix' => '<div id="token-secret-wrapper">',
      '#title' => t('Secret'),
      '#value' => substr($token->secret, 0, 6) . '...',
    );

    $ahah_path = "user/{$token->uid}/oauth/authorizations/{$token->key}/ahah/secret";
    $form['show_secret'] = array(
      '#type' => 'button',
      '#value' => t('Show secret'),
      '#ahah' => array(
        'path' => $ahah_path,
        'wrapper' => 'token-secret-wrapper',
        'method' => 'replace',
      ),
      '#suffix' => '</div>',
    );
  }
  else {
    $form['secret'] = array(
      '#type' => 'item',
      '#title' => t('Secret'),
      '#value' => $token->secret
    );
  }

  $form['allowed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Permissions'),
  );
  oauth_common_permissions_form($user, $form['allowed'], $consumer, $context, $token->services);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function oauth_common_permissions_form($account, &$form, $consumer, $context, $default_services = array('*')) {
  $tvars = array(
    '@appname' => $consumer->name,
    '@user' => $account->name,
    '@sitename' => variable_get('site_name', ''),
  );

  if ($context) {
    foreach ($context->authorization_levels as $name => $level) {
      $auth_opt = array(
        '#type' => 'checkbox',
        '#title' => t($level['title'], $tvars),
        '#description' => t($level['description'], $tvars),
        '#default_value' => in_array($name, $default_services),
      );
      $form['authorization']['levels'][$name] = $auth_opt;
    }
  }
}

function oauth_common_form_authorization_submit($form, $form_state) {
  $values = $form_state['values'];
  $token = $values['token_object'];
  $consumer = $token->consumer;

  // Collect the authorization levels
  if (isset($values['levels'])) {
    $token->services = array_keys(array_filter($values['levels']));
  }

  $token->authorized = $values['authorized'];
  $token->write(TRUE);

  drupal_set_message(t('The @consumer token @token was updated.', array(
    '@consumer' => $consumer->name,
    '@token' => $token->key)));
  drupal_goto(sprintf('user/%d/applications', $form_state['values']['user']));
}

function oauth_common_form_authorization_delete($form_state, $user, $token) {
  $consumer = $token->consumer;

  $cancel_url = 'user/%d/oauth/authorizations';

  if (!empty($_GET['destination'])) {
    $cancel_url = $_GET['destination'];
  }

  drupal_set_title(t('Deleting authorization for "@consumer"', array(
    '@consumer' => $consumer->name,
  )));

  $form = array(
    'token_object' => array(
      '#type' => 'value',
      '#value' => $token,
    ),
  );

  $form['user'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
  );

  $form['key'] = array(
    '#type' => 'value',
    '#value' => $token->key,
  );

  $form['description'] = array(
    '#type' => 'item',
    '#value' => t('Are you sure that you want to delete the authorization for "@consumer"?', array(
      '@consumer' => $consumer->name,
    )),
  );

  $form['cancel'] = array(
    '#type' => 'item',
    '#value' => l(t('Cancel'), sprintf($cancel_url, $user->uid, $token->key)),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  return $form;
}

function oauth_common_form_authorization_delete_submit($form, $form_state) {
  $values = $form_state['values'];
  $token = $values['token_object'];
  $consumer = $token->consumer;
  $token->delete();
  drupal_set_message(t('The @consumer token @token was deleted.', array(
    '@consumer' => $consumer->name,
    '@token' => $token->key)));
}
