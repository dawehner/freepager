<?php
/**
 * @file
 * Declares the Views plugin for paging.
 */

function freepager_views_plugins() {
  return array(
    'module' => 'freepager', // This just tells our themes are elsewhere.
      // Note: I just copied this line. I don't have the faintest what it
      // actually does. Blame @Itangalo.
    'style' => array(
      'freepager' => array(
        'title' => t('Pager'),
        'help' => t('Uses the available fields to build a pager.'),
        'handler' => 'freepager_plugin_style',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'theme' => 'freepager',
        'even empty' => TRUE,
//        'help topic' => 'freepager',
      ),
    ),
  );
}
