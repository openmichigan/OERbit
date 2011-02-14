<?php
// $Id: node.tpl.php,v 1.4.2.1 2009/05/12 18:41:54 johnalbin Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */
?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"><div class="node-inner">

  <?php print $picture; ?>

  <?php if (!$page): ?>
    <h2 class="title">
      <a href="<?php print $node_url; ?>" title="<?php print $title ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>

  <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <?php if ($submitted || $terms): ?>
    <div class="meta">
      <?php if ($submitted): ?>
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>

      <?php if ($terms): ?>
        <div class="terms terms-inline"><?php print t(' in ') . $terms; ?></div>
      <?php endif; ?>
    </div>
  <?php endif; ?>


  	 <?php /*print $content ."<hr />";*/ ?>
  	 
  <!-- Create related content menu -->
  <?php
    $is_admin = hierarchical_permissions_access('edit', $node);
    if ($is_admin) {
      $menu_items = _nodereferrer_create_nodeapi_view_referrer($node, FALSE, TRUE);
      print '<div class="nodereferrer-links" >';
      foreach ($menu_items as $menu_item) {
        print $menu_item['items'][0];
      }
      print '</div><div style="clear: left;"></div>';
    }
  ?>

  <?php
   $unitImage = $node->field_unit_image[0]['view'];
   $unitImageCaption = $node->field_unit_image_caption[0]['value'];
   	if ($unitImage == "") { $contentarea = "content-course-full"; } else { $contentarea = "content-course"; } 
  ?>
<!-- Start the content -->  
<div class="content-course-full" style="clear: both;">


  <?php if($unitImage != "") { ?>
    <div class="course-image">
  	  <?php print $unitImage; ?>
  	  <?php print $unitImageCaption; ?>
    </div>
  <?php } ?>






    <!-- Create related content menu -->
    <?php
      if ($is_admin) {
        print $node->content['nodereferrer_create_menu']['#value'];
      }
    ?>
    
  	<!-- Content -->
  	<?php print $node->content['body']['#value']; ?>
  	
  	<!-- Website link -->
  	<?php if (!empty($node->field_website[0]['url'])) { ?>
  	  <div class="unit-website">
  	    <a class="ext" href="<?php print $node->field_website[0]['url']; ?>" target="<?php print $node->field_website[0]['attributes']['target']; ?>"><?php print $node->field_website[0]['display_title']; ?></a>
  	  </div>
   <?php } ?>

  <!-- Unit/Course listing -->
<?php
  // bdr/kwc hack to work around views implementation in drupal  :)
  $chead_printed = FALSE;
  $rhead_printed = FALSE;
  $children = navigation_get_children($node);
  // dpm($children, "The children array returned from navigation_get_children");
  $ckeys = array_keys($children);

  print '<div class="view-content unit-course-list view view-courses view-id-courses view-display-id-node_content_3 view-dom-id-1">';
  foreach ($ckeys as $key) {
    $cnode = node_load($key);
    // dpm($cnode,"CNW:");
    // print "<br> Child Sticky/weight/creationdate: "."$cnode->sticky"."/"."$cnode->node_weight"."/"."$cnode->created"." ".format_date($cnode->created, $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);

    // For courses, print "Course(s)" or "Resource(s)" heading, if not already printed, then print course link
    if ($cnode->type == 'course') {
      if ($cnode->field_content_type[0]['value'] == 'resource' && !$rhead_printed) {
        print "<br><b>Resource(s)</b><br>";
	$rhead_printed = TRUE;
      }
      else if ($cnode->field_content_type[0]['value'] == 'course' && !$chead_printed) {
        print "<br><b>Course(s)</b><br>";
	$chead_printed = TRUE;
      }
      print "&rsaquo; ".$children[$key]."<br>";
    }
    // For units, print the unit link, then its children
    if ($cnode->type == 'unit') {
      print "<h3>".$children[$key]."</h3>";
      $courses = navigation_get_children($cnode);
      foreach ($courses as $cstring) {
        print "&rsaquo; "."$cstring"."<br>";
      }
    }
  }
  print '</div>';
?>
    
  </div>
  


	<?php //print "<pre>"; print_r($node); print "</pre>"; ?>
  <?php print $links; ?>
  

</div></div> <!-- /node-inner, /node -->
