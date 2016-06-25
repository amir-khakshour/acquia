<?php
/**
 * @file preprocess function for admin section of layerslider theme
 */

/**
 * Preprocess of theme_layerslider_slides_edit()
 */
function template_preprocess_layerslider_slides_edit(&$vars){
	acquia_include('slider', 'ac_slider');
	acquia_include('slider', 'layerslider');
	acquia_include('utility', 'layerslider');

	// Layerslider compatibility
	$vars['id'] = $vars['slid'];

	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
	$vars['plugins_url'] = url($libs_path . '/layerslider');
	$vars['skins'] = layerslider_get_skins_options();
	$vars['uploadClass'] = 'ls-upload';

	// load given slider settings
	$slider = acquiaSlider::get_by_id($vars['id']);
	$vars['slider']['properties'] = $slider->settings;
	$layers = acquiaSlide::get_by_slider_id($vars['slid']);
	//$vars['slider']['layers'] = $layers;
	foreach ($layers as $layer) {
		$vars['slider']['layers'][$layer->position]['sublayers'] = $layer->layers;
		$vars['slider']['layers'][$layer->position]['properties'] = $layer->settings;
	}

	// for new slider
	if (!isset($vars['slider']['layers'])) {
		$vars['slider']['layers'] = array(array('properties' => $vars['lsDefaults']['layers']));
	}
	layerslider_load_resources('admin_slider');
}


function theme_layerslider_block($vars){
	acquia_include('utility');
	acquia_include('utility', 'layerslider');
	acquia_include('slider', 'layerslider');

	// Returned data
	$data = '';
	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		layerslider_load_resources('slider');
		$id = $vars['slid'];
		$slider = layerslider::get_by_id($vars['slid']);
		$slides['properties'] = (array)$slider->settings;
		foreach (layerSlide::get_by_slider_id($vars['slid']) as $layer) {
			$slides['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
	}
	// Include slider file
	if(is_array($slides)) {
		// Get phpQuery
		if(!class_exists('phpQuery')) {
			include LS_ROOT_PATH.'/helpers/phpQuery.php';
		}

		include LS_ROOT_PATH.'/config/defaults.php';
		include LS_ROOT_PATH.'/../themes/slider_markup_init.php';
		include LS_ROOT_PATH.'/../themes/slider_markup_html.php';
		$data = implode('', $data);
	}
	return $data;
}