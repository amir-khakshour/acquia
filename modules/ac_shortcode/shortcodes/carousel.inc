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

function ac_shortcode_carousel_shortcode() {
	return array(
		'ac_carousel' => array(
			'title' => t('Carousel slider'),
			'description' => t('Creates a fancy carouFredSel slider shortcode.'),
			'form callback' => 'ac_shortcode_ac_carousel_form',
			'values process callback' => 'ac_shortcode_ac_carousel_preprocess',
			'process callback' => 'ac_shortcode_ac_carousel_process',
		),
	);
}

/**
 * Implements edit form of {{ac_fancy_carousel}} shortcode
 */
function ac_shortcode_ac_carousel_form($form, &$form_state) {
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$form['easing'] = array(
		'#type' => 'select',
		'#title' => t('Easing'),
		'#description' => t('Select easing type for animating carousel items.'),
		'#options' => acquia_easing_types(),
		'#default_value' => isset($values['easing']) ? $values['easing'] : NULL,
	);

	$form['speed'] = array(
		'#type' => 'textfield',
		'#title' => t('Scroll Speed'),
		'#field_suffix' => t('(ms)'),
		'#description' => t('Select How many times in milisecond should delay before scrolling.'),
		'#default_value' => isset($values['speed']) ? $values['speed'] : '350',
	);

	$values['auto'] = isset($values['auto']) && $values['auto'] == 'true' ? TRUE : FALSE;
	$form['auto'] = array(
		'#type' => 'checkbox',
		'#title' => t('Carousel should scroll automatically or not?'),
		'#default_value' => $values['auto'],
	);

	$values['nav'] = isset($values['nav']) && $values['nav'] == 'true' ? TRUE : FALSE;
	$form['nav'] = array(
		'#type' => 'checkbox',
		'#title' => t('Display Prev and Next navigation buttons.?'),
		'#default_value' => $values['nav'],
	);

	$values['controls'] = isset($values['controls']) && $values['controls'] == 'true' ? TRUE : FALSE;
	$form['nav'] = array(
		'#type' => 'checkbox',
		'#title' => t('Display controls buttons.?'),
		'#default_value' => $values['controls'],
	);

	$form['columns'] = array (
		'#type' => 'select',
		'#title' => t('Columns'),
		'#description' => t ( 'Number of Columns to show; e.g. 4' ),
		'#default_value' => isset($values['columns']) ? $values['columns'] : 4,
		'#options' => drupal_map_assoc ( range (1, 6) )
	);

	$form['spaced'] = array(
		'#type' => 'checkbox',
		'#title' => t('Spaced Items?'),
		'#default_value' => isset($values['spaced']) && $values['spaced'] == 'true' ? TRUE : FALSE,
	);

	$form['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => isset($values['padding']) ? $values['padding'] : acquia_variable_get('portfolio_blocks_padding', 20),
		'#states' => array(
			'visible' => array(
				':input[name="spaced"]' => array('checked' => TRUE),
			),
		),
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	return $form;
}

/**
 * preprocess {{ac_carousel}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_carousel_preprocess(&$values) {
	if (isset($values['auto']) && $values['auto'] == TRUE) {
		$values['auto'] = 'true';
	}else{
		$values['auto'] = 'false';
	}

	if (isset($values['nav']) && $values['nav'] == TRUE) {
		$values['nav'] = 'true';
	}else{
		$values['nav'] = 'false';
	}

	if (isset($values['controls']) && $values['controls'] == TRUE) {
		$values['controls'] = 'true';
	}else{
		$values['controls'] = 'false';
	}

	if (isset($values['spaced']) && $values['spaced'] == TRUE) {
		$values['spaced'] = 'true';
	}else{
		$values['spaced'] = 'false';
		$values['padding'] = 0;
	}
}

/**
 * process {{ac_fancy_carousel}} and {{ac_page_carousel}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_carousel_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
		'auto' => 'false',
		'nav' => 'false',
		'controls' => 'false',
		'easing' => '',
		'speed' => '',
		'columns' => 3,
		'padding' => 0,
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = 'clearfix';
	$attributes['class'][] = 'ac-carousel';
	$attributes['class'][] = 'owl-carousel';
	$attributes['class'][] = 'owl-theme';
	$attributes['class'][] = 'ac-appearance-grid';

	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	//---------------------------------------

	$attributes += acquia_data_arr_to_tag_arr(array('auto' => $auto, 'easing' => $easing, 'speed' => $speed, 'columns' => $columns, 'padding' => $padding));

	if (isset($attrs['controls']) && $attrs['controls'] == 'true') {
		$attributes['data-controlnav'] = 'true';
		$attributes['class'][]= 'ac-pager-enabled';
	}else{
		$attributes['data-controlnav'] = 'false';
	}

	if (isset($attrs['nav']) && $attrs['nav'] == 'true') {
		$attributes['data-directionnav'] = 'true';
		$attributes['class'][]= 'ac-prev-next-enabled';
	}else{
		$attributes['data-directionnav'] = 'false';
	}

	$attributes['class'] = implode(' ', $attributes['class']);

	drupal_add_library('acquia', 'owl.carousel');
	$out  = theme('acquia_preloader');
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</div>';
	return $out;
}