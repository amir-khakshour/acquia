<?php
/**
 * @file
 *  DiamondLayers Shortcode Abstract classes
 */


 /**
	* Define acquia shortcode model dummy name
	*/
 if (!defined('ACQUIA_SHORTCODE_MODEL_DUMMY_CLASS')) {
		define('ACQUIA_SHORTCODE_MODEL_DUMMY_CLASS', 'AcquiaShortcodeDummy');
 }

/**
 * AcquiaShortcodeException class.
 */
class AcquiaShortcodeException extends Exception {
	public $arguments;

	function __construct($message, $code = 0, $arguments = array()) {
		parent::__construct($message, $code);
		$this->arguments = $arguments;
	}
}

