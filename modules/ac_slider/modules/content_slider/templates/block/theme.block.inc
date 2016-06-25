<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

/**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_content_slider(&$vars){
	$vars['slides'] = array();

	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		acquia_include('slider', 'ac_slider');
		acquia_include('slider', 'content_slider');
		acquia_include('utility', 'content_slider');

		$slider = content_slider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;
		foreach ($slides = content_slide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
		// slide id
		$vars['slide_id'] = 'content_slider_' . $vars['slid'];
		content_slider_load_resources('content-slider');
	}
}
