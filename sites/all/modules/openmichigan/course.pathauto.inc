<?php
// $Id$

/*
 * COPYRIGHT 2011
 *
 * The Regents of the University of Michigan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.
 *
 * You may not use the name of The University of Michigan in any
 * advertising or publicity pertaining to the use of distribution of this software
 * without specific, written prior authorization. If the above copyright notice
 * or any other identification of the University of Michigan is included in any
 * copy of any portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INDIRECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Update path aliases for the course page.
 */
function course_pathauto_alias(&$node, $op) {
  switch ($op) {
    case 'insert':
    case 'update':
    case 'bulkupdate':
      if (module_exists('pathauto')) {
        module_load_include('inc', 'pathauto');
        $alias = 'node/' . $node->nid;
        $placeholders = pathauto_get_placeholders('node', $node);
        pathauto_create_alias('course', $op, $placeholders, $alias . '/overview', $node->nid, 'overview');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/sessions', $node->nid, 'sessions');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/materials', $node->nid, 'materials');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/highlights', $node->nid, 'highlights');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/rss', $node->nid, 'rss');
        pathauto_create_alias('course', $op, $placeholders, $alias . '/rdf', $node->nid, 'rdf');
      }
      break;
    case 'delete':
      if (module_exists('pathauto')) {
        module_load_include('inc', 'pathauto');
        path_set_alias('node/' . $node->nid . '/overview');
        path_set_alias('node/' . $node->nid . '/sessions');
        path_set_alias('node/' . $node->nid . '/materials');
        path_set_alias('node/' . $node->nid . '/highlights');
        path_set_alias('node/' . $node->nid . '/rss');
        path_set_alias('node/' . $node->nid . '/rdf');
      }
      break;
  }
}
