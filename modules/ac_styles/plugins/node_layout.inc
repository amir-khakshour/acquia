<?php

/**
 * style plugin for ac_style module.
 *
 * Calculate sum of two numbers.
 */

$plugin = array(
  'label' => t('Node Layout'),
  'handler' => array(
	'class' => 'node_layout',
  ),
);

/**
 * @file
 * Contains the unformatted summary style plugin.
 */

/**
 * The default style plugin for Hero section.
 *
 * @ingroup views_style_plugins
 */
class node_layout extends acquia_styles {
  /**
   *  style form
   */
  public function style_form($settings = array()) {

	acquia_include('options');
	acquia_include('context');

	// add assets
	drupal_add_css(drupal_get_path('module', 'ac_styles') . '/css/node-edit-form.css');
	drupal_add_js(drupal_get_path('module', 'ac_styles') . '/js/node-edit-form.js');

	$settings+= array(
	  'parents' => array(''),
	);

	$values = isset($this->values) && is_array($this->values) ? $this->values : array();
	$node = isset($settings['node']) && isset($settings['node']->type) ? $settings['node'] : menu_get_object();

	if (!isset($values['node_layout']) || empty($values['node_layout'])){
	  if (isset($node->type)) {
		$values['node_layout'] = variable_get('ac_styles_node_' . $node->type .'_default_context', acquia_theme_get_settings("node_layout", "second-sidebar"));
	  }else{
		$values['node_layout'] = acquia_theme_get_settings("node_layout", "second-sidebar");
	  }
	}

	$form = array();
	$form['node_layout'] = array(
	  '#prefix' => '<div class="ac-node-page-layout">',
	  '#suffix' => '</div>',
	  '#type' => 'radios',
	  '#title' => t('Node page Layout'),
	  '#description' => t('Select a layout for this node to apply.'),
	  '#default_value' => $values['node_layout'],
	  '#submit' => array('context_node_form_submit'),
	);

	foreach (acquia_get_layout_contexts() as $layout => $info) {
	  $label = t(str_replace(array("-", "_"), " ", $info));
	  $form['node_layout']['#options'][$layout] = $label;
	  $form['node_layout'][$layout]['#prefix'] = '<div class="acquia-layout-selection-wrapper">';
	  $form['node_layout'][$layout]['#suffix'] = '<span class="acquia-layout-icon '.$layout.'"><span class="text">'.$label.'</span></span></div>';
	}

	return $form;
  }
}

/**
 * Implements hook_plugins_PLUGIN_theme_registry_alter().
 */
function ac_styles_plugins_node_layout_theme_registry_alter(&$registry, $file) {
  if ($file == false) {
	return false;
  }
  $registry['html']['includes'][] = $file;
  $registry['html']['preprocess functions'][] = 'ac_styles_plugins_node_layout_preprocess_html';
}

/**
 * Implements hook_plugins_PLUGIN_preproces_html().
 */
function ac_styles_plugins_node_layout_preprocess_html(&$vars) {
  acquia_include('utility', 'ac_styles', 'includes');
  acquia_include('content');

  // Get styles from merging context and node meta
  $ac_styles = ac_styles_merge_nodemeta_by_context('ac_style');
  if (isset($ac_styles['node_layout']) && !empty($ac_styles['node_layout'])) {
	$vars['classes_array'][] = $ac_styles['node_layout'];
  }

}