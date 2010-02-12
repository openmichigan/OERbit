<?php
/*
 * Template to create a menu.
 *
 * Input is :
 *  $items, an array of array defining 'title' and 'fields'
 *
 */
 
 // We add stylesheets and javascript here - these are not required for the module
 // and are purely presentational. Themers do not need to do these calls - it's up
 // to you.
  drupal_add_css(drupal_get_path('module', 'nodereferrer_create') .'/theme/nodereferrer_create.css');
  drupal_add_js(drupal_get_path('module', 'nodereferrer_create') .'/theme/nodereferrer_create.js');
?>
<div class='nodereferrer-create-menu'>
  <ul class='nodereferrer-create-top-level'>
    <?php foreach($items as $top_level) : ?>
      <li>
        <div class='nodereferrer-create-title'>
          <?php echo $top_level['title']?>
          <img src='<?php echo base_path() . drupal_get_path('module', 'nodereferrer_create').'/theme/down.png' ?>'
               title=''
               alt=''
          />
        </div>
        <div class='nodereferrer-create-items'>
          <ul class='nodereferrer-create-second-level'>
            <?php foreach($top_level['items'] as $item) : ?>
              <li>
                <?php echo $item ?>
              </li>
            <?php endforeach; ?>
          </ul>
        </div>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
<br style='clear: both;' />
