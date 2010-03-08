<?php
// $Id: weight_handler_sort.inc,v 1.2.2.2 2009/01/26 00:28:54 nancyw Exp $
/**
 * @file
 * Sort handler for Weight module.
 */
class weight_handler_sort extends views_handler_sort {

   function query() {
   $this->ensure_my_table();
   // Reverse ASC and DESC for weight order so that the sticky weights are ordered like real weights.
   if ($this->options['order'] == 'ASC') {
     $this->options['order'] = 'DESC';
   }
   elseif ($this->options['order'] == 'DESC') {
     $this->options['order'] = 'ASC';
   }
   $this->query->add_orderby($this->table_alias, $this->real_field, $this->options['order']);
 }
}
