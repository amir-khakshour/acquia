<?php
/**
 * @file 
 */
class swipe_slider extends acquiaSlider{
	
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
        // Styled bg
        if (isset($_POST['acquiaSlider']['properties']['bg_style']) &&
            !empty($_POST['acquiaSlider']['properties']['bg_style']) &&
            !empty($slide['properties']['background_fid'])) {
          acquia_include('media');
          $slide['properties']['bg_formatted'] = image_style_url($_POST['acquiaSlider']['properties']['bg_style'], file_load($slide['properties']['background_fid'])->uri);
        }
				
				// Formatted title and subtitle
				$slide['properties']['title_formtted'] = check_markup($slide['properties']['title'], 'full_html');
				$slide['properties']['subtitle_formtted'] = check_markup($slide['properties']['subtitle'], 'full_html');

        // thumb
        if (isset($slide['properties']['thumbnail_fid']) && empty($slide['properties']['thumbnail_fid']) && !empty($slide['properties']['video_fid'])) {
          acquia_include('media');
          $thumb_fid = acquia_external_video_thumb($slide['properties']['video_fid']);
        }elseif (isset($slide['properties']['thumbnail_fid']) && !empty($slide['properties']['thumbnail_fid'])) {
          $thumb_fid = $slide['properties']['thumbnail_fid'];
        }else{
          $thumb_fid = $slide['properties']['background_fid'];
        }
        $thumb_style = isset($_POST['acquiaSlider']['properties']['thumb_style']) ? $_POST['acquiaSlider']['properties']['thumb_style'] : acquia_variable_get('default_thumb_style', 'square-small');
        $slide['properties']['thumbnail_formatted'] = image_style_url($thumb_style, file_load($thumb_fid)->uri);
        
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
			echo theme('swipe_slider', array('preview_mode' => true, 
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
			'width' => 960,
			'height' => 450,
      'fullwidth' => 'true',
      'fullheight' => 'false',
			'speed' => 300, 
			'pause' => 5000, 
			'bgColor' => '', 
		 );
		 
     $default_settings['bg_style'] = '';

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

class swipe_slide extends acquiaSlide{
	public function save() {
	}
}