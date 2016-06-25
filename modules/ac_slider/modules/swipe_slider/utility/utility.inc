<?php
/**
 * General utility functions to work with elastic slider
 */

 
/**
 * Load resource
 */
function swipe_slider_load_resources($type = 'slider') {
	switch($type) {
    // admin slider resources
		case 'admin':
			acquia_include('utility');
			include_once drupal_get_path('module', 'media') . '/wysiwyg_plugins/media.inc';
			media_include_browser_js();
			drupal_add_library('system', 'ui');
			drupal_add_library('system', 'farbtastic');
			drupal_add_library('system', 'ui.sortable');
			drupal_add_library('system', 'ui.draggable');
			drupal_add_library('system', 'ui.menu');
			drupal_add_library('system', 'ui.position');
			drupal_add_library('system', 'ui.button');
			drupal_add_library('system', 'ui.dialog');
			drupal_add_library('system', 'ui.autocomplete');
			drupal_add_library('system', 'ui.resizable');
			drupal_add_library('ac_slider', 'acquia_slider.admin');
			break;
	
    // slider frontend resources
		default:
		case 'swipe-slider':
			drupal_add_library('swipe_slider', 'swipe-slider');
			break;	
	}
}

/**
 * Load resource
 */
function swipe_slider_slider_settings_data($slid, $settings) {
	$cache = &drupal_static(__FUNCTION__, array());
	
	if (!isset($cache[$slid])) {
		$attrs = array('height', 'fullheight', 'pause', 'speed', 'pager');
		foreach ($attrs as $attr) {
			if (isset($settings[$attr])) {
				$cache[$slid]['data-' .$attr] = $settings[$attr];
			}
		}
	}
	
	return $cache[$slid];
}
