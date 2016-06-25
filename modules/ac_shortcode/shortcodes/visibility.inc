<?php
/**
 * @file shortcode defenition of audio
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

function ac_shortcode_visibility_shortcode() {
	return array(
		'ac_visibility' => array(
			'title' => t('visibility'),
			'description' => t('show or hide various pieces of information for different devices.'),
			'form callback' => 'ac_shortcode_ac_visibility_form',
			'values process callback' => 'ac_shortcode_ac_visibility_preprocess',
			'process callback' => 'ac_shortcode_ac_visibility_process',
		),
	);
}

/**
 * Implements edit form of {{ac_visibility}} shortcode
 */
function ac_shortcode_ac_visibility_form($form, &$form_state) {
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('visibility type'),
		'#description' => t('Here you can set the default visiblity of elements inside of this visiblity block.'),
		'#options' => acquia_visibility_list(),
		'#default_value' => isset($values['type']) ? $values['type'] : '',
	);

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
 * Process {{ac_visibility}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_visibility_preprocess(&$values) {

}

/**
 * process {{ac_visibility}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_visibility_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'type' => 'hidden-desktop',
	), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('type'), $_attrs, CHECK_LENGTH);
	$classes[] = 'clearfix';

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;

	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '  '.$text;
	$out .= '</div>';

	return $out;
}