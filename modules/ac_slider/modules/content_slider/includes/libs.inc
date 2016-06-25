<?php

/**
 * @file
 * backend needed plugins defined here
 */

/**
 * implementing hook_library()
 * Only backend needed plugins defined here
 */
function content_slider_library() {

 /** S2 - Middle Level Plugins **/
 $libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');

	// tooltip.
  $libraries['content-slider'] = array(
    'title' => 'tooltip',
    'website' => 'http://www.aquiathemes.net',
		'version' => '1.0',
    'js' => array(
      $libs_path . '/content-slider/content-slider.js' => array(),
    ),
    'css' => array(
      $libs_path . '/content-slider/content-slider.css' => array(),
    ),
  );

  return $libraries;
}
