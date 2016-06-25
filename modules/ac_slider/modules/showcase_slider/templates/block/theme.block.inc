<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

/**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_showcase_slider(&$vars){
	$vars['slides'] = array();
	if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		drupal_add_js(drupal_get_path('module', 'showcase_slider') . '/js/showcase_slider.js');
		drupal_add_css(drupal_get_path('module', 'showcase_slider') . '/css/showcase_slider.css');
		acquia_include('slider', 'ac_slider');
		acquia_include('slider', 'showcase_slider');
		acquia_include('utility', 'showcase_slider');

		$slider = showcase_slider::get_by_id($vars['slid']);
		$vars['slides']['properties'] = (array)$slider->settings;

		foreach ($slides = showcase_slider_slide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides']['layers'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
		// slide id
		$vars['slide_id'] = 'showcase_slider_' . $vars['slid'];
		$vars['slider_attrs'] = showcase_slider_slider_settings_data($vars['slid'], $vars['slides']['properties']);
		$vars['slider_attrs']['id'] = $vars['slide_id'];
		$vars['slider_attrs']['class'] = array('showcase-container', 'ac-swipe-slider', 'ac-init-hidden');

		$vars['container_attrs'] = array();
		$vars['container_attrs']['class'] = array('ps-container');
		$vars['container_attrs']['style'] = '';

		if (isset($vars['slides']['properties']['bgColor']) && !empty($vars['slides']['properties']['bgColor'])) {
			$vars['container_attrs']['style'] = 'background-color: '.$vars['slides']['properties']['bgColor'].';';
		}

		if (isset($vars['slides']['properties']['height']) && !empty($vars['slides']['properties']['height'])) {
			$vars['container_attrs']['style'] .= 'height: '.$vars['slides']['properties']['height'].'px;';
		}

		if (isset($vars['slides']['properties']['width']) && !empty($vars['slides']['properties']['width'])) {
			$width = $vars['slides']['properties']['height'].'px;';
			if (isset($vars['slides']['properties']['fullwidth']) && $vars['slides']['properties']['fullwidth'] = 'true') {
				$width = '100%';
			}
			$vars['container_attrs']['style'] .= 'width: ' . $width;
		}
	}
}



