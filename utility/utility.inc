<?php
/**
 * @file
 * Contains general utility functions for acquia that do not need to be
 * in the module file.
 *
 */

/**
 * Helper function to get array of addded library CSS/JS files from acquia_load_resources()
 * @param $type
 *		type of resources to load
 */
function acquia_ajax_get_resources($type){

	$old_css = drupal_add_css();
	$old_js = drupal_add_js();
	// loading required lib resources
	acquia_load_resources($type);

	$new_css = drupal_add_css();
	$new_js = drupal_add_js();

	return array(
		'css' => array_diff_key($new_css, $old_css),
		'js' => array_diff_key($new_js, $old_js),
	);
}

/**
 * makes the drupal version of "__" wordpress function.
 */
function acquia_class_arr_to_string($classes) {
	if (is_array($classes)) {
		$class = array();
		foreach ($classes as $class) {
			$class[] = '';
		}
	}
}

/**
 * Helper function for discovering shortcodes, shortcodes or other plugins of any
 * sort in the module trail.
 *
 * @param $type
 *   An extension type (e.g. shortcode or layout).
 * @param $theme
 *   (Optional) The key (machine-readable name) of a theme. Defaults to the key
 *   of the current theme.
 *
 * @return array
 *   An array containing the discovered definitions.
 */
function acquia_discovery($type, $path, $hook = 'info') {
	if (($discovery = &drupal_static(__FUNCTION__, array())) && isset($discovery[$path][$type])) {
		return $discovery[$path][$type];
	}

	$discovery[$path][$type] = array();
	$strlen = strlen($type) + 1;
	// Support files without '.inc' extension for backwards compatibility.
	foreach (file_scan_directory($path, '/\.' . $type . '(\.inc)?$/', array('key' => 'name')) as $name => $file) {
		$info = array();

		if (substr($name, -$strlen) === '.' . $type) {
			$name = substr($name, 0, strlen($name) - $strlen);
		}

		require_once $file->uri;
		if (function_exists($name .'_'. $hook)) {
			$info = call_user_func($name .'_'. $hook);
		}

		if ($info) {
			$discovery[$path][$type][$name]= array(
				'path' => dirname($file->uri),
				'file' => $file->filename,
				$hook => $info,
			);
		}

	}

	return $discovery[$path][$type];
}


/**
 * Get list of supported CSS animations
 * @param $css_file
 * 	A string representing animate.css file
 *
 * @param $reset
 * 	A boolean to reset the cache
 */
function acquia_css_animate_extract_animation($css_file = 'animate-custom.css', $reset = false) {
	$cache = &drupal_static(__FUNCTION__);

	if ($reset || !isset($cache)) {
		$cid = 'acquia:cssanimates:' . str_replace('.', '-', $css_file);

		if ($reset || !$cache = cache_get($cid)) {

			$dir = acquia_variable_get('animate_css_path');
			if ($contents = @file_get_contents($dir . '/' . $css_file)) {
				preg_match_all('/animation-name:\s?([^;}]*);?/i', $contents, $matches);
				if (isset($matches[1]) && !empty($matches[1])) {
					$cache = array_values(array_unique($matches[1]));
				}
			}
			cache_set($cid, $cache);
		}else {
			$cache = $cache->data;
		}

	}

	return $cache;
}

/**
 * Get list of enabled format for current user
 */
function user_enabled_filter_formats($uid = null){
	$user_formats = &drupal_static(__FUNCTION__);

	if (isset($uid) && is_numeric($uid)) {
		$user = user_load($uid);
	}else {
		global $user;
	}

	if (!isset($user_formats[$user->uid])) {

		$formats = array();
		// Get a list of formats that the current user has access to.
		foreach (filter_formats($user) as $format) {
			$formats[$format->format] = $format->name;
		}

		$user_formats[$user->uid] = $formats;
	}

	return $user_formats[$user->uid];
}

/**
 * Helper function to decide the given param is a bool value
 *
 * @param mixed $var
 *
 * @return bool
 */
