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

  <?php if ($submitted): ?>
    <div class="meta">
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
    </div>
  <?php endif; ?>


   
  <?php 
   $courseImage = $node->field_course_image[0]['view'];
   $courseImageCaption = $node->field_course_image_caption[0]['value'];
   	if ($courseImage == "") { $contentarea = "content-course-full"; } else { $contentarea = "content-course"; } 
  ?>
<!-- Start the content -->  
  <div class="<?php print $contentarea; ?>">
    <!-- Create related content menu -->
    <?php print $node->content['nodereferrer_create_menu']['#value']; ?>
    <!-- Term -->
  	<div class="term-year"><strong>Term:</strong> <?php print $node->field_course_term[0]['value']." ". $node->field_course_year[0]['view']; ?></div>
  	<!-- Publsihed & Revised Dates -->
  	<div class="dates"><span class="published"><strong>Published:</strong> <span property="dc:created"><?php print date('F j, Y',$node->created); ?></span></span> <span class="revised"><strong>Revised:</strong> <span property="dc:available"><?php print date('F j, Y',$node->changed); ?><span property="dc:created"></span></div>
  	
  	<!-- Content -->
  	
  	<!-- VIEW -->
  	<?php
  	  if ($section) {
     	  print $node->content[$section . '_node_content_1']['#value'];
      }
      else {
        print $node->content['body']['#value'];
        print $node->content['overview_node_content_1']['#value'];
      }
  	?>
  	<!-- End of VIEW -->
  	
  	
  	
  </div>
  
  
  
 <?php if ($courseImage != "") {  ?> 
  <div class="imgCapR" id="image-course">
    <!-- Download Course -->
  	<div class="course-download">
  		<a href="#">Download the full course resources</a>
  	</div>
  	
  	<!-- Course Image -->
  	<?php print $courseImage; ?>
  	<?php print $courseImageCaption; ?>
  	
  	<!-- Previous Terms -->
  	<!-- <div class="course-previous-terms">
  	PREVIOUS TERMS<br />
  	
  	</div> -->
  </div>
 <?php } ?>
 
   <div class="coursefooter">
   <!--  Keywords -->
     <div class="course-keywords">Keywords: <div class="terms terms-inline" property="dc:subject"><?php print $terms; ?></div></div>   
   </div>

  <?php print $links; ?>
  
  
  <?php print $node->field_file[0]['filename']; ?>
  <?php print $node->field_file[0]['filepath']; ?>

</div></div> <!-- /node-inner, /node -->
