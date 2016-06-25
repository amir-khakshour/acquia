<?php
/**
 * Slider slider core class definition
 */
define ('AC_SLIDERS_TABLE', 'acquia_sliders');
define ('AC_SLIDES_TABLE', 'acquia_slides');
/**
 * @file Classes file
 */

class acquiaSlider {
  public $slid;
  public $title;
  public $description;
  public $machine_name;
  public $type;
  public $settings;

  public function db_fields() {
    return array('title', 'description', 'machine_name', 'type', 'settings');
  }

  public function initialize() {
    if (is_string($this->settings)) {
      $this->settings = unserialize($this->settings);
    };
  }
  
  /**
   * Save existing slider data
   */
  public function save() {
    $response = FALSE;
    $fields = array();
    if ($this->title == NULL || $this->title == '') {
      return $response;
    }

    foreach ($this->db_fields() as $field) {
      $fields[$field] = $this->{$field};
    }

    if (is_array($fields['settings'])) {
      $fields['settings'] = serialize($fields['settings']);
    }

    if ($this->slid) {
      $response = db_update('acquia_sliders')
      ->fields($fields)
      ->condition('slid', $this->slid)
      ->execute();
    }
    else {
      $slid = db_insert(AC_SLIDERS_TABLE)
      ->fields($fields)
      ->execute();

      if ($slid > 0) {
        $this->slid = $slid;
        $response = TRUE;
      }
    }

    return $response;
  }
  
  /**
   * Create New Slider
   */
   public static function create($title, $description = NULL, $type = NULL, $settings = NULL, $machine_name = NULL) {
    # Create new acquiaSlider object
    $slider = new acquiaSlider();
    $slider->title = $title;
    $slider->description = $description;
    $slider->machine_name = ($machine_name) ? $machine_name : uniqid('ac-slider-');
    $slider->type = $type;
    $slider->settings = $settings;

    if ($slider->save()) {
      return $slider;
    }

    return NULL;
  }

  public static function get_all() {
    $results = db_select('{'.AC_SLIDERS_TABLE.'}', 'acs')
    ->fields('acs')
    ->execute()
    ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlider');

    if (!count($results)) {
      return array();
    }

    # Run object initialize
    foreach ($results as &$slider) {
      $slider->initialize();
      $slider->initialize();
    }

    # Return list menus
    return $results;
  }

  public static function get_by_id($slid) {
    $results = db_select('{'.AC_SLIDERS_TABLE.'}', 'acs')
    ->fields('acs')
    ->condition('slid', $slid)
    ->execute()
    ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlider');

    if (!count($results)) {
      return array();
    }

    # Run object initialize
    foreach ($results as &$slider) {
      $slider->initialize();
    }

    # Return list menus
    return array_shift($results);
  }

  public static function get_by_machine_name($machine_name) {
    $results = db_select('{'.AC_SLIDERS_TABLE.'}', 'acs')
      ->fields('acs')
      ->condition('machine_name', $machine_name)
      ->execute()
      ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlider');

    if (!count($results)) {
      return array();
    }

    # Run object initialize
    foreach ($results as &$slider) {
      $slider->initialize();
    }

    # Return list menus
    return $results;
  }

  public static function get_by_ids($slids) {
    $results = db_select('{'.AC_SLIDERS_TABLE.'}', 'acs')
      ->fields('acs')
      ->condition('slid', $slids, 'IN')
      ->execute()
      ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlider');

    if (!count($results)) {
      return array();
    }

    # Run object initialize
    foreach ($results as &$slider) {
      $slider->initialize();
    }

    # Return list menus
    return $results;
  }

  public static function delete($slid) {
    # Delete all slides of slider
    acquiaSlide::delete_by_slider($slid);

    # Delete slider
    return db_delete(AC_SLIDERS_TABLE)
      ->condition('slid', $slid)
      ->execute();
  }
  
  /**
   * prepare slide global settings before saving to DB
   */
  public static function prepare_settings($settings) {
    $defaults = self::get_default_settings();
    // remove other values
    foreach (array_keys($defaults) as $key) {
      if (array_key_exists($key, $settings)) {
        $defaults[$name] = $settings[$name];
      }
    }
    return $defaults;
  }
	
  public static function get_default_settings($key = NULL) {
    static $default_settings = array(
    );

    if ($key) {
      return $default_settings[$key];
    }

    return $default_settings;
  }
}

/**
 * acquiaSlide class
 */
class acquiaSlide {
  public $sid;
  public $slid;
  public $position;
  public $settings;
  public $layers;

  public function db_fields() {
    return array('slid', 'position', 'settings', 'layers');
  }

  public function initialize() {
    if (is_string($this->settings)) {
      $this->settings = unserialize($this->settings);
    }

    if (is_string($this->layers)) {
      $this->layers = unserialize($this->layers);
    }
  }

  public function save() {
    $fields = array();
    foreach ($this->db_fields() as $field_name) {
      $fields[$field_name] = $this->{$field_name};
    }

    if (is_array($fields['layers'])) {
      $fields['layers'] = serialize($fields['layers']);
    }

    if (is_array($fields['settings'])) {
      $fields['settings'] = serialize($fields['settings']);
    }

    if ($this->sid) {
      db_update(AC_SLIDES_TABLE)
        ->fields($fields)
        ->condition('sid', $this->sid)
        ->execute();
    }
    else {
      db_insert(AC_SLIDES_TABLE)
        ->fields($fields)
        ->execute();
    }
  }

