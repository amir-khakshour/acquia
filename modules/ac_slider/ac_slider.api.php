<?php

/**
 * Returns a list of sliders for the ac_slider.
 *
 * Sliders are defined in a multi-dimensional associative
 * array format with the following keys:
 *
 * - #class name (optional): slider class name
 * - #file: file name containing class definition
 * - #path : path to #file 
 *
 * @example
 * <code>
 * array(
 *  'layerslider' => array(
 *     '#class' => 'layerslider',
 *     '#file' => 'layerslider.class',
 *     '#path' => drupal_get_path('module', 'myModule'),
 *   ),
 * );
 * </code>
 */
function hook_ac_sliders_info() {
  return array();
}

/**
 * Alter the Sliders information before detection and caching takes place.
 *
 * The library definitions are passed by reference. A common use-case is adding
 * a module's integration files to the library array, so that the files are
 * loaded whenever the library is. As noted above, it is important to declare
 * integration files inside of an array, whose key is the module name.
 *
 * @see hook_libraries_info()
 */
function hook_ac_sliders_info_alter() {
  return array();
}
