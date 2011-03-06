<?php
// $Id$
/**
 * @file freepager.tpl.php
 * Default view template to display Free Pager.
 *
 * Available variables:
 *
 * $rows['current_row']
 *   The index of the currently viewed item in the list. (Starting on zero!)
 * $rows['total']
 *   The total number of items in the list.
 * $rows['previous']['link']
 *   The rendered link for the previous link.
 * $rows['previous']['text']
 *   The text to use for the previous link.
 * $rows['previous']['path']
 *   The url to use for the previous link.
 * $rows['next']['link']
 *   The rendered link for the next link.
 * $rows['next']['text']
 *   The text to use for the next link.
 * $rows['next']['path']
 *   The url to use for the next link.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php if (!empty($rows['previous']['path'])): ?>
  <span class="freepager-previous">
    <?php print $rows['previous']['link']; ?>
  </span>
<?php endif; ?>
<?php if (!empty($rows['next']['path'])): ?>
  <span class="freepager-next">
    <?php print $rows['next']['link']; ?>
  </span>
<?php endif; ?>
