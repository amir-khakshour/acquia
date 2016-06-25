<?php

/**
 * @file
 * backend needed plugins defined here
 */

/**
 * implementing hook_library()
 * Only backend needed plugins defined here
 */
function acquia_library() {

	/** S1 - Admin Level Plugins **/
  $path = drupal_get_path('module', 'acquia');

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
	$libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');

  // collageplus.
  $libraries['collageplus'] = array(
    'title' => 'colorpicker',
    'website' => 'http://www.eyecon.ro/colorpicker',
		'version' => '1.0',
    'js' => array(
      $libs_path . '/jquery-collagePlus/jquery.collagePlus.min.js' => array(),
    ),
    'css' => array(
      $libs_path . '/jquery-collagePlus/css/transitions.css' => array(),
    ),
  ); 
	
  // colorpicker.
  $libraries['colorpicker'] = array(
    'title' => 'colorpicker',
    'website' => 'http://www.eyecon.ro/colorpicker',
		'version' => '1.0',
    'js' => array(
      $libs_path . '/colorpicker/colorpicker.min.js' => array(),
      $path . '/js/acquia.plugins.js' => array(),
    ),
    'css' => array(
      $libs_path . '/colorpicker/css/colorpicker.min.css' => array(),
    ),
  ); 
	
	// fontello
  $libraries['fontello'] = array(
    'title' => 'Fontello',
    'website' => 'http://fontello.com/',
		'version' => '1.0',
    'css' => array(
      $libs_path . '/fonts/fontello/css/fontello.css' => array(),
			$libs_path . '/fonts/fontello/css/fontello-ie7.css' => array('browsers' => array('IE' => 'IE 7', '!IE' => FALSE)),
    ),
  );
	
	// fontello
  $libraries['fontadmin'] = array(
    'title' => 'fontadmin',
    'website' => 'http://fontello.com/',
		'version' => '1.0',
    'css' => array(
      $libs_path . '/fonts/fontadmin/css/fontadmin.css' => array(),
			$libs_path . '/fonts/fontadmin/css/fontadmin-ie7.css' => array('browsers' => array('IE' => 'IE 7', '!IE' => FALSE)),
    ),
  );

	// matchMedia
  $libraries['matchMedia'] = array(
    'title' => 'matchMedia',
    'website' => 'https://github.com/paulirish/matchMedia.js',
		'version' => '1.0',
    'js' => array(
      $libs_path . '/plugins/matchMedia.js' => array(),
      $libs_path . '/plugins/matchMedia.addListener.js' => array(),
    ),
  );
  
	// matchMedia
  $libraries['perfect-scrollbar'] = array(
    'title' => 'perfect scrollbar',
    'website' => 'http://www.yuiazu.net/perfect-scrollbar/',
		'version' => '0.4.4',
    'js' => array(
      $libs_path . '/perfect-scrollbar/min/perfect-scrollbar.min.js' => array(),
    ),
    'css' => array(
      $path . '/css/plugins/perfect-scrollbar.css' => array(),
    ),
  );

  // debounced resize
  $libraries['resize_event'] = array(
    'title' => t('jQuery resize event'),
    'website' => 'http://benalman.com/projects/jquery-resize-plugin/',
    'version' => 'v1.1 - 3/14/2010',
     'js' => array(
       $libs_path . '/plugins/jquery.ba-resize.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // carouFredSel
  $libraries['owl.carousel'] = array(
    'title' => t('OwlCarousel2 jQuery plugin'),
    'website' => 'https://github.com/smashingboxes/OwlCarousel2',
    'version' => '2.0.0-beta.3',
     'js' => array(
       $libs_path . '/owl.carousel/owl.carousel.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/owl.carousel/assets/owl.carousel.min.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // flexslider
  $libraries['flexslider'] = array(
    'title' => t('Flexslider jQuery plugin'),
    'website' => 'http://www.woothemes.com/flexslider/',
    'version' => '2.2.0',
     'js' => array(
       $libs_path . '/flexslider/flexslider.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/flexslider/flexslider.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // gMap
  $libraries['gmap'] = array(
    'title' => t('gMap jQuery plugin'),
    'website' => 'http://github.com/marioestrada/jQuery-gMap',
    'version' => '2.1.4',
     'js' => array(
       $libs_path . '/gmap/jquery.gmap.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // Bootstrap popover
  $libraries['bootstrap-popover'] = array(
    'title' => t('Bootstrap Popover plugin'),
    'website' => 'http://twitter.github.com/bootstrap/javascript.html#popovers',
    'version' => '2.3.0',
     'js' => array(
       $libs_path . '/bootstrap-popover/bootstrap-popover.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/bootstrap-popover/bootstrap-popover.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // Bootstrap tooltip
  $libraries['bootstrap-tooltip'] = array(
    'title' => t('Bootstrap Tooltip plugin'),
    'website' => 'http://twitter.github.com/bootstrap/javascript.html#tooltips',
    'version' => '2.3.0',
     'js' => array(
       $libs_path . '/bootstrap-tooltip/bootstrap-tooltip.js' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/bootstrap-tooltip/bootstrap-tooltip.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // isotope
  $libraries['isotope'] = array(
    'title' => t('isotope'),
    'website' => 'http://isotope.metafizzy.co/',
    'version' => '1.5.25',
     'js' => array(
       $libs_path . '/isotope/isotope.js' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/isotope/isotope.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // isotope
  $libraries['jquery.countTo'] = array(
    'title' => t('jquery.countTo'),
    'website' => 'https://github.com/mhuggins/jquery-countTo',
    'version' => '1.0',
     'js' => array(
       $libs_path . '/jquery.countTo/jquery.countTo.js' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
  );
  
  // jquery-easing
  $libraries['jquery-easing'] = array(
    'title' => t('jquery-easing'),
    'website' => 'http://gsgd.co.uk/sandbox/jquery/easing/',
    'version' => '1.3',
     'js' => array(
       $libs_path . '/jquery-easing/jquery-easing.min.js' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
  );

  // isotope
  $libraries['magnific-popup'] = array(
    'title' => t('Magnific Popup'),
    'website' => 'https://github.com/dimsemenov/Magnific-Popup',
    'version' => '0.9.9',
     'js' => array(
       $libs_path . '/magnific-popup/jquery.magnific-popup.js' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/magnific-popup/magnific-popup.css' => array(
         'weight' => -5,
         'every_page' => TRUE,
       ),
     ),
  );
	
	$libraries['mediaelement'] = array(
    'title' => t('mediaelement'),
    'website' => 'http://mediaelementjs.com/',
    'version' => '2.13.2',
     'js' => array(
       $libs_path . '/mediaelement/mediaelement-and-player.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/mediaelement/mediaelementplayer.min.css' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
  );
  
	$libraries['responsiveslides'] = array(
    'title' => t('responsiveslides'),
    'website' => 'http://responsiveslides.com/',
    'version' => '1.54',
     'js' => array(
       $libs_path . '/responsiveslides/responsiveslides.min.js' => array(
         'weight' => 0,
         'every_page' => TRUE,
       ),
     ),
     'css' => array(
       $libs_path . '/responsiveslides/responsiveslides.css' => array(
         'weight' => 0,
         'every_page' => FALSE,
       ),
     ),
  );
  
	$libraries['touchswipe'] = array(
    'title' => t('responsiveslides'),
    'website' => 'http://responsiveslides.com/',
    'version' => '1.54',
     'js' => array(
       $libs_path . '/touchswipe/jquery.touchSwipe.min.js' => array(
         'weight' => 0,
         'every_page' => FALSE,
       ),
     ),
  );
  
	$libraries['progress-circle'] = array(
    'title' => t('Progress Circle'),
    'website' => 'http://qiao.github.io/ProgressCircle.js/',
    'version' => '1.0',
     'js' => array(
       $libs_path . '/progress-circle/progress-circle.js' => array(
         'weight' => 0,
         'every_page' => FALSE,
       ),
     ),
  );
  
  return $libraries;
}
