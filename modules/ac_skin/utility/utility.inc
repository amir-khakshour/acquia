<?php
/**
 * @file
 * General utility functions for acquia Skin that do not need to be placed
 * in the module file.
 */

function ac_skin_get_skin_groups_arr(){
  $groups = &drupal_static(__FUNCTION__, NULL);

  if (!isset($groups)) {
	$groups = array_keys(ac_skin_get_theme_skin_items());
  }

  return $groups;
}


/**
 * Load given group of skin settings file
 */
function ac_skin_load_skin_group_file($group){
  $added = &drupal_static(__FUNCTION__, array());
  if (!isset($added[$group])) {
	$added[$group] = TRUE;
	$group_def = ac_skin_get_theme_skin_items();
	if (isset($group_def[$group]) && $def = $group_def[$group]){
	  if (file_exists($def['path'] .'/' .$def['file'])) {
		require_once $def['path'] .'/' .$def['file'];
	  }
	}
  }
}

/**
 * Get all skin settings array
 */
function ac_skin_get_all_group_styles($reset = FALSE) {
  $skin_settings = &drupal_static(__FUNCTION__, array());

  $settings = ac_skin_get_theme_skin_items();
  foreach($settings as $group => $def) {
	if (is_array($def)) {
	  // load group def file
	  ac_skin_load_skin_group_file($group);

	  $styles_func = $def['styles callback'];
	  if (function_exists($styles_func)) {
		$skin_settings[$group] = $styles_func();
	  }
	}
  }

  return $skin_settings;
}

/**
 * @todo
 */
function ac_skin_add_skin_assets(){
  $added = &drupal_static(__FUNCTION__, FALSE);
  if (!$added) {
	drupal_add_library('system', 'ui');
	drupal_add_library('system', 'ui.slider');
	$added = TRUE;
  }
}

/**
 * Get default value of skin attribute
 */
function ac_skin_get_skin_attr_default_val($key, $attr, $type = 'skin', $default = NULL) {

  $styles = ac_skin_get_all_group_styles();
  if (isset($styles[$key][$type][$attr]['default'])) {
	return $styles[$key][$type][$attr]['default'];
  }else{
	return $default;
  }
}

/**
 *
 */
function ac_skin_demo_box($targets = NULL) {
  $class = 'ac-font-preview';
  if ($targets != null){
	foreach($targets as $target) {
	  $class .=' ac-target-' . $target;
	}
  }

  $out  = '<div class="ac-preview-wrap" style="font-family: \'Open Sans\'; font-weight: normal">';
  $out .= '	<div class="'.$class.'">';
  $out .= '		<span>Grumpy wizards make toxic brew for the evil Queen and Jack.</span>';
  $out .= '	</div>';
  $out .= '	<strong class="label">preview</strong>';
  $out .= '</div>';

  return $out;
}

/**
 * Get skin element structure
 */
function ac_skin_get_group_styles($group) {
  $styles = ac_skin_get_all_group_styles();
  if (isset($styles[$group])) {
	return $styles[$group];
  }else{
	return array();
  }
}

/**
 * ac_skin_get_topbar_socials
 */
function ac_skin_get_topbar_socials($reset = FALSE) {
  $cache = &drupal_static(__FUNCTION__, NULL);

  if (!isset($cache) || $reset) {
	$cid = "acquia_topbar_socials";
	$cache = cache_get($cid);
	if (!$reset && $cache && isset($cache->data)) {
	  $cache = $cache->data;
	}else{
	  $cache = theme('acquia_topbar_socials', array('socials' => array_filter(acquia_theme_get_settings('social_icons', array(),  'topbar'), 'strlen')));
	  cache_set('acquia_topbar_socials', $cache);
	}
  }
  return $cache;
}

/**
 * ac_skin_get_topbar_socials
 */
function ac_skin_get_topbar_contact_info($reset = FALSE) {
  $cache = &drupal_static(__FUNCTION__, NULL);

  if (!isset($cache) || $reset) {
	$cid = 'acquia_topbar_contact_info';
	$cache = cache_get($cid);
	if (!$reset && $cache && isset($cache->data)) {
	  $cache = $cache->data;
	}else{
	  $cache = theme('acquia_topbar_contact_info', array('info' => array_filter(acquia_theme_get_settings('contact_info', array(),  'topbar'), 'strlen')));
	  cache_set('acquia_topbar_contact_info', $cache);
	}
  }
  return $cache;
}

/**
 * ac_skin_get_logo_images
 */
