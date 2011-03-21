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

<?php
/**
 * This script provides a very simplified way to reset the username
 * and password of the predefined uid=1 OERbit user.
 * Author: Ali Asad Lotia <lotia@umich.edu>
 *
 * Requirememnts:
 * PHP CLI (command line version of the php interpreter).
 * PHP mysql and mysqli support.
 *
 * Since it does something pretty drastic, there is no shebang on the
 * first line. You must pass it to the php intepreter like so:
 * "php <path to reset_admin_info.php script>"
 * Example invocation:
 * php ./reset_admin_info.php
 */


class ResetAdminInfo
{
  private $db_host = "localhost";
  private $db_port = 3309;
  private $db_user = "oerpublisher";
  private $db_pass = null;
  private $db_name = "oerpublish";

  private $db_handle = null;

  private $admin_user = "admin";
  private $admin_pass = null;

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


  public function set_admin_user($admin_user)
  {
    if ($admin_user) {
      $this->admin_user = $admin_user;
    }
  }


  public function set_admin_pass($admin_pass)
  {
    if ($admin_pass) {
      $this->admin_pass = $admin_pass;
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
   * Inform the user that they are about to do a destructive operation
   * on the DB.
   */
  public function print_greeting()
  {
    $greeting = <<<EOG
************************************************************************
* You are about to reset the admin username and password in the        *
* specified OERbit database.                                           *
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
   * Prompt the user for the OERbit admin username. Weak function
   * since we really don't do ANY input validation. Sets the db_name
   * class property to the specified value.
   */
  private function admin_user_prompt()
  {
    print "Enter the admin username, no spaces [" . $this->admin_user . "]:";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line) {
      $this->set_admin_user($in_line);
    }
    fclose($handle);
  }


  /**
   * Prompt the user for the OERbit admin password. Weak function
   * since we really don't do ANY input validation. Sets the db_name
   * class property to the specified value.
   */
  public function admin_pass_prompt()
  {
    print "Enter the admin password: ";
    $handle = fopen("php://stdin", "r");
    $in_line = trim(fgets($handle));
    if ($in_line && (strlen($in_line) > 5)) {
      $this->set_admin_pass($in_line);
    } else {
      print "You must specify a password 6 characters or longer.\n";
      $this->admin_pass_prompt();
    }
    fclose($handle);
  }


  /**
   * Reset the username of the admin user. We also reset the alias
   * pointing to the user page. Basic attempt at guarding against SQL
   * injection in entered values by using prepared statements.
   */
  public function reset_admin_user()
  {
    $this->admin_user_prompt();
    $dummy_email = $this->admin_user . "@localhost";
    $users_query = "UPDATE users SET  " .
      "users.name = ?, users.mail = ?, users.init = ? WHERE users.uid = 1";
    $users_statement = $this->db_handle->prepare($users_query);
    $users_statement->bind_param('sss',
				 $this->admin_user,
				 $dummy_email,
				 $dummy_email);
    if ($users_statement->execute()) {
      print "Reset the admin username to " . $this->admin_user . ".\n" .
	"Reset the admin email to $dummy_email.\n";
    }

    $url_alias_dst = "users/" . $this->admin_user;
    $url_alias_query = "UPDATE url_alias SET url_alias.dst = ? " .
      "WHERE url_alias.src = 'user/1'";
    $url_alias_statement = $this->db_handle->prepare($url_alias_query);
    $url_alias_statement->bind_param('s', $url_alias_dst);
    if ($url_alias_statement->execute()) {
      print "Reset the user/1 url alias to $url_alias_dst.\n";
    }
  }


  /**
   * Reset the password of the admin user. Basic attempt at guarding
   * against SQL injection in entered values by using prepared
   * statements.
   */
  public function reset_admin_pass()
  {
    $this->admin_pass_prompt();
    $pass_query = "UPDATE users SET users.pass = MD5(?) WHERE users.uid = 1";
    $pass_statement = $this->db_handle->prepare($pass_query);
    $pass_statement->bind_param('s', $this->admin_pass);
    if ($pass_statement->execute()) {
      print "Reset the admin password to the specified value.\n";
    }
  }
} // end of the ResetAdminInfo class


$admin_reset = new ResetAdminInfo();
$admin_reset->print_greeting();
$admin_reset->get_ok();
$admin_reset->get_connection_info();
$admin_reset->db_pass_prompt();
$admin_reset->db_connect();
$admin_reset->reset_admin_user();
$admin_reset->reset_admin_pass();
