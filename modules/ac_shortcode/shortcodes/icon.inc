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

function ac_shortcode_icon_shortcode() {
	return array(
		'ac_font_icon' => array(
			'title' => t('Font Icon'),
			'description' => t('Shortcode which creates a font icon.'),
			'form callback' => 'ac_shortcode_ac_font_icon_form',
			'values process callback' => 'ac_shortcode_ac_icon_preprocess',
			'process callback' => 'ac_shortcode_ac_font_icon_process',
		),
	);
}

/**
 * Implements edit form of {{ac_font_icon}} shortcode
 */
function ac_shortcode_ac_font_icon_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Icon'),
		'default' => $values['icon'],
		'parents' => array(),
		'animate' => isset($values['animate']) ? $values['animate'] : TRUE,
		'when' => isset($values['when']) ? $values['when'] : FALSE,
		'always_enabled' =>TRUE,
	));

	$ops = acquia_icon_types();
	add_default_option($ops);

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('Icon type?'),
		//'#description' => t('Select the Icon type here.'),
		'#default_value' => isset($values['type']) ? $values['type'] : '',
		'#options' => $ops,
	);

	$values['subtle'] = isset($values['subtle']) && $values['subtle'] == 'true' ?  TRUE : FALSE;
	$form['subtle'] = array(
		'#type' => 'checkbox',
		'#title' => t('Subtle style'),
		'#default_value' => isset($values['subtle']) ? $values['subtle'] : FALSE,
	);

	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Icon Color'),
		'#description' => t('Choose a color for your icon here'),
		'#default_value' => isset($values['color']) ? $values['color'] : '',
		'#options' => array_merge(array(
			'' => t('Theme Color'),
			'custom' => t('Custom Color'),
		),
			acquia_skins_list())
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom icon color'),
		'#description' => t('Select a custom color for your icon here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['bg_color'] = array(
		'#type' => 'select',
		'#title' => t('background Color'),
		'#description' => t('Choose a color for your circled icon background here'),
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : 'black',
		'#options' => array_merge(array(
			'theme-color' => t('Theme Color'),
			'custom' => t('Custom Color'),
		),
			acquia_skins_list()),
		'#states' => array(
			'invisible' => array(
				':input[name="type"]' => array('value' => 'simple'),
			),
			'disabled' => array(
				':input[name="type"]' => array('value' => 'simple'),
			),
		),
	);

	$form['custom_bg_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Background Color'),
		'#description' => t('Select a custom background color for your circled icon background here'),
		'#default_value' => isset($values['custom_bg_color']) ? $values['custom_bg_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="bg_color"]' => array('value' => 'custom'),
			),
			'enabled' => array(
				':input[name="bg_color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['size'] = array(
		'#type' => 'select',
		'#title' => t('Icon Size'),
		'#description' => t('select the size of icon.'),
		'#default_value' => isset($values['size']) ? $values['size'] : 'medium',
		'#options' => acquia_sizes_list(),
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form['position'] = array(
		'#type' => 'select',
		'#title' => t('Icon Position'),
		'#description' => t('Choose the position of your icon here'),
		'#default_value' => isset($values['position']) ? $values['position'] : 'center',
		'#options' => $op
	);

	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Icon Link?'),
		'#description' => t('Where should your Icon link to?'),
		'#default_value' => isset($values['link']) ? $values['link'] : '',
	);

	$form['link_target'] = array(
		'#type' => 'select',
		'#title' => t('Open Link in new Window?'),
		'#description' => t('Select here if you want to open the linked page in a new window'),
		'#default_value' => isset($values['link_target']) ? $values['link_target'] : '_self',
		'#options' => array(
			'_blank' => t('Yes, open in new window'),
			'_self' => t('No, open in same window'),
		),
		'#states' => array(
			'disabled' => array(
				':input[name="link"]' => array('value' => ''),
			),
			'invisible' => array(
				':input[name="link"]' => array('value' => ''),
			),
		),
	);


	$form['alt_color'] = array(
		'#type' => 'checkbox',
		'#title' => t('Alter color and background on hover?'),
		'#default_value' => isset($values['alt_color']) && $values['alt_color'] == 'true' ? TRUE : FALSE,
		'#states' => array(
			'enabled' => array(
				':input[name="circled"]' => array('checked' => true),
			),
			'visible' => array(
				':input[name="circled"]' => array('checked' => true),
			),
		),
	);

	/** Add popOver Tooltips **/
	$settings = array(
		'title' => t('Icon'),
		'add_title' => TRUE,
	);
	if (isset($values['info'])) {
		$settings['info'] = $values['info'];
		if (isset($values['info_title'])) {
			$settings['info_title'] = $values['info_title'];
		}
		if (isset($values['info_place'])) {
			$settings['info_place'] = $values['info_place'];
		}
		if (isset($values['info_trigger'])) {
			$settings['info_trigger'] = $values['info_trigger'];
		}
		if (isset($values['info_title'])) {
			$settings['info_title'] = $values['info_title'];
		}
		if (isset($values['info_content'])) {
			$settings['info_content'] = $values['info_content'];
		}
	}

	// add animate fields
	acquia_field_tooltip($form, $settings);

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
 * preprocess {{ac_icon}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_icon_preprocess(&$values) {
	if (!isset($values['color']) || $values['color'] !='custom') {
		unset($values['custom_color']);
	}

	if (isset($values['icon_str'])) {
		unset($values['icon_str']);
	}

	if (isset($values['bg_color']) && $values['bg_color'] !='custom') {
		unset($values['custom_bg_color']);
	}

	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link_target']);
	}

	if (!isset($values['type']) || $values['type'] == 'simple') {
		unset($values['bg_color']);
		unset($values['custom_bg_color']);
		unset($values['alt_color']);
	}

	if (isset($values['subtle']) && $values['subtle'] == TRUE) {
		$values['subtle'] = 'true';
	}else{
		unset($values['subtle']);
	}

	if (isset($values['alt_color']) && $values['alt_color'] == TRUE) {
		$values['alt_color'] = 'true';
	}else{
		unset($values['alt_color']);
	}
}

