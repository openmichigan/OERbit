<?php

/**
 *  A helper function to do cross-database concatation of date parts
 *
 *  @param $array - an array of values to be concatonated in sql
 *  @return - correct sql string for database type
 */
function date_sql_concat($array) {
  global $db_type;
  switch ($db_type) {
    case ('mysql'):
    case ('mysqli'):
      return "CONCAT(". implode(",", $array) .")";
    case ('pgsql'):
      return implode(" || ", $array);
  }
}

/**
 * Helper function to do cross-database NULL replacements
 *
 * @param an array of values to test for NULL values
 * @return SQL statement to return the first non-NULL value in the list.
 */
function date_sql_coalesce($array) {
  global $db_type;
  switch ($db_type) {
    case ('mysql'):
    case ('mysqli'):
    case ('pgsql'):
      return "COALESCE(". implode(',', $array) .")";
  }  
}

/**
 *  A helper function to do cross-database padding of date parts
 *
 *  @param $str - a string to apply padding to
 *  @param $size - the size the final string should be
 *  @param $pad - the value to pad the string with
 *  @param $side - the side of the string to pad
 */
function date_sql_pad($str, $size = 2, $pad = '0', $side = 'l') {
  switch ($side) {
  case ('r'):
    return "RPAD($str, $size, '$pad')";
  default:
    return "LPAD($str, $size, '$pad')";
  }
}

/**
 * A class to manipulate date SQL.
 */
class date_sql_handler {
  var $db_type = 'mysql';
  var $date_type = DATE_DATETIME;
  var $db_timezone = 'UTC'; // A string timezone name.
  var $local_timezone = NULL; // A string timezone name.
  var $db_timezone_field = NULL; // Use if the db timezone is stored in a field.
  var $local_timezone_field = NULL; // Use if the local timezone is stored in a field.
  var $offset_field = NULL; // Use if the offset is stored in a field.

  function construct($date_type = DATE_DATETIME, $local_timezone = NULL) {
    $this->db_type = $GLOBALS['db_type'];
    $this->date_type = $date_type;
    $this->db_timezone = 'UTC';
    $this->local_timezone = isset($local_timezone) ? $local_timezone : date_default_timezone_name();
    if (isset($this->definition['content_field'])) {
      $this->date_handler->date_type = $this->definition['content_field']['type'];
    }
    date_api_set_db_timezone();
  }

  /**
   * See if the db has timezone name support.
   */
  function db_tz_support($reset = FALSE) {
    $has_support = variable_get('date_db_tz_support', -1);
    if ($has_support == -1 || $reset) {
      date_api_set_db_timezone();
      $has_support = FALSE;
      switch ($this->db_type) {
        case 'mysql':
        case 'mysqli':
          if (version_compare(db_version(), '4.1.3', '>=')) {
            $test = db_result(db_query("SELECT CONVERT_TZ('2008-02-15 12:00:00', 'UTC', 'US/Central')"));
            if ($test == '2008-02-15 06:00:00') {
              $has_support = TRUE;
            }
          }
          break;
        case 'pgsql':
          $test = db_result(db_query("SELECT '2008-02-15 12:00:00 UTC' AT TIME ZONE 'US/Central'"));
          if ($test == '2008-02-15 06:00:00') {
            $has_support = TRUE;
          }
        break;
      }
      variable_set('date_db_tz_support', $has_support);
    }
    return $has_support;
  }

  /**
   * Set the database timzone offset.
   * 
   * Setting the db timezone to UTC is done to ensure consistency in date 
   * handling whether or not the database can do proper timezone conversion.
   * 
   * Views filters that not exposed are cached and won't set the timezone
   * so views date filters should add 'cacheable' => 'no' to their 
   * definitions to ensure that the database timezone gets set properly 
   * when the query is executed.
   * 
   * @param $offset
   *   An offset value to set the database timezone to. This will only
   *   set a fixed offset, not a timezone, so any value other than
   *   '+00:00' should be used with caution.
   */
  function set_db_timezone($offset = '+00:00') {
    static $already_set = FALSE;
    $type = $GLOBALS['db_type'];
    if (!$already_set) {
      if (($type == 'mysqli' || $type == 'mysql') && version_compare(db_version(), '4.1.3', '>=')) {
        db_query("SET @@session.time_zone = '$offset'");
      }
      elseif ($type == 'pgsql') {
        db_query("SET TIME ZONE INTERVAL '$offset' HOUR TO MINUTE");
      }
      $already_set = true;
    }
  }