function ac_skin_get_logo_images($reset = FALSE) {
  $cache = &drupal_static(__FUNCTION__, NULL);

  if (!isset($cache) || $reset) {
	$cid = 'acquia_header_logos';
	$cache = cache_get($cid);
	if (!$reset && $cache && isset($cache->data)) {
	  $cache = $cache->data;
	}else{
	  $logos = '<img src="'.omega_theme_get_setting('logo').'" class="logo-base" alt="'.t('Home').'" />';
	  $settings = omega_theme_get_setting('logos');

	  if (isset($settings['logo_white']['fid']) && $settings['logo_white']['fid'] !=0) {
		$logos .= '<img src="'.file_create_url(file_load($settings['logo_white']['fid'])->uri).'" class="logo-base logo-white" alt="'.t('Home').'" />';
	  }

	  if (acquia_theme_get_settings('retina_enabled', TRUE)) {
		if (isset($settings['retina_width']) && !empty($settings['retina_width'])) {
		  $style = ' style="max-width:'.str_replace(array('px', '%'), '', $settings['retina_width']).'px"';
		}else{
		  $style = '';
		}

		if (isset($settings['retina']['fid']) && $settings['retina']['fid'] !=0) {
		  $logos .= '<img src="'.file_create_url(file_load($settings['retina']['fid'])->uri).'" class="logo-retina" alt="'.t('Home').'" '.$style.'/>';
		}

		if (isset($settings['retina_white']['fid']) && $settings['retina_white']['fid'] !=0) {
		  $logos .= '<img src="'.file_create_url(file_load($settings['retina_white']['fid'])->uri).'" class="logo-retina base-white" alt="'.t('Home').'" '.$style.'/>';
		}
	  }
	  cache_set('acquia_header_logos', $logos);
	  return $logos;
	}
  }
  return $cache;
}

/**
 * @todo
 */
function ac_skin_build_info_file($array, $prefix = FALSE) {
  $info = '';

  foreach ($array as $key => $value) {
	if (is_array($value)) {
	  $info .= ac_skin_build_info_file($value, (!$prefix ? $key : "{$prefix}[{$key}]"));
	}
	else {
	  $info .= $prefix ? ("{$prefix}[" . $key .']') : $key;
	  $info .= " = '" . str_replace("'", "\'", $value) . "'\n";
	}
  }

  return $info;
}


/**
 * @todo
 */
function ac_skin_get_absolute_image_url($src){
  // Absolute URL
  if (stripos($src, 'http://') === 0 || stripos($src, 'https://') === 0) {
	return $src;
  }
  // Drupal relative Path
  else if (stripos($src, 'public://') === 0 || stripos($src, 'private://') === 0) {
	return file_create_url($src);
  }
  // Internal DiamondLayers path
  return file_create_url(drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . $src);
}

/**
 * DiamondLayers header Types
 */
function ac_skin_styles_wrap_acquia(&$element) {

  if (!isset($element['acquia'])) {
	$element['acquia'] = array(
	  '#type' => 'container',
	  '#tree' => TRUE,
	);
  }
}


/**
 * get list of skin settings defined by modules
 */
function ac_skin_get_theme_skin_items(){
  $settings = &drupal_static(__FUNCTION__, null);
  if (!isset($settings)) {
	acquia_include('theme');
	$settings = acquia_theme_discovery('skin', variable_get('ACQUIA_BASE_THEME'), 'skin_info');
  }
  return $settings;
}

/**
 * get list of fonts supplied by modules
 */
function ac_skin_discover_theme_fonts($font = NULL){
  $settings = &drupal_static(__FUNCTION__, null);
  if (!isset($settings)) {
	acquia_include('theme');
	$settings = acquia_theme_discovery('font', variable_get('ACQUIA_BASE_THEME'), 'font_info');
  }
  if (isset($settings[$font])) {
	return $settings[$font];
  }

  return $settings;
}

function ac_skin_extract_fonts($reset = FALSE){
  $fonts = &drupal_static(__FUNCTION__, null);

  if ($reset || !isset($fonts)) {
	$cid = 'acquia:' . variable_get('ACQUIA_BASE_THEME') .':fonts';
	$cache = cache_get($cid);
	if (!$reset && $cache && isset($cache->data)) {
	  $fonts = $cache->data;
	}else{
	  foreach (ac_skin_discover_theme_fonts() as $name => $info) {
		if (!isset($info['css'])) {
		  continue;
		}
		$path = $info['path'] . '/' . $info['css'];
		if (file_exists($path)) {
		  $content = file_get_contents($path);
		  preg_match_all('/font-family\s?:\s?(.*);/i', $content, $matches);
		  if (empty($matches[1])) {
			continue;
		  }
		  foreach ($matches[1] as $font) {
			$fonts[trim(str_replace(array('\'', '"'), '', $font))] = $name;
		  }
		}
	  }
	  cache_set($cid, $fonts);
	}
  }
  return $fonts;
}

/**
 *
 */
function ac_skin_get_theme_fonts_option(){
  $theme_fonts = array_keys((array)ac_skin_extract_fonts());
  if (!empty($theme_fonts)) {
	return array_combine($theme_fonts, $theme_fonts);
  }

  return array();
}

function ac_skin_load_theme_font($font) {
  $fonts = ac_skin_extract_fonts();
  if (isset($fonts[$font])) {
	$font_info = ac_skin_discover_theme_fonts($fonts[$font]);
	drupal_add_css($font_info['path'] .'/' .$font_info['css']);
  }
}