*******************************************************
       README.txt for weight.module for Drupal
    by Jeff Robbins ::: jeff /@t\ jjeff /d0t\ com
    maintained by harry slaughter <harry@devbee.com>
*******************************************************

This module adds a weight option to enabled node types. It uses the node
table's 'sticky' column to store weights as well as sticky information (so
that feature is not lost). Nodes with lower weight will float to the top of
lists, while heavier items will sink.

This is useful for sorting non-cronological nodes like bios or ecommerce
products.

Nodes will be sorted first by stickiness, then by weight, then by creation
date.

TO CREATE AN ORDERABLE VIEW (Admins can reweight nodes using drag-and-drop):

 * Create a view as normal with a "page" display
 * Change the view style to "weight changer"
 * Include Field Weight (though not as the first field you include).
 * Sort by Weight DESC.
 * Ensure only appropriate roles have access to the view.
 * Load up the view, reorder, and save!
