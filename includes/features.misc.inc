<?php
/**
 * @file
 * Misc Backend Features
 */

/**
 * Implements hook_user_default_permissions().
 */
function acquia_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'search',
  );

  return $permissions;
}


/**
 * Implements hook_registry_files_alter().
 * 
 * Adds the Mobile_Detect() class to the registry so that autoloading works.
 * See http://drupal.stackexchange.com/questions/42266 for a discussion.
 */
function acquia_registry_files_alter(&$files, $modules) {
  $files[acquia_variable_get('libs_path') . '/Mobile_Detect/Mobile_Detect.php'] = array(
    'module' => 'mobile_detect',
    'weight' => 0,
  );
}
