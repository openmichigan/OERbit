MimeDetect strives to provide consistent and accurate server side MIME type 
detection. It supports the PHP FileInfo Extension, the UNIX 'file' command, 
then tries to use the MIME type supplied with the file object. If everything
fails it will select a MIME type based on file extension. 

MimeDetect is Distributed with a magic database to make FileInfo based MIME
detection more consistent across servers. 
