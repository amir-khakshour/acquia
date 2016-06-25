<?php
/**
 * @file
 * Contains general utility functions for acquia composer module that do not need to be
 * in the module file.
 *
 */

/**
 * Get Composer info of given shortcode
 * @param {string} $tag
 * 	shortcode tag key
 */
function get_sc_composer_info($tag){
	// add required libe
	acquia_include('files', 'ac_composer');
	
  $list = collect_builder_shortcodes();
  if (is_array($list) && isset($list[$tag])){
    return $list[$tag];
  }
}

/**
 * include given shortcode defenition file 
 * @param {array} $shortcode
 * 	An array of shortcode defenition, including shortcode path and file name
 */
function ac_composer_add_sc_composer_files($composer){
	static $used = array();
	
	if (!isset($used[$composer['tag']]) &&
			isset($composer['required']) &&
			is_array($composer['required'])) {
		
		$stack = array();
		ac_composer_get_required_stack($composer, $stack);
		
		// add current tag composer file at the end of stack
		array_push($stack, $composer['tag']);
		foreach ($stack as $tag) {
			$composer = get_sc_composer_info($tag);
			if (isset($composer['path']) && isset($composer['file'])) {
				require_once $composer['path'] .'/' .$composer['file'];
				$used[$composer['tag']][] = $composer['path'] .'/' .$composer['file'];
			}
		}
	}else if (isset($composer['path']) && isset($composer['file'])) {
		require_once $composer['path'] .'/' .$composer['file'];
		$used[$composer['tag']][] = $composer['path'] .'/' .$composer['file'];
	}
	
	return $used[$composer['tag']];
}

/**
 * Add required shortcodes to stack array
 * @param {array} $composer
 * 		An array of shortcode composer settings
 * @param {array} $stack
 * 		A reference to the stack of required shortcodes for a given shortcode
 */
function ac_composer_get_required_stack($composer, &$stack = array()) {
	if (isset($composer['required']) && is_array($composer['required']) && !empty($composer['required'])) {
		
		foreach ($composer['required'] as $tag) {
			array_unshift($stack, $tag);
			$_composer = get_sc_composer_info($tag);
			ac_composer_get_required_stack($_composer, $stack);
		}
		
  }
}

/**
 * @TODO Document here
 */
//function db_translateColumnWidthToFractional($width) {
function db_class_to_col_size($class) {
  switch ( $class ) {
    case "vc_span2" :
      $w = "1/6";
      break;    
    case "vc_span3" :
      $w = "1/4";
      break;    
    case "vc_span4" :
      $w = "1/3";
      break;    
    case "vc_span6" :
      $w = "1/2";
      break;
    case "vc_span8" :
      $w = "2/3";
      break;    
    case "vc_span9" :
      $w = "3/4";
      break;    
    case "vc_span12" :
      $w = "1/1";
      break;    

    default :
      $w = $class;
  }
  return $w;
}

/**
 * @TODO Document here
 */
//function db_translateColumnsCountToSpanClass($grid_columns_count) {
function ac_composer_col_count_to_class($grid_columns_count) {
  $teaser_width = '';
  switch ($grid_columns_count) {
    case '1' :
      $teaser_width = 'vc_span12';
      break;
    case '2' :
      $teaser_width = 'vc_span6';
      break;
    case '3' :
      $teaser_width = 'vc_span4';
      break;
    case '4' :
      $teaser_width = 'vc_span3';
      break;
    case '5':
      $teaser_width = 'vc_span10';
      break;
    case '6' :
      $teaser_width = 'vc_span2';
      break;
  }
  //return $teaser_width;
  $custom = ac_composer_custom_col_class($teaser_width);
  return $custom ? $custom : $teaser_width;
}

/**
 * @TODO Document here
 */
function ac_composer_custom_col_class($class) {
	// @TODO move to UI
	$custom_array = (array)acquia_variable_get('column_css_classes', array());
	return !empty($custom_array[$class]) ? $custom_array[$class] : '';
}


/**
 * @TODO Document here
 */
//function db_vc_get_column_width_indent($width) {
function ac_composer_col_width_indent($width) {
	$identy = '11';
	if($width=='vc_span6') {
			$identy = '12';
	} elseif($width=='vc_span3') {
			$identy = '14';
	} elseif($width=='vc_span4') {
			$identy = '13';
	} elseif($width=='vc_span8') {
			$identy='23';
	} elseif($width=='vc_span2') {
			$identy='16';
	} elseif($width=='vc_span9') {
			$identy='34';
	}elseif($width=='vc_span2') {
			$identy='16';
	} elseif($width=='vc_span10') {
			$identy='56';
	}
	return $identy;
}

/**
 * Row Layout controls
 *
 * Returns a list of predefined and alterable row layouts 
 * @return {array} $layouts
 */
function ac_composer_row_layouts() {
	$layouts = array(
    /*
     * How to count mask?
     * mask = column_count . sum of all numbers. Example layout 12_12 mask = (column count=2)(1+2+1+2=6)= 26
    */
    array('cells' => '11', 'mask' => '12', 'title' => '1/1', 'icon_class' => 'l_11'),
    array('cells' => '12_12', 'mask' => '26', 'title' => '1/2 + 1/2', 'icon_class' => 'l_12_12'),
    array('cells' => '23_13', 'mask' => '29', 'title' => '2/3 + 1/3', 'icon_class' => 'l_23_13'),
    array('cells' => '13_13_13', 'mask' => '312', 'title' => '1/3 + 1/3 + 1/3', 'icon_class' => 'l_13_13_13'),
    array('cells' => '14_14_14_14', 'mask' => '420', 'title' => '1/4 + 1/4 + 1/4 + 1/4', 'icon_class' => 'l_14_14_14_14'),
    array('cells' => '14_34', 'mask' => '212', 'title' => '1/4 + 3/4', 'icon_class' => 'l_14_34'),
    array('cells' => '14_12_14', 'mask' => '313', 'title' => '1/4 + 1/2 + 1/4', 'icon_class' => 'l_14_12_14'),
    array('cells' => '56_16', 'mask' => '218', 'title' => '5/6 + 1/6', 'icon_class' => 'l_56_16'),
    array('cells' => '16_16_16_16_16_16', 'mask' => '642', 'title' => '1/6 + 1/6 + 1/6 + 1/6 + 1/6 + 1/6', 'icon_class' => 'l_16_16_16_16_16_16'),
    array('cells' => '16_23_16', 'mask' => '319', 'title' => '1/6 + 4/6 + 1/6', 'icon_class' => 'l_16_46_16'),
    array('cells' => '16_16_16_12', 'mask' => '424', 'title' => '1/6 + 1/6 + 1/6 + 1/2', 'icon_class' => 'l_16_16_16_12')
	);
	
	drupal_alter('ac_composer_row_layouts', $layouts);
	return $layouts;
}

/**
 * Removes unwanted <p> tags
 */
function ac_composer_remove_wpautop($content) {
  $content = preg_replace( '#^<\/p>|^<br \/>|<p>$#', '', $content );
  return $content;
}