<?php

namespace Drupal\freepager\Plugin\views\display;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Plugin\views\display\Block;

/**
 * The plugin that a pager based upon views.
 *
 * @ingroup views_display_plugins
 *
 * @ViewsDisplay(
 *   id = "freepager",
 *   title = @Translation("Pager block"),
 *   help = @Translation("Uses the available fields to build a pager."),
 *   uses_menu_links = FALSE,
 *   uses_route = FALSE,
 *   uses_hook_block = TRUE,
 *   contextual_links_locations = {"block"},
 *   theme = "views_freepager",
 *   admin = @Translation("Page"),
 * )
 */
class Freepager extends Block {

  /**
   * {@inheritdoc}
   */
  protected $usesAJAX = FALSE;

  /**
   * {@inheritdoc}
   */
  protected $usesPager = FALSE;

  /**
   * {@inheritdoc}
   */
  protected $usesMore = FALSE;

  /**
   * {@inheritdoc}
   */
  protected $usesAttachments = TRUE;

  /**
   * {@inheritdoc}
   */
  protected function defineOptions() {
    $options = parent::defineOptions();

    foreach (array_keys(static::pagerSettings()) as $setting_name) {
      $options[$setting_name] = ['default' => FALSE];
    }

    return $options;
  }

  public static function pagerSettings() {
    return [
      'path' => [
        'label' => t('Field containing path'),
        'description' => t("Select the field containing the paths managed by this pager. Field could contain something on the form 'node/{{ nid__value }}'."),
      ],
      'previous' => [
        'label' => t("Field for 'previous'"),
        'description' => t('Select the field containing data used for linking to previous item.'),
      ],
      'current' => [
        'label' => t("Field for 'current'"),
        'description' => t('Select the field containing data used for showing the currently viewed item.'),
      ],
      'next' => [
        'label' => t("Field for 'next'"),
        'description' => t('Select the field containing data used for linking to next item.'),
      ],
      'loop' => [
        'label' => t('Loop the pager'),
        'description' => t('Check this box to have the last item followed by the first one, and vice versa.'),
      ],
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function optionsSummary(&$categories, &$options) {
    parent::optionsSummary($categories, $options);

    // Remove the category set by the parent class before adding our own.
    unset($categories['block']);
    $categories['freepager_block'] = [
      'title' => $this->t('Pager block settings'),
      'column' => 'second',
      'build' => [
        '#weight' => -10,
      ],
    ];

    $options['block_description']['category'] = 'freepager_block';

    // Get all the fields present in this view, to use as setting summaries.
    $field_labels = $this->getFieldLabels();
    foreach (static::pagerSettings() as $name => $setting) {
      $options[$name] = [
        'category' => 'freepager_block',
        'title' => $setting['label'],
        'value' => isset($field_labels[$this->getOption($name)]) ? $field_labels[$this->getOption($name)] : $this->t('(none)'),
      ];
    }

    // The 'loop' option is treated differently. It isn't a field select list.
    $yesno = [0 => $this->t('no'), 1 => $this->t('yes')];
    $options['loop']['value'] = $yesno[$this->getOption($name)];
  }

  /**
   * {@inheritdoc}
   */
  public function buildOptionsForm(&$form, FormStateInterface $form_state) {
    parent::buildOptionsForm($form, $form_state);

    // Set some variables to increase code readability.
    $freepager_settings = static::pagerSettings();
    $section = &$form_state->get(['section']);

    // If one of Free pager's settings are built, populate the form.
    if (isset($freepager_settings[$section])) {
      $form['#title'] .= $freepager_settings[$section]['label'];
      $form[$section] = [
        '#type' => 'select',
        '#description' => $freepager_settings[$section]['description'],
        '#options' => [FALSE => t('(none)')] + $this->getFieldLabels(),
        '#default_value' => $this->getOption($section),
      ];

      // The 'loop' setting should be treated differently. It's a check box.
      if ($section == 'loop') {
        $form[$section] = [
          '#type' => 'checkbox',
          '#title' => $freepager_settings['loop']['label'],
          '#description' => $freepager_settings[$section]['description'],
          '#default_value' => $this->getOption($section),
        ];
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function submitOptionsForm(&$form, FormStateInterface $form_state) {
    parent::submitOptionsForm($form, $form_state);

    // Set some variables to increase code readability.
    $freepager_settings = static::pagerSettings();
    $section = $form_state->get('section');

    // If one of Free pager's settings are submitted, make sure to save them.
    if (isset($freepager_settings[$section])) {
      $this->setOption($section, $form_state->getValue($section));
    }
  }

}
