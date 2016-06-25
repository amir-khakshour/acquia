<?php
/**
 * @file
 * Contains general utility functions for acquia shortcode that do not need to be
 * in the module file.
 *
 */

/**
 * include given shortcode defenition file 
 * @param {array} $shortcode
 * 	An array of shortcode defenition, including shortcode path and file name
 */
function ac_shortcode_add_sc_files($shortcode){
	static $used = array();
	$used = &drupal_static(__FUNCTION__, array());
	
	if (isset($used[$shortcode['path'] .'/' .$shortcode['file']])) {
		return;
	}

	$stack = array();
	// Include shortcode files that are required by given shortcode
	if (isset($shortcode['required']) && is_array($shortcode['required']) && !empty($shortcode['required'])) {
		ac_shortcode_get_required_stack($shortcode, $stack);
  }

	array_push($stack, $shortcode['tag']);
	foreach ($stack as $tag) {
		$shortcode = ac_shortcode_get_sc_info($tag);
		if (isset($shortcode['path']) && isset($shortcode['file'])) {
			require_once $shortcode['path'] .'/' .$shortcode['file'];
		}
		$used[$shortcode['path'] .'/' .$shortcode['file']] = TRUE;
	}
}

/**
 * Add required shortcodes to stack array
 */
function ac_shortcode_get_required_stack($shortcode, &$stack = array()) {
	if (isset($shortcode['required']) && is_array($shortcode['required']) && !empty($shortcode['required'])) {
    foreach ($shortcode['required'] as $tag) {
			array_unshift($stack, $tag);
			$shortcode = ac_shortcode_get_sc_info($tag);
			ac_shortcode_get_required_stack($shortcode, $stack);
		}
  }
}

/**
 * Get shortcode defenition by it's name
 * @param {string} $tag
 * 	shortcode tag key
 */
function ac_shortcode_get_sc_info($tag){
  $list = ac_shortcode_list_all();
  if (is_array($list) && in_array($tag, array_keys($list))){
    return $list[$tag];
  }
}

/**
 * Get shortcode categories
 * @param {string} $tag
 * 	shortcode tag key
 */
function ac_extract_shortcode_categories($shortcodes = array(), $reset = false){
  $categories = &drupal_static(__FUNCTION__, NULL, $reset);

	if (!isset($categories)) {
		$categories = array();
		foreach ($shortcodes as $sc_base => $el) {
			if (!isset($el['category']) || empty($el['category'])) {
				continue;
			}
			
			if (is_array($el['category'])) {
				$categories += $el['category'];
			}else {
				$categories[] = $el['category'];
			}
			
		}
	}

	return $categories;
}

/**
 * Get array of shortcode elements that has sitewide settings enabled
 */
function ac_shortcode_get_sidewide_settings($reset = false){
  $data = &drupal_static(__FUNCTION__, NULL, $reset);

  if (!isset($data)) {
    $cid = 'ac_shortcode:sitewide_settings';
    if (!$reset && ($cache = cache_get($cid)) && !empty($cache->data)) {
      $data = $cache->data;
    }
    else {
      // include Shortcodes utility
			acquia_include('utility', 'ac_shortcode');
			
			$data = array();
      $shortcodes = ac_shortcode_list_all();

			foreach($shortcodes as $tag => $shortcode) {
       
        // exclude shortcodes that don't have sitewide settings or are hidden.
				if(!isset($shortcode['sitewide settings']) || (isset($shortcode['hidden']) && $shortcode['hidden'] == true)) {
					continue;
				}
        
				ac_shortcode_add_sc_files($shortcode);
        
				if (isset($shortcode['sitewide settings']) && function_exists($shortcode['sitewide settings'])) {
					$data[$tag]['settings'] = $shortcode['sitewide settings']();
					$data[$tag]['title'] = $shortcode['title'];
					$data[$tag]['description'] = $shortcode['description'];
				}

			}
      
			cache_set($cid, $data);
    }
  }

	return $data;
}

/**
 * Helper function to do bitwise operation on an array containig 0 or zero as values
 * @param {array} $input
 * 	An array of bits
 * @param {string} $operation
 * 	A string representing a mathematical operation such as OR, AND, XOR, ...
 */
function ac_shortcode_bitwise_array($input, $operation) {
	$ops = array('OR', 'AND', 'XOR');
	$operation = strtoupper($operation);
	
	if (!in_array($operation, $ops)){
		return false;
	}
	
	// add same item
	if(count($input) == 1) {
		$input[] = $input[0];
	}
	
	$first = array_shift($input);

	switch ($operation) {
		default:
		case 'AND':
			return array_reduce($input, function($a, $b) { return $a &&  $b; }, $first);
			
		case 'OR':
			return array_reduce($input, function($a, $b) { return $a || $b; }, $first);
		case 'XOR':
			return array_reduce($input, function($a, $b) { return $a ^ $b; }, $first);
	}
}

