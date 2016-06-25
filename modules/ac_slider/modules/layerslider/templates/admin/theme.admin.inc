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

	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
	$vars['plugins_url'] = url($libs_path . '/layerslider');
	$vars['skins'] = layerslider_get_skins_options();

	// load given slider settings
	$slider = acquiaSlider::get_by_id($vars['slid']);
	$vars['slider']['properties'] = $slider->settings;
	$layers = acquiaSlide::get_by_slider_id($vars['slid']);
	//$vars['slider']['layers'] = $layers;
	foreach ($layers as $layer) {
		$vars['slider']['layers'][$layer->position]['sublayers'] = $layer->layers;
		$vars['slider']['layers'][$layer->position]['properties'] = $layer->settings;
	}
	layerslider_load_resources('admin_slider');
}
