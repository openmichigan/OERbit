<?php
// $Id: apachesolr_rdf.index.inc,v 1.1.2.10 2009/11/02 00:08:05 drunkenmonkey Exp $

/**
 * Index the specified resources for the given context.
 */
function apachesolr_rdf_index_resources($uris, $info) {
  $server = apachesolr_rdf_server_load($info['server']);
  if (!$server) {
    return FALSE;
  }
  $host = $server['host'];
  $port = $server['port'];
  $path = $server['path'];

  try {
    // Get the $solr object
    $solr = apachesolr_get_solr($host, $port, $path);
    // If there is no server available, don't continue.
    if (!$solr->ping(variable_get('apachesolr_ping_timeout', 4))) {
      throw new Exception(t('Solr instance not available during indexing: ' .
          '@url', array('@url' => "http://$host:$port$path")));
    }
  }
  catch (Exception $e) {
    watchdog('Apache Solr RDF', check_plain($e->getMessage()), NULL,
        WATCHDOG_ERROR);
    return FALSE;
  }

  // Prepare create_document method
  $create_document = _apachesolr_rdf_get_schema_function(
      'create_document', $info['schema']);
  if (!$create_document) {
    return FALSE;
  }

  // Prepare documents
  $documents = array();
  $options = array('context' => $info['resources']['context']);
  foreach ($uris as $uri) {
    $triples = rdf_query($uri, NULL, NULL, $options);
    $triples = rdf_normalize($triples);
    $predicates = $triples[$uri];
    $document = $create_document($uri, $predicates, $info);
    if ($document && $document instanceof Apache_Solr_Document) {
      $documents[$uri] = $document;
    }
  }

  // Index documents
  if (count($documents)) {
    try {
      watchdog('Apache Solr RDF', 'Indexing @count resources.',
          array('@count' => count($documents)));
      // Chunk the adds by 20s
      $docs_chunk = array_chunk($documents, 20, TRUE);
      foreach ($docs_chunk as $docs) {
        $solr->addDocuments($docs);

        foreach ($docs as $uri => $doc) {
          db_query('UPDATE {apachesolr_rdf_resources} SET changed = 0 ' .
              "WHERE uri = '%s' AND index_id = %d", $uri, $info['id']);
        }
      }
      $solr->commit();
    }
    catch (Exception $e) {
      watchdog('Apache Solr RDF', check_plain($e->getMessage()), NULL,
          WATCHDOG_ERROR);
      return FALSE;
    }
  }
}

/**
 * Creates the ID used for indexing a resource.
 */
function apachesolr_rdf_create_id($uri, $index) {
  return "$uri@$index";
}

/**
 * Extracts a string from an object returned by rdf_query() and returns it
 * along with its type.
 */
function apachesolr_rdf_extract_object_string($object) {
  if (is_string($object)) {
    return array('type' => 'string', 'string' => $object);
  }
  if ($object instanceof RDF_URIRef) {
    return array('type' => 'uri', 'string' => $object->uri);
  }
  if ($object instanceof RDF_Literal) {
    return array('type' => $object->datatype, 'string' => $object->value);
  }
  return FALSE;
}

//
// Schema functions
//
// - dynamic fields

/**
 * Creates an Apache_Solr_Document from the specified resource, using the
 * approach with dynamic fields for selected predicates.
 */
function apachesolr_rdf_create_document_dynamic(
    $uri, $predicates, $info) {
  $fields = _apachesolr_rdf_get_dynamic_fields(
      apachesolr_rdf_server_load($info['server']));
  $doc = new Apache_Solr_Document;

  $doc->id = apachesolr_rdf_create_id($uri, $info['id']);
  $doc->uri = $uri;
  $doc->index = $info['id'];
  $doc->context = $info['resources']['context'];
  $text = '';
  $options = array('context' => $info['resources']['context']);
  foreach ($predicates as $predicate => $objects) {
    foreach ($objects as $object) {
      $object = apachesolr_rdf_extract_object_string($object);
      $type = $object['type'];
      $string = $object['string'];

      // Add property_object value, if enabled
      if (!empty($info['schema_args']['property_object'])) {
        $doc->setMultiValue('property_object', "$predicate $string");
      }
      // Add value to "text" string, if enabled
      if (!empty($info['schema_args']['text'])) {
        if ($type == 'uri') {
          // For resource objects, add their label to "text" field
          $triples = rdf_query($string, APACHESOLR_RDF_LABEL, NULL, $options);
          $triples = $triples->to_array();
          $triples = rdf_normalize($triples);
          if (!empty($triples[$string])) {
            $triples = $triples[$string];
            $label = '';
            foreach ($triples as $pred => $obj) {
              $obj = apachesolr_rdf_extract_object_string($obj);
              $label .= "{$obj['string']} ";
            }
            $label = trim($label);
            if ($label) {
              $text .= "\n$label";
            }
          }
        }
        else {
          $text .= "\n$string";
        }
      }
      // Add dynamic field, if applicable
      $label = isset($label) ? $label : NULL;
      apachesolr_rdf_dynamic_add_index_fields($info, $doc, $predicate, $string,
          $fields, $label);
    }
  }
  trim($text);
  if ($text) {
    $doc->text = $text;
  }

  return $doc;
}

