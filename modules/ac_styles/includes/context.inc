<?php

/**
* @file
 * CONTEXT HOOKS
*/

/**
 * Implements hook_context_plugins()
 * 
 * Defines the plugin handler for conditions and reactions
 */
function ac_styles_context_plugins() {
  $plugins = array();
  $plugins['ac_styles_reaction_ac_style'] = array(
    'handler' => array(
      'path' => drupal_get_path('module', 'ac_styles') . '/context',
      'file' => 'ac_styles_reaction_ac_style.inc',
      'class' => 'ac_styles_reaction_ac_style',
      'parent' => 'context_reaction_theme',
    ),
  );
  return $plugins;
}

/**
 * Implementation of hook_context_registry().
 */
function ac_styles_context_registry() {
  $registry = array();
  
  /**
   * Reaction Plugins
   */
  $registry['reactions']['ac_style'] = array(
    'title' => t('DiamondLayers Style'),
    'description' => t('Control style of page elements variables using context.'),
    'plugin' => 'ac_styles_reaction_ac_style',
  );

  return $registry;
}


