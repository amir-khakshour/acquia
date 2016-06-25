<?php
/**
 * @file
 * Builder shortcode collector
 */

/**
 * Builder shortcode collector
 *
 * @package AcquiaComposer
 */
class DiamondBuilderCollection{
  /**
   * Whther reset cached tempaltes data from DB or not
   */
  protected $reset = FALSE;
  /**
   * An array of enabled shortcodes list
   */
  protected static $enabled = array();

  /**
   * An array of shortcode objects
   */
  protected static $collection = array();

  /**
   * An array of shortcode composer objects
   */
  protected static $composer = array();

  /**
   * An array of shortcode infos
   */
  protected static $shortcodes = array();

  function __construct($reset = FALSE) {
    $this->reset = $reset;
    // Gather all available shortcodes
    $this->getAllShortcodes();
  }

  /**
   * Gather all shortcodes provided by modules
   */
  public function getAllShortcodes($reset = false){
    $shortcodes = &drupal_static(__FUNCTION__, NULL);

    if ($reset || !isset($shortcodes)) {
      $cid = 'ac_shortcode:shortcodes';
      if (!$reset && ($cache = cache_get($cid)) && !empty($cache->data)){
        $shortcodes = $cache->data;
      }else{
        $shortcodes = array();
        $shortcodes = self::load_includes();
        cache_set($cid, $shortcodes);
      }
    }

    self::$shortcodes = $shortcodes;
    return $shortcodes;
  }

  /**
   * Gather all shortcodes provided by modules
   */
  public function getEnabledShortcodes(){
    $shortcodes = &drupal_static(__FUNCTION__, NULL, $this->reset);
    if (!isset($shortcodes)) {
      $shortcodes = $this->getAllShortcodes();
      $enabled = $this->getEnabled();
      if (!empty($enabled)) {
        foreach ($shortcodes as $tag => $info) {
          if (!in_array($tag, $enabled)) {
            unset($shortcodes[$tag]);
          }
        }
      }else{
        drupal_set_message(t("!link shortcodes to use Visual Builder.", array('!link' => l('Enable some shortcodes', 'admin/config/content/formats/full_html', array('absolute'=>TRUE)))), $type='error');
        $shortcodes = array();
      }
    }

    return $shortcodes;
  }

  /**
   * Add shortcode to shortcode collections
   *
   * @param {array} shortcode info
   */
  function addShortcode($shortcode) {
    // Validate shortcode
    $this->validateShortcode($shortcode);
    self::$shortcodes[$shortcode['tag']] = $shortcode;
  }

  /**
   * Getter method to get shortcode info by shortcode tag
   * @param {string} $tag
   *   A string representing shortcode tag
   * @return {array} shortcode info
   */
  public function getShortcodeData($tag){
    if (isset(self::$shortcodes[$tag])) {
      return self::$shortcodes[$tag];
    }
  }

  /**
   * Get Shortcode Model
   */
  public function getShortcodeModel($tag){
    if (!$this->shortcodeExists($tag)) {
      return;
    }

    if (!isset(self::$collection[$tag])) {
      $this->includeShortcode($tag);
      $className = isset(self::$shortcodes[$tag]['model']) && class_exists(self::$shortcodes[$tag]['model'])
        ? self::$shortcodes[$tag]['model'] : ACQUIA_SHORTCODE_MODEL_DUMMY_CLASS;
      self::$collection[$tag] = new $className(self::$shortcodes[$tag]);
    }

    return self::$collection[$tag];
  }

  /**
   * Getter method to get Model for all shortcodes
   */
  public function getAllShortcodesCollection(){

    $sc_collection = &drupal_static(__FUNCTION__, NULL, $this->reset);

    if (!isset($sc_collection)) {
      foreach(self::$shortcodes as $tag => $info) {
        $this->getShortcodeModel($tag);
      }
      $sc_collection = self::$collection;
    }

    return $sc_collection;
  }

  /**
   * include shortcode file
   */
  public function includeShortcode($tag){
    static $used = array();

    if (!$this->shortcodeExists($tag) || isset($used[$tag])) {
      return;
    }
    // else
    acquia_include('utility', 'ac_shortcode');
    $shortcode = self::$shortcodes[$tag];
    ac_shortcode_add_sc_files($shortcode);
    $used[$tag] = TRUE;
  }

  /**
   * check if Shortcode exists in our collection
   */
  protected function shortcodeExists($tag){
    if (!isset(self::$shortcodes[$tag])) {
      throw new AcquiaShortcodeException("Unable to locate Shortcode!");
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Set Enabled shortcodes
   * @param {array} $shortcodes
   * 		An array of enabled shortcodes list
   */
  public static function setEnabled($shortcode){
    self::$enabled = $shortcode;
  }

  /**
   * Get Enabled shortcodes
   */
  public function getEnabled(){
    return self::$enabled;
  }

  /**
   * validate shortcode info
   */
  public function validateShortcode(&$shortcode){
    if (!isset($shortcode['tag']) ||
      !isset($shortcode['title'])) {
      throw new AcquiaShortcodeException("Unable to add Shortcode to collection!");
    }

    if (!isset($shortcode['class'])) {
      $shortcode['class'] = SHORTCODE_FISHBONES;
    }else if (!class_exists($shortcode['class'])) {
      throw new AcquiaShortcodeException("Unable to Locate Shortcode class!");
    }
  }

  /**
   * Get Shortcode categories
   */
  public function getShortcodeCateggories() {
    $shortcodes_cat = &drupal_static(__FUNCTION__, NULL);

    if (!isset($shortcodes_cat)) {
      $shortcodes_cat = array();
      foreach (self::$shortcodes as $info) {
        $info['category'] = isset($info['category']) ? $info['category'] : '_other_category_';
        $shortcodes_cat[$info['category']] = $info['category'];
      }
    }
    return $shortcodes_cat;
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
  public static function load_includes($type = 'shortcodes', $hook = 'shortcode', $file = NULL) {
    // Determine implementations.
    $directories = self::_get_directories($type);
    // built-in shortcodes
    $directories['ac_shortcode'] = drupal_get_path('module', 'ac_shortcode') . '/' . $type;

    $file_list = array();
    foreach ($directories as $module => $path) {
      $file_list[$module] = drupal_system_listing("/{$file}.inc\$/", $path, 'name', 0);
    }

    // Load implementations.
    $info = array();
    foreach (array_filter($file_list) as $module => $files) {
      foreach ($files as $file) {
        include_once './' . $file->uri;
        $result = self::_process_include($module, $module . '_' . $file->name, dirname($file->uri), $hook);

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
  private static function _get_directories($plugintype = 'shortcodes') {
    $directories = array();
    foreach (module_implements('ac_shortcode_include_directory') as $module) {
      $result = module_invoke($module, 'ac_shortcode_include_directory', $plugintype);
      if (isset($result) && is_string($result)) {
        $directories[$module] = drupal_get_path('module', $module) . '/' . $result;
      }
    }
    return $directories;
  }


  /**
   * Process a single hook implementation of a wysiwyg editor.
   *
   * @param $module
   *   The module that owns the hook.
   * @param $identifier
   *   Either the module or 'wysiwyg_' . $file->name
   * @param $hook
   *   The name of the hook being invoked.
   */
  private static function _process_include($module, $identifier, $path, $hook) {
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

}

