<?php
/*
 * COPYRIGHT 2011
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

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This script removes all OER data from the OERbit DB. It will delete
 * any course, resources, images you have put up post installation.
 * Author: Ali Asad Lotia <lotia@umich.edu>
 *
 * Requirememnts:
 * PHP CLI (command line version of the php interpreter).
 * PHP mysql and mysqli support.
 *
 * Since it pretty much empties the DB out, there is no shebang on the
 * first line. You must pass it to the php intepreter like so:
 * "php <path to db_cleanup.php script>"
 * Example invocation:
 * php ./db_cleanup.php
 */

class CleanDB
{
  private $db_host = "localhost";
  private $db_port = 3309;
  private $db_user = "oerpublisher";
  private $db_pass = null;
  private $db_name = "oerpublish";
  private $install_location = "/var/www/html/";

  private $db_handle = null;
  private $files_list = array();
  private $stale_files = array();

  /**
   * Tables that will be truncated by the truncate_tables() function.
   */
  private $trunc_tables =
    array(
          "aggregator_feed",
          "aggregator_item",
          "apachesolr_search_node",
          "authmap",
          "cache",
          "cache_apachesolr",
          "cache_block",
          "cache_content",
          "cache_filter",
          "cache_form",
          "cache_htmlpurifier",
          "cache_menu",
          "cache_page",
          "cache_rules",
          "cache_update",
          "cache_views",
          "cache_views_data",
	  "captcha_sessions",
          "contact",
          "hierarchical_permissions",
          "history",
          "image",
          "linkchecker_boxes",
          "linkchecker_comments",
          "linkchecker_links",
          "linkchecker_nodes",
          "node_comment_statistics",
          "print_mail_page_counter",
          "print_page_counter",
          "search_dataset",
          "search_index",
          "search_node_links",
          "search_total",
          "sessions",
          "term_data",
	  "term_hierarchy",
	  "term_node",
          "views_object_cache",
	  //"vocabulary",
	  //"vocabulary_node_types",
          "watchdog",
          "webform_submissions",
          "webform_submitted_data",
          "workflow_node_history"
          );

  /**
   * Tables which will be dropped by drop_extra_tables().
   */
  private $extra_tables =
    array(
          "cache_update_copy"
          );

  /**
   * Tables from which rows referring to deleted node.nid values are
   * deleted as the array keys. If the value isn't null, it is used
   * for setting non standard column match names. The deletion is done
   * by del_related_nodes().
   */
  private $rel_nid_ops =
    array(
	  "creativecommons_node" => null,
          "node_access" => null,
          "nodewords" => array(
                               "join_col" => "id"
                               ),
          "node_revisions" => null,
          "print_mail_node_conf" => null,
          "print_node_conf" => null,
          "workflow_node" => null,
          );


  /**
   * Tables from which rows referring to deleted node_revisions.vid
   * values are deleted as the array keys. If the value isn't null, it
   * is used for setting non standard column match names. The deletion
   * is done by del_related_versions().
   */
  private $rel_vid_ops =
    array(
	  "accessible_content_node_totals" => null,
	  "content_field_code" => null,
          "content_field_content_reference" => null,
          "content_field_contributors" => null,
          "content_field_course_instructor" => null,
          "content_field_course_level" => null,
          "content_field_course_reference" => null,
          "content_field_creators" => null,
          "content_field_file" => null,
          "content_field_instructor_academic_unit" => null,
          "content_field_parent_unit" => null,
          "content_field_publisher" => null,
          "content_field_unit_top" => null,
          "content_field_video" => null,
          "content_field_website" => null,
          "content_type_course" => null,
          "content_type_information" => null,
          "content_type_instructor" => null,
          "content_type_material" => null,
          "content_type_other" => null,
          "content_type_page" => null,
          "content_type_session" => null,
          "content_type_unit" => null
          );


  /**
   * Deletions from tables without doing any joins.
   */
  private $single_tbl_deletions =
    array(
	  "users" => array("operator" => ">"),
	  "users_roles" => array("operator" => "!="),
	  "creativecommons_user" => array("operator" => "!="),
	  "path_redirect" => array("operator" => "LIKE",
				   "column" => "source",
				   "compare_val" => "%education%"),
	  "path_redirect" => array("operator" => "LIKE",
				   "column" => "source",
				   "compare_val" => "%node%"),
	  "url_alias" => array("operator" => "LIKE",
			       "column" => "src",
			       "compare_val" => "%taxonomy%")
	  );

