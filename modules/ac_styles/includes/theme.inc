<?php
/**
 * @file
 *  Contains helper functions to build and override theme functions
 */


/**
 * implementing hook_theme()
 */
function ac_styles_theme($existing, $type, $theme, $path) {
	$path = drupal_get_path('module', 'acquia') . '/theme';
  $items = array(
    'ac_styles_bg_fallback_slider' => array(
      'variables' => array(),
      'file' => 'includes/theme.inc',
    ),
	);
	
	return $items;
}

function theme_ac_styles_bg_fallback_slider($vars){
  acquia_include('media');
  $image = array('fid' => $vars['bg_fallback']['fid']);
  if (isset($vars['bg_fallback_style']) && !empty($vars['bg_fallback_style'])){
    $image['style'] = array('image_style' => $vars['bg_fallback_style']);
  }
  
  $out = '<div id="ac-bg-fallback-slider">';
  $out .= acquia_image_format_simple($image);
  $out .= '</div>';
  return $out;
}

/**
 * Implements hook_theme_registry_alter().
 */
function ac_styles_theme_registry_alter(&$registry) {

  // Load all plugins type "operation".
  ctools_include('plugins');
  $plugins = ctools_get_plugins('ac_styles', 'plugins');
  
  $meta = array();
  // Include the main extension file for every enabled extension. This is
  // required for the next step (allowing extensions to register hooks in the
  // theme registry).
  foreach ($plugins as $pname => $info) {
    $plugin = ac_style_get_plugin($pname, $meta);
     // Give every enabled extension a chance to alter the theme registry.
    $hook = $info['module'] . '_plugins_' . $pname . '_theme_registry_alter';
    
    $file = '';
    if (isset($info['path']) && isset($info['file'])) {
      $file = $info['path'] . '/' . $info['file'];
    }
    if (!file_exists($file)) {
      $file = false;
    }
    
    if (function_exists($hook)) {
      $hook($registry, $file);
    }
  }

}
