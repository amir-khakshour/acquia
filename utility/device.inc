<?php
/**
 * @file Device related functions
 */

/**
 * Getter function to retrieve a Mobile_Detect() singleton.
 * 
 * @return object
 * Instance of Mobile_Detect(), NULL if failure.
 */
function ac_get_mobile_detect_object() {
  $detect = &drupal_static(__FUNCTION__);

  if (!isset($detect)) {   
    if (class_exists('Mobile_Detect')) {
      try {
        $detect = new Mobile_Detect();
      } catch (Exception $e) {
        $detect = NULL;
        watchdog('mobile_detect', 'Could not instantiate Mobile_Detect(): %message',
          array('%message' => $e->getMessage()), WATCHDOG_ALERT);
      }
    } else {
      $detect = NULL;
      watchdog('mobile_detect', 'Mobile_Detect() class does not exist', array(), WATCHDOG_ALERT);
    }
  }

  return $detect;
}
 
/**
 * Predicate function to test a device type.
 * 
 * This is intended to be used when the check could be based on user input.
 * The $type argument is checked against the list of valid types.  If the $type
 * is not a valid choice, an error is logged and FALSE is returned.  Otherwise
 * the test is run and returned.
 * 
 * @param string $type
 * The type to check.
 *
 * @return boolean
 * The result of the test; FALSE if the test name was invalid.
 */

function ac_check_devide_type($type = 'mobile') {
  $detect = ac_get_mobile_detect_object();
  return $detect->is($type);
}

/**
 * Get Current device type
 * 
 * @return string
 * The device type
 */

function ac_get_device_type() {
 $detect = ac_get_mobile_detect_object();
 return $detect->isMobile() ? ($detect->isTablet() ? 'tablet' : 'phone') : 'computer';
}