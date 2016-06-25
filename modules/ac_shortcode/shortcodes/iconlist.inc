<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_iconlist_shortcode() {
	return array(
		'ac_iconlist' => array (
			'title' => t('Icon list'),
			'description' => t('Creates a list with nice icons beside'),
			'form callback' => 'ac_shortcode_ac_iconlist_form',
			'values process callback' => 'ac_shortcode_ac_iconlist_preprocess',
			'process callback' => 'ac_shortcode_ac_iconlist_process',
		),
		'ac_iconlist_item' => array(
			'title' => t('Icon list item'),
			'description' => t('Creates a list item with nice icon beside'),
			'hidden' => TRUE,
			'enabled' => array('ac_iconlist' => true),
			'process callback' => 'ac_shortcode_ac_iconlist_item_process',
			'values process callback' => 'ac_shortcode_ac_iconlist_item_preprocess',
			'form callback' => 'ac_shortcode_ac_iconlist_item_form',
		)
	);
}

/**
 * Implements edit form of {{ac_iconlist}} shortcode
 */
function ac_shortcode_ac_iconlist_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$form['place'] = array(
		'#type' => 'select',
		'#title' => t('Icon Position'),
		'#description' => t('Set the position of the icons'),
		'#default_value' => isset($values['place']) ? $values['place'] : 'left',
		'#options' => array(
			'left' => t('left'),
			'right' => t('Right'),
		),
	);

	$form['size'] = array(
		'#type' => 'select',
		'#title' => t('Icon size'),
		'#description' => t('Set the size of the icons'),
		'#default_value' => isset($values['size']) ? $values['size'] : NULL,
		'#options' => acquia_sizes_list(),
	);

	$ops = acquia_icon_types();
	add_default_option($ops);

	$form['border'] = array(
		'#type' => 'select',
		'#title' => t('border type?'),
		//'#description' => t('Select the Icon type here.'),
		'#default_value' => isset($values['border']) ? $values['border'] : '',
		'#options' => $ops,
	);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Icon style'),
		'#description' => t('Set the style of the icons'),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
		'#options' => array(
			'alt_color' => t('Alter color and background on hover'),
			'static_color' => t('Static Color'),
		),
	);

	$ops = array_merge(array('' => t('Theme Default')), acquia_skins_list());
	$form['ico_color'] = array(
		'#type' => 'select',
		'#title' => t('Color'),
		'#description' => t('Choose a color for your icon here'),
		'#default_value' => isset($values['ico_color']) ? $values['ico_color'] : '',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="style"]' => array('value' => 'static_color'),
			),
			'enabled' => array(
				':input[name="style"]' => array('value' => 'static_color'),
			),
		),
	);

	$form['ico_bg'] = array(
		'#type' => 'select',
		'#title' => t('Background color'),
		'#description' => t('Choose a background color for your icon here'),
		'#default_value' => isset($values['ico_bg']) ? $values['ico_bg'] : '',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="style"]' => array('value' => 'static_color'),
			),
			'enabled' => array(
				':input[name="style"]' => array('value' => 'static_color'),
			),
		),
	);

	$form['no_desc'] = array(
		'#type' => 'checkbox',
		'#title' => t('Disable Description text'),
		'#default_value' => isset($values['no_desc']) && $values['no_desc'] == 'true' ?  TRUE : FALSE,
	);

	$settings = array(
		'title' => t('Icon'),
		'delay_enabled' => TRUE
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
		$settings['delay'] = $values['dely'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['where'] = array(
		'#type' => 'select',
		'#title' => t('Animate Section'),
		'#description' => t('Choose which section to animate?'),
		'#default_value' => isset($values['where']) ? $values['where'] : 'icon',
		'#options' => array(
			'block' => t('items'),
			'icon' => t('icons'),
		),
		'#states' => array(
			'visible' => array(
				':input[name="cssanimate[enabled]"]' => array('checked' => TRUE),
			),
			'enabled' => array(
				':input[name="cssanimate[enabled]"]' => array('checked' => TRUE),
			),
		),
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
 * Implements edit form of {{ac_iconlist_item}} shortcode
 */
/**
 * preprocess {{ac_iconlist}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_iconlist_preprocess(&$values) {
	if (isset($values['style']) && $values['style'] == 'alt_color') {
		unset($values['ico_color']);
		unset($values['ico_bg']);
	}

	if (isset($values['no_desc']) && $values['no_desc'] == TRUE) {
		$values['no_desc'] = 'true';
	}else{
		unset($values['no_desc']);
	}
}

function ac_shortcode_ac_iconlist_item_form($form, &$form_state) {
	acquia_include('fields');
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

	$form = array();

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('List Item Title'),
		'#description' => t('Enter the List Item Title here.'),
		'#default_value' => isset($values['title']) ? $values['title'] : t('List Title'),
	);

	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Title Link?'),
		'#description' => t('Do you want to apply a link to the title?'),
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

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Icon'),
		'default' => $values['icon'],
		'parents' => array(),
		'animate' => FALSE,
		'when' => isset($values['when']) ? $values['when'] : FALSE,
		'always_enabled' =>TRUE,
	));

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('List Item Content'),
		'#description' => t('Enter the List Item content here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : t('List Content goes here'),
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


/**
 * preprocess {{ac_iconlist_item}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_iconlist_item_preprocess(&$values) {
	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link']);
		unset($values['link_target']);
	}

	if (!isset($values['animate'])) {
		unset($values['where']);
	}
}


/**
 * process {{ac_iconlist_item}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_iconlist_item_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('content');
	acquia_include('fonts');
	$_attrs = ac_shortcode_attrs(array(
		'title' => '',
		'icon' => '',
		'font' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	// get icon class
	$ico_class = array(acquia_fontello_glyph_get_code($icon));
	//$ico_class[] = 'ac-boxed-xx-large';

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'ac-font-icon';
	//$classes[] = 'ac-size-large';

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;

	$icon = '    <span'.drupal_attributes($attributes).'>';
	$icon .= '      '.theme('acquia_iconfont', array('class' => $ico_class));
	$icon .= '    </span>';

	if (isset($attrs['link']) && !empty($attrs['link'])) {
		$attrs['link'] = $attrs['link'] == 'front' ? '<front>' : $attrs['link'];
		$icon = l($icon, $attrs['link'], array('html' => true, 'attributes' => array('target' => $attrs['link_target'])));
		$title = l($title, $attrs['link'], array('html' => true, 'attributes' => array('target' => $attrs['link_target'])));
	}

	$out = '';

	$out = '';
	$out .= '<li class="item clearfix">';
	$out .= '  <div class="icon">';
	$out .= $icon;
	$out .= '  </div>';
	$out .= '  <div class="'.$sc_name.'-content-wrap">';
	$out .= '    <h4 class="title">' .$title. '</h4>';
	if (trim(	$text) != '') {
		$out .= '    <div class="'.$sc_name.'-content">';
		$out .=       $text;
		$out .= '    </div>';
	}
	$out .= '  </div>';
	$out .= '</li>';

	return $out;
}

/**
 * process {{ac_iconlist}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_iconlist_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'place' => 'left',
		'style' => 'static_color',
		'ico_color' => '',
		'ico_bg' => '',
		'size' => 'medium',
		'border' => 'circled',
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('place', 'style', 'size', 'border'), $_attrs, CHECK_LENGTH);
	$classes[] = ($style == 'static_color') ?  acquia_get_class_by_args(array('ico_color', 'ico_bg'), $_attrs, CHECK_LENGTH) : NULL;
	$classes[] = isset($attrs['no_desc']) && $attrs['no_desc'] == 'true' ? 'ac-no-desc' : NULL;
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate ac-anim-childs' : null;

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;

	// Animate data
	if (isset($attrs['animate'])) {
		$attrs['where'] = isset($attrs['where']) ? $attrs['where'] : 'block';
		$attributes += acquia_get_anim_data_by_attrs($attrs);
		$attributes['data-anim-childs'] = $attrs['where'] == 'block' ? '.item' : '.icon';
	}

	$out = '';
	$out .= '<ul'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</ul>';

	return $out;
}

/**
 * Defines {{ac_iconlist}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_iconlist_sitewide_settings() {
	acquia_include('options');
	return array(
		'border' => array(
			'#type' => 'select',
			'#title' => t('border type'),
			'#description' => t('Select the default sitewide border type for icon list icon shortcode.'),
			'#options' => acquia_icon_types(),
		),
	);
}

