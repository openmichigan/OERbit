<?php
// $Id: weight_handler_field_sticky.inc,v 1.2.2.2 2009/01/26 00:28:54 nancyw Exp $
/**
 * @file
 * Field handler for Weight module.
 */

class weight_handler_field_sticky extends views_handler_field_numeric {
  function render($values) {
    $value = $values->{$this->field_alias};
    // convert sticky values to corresponding weights.
    if ($value > 0) {
      $value = $value == 1 ? 0 : (100 - $value);
    }
    else {
      $value = $value == 0 ? 0 : -($value + 100);
    }
    if (!empty($this->options['set_precision'])) {
      $value = number_format($value, $this->options['precision'], $this->options['decimal'], $this->options['separator']);
    }
    else {
      $remainder = abs($value) - intval(abs($value));
      $value = number_format($value, 0, '', $this->options['separator']);
      if ($remainder) {
        $value .= $this->options['decimal'] . $remainder;
      }
    }
    return check_plain($this->options['prefix'] . $value . $this->options['suffix']);
  }   
}
