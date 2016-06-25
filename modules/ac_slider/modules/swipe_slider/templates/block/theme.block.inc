<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

 /**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_swipe_slider(&$vars){
	$vars['slides'] = array();
	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		
		drupal_add_js(drupal_get_path('module', 'swipe_slider') . '/js/swipe_slider.js');
		drupal_add_css(drupal_get_path('module', 'swipe_slider') . '/css/swipe_slider.css');
    acquia_include('slider', 'ac_slider');
    acquia_include('slider', 'swipe_slider');
    acquia_include('utility', 'swipe_slider');
    
		$slider = swipe_slider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;

		foreach ($slides = swipe_slide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
    // slide id
		$vars['slide_id'] = 'swipe_slider_' . $vars['slid'];
    $vars['slider_attrs'] = swipe_slider_slider_settings_data($vars['slid'], $vars['slides']['properties']);
    $vars['slider_attrs']['id'] = $vars['slide_id'];
    $vars['slider_attrs']['class'] = array('swiper-container', 'ac-swipe-slider', 'ac-init-hidden');
		
    $vars['slider_outter_attrs']['class'] = array('swiper-outter');
		$vars['slider_outter_attrs']['style'] = '';
		if (isset($vars['slides']['properties']['bgColor']) && !empty($vars['slides']['properties']['bgColor'])) {
			$vars['slider_outter_attrs']['style'] = 'background-color: '.$vars['slides']['properties']['bgColor'].';';
		}
		
		if (isset($vars['slides']['properties']['background_fid']) && !empty($vars['slides']['properties']['background_fid'])) {
			$bg = file_create_url(file_load($vars['slides']['properties']['background_fid'])->uri);
			$vars['slider_outter_attrs']['style'] .= 'background-image: url('.$bg.');';
			$vars['slider_outter_attrs']['style'] .= 'background-size: cover;';
		}

		$vars['slider_wrapper_attrs']['class'] = array('swiper-wrapper');
		if (isset($vars['slides']['properties']['height']) && !empty($vars['slides']['properties']['height'])) {
			$vars['slider_outter_attrs']['style'] .= 'height: '.$vars['slides']['properties']['height'].'px;';
		}
    swipe_slider_load_resources('swipe-slider');
	}
}