function acquia_bool($var) {
	switch (strtolower($var)) {
		case FALSE:
		case 'false':
		case 'no':
		case '0':
			$res = FALSE;
			break;
		default:
			$res = TRUE;
			break;
	}

	return $res;
}

/**
 * Helper function to push one array elements into another and return the combined array
 *
 * @param {array} $stack
 *
 * @param {array} $elements
 *
 * @return {array} $stack
 */
function acquia_arr_push_copy($stack = array(), $elements = array()) {
	foreach ($elements as $el){
		$stack[] = $el;
	}
	return $stack;
}

/**
 * Merge user defined arguments into defaults array.
 *
 * This function is used throughout WordPress to allow for both string or array
 * to be merged into another array.
 *
 * @since 2.2.0
 *
 * @param string|array $args Value to merge with $defaults
 * @param array $defaults Array that serves as the defaults.
 * @return array Merged user defined values with defaults.
 */
function acquia_parse_args( $args, $defaults = '' ) {
	if ( is_object( $args ) )
		$r = get_object_vars( $args );
	elseif ( is_array( $args ) )
		$r =& $args;
	else
		acquia_parse_str( $args, $r );

	if ( is_array( $defaults ) )
		return array_merge( $defaults, $r );
	return $r;
}

/**
 * Parses a string into variables to be stored in an array.
 *
 * Uses {@link http://www.php.net/parse_str parse_str()} and stripslashes if
 * {@link http://www.php.net/magic_quotes magic_quotes_gpc} is on.
 *
 * @param string $string The string to be parsed.
 * @param array $array Variables will be stored in this array.
 */
function acquia_parse_str( $string, &$array ) {
	parse_str( $string, $array );
	if ( get_magic_quotes_gpc() )
		$array = stripslashes_deep( $array );
}

/**
 * Generates a random and unique id accepting a prefix
 *
 * @param string $prefix The prefix string
 */
function acquia_get_unique_id( $prefix = '') {
	//set the random id length 
	$random_id_length = 10;
	//generate a random id encrypt it and store it in $rnd_id 
	$rnd_id = crypt(uniqid(rand(),1));
	//to remove any slashes that might have come 
	$rnd_id = strip_tags(stripslashes($rnd_id));
	//Removing any . or / and reversing the string 
	$rnd_id = str_replace(".","",$rnd_id);
	$rnd_id = strrev(str_replace("/","",$rnd_id));
	//finally I take the first 10 characters from the $rnd_id 
	$rnd_id = substr($rnd_id,0,$random_id_length);

	$rnd_id = !empty($prefix) ? $prefix.'-'.$rnd_id : $rnd_id;

	return $rnd_id;
}

/**
 * @TODO Document Here.
 */
function acquia_add_tooltip_libs_by_type($type ='tooltip') {
	drupal_add_library('acquia', 'bootstrap-tooltip');
	if ($type == 'popover') {
		drupal_add_library('acquia', 'bootstrap-popover');
	}
}

/**
 * @TODO Document Here.
 */
function acquia_node_sibling($dir = 'next', $node, $next_node_text=NULL, $prepend_text=NULL, $append_text=NULL, $tid = FALSE){
	if($tid){
		$query = 'SELECT n.nid, n.title FROM {node} n INNER JOIN {term_node} tn ON n.nid=tn.nid WHERE '
			. 'n.nid ' . ($dir == 'prev' ? '<' : '>') . ' :nid AND n.type = :type AND n.status=1 '
			. 'AND tn.tid = :tid ORDER BY n.nid ' . ($dir == 'prev' ? 'DESC' : 'ASC');
		$result = db_query($query, array(':nid' => $node->nid, ':type' => $node->type, ':tid' => $tid))->fetch();
	}else{
		$query = 'SELECT n.nid, n.title FROM {node} n WHERE '
			. 'n.nid ' . ($dir == 'prev' ? '<' : '>') . ' :nid AND n.type = :type AND n.status=1 '
			. 'ORDER BY n.nid ' . ($dir == 'prev' ? 'DESC' : 'ASC');
		$result = db_query($query, array(':nid' => $node->nid, ':type' => $node->type))->fetch();
	}

	if($result){
		$text = $next_node_text ? $next_node_text : $result->title;
		$icon = $dir == 'next' ? 'icon-right-open-big' : 'icon-left-open-big';
		return $prepend_text .
		l('<span>'.$text.'</span><i class="'.$icon.'"></i>', 'node/'.$result->nid,
			array(
				'html' => TRUE,
				'rel' => $dir,
				'attributes' => array('class' => array('ac-'.$dir), 'title' => $text)
			)) . $append_text;
	}else{
		return NULL;
	}
}

