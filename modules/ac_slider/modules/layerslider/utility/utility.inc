<?php
if(!defined('TAB')) {
	define("TAB", "\t");
}
if(!defined('NL')) {
	define("NL", "\r\n");
}

function apply_filters($function) {
	if (function_exists($function)) {
		$args = func_get_args();
		array_shift($args);
		return call_user_func_array($function, (array)$args);
	}
}

function ls_get_image($fid) {
	if (is_numeric($fid)&& $fid !=0) {
		$file = file_load((int)$fid);
		return isset($file->uri) ? file_create_url($file->uri) : '';
	}
	return '';
}
/*
 * This function loads the required JavaScripts and settings for a layerslider
 * instance.
 *
 * @param string $id [optional]
 *  ID Attribute for acquia_revolution_slider container
 * @param object|strong $settings [optional]
 *  Settings to load or the machine name of an existing profile 
 */

function layerslider_add_js($id = NULL, $properties = NULL) {

  // If the ID or profile aren't set, it is assumed the settings will be set
  // manually via the calling module/theme
  if (!empty($id) && !empty($properties)) {
    // JavaScript settings
    $js_settings = array(
      'instances' => array(
        $id => layerslider_process_js_properties($properties),
      ),
    );
    // @todo add alter hook for profile
    drupal_add_js(array('acquiaLayerSlider' => $js_settings), 'setting');
  }

  // Loader JavaScript
  drupal_add_js(drupal_get_path('module', 'layerslider') . '/js/layerslider.load.js', array('type' => 'file', 'scope' => 'footer'));
}