  /**
   * Return timezone offset for the date being processed.
   */
  function get_offset() {
    if (!empty($this->db_timezone) && !empty($this->local_timezone)) {
      if ($this->db_timezone != $this->local_timezone) {
        $date = date_now($this->db_timezone);
        date_timezone_set($date, timezone_open($this->local_timezone));
        return date_offset_get($date);
      }
    }
    return 0;
  }

  /**
   * Helper function to create cross-database SQL dates.
   *
   * @param $field
   *   The real table and field name, like 'tablename.fieldname'.
   * @param $offset
   *   The name of a field that holds the timezone offset or an
   *   offset value. If NULL, the normal Drupal timezone handling
   *   will be used, if $offset = 0 no adjustment will be made.
   * @return
   *   An appropriate SQL string for the db type and field type.
   */
  function sql_field($field, $offset = NULL) {
    if (strtoupper($field) == 'NOW') {
      // NOW() will be in UTC since that is what we set the db timezone to.
      $this->local_timezone = 'UTC';
      return $this->sql_offset('NOW()', $offset);
    }
    switch ($this->db_type) {
      case 'mysql':
      case 'mysqli':
        switch ($this->date_type) {
          case DATE_UNIX:
            $field = "FROM_UNIXTIME($field)";
            break;
          case DATE_ISO:
            if (version_compare(db_version(), '4.1.1', '>=')) {
              $field = "STR_TO_DATE($field, '%Y-%m-%%dT%T')";
            }
            else {
              $field = "REPLACE($field, 'T', ' ')";
            }
            break;
          case DATE_DATETIME:
            break;
        }
        break;
      case 'pgsql':
        switch ($this->date_type) {
          case DATE_UNIX:
            $field = "$field::ABSTIME";
            break;
          case DATE_ISO:
            $field = "TO_DATE($field, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS')";
            break;
          case DATE_DATETIME:
            break;
        }
      break;
    }
    // Adjust the resulting value to the right timezone/offset.
    return $this->sql_tz($field, $offset);
  }

  /**
   * Adjust a field value by an offset in seconds.
   */
  function sql_offset($field, $offset = NULL) {
    if (!empty($offset)) {
      switch ($this->db_type) {
        case 'mysql':
        case 'mysqli':
          if (version_compare(db_version(), '4.1.1', '>=')) {
            return "ADDTIME($field, SEC_TO_TIME($offset))";
          }
          else {
            return "DATE_ADD($field, INTERVAL $offset SECOND)";
          }
        case 'pgsql':
          return "($field + INTERVAL '$offset SECONDS')";;
      }
    }
    return $field;
  }

  /**
   * Adjust a field value by time interval.
   * 
   * @param $field
   *   The field to be adjusted.
   * @param $direction
   *   Either ADD or SUB.
   * @param $count
   *   The number of values to adjust.
   * @param $granularity
   *   The granularity of the adjustment, should be singular,
   *   like SECOND, MINUTE, DAY, HOUR.
   */
  function sql_date_math($field, $direction, $count, $granularity) {
    $granularity = strtoupper($granularity);
    switch ($this->db_type) {
      case 'mysql':
      case 'mysqli':
        switch ($direction) {
          case 'ADD':
            return "DATE_ADD($field, INTERVAL $count $granularity)";
          case 'SUB':
            return "DATE_SUB($field, INTERVAL $count $granularity)";
          }

      case 'pgsql':
        $granularity .= 'S';
        switch ($direction) {
          case 'ADD':
            return "($field + INTERVAL '$count $granularity')";
          case 'SUB':
            return "($field - INTERVAL '$count $granularity')";
        }
     }
     return $field;
  }  

