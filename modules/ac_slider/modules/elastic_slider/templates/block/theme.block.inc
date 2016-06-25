<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

 /**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_elastic_slider(&$vars){
	$vars['slides'] = array();
	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
    acquia_include('slider', 'ac_slider');
    acquia_include('slider', 'elastic_slider');
    acquia_include('utility', 'elastic_slider');
    
		$slider = elasticSlider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;
		foreach ($slides = elasticSlide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
    // slide id
    $vars['slide_id'] = 'elasticSlider_' . $vars['slid'];
    elastic_slider_load_resources('slider');
	}
}
