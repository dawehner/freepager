<?php
/**
 * @file freepager_plugin_style.tpl.php
 * Contains the style plugin for Free Pager.
 */

/**
 * The style plugin for Pager by Views.
 *
 * @ingroup views_style_plugins
 */
class freepager_plugin_style extends views_plugin_style {

  /**
   * Set default options.
   */
  function options(&$options) {
    parent::options($options);
    $options['current'] = 0;
  }

  /**
   * Fill the style setting form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get the list of field handlers available in this display. We'll use these
    // in the options later.
    $handlers = $this->display->handler->get_handlers('field');

    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#value' => t('You need at least one field before you can configure your jump menu settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      return;
    }

    $form['markup'] = array(
      '#value' => t('To set up the pager, you must select one field that
        contains the path used for creating the previous and next links – as
        well as detecting the current page. You must also select fields to use
        for the rendering the \'previous\' and \'next\' link texts.'),
      '#prefix' => '<div class="form-item description">',
      '#suffix' => '</div>',
    );

    // Build an array to use for select lists containing all the available
    // handlers.
    foreach ($handlers as $id => $handler) {
      $options[$id] = $handler->ui_name();
    }

    $form['path'] = array(
      '#type' => 'select',
      '#title' => t('Path field'),
      '#description' => t('Select the field containing the path to use for paging.'),
      '#options' => $options,
      '#default_value' => $this->options['path'],
    );

    $form['previous'] = array(
      '#type' => 'select',
      '#title' => t('Previous field'),
      '#description' => t('Select the field used for the \'previous\' link.'),
      '#options' => $options,
      '#default_value' => $this->options['previous'],
    );

    $form['next'] = array(
      '#type' => 'select',
      '#title' => t('Next field'),
      '#description' => t('Select the field used for the \'next\' link.'),
      '#options' => $options,
      '#default_value' => $this->options['next'],
    );

    $form['current'] = array(
      '#type' => 'select',
      '#title' => t('Text for current item'),
      '#description' => t('If you want to show a text for the current item,
        select the field containing that text.'),
      '#options' => array(0 => '(no text)') + $options,
      '#default_value' => $this->options['current'],
    );

    $form['render_html'] = array(
      '#type' => 'checkbox',
      '#title' => t('Accept HTML'),
      '#description' => t('If marked, HTML inside fields will be rendered rather than escaped.'),
      '#default_value' => $this->options['render_html'],
    );
  }

  // Rendering function overridden in order to return previous and next link
  // instead of all rows.
  function render() {
    // If we don't have any fields, set an error message and bail out.
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    // If we don't have any results, bail out.
    // TODO: Make this happen prior to rendering, since we don't want an empty
    // container for this view.
    if (count($this->view->result) == 0) {
      $this->view->build_info['fail'] = TRUE;
      return FALSE;
    }

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);

    $path_field = $this->options['path'];
    $previous_field = $this->options['previous'];
    $next_field = $this->options['next'];
    $current_field = $this->options['current'];

    // Go through the list of paths in the defined path field, to see which row
    // (if any) matches the current (internal) path. Only first hit is used.
    $current_path = implode('/', arg());
    foreach ($this->rendered_fields as $row_number => $fields) {
      if ($fields[$path_field] == $current_path) {
        $rows['current_row'] = $row_number;
        break;
      }
    }

    // If we don't have a hit on current path, bail out.
    // TODO: Make this happen prior to rendering, since we don't want an empty
    // container for this view.
    if (!isset($rows['current_row'])) {
      $this->view->build_info['fail'] = TRUE;
      return FALSE;
    }

    // If we have a hit on the displayed path, populate some data to send off
    // to the theme template.
    // (This if statement is not necessary, but will have to be reintroduced
    // when the if statement above is moved elsewhere.)
    if (isset($rows['current_row'])) {
      // Set total number of rows, in case a themer wants to display this.
      $rows['total'] = count($this->rendered_fields);
      // Set the current text, if applicable.
      if ($current_field) {
        $rows['current']['text'] =
          $this->rendered_fields[$rows['current_row']][$current_field];
        // If fields aren't set to rendering HTML, escape the field content.
        if (!($this->options['render_html'])) {
          $rows['current']['text'] = check_plain($rows['current']['text']);
        }
      }
      // Set link, text and path for the previous row.
      $rows['previous'] = array(
        'link' => l(
          $this->rendered_fields[$rows['current_row'] - 1][$previous_field],
          $this->rendered_fields[$rows['current_row'] - 1][$path_field],
          array('attributes' => array('class' => 'freepager-previous'),
            'html' => $this->options['render_html'])
        ),
        'text' => $this->rendered_fields[$rows['current_row'] - 1][$previous_field],
        'path' => $this->rendered_fields[$rows['current_row'] - 1][$path_field],
      );
      // Do the same for the next row.
      $rows['next'] = array(
        'link' => l(
          $this->rendered_fields[$rows['current_row'] + 1][$next_field],
          $this->rendered_fields[$rows['current_row'] + 1][$path_field],
          array('attributes' => array('class' => 'freepager-next'),
            'html' => $this->options['render_html'])
        ),
        'text' => $this->rendered_fields[$rows['current_row'] + 1][$next_field],
        'path' => $this->rendered_fields[$rows['current_row'] + 1][$path_field],
      );

      // Theme the whole shebang and send it off.
      return theme($this->theme_functions(), $this->view, $this->options, $rows, $title);
    }
  }

  function validate() {
    $errors = parent::validate();
    if (empty($this->options['path'])) {
      $errors[] = t('The \'path\' setting for @display (pager display) is missing.',
        array('@display' => $this->display->display_title));
    }
    if (empty($this->options['previous'])) {
      $errors[] = t('The \'previous\' setting for @display (pager display) is missing.',
        array('@display' => $this->display->display_title));
    }
    if (empty($this->options['next'])) {
      $errors[] = t('The \'next\' setting for @display (pager display) is missing.',
        array('@display' => $this->display->display_title));
    }
//
//    if ($this->view->pager['items_per_page'] != 0) {
//      $errors[] = t('The pager plugin requires items per page to be unlimited.');
//    }
//    TODO: I don't know why I can't get the check on pager to work. This should
//    be updated and corrected, eventually.
    return $errors;
  }
}
