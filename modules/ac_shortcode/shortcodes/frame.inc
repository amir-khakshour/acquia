<?php
/**
 * @file shortcode defenition of frame
 */
/**
 * Implements ac_shortcode_SHORTCODE_shortcode()
 * @return an array of shortcodes defenition
 * 
 * 	Shortcode settings array consists of below values:
 * 	 %tag : Shortcode tag
 * 	 %title: Shortcode title
 * 	 %description: Shortcode description
 * 	 %category: An array of categories that this shortcode belongs to
 * 	 %class: A class name that contains methods to process the tag
 * 	 %file: Shortcode class file name
 * 	 %path: Relative path to shortcode class file
 * 	 %nested shortcodes: Array of shortcode tags that can be nested
 *    	in this shortcode and processed as a value of current shortcode
 * 	 %hidden: A Boolean value indicating whether this shortcode must
 *    	be hidden in the shortcodes list or not. it works in conjunction
 *    	with %enabled key.
 * 	 %enabled: Array of shortcode tags and a Boolean value that represents
 *    	the circumstances that the shortcode can be enabled based on the
 *    	status of other shortcodes.
 */

function ac_shortcode_frame_shortcode() {
	 return array(
		'ac_frame' => array(
			'title' => t('Frame'),
			'description' => t('frame enabled image.'),
			'form callback' => 'ac_shortcode_ac_frame_form',
			//'values process callback' => 'ac_shortcode_ac_frame_preprocess',
			'process callback' => 'ac_shortcode_ac_frame_process',
		),
	 );
}

/**
 * Implements edit form of {{ac_frame}} shortcode
 */
function ac_shortcode_ac_frame_form($form, &$form_state) {
	 /** Global shortcode elements **/
	$form['class'] = array(
		'#type' => 'textfield',
		'#title' => t('Extra class name'),
		'#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
		'#default_value' => isset($values['class']) ? $values['class'] : '',
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	 
	return $form;
}

/**
 * preprocess {{ac_frame}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_frame_preprocess(&$values) {

}

/**
 * process {{ac_frame}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_frame_process($attrs, $text = null, $shortcode = '') {
	//acquia_include('content');
	//acquia_include('utility');
	//
	//$_attrs = ac_shortcode_attrs(array(
	//	'fid'      => '',
	//	'loop'     => 'false', /* Enable repeating Frame: True/False */
	//	'autoplay' => 'false', /* Automatically start Frame: True/False */
	//	'preload'  => 'false', /* Preload Frame before playing: True/False */
	//	'type'  => '',
	//), $attrs);
	//extract($_attrs);
  return '<div class="ac-frame ac-frame-on">' . $text .'</div>';
}