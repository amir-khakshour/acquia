<?php
/**
 * General Utility functions to work with acquia sliders
 */
function _e($text, $domain = 'default') {
  print t($text);
}

/**
 * 
 * turn boolean to string
 */
function ac_slider_getParam($key, $default, $settings, $bool = TRUE){
  if (!isset($settings[$key])) {
    $value = $default;
  }else {
		$value = $settings[$key];
	}
	
	if (in_array($value, array('true', 'false', 'on', 'off'))) {
		if ($bool) {
			return $value == 'true' ? 'true' : 'false';
		}
		return $value == 'true' ? '"on"' : '"off"';
	}else if (is_numeric($value)) {
		return $value;
	}else {
		return '"' .$value .'"';
	}
}

/**
 * Returns the array of supported sliders.
 *
 * @see hook_ac_slider_info
 *
 * @param $slider
 *   A specific type of slider that supports ac_slider.
 * @param $key
 *   A key that hook_ac_slider_info supports.
 *
 * @return An array of slider labels keyed by the slider names.
 */
function get_sliders_info($slider = NULL, $key = NULL, $reset = TRUE) {
  $sliders = &drupal_static(__FUNCTION__);
  $slider_by_key = &drupal_static(__FUNCTION__ . '_by_key');

  if ($reset || !isset($sliders) || !isset($slider_by_key)) {
    $sliders = $slider_by_key = array();
    if (!$reset && ($cache = cache_get('ac_sliders_info'))) {
      $sliders = $cache->data;
    }
    else {
      $sliders = module_invoke_all('ac_sliders_info');
      drupal_alter('ac_sliders_info', $sliders);
      cache_set('ac_sliders_info', $sliders);
    }

    foreach ($sliders as $slider_type => $slider_information) {
      foreach ($slider_information as $slider_key => $slider_value) {
        $slider_by_key[$slider_key][$slider_type] = $slider_value;
      }
    }
  }

	// returns 
  if ($key && $slider) {
    return !empty($sliders[$slider][$key]) ? $sliders[$slider][$key] : NULL;
  }
  elseif ($key) {
    return !empty($slider_by_key[$key]) ? $slider_by_key[$key] : array();
  }
  elseif ($slider) {
    return $sliders[$slider];
  }
  return $sliders;
}

/**
 * get slider settings
 * 
 */
function get_slider_info($type, $key = null, $prop = '#settings') {
	
	$settings = get_sliders_info($type, $prop);
	if (empty($settings)) {
		return false;
	}
	if (!empty($key) && isset($settings[$key])) {
		return $settings[$key];
	}
	return $settings;
}

/**
 * get slider types array
 * 
 */
function get_slider_types($type = null, $reset = false) {
	$types = &drupal_static(__FUNCTION__, array());
	if (empty($types) || $reset == true) {
		$types = array();
		foreach (get_sliders_info() as $sid => $info) {
			$types[$sid] = t($info['#title']);
		}
	}
	
	return !empty($type) && isset($types[$type]) ? $types[$type] : $types;
}

/**
 * Get all available sliders
 */
function get_all_sliders() {
	$cache = &drupal_static(__FUNCTION__, NULL);
	if (!isset($cache)) {
		acquia_include('slider', 'ac_slider');
		$cache = acquiaSlider::get_all();
	}

	return $cache;
}

/**
 * Get all sliders by slider type
 */
function get_sliders_by_type($type) {
	$cache = &drupal_static(__FUNCTION__, NULL);
	
	if (!isset($cache)) {
		
		$cache = array();
		foreach (get_all_sliders() as $slider) {
			if ($slider->type != $type) {
				continue;
			}
			$cache[$slider->slid] = t($slider->title);
		}
	}

	return $cache;
}

/**
 * get_sliders_by_id
 */
function get_sliders_by_id() {
	$cache = &drupal_static(__FUNCTION__, NULL);
	
	if (!isset($cache)) {
		
		$cache = array();
		foreach (get_all_sliders() as $slider) {
			$cache[$slider->slid] = t($slider->title);
		}
	}

	return $cache;
}