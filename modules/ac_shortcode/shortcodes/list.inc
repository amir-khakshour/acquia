<?php
/**
 * @file shortcode defenition of {{quote}}
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
function ac_shortcode_list_shortcode(){
	return array(
		'ac_list' => array(
			"title" => t("Fancy List"),
			"description" => t("Creates a fancy style list."),
			'js callback' => 'ac_shortcode_ac_list_js_settings',
			'form callback' => 'ac_shortcode_ac_list_form',
			'values process callback' => 'ac_shortcode_ac_list_preprocess',
			'process callback' => 'ac_shortcode_ac_list_process',
			'sitewide settings' => 'ac_shortcode_ac_list_sitewide_settings',
			'nested shortcodes' => array('items' => 'ac_list_item'),
		),
		'ac_list_item' => array(
			'form callback' => 'ac_shortcode_ac_list_item_form',
			'values process callback' => 'ac_shortcode_ac_list_item_preprocess',
			'process callback' => 'ac_shortcode_ac_list_item_process',
			//'sitewide settings' => 'ac_shortcode_ac_list_item_sitewide_settings',
			'hidden' => TRUE,
			'enabled' => array('ac_list' => TRUE),
		),
	);
}

/*==============================================================*/
// {{ac_list}} shortcode
/*==============================================================*/
/**
 * Defines {{ac_list}} shortcode js settings
 */
function ac_shortcode_ac_list_js_settings() {
	$settings['order']			= 100;
	$settings['tinymce'] 		= array('instantInsert' => "[ac_list style='icon' borders='false' subtle='false'][ac_list_item icon='flash']Your Text here.[/ac_list_item][/ac_list]");
	$settings['group']			= t('Misc');
	$settings['group_mn']		= 'misc';
	return $settings;
}

/**
 * Implements edit form of {{ac_list}} shortcode
 */
function ac_shortcode_ac_list_form($form, $form_state){
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
	acquia_include('options');
	acquia_include('content');

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('List style'),
		'#description' => t('Choose the style of the your list items here'),
		'#default_value' => isset($values['style']) ? $values['style'] : NULL,
		'#options' => acquia_list_styles(),
	);

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form['list'] = array(
		'#type' => 'container',
	);

	$form['list'][$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Content'),
		'#description' => t('Enter the Fancy Quote content here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	$form['icon_sel'] = array(
		'#type' => 'container',
		'#states' => array(
			'visible' => array(
				':input[name="style"]' => array('value' => 'icon'),
			),
			'enabled' => array(
				':input[name="style"]' => array('value' => 'icon'),
			),
		),
	);

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('List items Icon'),
		'default' => $values['icon'],
		'parents' => array(),
		'animate' => FALSE,
		'always_enabled' =>TRUE,
	));

	$form['fonticon']['#states'] = array(
		'visible' => array(
			':input[name="style"]' => array('value' => 'icon'),
		),
		'enabled' => array(
			':input[name="style"]' => array('value' => 'icon'),
		),
	);

	$form['icon_sel']['num'] = array(
		'#type' => 'select',
		'#title' => t('Number of list items'),
		//'#description' => t('Size of Fancy Quote text.'),
		'#default_value' => isset($values['num']) ? $values['num'] : NULL,
		'#options' => drupal_map_assoc(range(1, 10)),
	);

	$values['subtle'] = isset($values['subtle']) && $values['subtle'] == 'true' ?  TRUE : FALSE;
	$form['icon_sel']['subtle'] = array(
		'#type' => 'checkbox',
		'#title' => t('Subtle style'),
		'#default_value' => isset($values['subtle']) ? $values['subtle'] : FALSE,
	);

	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Font size'),
		'#description' => t('Size of Fancy Quote text.'),
		'#default_value' => isset($values['font']) ? $values['font'] : NULL,
		'#options' => acquia_font_sizes(),
	);

	$form['borders'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enabled Bottom border for list items?'),
		'#description' => t(''),
		'#default_value' => isset($values['borders']) && $values['borders'] == 'true' ?  TRUE : FALSE,
	);

	$settings = array(
		'title' => t('List Items'),
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
 * preprocess {{ac_list}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_list_preprocess(&$values){
	if (isset($values['style']) && $values['style'] == 'icon' && isset($values['fonticon'])) {
		foreach ($values['text_format_cid'] as $cid => $key) {
			if (isset($values[$cid]) && is_array($values[$cid]) && isset($values[$cid]['value'])) {
				unset($values[$cid]);
			}
		}
		$items = isset($values['num']) ? (int) $values['num'] : 5;
		$text = acquia_variable_get('dummy_text', t('your text here.'));

		for ($i= 0; $i<$items; $i++) {
			$values['items'][] = array('icon' => $values['fonticon']['icon'], 'content' => $text);
		}
		$values['icon'] = $values['fonticon']['icon'];
		unset($values['fonticon']);
		if (isset($values['subtle']) && $values['subtle'] == TRUE) {
			$values['subtle'] = 'true';
		}else{
			unset($values['subtle']);
		}
	}else{
		unset($values['items']);
		unset($values['fonticon']);
		unset($values['subtle']);
	}

	if (isset($values['borders']) && $values['borders'] == TRUE) {
		$values['borders'] = 'true';
	}else{
		unset($values['borders']);
	}
}

/**
 * process {{ac_list}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_list_process($attrs, $text = null, $shortcode = ''){
	acquia_include('content');
	acquia_include('process', 'ac_shortcode');
	$_attrs = ac_shortcode_attrs(array(
		'style' => 'un',
		'font' => 'normal',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('style', 'font'), $_attrs);
	$classes[] = isset($attrs['subtle']) && $attrs['subtle'] == 'true' ? 'ac-subtle-style' : '';
	$classes[] = isset($attrs['borders']) && $attrs['borders'] == 'true'? 'ac-li-bordered': null;
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate ac-anim-childs' : null;
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

	// Animate data
	if (isset($attrs['animate'])) {
		$attributes += acquia_get_anim_data_by_attrs($attrs);
		$attributes['data-anim-childs'] = 'li';
	}


	if ($style == 'icon') {
		$text = '<ul>' .$text .'</ul>';
	}

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '  '.$text;
	$out .= '</div>';

	return $out;
}

/**
 * preprocess {{ac_list_item}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_list_item_preprocess(&$values){
}

/**
 * preprocess {{ac_list_item}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_list_item_process($attrs, $text = null, $shortcode = ''){
	acquia_include('fonts');
	$_attrs = ac_shortcode_attrs(array(
		'icon' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	// get icon class
	$ico_class = array(acquia_fontello_glyph_get_code($icon));

	$attributes = array();
	$attributes['class'] = 'li-ico';
	$icon = '    <span'.drupal_attributes($attributes).'>';
	$icon .= '      '.theme('acquia_iconfont', array('class' => $ico_class));
	$icon .= '    </span>';

	$out = '';
	$out .= '<li class="item">';
	$out .= '  '.$icon;
	$out .= '  '.$text;
	$out .= '</li>';

	return $out;
}