/**
 * Load include files for shortcodes implemented by all modules.
 *
 * @param $type
 *   The type of includes to search for, can be 'shortcodes'.
 * @param $hook
 *   The hook name to invoke.
 * @param $file
 *   An optional include file name without .inc extension to limit the search to.
 *
 * @see wysiwyg_get_directories(), _wysiwyg_process_include()
 */
function ac_shortcode_load_includes($type = 'shortcodes', $hook = 'shortcode', $file = NULL) {
  // Determine implementations.
  $directories = ac_shortcode_get_directories($type);
	// built-in shortcodes
  $directories['ac_shortcode'] = drupal_get_path('module', 'ac_shortcode') . '/' . $type;
	
  $file_list = array();
  foreach ($directories as $module => $path) {
    $file_list[$module] = drupal_system_listing("/{$file}.inc\$/", $path, 'name', 0);
  }

  // Load implementations.
  $info = array();
  foreach (array_filter($file_list) as $module => $files) {
    foreach ($files as $file) {
      include_once './' . $file->uri;
      $result = _ac_shortcode_process_include($module, $module . '_' . $file->name, dirname($file->uri), $hook);
      if (is_array($result)) {
        $info = array_merge($info, $result);
      }
    }
  }
  return $info;
}

/**
 * Return a list of directories by modules implementing ac_shortcode_include_directory().
 *
 * @param $plugintype
 *   The type of a plugin; can be 'shortcodes'.
 *
 * @return
 *   An array containing module names suffixed with '_' and their defined
 *   directory.
 *
 * @see ac_shortcode_load_includes(), _ac_shortcode_process_include()
 */
function ac_shortcode_get_directories($plugintype) {
  $directories = array();
  foreach (module_implements('ac_shortcode_include_directory') as $module) {
    $result = module_invoke($module, 'ac_shortcode_include_directory', $plugintype);
    if (isset($result) && is_string($result)) {
      $directories[$module] = drupal_get_path('module', $module) . '/' . $result;
    }
  }
  return $directories;
}

/**
 * Process a single hook implementation of a wysiwyg editor.
 *
 * @param $module
 *   The module that owns the hook.
 * @param $identifier
 *   Either the module or 'wysiwyg_' . $file->name
 * @param $hook
 *   The name of the hook being invoked.
 */
function _ac_shortcode_process_include($module, $identifier, $path, $hook) {
  $function = $identifier . '_' . $hook;

  if (!function_exists($function)) {
    return NULL;
  }

  $result = $function();

  if (!isset($result) || !is_array($result)) {
    return NULL;
  }

  // Fill in defaults.
  foreach ($result as $shortcode => $properties) {
    $result[$shortcode]['module'] = $module;
    $result[$shortcode]['name'] = $shortcode;
    $result[$shortcode]['path'] = $path;
  }

  return $result;
}

/**
 * @TODO document here
 */
function ac_shortcode_list_tags() {
	$tags = &drupal_static(__FUNCTION__,  NULL);
	
	if (!isset($tags)) {
		foreach (ac_shortcode_list_all() as $tag => $info){
			$tags[] = $tag;
		}
	}
	
	return $tags;	
}

/**
 * @TODO Document Here.
 */
function ac_shortcode_css_color_hex2rgb( $_color, $raw = false ) {
    
    if( is_array($_color) ) {
        $rgb_array = array_map('intval', $_color);    
    }else {

        $color = str_replace( '#', '', trim($_color) );

        if ( count($color) < 6 ) {
            $color .= $color;
        }

        $rgb_array = sscanf($color, '%2x%2x%2x');     

        if( is_array($rgb_array) && count($rgb_array) == 3 ) {
						acquia_include('utility');
            $rgb_array = array_map('absint', $rgb_array);
        }else {
            return '';
        }
    }

    if ( !$raw ) {
        return sprintf( 'rgb(%d,%d,%d)', $rgb_array[0], $rgb_array[1], $rgb_array[2] );
    }
    return $rgb_array;
}

/**
 * @TODO Document Here.
 */
function ac_shortcode_css_color_hex2rgba( $color, $opacity = 0 ) {

    if ( !$color ) return '';

    $rgb_array = ac_shortcode_css_color_hex2rgb( $color, true );

    return sprintf( 'rgba(%d,%d,%d,%s)', $rgb_array[0], $rgb_array[1], $rgb_array[2], ac_shortcode_css_get_opacity( $opacity ) );
}

/**
 * @TODO Document Here.
 */
function ac_shortcode_css_get_opacity( $opacity = 0 ) {
	$opacity = ($opacity > 0) ? $opacity/100 : 0;
	return $opacity;
}


/**
 * @param $columns
 * @return string
 */
function ac_shortcode_col_to_width($columns){
    $col_width_arr = array(1 => '100%', 2 => 100/2 . '%', 3 => 100/3 . '%', 4 => 100/4 . '%', 5 => 100/5 . '%', 6 => 100/6 . '%');
    if (in_array($columns, array_keys($col_width_arr))) {
        return $col_width_arr[$columns];
    }
    return '100%';
}