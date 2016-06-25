<?php
/**
 * @file shortcode defenition of  text_block
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
function ac_shortcode_text_block_shortcode() {
	return array(
		'ac_col_text' => array(
			"title" => t("Text"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_col_text_form',
			'process callback' => 'ac_shortcode_ac_col_text_process',
			'values process callback' => 'ac_shortcode_ac_col_text_preprocess',
			'sitewide settings' => 'ac_shortcode_ac_col_text_sitewide_settings',
			'category' => 'content',
		),
		'vc_column_text' => array(
			"title" => t("Text Block - Deprecated"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_col_text_form',
			'process callback' => 'ac_shortcode_ac_col_text_process',
			'values process callback' => 'ac_shortcode_ac_col_text_preprocess',
			'sitewide settings' => 'ac_shortcode_ac_col_text_sitewide_settings',
			'category' => 'content',
		),
	);
}

/**
 * Implements edit form of {{ac_col_text}} shortcode
 */
function ac_shortcode_ac_col_text_form($form, $form_state) {
	acquia_include('options');

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

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Content'),
		'#description' => t('Enter the text block content here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Font size'),
		'#description' => t('Select size of text block.'),
		'#default_value' => isset($values['font']) ? $values['font'] : NULL,
		'#options' => acquia_font_sizes(),
	);

	$ops = array_merge(array('inherit' => t('Inherit'), 'custom' => t('Custom Color')), acquia_skins_list());
	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('text Color'),
		'#description' => t('Choose a text color for your text block here.'),
		'#default_value' => isset($values['color']) ? $values['color'] : '',
		'#options' => $ops,
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom text Color'),
		'#description' => t('Select a custom text color for your text block here.'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);

	$settings = array(
		'title' => t('Text Block'),
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

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * Process {{ac_callout}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_col_text_preprocess(&$values) {
	if (isset($values['color']) && $values['color'] !='custom') {
		if ($values['color'] == 'inherit') {
			unset($values['color']);
		}
		unset($values['custom_color']);
	}
}

/**
 * @deprecated since 1.1.7
 * @param $attrs
 * @param null $text
 * @param string $shortcode
 */
function ac_shortcode_vc_column_text_process($attrs, $text = null, $shortcode = '') {
	return ac_shortcode_ac_col_text_process($attrs, $text, $shortcode);
}


/**
 * process {{ac_col_text}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_col_text_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$shortcode = 'ac_col_text';
	$sc_name = str_replace('_', '-', $shortcode);

	$attrs_to_class = array();

	$styles = array();
	if (isset($attrs['color']) && $attrs['color'] != 'custom') {
		$attrs_to_class[] = 'color';
	}else if (isset($attrs['custom_color'])) {
		$styles['color'] = $attrs['custom_color'];
	}

	if (isset($attrs['font']) && !empty($attrs['font'])) {
		$attrs_to_class[] = 'font';
	}

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args($attrs_to_class, $attrs, CHECK_LENGTH);
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

	$attributes['class'] = $classes;
	$attributes['style'] = acquia_style_arr_to_tag(	$styles );

	// Animate data 
	$attributes += acquia_get_anim_data_by_attrs($attrs);

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</div>';

	return $out;
}
