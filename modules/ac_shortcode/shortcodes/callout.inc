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

// Define Callout Button prefix used with form processing
define('CALLOUT_BTN_PREFIX', 'btn_');

function ac_shortcode_callout_shortcode() {
	return array(
		'ac_callout' => array(
			'title' => t('callout'),
			'description' => t('Creates a nice call to action box.'),
			'form callback' => 'ac_shortcode_ac_callout_form',
			'values process callback' => 'ac_shortcode_ac_callout_preprocess',
			'process callback' => 'ac_shortcode_ac_callout_process',
			'sitewide settings' => 'ac_shortcode_ac_callout_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_callout}} shortcode
 */
function ac_shortcode_ac_callout_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');

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
		'#title' => t('Content'),
		'#description' => t('Enter the callout block content here.'),
		'#default_value' => isset($values['content']) ?
			rawurldecode(base64_decode(strip_tags($values['content']))) :
			array(),
		'#format' => NULL,
		'#rows' => 15,
	);


	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Font size'),
		'#description' => t('Size of callout block text.'),
		'#default_value' => isset($values['font']) ? $values['font'] : NULL,
		'#options' => acquia_font_sizes(),
	);

	$form['text_align'] = array(
		'#type' => 'select',
		'#title' => t('Text align'),
		'#description' => t('Choose the alignment of your callout block text here'),
		'#default_value' => isset($values['text_align']) ? $values['text_align'] : (acquia_variable_get('doc_direction') == 'LTR' ? 'left' : 'right'),
		'#options' => acquia_align_list(),
	);

	$form['background'] = array(
		'#type' => 'select',
		'#title' => t('Background & Border'),
		'#description' => t('Select the border and background of your callout block here.'),
		'#default_value' => isset($values['background']) ? $values['background'] : NULL,
		'#options' => array(
			'none' => t('None'),
			'plain' => t('Border enabled, no background'),
			'plain_bg' => t('Border & default background enabled'),
			'fancy_bg' => t('Border & Custom background enabled'),
			'fancy' => t('Border & fancy background enabled'),
		),
	);

	$ops = array_merge(array('theme_default' => t('Theme Default'), 'custom' => t('Custom Color')), acquia_skins_list());
	add_default_option($ops);

	$form['bg_color'] = array(
		'#type' => 'select',
		'#title' => t('Callout Background Color'),
		'#description' => t('Choose a Background color for your Callout block here.'),
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : '',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="background"]' => array('value' => 'fancy_bg'),
			),
		),
	);

	$form['custom_bg'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Callout Background Color'),
		'#description' => t('Select a custom background color for your Callout block here.'),
		'#default_value' => isset($values['custom_bg']) ? $values['custom_bg'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="bg_color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Callout text Color'),
		'#description' => t('Choose a text color for your Callout block here.'),
		'#default_value' => isset($values['color']) ? $values['color'] : '',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="background"]' => array('value' => 'fancy_bg'),
			),
		),
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Callout text Color'),
		'#description' => t('Select a custom text color for your Callout block here.'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="background"]' => array('value' => 'custom'),
			),
		),
	);

	$form['border'] = array(
		'#type' => 'select',
		'#title' => t('Border'),
		'#description' => t('Select the border type of your callout block here.'),
		'#default_value' => isset($values['border']) ? $values['border'] : NULL,
		'#options' => acquia_callout_border_types(),
		'#states' => array(
			'visible' => array(
				':input[name="background"]' => array('value' => 'fancy'),
			),
			'enabled' => array(
				':input[name="background"]' => array('value' => 'fancy'),
			),
		),
	);

	$form['btn_align'] = array(
		'#type' => 'select',
		'#title' => t('Button alignment'),
		'#description' => t('Select the alignment of your callout Button here.'),
		'#default_value' => isset($values['btn_align']) ? $values['btn_align'] : NULL,
		'#options' => acquia_callout_btn_align_list(),
	);

	$settings = array(
		'title' => t('Callout Block'),
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
	}
	// add animate fields
	acquia_field_animate($form, $settings);

	$form['btn'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable Callout Button?'),
		'#default_value' => isset($values['btn']) && $values['btn'] == 'true' ? TRUE : FALSE,
	);

	// Callout Button
	$tag = 'ac_button'; // button shortcode
	$tag_info = ac_shortcode_get_sc_info($tag);
	ac_shortcode_add_sc_files($tag_info);

	$form['callout_btn'] = array(
		'#type' => 'fieldset',
		'#title' => t('Callout Button'),
		'#collapsible' => TRUE,
		'#states' => array(
			'disabled' => array(
				':input[name="btn"]' => array('checked' => FALSE),
			),
			'invisible' => array(
				':input[name="btn"]' => array('checked' => FALSE),
			),
		),
	);

	$btn_form_clone = array();
	$btn_form = call_user_func_array($tag_info['form callback'], array(array() , $form_state, CALLOUT_BTN_PREFIX));
	$form['callout_btn'] += $btn_form;

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
 * Process {{ac_callout}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_callout_preprocess(&$values) {
	if (isset($values['type']) && $values['type'] !='go_top') {
		unset($values['gotop_title']);
	}

	if (isset($values['type']) && $values['type'] =='invisible') {
		unset($values['width']);
	}

	if (isset($values['background']) && $values['background'] !='fancy_bg') {
		unset($values['bg_color']);
		unset($values['custom_bg']);

		unset($values['color']);
		unset($values['custom_color']);
	}

	if (isset($values['bg_color']) && $values['bg_color'] !='custom') {
		unset($values['custom_bg']);
	}

	foreach ($values['text_format_cid'] as $cid => $key) {
		if (isset($values[$cid]) && is_array($values[$cid]) && isset($values[$cid]['value'])) {
			$values[$cid]['value'] = base64_encode($values[$cid]['value']);
		}
	}

	if (isset($values['btn']) && $values['btn'] == TRUE) {
		$values['btn'] = 'true';
	}else{
		$values['btn'] = 'false';
	}
}

/**
 * process {{ac_callout}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_callout_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'font' => '',
		'text_align' => 'left',
		'background' => 'fancy',
		'border' => 'rounded',
		'btn_align' => 'left',
		'bg_color' => '',
		'color' => '',
		'btn' => 'true',
	), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$_attrs['bg_color'] = ($_attrs['bg_color'] == 'sw') ? acquia_theme_get_settings('ac_callout_bg_color', null, 'shortcodes') : $_attrs['bg_color'];

	$classes = array();
	$classes[] = $sc_name;
	$classes[]= acquia_get_class_by_args(array('text_align', 'background', 'border', 'btn_align', 'bg_color', 'color', 'font'), $_attrs, CHECK_LENGTH);
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
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

	$styles = array();
	if (isset($attrs['custom_bg'])) {
		$styles['background-color'] = $attrs['custom_bg'];
		$attributes['style'] = acquia_style_arr_to_tag(	$styles );
	}
	// Animate data 
	$attributes += acquia_get_anim_data_by_attrs($attrs);

	if ($btn == 'true') {
		// Callout Button
		$tag = 'ac_button'; // button shortcode
		$tag_info = ac_shortcode_get_sc_info($tag);
		ac_shortcode_add_sc_files($tag_info);
		if (isset($tag_info['process callback']) && function_exists($tag_info['process callback'])){
			$callout_btn = call_user_func($tag_info['process callback'], $attrs, isset($attrs['btn_content']) ? $attrs['btn_content'] : t('Click me'), $tag);
		}
	}

	if ($text) {
		$text = check_markup(base64_decode($text), 'full_html');
	}

	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= '  <div class="'.$sc_name.'-content">';
	$out .= '		'.	$text;
	$out .= '  </div>';
	if ($btn == 'true') {
		$out .= '  <div class="'.$sc_name.'-button">';
		$out .= '		'.	$callout_btn;
		$out .= '  </div>';
	}
	$out .= '</div>';

	return $out;
}

/**
 * Defines {{ac_callout}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_callout_sitewide_settings() {
	acquia_include('options');
	return array(
		'ac_callout_bg_color' => array(
			'#type' => 'select',
			'#title' => t('background color'),
			'#description' => t('Select a default background color for your Callout block here.'),
			'#options' => acquia_skins_list(),
		),
	);
}