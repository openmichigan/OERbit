
Apache Solr Attachments for 6.x

Requires the ability to run java and installation of tika 0.3 or higher,
or access to a solr server set up for content extraction (e.g. a Solr
1.4 final release).  For Solr, there is a patch to apply to the solrconfig
to add another request handler.

see:  
http://lucene.apache.org/tika/gettingstarted.html
http://lucene.apache.org/tika/formats.html

Tika will extract many file formats, including PDFs, MS Office (2003 format
as well as new docx format).  Java 6 (aka 1.6) may be needed on some
platforms to support all formats.  The page on formats seems not to be 100% 
up to date.  In particular, https://issues.apache.org/jira/browse/TIKA-152
is committed, so it does currently support MS Office 2007 documents to 
some reasonable degee.

The easiest-to-find pre-built tika 0.3 is to check out a version of Solr trunk
from around March 2009 such as:

svn co -r779609 http://svn.apache.org/repos/asf/lucene/solr/trunk/contrib/extraction/lib tika-0.3

You can copy/move directory to somewhere convenient, though it's probably a good idea
to keep it outside your docroot.

While Solr now uses tika 0.4, it no longer lncludes the command-line extraction
application.

You will likely need to build tika from source using maven (mvn).  Get the tika
source from:
http://lucene.apache.org/tika/download.html

You may need to increase the memory for java/mvn using (for example):
export MAVEN_OPTS="-Xmx1024m -Xms512m"

mvn install

will build the full set of tika applications - it will build the app jar
in a location like tika-app/target/tika-app-0.4.jar

Copy tika-app-0.4.jar from there or point the module path to it.

See also build instructions at: http://drupal.org/node/540974#comment-1944082

If you are using Solr to extract your content, you need to copy (or symlink) 
the contents of contrib/extraction/lib to a directory named lib under your 
solr home, or alter solrconfig.xml to add the orgiginal directory as a
lib directory.