  /**
   * Select a date value from the database, adjusting the value
   * for the timezone.
   * 
   * Check whether database timezone conversion is supported in
   * this system and use it if possible, otherwise use an
   * offset.
   * 
   * @param $offset
   *   Set a fixed offset or offset field to use for the date. 
   *   If set, no timezone conversion will be done and the 
   *   offset will be used.
   */
  function sql_tz($field, $offset = NULL) {
    // If the timezones are values they need to be quoted, but
    // if they are field names they do not.
    $db_zone   = $this->db_timezone_field ? $this->db_timezone_field : "'{$this->db_timezone}'";
    $localzone = $this->local_timezone_field ? $this->local_timezone_field : "'{$this->local_timezone}'"; 

    // If a fixed offset is required, use it.
    if ($offset !== NULL) {
      return $this->sql_offset($field, $offset);
    }
    // If the db and local timezones are the same, make no adjustment.
    elseif ($db_zone == $localzone) {
      return $this->sql_offset($field, 0);
    }
    // If the db has no timezone support, adjust by the offset,
    // could be either a field name or a value.
    elseif (!$this->db_tz_support()) {
      if (!empty($this->offset_field)) {
        return $this->sql_offset($field, $this->offset_field);
      }
      else {
        return $this->sql_offset($field, $this->get_offset());
      }
    }
    // Otherwise make a database timezone adjustment to the field.
    else {
      switch ($this->db_type) {
        case 'mysql':
        case 'mysqli':
          return "CONVERT_TZ($field, $db_zone, $localzone)";
        case 'pgsql':
          // WITH TIME ZONE assumes the date is using the system
          // timezone, which should have been set to UTC.
          return "$field::timestamp with time zone AT TIME ZONE $localzone";
      }
    }
  }

  /**
   * Helper function to create cross-database SQL date formatting.
   *
   * @param $format
   *   A format string for the result, like 'Y-m-d H:i:s'.
   * @param $field
   *   The real table and field name, like 'tablename.fieldname'.
   * @return
   *   An appropriate SQL string for the db type and field type.
   */
  function sql_format($format, $field) {
    switch ($this->db_type) {
      case 'mysql':
      case 'mysqli':
        $replace = array(
          'Y' => '%Y', 'y' => '%y',
          'm' => '%m', 'n' => '%c',
          'd' => '%%d', 'j' => '%e',
          'H' => '%H',
          'i' => '%i',
          's' => '%%s',
          '\WW' => 'W%U',
          );
        $format = strtr($format, $replace);
        return "DATE_FORMAT($field, '$format')";
      case 'pgsql':
        $replace = array(
          'Y' => 'YYYY', 'y' => 'Y',
          'm' => 'MM', 'n' => 'M',
          'd' => 'DD', 'j' => 'D',
          'H' => 'HH24',
          'i' => 'MI',
          's' => 'SS',
          '\T' => '"T"',
          //'\W' => // TODO, what should this be?
          );
        $format = strtr($format, $replace);
        return "TO_CHAR($field, '$format')";
    }
  }

  /**
   * Helper function to create cross-database SQL date extraction.
   *
   * @param $extract_type
   *   The type of value to extract from the date, like 'MONTH'.
   * @param $field
   *   The real table and field name, like 'tablename.fieldname'.
   * @return
   *   An appropriate SQL string for the db type and field type.
   */
  function sql_extract($extract_type, $field) {
    // Note there is no space after FROM to avoid db_rewrite problems
    // see http://drupal.org/node/79904.
    switch (strtoupper($extract_type)) {
    case ('DATE'):
      return $field;
    case ('YEAR'):
      return "EXTRACT(YEAR FROM($field))";
    case ('MONTH'):
      return "EXTRACT(MONTH FROM($field))";
    case ('DAY'):
      return "EXTRACT(DAY FROM($field))";
    case ('HOUR'):
      return "EXTRACT(HOUR FROM($field))";
    case ('MINUTE'):
      return "EXTRACT(MINUTE FROM($field))";
    case ('SECOND'):
      return "EXTRACT(SECOND FROM($field))";
    case ('WEEK'):  // ISO week number for date
      switch ($this->db_type) {
        case ('mysql'):
        case ('mysqli'):
          // WEEK using arg 3 in mysql should return the same value as postgres EXTRACT
          return "WEEK($field, 3)";
        case ('pgsql'):
          return "EXTRACT(WEEK FROM($field))";
      }
    case ('DOW'):
      switch ($this->db_type) {
        case ('mysql'):
        case ('mysqli'):
          // mysql returns 1 for Sunday through 7 for Saturday
          // php date functions and postgres use 0 for Sunday and 6 for Saturday
          return "INTEGER(DAYOFWEEK($field) - 1)";
        case ('pgsql'):
          return "EXTRACT(DOW FROM($field))";
      }
    case ('DOY'):
      switch ($this->db_type) {
        case ('mysql'):
        case ('mysqli'):
          return "DAYOFYEAR($field)";
        case ('pgsql'):
          return "EXTRACT(DOY FROM($field))";
      }
    }
  }

