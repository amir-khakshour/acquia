<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

/**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_flexslider(&$vars){
	$vars['slides'] = array();

	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		acquia_include('slider', 'ac_slider');
		acquia_include('slider', 'flexslider');
		acquia_include('utility', 'flexslider');
		$slider = flexSlider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;
		foreach ($slides = flexSlide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
		// slide id
		$vars['slide_id'] = 'flexSlider_' . $vars['slid'];
		flexslider_load_resources('slider');
	}
}
