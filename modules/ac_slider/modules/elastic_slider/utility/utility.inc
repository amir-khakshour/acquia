<?php
/**
 * General utility functions to work with elastic slider
 */

 
/**
 * Load resource
 */
function elastic_slider_load_resources($type = 'slider') {
	switch($type) {
    // admin slider resources
		case 'admin':
			$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
			
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
			drupal_add_library('acquia', 'jquery-easing');
			drupal_add_library('ac_slider', 'acquia_slider.admin');
			drupal_add_css($libs_path . '/elastic-slider/css/elastic-slider.css');
			break;
	
    // slider frontend resources
		default:
		case 'slider':
			drupal_add_library('elastic_slider', 'elastic_slider');
			drupal_add_library('acquia', 'touchswipe');
			break;	
	}
}