function layerslider_render_js($id, $slides = array()) {
  if (is_array($slides)) {
  $data = '';
  // $data .= NL . '<script type="text/javascript">' . NL;
    $data .= TAB . 'jQuery(document).ready(function() { ' . NL;

    $data .= TAB . TAB . 'jQuery("#' . $id . '").layerSlider({ ' . NL;
    $data .= TAB . TAB . TAB . 'width : \'' . ac_check_unit($slides['properties']['width']) . '\',' . NL;
    $data .= TAB . TAB . TAB . 'height : \'' . ac_check_unit($slides['properties']['height']) . '\',' . NL;
    $data .= TAB . TAB . TAB . 'responsive : ';
    $data .= isset($slides['properties']['responsive']) ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'responsiveUnder : ';
    $data .=!empty($slides['properties']['responsiveunder']) ? $slides['properties']['responsiveunder'] : '0';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'sublayerContainer : ';
    $data .=!empty($slides['properties']['sublayercontainer']) ? $slides['properties']['sublayercontainer'] : '0';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'autoStart : ';
    $data .= ( isset($slides['properties']['autostart']) && $slides['properties']['autostart'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'pauseOnHover : ';
    $data .= ( isset($slides['properties']['pauseonhover']) && $slides['properties']['pauseonhover'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'firstLayer : ';
    $data .= is_numeric($slides['properties']['firstlayer']) ? $slides['properties']['firstlayer'] : '\'random\'';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'animateFirstLayer : ';
    $data .= ( isset($slides['properties']['animatefirstlayer']) && $slides['properties']['animatefirstlayer'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'randomSlideshow : ';
    $data .= ( isset($slides['properties']['randomslideshow']) && $slides['properties']['randomslideshow'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'twoWaySlideshow : ';
    $data .= ( isset($slides['properties']['twowayslideshow']) && $slides['properties']['twowayslideshow'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'keybNav : ';
    $data .= ( isset($slides['properties']['keybnav']) && $slides['properties']['keybnav'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'touchNav : ';
    $data .= ( isset($slides['properties']['touchnav']) && $slides['properties']['touchnav'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'imgPreload : ';
    $data .= ( isset($slides['properties']['imgpreload']) && $slides['properties']['imgpreload'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'navPrevNext : ';
    $data .= ( isset($slides['properties']['navprevnext']) && $slides['properties']['navprevnext'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'navStartStop : ';
    $data .= ( isset($slides['properties']['navstartstop']) && $slides['properties']['navstartstop'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'navButtons : ';
    $data .= ( isset($slides['properties']['navbuttons']) && $slides['properties']['navbuttons'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'hoverPrevNext : ';
    $data .= ( isset($slides['properties']['hoverprevnext']) && $slides['properties']['hoverprevnext'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'hoverBottomNav : ';
    $data .= ( isset($slides['properties']['hoverbottomnav']) && $slides['properties']['hoverbottomnav'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'showBarTimer : ';
    $data .=!empty($slides['properties']['bartimer']) && $slides['properties']['bartimer'] == 'on' ? 'true' : 'false';
    $data .= ',' . NL;
		$data .= TAB . TAB . TAB . 'showCircleTimer : ';
    $data .=!empty($slides['properties']['circletimer']) && $slides['properties']['circletimer'] == 'on' ? 'true' : 'false';
    $data .= ',' . NL;
		$data .= TAB . TAB . TAB . 'thumbnailNavigation : \'';
    $data .=!empty($slides['properties']['thumb_nav']) ? $slides['properties']['thumb_nav'] : 'hover';
    $data .= '\',' . NL;
    $data .= TAB . TAB . TAB . 'tnWidth : ';
    $data .=!empty($slides['properties']['thumb_width']) ? $slides['properties']['thumb_width'] : '100';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'tnHeight : ';
    $data .=!empty($slides['properties']['thumb_height']) ? $slides['properties']['thumb_height'] : '60';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'tnContainerWidth : \'';
    $data .=!empty($slides['properties']['thumb_container_width']) ? $slides['properties']['thumb_container_width'] : '60%';
    $data .= '\',' . NL;
    $data .= TAB . TAB . TAB . 'tnActiveOpacity : ';
    $data .=!empty($slides['properties']['thumb_active_opacity']) ? $slides['properties']['thumb_active_opacity'] : '35';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'tnInactiveOpacity : ';
    $data .=!empty($slides['properties']['thumb_inactive_opacity']) ? $slides['properties']['thumb_inactive_opacity'] : '100';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'skin : \'';
    $data .= $slides['properties']['skin'];
    $data .= '\',' . NL;
    $data .= TAB . TAB . TAB . 'skinsPath : \'';
    $data .= url(LAYERSLIDER_SKIN_PATH, array('absolute' => TRUE));
    $data .= '\',' . NL;

    if (!empty($slides['properties']['backgroundcolor'])) :
      $data .= TAB . TAB . TAB . 'globalBGColor : \'';
      $data .= $slides['properties']['backgroundcolor'];
      $data .= '\',' . NL;
    endif;
    if (!empty($slides['properties']['backgroundimage'])) :
      $data .= TAB . TAB . TAB . 'globalBGImage : \'';
      $data .=!empty($slides['properties']['backgroundimage']) ? '\'' . $slides['properties']['backgroundimage'] . '\'' : 'false';
      $data .= '\',' . NL;
    endif;

    $data .= TAB . TAB . TAB . 'yourLogo : ';
    $data .=!empty($slides['properties']['yourlogo']) ? '\'' . $slides['properties']['yourlogo'] . '\'' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'yourLogoStyle : ';
    $data .=!empty($slides['properties']['yourlogostyle']) ? '\'' . $slides['properties']['yourlogostyle'] . '\'' : '\'position: absolute; left: 10px; top: 10px; z-index: 99;\'';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'yourLogoLink : ';
    $data .=!empty($slides['properties']['yourlogolink']) ? '\'' . $slides['properties']['yourlogolink'] . '\'' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'yourLogoTarget : ';
    $data .=!empty($slides['properties']['yourlogotarget']) ? '\'' . $slides['properties']['yourlogotarget'] . '\'' : '\'_self\'';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'loops : ';
    $data .=!empty($slides['properties']['loops']) ? $slides['properties']['loops'] : 0;
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'forceLoopNum : ';
    $data .= ( isset($slides['properties']['forceloopnum']) && $slides['properties']['forceloopnum'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'autoPlayVideos : ';
    $data .= ( isset($slides['properties']['autoplayvideos']) && $slides['properties']['autoplayvideos'] != 'false') ? 'true' : 'false';
    $data .= ',' . NL;


    $autoPauseSlideshow = !empty($slides['properties']['autopauseslideshow']) ? $slides['properties']['autopauseslideshow'] : 'auto';

    if ($autoPauseSlideshow == 'auto') {
      $autoPauseSlideshow = '\'auto\'';
    } else if ($autoPauseSlideshow == 'enabled') {
      $autoPauseSlideshow = 'true';
    } else if ($autoPauseSlideshow == 'disabled') {
      $autoPauseSlideshow = 'false';
    }

    $data .= TAB . TAB . TAB . 'autoPauseSlideshow : ';
    $data .= $autoPauseSlideshow;
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'youtubePreview : ';
    $data .=!empty($slides['properties']['youtubepreview']) ? '\'' . $slides['properties']['youtubepreview'] . '\'' : '\'maxresdefault.jpg\'';
    $data .= ',' . NL;

    $data .= TAB . TAB . TAB . 'cbInit : ';
    $data .=!empty($slides['properties']['cbinit']) ? stripslashes($slides['properties']['cbinit']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbStart : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbstart']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbStop : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbstop']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbPause : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbpause']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbAnimStart : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbanimstart']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbAnimStop : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbanimstop']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbPrev : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbprev']) : 'function() {}';
    $data .= ',' . NL;
    $data .= TAB . TAB . TAB . 'cbNext : ';
    $data .=!empty($slides['properties']['cbstart']) ? stripslashes($slides['properties']['cbnext']) : 'function() {}';
    $data .= NL;
    $data .= TAB . TAB . '});' . NL;
    $data .= TAB . '});' . NL;
    //$data .= '</script>' . NL;
    
    drupal_add_js($data, 'inline');
  }
}


/**
 * Load resource
 */
function layerslider_load_resources($section = 'slider') {
	switch($section) {
	
		default:
		case 'slider':
			drupal_add_library('acquia', 'jquery-easing');
			drupal_add_library('layerslider', 'layerslider');
			break;	
		
		case 'admin_slider':
			include_once drupal_get_path('module', 'media') . '/wysiwyg_plugins/media.inc';
			media_include_browser_js();
			
			drupal_add_library('system', 'ui');
			drupal_add_library('system', 'farbtastic');
			drupal_add_library('system', 'ui.slider');
			drupal_add_library('system', 'ui.sortable');
			drupal_add_library('system', 'ui.draggable');
			drupal_add_library('acquia', 'jquery-easing');
			drupal_add_library('layerslider', 'layerslider.admin');
			
			$path = drupal_get_path('module', 'layerslider');
			//drupal_add_js(drupal_get_path('module', 'ac_slider') . '/js/acquia-admin.js');
			//drupal_add_css(drupal_get_path('module', 'ac_slider') . '/css/acquia-admin.css');
			drupal_add_css($path . '/css/custom.css');
			drupal_add_js($path . '/js/admin.js');

			break;
			
	}
}

/**
 * Returns list of Layer Slider skins
 */
function layerslider_get_skins_options($reset = false) {
	$options = &drupal_static(__FUNCTION__, array());
	if (count($options) < 1 || $reset == true) {
		$options = array_combine(array_keys(layerslider_get_skins($reset)), array_keys(layerslider_get_skins($reset)));
	}
	return $options;
}

/**
 * Returns list of Layer Slider skins
 */
function layerslider_get_skins($reset = false) {
	$skins = &drupal_static(__FUNCTION__);

	if (!isset($skins) && !$reset) {
		$skins = array();

		$skins_path = LAYERSLIDER_SKIN_PATH;
		if(is_dir($skins_path)) {
			$skins = file_scan_directory($skins_path, '/\.(css)$/i');
		}
		
		$_skins = array();
		asort($skins);
		foreach ($skins as $id => $skin) {
			$id = explode('/', $id);
			array_pop($id);
			$_id = array_pop($id);
			$_skins[$_id] = array('name' => $_id,'path' => implode('/', $id));
		}
		$skins = $_skins;
	}
	
	return $skins;
}

/**
 *
 */
function lsGetSkins() {

	// Get skins
	$skins = array_map('basename', glob(LS_ROOT_PATH.'/static/skins/*', GLOB_ONLYDIR));

	// Get 3rd party skins
	// ...

	// Get info
	foreach($skins as $key => $skin) {

		// Get the folder and name for fallback
		$ret[$key]['folder'] = $ret[$key]['name'] = $skin;

		// Get screenshot if any
		if(file_exists(LS_ROOT_PATH.'/static/skins/'.$skin.'/screenshot.jpg')) {
			$ret[$key]['screenshot'] = LS_ROOT_PATH.'/static/skins/'.$skin.'/screenshot.jpg';
		}

		// Get skin info if any
		if(file_exists(LS_ROOT_PATH.'/static/skins/'.$skin.'/info.json')) {

			// Get info
			$ret[$key]['info'] = json_decode(file_get_contents(LS_ROOT_PATH.'/static/skins/'.$skin.'/info.json'), true);

			// Override name
			$ret[$key]['name'] = $ret[$key]['info']['name'];
		}
	}

	return $ret;
}


function ls_get_thumbnail($id = null, $url = null) {
	// Image ID image_style_url($variables["lightbox_style"],  $item['uri']);
	if(!empty($id)) {
		if($image = image_style_url('ls-thumb', file_load($id)->uri)) {
			return $image;
		}
	} 

	if(!empty($url)) {
		return $url;
	}
	return acquia_variable_get('layerslider_root').'/static/img/not_set.png';
}


function ls_parse_defaults($defaults = array(), $raw = array()) {

	$ret = array();
	foreach($defaults as $key => $default) {
		$phpKey = is_string($default['keys']) ? $default['keys'] : $default['keys'][0];
		$jsKey  = is_string($default['keys']) ? $default['keys'] : $default['keys'][1];
		$retKey = isset($default['props']['meta']) ? 'props' : 'attrs';

		if(isset($raw[$phpKey]) && is_array($raw[$phpKey])) {
			$ret[$retKey][$jsKey] = $raw[$phpKey];
		} elseif(is_bool($default['value'])) {
			if($default['value'] == true && empty($raw[$phpKey])) {
				$ret[$retKey][$jsKey] = false;
			} elseif($default['value'] == false && !empty($raw[$phpKey])) {
				$ret[$retKey][$jsKey] = true;
			}
		} elseif(isset($raw[$phpKey])) {
			if(isset($default['props']['meta']) || $default['value'] != $raw[$phpKey]) {
				$ret[$retKey][$jsKey] = is_numeric($raw[$phpKey]) ? (float) $raw[$phpKey] : stripslashes($raw[$phpKey]);
			}
		}
	}

	return $ret;
}


function ls_array_to_attr($arr, $mode = '') {
	if(!empty($arr) && is_array($arr)) {
		$ret = array();
		foreach($arr as $key => $val) {
			if($mode == 'css' && is_numeric($val)) {
				$ret[] = ''.$key.':'.ac_check_unit($val).';';
			} elseif(is_bool($val)) {
				$bool = $val ? 'true' : 'false';
				$ret[] = "$key:$bool;";
			} else {
				$ret[] = "$key:$val;";
			}
		}
		return implode('', $ret);
	}
}
