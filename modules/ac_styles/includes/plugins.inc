<?php

/**
 * Context plugins.
 */
function _ac_styles_plugins() {
  $plugins = array();

  /**
   * Conditions.
   */
  
  /**
   * Reactions.
   */
  $plugins['header_style'] = array(
    'label' => t('header Style'),
    'handler' => array(
      'path' => drupal_get_path('module', 'ac_styles') . '/plugins',
      'file' => 'header_style.inc',
      'class' => 'header_style',
      'parent' => 'acquia_styles',
    ),
  );

  /**
   * Reactions.
   */
  $plugins['hero_style'] = array(
    'label' => t('Hero Style'),
    'handler' => array(
      'path' => drupal_get_path('module', 'ac_styles') . '/plugins',
      'file' => 'hero_style.inc',
      'class' => 'hero_style',
      'parent' => 'acquia_styles',
    ),
  );
  
  /**
   * Reactions.
   */
  if (module_exists('ac_slider')) {
    $plugins['header_slider'] = array(
      'label' => t('Header slider'),
      'handler' => array(
        'path' => drupal_get_path('module', 'ac_styles') . '/plugins',
        'file' => 'header_slider.inc',
        'class' => 'header_slider',
        'parent' => 'acquia_styles',
      ),
    );
  }
  
  /**
   * Reactions.
   */
  $plugins['node_layout'] = array(
    'label' => t('Node Layout'),
    'handler' => array(
      'path' => drupal_get_path('module', 'ac_styles') . '/plugins',
      'file' => 'node_layout.inc',
      'class' => 'node_layout',
      'parent' => 'acquia_styles',
    ),
  );

  return $plugins;
}
