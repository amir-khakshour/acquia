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
function ac_shortcode_tabs_shortcode() {
	return array(
		'ac_tabs' => array(
			"title" => t("Tabs"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_tabs_form',
			'values process callback' => 'ac_shortcode_ac_tabs_preprocess',
			'process callback' => 'ac_shortcode_ac_tabs_process',
		),
		'ac_tab' => array(
			"title" => t("Tab"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_tab_form',
			'process callback' => 'ac_shortcode_ac_tab_process',
			'enabled' => array('ac_tabs' => TRUE),
			'hidden' => TRUE,
		),
	);
}

/*==============================================================*/
// {{ac_tabs}} shortcode callbacks
/*==============================================================*/
function ac_shortcode_ac_tabs_form($form, $form_state) {
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Widget title'),
		'#description' => t('What text use as a widget title. Leave blank if no title is needed.'),
		'#default_value' => isset($values['title']) ? $values['title'] : NULL,
	);

	// $form['interval'] = array(
	//	 '#type' => 'select',
	//	 '#title' => t('Auto rotate tabs'),
	//	 '#description' => t('Auto rotate tabs each X seconds.'),
	//	 '#options' => array('disabled', 0, 3, 5, 10, 15),
	//	 '#default_value' => isset($values['interval']) ? $values['interval'] : 'disabled',
	// );
	// 
	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Style'),
		'#default_value' => isset($values['style']) ? $values['style'] : 'simple',
		'#description' => t('select tab style.'),
		'#options' => acquia_tab_styles(),
	);

	$form['position'] = array(
		'#type' => 'select',
		'#title' => t('Tabs position'),
		'#default_value' => isset($values['position']) ? $values['position'] : 'top',
		'#description' => t('Where should the tabs be displayed'),
		'#options' => array(
			'top' => t('Display tabs at the top'),
			'left' => t('Display Tabs on the left'),
			'right' => t('Display Tabs on the right'),
		),
	);

	$form['init'] = array(
		'#type' => 'textfield',
		'#title' => t('Initial Open'),
		'#description' => t('Enter the Number of the Tab that should be open initially.'),
		'#default_value' =>  isset($values['init']) ? $values['init'] : 0,
	);

	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Tab Title Font size'),
		'#description' => t('Font size of tab\'s title text.'),
		'#options' => array_merge(array('' => t('Theme Default')), acquia_font_sizes()),
	);


	$form['no_borders'] = array(
		'#type' => 'checkbox',
		'#title' => t('No borders'),
		'#description' => t('Disable tabs borders.'),
		'#default_value' => isset($values['no_borders']) && $values['no_borders'] == 'true' ? TRUE : FALSE,
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


function ac_shortcode_ac_tabs_preprocess(&$values) {
	if (isset($values['no_borders']) && $values['no_borders'] == TRUE) {
		$values['no_borders'] = 'true';
	}else{
		unset($values['no_borders']);
	}
}

/**
 * process {{ac_tabs}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_tabs_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'style' => 'simple',
		'title' => '',
		'position' => 'top',
		'init' => 1,
		'font' => '',
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;

	$styles = explode(' ', $style);
	if (!empty($styles)) {
		foreach ($styles as $_style) {
			$classes[] = $_style . '-style';
		}
	}

	$classes[] = strstr($style, 'simple') && !strstr($style, 'centered') ? $position . '-position' : '';
	$classes[]= acquia_get_class_by_args(array('font'), $_attrs, CHECK_LENGTH);
	$classes[] = (trim($title) != '') ? 'titled' : '';
	$classes[] = isset($attrs['no_borders']) && $attrs['no_borders'] == 'true' ? 'ac-no-borders' : null;
	$classes[] = 'clearfix';
	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;
	$attributes['data-init'] = $init;

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '	<div class="'.$sc_name.'-i">';
	if (trim($title) != '' && strstr($style, 'fancy')) {
		$out .= '		<div class="ac-tabs-title">';
		$out .= '			'.t($title);
		$out .= '		</div>';
	}
	$out .= '		<div class="ac-tabs-panes">';
	$out .= '			'.$text;
	$out .= '		</div>';
	$out .= '	</div>';
	$out .= '</div>';
	return $out;
}
/*==============================================================*/
// {{ac_tab}} shortcode callbacks
/*==============================================================*/
/**
 * Implements edit form of {{ac_tab}} shortcode
 */
function ac_shortcode_ac_tab_form($form, $form_state) {
	acquia_include('fields');
	acquia_include('content');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Title'),
		'#description' => t('change tab title here.'),
		'#default_value' => isset($values['title']) ? $values['title'] : t('Tab'),
	);

	acquia_field_iconfont($form, $form, array(
		'title' => t('Tab Icon'),
		'default' => $values['icon'],
		'collapsed' => TRUE,
		'parents' => array(),
	));

	$form['tab_id'] = array(
		'#type' => 'textfield',
		'#title' => t('Tab id'),
		'#default_value' => isset($values['tab_id']) ? $values['tab_id'] :  time().'-1-'.rand(0, 100),
		'#disabled' => TRUE,
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * process {{ac_tab}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_tab_process($attrs, $text = null, $shortcode = '') {
	$_attrs = ac_shortcode_attrs(array(
		'title' => '',
		'icon' => '',
		'font' => 'fontello',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = !empty($icon) ? $sc_name . '-has-icon' : '';

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

	if (!empty($icon)) {
		$icon = theme('acquia_iconfont', array('font'=> $font, 'icon' => $icon));
	}

	$out = '';

	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '<div class="'.$sc_name.'-tab">';
	$out .= $icon;
	$out .= $title;
	$out .= '</div>';
	$out .= '<div class="'.$sc_name.'-pane">';
	$out .= '<div class="inner clearfix">';
	$out .= $text;
	$out .= '</div>';
	$out .= '</div>';
	$out .= '</div>';

	return $out;
}
