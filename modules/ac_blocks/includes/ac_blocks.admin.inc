<?php
/**
 * @file
 * Admin functions for the Delta blocks module.
 */

function ac_blocks_admin_settings($form, &$form_state) {
  acquia_include('theme');
  acquia_load_resources('admin');
  
	// wrap acquia options style
	acquia_theme_wrap_acquia_admin_style($form, array('title' => t('blocks configuration')));
  
  $form['ac_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('DiamondLayers blocks configuration'),
  );
  
  $blocks = array_keys(_ac_blocks_get_blocks());
  $form['ac_blocks']['ac_blocks_toggle'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Toggle DiamondLayers blocks'),
    '#options' => ac_blocks_options(),
    '#default_value' => variable_get('ac_blocks_toggle', array_combine($blocks, $blocks)),
    '#description' => t('The selected items will be available as blocks.'),
  );
  
  return system_settings_form($form);
}