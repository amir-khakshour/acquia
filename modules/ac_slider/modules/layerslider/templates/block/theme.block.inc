<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

 /**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_layerslider(&$vars){
	acquia_include('utility', 'layerslider');
	acquia_include('slider', 'layerslider');
	
	$vars['slides'] = array();
	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		$slider = layerslider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;
		foreach ($slides = layerSlide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
	}
	// slide id
	$vars['slide_id'] = 'layerslider_' . $vars['slid'];
	layerslider_load_resources();
	layerslider_render_js($vars['slide_id'], $vars['slides']);
}
