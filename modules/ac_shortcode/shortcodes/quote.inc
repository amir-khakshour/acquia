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
function ac_shortcode_quote_shortcode(){
	return array(
		'ac_quote' => array(
			"title" => t("Fancy Quote"),
			"description" => t("Creates a fancy style Quote."),
			'js callback' => 'ac_shortcode_ac_quote_js_settings',
			'form callback' => 'ac_shortcode_ac_quote_form',
			'values process callback' => 'ac_shortcode_ac_quote_preprocess',
			'process callback' => 'ac_shortcode_ac_quote_process',
			'sitewide settings' => 'ac_shortcode_ac_quote_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_quote}} shortcode
 */
function ac_shortcode_ac_quote_form($form, $form_state){
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

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Content'),
		'#description' => t('Enter the Fancy Quote content here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : t('Be sure you put your feet in the right place, then stand firm.'),
		'#format' => NULL,
		'#rows' => 15,
	);

	$settings = array(
		'title' => t('Fancy Quote'),
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('Quote type'),
		'#description' => t('Choose the type of the Fancy Quote here'),
		'#default_value' => isset($values['type']) ? $values['type'] : NULL,
		'#options' => acquia_quote_types(),
	);

	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Font size'),
		'#description' => t('Size of Fancy Quote text.'),
		'#default_value' => isset($values['font']) ? $values['font'] : NULL,
		'#options' => acquia_font_sizes(),
	);

	$form['background'] = array(
		'#type' => 'select',
		'#title' => t('Background & Border'),
		'#description' => t('Select the border and background of the Fancy Quote here.'),
		'#default_value' => isset($values['background']) ? $values['background'] : NULL,
		'#options' => array(
			'simple' => t('no border and background'),
			'plain' => t('Border enabled, no background'),
			'fancy' => t('Border & background enabled'),
		),
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'blockquote'),
			),
		),
	);


	$form['position'] = array(
		'#type' => 'select',
		'#title' => t('Quote position'),
		'#description' => t('Select the Quote position here.'),
		'#default_value' => isset($values['position']) ? $values['position'] : NULL,
		'#options' => array(
			'left' => t('Left'),
			'right' => t('Right'),
		),
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'pullquote'),
			),
		),
	);

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
 * preprocess {{ac_quote}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_quote_preprocess(&$values){
	if (isset($values['type']) && $values['type'] !='blockquote') {
		unset($values['background']);
	}

	if (isset($values['type']) && $values['type'] !='pullquote') {
		unset($values['position']);
	}
}

/**
 * process {{ac_quote}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_quote_process($attrs, $text = null, $shortcode = ''){
	acquia_include('content');
	acquia_include('process', 'ac_shortcode');
	$_attrs = ac_shortcode_attrs(array(
		'type' => 'blockquote',
		'font' => 'normal',
		'background' => 'fancy',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('type', 'font', 'background'), $_attrs);
	$classes[] = isset($attrs['position']) && !empty($attrs['position']) ?
		acquia_get_class_by_args(array('quote_position'), array('quote_position' => $attrs['position'])) : null;
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$classes[] = 'ac-b-space';
	$classes[] = 'ca-item';
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
	$attributes += acquia_get_anim_data_by_attrs($attrs);

	$iconfont ='';
	if ($type == 'blockquote') {
		$iconfont = theme('acquia_iconfont', array('class' => array('icon-quote', 'quote-left')));
	}

	$text = $iconfont .$text;

	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '		<div class="quote-box ac-bordered">';
	$out .= '		'.$text;
	$out .= '		</div>';
	$out .= '</div>';

	return $out;
}