/**
 * Adds dynamic fields for the predicate/object pair to the document, if
 * applicable.
 */
function apachesolr_rdf_dynamic_add_index_fields(
    $info, &$doc, $p, $o, $fields, $label = NULL) {
  $types = array(
    'text' => 't',
    'string' => 's',
    'integer' => 'i',
    'float' => 'f',
    'boolean' => 'b',
  );
  $context = $info['resources']['context'];
  foreach (_apachesolr_rdf_get_dynamic_fields_by_uri($fields, $p)
      as $id => $v) {
    $t = $v['type'];
    $mv = empty($v['multiValued']) ? 's' : 'm';
    if (isset($types[$t])) {
      $name = "{$types[$t]}{$mv}_$id";
      if ($v['multiValued']) {
        $doc->setMultiValue($name, $o);
      }
      else {
        if (!empty($doc->$name)) {
          $doc->$name = $doc->$name . "\n$o";
        }
        else {
          $doc->$name = $o;
        }
      }
    }
    else {
      // Some supported datatypes require a special treatment
      switch ($t) {
        case 'date':
          $time = strtotime($o);
          if ($time === FALSE) {
            watchdog('Apache Solr RDF', 'Could not parse date: "@date"',
                array('@date' => $o), WATCHDOG_WARNING);
            break;
          }
          $name = "i{$mv}_$id";
          if ($v['multiValued']) {
            $doc->setMultiValue($name, $time);
          }
          else {
            if (!empty($doc->$name)) {
              $doc->$name = $doc->$name . "\n$time";
            }
            else {
              $doc->$name = $time;
            }
          }
          break;

        case 'resource':
          $name = "s{$mv}_$id";
          if ($v['multiValued']) {
            $doc->setMultiValue($name, $o);
          }
          else {
            if (!empty($doc->$name)) {
              $doc->$name = $doc->$name . "\n$o";
            }
            else {
              $doc->$name = $o;
            }
          }
          // Add label
          if (!isset($label)) {
            $options = array('context' => $context);
            $triples = rdf_query($o, APACHESOLR_RDF_LABEL, NULL, $options);
            $triples = $triples->to_array();
            $triples = rdf_normalize($triples);
            if (!empty($triples[$o])) {
              $triples = $triples[$o];
              $label = '';
              foreach ($triples as $pred => $obj) {
                $obj = apachesolr_rdf_extract_object_string($obj);
                $label .= "{$obj['string']} ";
              }
              $label = trim($label);
            }
          }
          if (!empty($label)) {
            $name = "t{$mv}_$id";
            if ($v['multiValued']) {
              $doc->setMultiValue($name, $label);
            }
            else {
              if (!empty($doc->$name)) {
                $doc->$name = $doc->$name . "\n$label";
              }
              else {
                $doc->$name = $label;
              }
            }
          }
          break;

        default:
          // It has to be a type defined by a hook
          $f = _apachesolr_rdf_get_dynamic_type_function('add_to_document', $t);
          if ($f) {
            $f($doc, $id, $v, $o, $context, isset($label) ? $label : NULL);
          }
          else {
            watchdog('Apache Solr RDF', 'Unknown datatype: @type.',
                array('@type' => $t), WATCHDOG_WARNING);
          }
      }
    }
  }
}

//
// - text data
//

/**
 * Creates an Apache_Solr_Document from the specified resource, using the
 * approach where just the text data associated with the resources is indexed.
 */
function apachesolr_rdf_create_document_text_data(
    $uri, $predicates, $info) {
  $doc = new Apache_Solr_Document;

  $doc->id = apachesolr_rdf_create_id($uri, $info['id']);
  $doc->uri = $uri;
  $doc->index = $info['id'];
  $doc->context = $info['resources']['context'];

  $options = array('context' => $info['resources']['context']);
  foreach ($predicates as $predicate => $objects) {
    foreach ($objects as $object) {
      $object = apachesolr_rdf_extract_object_string($object);
      $type = $object['type'];
      $string = $object['string'];
      if ($type == 'uri') {
        if ($predicate == APACHESOLR_RDF_TYPE) {
          //  Index the type additionally in a seperate field
          $doc->setMultiValue('type', $string);
        }
        // For resource objects, index their label
        $triples = rdf_query($string, APACHESOLR_RDF_LABEL, NULL, $options);
        $triples = $triples->to_array();
        $triples = rdf_normalize($triples);
        if (!empty($triples[$string])) {
          $triples = $triples[$string];
          $string = '';
          foreach ($triples as $pred => $obj) {
            $obj = apachesolr_rdf_extract_object_string($obj);
            $string .= $obj['string'];
          }
          $string = trim($string);
          $doc->setMultiValue('object_property', $predicate);
          $doc->setMultiValue('object_label', $string);
        }
        else {
          // If there is no text data on the object, fall back to indexing
          // the URI.
          // TODO: Is this a good idea?
          $doc->setMultiValue('object_property', $predicate);
          $doc->setMultiValue('object_label', $string);
        }
      }
      else {
        $doc->setMultiValue('property', $predicate);
        $doc->setMultiValue('text', $string);
      }
    }
  }

  return $doc;
}
