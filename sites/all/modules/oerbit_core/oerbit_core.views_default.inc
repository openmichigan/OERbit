<?php

/**
 * Implementation of hook_views_default_views().
 */
function oerbit_core_views_default_views() {
  $views = array();

  // Exported view: open_blog
  $view = new view;
  $view->name = 'open_blog';
  $view->description = 'Blog View on the homepage.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'aggregator_item';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'timestamp' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'custom',
      'custom_date_format' => 'F j, Y',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'aggregator_item',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'display_as_link' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'aggregator_item',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'aggregator_item',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', '<h3 class="shaded"><a href="https://open.umich.edu/blog/">open.blog</a></h3>
<div id="blogPic"><img src="/sites/all/themes/oer/images/blogpic.jpg" alt="CC-BY_NC_SA: Three Gossips by TOJOSAN, Flickr"/></div>
<h4><a href="http://open.umich.edu/blog/feed/"><img src="/sites/all/themes/oer/images/rss.gif" alt="RSS Feed" /></a>&nbsp;&nbsp;Recent Posts</h4>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('items_per_page', 3);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;

  return $views;
}
