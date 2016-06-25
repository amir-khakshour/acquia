<?php

/**
 * @file
 *
 */

@define(CHECK_LENGTH, 1);

/**
 * Get list of enabled animation.css library animation types
 */
function acquia_animate_get_anim_list() {
  $cache = &drupal_static(__FUNCTION__);

  if (!isset($cache)) {
		$cid = 'acquia:anim_list';
		
		if (!$cache = cache_get($cid)) {
			$path = acquia_variable_get('libs_path', 'sites/all/libraries') . '/animate.css/source';
			$cache = array();
			foreach (file_scan_directory($path, '/(\.css)$/', array('key' => 'name')) as $name => $file) {
				$cache[$name] = $name;
			}
			cache_set($cid, $cache);
		}else {
			$cache = $cache->data;
		}
	
  }

	return $cache;
}

/**
 * Making a HTML class attributes from given array
 * @todo add documentation
 * @param {array} $args
 * @param {array} $vals
 * @param {const} $flags
 * @param {string} $const
 */
function acquia_get_class_by_args($args, $vals, $flags = NULL, $prefix = NULL, $const = 'ac'){
	$out = array();
	if (!empty($prefix)) {
		$prefix .= '-';
	}
	foreach($args as $arg) {
		$value = isset($vals[$arg]) ? trim($vals[$arg]) : '';
		if ($flags & CHECK_LENGTH && empty($value)) {
			continue;
		}
		$value = explode(' ', $value);
		foreach ($value as $val) {
			$out[] = $const .'-' .$prefix .$arg .'-' .$val;
		}
	}
	return implode(' ', $out);
}

/**
 * Making a HTML data attributes of animation info from given array
 * @todo add documentation
 */
function acquia_get_anim_data_by_attrs($attrs, $list = FALSE, $data_const = 'anim', $prefix = ''){
 $anim_opts = array('animate' => 'type', 'when' => 'when', 'delay' => 'delay', 'where' => 'where', 'childs' => 'childs');
 if ($list == TRUE && !isset($attrs['childs'])) {
	 $attrs[$prefix . 'childs'] = 'anim-item';
 }
 
 $data = array();
 foreach($anim_opts as $attr_key => $map){
	if (isset($attrs[$prefix . $attr_key])) {
		$data[$data_const .'-'. $map] = $attrs[$prefix . $attr_key];
	}
 }
 return acquia_data_arr_to_tag_arr($data); 
}

/**
 * Making a HTML data attributes of Tooltip info from given array
 * @todo add documentation
 */
function acquia_get_tooltip_data_by_attrs($attrs, $prefix = ''){
 $anim_opts = array('info' => 'toggle', 'info_place' => 'placement', 'info_trigger' => 'trigger', 'info_content' => 'content', 'info_title' => 'original-title');

 $attrs['info'] = isset($attrs['info']) ? $attrs['info'] : 'tooltip';
 
 $data = array();
 foreach($anim_opts as $attr_key => $map){
	if (isset($attrs[$prefix . $attr_key])) {
		$data[$map] = $attrs[$prefix . $attr_key];
	}
 }
 
 return acquia_data_arr_to_tag_arr($data); 
}

/**
 * makes styles string from given styles array
 */
function acquia_style_arr_to_tag(&$styles) {

	$string_vals_prop = array(
		
	);
	
	$out = array();
	$styles = array_filter($styles, 'strlen');
	foreach($styles as $prop => $value) {
		if (in_array($prop, $string_vals_prop)) {
			$value = '"' . $value . '"';
		}
		$out[] = $prop .':' .$value;
	}
	
	return implode('; ', $out);
}

/**
 * Converts array of key => value to data-key => value to be placed into HTML tag
 */
function acquia_data_arr_to_tag_arr($data) {
	
	$out = array();
	$data = array_filter($data, 'strlen');
	foreach($data as $prop => $value) {
		$out["data-" . $prop] = $value;
	}
	
	return $out;

}
