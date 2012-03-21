<?php
/**
 * @file
 * Contains the block display plugin.
 */

/**
 * The plugin that handles a block.
 *
 * @ingroup views_display_plugins
 */
class freepager_plugin_display_pagerblock extends views_plugin_display_block {
  function option_definition() {
    $options = parent::option_definition();

    $options['block_description'] = array('default' => '', 'translatable' => TRUE);
    $options['block_caching'] = array('default' => DRUPAL_NO_CACHE);

    return $options;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['block'] = array(
      'title' => t('Block settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    $block_description = strip_tags($this->get_option('block_description'));
    if (empty($block_description)) {
      $block_description = t('None');
    }

    $options['block_description'] = array(
      'category' => 'block',
      'title' => t('Block name'),
      'value' => views_ui_truncate($block_description, 24),
    );

    $cache_type = $this->get_option('block_caching');
    if (empty($cache_type)) {
      $cache_type = DRUPAL_NO_CACHE;
    }

    $types = $this->block_caching_modes();
    $options['block_caching'] = array(
      'category' => 'other',
      'title' => t('Block caching'),
      'value' => $types[$this->get_cache_type()],
    );
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'block_description':
        $form['#title'] .= t('Block admin description');
        $form['block_description'] = array(
          '#type' => 'textfield',
          '#description' => t('This will appear as the name of this block in administer >> structure >> blocks.'),
          '#default_value' => $this->get_option('block_description'),
        );
        break;
      case 'block_caching':
        $form['#title'] .= t('Block caching type');

        $form['block_caching'] = array(
          '#type' => 'radios',
          '#description' => t("This sets the default status for Drupal's built-in block caching method; this requires that caching be turned on in block administration, and be careful because you have little control over when this cache is flushed."),
          '#options' => $this->block_caching_modes(),
          '#default_value' => $this->get_cache_type(),
        );
        break;
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'display_id':
        $this->update_block_bid($form_state['view']->name, $this->display->id, $this->display->new_id);
        break;
      case 'block_description':
        $this->set_option('block_description', $form_state['values']['block_description']);
        break;
      case 'block_caching':
        $this->set_option('block_caching', $form_state['values']['block_caching']);
        $this->save_block_cache($form_state['view']->name . '-'. $form_state['display_id'], $form_state['values']['block_caching']);
        break;
    }
  }
}