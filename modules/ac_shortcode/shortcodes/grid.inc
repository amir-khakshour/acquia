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

function ac_shortcode_grid_shortcode() {
	return array(
		'ac_grid' => array(
			'title' => t('DiamondLayers Grid'),
			'description' => t('Creates a Grid Layout in element children.'),
			'form callback' => 'ac_shortcode_ac_grid_form',
			'values process callback' => 'ac_shortcode_ac_grid_preprocess',
			'process callback' => 'ac_shortcode_ac_grid_process',
		),
	);
}

/**
 * Implements edit form of {{ac_fancy_grid}} shortcode
 */
function ac_shortcode_ac_grid_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$form['columns'] = array (
		'#type' => 'select',
		'#title' => t('Columns'),
		'#description' => t ( 'Number of Columns for grid layout; e.g. 4' ),
		'#default_value' => isset($values['columns']) ? $values['columns'] : 4,
		'#options' => drupal_map_assoc ( range (1, 6) )
	);

	$form['break'] = array (
		'#type' => 'textfield',
		'#title' => t('Responsive Width'),
		'#description' => t('By default 150px.'),
		'#default_value' => isset($values['break']) ? $values['break'] : 150,
	);

	$form['borders'] = array (
		'#type' => 'checkbox',
		'#title' => t('Enable Borders around grid items?'),
		//'#description' => t ( 'Number of Columns for grid layout; e.g. 4' ),
		'#default_value' => isset($values['borders']) && $values['borders'] == 'true' ? TRUE : FALSE,
	);

	$settings = array(
		'title' => t('Grid Items'),
		'delay_enabled' => TRUE
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
		$settings['delay'] = $values['dely'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	return $form;
}

/**
 * preprocess {{ac_grid}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_grid_preprocess(&$values) {
	if (isset($values['borders']) && $values['borders'] == TRUE) {
		$values['borders'] = 'true';
	}else{
		unset($values['borders']);
	}

	if (isset($values['break']) && $values['break'] == 150) {
		unset($values['break']);
	}
}

/**
 * process {{ac_fancy_grid}} and {{ac_page_grid}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_grid_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
		'columns' => '4',
		'break' => '150',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = isset($attrs['borders']) && $attrs['borders'] == 'true' ? 'ac-border-enabled' : 'ac-no-borders';
	$attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$attributes['class'][] = $_attrs['columns'] == 1 ? 'ac-full-width' : null;
	$attributes['class'][] = 'clearfix';

	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	//---------------------------------------

	acquia_include('utility', 'ac_shortcode');
	$_attrs['cols-width'] = ac_shortcode_col_to_width($_attrs['columns']);

	$attributes += acquia_data_arr_to_tag_arr($_attrs);

	// Animate data
	if (isset($attrs['animate'])) {
		$attributes += acquia_get_anim_data_by_attrs($attrs);
		$attributes['data-anim-childs'] = '.ac-grid-item';
	}

	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</div>';

	return $out;
}