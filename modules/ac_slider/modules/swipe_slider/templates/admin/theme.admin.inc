<?php
/**
 * @file preprocess function for admin section of layerslider theme
 */

/**
 * Preprocess of theme_layerslider_slides_edit()
 */
function template_preprocess_swipe_slider_slides_edit(&$vars){
	acquia_include('options');
	acquia_include('slider', 'ac_slider');
	acquia_include('slider', 'swipe_slider');
	acquia_include('options', 'swipe_slider');
	drupal_add_library('acquia', 'swipe_slider');
	drupal_add_css(drupal_get_path('module', 'swipe_slider') . '/css/swipe_slider-admin-preview.css');

	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
	$vars['plugins_url'] = url($libs_path . '/layerslider');
	$vars['transitions'] = swiper_slider_transitions();
	$vars['bg_positions'] = acquia_css_background_position();

	// load given slider settings
	$slider = acquiaSlider::get_by_id($vars['slid']);
	$vars['slider']['properties'] = $slider->settings;
	$vars['slider']['properties']+= array('title' => $slider->title);
	$layers = acquiaSlide::get_by_slider_id($vars['slid']);

	//$vars['slider']['layers'] = $layers;
	foreach ($layers as $layer) {
		$vars['slider']['layers'][$layer->position]['sublayers'] = $layer->layers;
		$vars['slider']['layers'][$layer->position]['properties'] = $layer->settings;
	}
}
