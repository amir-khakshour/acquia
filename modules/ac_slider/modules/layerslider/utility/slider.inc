<?php
/**
 * @file 
 */
class layerslider extends acquiaSlider{
	
  public static function register_settings() {
		
		

		// Add slider
		if (isset($_POST['action']) && $_POST['action'] == 'ls_save_slider' && strstr($_SERVER['REQUEST_URI'], SLIDER_LIST_PATH)) {
			$slid = (int)$_POST['slider_id'];
			$slider = self::get_by_id($slid);

			// save slider Main data
			$slider->title = isset($_POST['layerslider-slides']['properties']['title']) ? $_POST['layerslider-slides']['properties']['title'] : $slider->title;
			//$slider->description = $custom['sls_desc'];
			$slider->settings = $_POST['layerslider-slides']['properties'];
			$slider->save();

			acquiaSlide::delete_by_slider($slid);
			// save slider data
			foreach($_POST['layerslider-slides']['layers'] as $sid => $slide) {
				// add modification 
				if (!isset($slide['sublayers'])) {
					$slide['sublayers'] = array();
				}
				
				// Add modifications
				acquiaSlide::create($slid, $sid, $slide['properties'], $slide['sublayers']);
			}

			echo $slid;

			die();
		}

	}

  /**
   * prepare slide global settings before saving to DB
   */
  public static function prepare_settings($settings, $type = 'slide') {

		switch ($type) {
			default:
			case 'slide':
	    $defaults = self::get_default_settings();	
				break;
			
			case 'layer':
				break;
		}
		
    // remove other values
    foreach (array_keys($defaults) as $key) {
      if (array_key_exists($key, $settings)) {
        $defaults[$key] = $settings[$key];
      }
    }

    return $defaults;
  }
	
  public static function get_default_settings($key = NULL) {
    static $default_settings = array(
			 // basic
			 'title'                   => '',
			 'width'                   => 960,
			 'height'                  => 350,
			 'responsive'              => 'on',
			 'forceresponsive'         => 'on',
			 'responsiveUnder'         => 0,
			 'sublayerContainer'       => 0,
			 // slideshow
			 'autostart'               => 'on',
			 'pauseonhover'            => 'on',
			 'firstlayer '             => 1,
			 'animatefirstlayer'       => 'on',
			 'randomslideshow'         => 'off',
			 'twowayslideshow'         => 'on',
			 'loops'                   => 0,
			 'forceloopnum'            => 'on',
			 'autoplayvideos'          => 'on',
			 'autopauseslideshow'      => 'auto',
			 'youtubepreview'          => 'maxresdefault.jpg',
			 'keybnav'                 => 'on',
			 'touchnav'                => 'on',
			 // appearance
			 'skin'                    => 'defaultskin',
			 'skinsPath'               => LAYERSLIDER_SKIN_PATH,
			 'backgroundcolor'         => '',
			 'backgroundimage'         => '',
			 'sliderstyle'             => '',
			 // Navigation
			 'navprevnext'             => 'on',
			 'navstartstop'            => 'on',
			 'navbuttons'              => 'on',
			 'hoverprevnext'           => 'on',
			 'hoverbottomnav'          => 'on',
			 'bartimer'                => 'off',
			 'circletimer'             => 'on',
			 'thumb_nav'               => 'hover',
			 'thumb_width'             => 100,
			 'thumb_height'            => 60,
			 'thumb_container_width'   => '60%',
			 'thumb_active_opacity'    => 35,
			 'thumb_inactive_opacity'  => 100,
			 // misc
			 'imgpreload'              => 'on',
			 'relativeurls'            => 'off',
			 'bodyinclude'             => 'off',
			 'yourlogo'                => 0,
			 'yourlogostyle'           => 'left: 10px; top: 10px;',
			 'yourlogolink'            => '',
			 'yourlogotarget'          => '_self',
		 );
		 
		 if (isset($key)) {
			 // Return the specific item
			 if (array_key_exists($key, $default_settings)) {
				 return $default_settings[$key];
			 }
		 }
		 // Return all items
		 return $default_settings;
  }
	
}

class layerSlide extends acquiaSlide{

}