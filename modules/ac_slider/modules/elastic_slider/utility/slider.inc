<?php
/**
 * @file 
 */
class elasticSlider extends acquiaSlider{
	
  public static function register_settings() {
		
		

		// Add slider
		if (isset($_POST['slider_edit']) && $_POST['slider_edit'] == 1 && strstr($_SERVER['REQUEST_URI'], SLIDER_LIST_PATH)) {
			$slid = (int)$_POST['slid'];
			$slider = self::get_by_id($slid);

			// save slider Main data
			$slider->title = isset($_POST['acquiaSlider']['properties']['title']) ? $_POST['acquiaSlider']['properties']['title'] : $slider->title;
			//$slider->description = $custom['sls_desc'];
			$slider->settings = $_POST['acquiaSlider']['properties'];
			$slider->save();

			acquiaSlide::delete_by_slider($slid);
			// save slider data
			foreach($_POST['acquiaSlider']['layers'] as $sid => $slide) {
				// add modification 
				if (!isset($slide['sublayers'])) {
					$slide['sublayers'] = array();
				}
				acquia_include('media');
				$thumb_style = isset($_POST['acquiaSlider']['properties']['thumb_style']) ? $_POST['acquiaSlider']['properties']['thumb_style'] : 'elastic_slider_thumb';
				$thumb_fid = isset($slide['properties']['thumbnail_fid']) && !empty($slide['properties']['thumbnail_fid']) ? $slide['properties']['thumbnail_fid'] : $slide['properties']['background_fid'];
				$slide['properties']['thumbnail_formatted'] = acquia_image_format_simple(array('fid' => $thumb_fid, 'style' => array('image_style' => $thumb_style)));
				
				// Add modifications
				acquiaSlide::create($slid, $sid, $slide['properties'], $slide['sublayers']);
			}

			echo $slid;

			die();
		}// Returns Preview
		else if (isset($_POST['slider_play']) 
		&& $_POST['slider_play'] == 1 
		&& strstr($_SERVER['REQUEST_URI'], SLIDER_LIST_PATH)
		&& isset($_POST['acquiaSlider'])) {
			echo theme('elastic_slider', array('preview_mode' => true, 
																		 'slid' => (int)$_POST['slid'],
																		 'slides' => $_POST['acquiaSlider']['layers'], 
																		 'settings' => $_POST['acquiaSlider']['properties']));
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
			 'width'                   => 960,
			 'height'                  => 350,
			 'fullwidth'               => 'true',
			 'animation'               => 'sides',
			 'autoplay'                => 'false',
			 'slideshow_interval'      => 3000,
			 'speed'      						 => 800,
			 'easing'         				 => '',
			 'titlesFactor'       		 => 0.60,
			 'titlespeed'       		   => 800,
			 'titlespeed'       		   => 800,
			 'titleeasing'       		   => '',
			 'thumbMaxWidth'       		 => 150,
			 'thumb_style'       		 => 'elastic_slider_thumb',
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

class elasticSlide extends acquiaSlide{
	public function save() {
	}
}