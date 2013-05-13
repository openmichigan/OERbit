<?php

class DrupalOAuthConsumer extends OAuthConsumer {
  public $csid = 0;

  public $uid = 0;
  public $name = '';
  public $context = '';
  public $created = 0;
  public $changed = 0;
  public $callback_url = 'oob';
  public $configuration = array();

  public $provider_consumer = FALSE;
  public $in_database = FALSE;

  function __construct($key, $secret, $params = array()) {
    // Backwards compatibility with 6.x-3.0-beta3
    if (is_string($params)) {
      $callback_url = $params;
      if (func_num_args() > 4) {
        $params = func_get_arg(4);
      }
      else {
        $params = array();
      }
      $params['callback_url'] = $callback_url;
    }

    foreach ($params as $param_key => $value) {
      if (isset($this->$param_key)) {
        $this->$param_key = $value;
      }
    }

    if (!empty($this->created)) {
      $this->provider_consumer = TRUE;
    }

    parent::__construct($key, $secret, $this->callback_url);
  }

  /**
   * Writes the consumer to the database
   *
   * @return void
   */
  public function write() {
    $update = !empty($this->csid);
    $primary = $update ? array('csid') : array();

    if ($this->provider_consumer) {
      $this->changed = time();

      $values = array(
        'consumer_key'  => $this->key,
        'created'       => $this->created,
        'changed'       => $this->changed,
        'uid'           => $this->uid,
        'name'          => $this->name,
        'context'       => $this->context,
        'callback_url'  => $this->callback_url,
      );

      if ($update) {
        $values['csid'] = $this->csid;
      }
      else {
        $this->created = time();
        $values['created'] = $this->created;
      }

      $ready = drupal_write_record('oauth_common_provider_consumer', $values, $primary);

      if (!$ready) {
        throw new OAuthException("Couldn't save consumer");
      }
    }

    $values = array(
      'key_hash'      => sha1($this->key),
      'consumer_key'  => $this->key,
      'secret'        => $this->secret,
      'configuration' => serialize(empty($this->configuration) ? array() : $this->configuration),
    );

    if ($update) {
      $values['csid'] = $this->csid;
    }

    drupal_write_record('oauth_common_consumer', $values, $primary);

    $this->csid = $values['csid'];
    $this->in_database = TRUE;

    if (!$update) {
      $values = array(
        'csid' => $this->csid,
        'consumer_key' => $this->key,
      );
      drupal_write_record('oauth_common_provider_consumer', $values, array('consumer_key'));
    }
  }

  /**
   * Deletes the consumer from the database
   *
   * @return void
   */
  public function delete() {
    self::deleteConsumer($this->csid);
  }

  /**
   * Deletes the consumer with the id from the database.
   *
   * @param string $csid
   *  The consumer id.
   * @return void
   */
  public static function deleteConsumer($csid) {
    //TODO: Add compatibility layer?
    db_query("DELETE c, pc, t, pt FROM {oauth_common_consumer} c
      LEFT JOIN {oauth_common_provider_consumer} pc ON pc.csid = c.csid
      LEFT JOIN {oauth_common_token} t ON t.csid = c.csid
      LEFT JOIN {oauth_common_provider_token} pt ON pt.tid = t.tid
      WHERE c.csid = %d", array(
      ':csid' => $csid,
    ));
  }

  /**
   * Deprecated - Gets the consumer with the specified key
   *
   * @param string $key
   *  The key of the consumer to get
   * @param bool $provider_consumer
   *  Optional. Whether the consumer we're about to load is a provider or
   *  consumer consumer. Defaults to TRUE.
   * @return DrupalOAuthConsumer
   *  The loaded consumer object or FALSE if load failed
   */
  public static function load($key, $provider_consumer = TRUE) {
    return DrupalOAuthConsumer::loadProviderByKey($key, $provider_consumer);
  }

  /**
   * Gets a provider consumer with the specified id
   *
   * @param int $id
   *  The id of the consumer to get
   * @param boolean $load_provider_data
   *  Whether to load provider related data or not
   * @return DrupalOAuthConsumer
   *  The loaded consumer object or FALSE if load failed
   */
  public static function loadById($csid, $load_provider_data = TRUE) {
    $fields = 'c.csid, c.consumer_key, c.secret, c.configuration';
    $join = '';

    if ($load_provider_data) {
      $fields .= ', pc.created, pc.changed, pc.uid, pc.name, pc.context, pc.callback_url';
      $join = 'LEFT JOIN {oauth_common_provider_consumer} pc ON pc.csid = c.csid';
    }

    return self::fromResult(db_query("SELECT " . $fields . " FROM {oauth_common_consumer} c " . $join . " WHERE c.csid = %d", array(
      ':csid' => $csid,
    )));
  }

  /**
   * Gets a provider consumer with the specified key
   *
   * @param string $key
   *  The key of the consumer to get
   * @param boolean $provider
   *  Used internally for backwards compatibility with ::load()
   * @return DrupalOAuthConsumer
   *  The loaded consumer object or FALSE if load failed
   */
  public static function loadProviderByKey($key, $provider = TRUE) {
    // Only INNER supported - LEFT is only for backwards compatability with deprecated DrupalOAuthConsumer::load() from 6.x-3.0-beta3
    $join = $provider ? 'INNER' : 'LEFT';
    // For backwards compatibility with deprecated DrupalOAuthConsumer::load() from 6.x-3.0-beta3
    $where = $provider ? '' : ' AND pc.csid IS NULL';
    // For backwards compatibility with deprecated DrupalOAuthConsumer::load() from 6.x-3.0-beta3
    $fields = $provider ? 'pc.*, c.secret, c.configuration' : 'c.csid, c.consumer_key, c.secret, c.configuration, pc.created, pc.changed, pc.uid, pc.name, pc.context, pc.callback_url';

    $query = "SELECT " . $fields . " FROM {oauth_common_consumer} c " . $join . " JOIN {oauth_common_provider_consumer} pc ON pc.csid = c.csid WHERE c.key_hash = '%s'" . $where;
    return self::fromResult(db_query($query, array(
      ':key_hash' => sha1($key),
    )));
  }

  /**
   * Constructs a consumer from a db-result resource
   *
   * @param resource $res
   *  A database result resource
   * @return DrupalOAuthConsumer
   *  The constructed consumer object or NULL if no rows could be read or construction failed
   */
  public static function fromResult($res) {
    //TODO: Ensure this works with old inputs?
    if ($data = db_fetch_array($res)) {
      if (!empty($data['configuration'])) {
        $data['configuration'] = unserialize($data['configuration']);
      }
      $data['in_database'] = TRUE;
      return new DrupalOAuthConsumer($data['consumer_key'], $data['secret'], $data);
    }
    return NULL;
  }
}
