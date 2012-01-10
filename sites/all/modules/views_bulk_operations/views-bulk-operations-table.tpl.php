<?php
/**
 * @file views-bulk-operations-table.tpl.php
 * Template to display a VBO as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * @ingroup views_templates
 */
?>
<table class="<?php print $class; ?>">
   <?php if (!empty($title)) : ?>
     <caption><?php print $title; ?></caption>
   <?php endif; ?>
  <thead>
    <tr>
      <?php foreach ($header as $key => $value): ?>
        <?php if ($key == 'select') { ?>
          <th class="select"><?php print $value ?></th>
        <?php } else { ?>
          <th class="views-field views-field-<?php print $fields[$key] ?>"><?php print $value ?></th>
        <?php } ?>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($rows as $count => $row): ?>
      <tr class="<?php print implode(' ', $row_classes[$count]); ?>">
        <?php foreach ($row as $field => $content): ?>
          <?php if ($field == 'select') { ?>
            <td class="views-field select">
          <?php } else { ?>
            <td class="views-field <?php if (!empty($fields[$field])) print "views-field-{$fields[$field]}"; ?>">
          <?php } ?>
              <?php print $content; ?>
            </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