  /**
   * Updates of table rows.
   */
  private $single_tbl_ups =
    array(
	  "node" => array("operator" => ">"),
	  "node_revisions" => array("operator" => "!="),
	  "workflow_node" => array("operator" => "!="),
	  "accesslog" => array("operator" => "!="),
	  "files" => array("operator" => "!=")
	  );

  /**
   * Define setters.
   */
  public function set_db_pass($db_pass)
  {
    $this->db_pass = $db_pass;
  }


  public function set_db_user($db_user)
  {
    if ($db_user) {
      $this->db_user = $db_user;
    }
  }


  public function set_db_host($db_host)
  {
    if ($db_host) {
      $this->db_host = $db_host;
    }
  }


  public function set_db_port($db_port)
  {
    if ($db_port) {
      $this->db_port = $db_port;
    }
  }


  public function set_db_name($db_name)
  {
    if ($db_name) {
      $this->db_name = $db_name;
    }
  }


  public function set_install_location($path)
  {
    if ($path) {
      $this->install_location = $path;
    }
  }
  // End setter definition


  /**
   * Connect to the DB and get a database connection handle. The db
   * handle is stored in the db_handle class property.
   */
  public function db_connect()
  {
    $this->db_handle = mysqli_init();
    if (!$this->db_handle->real_connect($this->db_host,
                                        $this->db_user,
                                        $this->db_pass,
                                        $this->db_name,
                                        $this->db_port)) {
      die("Connect error (" . mysqli_connect_errno() . ") " .
          mysqli_connect_error() . "\n");
    } else {
      print "Connected to " . $this->db_handle->host_info . "\n";
    }
  }


  /**
   * Truncate the tables specified in the $trunc_tables instance array.
   */
  public function truncate_tables()
  {
    $base_query = "TRUNCATE TABLE %s; ";
    $conf_msg = "Truncated table ";

    $query = $this->build_queries_from_list($base_query,
                                          $this->trunc_tables);

    if ($this->run_multi_query($query) === 0) {
      $this->multi_query_conf($conf_msg, $this->trunc_tables);
    }
  }


  /**
   * Run the queries specified in $query. $query is a string that
   * contains one or more queries.
   *
   * Returns 0 if all the queries complete without error. The program
   * will die if any errors are encountered when running any query.
   *
   * Prints a notice that no query was specified and returns 1 if
   * $query is null or an empty string.
   *
   * @param query string contains one or more valid SQL queries
   *
   * @return int 1 if no query is specified. int 0 if all queries
   * completed successfully and there were no errors
   */
  private function run_multi_query($query)
  {
    if (!$query || (strlen($query) == 0)) {
      print "No query specified.\n";
      return 1;
    } elseif ($this->db_handle->multi_query($query)) {
      do {
        if (strlen($this->db_handle->error) > 0) {
          die("Query execution error. " .
              $this->db_handle->error . "\n");
        } else {
          // We're just deleting so we don't do anything with the
          // result. Just free the result if any so we can fire the
          // next query.
          if ($result = $this->db_handle->store_result()) {
            $result->free();
          }
        }
      } while ($this->db_handle->next_result() ||
	       (strlen($this->db_handle->error) > 0));
    }
    return 0;
  }


  /**
   * Print a confirmation message on a separate line for each item in
   * item list. The content of the confirmation message is specified
   * in $message and each member of item list is appended to that
   * message.
   *
   * @param message string the query specific message
   * @param item_list array a list of items that is appended to the
   * query specific message
   * @param fixed_auto_incr bool default FALSE prints indication that
   * that auto_increment fields was reset if TRUE.
   */
  private function multi_query_conf($message, $item_list,
				    $fixed_auto_incr = FALSE)
  {
    foreach ($item_list as $item) {
      print $message . $item;
      if ($fixed_auto_incr === TRUE) {
	print " and reset the auto increment value";
      }
      print ".\n";
    }
  }


  /**
   * Takes a base query and an array of items. Creates a series of
   * queries that are the $base_query with the value of the each
   * member of $item_list inserted in the specified position in
   * $base_query.
   *
   * @param base_query string the template query
   * @param item_list array the specific items that are inserted into
   * the template query
   *
   * @return query string the SQL queries with all the members of
   * item_list inserted into the base_query template.
   */
  private function build_queries_from_list ($base_query, $item_list)
  {
    $query = null;

    foreach ($item_list as $item) {
      $query .= sprintf($base_query, $item);
    }
    return $query;
  }


