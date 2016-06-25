<?php

/**
 * @file
 * Contains the variables used by media and their defaults.
 */

/* ***************************************** */
/* CONSTANTS                                 */
/* ***************************************** */

/**
 * Define constants.
 */
define('ACQUIA_VARIABLE_NAMESPACE', 'ac_');
define('ACQUIA_T_VARIABLE_NAMESPACE', 'ac_t');

/**
 *  Wrapper for variable_get() that uses the acquia variable registry.
 *
 *  @param string $name
 *    The variable name to retrieve. Note that it will be namespaced by
 *    pre-pending ACQUIA_VARIABLE_NAMESPACE, as to avoid variable collisions with
 *    other modules.
 *  @param unknown $default
 *    An optional default variable to return if the variable hasn't been set
 *    yet. Note that within this module, all variables should already be set
 *    in the acquia_variable_default() function.
 *  @return unknown
 *    Returns the stored variable or its default.
 *
 *  @see acquia_variable_set()
 *  @see acquia_variable_del()
 *  @see acquia_variable_default()
 */
function acquia_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing still desired.
  if (!isset($default)) {
    $default = acquia_variable_default($name);
  }
  // Namespace all variables
  $variable_name = ACQUIA_VARIABLE_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 *  Wrapper for variable_set() that uses the Media variable registry.
 *
 *  @param string $name
 *    The variable name to set. Note that it will be namespaced by
 *    pre-pending ACQUIA_VARIABLE_NAMESPACE, as to avoid variable collisions with
 *    other modules.
 *  @param unknown $value
 *    The value for which to set the variable.
 *  @return unknown
 *    Returns the stored variable after setting.
 *
 *  @see acquia_variable_get()
 *  @see acquia_variable_del()
 *  @see acquia_variable_default()
 */
function acquia_variable_set($name, $value) {
  $variable_name = ACQUIA_VARIABLE_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 *  Wrapper for variable_del() that uses the Media variable registry.
 *
 *  @param string $name
 *    The variable name to delete. Note that it will be namespaced by
 *    pre-pending ACQUIA_VARIABLE_NAMESPACE, as to avoid variable collisions with
 *    other modules.
 *
 *  @see acquia_variable_get()
 *  @see acquia_variable_set()
 *  @see acquia_variable_default()
 */
function acquia_variable_del($name) {
  $variable_name = ACQUIA_VARIABLE_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * Returns the final machine name of a Media namespaced variable.
 */
function acquia_variable_name($name) {
  return ACQUIA_VARIABLE_NAMESPACE . $name;
}

/**
 *  The default variables within the DiamondLayers namespace.
 *
 *  @param string $name
 *    Optional variable name to retrieve the default. Note that it has not yet
 *    been pre-pended with the ACQUIA_VARIABLE_NAMESPACE namespace at this time.
 *  @return unknown
 *    The default value of this variable, if it's been set, or NULL, unless
 *    $name is NULL, in which case we return an array of all default values.
 *
 *  @see acquia_variable_get()
 *  @see acquia_variable_set()
 *  @see acquia_variable_del()
 */
function acquia_variable_default($name = NULL, $reset = false) {
  static $defaults;

  if (!isset($defaults) || $reset) {
    if (!$reset && $defaults = cache_get('acquia_default_variables', 'cache')) {
      $defaults = $defaults->data;
    }else{
      // Select the module-defined styles.
      foreach (module_implements('acquia_default_variables') as $module) {
        $module_vars = module_invoke($module, 'acquia_default_variables');
        foreach ($module_vars as $_name => $default) {
          $defaults[$_name] = $default;
        }
      }
      drupal_alter('acquia_default_variables', $defaults);
      cache_set('acquia_default_variables', $defaults);
    }
  }
  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

