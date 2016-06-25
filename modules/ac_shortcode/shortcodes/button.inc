<?php
/**
 * @file shortcode defenition of video
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

function ac_shortcode_button_shortcode() {
	return array(
		'ac_button' => array(
			'title' => t('Button'),
			'description' => t('Creates a colored button'),
			'form callback' => 'ac_shortcode_ac_button_form',
			'values process callback' => 'ac_shortcode_ac_button_preprocess',
			'process callback' => 'ac_shortcode_ac_button_process',
			'sitewide settings' => 'ac_shortcode_ac_button_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_button}} shortcode
 */
function ac_shortcode_ac_button_form($form, &$form_state, $prefix = '') {
	acquia_include('fields');
	acquia_include('content');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();


	$ops = acquia_button_styles();
	add_default_option($ops);
	$form[$prefix . 'style'] = array(
		'#type' => 'select',
		'#title' => t('Button Style'),
		'#description' => t('Choose the style of your button here'),
		'#default_value' => isset($values[$prefix . 'style']) ? $values[$prefix . 'style'] : '',
		'#options' => $ops,
	);

	$form[$prefix . 'shine'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable sunshine style button?'),
		'#description' => '',
		'#default_value' => isset($values[$prefix . 'shine']) && $values[$prefix . 'shine'] == 'true' ?  TRUE : FALSE,
		'#states' => array(
			'visible' => array(
				':input[name="'.$prefix.'style"]' => array('value' => 'subtle'),
			),
		),
	);

	$form[$prefix . 'typo'] = array(
		'#type' => 'select',
		'#title' => t('Typography style'),
		'#description' => t('Choose the Typography style of your button here'),
		'#default_value' => isset($values[$prefix . 'typo']) ? $values[$prefix . 'typo'] : 'none',
		'#options' => array('none' => t('NONE'), 'soft' => t('Soft'), 'hard' => t('Hard')),
	);

	$form[$prefix . 'label'] = array(
		'#type' => 'textfield',
		'#title' => t('Button Label'),
		'#description' => t('This is the text that appears on your button.'),
		'#default_value' => isset($values[$prefix . 'label']) ? $values[$prefix . 'label'] : t('Click me'),
	);

	$form[$prefix . 'link'] = array(
		'#type' => 'textfield',
		'#title' => t('Button Link?'),
		'#description' => t('Where should your button link to?'),
		'#default_value' => '',
	);

	$form[$prefix . 'link_target'] = array(
		'#type' => 'select',
		'#title' => t('Open Link in new Window?'),
		'#description' => t('Select here if you want to open the linked page in a new window'),
		'#default_value' => isset($values[$prefix . 'link_target']) ? $values[$prefix . 'link_target'] : '_self',
		'#options' => array(
			'_blank' => t('Yes, open in new window'),
			'_self' => t('No, open in same window'),
		),
	);

	$ops = array_merge(array('theme_default' => t('Theme Default'), 'custom' => t('Custom Color')), acquia_skins_list());
	add_default_option($ops);

	$form[$prefix . 'bg_color'] = array(
		'#type' => 'select',
		'#title' => t('Button Color'),
		'#description' => t('Choose a color for your button here'),
		'#default_value' => isset($values[$prefix . 'bg_color']) ? $values[$prefix . 'bg_color'] : '_self',
		'#options' => $ops,
	);

	$form[$prefix . 'custom_bg'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Background Color'),
		'#description' => t('Select a custom background color for your Button here'),
		'#default_value' => isset($values[$prefix . 'custom_bg']) ? $values[$prefix . 'custom_bg'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="'.$prefix.'bg_color"]' => array('value' => 'custom'),
			),
		),
	);

	$form[$prefix . 'custom_font'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Font Color'),
		'#description' => t('Select a custom font color for your Button here'),
		'#default_value' => isset($values[$prefix . 'custom_font']) ? $values[$prefix . 'custom_font'] : '#ffffff',
		'#states' => array(
			'visible' => array(
				':input[name="'.$prefix.'bg_color"]' => array('value' => 'custom'),
			),
		),
	);

	$form[$prefix . 'size'] = array(
		'#type' => 'select',
		'#title' => t('Button Size'),
		'#description' => t('Choose the size of your button here'),
		'#default_value' => isset($values[$prefix . 'size']) ? $values[$prefix . 'size'] : 'medium',
		'#options' => array(
			'small' => t('Small'),
			'medium' => t('Medium'),
			'large' => t('Large'),
			'x-large' => t('X-Large'),
		),
	);

	$ops = acquia_btn_border_types();
	add_default_option($ops);

	$form[$prefix . 'type'] = array(
		'#type' => 'select',
		'#title' => t('Border type'),
		'#description' => t('Choose the type of your button here'),
		'#default_value' => isset($values[$prefix . 'type']) ? $values[$prefix . 'type'] : 'sw',
		'#options' => $ops,
	);

	$ops = array_merge(array('theme_default' => t('Theme Default'), 'custom' => t('Custom Color')), acquia_skins_list());
	add_default_option($ops);

	$form[$prefix . 'border_color'] = array(
		'#type' => 'select',
		'#title' => t('Border color'),
		'#description' => t('Select a color for your Button border here.'),
		'#default_value' => isset($values[$prefix . 'border_color']) ? $values[$prefix . 'border_color'] : '',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="'.$prefix.'style"]' => array('value' => 'bordered'),
			),
		),
	);

	$form[$prefix . 'custom_border_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Border Color'),
		'#description' => t('Select a Custom color for your Button border here.'),
		'#default_value' => isset($values[$prefix . 'custom_border_color']) ? $values[$prefix . 'custom_border_color'] : '#d1d1d1',
		'#states' => array(
			'visible' => array(
				':input[name="'.$prefix.'border_color"]' => array('value' => 'custom'),
			),
		),
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form[$prefix . 'position'] = array(
		'#type' => 'select',
		'#title' => t('Button position'),
		'#description' => t('Choose the position of your button here'),
		'#default_value' => isset($values[$prefix . 'position']) ? $values[$prefix . 'position'] : '',
		'#options' => $op,
	);

	$form[$prefix . 'full_width'] = array(
		'#type' => 'checkbox',
		'#title' => t('Shift button at a new row?'),
		'#description' => t(''),
		'#default_value' => isset($values[$prefix . 'full_width']) && $values[$prefix . 'full_width'] == 'true' ?  TRUE : FALSE,
	);

	$form[$prefix . 'block_level'] = array(
		'#type' => 'checkbox',
		'#title' => t('Stretch button width to it\'s container width?'),
		'#description' => t(''),
		'#default_value' => isset($values[$prefix . 'block_level']) && $values[$prefix . 'block_level'] == 'true' ?  TRUE : FALSE,
	);

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Button'),
		'default' => isset($values['icon']) ? $values['icon'] : NULL,
		'collapsed' => TRUE,
	));

	$settings = array(
		'title' => t('Button'),
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
		$settings['delay_enabled'] = TRUE;
	}

	if (!empty($prefix)) {
		$settings['field_name'] = $prefix . 'cssanimate';
	}

	// add animate fields
	acquia_field_animate($form, $settings);


	/** Add popOver Tooltips **/
	$settings = array(
		'title' => t('Button'),
		'add_title' => TRUE,
	);
	if (isset($values['info'])) {
		$settings['info'] = $values['info'];
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
	$form[$prefix . 'class'] = array(
		'#type' => 'textfield',
		'#title' => t('Extra class name'),
		'#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
		'#default_value' => isset($values[$prefix . 'class']) ? $values[$prefix . 'class'] : '',
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	$form['prefix'] = array(
		'#type' => 'value',
		'#value' => $prefix,
	);

	return $form;
}


/**
 * preprocess {{ac_button}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_button_preprocess(&$values) {
	$prefix = isset($values['prefix']) ? $values['prefix'] : '';

	if (isset($values[$prefix . 'border_color']) && isset($values[$prefix . 'style']) && $values[$prefix . 'style'] !='bordered') {
		unset($values[$prefix . 'border_color']);
	}

	if (isset($values[$prefix . 'bg_color']) && $values[$prefix . 'bg_color'] !='custom') {
		unset($values[$prefix . 'custom_bg']);
		unset($values[$prefix . 'custom_font']);
	}

	if (isset($values[$prefix . 'typo']) && $values[$prefix . 'typo'] == 'none') {
		unset($values[$prefix . 'typo']);
	}

	if (isset($values[$prefix . 'cssanimate']['enabled']) && $values[$prefix . 'cssanimate']['enabled'] == 1) {
		foreach($values[$prefix . 'cssanimate'] as $key => $value) {
			$values[$prefix . $key] = $value;
		}
	}
	unset($values[$prefix . 'cssanimate']);

	if ( !isset($values[$prefix . 'border_color']) || (isset($values[$prefix . 'border_color']) && $values[$prefix . 'border_color'] !='custom') ) {
		unset($values[$prefix . 'custom_border_color']);
	}

	if (isset($values[$prefix . 'shine']) && $values[$prefix . 'shine'] == TRUE) {
		$values[$prefix . 'shine'] = 'true';
	}else{
		$values[$prefix . 'shine'] = 'false';
	}

	if (isset($values[$prefix . 'full_width']) && $values[$prefix . 'full_width'] == TRUE) {
		$values[$prefix . 'full_width'] = 'true';
	}else{
		$values[$prefix . 'full_width'] = 'false';
	}

	if (isset($values[$prefix . 'block_level']) && $values[$prefix . 'block_level'] == TRUE) {
		$values[$prefix . 'block_level'] = 'true';
	}else{
		$values[$prefix . 'block_level'] = 'false';
	}

}

/**
 * process {{ac_button}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_button_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	acquia_include('fonts');

	$prefix = isset($attrs['prefix']) ? $attrs['prefix'] : '';

	if (!empty($prefix)) {
		$attrs_clone = array();
		foreach($attrs as $key => $val) {
			$attrs_clone[preg_replace('/^'.$prefix.'/', '', $key)] = $val;
		}
		$attrs = $attrs_clone;
	}
	$_attrs = ac_shortcode_attrs(array(
		'label' => 'Click me',
		'link' => '',
		'link_target' => '',
		'bg_color' => 'sw',
		'custom_bg' => '#444444',
		'custom_font' => '#ffffff',
		'border_color' => '',
		'custom_border_color' => '',
		'size' => 'medium',
		'style' => 'sw',
		'position' => '',
		'icon' => '',
		'shine' => 'false',
		'full_width' => 'false',
		'block_level' => 'false',
		'type' => '',
		'typo' => '',
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', $shortcode);
	$styles = array();
//	$_attrs['type'] = ($_attrs['type'] == 'sw') ? acquia_theme_get_settings('ac_button_type', null, 'shortcodes') : $_attrs['type'];
	$_attrs['style'] = ($_attrs['style'] == 'sw') || empty($_attrs['style']) ? acquia_theme_get_settings('ac_button_style', null, 'shortcodes') : $_attrs['style'];
//	$_attrs['bg_color'] = ($_attrs['bg_color'] == 'sw') ? acquia_theme_get_settings('ac_button_bg_color', null, 'shortcodes') : $_attrs['bg_color'];

	if ($_attrs['bg_color'] == 'custom') {
		if ($style !== 'flip') {
			$styles['background-color'] = $custom_bg;
			$styles['border-color'] = $custom_bg;
			$styles['color'] = $custom_font;
		} else {
			$styles['color'] = $custom_bg;
		}
	}

	if ( $style == 'bordered' && !empty($border_color) ) {
		// Bordered button - border color
		if ($border_color == 'sw') {
			$_attrs['border_color'] = acquia_theme_get_settings('ac_button_border_color', null, 'shortcodes');
		}else if ($border_color == 'custom' && !empty($custom_border_color)) {
			$styles['border-color'] = $custom_border_color;
		}
	}

	if (!empty($icon)) {
		$class = acquia_fontello_glyph_get_code($icon);
		if($style == 'flip') {
			$ico_attrs['class'] = array($sc_name.'-icon');
			if ($_attrs['bg_color'] == 'custom') {
				$ico_attrs['style']['border-color'] = $custom_bg;
				$ico_attrs['style']['color'] = $custom_font;
				$ico_attrs['style'] = acquia_style_arr_to_tag(	$ico_attrs['style'] );
			}else{
				$ico_attrs['class'][] = acquia_get_class_by_args(array('color', 'border_color'), array('color' => $bg_color, 'border_color' => $bg_color), CHECK_LENGTH);
				$ico_attrs['class'] = implode(' ', $ico_attrs['class']);
			}
			$icon = '<span'.drupal_attributes($ico_attrs).'>'.theme('acquia_iconfont', array('class' => $class)).'</span>';
		}else{
			$icon = '<span class="'.$sc_name.'-icon '.$class.'">&nbsp;</span>';
		}
	}

	if (($style == 'subtle-fade' || $style == 'flip') && acquia_variable_get('doc_direction') == 'LTR') {
		$out = '<span class="'.$sc_name.'-label">'.$label.'</span>' . $icon;
	}else {
		if ($shine == 'true') {
			$icon .= '<span class="shine"></span>';
		}
		$out = $icon . '<span class="'.$sc_name.'-label">'.$label.'</span>';
	}

	$options = array();
	$options['html'] = TRUE;
	if (trim($link) == '' || $link == '#') {
		$link = '#';
		$options['external'] = TRUE;
	}

	// Build Attributes that should be use as class
	$attrs_to_class = array('style', 'typo', 'type', 'size');

	if ( $style == 'subtle-fade' ) {
		if ($_attrs['bg_color'] != 'custom') {
			$_attrs['color'] = $_attrs['bg_color'];
			$attrs_to_class[] = 'color';

			$_attrs['border_color'] = $_attrs['bg_color'];
			$attrs_to_class[] = 'border_color';
		}
	}

	if ($block_level == 'true') {
		$attrs_to_class[] = 'block_level';
	}

	if ($position != 'center') {
		$attrs_to_class[] = 'position';
	}

	if ($style != 'flip') {
		$attrs_to_class[] = 'bg_color';
	}else {
		$_attrs['color'] = $bg_color;
		$attrs_to_class[] = 'color';
	}

	if ($style == 'bordered') {
		$attrs_to_class[] = 'border_color';
	}

	$options['attributes'] = array();
	$options['attributes']['class'] = array();
	$options['attributes']['class'][] = $sc_name;
	$options['attributes']['class'][]= acquia_get_class_by_args($attrs_to_class, $_attrs, CHECK_LENGTH);
	$options['attributes']['class'][] = $shine == 'true' ? 'ac-shine' : NULL;
	$options['attributes']['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$options['attributes']['class'] = trim(implode(' ', $options['attributes']['class']));
	$options['attributes']['title'] = isset($attrs['info_title']) && !empty($attrs['info_title']) ? $attrs['info_title'] : $label;
	$options['attributes']['target'] = $link_target;
	$options['attributes']['style'] = acquia_style_arr_to_tag(	$styles );

	foreach ($options['attributes'] as $attr => $val) {
		if ( empty($val) ) {
			unset( $options['attributes'][$attr] );
		}
	}

	// image data attributes
	if (isset($attrs['animate'])){
		$options['attributes'] += (array)acquia_get_anim_data_by_attrs($attrs);
	}

	// Tootltip
	if (isset($attrs['info'])){
		acquia_add_tooltip_libs_by_type($attrs['info']);
		$options['attributes'] += (array)acquia_get_tooltip_data_by_attrs($attrs);
	}

	$out = l($out, $link, $options);

	$wrap_attrs = array();
	$wrap_attrs['class'] = array();
	$wrap_attrs['class'][] = $sc_name.'-wrap';
	$wrap_attrs['class'][] = $block_level == 'true' || $full_width == 'true' ? 'ac-fullwidth' : NULL;
	$wrap_attrs['class'][] = acquia_get_class_by_args(array('position', 'info'), $attrs, CHECK_LENGTH);

	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$wrap_attrs['class'][] = $class;
		}
	}
	$wrap_attrs['class'] = array_filter($wrap_attrs['class'], 'strlen');
	$wrap_attrs['class'] = implode(' ', $wrap_attrs['class']);
	//---------------------------------------

	$out =  '<div'.drupal_attributes($wrap_attrs).'>'.$out.'</div>';

	return $out;
}

/**
 * Defines {{ac_button}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_button_sitewide_settings() {
	acquia_include('options');
	return array(
		'ac_button_bg_color' => array(
			'#type' => 'select',
			'#title' => t('background color'),
			'#description' => t('Select a default background color for your buttons here.'),
			'#options' => array_merge(array('' => t('theme default')), acquia_skins_list()),
		),
		'ac_button_type' => array(
			'#type' => 'select',
			'#title' => t('border type'),
			'#description' => t('Select a default border type for your buttons here.'),
			'#options' => acquia_btn_border_types(),
		),
		'ac_button_style' => array(
			'#type' => 'select',
			'#title' => t('style'),
			'#description' => t('Select a default style for your buttons here.'),
			'#options' => acquia_button_styles(),
		),
		'ac_button_border_color' => array(
			'#type' => 'select',
			'#title' => t('Border Color'),
			'#description' => t('Select a default border color for your Buttons here.'),
			'#options' => array_merge(array('' => t('theme default')), acquia_skins_list()),
		),
		'ac_button_typo' => array(
			'#type' => 'select',
			'#title' => t('Typography style'),
			'#description' => t('Choose the Typography style of your button here'),
			'#options' => array('none' => t('NONE'), 'soft' => t('Soft'), 'hard' => t('Hard')),
		),
	);
}