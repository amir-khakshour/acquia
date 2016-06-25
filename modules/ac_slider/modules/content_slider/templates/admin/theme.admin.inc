<?php
/**
 * @file preprocess function for admin section of layerslider theme
 */

 /**
 * Preprocess of theme_layerslider_slides_edit()
 */
function template_preprocess_content_slider_slides_edit(&$vars){
	acquia_include('options');
	acquia_include('slider', 'ac_slider');
	acquia_include('slider', 'content_slider');
	acquia_include('options', 'content_slider');
  drupal_add_library('acquia', 'content_slider');
	drupal_add_css(drupal_get_path('module', 'content_slider') . '/css/content_slider-admin-preview.css');

	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
	$vars['plugins_url'] = url($libs_path . '/layerslider');

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
