<?php
/*
The following file enables the uploading of each image from the java applet.
*/

echo "RECEIVING:";

$uploaddir = '[PATH TO UPLOAD DIRECTORY]';

$fpath = $_FILES['userfile']['name'];
$fext = array_pop(explode('.', $fpath));

if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploaddir . $fpath))
{
    echo "YES";
} 
else
{
    echo "NO";
	print_r($_FILES); 
} 

?>