  public static function create($slid, $position, $settings = NULL, $layers = NULL) {
    $slider = acquiaSlider::get_by_id($slid);
    if ($slider == NULL) {
      return;
    }

    $new_slide = new acquiaSlide();
    $new_slide->slid = $slid;
    $new_slide->position = $position;
    $new_slide->settings = $settings;
    $new_slide->layers = $layers;

    $new_slide->save();
  }

  public static function get_by_slider_id($slid) {
    $results = db_select(AC_SLIDES_TABLE, 'acs')
    ->fields('acs')
    ->condition('slid', $slid)
    ->orderBy('position')
    ->execute()
    ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlide');

    if (count($results) > 0) {
      foreach ($results as &$slide) {
        $slide->initialize();
      }

      return $results;
    }

    return array();
  }

  public static function get_by_sliders($slids) {
    $results = db_select(AC_SLIDES_TABLE, 'acs')
      ->fields('acs')
      ->condition('slid', $slids, 'IN')
      ->orderBy('position')
      ->execute()
      ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlide');

    if (count($results) > 0) {
      foreach ($results as &$slide) {
        $slide->initialize();
      }

      return $results;
    }

    return array();
  }

  public static function get($sid) {
    $output = NULL;
    $results = db_select(AC_SLIDES_TABLE, 'acs')
      ->fields('acs')
      ->condition('sid', $sid)
      ->execute()
      ->fetchAll(PDO::FETCH_CLASS, 'acquiaSlide');

    if (count($results) > 0) {
      $output = array_shift($results);
      $output->initialize();
    }

    return $output;
  }

  public static function delete($sid) {
    return db_delete(AC_SLIDES_TABLE)
      ->condition('sid', $sid)
      ->execute();
  }

  public static function delete_by_slider($slid) {
    return db_delete(AC_SLIDES_TABLE)
      ->condition('slid', $slid)
      ->execute();
  }

  public static function delete_after($slid, $sid) {
    return db_delete(AC_SLIDES_TABLE)
      ->condition('slid', $slid, '=')
      ->condition('position', $sid, '>=')
      ->execute();
  }
	
  public static function get_default_settings($key = NULL) {
    static $default_settings = array(
      'background_image' => -1,
      'timelinewidth' => 80,
      'custom_thumbnail' => -1,
    );

    if ($key && $key != '') {
      return $default_settings[$key];
    }

    return $default_settings;
  }
}

class acquiaCommon {
  public static $in_effects = array(
    "fadeIn",
    "fadeInUp",
    "fadeInDown",
    "fadeInLeft",
    "fadeInRight",
    "fadeInUpBig",
    "fadeInDownBig",
    "fadeInLeftBig",
    "fadeInRightBig",
    "bounceIn",
    "bounceInDown",
    "bounceInUp",
    "bounceInLeft",
    "bounceInRight",
    "rotateIn",
    "rotateInDownLeft",
    "rotateInDownRight",
    "rotateInUpLeft",
    "rotateInUpRight",
    "lightSpeedIn",
    "rollIn",
  );

  public static $out_effects = array(
    "fadeOut",
    "fadeOutUp",
    "fadeOutDown",
    "fadeOutLeft",
    "fadeOutRight",
    "fadeOutUpBig",
    "fadeOutDownBig",
    "fadeOutLeftBig",
    "fadeOutRightBig",
    "bounceOut",
    "bounceOutDown",
    "bounceOutUp",
    "bounceOutLeft",
    "bounceOutRight",
    "rotateOut",
    "rotateOutDownLeft",
    "rotateOutDownRight",
    "rotateOutUpLeft",
    "rotateOutUpRight",
    "lightSpeedOut",
    "rollOut",
  );

  public static $default_layers = array(
    'text' => array(
      'type' => 'text',
      'width' => 100,
      'height' => 20,
      'left' => 0,
      'top' => 0,
      'starttime' => 0,
      'stoptime' => 30,
      'startani' => 'none',
      'stopani' => 'none',
      'style' => 'style1',
      'zindex' => 1000,
      'title' => 'Text',
      'background' => '',
      'backgroundtransparent' => 100,
      'fontsize' => '',
      'fontstyle' => '',
      'textalign' => '',
      'color' => '',
      'transparent' => 100,
    ),
    'image' => array(
      'type' => 'image',
      'width' => 100,
      'height' => 20,
      'left' => 0,
      'top' => 0,
      'starttime' => 0,
      'stoptime' => 30,
      'startani' => 'none',
      'stopani' => 'none',
      'style' => 'style1',
      'zindex' => 1000,
      'title' => '',
      'fileid' => '',
      'background' => '',
      'backgroundtransparent' => 100,
      'transparent' => 100,
    ),
    'video' => array(
      'type' => 'video',
      'width' => 100,
      'height' => 20,
      'left' => 0,
      'top' => 0,
      'starttime' => 0,
      'stoptime' => 30,
      'startani' => 'none',
      'stopani' => 'none',
      'style' => 'style1',
      'zindex' => 1000,
      'title' => '',
      'fileid' => '',
      'background' => '',
      'backgroundtransparent' => 100,
      'transparent' => 100,
    ),
  );
}
