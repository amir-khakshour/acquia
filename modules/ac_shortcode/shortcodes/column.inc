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
function ac_shortcode_column_shortcode() {
	return array(
		'ac_col' => array(
			'title' => t('Column'),
			'description' => t('Creates sections of container in variable width.'),
			'form callback' => 'ac_shortcode_ac_col_form',
			'process callback' => 'ac_shortcode_ac_col_process',
		),

		'ac_col_inner' => array(
			'title' => t('Column Inner'),
			'description' => t(''),
			'process callback' => 'ac_shortcode_ac_col_process',
			'form callback' => 'ac_shortcode_ac_col_form',
			'hidden' => TRUE,
			"enabled" => array('ac_col' => TRUE),
		),
		'vc_column' => array(
			'title' => t('Column - Depricated'),
			'description' => t('Creates sections of container in variable width.'),
			'form callback' => 'ac_shortcode_ac_col_form',
			'process callback' => 'ac_shortcode_ac_col_process',
		),
		'vc_column_inner' => array(
			'title' => t('Column Inner'),
			'description' => t(''),
			'process callback' => 'ac_shortcode_ac_col_process',
			'form callback' => 'ac_shortcode_ac_col_form',
			'hidden' => TRUE,
			"enabled" => array('vc_column' => TRUE),
		),
	);
}


/**
 * Implements edit form of {{ac_col}} shortcode
 */
function ac_shortcode_ac_col_form($form, $form_state) {
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

	acquia_include('fields');
	acquia_include('content');

	$settings = array(
		'title' => t('Column'),
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['class'] = array(
		'#type' => 'textfield',
		'#title' => t('Extra class name'),
		'#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
		'#default_value' => isset($values['class']) ? $values['class'] : '',
	);

	$form['width'] = array(
		'#type' => 'value',
		'#value' => isset($values['width']) ? $values['width'] : '1/1',
	);

	if (isset($values['first'])) {
		$form['first'] = array(
			'#type' => 'value',
			'#value' => isset($values['first']) ? $values['first'] : TRUE,
		);
	}

	if (isset($values['last'])) {
		$form['last'] = array(
			'#type' => 'value',
			'#value' => isset($values['last']) ? $values['last'] : TRUE,
		);
	}

	if (isset($values['odd'])) {
		$form['odd'] = array(
			'#type' => 'value',
			'#value' => isset($values['odd']) ? $values['odd'] : TRUE,
		);
	}

	if (isset($values['even'])) {
		$form['even'] = array(
			'#type' => 'value',
			'#value' => isset($values['even']) ? $values['even'] : TRUE,
		);
	}

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * @deprecated since 1.1.7
 * @param $attrs
 * @param null $text
 * @param string $shortcode
 */
function ac_shortcode_vc_column_process($attrs, $text = null, $shortcode = '') {
	return ac_shortcode_ac_col_process($attrs, $text, $shortcode);
}


/**
 * process {{ac_col_text}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_col_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('options');
	acquia_include('utility', 'ac_composer');
	$attrs = (array)$attrs;
	$shortcode = str_replace('vc_column', 'ac_col', $shortcode);
	$sc_name = str_replace('_', '-', $shortcode);

	$width = '1/1';
	if (isset($attrs['width'])) {
		$width = $attrs['width'];
	}
	if (in_array($width, array_keys(acquia_column_width_to_class()))) {
		$width_to_class = acquia_column_width_to_class();
		$width = $width_to_class[$width];
	}
	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'clearfix';
	$classes[] = $sc_name != 'ac-col' ? 'ac-col' : null;
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$classes[] = isset($attrs['width']) ? str_replace('_', '-', $width) : NULL;
	$classes[] = in_array('first', array_keys($attrs)) ? 'first' : null;
	$classes[] = in_array('last', array_keys($attrs)) ? 'last' : null;
	$classes[] = in_array('odd', array_keys($attrs)) ? 'odd' : null;
	$classes[] = in_array('even', array_keys($attrs)) ? 'even' : null;

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes['class'] = $classes;

	// Animate data 
	$attributes += acquia_get_anim_data_by_attrs($attrs);

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '  <div class="col-inner clearfix">';
	$out .= '		'.$text;
	$out .= '  </div>';
	$out .= '</div>';

	return $out;
}

 
