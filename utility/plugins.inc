<?php
// $Id
/**
 * @todo
 *
 */

/**
 * Return a list of directories by modules implementing acquia_include_directory().
 *
 * @param $plugintype
 *   The type of a plugin; can be 'shortcode'.
 *
 * @return
 *   An array containing module names suffixed with '_' and their defined
 *   directory.
 *
 * @see acquia_load_includes()
 */
function acquia_get_directories($plugintype) {
  $directories = array();
  foreach (module_implements('acquia_include_directory') as $module) {
    $result = module_invoke($module, 'acquia_include_directory', $plugintype);
    if (isset($result) && is_string($result)) {
      $directories[$module] = drupal_get_path('module', $module) . '/' . $result;
    }
  }
  return $directories;
}

/**
 * Load include files for shortcodes implemented by all modules.
 *
 * @param $type
 *   The type of includes to search for, can be 'shortcodes', 'composer', 'skins', ...
 * @param $hook
 *   The hook name to invoke.
 * @param $file
 *   An optional include file name without .inc extension to limit the search to.
 *
 * @see _get_directories(), _process_include()
 */
function acquia_load_includes($type, $hook, $file = NULL) {
	// Determine implementations.
	$directories = acquia_get_directories($type);
	
	$file_list = array();
	foreach ($directories as $module => $path) {
		$file_list[$module] = drupal_system_listing("/{$file}.inc\$/", $path, 'name', 0);
	}

	// Load implementations.
	$info = array();
	foreach (array_filter($file_list) as $module => $files) {
		foreach ($files as $file) {
			include_once './' . $file->uri;
			$result = _acquia_plugins_process_include($module, $module . '_' . $file->name, dirname($file->uri), $hook);
			if (is_array($result)) {
			 
				// Fill in defaults.
				foreach ($result as $tag => $properties) {
					$result[$tag]['module'] = $module;
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
 * Process a single hook implementation of an acquia plugin.
 *
 * @param $module
 *   The module that owns the hook.
 * @param $identifier
 *   Either the module or 'ac_composer_' . $file->name
 * @param $hook
 *   The name of the hook being invoked.
 */
function _acquia_plugins_process_include($module, $identifier, $path, $hook) {
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