  /**
   * Create a where clause to compare a complete date field to a complete date value.
   *
   * @param string $type
   *   The type of value we're comparing to, could be another field
   *   or a date value.
   * @param string $field
   *   The db table and field name, like "$table.$field".
   * @param string $operator
   *   The db comparison operator to use, like '='.
   * @param int $value
   *   The value to compare the extracted date part to, could be a
   *   field name or a date string or NOW().
   * @return 
   *   SQL for the where clause for this operation.
   */
  function sql_where_date($type, $field, $operator, $value, $adjustment = 0) {
    $type = strtoupper($type);
    if (strtoupper($value) == 'NOW') {
      $value = $this->sql_field('NOW', $adjustment);
    }
    elseif ($type == 'FIELD') {
      $value = $this->sql_field($value, $adjustment);
    }    
    elseif ($type == 'DATE') {
      $date = date_make_date($value, date_default_timezone_name(), DATE_DATETIME);
      if (!empty($adjustment)) {
        date_modify($date, $adjustment .' seconds');
      }
      // When comparing a field to a date we can avoid doing timezone 
      // conversion by altering the comparison date to the db timezone.
      // This won't work if the timezone is a field instead of a value.
      if (empty($this->db_timezone_field) && empty($this->local_timezone_field) && $this->db_timezone_field != $this->local_timezone_field) {
        date_timezone_set($date, timezone_open($this->db_timezone));
        $this->local_timezone = $this->db_timezone;
      }
      $value = "'". date_format_date($date, 'custom', DATE_FORMAT_DATETIME) ."'";
    }    
    if ($this->local_timezone != $this->db_timezone) {
      $field = $this->sql_field($field);
    }
    else {
      $field = $this->sql_field($field, 0);
    }
    return "$field $operator $value";
  }

  /**
   * Create a where clause to compare an extracted part of a field to an integer value.
   *
   * @param string $part
   *   The part to extract, YEAR, MONTH, DAY, etc.
   * @param string $field
   *   The db table and field name, like "$table.$field".
   * @param string $operator
   *   The db comparison operator to use, like '='.
   * @param int $value
   *   The integer value to compare the extracted date part to.
   * @return 
   *   SQL for the where clause for this operation.
   */
  function sql_where_extract($part, $field, $operator, $value, $adjustment = 0) {
    $field = $this->sql_field($field, $adjustment);
    return $this->sql_extract($part, $field) ." $operator $value";
  }

  /**
   * Create a where clause to compare a formated field to a formated value.
   *
   * @param string $format
   *   The format to use on the date and the value when comparing them.
   * @param string $field
   *   The db table and field name, like "$table.$field".
   * @param string $operator
   *   The db comparison operator to use, like '='.
   * @param string $value
   *   The value to compare the extracted date part to, could be a
   *   field name or a date string or NOW().
   * @return 
   *   SQL for the where clause for this operation.
   */
  function sql_where_format($format, $field, $operator, $value, $adjustment = 0) {
    $field = $this->sql_field($field, $adjustment);
    return $this->sql_format($format, $field) ." $operator '$value'";
  }

  /**
   * An array of all date parts,
   * optionally limited to an array of allowed parts.
   */
  function date_parts($limit = NULL) {
    $parts =  array(
      'year' => date_t('Year', 'datetime'), 'month' => date_t('Month', 'datetime'), 'day' => date_t('Day', 'datetime'),
      'hour' => date_t('Hour', 'datetime'), 'minute' => date_t('Minute', 'datetime'), 'second' => date_t('Second', 'datetime'),
      );
    if (!empty($limit)) {
      $last = FALSE;
      foreach ($parts as $key => $part) {
        if ($last) {
          unset($parts[$key]);
        }
        if ($key == $limit) {
          $last = TRUE;
        }
      }
    }
    return $parts;
  }

