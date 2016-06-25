<?php

/**
 * @file preprocess functions for block dispaly of layerslider
 */

 /**
 * Preprocess of theme_layerslider()
 */
function template_preprocess_rev_slider(&$vars){
	acquia_include('slider', 'rev_slider');
	$vars['slider'] = array();
	if (isset($vars['preview_mode']) && $vars['preview_mode'] == true) {
		
	}else if (isset($vars['slid']) && is_numeric($vars['slid'])) {
		$slider = revSlider::get_by_id($vars['slid']);
		$vars['settings'] = (array)$slider->settings;
		foreach ($slides = revSlide::get_by_slider_id($vars['slid']) as $layer) {
			$vars['slides'][] = array('properties' => $layer->settings, 'sublayers' => $layer->layers);
		}
	}

	// Use already assigned id for preview mode
	if (isset($vars['slide_id'])) {
		$vars['settings']['id'] = $vars['slide_id'];
	}
	
	// Assign HTML properties
	$vars['prop'] = rev_slider_get_slider_prop($vars['settings']);
	
  // Add Slider settings to Drupal.settings
	//rev_slider_add_js_settings($vars['slide_id'], $vars['slider']['properties']);

	rev_slider_load_resources('slider');
}

/**
 * Default theme implementation for rev_slider_slides
 */
function theme_rev_slider_slides(&$vars){
  $output = '';

  // Build the list
  if (!empty($vars['slides'])) {
    $output .= "<ul>";
    foreach ($vars['slides'] as $i => $slide) {

      $output .= theme('rev_slider_slide', array(
        'slide' => $slide,
        'settings' => $vars['settings'],
        'index' => $i,
      ));
    }
    $output .= "</ul>";
  }else {
		return '<div class="no-slides-text">
		No slides found, please add some slides
		</div>';
	}

  return $output;
}

/**
 * Default theme implementation for rev_slider_sublayers
 */
function theme_rev_slider_sublayers(&$vars){
  $output = '';

  // Build the list
  if (!empty($vars['sublayers'])) {
    foreach ($vars['sublayers'] as $sublayer) {
      $output .= theme('rev_slider_sublayer', array(
        'sublayer' => $sublayer,
      ));
    }
  }

  return $output;
}

/**
 * Default theme implementation for rev_slider_slide
 */
/*function theme_rev_slider_slide(&$vars){
	$item = &$vars['item'];
	$settings = &$vars['settings'];
	$index = &$vars['index'];
	
  return $output;
}
*/