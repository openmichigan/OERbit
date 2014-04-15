<?php

/**
 * @file custom_search-results.tpl.php
 * Theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $type: The type of search, e.g., "node" or "user".
 * - $filter: Rendered content types filter
 * - $filter_positon: above/below/disabled
 *
 * @see template_preprocess_custom_search_results()
 */
?>
<?php if (isset($filter) && $filter != '' && $filter_position == 'above') { ?>
  <div class="custom-search-filter">
    <?php print $filter; ?>
  </div>
<?php } ?>
<dl class="search-results <?php print $type; ?>-results">
  <?php print $search_results; ?>
</dl>
<?php if (isset($filter) && $filter != '' && $filter_position == 'below') { ?>
  <div class="custom-search-filter">
    <?php print $filter; ?>
  </div>
<?php } ?>
<?php print $pager; ?>