  /**
   * Part information.
   *
   * @param $op
   *   'min', 'max', 'format', 'sep', 'empty_now', 'empty_min', 'empty_max'. 
   *   Returns all info if empty.
   * @param $part
   *   'year', 'month', 'day', 'hour', 'minute', or 'second.
   *   returns info for all parts if empty.
   */
  function part_info($op = NULL, $part = NULL) {
    $info = array();
    $info['min'] = array(
      'year' => 100, 'month' => 1, 'day' => 1,
      'hour' => 0, 'minute' => 0, 'second' => 0);
    $info['max'] = array(
      'year' => 4000, 'month' => 12, 'day' => 31,
      'hour' => 23, 'minute' => 59, 'second' => 59);
    $info['format'] = array(
      'year' => 'Y', 'month' => 'm', 'day' => 'd',
      'hour' => 'H', 'minute' => 'i', 'second' => 's');
    $info['sep'] = array(
      'year' => '', 'month' => '-', 'day' => '-',
      'hour' => ' ', 'minute' => ':', 'second' => ':');
    $info['empty_now'] = array(
      'year' => date('Y'), 'month' => date('m'), 'day' => min('28', date('d')),
      'hour' => date('H'), 'minute' => date('i'), 'second' => date('s'));  
    $info['empty_min'] = array(
      'year' => '1000', 'month' => '01', 'day' => '01',
      'hour' => '00', 'minute' => '00', 'second' => '00');  
    $info['empty_max'] = array(
      'year' => '9999', 'month' => '12', 'day' => '31',
      'hour' => '23', 'minute' => '59', 'second' => '59');  
    if (!empty($op)) {
      if (!empty($part)) {
        return $info[$op][$part];
      }
      else {
        return $info[$op];
      }
    }
    return $info;
  }

  /**
   * Create a complete datetime value out of an 
   * incomplete array of selected values.
   * 
   * For example, array('year' => 2008, 'month' => 05) will fill
   * in the day, hour, minute and second with the earliest possible
   * values if type = 'min', the latest possible values if type = 'max',
   * and the current values if type = 'now'.
   */
  function complete_date($selected, $type = 'now') {
    if (empty($selected)) {
      return '';
    }
    // Special case for weeks.
    if (array_key_exists('week', $selected)) {
      $dates = date_week_range($selected['week'], $selected['year']);
      switch ($type) {
        case 'empty_now':
        case 'empty_min':
        case 'min':
          return date_format($dates[0], 'Y-m-d H:i:s');
        case 'empty_max':
        case 'max':
          return date_format($dates[1], 'Y-m-d H:i:s');
        default:
          return;
      }
    }

    $compare = array_merge($this->part_info('empty_'. $type), $selected);
    // If this is a max date, make sure the last day of 
    // the month is the right one for this date.
    if ($type == 'max') {
      $compare['day'] = date_days_in_month($compare['year'], $compare['month']);
    }
    $value = '';
    $separators = $this->part_info('sep');
    foreach ($this->date_parts() as $key => $name) {
      $value .= $separators[$key] . (!empty($selected[$key]) ? $selected[$key] : $compare[$key]);
    }
    return $value;
  }
  /**
   * Convert a format string into help text,
   * i.e. 'Y-m-d' becomes 'YYYY-MM-DD'.
   *
   * @param unknown_type $format
   * @return unknown
   */
  function format_help($format) {
    $replace = array(
      'Y' => 'YYYY', 'm' => 'MM', 'd' => 'DD',
      'H' => 'HH', 'i' => 'MM', 's' => 'SS', '\T' => 'T');
    return strtr($format, $replace);
  }

  /**
   *  A function to test the validity of various date parts
   */
  function part_is_valid($value, $type) {
    if ( !preg_match('/^[0-9]*$/', $value) ) {
      return false;
    }
    $value = intval($value);
    if ($value <= 0) return false;
    switch ($type) {
      case 'year':
        if ($value < DATE_MIN_YEAR) return false;
        break;
      case 'month':
        if ($value < 0 || $value > 12) return false;
        break;
      case 'day':
        if ($value < 0 || $value > 31) return false;
        break;
      case 'week':
        if ($value < 0 || $value > 53) return false;
    }
    return true;
  }

