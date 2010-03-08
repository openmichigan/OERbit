<?php
// $Id: menu_block.book.inc,v 1.1 2008/11/29 18:17:55 johnalbin Exp $

/**
 * @file
 * Provides book integration.
 */

/**
 * Returns a list of book menus.
 *
 * @return
 *   array The list of book menus.
 */
function book_get_menus() {
  $menus = array();
  foreach (book_get_books() AS $book) {
    $menus[$book['menu_name']] = $book['title'];
  }
  return $menus;
}
