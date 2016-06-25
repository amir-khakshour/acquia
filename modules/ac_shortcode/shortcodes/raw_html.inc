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

function ac_shortcode_raw_html_shortcode() {
	return array(
		'ac_raw_html' => array(
			'title' => t('Raw HTML'),
			'description' => t('Adds HTML to page.'),
			'form callback' => 'ac_shortcode_ac_raw_html_form',
			'values process callback' => 'ac_shortcode_ac_raw_html_preprocess',
			'process callback' => 'ac_shortcode_ac_raw_html_process',
			'category' => 'structure',
		),
	);
}

/**
 * Implements edit form of {{ac_raw_html}} shortcode
 */
function ac_shortcode_ac_raw_html_form($form, &$form_state) {
	$cid = &drupal_static(__FUNCTION__);

	// saving and restoring cid we we use don't want
	//	to rebuild after adding new tabs
	if (isset($form_state['cid'])) {
		$cid = $form_state['cid'];
	}else if (!isset($cid)) {
		$cid = uniqid('content_');
		$form_state['cid'] = $cid;
	}

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Raw HTML'),
		'#description' => t('Enter your HTML content.'),
		'#default_value' => isset($values['content']) ?
			rawurldecode(base64_decode(strip_tags($values['content']))) :
			array(),
		'#format' => NULL,
		'#rows' => 15,
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

function ac_shortcode_ac_raw_html_preprocess(&$values){
	foreach ($values['text_format_cid'] as $cid => $key) {
		if (isset($values[$cid]) && is_array($values[$cid]) && isset($values[$cid]['value'])) {
			$values[$cid]['value'] = base64_encode($values[$cid]['value']);
		}
	}
}

/**
 * process {{ac_raw_html}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_raw_html_process($attrs, $text = null, $shortcode = '') {
	//acquia_include('content');
	//$_attrs = ac_shortcode_attrs(array(
	//	'content' => 'shadow',
	//	'title_align' => '',
	//	), $attrs);
	//
	//extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
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

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '  '.rawurldecode(base64_decode(strip_tags($text)));
	$out .= '</div>';

	return $out;
}
