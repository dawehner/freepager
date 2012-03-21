<?php
/**
 * @file freepager.tpl.php
 * Default view template to display Free Pager.
 *
 * Available variables:
 *
 * $previous
 *   The rendered field used for the row before the viewed one. May be empty.
 * $previous_path
 *   The path for the previous row.
 * $current
 *   The rendered field used for the currently viewed row.
 * $current_path
 *   The current path.
 * $next
 *   The rendered field used for the row after the viewed one. May be empty.
 * $next_path
 *   The path for the next row.
 * $row_number
 *   The number of the viewed row.
 * $total_rows
 *   The total number of rows in the list from Views.
 *
 * @ingroup views_templates
 */
?>

<?php if (!empty($previous)): ?>
  <span class="freepager-previous">
    <?php print $previous; ?>
  </span>
<?php endif; ?>
<?php if (!empty($current)): ?>
  <span class="freepager-current">
    <?php print $current; ?>
  </span>
<?php endif; ?>
<?php if (!empty($next)): ?>
  <span class="freepager-next">
    <?php print $next; ?>
  </span>
<?php endif; ?>
