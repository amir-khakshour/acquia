<?php

	
/**
 * Add global js vars 
 * 	Adds settings vars to work with shortcodes mce button
 * 	@param {array} $sc provided shortcodes list
 * 	
 */
function add_shortcode_btn_globals($sc = array()) {
	
	$settings = array();
	$settings['shortcodes'] = array(
		'mce_btn' => array(
			'title' => t('DiamondLayers Shortcodes'),
			'image' => file_create_url(AC_MCE_PLUGINS_IMG_ASSETS_DIR . '/tiny-button.png'),
		),
	);
	
	$settings['shortcodes']['mce_btn']['options'] = $sc;
	$settings['shortcodes']['ajaxURL'] = acquia_variable_get('path_prefix') . ACQUIA_SHORTCODE_AJAX_URL;
	drupal_add_js($settings, 'setting');
}
