<?php
// $Id: revisions-summary.tpl.php,v 1.5 2009/04/30 03:26:48 rdeboer Exp $
/**
 * @file
 * revisions-summary.tpl.php
 * Template to handle layout details of the submenu that appears above the
 * summary of node revisions.
 *
 * Variables available:
 * - $submenu_links: an array of <a>-tags
 * - $content: summary of node revisions (as a table)
 */
?>
<?php if ($submenu_links): ?>
  <div class="submenu revisions">
    <?php print implode(' <strong>|</strong> ', $submenu_links); ?>
  </div>
  <hr/>
<?php endif; ?>
<?php print $content;
