<?php
/**
 * @file
 * Declares the Views plugin for paging.
 */

/**
 * Declares the pager block display.
 * @return type 
 */
function freepager_views_plugins() {
  return array(
//    'module' => 'freepager', // This just tells our themes are elsewhere.
    'display' => array(
      'freepager' => array(
        'title' => t('Pager block'),
        'help' => t('Uses the available fields to build a pager.'),
        'handler' => 'freepager_plugin_display_pagerblock',
        'theme' => 'views_view',
        'uses hook block' => TRUE,
//        'contextual links locations' => array('block'),
//        'use ajax' => TRUE,
//        'use pager' => TRUE,
//        'use more' => TRUE,
        'accept attachments' => TRUE,
        'admin' => t('Free Pager block'),
      ),
    ),
  );
}
