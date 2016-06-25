<?php
/**
 * Returns array( 'rgba', 'ie_color' ).
 *
 * @param string $color.
 * @param string $ie_color.
 * @param int $opacity.
 *
 * @return array.
 */
function acquia_theme_make_ie_compat_rgba( $color, $ie_color, $opacity ) {
  $return = array(
	'color' => acquia_theme_color_hex2rgba( $color, $opacity ),
	'ie' => $ie_color
  );

  if ( $opacity == 100 ) {
	$return['ie'] = $color;
  }

  return $return;
}


/**
 * Description here.
 */
function acquia_theme_get_opacity( $opacity = 0 ) {
  $opacity = ($opacity > 0) ? $opacity/100 : 0;
  return $opacity;
}


/**
 * Description here.
 */
function acquia_theme_color_hex2rgb( $_color, $raw = false ) {

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
 * Description here.
 */
function acquia_theme_color_hex2rgba( $color, $opacity = 0 ) {

  if ( !$color ) return '';

  $rgb_array = acquia_theme_color_hex2rgb( $color, true );

  return sprintf( 'rgba(%d,%d,%d,%s)', $rgb_array[0], $rgb_array[1], $rgb_array[2], acquia_theme_get_opacity( $opacity ) );
}

/**
 * Return web font properties array.
 *
 * @param string $font
 * @return object/bool Returns object{'font_name', 'bold', 'italic'} or false.
 */
function acquia_theme_make_web_font_object( $font, $defaults = array() ) {
  // defaults
  $weight = $style = 'normal';
  $family = 'Raleway';

  if ( !empty($defaults) ) { extract((array)$defaults); }

  $clear = explode('&', $font);
  $clear = explode(':', $clear[0]);

  if ( isset($clear[1]) ) {
	$vars = explode('italic', $clear[1]);

	if ( isset($vars[1]) ) $style = 'italic';

	if ( '700' == $vars[0] || 'bold' == $vars[0] ) {
	  $weight = 'bold';
	} else if( '400' == $vars[0] || 'normal' == $vars[0] ) {
	  $weight = 'normal';
	} else if( $vars[0] ) {
	  $weight = $vars[0];
	}
  }

  if ( '' != $clear[0] ) {
	$family = $clear[0];
  }

  $font = new stdClass();
  $font->family = $family;
  $font->style = $style;
  $font->weight = $weight;

  return $font;
}


/**
 * Description here.
 */
function acquia_get_css_img_attribute($image) {
  if(empty($image)) {
	return 'none';
  }
  return sprintf("url('%s')", $image);
}

/**
 *
 */
function acquia_merge_style_with_defaults(&$values, $style) {
  foreach ($style as $key => $props) {
	if (is_array($props['default'])) {
	  foreach ($props['default'] as $attr => $value) {
		if (!isset($values[$key][$attr])) {
		  $values[$key][$attr] = $value;
		}
	  }
	}elseif (!isset($values[$key])) {
	  $values[$key] = $props['default'];
	}
  }
}

/**
 * Compile less vars from theme options.
 */
function acquia_theme_compile_less_vars($skin) {
  acquia_include('utility', 'ac_skin');
  $image_defaults = array(
	'image'			=> '',
	'repeat'		=> 'repeat',
	'position_x'	=> 'center',
	'position_y'	=> 'center'
  );

  $groups_style = ac_skin_get_all_group_styles();
  $less_vars = array();
  $fonts = array();

  foreach ($groups_style as $group_styles) {
	if (empty($group_styles))
	  continue;
	foreach ($group_styles as $sub_group => $defaults) {
	  // extract scheme settings
	  $defaults['typo'] = isset($defaults['typo']) ? $defaults['typo'] : array();
	  $defaults['scheme'] = isset($defaults['scheme']) ? $defaults['scheme'] : array();

	  $styles = array_merge_recursive($defaults['typo'], $defaults['scheme']);
	  if (!empty($styles)) {
		$values = isset($skin[$sub_group]) ? $skin[$sub_group] : array();

		// merge with default styles
		acquia_merge_style_with_defaults($values, $styles);

		foreach ($styles as $attr => $prop) {
		  $type = $prop['type'];
		  $default = $prop['default'];
		  $attr_values = isset($values[$attr]) ? $values[$attr] : '';

		  switch($type) {
			// RGBA color
			case 'rgba_color':
			  if (!isset($attr_values['color'])) {
				break;
			  }
			  if ($attr_values['opacity'] <100) {
				// make RGBA of color with opacity
				$attr_values = acquia_theme_make_ie_compat_rgba(
				  $attr_values['color'],
				  $attr_values['ie'],
				  $attr_values['opacity']
				);
			  }

			  acquia_add_less_var($sub_group, $attr, $attr_values['color'], $less_vars);
			  acquia_add_less_var($sub_group, $attr, $attr_values['ie'], $less_vars, 'ie');
			  break;

			case 'bg':
			  if (!isset($attr_values['image']) || empty($attr_values['image'])){
				break;
			  }else{
				$attr_values['image'] = acquia_get_css_img_attribute(ac_skin_get_absolute_image_url($attr_values['image']));
			  }

			  if (!isset($attr_values['full']) || $attr_values['full'] == 1){
				$attr_values['repeat'] = 'no-repeat';
				$attr_values['attachment'] = 'fixed';
				$attr_values['size'] = 'cover';
				unset($attr_values['full']);
			  }else{
				$attr_values['attachment'] = '~""';
				$attr_values['size'] = 'inherit';
			  }

			  foreach ($attr_values as $_key => $_value) {
				acquia_add_less_var($sub_group, $attr, $_value, $less_vars, $_key);
			  }
			  break;

			case 'font':
			  if(!is_string($attr_values)){
			  }
			  $fonts[$attr_values] = $attr_values;
			  $computed_font = acquia_theme_make_web_font_object($attr_values);
			  if ( !$computed_font ) {
				break;
			  }

			  if (isset($prop['prefix'])) {
				$computed_font->family = $prop['prefix'] . $computed_font->family;
			  }

			  if (isset($prop['suffix'])) {
				$computed_font->family .= $prop['suffix'];
			  }
			  acquia_add_less_var($sub_group, $attr, $computed_font->family, $less_vars);
			  acquia_add_less_var($sub_group, $attr, $computed_font->style, $less_vars, 'style');
			  acquia_add_less_var($sub_group, $attr, $computed_font->weight, $less_vars, 'weight');
			  break;

			// font-size
			default:

			  if (is_array($attr_values)) {
				$value = $attr_values[$type];
			  }else{
				$value = $attr_values;
			  }

			  if ($type == 'number') {
				$value = intval($value);
			  }else if ($type == 'transform') {
				switch ($value) {
				  case 'up':
					$value = 'uppercase';
					break;
				  case 'cap':
					$value = 'capitalize';
					break;
				  case 'lo':
					$value = 'lowercase';
					break;
				  case 'it':
					$value = 'italic';
					break;
				}
			  }

			  if (isset($prop['prefix'])) {
				$value = $prop['prefix'] . $value;
			  }

			  if (isset($prop['suffix'])) {
				$value .= $prop['suffix'];
			  }
			  acquia_add_less_var($sub_group, $attr, $value, $less_vars);
			  break;
		  }

		}
	  }
	}
  }
  // add shortcode data as less vars
  if (isset($skin['shortcodes'])) {
	foreach ($skin['shortcodes'] as $shortcode => $value) {
	  if (!empty($value)) {
		acquia_add_less_var('sc', $shortcode, $value, $less_vars);
	  }
	}
  }

  // add block titles style
  if (isset($less_vars['sc__ac_fancy_header_style']) &&
	in_array($less_vars['sc__ac_fancy_header_style'],
	  array('single_thin_bottom', 'single_thick_bottom', 'double_solid_thick_bottom'))
  ) {
	$less_vars['block_title_style'] = 'bottom-borderd';
  }

  // add block titles style
  if (isset($less_vars['sc__ac_fancy_header_style']) &&
	in_array($less_vars['sc__ac_fancy_header_style'],
	  array('single_thin_bottom', 'single_thick_bottom', 'double_solid_thick_bottom'))
  ) {
	$less_vars['block_title_style'] = 'bottom-borderd';
  }
  // add block titles style
  if (isset($less_vars['sc__ac_button_style']) &&
	in_array($less_vars['sc__ac_button_style'],
	  array('subtle', 'subtle-fade'))
  ) {
	$less_vars['feature_style'] = 'subtle';
  }else{
	$less_vars['feature_style'] = 'normal';
  }

  // modify header bg
  if (isset($less_vars['header__bg__image']) &&
	empty($less_vars['header__bg__image'])) {
	$less_vars['header__bg__image'] = 'none';
  }

  // Main Menu Style
  if (isset($skin['main_menu_style'])) {
	$menu_style = explode(' ', $skin['main_menu_style']);
	$less_vars['main_menu_style'] = array_shift($menu_style);
	if (!empty($menu_style)){
	  $less_vars['main_menu_child_style'] = array_shift($menu_style);
	}else{
	  $less_vars['main_menu_child_style'] = 'none';
	}
  }
  // Header background
  $less_vars['header__bg__image'] = isset($less_vars['header__bg__image']) && !empty($less_vars['header__bg__image']) ? $less_vars['header__bg__image'] : 'none';
  return array('vars' => $less_vars, 'fonts' => $fonts);
}
/**
 *
 */
function acquia_add_less_var($key, $attr, $value, &$less_vars, $suffix = NULL){
  if (!empty($suffix)) {
	$less_vars[$key .'__' .$attr .'__' .$suffix] = $value;
  }else{
	$less_vars[$key .'__' .$attr] = $value;
  }
}

/**
 *
 */
function ac_skin_save_new_skin_styles($new_styles){
  $theme = variable_get('theme_default');
  $settings = variable_get("theme_{$theme}_settings");
  if (isset($settings['acquia'])) {
	$old_styles = $settings['acquia'];
  }
  foreach($new_styles as $type => $groups) {
	foreach ($groups as $group_name => $styles) {
	  $old_styles['skin'][$type][$group_name] = $styles;
	}
  }

  // Override old settings with new ones
  acquia_skin_override_skin_settings($old_styles['skin']);

  $skin_vars = acquia_theme_get_skin_vars_from_theme($old_styles);
  $css = acquia_theme_get_css_from_skin_vars($skin_vars);
  acquia_theme_save_skin_styles($css);
}


/**
 * @todo
 */
function acquia_skin_override_skin_settings($skin_settings) {
  if (empty($skin_settings)) {
	return;
  }

  $theme = variable_get('theme_default');
  $settings = variable_get("theme_{$theme}_settings");
  if (isset($settings['acquia']['skin'])) {
	$settings['acquia']['skin'] = $skin_settings;
  }

  variable_set("theme_{$theme}_settings", $settings);
}


/**
 * Escape function for lessphp.
 *
 */
function acquia_lessphp_escape( $value ) {
  $v = &$value[2][1][1];
  $v = rawurlencode( $v );

  return $value;
}

/**
 *
 */
function acquia_theme_get_css_from_skin_vars($skin){
  $generator = acquia_theme_compile_less_vars($skin);
  $less_vars = $generator['vars'];
  // Compile base accent color
  acquia_include('lessc', 'ac_skin');
  $less = new lessc;
  $less->registerFunction("escape", "acquia_lessphp_escape");
  $less->setVariables($less_vars);

  if (!empty($generator['fonts'])) {
	$css = ac_skin_add_font_importer($generator['fonts']);
  }

  $less_path = drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/skin/skin.less';
  if (file_exists($less_path)) {
	$css .= $less->compileFile($less_path);
  }
  return $css;
}

/**
 *
 */
function ac_skin_add_font_importer($fonts) {
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
  $fonts = array_filter($fonts, 'strlen');

  if(empty($fonts)) {
	return;
  }

  $out = '';
  $subsets = array();
  $search = '&subset=';
  $safe_fonts = array_keys(acquia_websafe_fonts());
  $theme_fonts = ac_skin_extract_fonts();
  $theme_fonts_to_import = array();

  foreach ($fonts as &$font) {
	if (in_array($font, $safe_fonts)) {
	  unset($font);
	  continue;
	}

	if (!isset($theme_fonts[$font])) {
	  $font = str_replace( ' ', '+', $font );
	  if ($pos = stripos($font, $search)) {
		$subsets[] = substr($font, $pos + strlen($search));
		$font = substr($font, 0, $pos);
	  }
	}else {
	  $theme_fonts_to_import[] = $font;
	  unset($font);
	}
  }

  // if we have google fonts
  if (!empty($fonts)) {
	$fonts = implode('|', $fonts);
	if (!empty($subsets)) {
	  $fonts .= '&subset=' .implode(',', $subsets);
	}

	$protocol = "http";
	if ( isset( $_SERVER['HTTPS'] ) && $_SERVER['HTTPS'] == 'on' ) {
	  $protocol = "https";
	}

	$out .= "@import url(" .$protocol ."://fonts.googleapis.com/css?family=" .$fonts . ");\r\n";
  }

  // if we have theme fonts
  if (!empty($theme_fonts_to_import)) {
	$import = '';
	foreach ($theme_fonts_to_import as $font) {
	  $font_info = ac_skin_discover_theme_fonts($theme_fonts[$font]);
	  $out .= "@import url(" .url($font_info['path'] .'/' .$font_info['css'], array('absolute' => TRUE)).");\n";
	}
  }
  return $out;
}

/**
 *
 */
function acquia_theme_save_skin_styles($css, $file = NULL){
  $comment  = "/**\r\n";
  $comment .= " * Custom acquia theme css file\r\n";
  $comment .= " * 	Generated on ".format_date(time())."\r\n";
  $comment .= " * @copyright http://acquiathems.com\r\n";
  $comment .= " **/\r\n";

  $css = $comment .$css;

  if (empty($file)) {
	$file = variable_get('acquia_theme_custom_css', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/css/skin.css');
  }

  if (!file_unmanaged_save_data($css, $file, FILE_EXISTS_REPLACE)) {
	drupal_set_message('Generating skin css file was unsucesful!');
  }
}

/**
 * @todo
 */
function acquia_skin_override_theme_settings($config) {
  if (empty($config)) {
	return;
  }

  $theme = variable_get('theme_default');
  $settings = (array)variable_get("theme_{$theme}_settings");
  $settings['acquia'] = isset($settings['acquia']) ? $settings['acquia'] : array();

  // preserve contact and social icons in top bar
  if (isset($settings['acquia']['topbar'])) {
	$config['topbar']['contact_info'] = $settings['acquia']['topbar']['contact_info'];
	$config['topbar']['social_icons'] = $settings['acquia']['topbar']['social_icons'];
  }
  $settings['acquia'] = $config;
  variable_set("theme_{$theme}_settings", $settings);
}

/**
 * Form submit handler for the theme settings form to clean up stale values.
 */
function acquia_generate_skin($form, &$form_state) {
  $values = $form_state['values'];
  $acquia = acquia_theme_get_acquia_settings();
  $info = $values['skin_generator'];

  acquia_variable_set('skin_generator', $values['skin_generator']);
  if (!isset($info['name']) || empty($info['name'])) {
	return form_set_error('skin_generator', t('Please provide a name for your skin!'));
  }
  acquia_include('file');
  acquia_include('utility');
  acquia_include('utility', 'ac_skin');

  $theme = variable_get('ACQUIA_BASE_THEME');
  // Check that the destination is writable.
  $temporary_directory = 'temporary://';

  // Prepare target locations for generated files.
  $id = $theme . '-' . substr(hash('sha256', serialize($values['skin_generator']['name']) . microtime()), 0, 8);
  $paths['skins'] = acquia_variable_get('theme_skins_dir');
  $paths['target'] = $paths['skins'] . '/' . $id;

  foreach ($paths as $path) {
	file_prepare_directory($path, FILE_CREATE_DIRECTORY);
  }

  $paths['target'] = $paths['target'] . '/';

  // clean skin info
  acquia_skin_generator_prepare_info($info, $acquia, $paths['target']);

  $files = array(
	'config.json' => drupal_json_encode($acquia),
	'skin.info' => ac_skin_build_info_file($info)
  );

  // Create base files
  foreach ($files as $file => $data) {
	$uri = $paths['target'] . $file;
	if (!file_exists($uri) && !file_unmanaged_save_data($data, $uri, FILE_EXISTS_REPLACE)) {
	  return form_set_error('skin_generator', t('Generating skin was unsuccessful!'));
	}
  }

  // save Skin settings
  $skin_vars = acquia_theme_get_skin_vars_from_theme($acquia);
  $css = acquia_theme_get_css_from_skin_vars($skin_vars);

  // save to skin.css file
  acquia_theme_save_skin_styles($css);

  // save to new skin css file
  acquia_theme_save_skin_styles($css, $paths['target'] . 'skin.css');

  // save to new skin css file
  // @todo change it to the GURU way
  $custom_skin_path = variable_get('acquia_theme_custom_skin_css', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/css/custom-skin.css');
  if (is_file($custom_skin_path) && $styles = file_get_contents($custom_skin_path)) {
	if (!empty($styles) && !file_unmanaged_save_data($styles, $paths['target'] . 'custom-skin.css', FILE_EXISTS_REPLACE)) {
	  drupal_set_message('Generating custom skin file to the new skin was unsucesful!');
	}
  }

  // saving custom-skin.sass to new skin folder
  // @todo change it to the GURU way
  $custom_skin_path = variable_get('acquia_theme_custom_skin_sass', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/sass/custom-skin.scss');
  if (is_file($custom_skin_path) && $styles = file_get_contents($custom_skin_path)) {
	if (!empty($styles) && !file_unmanaged_save_data($styles, $paths['target'] . 'custom-skin.scss', FILE_EXISTS_REPLACE)) {
	  drupal_set_message('Generating custom skin file to the new skin was unsucesful!');
	}
  }

  cache_clear_all(ACQUIA_SKINS_CID, 'cache');
}

/**
 *
 */
function acquia_theme_get_skin_vars_from_theme($acquia){
  $skin_vars = $acquia['skin'];
  $skin_vars = array_merge_recursive($skin_vars['scheme'], $skin_vars['typo']);
  $skin_vars['shortcodes'] = $acquia['shortcodes'];
  $skin_vars['main_menu_style'] = $acquia['main_menu_style'];

  return $skin_vars;
}

/**
 * @todo
 */
function acquia_skin_generator_prepare_info(&$info, $acquia, $target) {
  if (isset($info['submit'])) {
	unset($info['submit']);
  }

  if (isset($info['screenshot']['fid']) && !empty($info['screenshot']['fid'])) {
	$screenshot = file_load($info['screenshot']['fid']);
	if ($path = file_unmanaged_copy($screenshot->uri, $target . $screenshot->filename)) {
	  $info['screenshot'] = $screenshot->filename;
	}
  }

  if (isset($acquia['skin']['scheme']['general']['accent-color'])) {
	$info['accent-color'] = $acquia['skin']['scheme']['general']['accent-color'];
  }

  if (isset($acquia['boxed'])) {
	$info['boxed'] = $acquia['boxed'];
  }

  if (isset($acquia['header_layout'])) {
	$info['header_layout'] = $acquia['header_layout'];
	if ($acquia['header_layout'] == 'classic' && acquia_theme_get_settings('header_content', '') != '') {
	  $info['header_content'] = drupal_hash_base64(acquia_theme_get_settings('header_content', ''));
	}
  }

  // add timestamp
  $info['datestamp'] = time();
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
function acquia_theme_skin_info($path=NULL, $reset=FALSE, $type = 'info') {
  $skins = &drupal_static(__FUNCTION__, NULL);

  if ($reset || !isset($skins)) {
	$cache = cache_get(ACQUIA_SKINS_CID);
	if (!$reset && $cache && isset($cache->data)) {
	  $skins = $cache->data;
	}else{
	  if (empty($path)) {
		$path = acquia_variable_get('theme_skins_dir');
	  }
	  $skins = array();

	  foreach (file_scan_directory($path, '/\.' . $type . '$/') as $file) {
		$skin_path = str_replace($file->filename, '', $file->uri);
		$skin_mn = str_replace(array(acquia_variable_get('theme_skins_dir'), '/', '\\'), '', $skin_path);
		$skins[$skin_mn] = drupal_parse_info_file($file->uri);
		$skins[$skin_mn]['uri'] = $skin_path;
	  }
	  cache_set(ACQUIA_SKINS_CID, $skins);
	}
  }
  return $skins;
}
