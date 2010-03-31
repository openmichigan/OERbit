$Id: README.txt,v 1.1.2.5 2009/11/02 00:08:05 drunkenmonkey Exp $

This module integrates the Resource Description Framework (RDF) module with
Apache Solr search servers, providing the possibility to do fulltext searches,
including faceting, on arbitrary RDF data from that module.


Installation:
-------------
The module can be enabled just like any other module, without any errors.

To actually use it to index and search data, however, a few things are required.
Firstly, it is necessary that you have set up the apachesolr module correctly,
with the SolrPhpClient available to the module.
You'll then have to set up one or more Solr servers dedicated to indexing the
RDF data. For this, you can choose between various schemas (you could even
create your own), two of which come with this module, "Dynamic fields" and
"Text data". (For explanations of these schemas, as well of apachesolr_rdf
schemas in general, see below.) Then you set up a Solr server just like you'd
normally do for the apachesolr module (see that module's README.txt for
details), but use the schema.xml and solrconfig.xml files appropriate for the
chosen schema instead of the ones delivered with the apachesolr module. Which
ones these are will normally be contained in the schema's description. There
may also be other actions to take, depending on the schema, which would be
described in the schema's description, too.

Once the server is set up properly, you'll have to tell the module about it. To
do this, go to Administer > Site configuration > Apache Solr RDF and click "Add
new server". Select the appropriate schema, choose a name and description (these
will only be displayed to admins, the only public information are the searches),
and enter the server's host information. Clicking "Add server" will create the
server. But at the moment, no data is collected.

For this, you will have to add an index, too. Procede just like when adding the
server, most fields should be self-explanatory. The data to index is determined
by context, so the "Context" field will determine, which resources will be
indexed by this index on the chosen server. This will probably be extended in
the future, to i.e. index all resources with a certain property, or
property value.

Lastly, for the actually using the server to search data via the site, you will
have to add a serach, too. Once this is done, go to Search > RDF (or to the path
search/apachesolr_rdf) to see a list of all currently enabled searches. Clicking
onetakes you to that search's input form, which should work like expected. The
advanced search options differ between schemas.


Schemas:
--------
Schemas are a way of telling this module how, for a particular server (and its
indexes and searches) it should handle certain tasks, like creating the Solr
documents out of RDF triples, or executing a search. Schemas are defined via
hook_apachesolr_rdf_schemas(), which is documented in apachesolr_rdf.hooks.php.
The schema will determine how the server should be set up, what search features
are available and what results a certain search will return.
Two schemas are delivered with this module, which should be useful for a wide
range of applications:

* Dynamic Fields: In this schema, dynamic fields are used to index some objects
  (= third components of triples) directly mapped to the corresponding
  predicates, which e.g. allows for more detailled facetting and filtering.
  Objects which are RDF resources are indexed with their URIs to allow for
  exact queries on objects.
  When using this schema for normal searches, you should add the default dynamic
  fields right after defining the server. To do so, go to the server's "Edit"
  page and click "Add default fields". This will define fields for the rdf:type,
  rdfs:label and rdfs:comment predicates, which will then be used for rendering
  search results (this works even if you rename them). Other fields can be
  defined manually via the "Add new field" link on the server's "Edit" page.
  To enable this schema, you'll also have to place the file
  sindice-url-preserving-tokenizer.jar into Solr's lib directory (when using the
  example application this is located at $SOLR_HOME/example/solr/lib).
* Text data: This schema, on the other hand, concentrates (as the name suggests)
  on indexing the text data associated with a resource, i.e. the literal-valued
  objects directly, but for resource-valued objects only their labels. This
  may lead to better results when doing fulltext searches with just keywords,
  where resources related to those keywords should be found. Facetting is only
  possible on the existence of predicates, or on the type.

When defining your own schema, please note that it has to contain the field
"index" of type "integer", for storing the ID of the index this document was
indexed for. The document ID should be some combination of the index ID and the
resource's URI, e.g. as returned by the apachesolr_rdf_create_id() function.


Note:
-----
The classes in sindice-url-preserving-tokenizer.jar were derived from the
Lucene project (http://lucene.apache.org/) and written by Renaud Debru
(http://groups.drupal.org/user/35034).
