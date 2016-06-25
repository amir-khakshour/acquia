<?php
/**
 * Theme function utility
 */
@define ('ACQUIA_THEME_PATTERN_PATH',  acquia_variable_get('theme_presets') . '/patterns');
 /**
  * Get list of available patterns from an acquia theme pattern directory
  */
 function acquia_theme_get_patterns($reset = FALSE) {
	$patterns = &drupal_static(__FUNCTION__, NULL);
	
  if (!isset($patterns) || $reset) {
	  $cid = 'acquia_theme_patterns';
		$cache = cache_get($cid);
		if (!$reset && $cache && isset($cache->data)) {
      $patterns = $cache->data;
    }else{
			$patterns = array();
			if(is_dir(ACQUIA_THEME_PATTERN_PATH)) {
				$patterns = file_scan_directory(ACQUIA_THEME_PATTERN_PATH, '/\.(gif|png|jpg|jpeg)$/i');
			}
			asort($patterns);
			cache_set('acquia_theme_patterns', $patterns);
		}
	}
	return $patterns;
 }

/**
 * Generate HTML image of avilable patterns
 */
function acquia_theme_generate_pattern_list(){
	$cache = &drupal_static(__FUNCTION__, NULL);
	
	if (!isset($cache)) {
		$cache = '';
		$patterns = acquia_theme_get_patterns();
		if (!empty($patterns)){
			foreach ($patterns as $pattern) {
				$relative_path = str_replace(drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')), '', $pattern->uri);
				$cache .='<span style="background-image:url('.file_create_url($pattern->uri).')" data-uri="' .$relative_path .'" data-src="' .url($pattern->uri, array('absolute' => TRUE)) .'" class="ac-sel img-'.$pattern->name.'"><i></i></span>';
			}
		}
	}
	
	return $cache;
}


/**
 * hex 2 rgba
 */
function hex2rgba($color, $opacity = false) {
	$default = 'rgb(0,0,0)';

	//Return default if no color provided
	if(empty($color))
          return $default; 

	//Sanitize $color if "#" is provided 
        if ($color[0] == '#' ) {
        	$color = substr( $color, 1 );
        }

        //Check if color has 6 or 3 characters and get values
        if (strlen($color) == 6) {
                $hex = array( $color[0] . $color[1], $color[2] . $color[3], $color[4] . $color[5] );
        } elseif ( strlen( $color ) == 3 ) {
                $hex = array( $color[0] . $color[0], $color[1] . $color[1], $color[2] . $color[2] );
        } else {
                return $default;
        }

        //Convert hexadec to rgb
        $rgb =  array_map('hexdec', $hex);

        //Check if opacity is set(rgba or rgb)
        if($opacity){
        	if(abs($opacity) > 1)
        		$opacity /= 100;
        	$output = 'rgba('.implode(",",$rgb).','.$opacity.')';
        } else {
        	$output = 'rgb('.implode(",",$rgb).')';
        }
        //Return rgb(a) color string
        return $output;
}

/**
 *
 */
function acquia_theme_wrap_acquia_admin_style(&$form,  $settings = array()){
	
	$settings += array(
	 'logo' => TRUE,
	 'support_nav' => FALSE,
	 'vtabs' => FALSE,
	 'title' => drupal_get_title(),
	 'subtitle' => '',
	 'attributes' => array(
	   'class' => array(),
		),
	);

	if ($settings['vtabs']) {
		acquia_add_vertical_tabs_style($form);
	}
	
	$form['ac-header'] = array(
   '#markup' => acquia_theme_options_header($settings),
   '#weight' => -100,
  );
	
	$form['#suffix'] = acquia_theme_options_footer();
}

/**
 * Builds theme settings form header
 */
function acquia_theme_options_header($settings = array()){
 
	if (!is_array($settings['attributes']['class'])) {
		$settings['attributes']['class'] = explode(' ', $settings['attributes']['class']);
	}

	$settings['attributes']['class'] = array_merge(array('ac-admin', 'acquia-theme-options'), $settings['attributes']['class']);

	if ($settings['vtabs']) {
		$settings['attributes']['class'][] = 'ac-vtabs-enabled';
	}
  // fake Submit BTN
	$form = array();
	$form['submit'] = array(
		'#type' => 'submit',
    '#value' => t('Save configuration'),
		'#attributes' => array('data-target' => '#system-theme-settings', 'class' => array('fake-submit'))
	);
	
	$ac_logo_path = file_create_url(drupal_get_path('module', 'acquia') . '/images/aquiathemes.png');
	$out  = '		<div'.drupal_attributes($settings['attributes']).'>';
	$out .= '			<div id="ac-options-header" class="ac-options-header">';
	$out .= '				<div class="header-top">';
	$out .= '						<div id="js-warning" style="display: none;">Warning- This options panel will not work properly without javascript!</div>';
	
	if ($settings['logo'] == TRUE) {
		$out .= '						<a class="logo ac-cell" href="http://aquiathemes.net" title="acquiathemes"><img src="'.$ac_logo_path.'" /></a>';
	}
	
	$out .= '						<div class="info ac-cell">';
	$out .= '							<h3 class="title">'.$settings['title'].'</h3>';
	$out .= '							<span class="subtitle">'.$settings['subtitle'].'</span>';
	$out .= '						</div>';


	if ($settings['support_nav'] == TRUE) {
		$out .= '						<nav id="main-nav" class="ac-main-nav ac-cell">';
		$out .= '							<ul>';
		$out .= '								<li><a href="http://support.aquiathemes.net">'.t('Support').'</a></li>';
		$out .= '								<li><a href="http://support.aquiathemes.net/docs/'.variable_get('ACQUIA_BASE_THEME').'">'.t('Docuementation').'</a></li>';
		$out .= '								<li><a href="http://support.aquiathemes.net/changelog/'.variable_get('ACQUIA_BASE_THEME').'">'.t('Changelog').'</a></li>';
		$out .= '								<li><a href="http://demo.aquiathemes.net/aura">'.t('Demo').'</a></li>';
		$out .= '							</ul>';
		$out .= '						</nav>';
	}

	if ($settings['vtabs'] == TRUE) {
		$out .= '							<a class="toggle-tabs ac-cell" href="#" data-target="#system-theme-settings" title="'.t('Show all Options').'">';
		$out .= '				  			'. theme('acquia_iconfont', array('class' => array('icon-btn', ' icon-admin-full'))) . '';
		$out .= '							</a>';
	}
	
	$out .= '					</div>';
	$out .= '			</div>';

	return $out;
}

/**
 * Builds theme settings form footer
 */
function acquia_theme_options_footer(){
 return '</div>';
}


/**
 * Attach Vertical Tabs CSS to the form 
 *
 * @param {array} $form
 */
function acquia_add_vertical_tabs_style(&$form) {
	$loaded = drupal_add_css();
	$new = drupal_add_css(drupal_get_path('module', 'acquia') . '/css/theme-settings.css');
	$css = array_diff_key($new, $loaded);

  $form['#attached']['css'] = $css;
}

/**
 * Discovers layouts, extensions or other plugins in the theme trail.
 *
 * @param string $type
 *   A theme extension type (e.g. layout or extension).
 * @param string $theme
 *   (Optional) The key (machine-readable name) of a theme. Defaults to the key
 *   of the current theme.
 *
 * @return array
 *   An array containing the discovered definitions.
 */
function acquia_theme_discovery($type, $theme = NULL, $hook = 'info', $reset = false) {
	$discovery = &drupal_static(__FUNCTION__, array());
	
  $theme = isset($theme) ? $theme : variable_get('theme_default');
	
  if ($reset || !isset($discovery[$theme][$type])) {
		$cid = 'acquia:discovery:' .$type .':' .$theme . ':' .$hook;
		$cache = cache_get($cid);
		if (!$reset && $cache && isset($cache->data)) {
			$discovery[$theme][$type] = $cache->$data;
		}else{
			 $discovery[$theme][$type] = array();
		 
			 // Retrieve all themes from the theme trail of the given theme.
			 $themes = $theme === FALSE ? list_themes() : acquia_theme_trail($theme);
		 
			 // Collect paths to all sub-themes grouped by base themes. These will be
			 // used for filtering. This allows base themes to have sub-themes in its
			 // folder hierarchy without affecting the base themes template discovery.
			 $paths = array();
			 foreach (list_themes() as $key => $info) {
				 if (!empty($info->base_theme)) {
					 $paths[$info->base_theme][$key] = dirname($info->filename);
				 }
			 }
			 foreach ($paths as $basetheme => $subthemes) {
				 foreach ($subthemes as $subtheme => $path) {
					 if (isset($paths[$subtheme])) {
						 $paths[$basetheme] = array_merge($paths[$basetheme], $paths[$subtheme]);
					 }
				 }
			 }
		 
			 $strlen = strlen($type) + 1;
			 foreach ($themes as $key => $label) {
				 // Retrieve the array of paths that should be ignored for this theme.
				 $ignore = isset($paths[$key]) ? $paths[$key] : array();
				 $path = drupal_get_path('theme', $key);
				 // Support files without '.inc' extension for backwards compatibility.
				 foreach (file_scan_directory($path, '/\.' . $type . '(\.inc)?$/', array('key' => 'name')) as $name => $file) {
					 // Ignore sub-theme implementations for the current theme.
					 if (strpos($file->uri, str_replace($ignore, '', $file->uri)) !== 0) {
						 continue;
					 }
		 
					 include_once './' . $file->uri;
					 
					 if (substr($name, -$strlen) === '.' . $type) {
						 $name = substr($name, 0, strlen($name) - $strlen);
					 }
					 
					 $info = _acquia_theme_process_include($theme, $theme . '_' . $name, dirname($file->uri), $hook);
		 
					 if (is_array($info)) {
						 // Fill in defaults.
						 foreach ($info as $plugin => $properties) {
							 $discovery[$theme][$type][$plugin] = $properties;
							 $discovery[$theme][$type][$plugin] += array(
								 'name' => $name,
								 'path' => dirname($file->uri),
								 'file' => $file->uri,
								 'theme' => $key,
							 );
						 }
					 }
					 else if (!empty($info)){
						 $discovery[$theme][$type][$name] = $info;
						 $discovery[$theme][$type][$name] += array(
							 'name' => $name,
							 'path' => dirname($file->uri),
							 'file' => $file->uri,
							 'theme' => $key,
						 );
					 }
				 }
				 
			 }
		}
	}

  return $discovery[$theme][$type];
}

/**
 * Process a single hook implementation of an acquia plugin.
 *
 * @param $module
 *   The module that owns the hook.
 * @param $identifier
 *   Either the module or 'ac_composer_' . $file->name
 * @param $hook
 *   The name of the hook being invoked.
 */
function _acquia_theme_process_include($theme, $identifier, $path, $hook) {
	$function = $identifier . '_' . $hook;

	if (!function_exists($function)) {
		return NULL;
	}

	$result = $function();

	if (!isset($result) || !is_array($result)) {
		return NULL;
	}

	return $result;
}

/**
 * Builds the full theme trail (deepest base theme first) for a theme.
 *
 * @param string $theme
 *   (Optional) The key (machine-readable name) of a theme. Defaults to the key
 *   of the current theme.
 *
 * @return array
 *   An array of all themes in the trail, keyed by theme key.
 */
function acquia_theme_trail($theme = NULL) {
  $theme = isset($theme) ? $theme : variable_get('theme_default');

  if (($cache = &drupal_static(__FUNCTION__)) && isset($cache[$theme])) {
    return $cache[$theme];
  }

  $cache[$theme] = array();

  if ($theme == $GLOBALS['theme'] && isset($GLOBALS['theme_info']->base_themes)) {
    $cache[$theme] = $GLOBALS['theme_info']->base_themes;
  }

  $themes = list_themes();
  if (empty($cache[$theme]) && isset($themes[$theme]->info['base theme'])) {
    $cache[$theme] = system_find_base_themes($themes, $theme);
  }

  // Add our current subtheme ($key) to that array.
  $cache[$theme][$theme] = $themes[$theme]->info['name'];

  return $cache[$theme];
}
