<?php

/**
 * @file
 * backend needed plugins defined here
 */

/**
 * implementing hook_library()
 * Only backend needed plugins defined here
 */
function ac_visual_composer_library() {

	/** S1 - Admin Level Plugins **/
  $path = drupal_get_path('module', 'acquia');

	// backend.
  $libraries['tooltip'] = array(
    'title' => 'tooltip',
    'website' => 'http://www.aquiathemes.net',
		'version' => '1.0',
    'js' => array(
      $path . '/js/acquia.plugins.js' => array(),
    ),
    'css' => array(
      $path . '/css/acquia.plugins.css' => array(),
    ),
  );
  
  // tooltip.
  $libraries['tooltip'] = array(
    'title' => 'tooltip',
    'website' => 'http://www.aquiathemes.net',
		'version' => '1.0',
    'js' => array(
      $path . '/js/acquia.plugins.js' => array(),
    ),
    'css' => array(
      $path . '/css/acquia.plugins.css' => array(),
    ),
  );

	/** S2 - Middle Level Plugins **/
	
  return $libraries;
}
