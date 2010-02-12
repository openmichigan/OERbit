<?php
/*
 * Template to create an inline menu.
 *
 * Input variables are :
 *  $title : Title of the menu
 *  $items : Array of menu items
 *
 */
 
 // We add stylesheets and javascript here - these are not required for the module
 // and are purely presentational. Themers do not need to do these calls - it's up
 // to you.
  drupal_add_css(drupal_get_path('module', 'nodereferrer_create') .'/theme/nodereferrer_create.css');
  drupal_add_js(drupal_get_path('module', 'nodereferrer_create') .'/theme/nodereferrer_create.js');
?>

<div class='nodereferrer-create-inline-menu'>
  <img src='<?php echo base_path() . drupal_get_path('module', 'nodereferrer_create').'/theme/down.png' ?>'
       class='nodereferrer-create-down'
       title=''
       alt=''
  />
  <div class='nodereferrer-create-items'>
    <ul>
      <?php foreach($items as $i) : ?>
        <li><?php echo $i?></li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>

