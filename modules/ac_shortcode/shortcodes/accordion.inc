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
function ac_shortcode_accordion_shortcode() {
	return array(
		'ac_accordion_tab' => array(
			"title" => t("Accordion tab"),
			"enabled" => array('ac_accordion' => TRUE),
			"hidden" => TRUE,
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_accordion_tab_form',
			'process callback' => 'ac_shortcode_ac_accordion_tab_process',
			'values process callback' => 'ac_shortcode_ac_accordion_tab_preprocess',
		),
		'ac_accordion' => array(
			"title" => t("Accordion"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_accordion_form',
			'values process callback' => 'ac_shortcode_ac_accordion_preprocess',
			'process callback' => 'ac_shortcode_ac_accordion_process',
		),
		'vc_accordion_tab' => array(
			"title" => t("Accordion tab"),
			"enabled" => array('ac_accordion' => TRUE),
			"hidden" => TRUE,
			"description" => "",
			'form callback' => 'ac_shortcode_ac_accordion_tab_form',
			'process callback' => 'ac_shortcode_ac_accordion_tab_process',
			'values process callback' => 'ac_shortcode_ac_accordion_tab_preprocess',
		),
		'vc_accordion' => array(
			"title" => t("Accordion"),
			"description" => t("some description here"),
			'form callback' => 'ac_shortcode_ac_accordion_form',
			'values process callback' => 'ac_shortcode_ac_accordion_preprocess',
			'process callback' => 'ac_shortcode_ac_accordion_process',
			"enabled" => array('ac_accordion' => TRUE),
			"hidden" => TRUE,
		),
	);
}


/**
 * Implements edit form of {{ac_accordion_tab}} shortcode
 */
function ac_shortcode_ac_accordion_tab_form($form, &$form_state) {
	acquia_include('fields');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Toggle'),
		'default' => isset($values['icon']) ? $values['icon'] : NULL,
		'parents' => array(),
	));

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Title'),
		'#description' => t('Enter the toggle title here.'),
		'#default_value' => isset($values['title']) ? $values['title'] : t('Toggle title'),
	);

	$values['open'] = isset($values['open']) && $values['open'] == 'true' ? TRUE : FALSE;
	$form['open'] = array(
		'#type' => 'checkbox',
		'#title' => t('Initial Open?'),
		'#description' => t('chenge to On if you want this toggle should be open initially.'),
		'#default_value' => $values['open'],
	);

	if (isset($values['sorting']) && $values['sorting'] == TRUE) {
		$form['tags'] = array(
			'#type' => 'textfield',
			'#title' => t('Tags'),
			'#description' => t('Enter comma separated tags here; this will be used for sorting toggles. if sroting is active then user can filter the visible toggles with the help of these tags.'),
			'#default_value' => isset($values['tags']) ? $values['tags'] : NULL,
		);
	}


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
 * Implements edit form of {{ac_accordion}} shortcode
 */
function ac_shortcode_ac_accordion_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$values['sorting'] = isset($values['sorting']) && $values['sorting'] == 'true' ? TRUE : FALSE;
	$form['sorting'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable Toggles Sorting?'),
		'#description' => t('chenge to On if you want to enable toggle sorting.'),
		'#default_value' => $values['sorting'],
	);

	$settings = array(
		'title' => t('Toggles'),
		'delay_enabled' => TRUE
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
		$settings['delay'] = $values['delay'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('Toggle Type'),
		'#description' => t('Should only one toggle be active at a time and the others be hidden or can multiple toggles be open at the same time?'),
		'#options' => array(
			'accordion' => t('Accordion - Only one toggle open at a time'),
			'toggle' => t('Toggle - Multiple toggles open allowed'),
		),
		'#default_value' => isset($values['type']) ? $values['type'] : 'accordion',
	);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Style'),
		'#description' => t('select toggles style.'),
		'#default_value' => isset($values['style']) ? $values['style'] : 'simple',
		'#options' => acquia_accordion_styles(),
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
 * preprocess {{ac_accordion}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_accordion_preprocess(&$values) {
	if (isset($values['sorting']) && $values['sorting'] == TRUE) {
		$values['sorting'] = 'true';
	}else{
		$values['sorting'] = 'false';
	}
}

/**
 * preprocess {{ac_accordion_tab}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_accordion_tab_preprocess(&$values) {
	if (isset($values['sorting'])) {
		unset($values['sorting']);
	}

	if (isset($values['open']) && $values['open'] == TRUE) {
		$values['open'] = 'true';
	}else{
		$values['open'] = 'false';
	}
}

/**
 * process {{ac_toggle}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_accordion_tab_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'open' => '',
		'title' => '',
		'icon' => '',
		'font' => 'fontello',
		'tags' => '',
		'class' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', 'ac_toggle');

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = !empty($icon) ? 'ac-toggle-has-icon' : '';

	//---------------------------------------
	if (!empty($class)) {
		foreach (explode(' ', $class) as $_class) {
			$classes[] = $_class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;
	$attributes['data-tags'] = create_tag_data($tags);
	$attributes['data-open'] = $open;

	if (!empty($icon)) {
		acquia_include('fonts');
		acquia_fontello_glyph_get_code($icon);
		$icon = theme('acquia_iconfont', array('font'=> $font, 'icon' => $icon));
	}

	$out = '';

	$out .= '		<div'.drupal_attributes($attributes).'>';
	$out .= '			<div class="'.$sc_name.'-tab">';
	$out .= '				<span class="inner">';
	$out .= '				'.$icon;
	$out .= '				'.$title;
	$out .= '				</span>';
	$out .= '			</div>';
	$out .= '			<div class="'.$sc_name.'-pane">';
	$out .= '				<div class="inner clearfix">';
	$out .= '					'.$text;
	$out .= '				</div>';
	$out .= '			</div>';
	$out .= '		</div>';

	return $out;
}



/**
 * process {{ac_toggle_container}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_accordion_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'style' => 'minimal',
		'type' => 'accordion',
		'sorting' => '',
		'class' => '',
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', 'ac_toggle_container');

	$classes = array();
	$classes[] = $sc_name;
	foreach (explode(' ', $style) as $_style){
		$classes[] = $_style . '-style';
	}

	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;

	//---------------------------------------
	if (!empty($class)) {
		foreach (explode(' ', $class) as $_class) {
			$classes[] = $_class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;
	$attributes['data-toggle-type'] = $type;
	$attributes['data-sorting'] = $sorting;

	// Animate data 
	$attributes += acquia_get_anim_data_by_attrs($attrs);

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</div>';

	return $out;
}

/**
 * Create tags data by given tags string
 */
function create_tag_data($tags) {
	$out = array('{all}');
	if ( is_string($tags) && !empty($tags) ) {
		$tags = explode(',', $tags);
		if (is_array($tags) && count($tags)) {
			foreach($tags as $tag) {
				$out[] = '{' .trim($tag). '}';
			}
		}
	}
	return implode(' ', $out);
}

