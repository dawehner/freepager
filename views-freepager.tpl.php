<?php
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
 * $rows['current']['text']
 *   The text designated for the current row. FALSE if no field is set.
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

<?php print $previous; ?><br />
<?php print $current; ?><br />
<?php print $next; ?><br />
