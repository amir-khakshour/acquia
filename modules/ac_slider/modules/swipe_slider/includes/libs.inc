<?php

/**
 * @file
 * backend needed plugins defined here
 */

/**
 * implementing hook_library()
 * Only backend needed plugins defined here
 */
function swipe_slider_library() {

 /** S2 - Middle Level Plugins **/
 $libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');

	// tooltip.
  $libraries['swipe-slider'] = array(
    'title' => 'swipeslider',
    'website' => 'http://www.aquiathemes.net',
		'version' => '1.0',
    'js' => array(
      $libs_path . '/swiper/dist/idangerous.swiper.min.js' => array(),
    ),
    'css' => array(
      $libs_path . '/swiper/dist/idangerous.swiper.css' => array(),
    ),
  );

  return $libraries;
}
