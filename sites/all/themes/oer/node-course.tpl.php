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
 
 /*** CUSTOM ADDITIONS ***/
   $courseImage = $node->field_course_image[0]['view'];
   $courseImageCaption = $node->field_course_image_caption[0]['value'];
   $courseDownload = $node->field_course_download_display[0]['value'];
   $courseTerm = $node->field_course_term[0]['value']." ". $node->field_course_year[0]['view'];
   
   if ($terms) { $courseKeywords = '<div class="course-keywords">Keywords: <div class="terms terms-inline" property="dc:subject">'. $terms . '</div></div>'; } else { $courseKeywords = ''; }
   
   
   
   
?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"><div class="node-inner">

  <?php /*print $picture;*/ ?>
  
  
  
  
<!-- TITLE -->
  <?php if (!$page): ?>
    <h2 class="title"><a href="<?php print $node_url; ?>" title="<?php print $title ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>

  <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <?php if ($submitted): ?>
    <div class="meta">
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
    </div>
  <?php endif; ?>
  
<div class="content-course-full" style="clear: both;">

<!-- Course Image -->
  
  <?php if($courseImage != "") { ?>
    <div class="course-image">
  	  <?php print $courseImage; ?>
  	  <?php print $courseImageCaption; ?>
    </div>
  <?php } ?>

 <table class="courseinfo" style="width: auto;">
 	<tr>
 		<td><!-- Term -->
  	<?php if ($courseTerm != '') { ?>
  	<div class="term-year">
  		<strong>Term:</strong> <?php print $courseTerm; ?>
  	</div>
  	<?php } ?></td>
 		<td><span class="published"><strong>Published:</strong> <span property="dc:created"><?php print date('F j, Y',$node->created); ?></span></span></td>
 	</tr>
 	<tr>
 		<td><!-- Download Course -->
  	<?php if($courseDownload != 'No') { ?>
   	<div class="course-download">
    	<a href="#">Download all materials</a>
   	</div>
  	<?php } ?></td>
 		<td valign="top"><span class="revised"><strong>Revised:</strong> <span property="dc:available"><?php print date('F j, Y',$node->changed); ?></span></span></td>
 	</tr>
 </table>
  
  	
  	  
  	
  	<!-- Content -->
  	
  	<!-- VIEW -->
  	<?php
  	  if ($section) {
  	    print $node->content[$section . '_links_node_content_1']['#value'];
  	    print $courseKeywords;
  	      ?>
     
    <!-- Create related content menu -->
    <?php
      $menu_items = _nodereferrer_create_nodeapi_view_referrer($node, FALSE, TRUE);
      print '<div class="nodereferrer-links" >';
      switch ($section) {
        case 'highlights':
          print $menu_items[1]['items'][0];
          break;
        case 'materials':
          print $menu_items[2]['items'][0];
          if (user_access('create material content')) {
            print '<br />' . l('Zip Upload', 'node/' . $node->nid . '/zip_upload');
          }
          break;
        case 'sessions':
          print $menu_items[3]['items'][0];
          break;
        case 'information':
        default:
          print $menu_items[0]['items'][0];
          break;
      }
      print '</div><div style="clear: left;"></div>';
    ?>

  	    
  	    <?php
  	    if (user_is_anonymous()) {
     	    print $node->content[$section . '_node_content_1']['#value'];
     	  }
     	  else {
     	    print $node->content[$section . '_node_content_2']['#value'];
     	  }
      }
      else {
        print $node->content['body']['#value'];
  	    print $courseKeywords;
        ?>
     
     
     <!-- Create related content menu -->
    <?php
      $menu_items = _nodereferrer_create_nodeapi_view_referrer($node, FALSE, TRUE);
      print '<div class="nodereferrer-links">';
      switch ($section) {
        case 'highlights':
          print $menu_items[1]['items'][0];
          break;
        case 'materials':
          print $menu_items[2]['items'][0];
          print '<br />' . l('Zip Upload', 'node/' . $node->nid . '/zip_upload');
          break;
        case 'sessions':
          print $menu_items[3]['items'][0];
          break;
        case 'information':
        default:
          print $menu_items[0]['items'][0];
          break;
      }
      print '</div>';
    ?>
     
     
     
     
        <?php
        if (user_is_anonymous()) {
          print $node->content['overview_node_content_1']['#value'];
        }
        else {
          print $node->content['overview_node_content_2']['#value'];
        }
        print $node->content['instructor_node_content_1']['#value'];
      }
  	?>
  	<!-- End of VIEW -->
  	
  	
  	
  	

  
</div>

 
 
   <div class="coursefooter">
     <?php
       if (isset($node->cc)) {
         print $node->cc->get_html();
       }
     ?>
   </div>

  <?php print $links; ?>
  
<?php //print "<pre>"; print_r($node); print "</pre>"; ?>
</div></div> <!-- /node-inner, /node -->