/**
 * Builds acquia button
 *
 */
function acquia_button($vars){
	$out = '';

	$label = isset($vars['label']) && !empty($vars['label']) ? t($vars['label']) : t('Click me');

	if (module_exists('ac_shortcode')) {
		acquia_include('utility', 'ac_shortcode');
		$tag = 'ac_button'; // button shortcode
		$tag_info = ac_shortcode_get_sc_info($tag);
		ac_shortcode_add_sc_files($tag_info);
		if (isset($tag_info['process callback']) && function_exists($tag_info['process callback'])){
			$out = call_user_func($tag_info['process callback'], $vars, $label, $tag);
		}
	}else{
		$out = l($label, $vars['link'],
			array('html' => TRUE,
				'absolute' => TRUE,
				'attributes' => array('class' => 'ac-button', 'ac-proj-link')));
	}

	return $out;
}

/**
 * Helper that generates a machine name using a provided human readable name.
 *
 * @param string $human_name
 *   Human readable name.
 *
 * @return string
 *   Machine name cleaned-up of any special chars.
 */
function machine_name($input) {
	return strtolower(preg_replace(array(
		'/[^a-zA-Z0-9]+/',
		'/-+/',
		'/^-+/',
		'/-+$/',
	), array('-', '-', '', ''), $input));
}

/**
 * Converts value to nonnegative integer.
 *
 * @since 2.5.0
 *
 * @param mixed $maybeint Data you wish to have converted to a nonnegative integer
 * @return int An nonnegative integer
 */
function absint( $maybeint ) {
	return abs( intval( $maybeint ) );
}

/**
 *
 */
function acquia_render_cid_parts($granularity = NULL) {
	global $base_root, $user;

	$cid_parts[] = variable_get('theme_default');
	// If Locale is enabled but we have only one language we do not need it as cid
	// part.
	if (drupal_multilingual()) {
		foreach (language_types_configurable() as $language_type) {
			$cid_parts[] = $GLOBALS[$language_type]->language;
		}
	}

	if (!empty($granularity)) {
		// 'PER_ROLE' and 'PER_USER' are mutually exclusive. 'PER_USER' can be a
		// resource drag for sites with many users, so when a module is being
		// equivocal, we favor the less expensive 'PER_ROLE' pattern.
		if ($granularity & DRUPAL_CACHE_PER_ROLE) {
			$cid_parts[] = 'r.' . implode(',', array_keys($user->roles));
		}
		elseif ($granularity & DRUPAL_CACHE_PER_USER) {
			$cid_parts[] = "u.$user->uid";
		}

		if ($granularity & DRUPAL_CACHE_PER_PAGE) {
			$cid_parts[] = $base_root . request_uri();
		}
	}

	return $cid_parts;
}


function ac_gen_cid($data, $extra=''){
	$prefix = 'ac_cid';
	$cid = '';
	if (is_array($data)){
		$cid = md5(serialize($data));
	}
	if (!empty($extra)) {
		$cid .= md5($extra);
	}
	return sprintf('%s::%s', $prefix, $cid);
}


function ac_register_theme(){
	// DiamondLayers enabled theme & version
	$theme = variable_get('ACQUIA_BASE_THEME', 'AURA');
	$version = variable_get('ACQUIA_THEME_VERSION', '1.1.7');

	$ch = curl_init();
	$url = sprintf('http://endpoint.diamondlayers.com/endpoint?theme=%s;version=%s', $theme, $version);
	curl_setopt($ch,CURLOPT_URL,$url);
	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
	curl_exec($ch);
	curl_close($ch);
}