  function views_formats($granularity, $type = 'sql') {
    $formats = array('display', 'sql');
    // Start with the site long date format and add seconds to it
    $long = str_replace(':i', ':i:s', variable_get('date_format_long',  'l, F j, Y - H:i'));
    switch ($granularity) {
      case ('year'):
        $formats['display'] = 'Y';
        $formats['sql'] = 'Y';
        break;
      case ('month'):
        $formats['display'] = date_limit_format($long, array('year', 'month'));
        $formats['sql'] = 'Y-m';
        break;
      case ('day'):
        $formats['display'] = date_limit_format($long, array('year', 'month', 'day'));
        $formats['sql'] = 'Y-m-d';
        break;
      case ('hour'):
        $formats['display'] = date_limit_format($long, array('year', 'month', 'day', 'hour'));
        $formats['sql'] = 'Y-m-d\TH';
        break;
      case ('minute'):
        $formats['display'] = date_limit_format($long, array('year', 'month', 'day', 'hour', 'minute'));
        $formats['sql'] = 'Y-m-d\TH:i';
        break;
      case ('second'):
        $formats['display'] = date_limit_format($long, array('year', 'month', 'day', 'hour', 'minute', 'second'));
        $formats['sql'] = 'Y-m-d\TH:i:s';
        break;
      case ('week'):
        $formats['display'] = 'F j Y (W)';
        $formats['sql'] = 'Y-\WW';
        break;
    }
    return $formats[$type];
  }

  function granularity_form($granularity) {
    $form = array(
      '#title' => t('Granularity'),
      '#type' => 'radios',
      '#default_value' => $granularity,
      '#options' => $this->date_parts(),
      );
    return $form;
  }

  /**
   * Parse date parts from an ISO date argument.
   * 
   * Based on ISO 8601 date duration and time interval standards.
   *
   * See http://en.wikipedia.org/wiki/ISO_8601#Week_dates for definitions of ISO weeks.
   * See http://en.wikipedia.org/wiki/ISO_8601#Duration for definitions of ISO duration and time interval.
   *
   * Parses a value like 2006-01-01--2006-01-15, or 2006-W24, or @P1W.
   * Separate from and to dates or date and period with a double hyphen (--).
   *
   * The 'to' portion of the argument can be eliminated if it is the same as the 'from' portion.
   * Use @ instead of a date to substitute in the current date and time.
   *
   * Use periods (P1H, P1D, P1W, P1M, P1Y) to get next hour/day/week/month/year from now.
   * Use date before P sign to get next hour/day/week/month/year from that date.
   * Use period then date to get a period that ends on the date.
   *
   */
  function arg_parts($argument) {
    $values = array();
    // Keep mal-formed arguments from creating errors.
    if (empty($argument) || is_array($argument)) {
      return array('date' => array(), 'period' => array());
    }
    $fromto = explode('--', $argument);
    foreach ($fromto as $arg) {
      $parts = array();
      if ($arg == '@') {
        $parts['date'] = date_array(date_now());
      }
      elseif (preg_match('/(\d{4})?-?(W)?(\d{1,2})?-?(\d{1,2})?[T\s]?(\d{1,2})?:?(\d{1,2})?:?(\d{1,2})?/', $arg, $matches)) {
        $date = array();
        if (!empty($matches[1])) $date['year'] = $matches[1];
        if (!empty($matches[3])) {
          if (empty($matches[2])) {
            $date['month'] = $matches[3];
          }
          else {
            $date['week'] = $matches[3];
          }    
        }
        if (!empty($matches[4])) $date['day'] = $matches[4];
        if (!empty($matches[5])) $date['hour'] = $matches[5];
        if (!empty($matches[6])) $date['minute'] = $matches[6];
        if (!empty($matches[7])) $date['second'] = $matches[7];
        $parts['date'] = $date;
      }
      if (preg_match('/^P(\d{1,4}[Y])?(\d{1,2}[M])?(\d{1,2}[W])?(\d{1,2}[D])?([T]{0,1})?(\d{1,2}[H])?(\d{1,2}[M])?(\d{1,2}[S])?/', $arg, $matches)) {
        $period = array();
        if (!empty($matches[1])) $period['year'] =  str_replace('Y', '', $matches[1]);
        if (!empty($matches[2])) $period['month'] = str_replace('M', '', $matches[2]);
        if (!empty($matches[3])) $period['week'] = str_replace('W', '', $matches[3]);
        if (!empty($matches[4])) $period['day'] = str_replace('D', '', $matches[4]);
        if (!empty($matches[6])) $period['hour'] = str_replace('H', '', $matches[6]);
        if (!empty($matches[7])) $period['minute'] = str_replace('M', '', $matches[7]);
        if (!empty($matches[8])) $period['second'] = str_replace('S', '', $matches[8]);
        $parts['period'] = $period;
      }
      $values[] = $parts;
    }
    return $values;
  }