  /**
   * There are extra tables sitting around in the DB, so we drop them
   * if they still exist.
   */
  public function drop_extra_tables()
  {
    $base_query = "DROP TABLE IF EXISTS %s; ";
    $conf_msg = "Dropped table ";

    $query = $this->build_queries_from_list($base_query, $this->extra_tables);

    if ($this->run_multi_query($query) === 0) {
      $this->multi_query_conf($conf_msg, $this->extra_tables);
    }
  }


  /**
   * Prompt the user for the password of the database. Weak function
   * since we really don't do ANY input validation. Sets the db_pass
   * class property to the specified value.
   */
  public function db_pass_prompt()
  {
    print "Enter the database password: ";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_db_pass($in_line);
    }
    fclose($handle);
  }


  /**
   * Build the SQL for deletion of records from a single table.
   *
   * @param table string name of the table from which to delete records
   * @param options associative array
   * recognized keys are "operator", "column", "compare_val".
   *
   * "operator" can be any valid MySQL operator e.g. > LIKE = !=
   *
   * "column" can be any valid column in the table
   *
   * "compare_val" can be the value against which to compare the
   * column value using operation specified in the operator.
   *
   * "operator" is required. "column" and "compare_val" are optional.
   *
   * @return string query with additional query to reset the auto
   * increment value.
   */
  private function mk_single_tbl_del_query($table, $options)
  {
    $operator = $options["operator"];
    $column = null;
    $compare_val = null;

    if (isset($options["column"])) {
      $column = $options["column"];
    } else {
      $column = "uid";
    }

    if (isset($options["compare_val"])) {
      $compare_val = $options["compare_val"];
    } else {
      $compare_val = "1";
    }

    return "DELETE FROM $table WHERE " .
      "$table.$column $operator \"$compare_val\"; ";
  }


  /**
   * Delete all nodes that are OER content since we don't want any old
   * content sitting around on a freshly installed system.
   */
  public function del_content_nodes()
  {
    $del_query = "DELETE FROM node WHERE " .
      "node.type != 'webform' AND " .
      "node.type != 'page' AND " .
      "node.type NOT LIKE 'accessibility_%'; ";


    $query = $del_query . $this->fix_auto_incr_query("node");

    if ($this->run_multi_query($query) === 0) {
      print "Deleted OER content nodes and reset the auto_increment value.\n";
    }
  }


  /**
   * Build the query to set the auto increment value to 1 + the
   * current highest number in the column set to auto increment.
   *
   * @param string name of the table for which the auto increment value
   * will be fixed
   *
   * @return string SQL that will reset the auto increment value to 1
   * + the current highest number in the auto incremented column.
   */
  private function fix_auto_incr_query($table)
  {
    return "ALTER TABLE $table AUTO_INCREMENT = 1; ";
  }


  /**
   * Build the queries used by del_related_nodes() and
   * del_related_versions(). Uses the keys of the $deletions array as
   * the list of tables.
   *
   * Can match a table column other than the default "nid" against
   * node.nid if an array with the value of the key "join_col".
   *
   * @param $deletions array of tables from which content should be
   * deleted. See the $rel_nid_ops or $rel_vid_ops object properties
   * for examples.
   *
   * @param $ref_table string the table that will be LEFT joined
   *
   * @param $ref_col string the column in $ref_table against which the
   * comparison will be done.
   *
   * @return string that is the SQL for deleting rows that referred to
   * nodes deleted by del_content_nodes().
   */
  private function mk_del_related_queries($deletions, $ref_table, $ref_col)
  {
    $query = null;
    $tables = array_keys($deletions);

    foreach ($tables as $table) {
      $raw_query = "DELETE FROM $table USING $table LEFT JOIN " .
	"$ref_table ON $table.";
      // Conditional checks if "join_col" is specified and uses that
      // column name to compare against node.nid.
      if (isset($deletions[$table]["join_col"])) {
        $raw_query .= $deletions[$table]["join_col"];
      } else {
        $raw_query .= $ref_col;
      }
      $raw_query .= " = $ref_table.$ref_col WHERE " .
	"$ref_table.$ref_col IS NULL; ";
      $query .= $raw_query . $this->fix_auto_incr_query($table);
    }
    return $query;
  }


  /**
   * Delete rows in various tables that are related to the nodes
   * deleted in del_content_nodes(). For this function to do anything
   * useful, you MUST call del_content_nodes() first.
   */
  public function del_related_nodes()
  {
    $conf_msg = "Deleted rows representing deleted nodes from table ";
    $query = $this->mk_del_related_queries($this->rel_nid_ops,
					   "node",
					   "nid");

    if ($this->run_multi_query($query) === 0) {
      $this->multi_query_conf($conf_msg,
			      array_keys($this->rel_nid_ops),
			      TRUE);
    }
  }


  /**
   * A second pass on deleting content from the node_revisions
   * table. The del_related_nodes() function only deletes rows that
   * correspond to deleted nodes. This function deletes all but the
   * vid currently specified in the node table for each nid. Must run
   * after del_related_nodes()
   */
  public function del_extra_revs()
  {
    $raw_query = "DELETE FROM node_revisions USING node_revisions " .
      "LEFT JOIN node ON node_revisions.vid = node.vid WHERE node.vid IS " .
      "NULL AND node.nid IS NULL; ";

    $query = $raw_query . $this->fix_auto_incr_query("node_revisions");

    if ($this->run_multi_query($query) === 0) {
      print "Deleted all rows from node_revisions containing vid values not referenced in node.\n";
      print "Also reset the auto increment value.\n";
    }
  }


  /**
   * Delete rows in various tables that refer to the versions deleted
   * in del_extra_revs(). For this function to do anything useful, you
   * MUST call del_extra_revs() first.
   */
  public function del_related_versions()
  {
    $conf_msg = "Deleted rows representing deleted versions from table ";
    $query = $this->mk_del_related_queries($this->rel_vid_ops,
					   "node_revisions",
					   "vid");

    if ($this->run_multi_query($query) === 0) {
      $this->multi_query_conf($conf_msg,
			      array_keys($this->rel_vid_ops),
			      TRUE);
    }
  }


  /**
   * Delete rows from tables using criteria within a single
   * table. This function uses the values of the $single_tbl_deletions
   * object property.
   */
  public function do_single_table_dels() {
    $query = null;
    $conf_msg = null;

    $tables = array_keys($this->single_tbl_deletions);

    foreach($tables as $table) {
      $query .=
	$this->mk_single_tbl_del_query($table,
				       $this->single_tbl_deletions[$table]
				       );
      $query .= $this->fix_auto_incr_query($table);

      $conf_msg .= $this->single_tbl_del_conf($table);
      $conf_msg .= $this->auto_incr_reset_conf($table);
    }

    if ($this->run_multi_query($query) === 0) {
    print $conf_msg;
    }
  }


  /**
   * Generate confirmation string for deletion of records from a single
   * table.
   *
   * @param string table on which the operation is being done.
   *
   * @return string confirmation of
   */
  // TODO: Perhaps this should be made a little more general purpose
  // for all single table operations.
  private function single_tbl_del_conf($table) {
    return "Deleted unneeded rows from the $table table.\n";
  }


  /**
   * Generate string that indicates that the auto increment value has
   * been reset for the specified table.
   *
   * @param string table for which the auto increment has been reset.
   */
  private function auto_incr_reset_conf ($table) {
    return "Also reset the auto increment value in the $table table.\n";
  }


  /**
   * Generate the query to update records in specified table using
   * specified criteria.
   *
   * @param string name of the table
   * @param array options At present only the required "operator" key is
   * handled.
   *
   * @return string The SQL query for updating the specified table
   * using the specified operation.
   */
  private function mk_single_tbl_up_query($table, $options)
  {
    $operator = $options["operator"];
    $value = 1;
    $compare_val = $value;

     return "UPDATE $table SET $table.uid = \"$value\" WHERE " .
      "$table.uid $operator \"$compare_val\"; ";
  }


  /**
   * Update rows in tables defined in the single_tbl_ups object
   * property.
   */
  public function do_single_table_ups() {
    $query = null;
    $conf_msg = null;

    $tables = array_keys($this->single_tbl_ups);

    foreach($tables as $table) {
      $query .=
	$this->mk_single_tbl_up_query($table,
				      $this->single_tbl_ups[$table]
				      );

      $conf_msg .= $this->single_tbl_up_conf($table);
    }

    if ($this->run_multi_query($query) === 0) {
    print $conf_msg;
    }
  }


  /**
   * Generate confirmation string for deletion of records from a single
   * table.
   *
   * @param string table on which the operation is being done.
   *
   * @return string confirmation of
   */
  // TODO: Perhaps this should be made a little more general purpose
  // for all single table operations.
  private function single_tbl_up_conf($table) {
    return "Updated rows in the $table table.\n";
  }


  /**
   * Additional operations on the url_alias table.
   *
   * We use the MySQL regexp function. I'm almost certain that both
   * DBAs and seasoned PHP programmers will weep when they read this
   * code and see the nastiness that is present in $raw_query_2 and
   * $raw_query_3 below.
   */
  public function url_alias_cleanup()
  {
    $raw_query_1 = "DELETE FROM url_alias WHERE " .
      "url_alias.src != 'user/1' AND url_alias.src LIKE 'user/%'; ";

    // this is a HACK to get the DB cleaned up and allow comparision
    // with the node.nid values.
    $raw_query_2 = "DELETE FROM url_alias USING url_alias LEFT JOIN " .
      "node ON node.nid = SUBSTRING_INDEX(url_alias.src, '/', -1) WHERE " .
      "SUBSTRING_INDEX(url_alias.src, '/', -1) REGEXP '^[0-9]+$' AND " .
      "node.nid IS NULL; ";

    // a second pass once we have deleted all the URLs of a certain
    // form. Uses a variant of the above HACK.
    $raw_query_3 = "DELETE FROM url_alias USING url_alias LEFT JOIN ".
      "node ON node.nid = " .
      "SUBSTRING_INDEX(SUBSTRING_INDEX(url_alias.src, '/', -2), '/', 1) " .
      "WHERE SUBSTRING_INDEX(SUBSTRING_INDEX(url_alias.src, '/', -1), '/', 1)" .
      " NOT REGEXP '^[0-9]+$' AND node.nid IS NULL; ";

    $query = $raw_query_1 . $raw_query_2 . $raw_query_3 .
      $this->fix_auto_incr_query("url_alias");

    if ($this->run_multi_query($query) === 0) {
      print "Cleaned up the url_alias_table.\n" .
	$this->auto_incr_reset_conf("url_alias");
    }
  }


  /**
   * Deactivate the cosign authentication module.
   */
  public function deactivate_cosign_auth()
  {
    $query = "UPDATE system SET system.status = 0 WHERE " .
      "system.name = 'cosign' AND " .
      "system.type = 'module'; ";

    if ($this->run_multi_query($query) === 0) {
      print "Deactivated the cosign module.\n";
    }
  }


  /**
   * Get the full path to every file in the files table and save that
   * value in the files_list object property array.
   */
  private function get_all_filepaths()
  {
    $query = "SELECT filepath FROM files; ";
    $result = $this->db_handle->query($query);

    if (!$result) {
      die("The query failed.\n" . $this->db_handle->error . "\n");
    }

    while ($row = $result->fetch_row()) {
      array_push($this->files_list, $row[0]);
    }

    $result->free();
  }


  /**
   * Delete all rows from the files table that don't have a
   * corresponding file on filesystem. We do a VERY weak check to see
   * if OERbit is installed at the $install_location property by
   * seeing if the specified value is in fact a directory.
   */
  private function find_absent_files()
  {
    if (is_dir(substr($this->install_location, 0,-1))) {
      foreach ($this->files_list as $path) {
	if (!is_file($this->install_location . $path)) {
	  array_push($this->stale_files, $path);
	}
      }
    } else {
      print "The specified OERbit install location " .
	$this->install_location . " is incorrect.\n" .
	"No files table cleanup will be done.\n";
    }
  }

  /**
   * Generate the query that will be used to remove left over records
   * in the files table.
   *
   * @return string the above described query.
   */
  private function make_files_cleanup_query()
  {
    $query = null;

    if (count($this->stale_files) > 0) {
      $query = "DELETE FROM files WHERE ";

      while (count($this->stale_files) > 0) {
	$path = array_pop($this->stale_files);
	$query .= " files.filepath = '$path' ";

	if (count($this->stale_files) > 0) {
	  $query  .= " OR ";
	}
      }
      $query .= " ; ";
    }

    return $query;
  }


  /**
   * Remove any row from the files table for which there's no
   * corresponding file.
   */
  public function files_cleanup()
  {
    $this->get_all_filepaths();
    $this->find_absent_files();
    $query = $this->make_files_cleanup_query();
    if ($query && $this->db_handle->query($query)) {
      print "Removed missing files from the files table.\n";
    }
  }


  /**
   * Cleanup the filefield_meta table. This function MUST run after
   * the files_cleanup function.
   */
  public function filefield_meta_cleanup()
  {
    $query = "DELETE FROM filefield_meta USING filefield_meta LEFT JOIN " .
      "files ON filefield_meta.fid = files.fid WHERE files.fid IS NULL; ";

    if ($this->run_multi_query($query) === 0) {
      print "Removed metadata for missing files from the filefield_meta table.\n";
    }
  }


  /**
   * Inform the user that they are about to do a destructive operation
   * on the DB.
   */
  public function print_greeting()
  {
    $greeting = <<<EOG
************************************************************************
* You are about to delete content from the specified OERbit database.  *
* Make sure you have a backup of the DB before proceeding.             *
************************************************************************
EOG;
    print $greeting . "\n";
  }


  /**
   * Get the users approval before proceeding. The user MUST enter
   * 'yes' to proceed, any other response will cause the script to
   * terminate.
   */
  public function get_ok()
  {
    print "Do you wish to proceed?\n" .
      "Type 'yes' (no quotes) if you wish to proceed.\n" .
      "Any other reponse will terminate this script.\n" .
      "Proceed? ";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line != "yes") {
      die("The DB content lives to fight another day. Have a nice day!\n");
    }
    fclose($handle);
  }


  /**
   * Prompt the user for the DB host, port, name. Show defaults in
   * square brackets. This function just calls other functions that
   * actually do the work.
   */
  public function get_connection_info()
  {
    print "Enter the connection info below.\n" .
      "Defaults are shown within the square brackets [].\n";
    $this->db_host_prompt();
    $this->db_port_prompt();
    $this->db_name_prompt();
    $this->db_user_prompt();
  }


  /**
   * Prompt the user for the database host name. Weak function since
   * we really don't do ANY input validation. Sets the db_host class
   * property to the specified value.
   */
  public function db_host_prompt()
  {
    print "Enter the database host name [" . $this->db_host . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_db_host($in_line);
    }
    fclose($handle);
  }


  /**
   * Prompt the user for the database port number. Weak function since
   * we really don't do ANY input validation. Sets the db_port class
   * property to the specified value.
   */
  public function db_port_prompt()
  {
    print "Enter the database port number [" . $this->db_port . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_db_port($in_line);
    }
    fclose($handle);
  }


  /**
   * Prompt the user for the database user name. Weak function since
   * we really don't do ANY input validation. Sets the db_user class
   * property to the specified value.
   */
  public function db_user_prompt()
  {
    print "Enter the database user name [" . $this->db_user . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_db_user($in_line);
    }
    fclose($handle);
  }


  /**
   * Prompt the user for the database name. Weak function since we
   * really don't do ANY input validation. Sets the db_name class
   * property to the specified value.
   */
  public function db_name_prompt()
  {
    print "Enter the database name [" . $this->db_name . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_db_name($in_line);
    }
    fclose($handle);
  }


  /**
   * Prompt the user for full path to the directory in which drupal
   * has been installed.
   */
  public function install_location_prompt()
  {
    print "Enter the OERbit install location [" . $this->install_location . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      // check if there is a trailing slash in the supplied path. If
      // not, add one.
      if (substr($in_line, -1) != '/') {
	$in_line = $in_line . '/';
      }
      $this->set_install_location($in_line);
    }
    fclose($handle);
  }
} // end of the CleanDB class


$db_clean = new CleanDB();
$db_clean->print_greeting();
$db_clean->get_ok();
$db_clean->install_location_prompt();
$db_clean->get_connection_info();
$db_clean->db_pass_prompt();
$db_clean->db_connect();
$db_clean->drop_extra_tables();
$db_clean->truncate_tables();
//$db_clean->del_content_nodes();
$db_clean->del_related_nodes();
$db_clean->del_extra_revs();
$db_clean->del_related_versions();
$db_clean->do_single_table_dels();
$db_clean->do_single_table_ups();
// $db_clean->url_alias_cleanup();
$db_clean->files_cleanup();
$db_clean->filefield_meta_cleanup();
$db_clean->deactivate_cosign_auth();