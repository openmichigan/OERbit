Background
===============
MimeDetect strives to provide consistent and accurate server side MIME type
detection. It supports the PHP FileInfo Extension, the UNIX 'file' command,
then tries to use the MIME type supplied with the file object. If everything
fails it will select a MIME type based on file extension.

Troubleshooting
===============
MimeDetect is distributed with a Magic database file to make FileInfo based
MIME detection more consistent across servers. This database file may not
work with your server. When this happens, you may see an error message like
this in your Drupal status report:

  Fileinfo could not load the magic file. It could be corrupted. Try
  reinstalling the magic file distributed with the MimeDetect module.
  (Currently using Mime type detection PHP Fileinfo Extension)

This message means that the included 'magic' database file will not work with
your server configuration and may have to use a different 'magic' file.
Usually there is a 'magic' file included in the File 4.x distribution, a PHP
extension installed on your server.

The first step to troubleshooting this problem is to determine if the extension
is installed on your server, and then to learn the path to the 'magic' file.
You can contact your web host for this. Then, in your settings.php, you can
define a new variable that tells Mimedetect the correct and absolute path of
the file to use:

  $conf = array(
    'mimedetect_magic' => '/usr/share/file/magic',
  );

The path '/usr/share/file/' is a common location for this file but you may have
to replace that path with the correct magic file path if it is different on
your server. Some configurations will require you to use a file extension on
the file name, such as '/usr/share/file/magic.mime'.

If this error message persists then you can create a PHP script to test that
you have the correct path to the 'magic' database file. Create a simple text
file named test.php in your web root and call it in a browser.  Use this
snippet in your script:

<?php
  $magic_file = '/usr/share/file/magic';
  $finfo = finfo_open(FILEINFO_MIME, $magic_file);
  if (!$finfo) {
    echo "Opening fileinfo database failed";
    exit();
  }
?>

Again, as mentioned above, the path will need to reflect the correct magic file
path and you may need to add .mime to the file name.
