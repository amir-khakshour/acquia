<?php
/**
 * @file 
 */
class content_slider extends acquiaSlider{
	
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
			echo theme('content_slider', array('preview_mode' => true, 
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
			'easing' => 'fade',
			'animation' => 'fade',              //String: Select your animation type, "fade" or "slide"
			'easing' => 'swing',                //{NEW} String: Determines the easing method used in jQuery transitions. jQuery easing plugin is supported!
			'direction' => 'horizontal',        //String: Select the sliding direction, "horizontal" or "vertical"
			'reverse' => 'false',                 //{NEW} Boolean: Reverse the animation direction
			'animationLoop' => 'true',             //Boolean: Should the animation loop? If false, directionNav will received "disable" classes at either end
			'smoothHeight' => 'false',            //{NEW} Boolean: Allow height of the slider to animate smoothly in horizontal mode  
			'startAt' => 0,                     //Integer: The slide that the slider should start on. Array notation (0 = first slide)
			'slideshow' => 'true',                //Boolean: Animate slider automatically
			'slideshowSpeed' => 7000,           //Integer: Set the speed of the slideshow cycling, in milliseconds
			'animationSpeed' => 600,            //Integer: Set the speed of animations, in milliseconds
			'initDelay' => 0,                   //{NEW} Integer: Set an initialization delay, in milliseconds
			'randomize' => 'false',               //Boolean: Randomize slide order
			'bgColor' => '',
			'speed' => 1000,
			'timeout' => 4000,
			
			
			// Usability features
			'pauseOnAction' => 'true',            //Boolean' => Pause the slideshow when interacting with control elements, highly recommended.
			'pauseOnHover' => 'false',            //Boolean' => Pause the slideshow when hovering over slider, then resume when no longer hovering
			'useCSS' => 'true',                   //{NEW} Boolean' => Slider will use CSS3 transitions if available
			'touch' => 'true',                    //{NEW} Boolean' => Allow touch swipe navigation of the slider on touch-enabled devices
			'video' => 'false',                   //{NEW} Boolean' => If using video in the slider, will prevent CSS3 3D Transforms to avoid graphical glitches
			
			// Primary Controls
			'controlNav' => 'true',               //Boolean' => Create navigation for paging control of each clide? Note' => Leave true for manualControls usage
			'directionNav' => 'true',             //Boolean' => Create navigation for previous/next navigation? (true/false)
			'prevText' => 'Previous',           //String' => Set the text for the "previous" directionNav item
			'nextText' => 'Next',
      
      // Carousel Options
      'itemWidth' => 0,                   //{NEW} Integer: Box-model width of individual carousel items, including horizontal borders and padding.
      'itemMargin'=> 0,                  //{NEW} Integer: Margin between carousel items.
      'minItems'=> 1,                    //{NEW} Integer: Minimum number of carousel items that should be visible. Items will resize fluidly when below this.
      'maxItems'=> 0,                    //{NEW} Integer: Maxmimum number of carousel items that should be visible. Items will resize fluidly when above this limit.
      'move'=> 0,                        //{NEW} Integer: Number of carousel items that should move on animation. If 0, slider will move all visible items.
		 );
		 
     $default_settings['thumb_style'] = acquia_variable_get('default_thumb_style', 'square-small');
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

class content_slide extends acquiaSlide{
	public function save() {
	}
}