  /**
   * Convert strings like '+1 day' to the ISO equivalent, like 'P1D'.
   */
  function arg_replace($arg) {
    if (!preg_match('/([+|-])\s?([0-9]{1,32})\s?([day(s)?|week(s)?|month(s)?|year(s)?|hour(s)?|minute(s)?|second(s)?]{1,10})/', $arg, $results)) {
      return str_replace('now', '@', $arg);
    }
    $direction = $results[1];
    $count = $results[2];
    $item = $results[3];

    $replace = array(
      'now' => '@',
      '+' => 'P',
      '-' => 'P-',
      'years' => 'Y',
      'year' => 'Y',
      'months' => 'M',
      'month' => 'M',
      'weeks' => 'W',
      'week' => 'W',
      'days' => 'D',
      'day' => 'D',
      'hours' => 'H',
      'hour' => 'H',
      'minutes' => 'M',
      'minute' => 'M',
      'seconds' => 'S',
      'second' => 'S',
      '  ' => '',
      ' ' => '',
      );
    $prefix = in_array($item, array('hours', 'hour', 'minutes', 'minute', 'seconds', 'second')) ? 'T' : '';  
    return $prefix . strtr($direction, $replace) . $count . strtr($item, $replace);  
  }

  /**
   * Use the parsed values from the ISO argument to determine the
   * granularity of this period.
   */
  function arg_granularity($arg) {
    $granularity = '';
    $parts = $this->arg_parts($arg);
    $date = !empty($parts[0]['date']) ? $parts[0]['date'] : (!empty($parts[1]['date']) ? $parts[1]['date'] : array());
    foreach ($date as $key => $part) {
      $granularity = $key;    
    }
    return $granularity;
  }

  /**
   * Use the parsed values from the ISO argument to determine the
   * min and max date for this period.
   */
  function arg_range($arg) {
    // Parse the argument to get its parts
    $parts = $this->arg_parts($arg);

    // Build a range from a period-only argument (assumes the min date is now.)
    if (empty($parts[0]['date']) && !empty($parts[0]['period']) && (empty($parts[1]))) {
      $min_date = date_now();
      $max_date = drupal_clone($min_date);
      foreach ($parts[0]['period'] as $part => $value) {
        date_modify($max_date, "+$value $part");
      }
      date_modify($max_date, '-1 second');
      return array($min_date, $max_date);
    }
    // Build a range from a period to period argument
    if (empty($parts[0]['date']) && !empty($parts[0]['period']) && !empty($parts[1]['period'])) {
      $min_date = date_now();
      $max_date = drupal_clone($min_date);
      foreach ($parts[0]['period'] as $part => $value) {
        date_modify($min_date, "+$value $part");
      }
      date_modify($min_date, '-1 second');
      foreach ($parts[1]['period'] as $part => $value) {
        date_modify($max_date, "+$value $part");
      }
      date_modify($max_date, '-1 second');
      return array($min_date, $max_date);
    }
    if (!empty($parts[0]['date'])) {
      $value = date_fuzzy_datetime($this->complete_date($parts[0]['date'], 'min'));
      $min_date = date_make_date($value, date_default_timezone_name(), DATE_ISO);
      // Build a range from a single date-only argument.
      if (empty($parts[1]) || (empty($parts[1]['date']) && empty($parts[1]['period']))) {
        $value = date_fuzzy_datetime($this->complete_date($parts[0]['date'], 'max'));
        $max_date = date_make_date($value, date_default_timezone_name(), DATE_ISO);
        return array($min_date, $max_date);
      }
      // Build a range from start date + period.
      elseif (!empty($parts[1]['period'])) {
        foreach ($parts[1]['period'] as $part => $value) {
          $max_date = drupal_clone($min_date);
          date_modify($max_date, "+$value $part");
        }
        date_modify($max_date, '-1 second');
        return array($min_date, $max_date);
      }
    }
    // Build a range from start date and end date.
    if (!empty($parts[1]['date'])) {
      $value = date_fuzzy_datetime($this->complete_date($parts[1]['date'], 'max'));
      $max_date = date_make_date($value, date_default_timezone_name(), DATE_ISO);
      if (isset($min_date)) {
        return array($min_date, $max_date);
      }
    }
    // Build a range from period + end date.
    if (!empty($parts[0]['period'])) {
      $min_date = date_now();
      foreach ($parts[0]['period'] as $part => $value) {
        date_modify($min_date, "$value $part");
      }
      return array($min_date, $max_date);
    }
     // Intercept invalid info and fall back to the current date.
    $now = date_now();
    return array($now, $now);
 }
}