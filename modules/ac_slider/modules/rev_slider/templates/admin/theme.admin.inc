<?php

/**
 * @file preprocess function for admin section of layerslider theme
 */

 /**
 * Preprocess of theme_layerslider_slides_edit()
 */
function template_preprocess_rev_slider_slides_edit(&$vars){
	acquia_include('slider', 'ac_slider');
	acquia_include('utility', 'rev_slider');
	
	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');
	$vars['plugins_url'] = url(REVSLIDER_PLUGIN_PATH);
	
  $vars['start_anim'] = rev_slider_start_animation();
  $vars['end_anim'] = rev_slider_end_animation();
  $vars['easing'] = rev_slider_easing();
  $vars['end_easing'] = rev_slider_end_easing();

	// load given slider settings
  $slider = acquiaSlider::get_by_id($vars['slid']);
	$slider->settings['title'] = $slider->title;
	$vars['slider']['properties'] = $slider->settings;
  $layers = acquiaSlide::get_by_slider_id($vars['slid']);
	//$vars['slider']['layers'] = $layers;
	foreach ($layers as $layer) {
		$vars['slider']['layers'][$layer->position]['sublayers'] = $layer->layers;
		$vars['slider']['layers'][$layer->position]['properties'] = $layer->settings;
	}
	
	$caption_classes = rev_slider_get_caption_array( REVSLIDER_PLUGIN_PATH . '/css/captions.css');
	drupal_add_js(array('captionClasses' => drupal_json_encode($caption_classes)), 'setting');
}
