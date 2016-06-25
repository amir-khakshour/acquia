<?php
/**
 * @file 
 */
class revSlider extends acquiaSlider{

  public static function register_settings() {
		
		
		// Add slider
		if (isset($_POST['slider_edit']) && $_POST['slider_edit'] == 1 && strstr($_SERVER['REQUEST_URI'], SLIDER_LIST_PATH)) {
			$slid = (int)$_POST['slid'];
			$slider = self::get_by_id($slid);
			// save slider Main data
			$slider->title = isset($_POST['acquiaSlider']['properties']['title']) ? $_POST['acquiaSlider']['properties']['title'] : $slider->title;
			//$slider->description = $custom['sls_desc'];
			$slider->settings = self::prepare_settings($_POST['acquiaSlider']['properties']);
			$slider->save();
			
			acquiaSlide::delete_by_slider($slid);
			// save slider data
			foreach($_POST['acquiaSlider']['layers'] as $sid => $slide) {
				// add modification 
				if (!isset($slide['sublayers'])) {
					$slide['sublayers'] = array();
				}
				// update start time
				foreach ($slide['sublayers'] as $delta => $item) {
					if ($item['start'] == 0) {
						$slide['sublayers'][$delta]['start'] = rev_slider_getNextTime($slide['sublayers'], $delta);
					}
				}
				$slide['properties']['slide_transition'] = explode(',', $slide['properties']['slide_transitions']);

				acquiaSlide::create($slid, $sid, $slide['properties'], $slide['sublayers']);
				
			}

			echo $slid;

			die();
		}		// Returns Preview
		else if (isset($_POST['slider_play']) 
		&& $_POST['slider_play'] == 1 
		&& strstr($_SERVER['REQUEST_URI'], SLIDER_LIST_PATH)
		&& isset($_POST['acquiaSlider'])) {
		
			foreach($_POST['acquiaSlider']['layers'] as $sid => $slide) {
				// add modification 
				// update start time
				foreach ($slide['sublayers'] as $delta => $item) {
					if ($item['start'] == 0) {
						$slide['sublayers'][$delta]['start'] = rev_slider_getNextTime($slide['sublayers'], $delta);
					}
				}
				$slide['properties']['slide_transition'] = explode(',', $slide['properties']['slide_transitions']);	
			}
			
			echo theme('rev_slider', array('preview_mode' => true, 
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
		$off_checks = array();
		switch ($type) {
			default:
			case 'slide':
	    $defaults = self::get_default_settings();	
	    $off_checks = self::get_off_checkboxes($type);	
				break;
			
			case 'layer':
				break;
		}
		
    // remove other values
    foreach (array_keys($defaults) as $key) {
      if (array_key_exists($key, $settings)) {
        $defaults[$key] = $settings[$key];
      }else if (in_array($key, $off_checks)) {
				$defaults[$key] = 'off';
			}
    }
    return $defaults;
  }
	
	/**
	 * Get list of checkboxes that have off value if not set in slider settings.
	 *
	 * @param string $type
	 *	type of settings (slider|layer|sublayer)
	 */
  public static function get_off_checkboxes($type) {
		switch ($type) {
			default:
			case 'slide':
				return array(
					'touchenabled',
					'stop_on_hover',
				);
			break;
			
			case 'layer':
				return array(
					'fullwidth_centering',
				);
				
			case 'sublayer':
				return array(
					
				);
			break;
			
		}

	}
	
  public static function get_default_settings($key = NULL) {
    static $default_settings = array(
			// basic
			'slider_type'                     => 'fixed',
			'width'                           => 960,
			'height'                          => 350,
			'responsitive_w1'                 => 940,
			'responsitive_sw1'                => 770,
			'responsitive_w2'                 => 780,
			'responsitive_sw2'                => 500,
			'responsitive_w3'                 => 510,
			'responsitive_sw3'                => 310,
			'responsitive_w4'                 => '',
			'responsitive_sw4'                => '',
			'responsitive_w5'                 => '',
			'responsitive_sw5'                => '',
			'responsitive_w6'                 => '',
			'responsitive_sw6'                => '',
			'fullscreen_offset_container'     => '',
			// -> profile settings
			// General
			'delay'                           => 9000,
			'shuffle'                         => 'false',
			'lazy_load'                       => 'false',
			'load_googlefont'                 => 'false',
			'google_font'                     => 'PT+Sans+Narrow:400,700',
			'stop_slider'                     => 'false',
			'stop_after_loops'                => 0,
			'stop_at_slide'                   => 2,
			'disable_title'                   => 'false',
			//'videoJsPath'                     => acquia_variable_get('libs_path', 'sites/all/libraries') . '/revolutionslider/videojs/',
			// Position
			'position'                        => 'center',
			'margin_top'                      => 0,
			'margin_bottom'                   => 0,
			'margin_left'                     => 0,
			'margin_right'                    => 0,
			// Appearance
			'shadow_type'                     => 0,
			'show_timerbar'                   => 'top',
			'background_color'                => '#E9E9E9',
			'padding'                         => 0,
			'background_dotted_overlay'       => 'none',
			'show_background_image'           => 'false',
			'background_image'                => '',
			'background_image_fid'            =>  -1,
			'bg_fit'                					=> 'cover',
			'bg_repeat'                				=> 'repeat',
			'bg_position'                				=> 'center center',
			// Navigaion
			'touchenabled'                    => 'on',
			'stop_on_hover'                   => 'on',
			'navigaion_type'                  => 'bullet',
			'navigation_arrows'               => 'solo',
			'navigation_style'                => 'round',
			'navigaion_always_on'             => 'false',
			'hide_thumbs'                     => 200,
			'navigaion_align_hor'             => 'center',
			'navigaion_align_vert'            => 'bottom',
			'navigaion_offset_hor'            => 0,
			'navigaion_offset_vert'           => 20,
			'leftarrow_align_hor'             => 'left',
			'leftarrow_align_vert'            => 'center',
			'leftarrow_offset_hor'            => 20,
			'leftarrow_offset_vert'           => 0,
			'rightarrow_align_hor'            => 'right',
			'rightarrow_align_vert'           => 'center',
			'rightarrow_offset_hor'           => 20,
			'rightarrow_offset_vert'          => 0,
			// Thumbnail
			'thumb_width'                     => 100,
			'thumb_height'                    => 50,
			'thumb_amount'                    => 5,
			// Mobile Visibility
			'hide_slider_under'               => 0,
			'hide_defined_layers_under'       => 0,
			'hide_all_layers_under'           => 0,
			// Alternative First Slide
			'start_with_slide'                => 1,
			'first_transition_active'         => 'false',
			'first_transition_type'           => 'fade',
			'first_transition_duration'       => 300,
			'first_transition_slot_amount'    => 7,
			'link_type'                       => 'regular',
			'link'                            => '',
			'link_open_in'                    => '_self',
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

class revSlide extends acquiaSlide{

}