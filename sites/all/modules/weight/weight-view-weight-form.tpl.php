<?php
/* $Id: weight-view-weight-form.tpl.php,v 1.3.2.2 2009/01/26 00:28:54 nancyw Exp $
/**
 * @file
 * Views template for Weight module.
 */
?>

<table class="<?php print $class; ?>" id="<?php print $id; ?>">
  <thead>
    <tr>
      <?php if (count($header)): ?>
	      <?php foreach ($header as $field => $label): ?>
          <th class="views-field views-field-<?php print $fields[$field]; ?>">
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      <?php endif; ?>
    </tr>
  </thead>
  <tbody>
	  <?php  if (count($rows)): ?>
      <?php  foreach ($rows as $count => $row): ?>
        <tr class="<?php print ($count % 2 == 0) ? 'even' : 'odd';?> draggable">
          <?php foreach ($row as $field => $content): ?>
            <td class="views-field views-field-<?php print isset($fields[$field]) ? $fields[$field] : '' ?>">
              <?php print $content; ?>
            </td>
          <?php endforeach; ?>
        </tr>
      <?php endforeach;  ?>
    <?php endif; ?>
  </tbody>
</table>
<?php print $submit; ?>