/**
 * process {{ac_font_icon}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_font_icon_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('fonts');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
		'type' => 'simple',
		'icon' => '',
		'link' => '',
		'link_target' => '',
		'color' => '',
		'custom_color' => '',
		'size' => 'tiny',
		'position' => '',
		'subtle' => 'false',
		'bg_color' => '',
		'custom_bg_color' => '',
		'alt_color' => 'false',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	// get icon class
	$ico_class = acquia_fontello_glyph_get_code($icon);

	// Make Style
	$attributes = array();
	$style = array();

	$attrs_to_class = !empty($position) && $position != 'center' ? array('position') : array();
	$attrs_to_class[] = 'type';

	if ($color == 'custom' && !empty($custom_color)) {
		$style['color'] = $custom_color;
	}elseif (!empty($color) && $color != 'custom'){
		$attrs_to_class[] = 'color';
	}

	if ($type != 'simple' && $subtle == 'false') {
		if (!empty($custom_bg_color)) {
			$style['background'] = $custom_bg_color;
		}elseif (!empty($bg_color) && $bg_color != 'custom'){
			$attrs_to_class[] = 'bg_color';
		}
	}

	if ($subtle == 'true') {
		if (!empty($custom_bg_color)) {
			$style['border-color'] = $custom_bg_color;
		}elseif (!empty($bg_color) && $bg_color != 'custom'){
			$attrs_to_class[] = 'border_color';
			$_attrs['border_color'] = $bg_color;
		}
	}

	$attrs_to_class[] = 'size';

	$classes = array();
	$classes[] = $sc_name;
	$classes[]= ($type != 'simple') ? 'ac-bg-enabled' : '';
	$classes[]= ($subtle == 'true') ? 'ac-subtle-style' : '';
	$classes[]= ($alt_color == 'true') ? 'ac-alt-color' : '';
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$classes[]= acquia_get_class_by_args($attrs_to_class, $_attrs);

	//---------------------------------------
	if (!empty($class)) {
		foreach (explode(' ', $class) as $_class) {
			$classes[] = $_class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes['class'] = $classes;
	$attributes['style'] = acquia_style_arr_to_tag($style);

	if (isset($attrs['animate'])) {
		// Animate data
		$attributes += acquia_get_anim_data_by_attrs($attrs);
	}

	if (isset($attrs['info']) && empty($link)){
		$attrs['title'] = isset($attrs['title']) ? $attrs['title'] : NULL;
		$attrs['info_title'] = isset($attrs['info_title']) ? $attrs['info_title'] : $attrs['title'];
		acquia_add_tooltip_libs_by_type($attrs['info']);
		$attributes += (array)acquia_get_tooltip_data_by_attrs($attrs);
	}

	$out = '';
	$out .= '<span'.drupal_attributes($attributes).'>';
	$out .= theme('acquia_iconfont', array('class' => array($ico_class)));
	$out .= '</span>';

	if (!empty($link)) {
		$link_attrs = array();
		$link_attrs['class'] = array($sc_name .'-link');
		$link_attrs['class'][] = $ico_class . '-l';
		$link_attrs['target'] = $attrs['link_target'];
		if (isset($attrs['info'])) {
			acquia_add_tooltip_libs_by_type($attrs['info']);
			$link_attrs += (array)acquia_get_tooltip_data_by_attrs($attrs);
		}
		$link = $link == 'front' ? '<front>' : $link;
		$out = l($out, $link, array('html' => true, 'attributes' => $link_attrs));
	}

	$wrap_attrs = array();
	$wrap_attrs['class'] = array();
	$wrap_attrs['class'][] = $sc_name.'-wrap';
	$wrap_attrs['class'][] = $icon;
	$wrap_attrs['class'][] = acquia_get_class_by_args(array('position', 'info'), $attrs, CHECK_LENGTH);
	$wrap_attrs['class'] = array_filter($wrap_attrs['class'], 'strlen');
	$wrap_attrs['class'] = implode(' ', $wrap_attrs['class']);

	$out =  '<div'.drupal_attributes($wrap_attrs).'>'.$out.'</div>';
	return $out;
}