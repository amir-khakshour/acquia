<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_progressbar_shortcode() {
	return array(
		'ac_progressbar_item' => array(
			'title' => t('Progress Bars item'),
			'description' => t('Creates a Progress Bar item.'),
			'hidden' => TRUE,
			'enabled' => array('ac_progressbar' => true),
			'process callback' => 'ac_shortcode_ac_progressbar_item_process',
			'values process callback' => 'ac_shortcode_ac_progressbar_item_preprocess',
			'form callback' => 'ac_shortcode_ac_progressbar_item_form',
		),
		'ac_progressbar' => array (
			'title' => t('Progress Bars'),
			'description' => t('Create some progress bars'),
			'form callback' => 'ac_shortcode_ac_progressbar_form',
			'values process callback' => 'ac_shortcode_ac_progressbar_preprocess',
			'process callback' => 'ac_shortcode_ac_progressbar_process',
			'sitewide settings' => 'ac_shortcode_ac_progressbar_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_progressbar}} shortcode
 */
function ac_shortcode_ac_progressbar_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Progress bars style'),
		'#description' => t('Set the style of the Progress bars.'),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
		'#options' => array(
			'compact' => t('Compact style'),
			'extended' => t('Extended - Mini Style'),
			'extended big' => t('Extended - Big Style'),
		),
	);

	$ops = array_merge(array('theme_default' => t('Theme Default')), acquia_skins_list());
	add_default_option($ops);

	$form['bg_style'] = array(
		'#type' => 'select',
		'#title' => t('Background color'),
		'#description' => t('Choose a background color for your Progress bars here'),
		'#default_value' => isset($values['bg_style']) ? $values['bg_style'] : 'blue',
		'#options' => $ops,
		'#states' => array(
			'visible' => array(
				':input[name="style"]' => array('value' => 'compact'),
			),
			'enabled' => array(
				':input[name="style"]' => array('value' => 'compact'),
			),
		),
	);

	$form['no_striped'] = array(
		'#type' => 'checkbox',
		'#title' => t('No striped?'),
		'#default_value' => isset($values['no_striped']) && $values['no_striped'] == TRUE ? TRUE : FALSE,
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
 * Implements edit form of {{ac_progressbar_item}} shortcode
 */
function ac_shortcode_ac_progressbar_item_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Progress Bar Title'),
		'#description' => t('Enter the Progress Bars title here.'),
		'#default_value' => isset($values['title']) ? $values['title'] : t('Skill or Task'),
	);

	if (isset($values['style']) && $values['style'] == 'extended') {
		$ops = array_merge(array('theme_default' => t('Theme Default')), acquia_skins_list());
		add_default_option($ops);

		$form['bg_style'] = array(
			'#type' => 'select',
			'#title' => t('Background color'),
			'#description' => t('Choose a background color for your Progress bar here'),
			'#default_value' => isset($values['bg_style']) ? $values['bg_style'] : 'blue',
			'#options' => $ops,
		);
	}

	$form['progress'] = array(
		'#type' => 'select',
		'#title' => t('Progress in %'),
		'#description' => t('Select a number between 0 and 100?'),
		'#default_value' => isset($values['progress']) ? $values['progress'] : 20,
		'#options' => drupal_map_assoc(range(0, 100)),
	);

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Progress bar'),
		'default' => $values['icon'],
		'collapsed' => TRUE,
	));

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
 * preprocess {{ac_progressbar_item}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_progressbar_item_preprocess(&$values) {

	if (isset($values['style'])) {
		unset($values['style']);
	}
}

/**
 * preprocess {{ac_progressbar}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_progressbar_preprocess(&$values) {
	if (isset($values['style']) && $values['style'] != 'compact') {
		unset($values['bg_style']);
	}

	if (isset($values['no_striped']) && $values['no_striped']) {
		$values['no_striped'] = 'true';
	}else{
		unset($values['no_striped']);
	}
}

/**
 * process {{ac_progressbar_item}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_progressbar_item_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('content');
	acquia_include('fonts');
	$_attrs = ac_shortcode_attrs(array(
		'title' => '',
		'progress' => '',
		'icon' => '',
		'font' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);


	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'anim-item';

	if (isset($attrs['bg_style'])) {
		$attrs['bg_style'] = $attrs['bg_style'] == 'sw' ? acquia_theme_get_settings('ac_progressbar_bg_style', null, 'shortcodes') : $attrs['bg_style'];
		$classes[] = !empty($attrs['bg_style']) ? $attrs['bg_style'] .'-bar' : NULL;
	}


	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;
	$attributes['data-percentage'] = $progress;

	if (!empty($icon)) {
		$attributes['class'][] ='ac-icon-enabled';
		$ico_class = array(acquia_fontello_glyph_get_code($icon));
		$icon = '<span class="ico-wrap">' .theme('acquia_iconfont', array('class' => $ico_class)) .'</span>';
	}

	drupal_add_library('acquia', 'jquery.countTo');

	$out = '<li'.drupal_attributes($attributes).'>';
	$out .= '		<p class="label">';
	$out .= '				'.$icon;
	$out .= '				<span class="inner">'.strip_tags($title);
	$out .= '					<span class="units"><span>'.$progress.'</span>%</span>';
	$out .= '				</span>';
	$out .= '		</p>';
	$out .= '		<div class="progress"><div class="bar-outer"><div class="bar" style="width: '.$progress.'%" data-progress="'.$progress.'"></div></div></div>';
	$out .= '</li>';

	return $out;
}

/**
 * process {{ac_progressbar}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_progressbar_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'style' => 'left',
		'bg_style' => '',
	), $attrs);
	extract($_attrs);

	$_attrs['bg_style'] = ($_attrs['bg_style'] == 'sw') ? acquia_theme_get_settings('ac_progressbar_bg_style', null, 'shortcodes') : $_attrs['bg_style'];

	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('style'), $_attrs, CHECK_LENGTH);
	$classes[] = !empty($_attrs['bg_style']) ? $_attrs['bg_style'] .'-bar' : NULL;
	$classes[] = 'ac-animate';
	$classes[] = 'ac-anim-childs';
	$classes[] = isset($attrs['no_striped']) && $attrs['no_striped'] == 'true'? 'ac-no-striped' : NULL;

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
	$attributes['data-anim-childs'] = '.ac-progressbar-item';

	$out = '';
	$out .= '<ul'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</ul>';

	return $out;
}

/**
 * Defines {{ac_progressbar}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_progressbar_sitewide_settings() {
	acquia_include('utility');
	acquia_include('options');
	return array(
		'ac_progressbar_bg_style' => array(
			'#type' => 'select',
			'#title' => t('Progress Bars color'),
			'#description' => t('Select a custom background color for your Progress Bars here.'),
			'#default_value' => acquia_theme_get_settings('ac_progressbar_bg_style', null, 'shortcodes'),
			'#options' => acquia_skins_list(),
		),
	);
}