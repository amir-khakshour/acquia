<?php
/**
 * @file
 * Contains File utility functions for acquia composer module
 */


/**
 * Gather all shortcodes Composers provided by modules
 */
function collect_builder_shortcodes(){
  $composer = &drupal_static(__FUNCTION__, NULL);

  // @DEBUG
  $composer = ac_composer_load_includes();
  if (!isset($composer)) {
    $cid = 'ac_composer:composers';

    if (($cache = cache_get($cid)) && !empty($cache->data)) {
      $composer = $cache->data;
    }else {
      $composer = array();
      $composer = ac_composer_load_includes();
      cache_set($cid, ac_composer_load_includes());
    }
  }
  return $composer;
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
 * @see _get_directories(), _process_include()
 */
function ac_composer_load_includes($type = 'composer', $hook = 'composer', $file = NULL) {
	// Determine implementations.
	$directories = _ac_composer_get_directories($type);
	// built-in shortcodes
	$directories['ac_composer'] = drupal_get_path('module', 'ac_composer') . '/' . $type;

	$file_list = array();
	foreach ($directories as $module => $path) {
		$file_list[$module] = drupal_system_listing("/{$file}.inc\$/", $path, 'name', 0);
	}

	// Load implementations.
	$info = array();
	foreach (array_filter($file_list) as $module => $files) {
		foreach ($files as $file) {
			include_once './' . $file->uri;
			$result = _ac_composer_process_include($module, $module . '_' . $file->name, dirname($file->uri), $hook);

			if (is_array($result)) {

				// Fill in defaults.
				foreach ($result as $tag => $properties) {
					$result[$tag]['module'] = $module;
					$result[$tag]['tag'] = $tag;
					if ( !isset($properties['path']) ) {
						$result[$tag]['file'] = $file->name . '.inc';
						$result[$tag]['path'] = dirname($file->uri);
					}
				}

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
 * @see load_includes(),process_include()
 */
function _ac_composer_get_directories($plugintype = 'composer') {
	$directories = array();
	foreach (module_implements('ac_composer_include_directory') as $module) {
		$result = module_invoke($module, 'ac_composer_include_directory', $plugintype);
		if (isset($result) && is_string($result)) {
			$directories[$module] = drupal_get_path('module', $module) . '/' . $result;
		}
	}
	return $directories;
}

/**
 * Process a single hook implementation of a Composer shortcode.
 *
 * @param $module
 *   The module that owns the hook.
 * @param $identifier
 *   Either the module or 'ac_composer_' . $file->name
 * @param $hook
 *   The name of the hook being invoked.
 */
function _ac_composer_process_include($module, $identifier, $path, $hook) {
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