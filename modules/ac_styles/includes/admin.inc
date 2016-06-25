<?php

/**
 * Form builder; Configure acquia styles - general settings.
 *
 * @ingroup forms
 */
function ac_styles_general_settings($form, &$form_state) {
  //acquia_include('taxonomy');
  //acquia_include('options');
  acquia_include('theme');
  acquia_include('context');

  acquia_theme_wrap_acquia_admin_style($form, array('vtabs' => true));

  // add assets
  drupal_add_css(drupal_get_path('module', 'ac_styles') . '/css/node-edit-form.css');
  drupal_add_js(drupal_get_path('module', 'ac_styles') . '/js/node-edit-form.js');
  acquia_load_resources();

  $form['ac_styles_vtabas'] = array(
	'#type' => 'vertical_tabs',
	'#title' => t('DiamondLayers styles'),
  );

  // Default blog context
  $form['general'] = array(
	'#type' => 'fieldset',
	'#title' => t('General Settings'),
	'#group' => t('ac_styles_vtabas'),
  );

  $default = acquia_variable_get("node_default_layout", "second-sidebar");
  $layouts = array();
  foreach (acquia_get_layout_contexts() as $layout => $info) {
	$label = t(str_replace(array("-", "_"), " ", $info));
	$layouts['#options'][$layout] = $label;
	$layouts[$layout]['#prefix'] = '<div class="acquia-layout-selection-wrapper">';
	$layouts[$layout]['#suffix'] = '<span class="acquia-layout-icon '.$layout.'"><span class="text">'.$label.'</span></span></div>';
  }

  foreach (node_type_get_types() as $type => $info) {
	// Default blog context
	$form['general']['ac_styles_node_' . $type .'_default_context'] = array(
	  '#type' => 'radios',
	  '#title' => t('@type layout', array('@type' => $info->name)),
	  '#description' => t('Select a default layout for @type content type.', array('@type' => $info->name)),
	  '#default_value' => variable_get('ac_styles_node_' . $type .'_default_context', $default),
	  //'#submit' => array('context_node_form_submit'),
	  '#prefix' => '<div class="ac-node-page-layout">',
	  '#suffix' => '</div>',
	);
	$form['general']['ac_styles_node_' . $type .'_default_context'] +=$layouts;
  }
  return system_settings_form($form);
}
