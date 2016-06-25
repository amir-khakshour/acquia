<?php
/**
 *
 *
 */

 /**
 * Adds required CSS files for fontello fonts
 */
function acquia_get_fontello_css($settings = array()) {
	$settings += array(
		'font_name' => 'fontello',
		'font_config' => 'config.json',
	);
  $config = acquia_fontello_extract_config($settings['font_name'], $settings['font_config']);
	return acquia_ajax_fontello_css($config['path'], $config['font']);
}
/**
 * Load fontello css files required to render font icons properly
 * @param $path
 * 		relative path to font file directory e.g: sites/all/libraries/fonts/fontello
 * @param $font
 * 		name of font file 
 */
 function acquia_ajax_fontello_css($path, $font){
	$loaded = drupal_add_css();
	drupal_add_css($path .'/css/' .$font .'.css');
	$new = drupal_add_css($path .'/css/' .$font .'-ie7.css', array('browsers' => array('IE' => 'IE 7', '!IE' => FALSE)));
	return array_diff_key($new, $loaded);
}
 /**
 * make icon font character array
 * @paran $name
 *   name of font files under font libs
 * @paran $config
 *   file name of font config 
 */
function acquia_fontello_extract_config($name ='fontello', $config ='config.json') {
  $cache = &drupal_static(__FUNCTION__);

  if (!isset($cache)) {
		$cid = 'acquia:icofontconf:' .$name .':' .$config;
		
		if (!$cache = cache_get($cid)) {
			$lib_path = acquia_variable_get('libs_path', 'sites/all/libraries');
			$dir = acquia_variable_get('fonts_path', $lib_path . '/fonts') . '/' . $name;
			if ($contents = @file_get_contents($dir . '/' . $config)) {
				$config = json_decode($contents, true);
				if (!is_array($config)) {
					drupal_set_message('Path to config file of webfont is invalid!');
					return;
				}
				else if (isset($config['glyphs']) && is_array($config['glyphs'])) {
					foreach ($config['glyphs'] as $glyph) {
						$cache['glyphs'][$glyph['code']] = $glyph['css'];
					}
					ksort($cache['glyphs']);
					$cache['path'] = $dir;
					$cache['font'] = $config['name'] ? $config['name'] : 'fontello';
					$cache['class-prefix'] = $config['css_prefix_text'];
					cache_set($cid, $cache);
				}
			}else{
				drupal_set_message('Config file content is invalid!');
				return;
			}
		}else {
			$cache = $cache->data;
		}
	
  }

	return $cache;
}

 
/**
 * get given glyph code number or string based on glyph type.
 * @todo Document
 */
function acquia_fontello_glyph_get_code($glyph, $name ='fontello', $config ='config.json') {
	$prefix = &drupal_static(__FUNCTION__);
	
	if (is_numeric($glyph)) {
		$type = 'number';
		$glyph = (int) $glyph;
	}else{
		$type = 'string';
		if (!isset($prefix)) {
			$config = acquia_fontello_extract_config($name, $config);
			$prefix = $config['class-prefix'];
		}
	}
	
	// Code based icons
	if ($type == 'number') {
		$glyphs = acquia_fontello_glyphs($type, $name, $config);
		$glyph = isset($glyphs[$glyph]) ? $glyphs[$glyph] : 'icon-null';
	}
	// String based icons
	else{
		
		$glyph = $prefix . $glyph;
	}

	return $glyph;
}
/**
 * Get font icon character codes of given font by a associative array
 * which icon string code is the key and the value is the number code or reverse.
 * 
 * @paran $type
 *   type of glyphs array, icon string codes or icon number code
 * @paran $name
 *   name of font files under font libs
 * @paran $config
 *   file name of font config 
 */
function acquia_fontello_glyphs($type, $name ='fontello', $config ='config.json') {
  $cache = &drupal_static(__FUNCTION__);
  if (!isset($cache)) {
		$cid = 'acquia:glyphs:' .$type;
		if ($cache = cache_get($cid)) {
      $cache = $cache->data;
    }else{
			$config = acquia_fontello_extract_config($name, $config);
			$glyphs = $config['glyphs'];
			foreach ($glyphs as $code => $glyph) {
				$glyphs[$code] = $config['class-prefix'] . $glyph;
			}
			cache_set($cid, $glyphs);
		}
	}
	return $cache;
}