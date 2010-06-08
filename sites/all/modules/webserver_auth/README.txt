$Id: README.txt,v 1.3 2008/07/17 20:07:27 weitzman Exp $

Description
-----------
Admins can now enable access control their the drupal directory via their webserver (e.g. http auth, NTLM, .htaccess)
and with this module, Drupal honor's the web server's authentication.

Install
----------
Enable access control on your your drupal directory and subdirectories. For Windows, you must turn
'windows integrated authentication' for the drupal directory in IIS or use Apache ntlm module (untested)

Install this module as usual.

You probably want to disable the 'user login' block. if you choose to leave it enabled, it will still work.
 
If you allow automatic registration in user module Admin, this module automatically creates
new users as they are encountered. otherwise, you will have to create a user account manually before users can login

On the admin/system/modules/webserver_auth page, you might want to add a domain name 
which will automatically be appended to usernames in order to store an
email address for new users. Useful when all users work for the same organization 
and thus the same domain name.

TODO:
- optionally grab elements from LDAP server (e.g. Windows Active Directory) immediately after 
user login. this will auto populate fields like phone number, birthday, etc.
  