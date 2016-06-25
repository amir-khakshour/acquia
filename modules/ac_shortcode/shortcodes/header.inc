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

function ac_shortcode_header_shortcode() {
	return array(
		'ac_fancy_header' => array(
			'title' => t('Fancy Header'),
			'description' => t('Creates a fancy header shortcode.'),
			'form callback' => 'ac_shortcode_ac_fancy_header_form',
			'values process callback' => 'ac_shortcode_ac_fancy_header_preprocess',
			'process callback' => 'ac_shortcode_ac_header_process',
			'sitewide settings' => 'ac_shortcode_ac_fancy_header_sitewide_settings',
		),
		'ac_page_header' => array(
			'title' => t('Page Header'),
			'description' => t('Creates a page header shortcode.'),
			'form callback' => 'ac_shortcode_ac_page_header_form',
			'values process callback' => 'ac_shortcode_ac_page_header_preprocess',
			'process callback' => 'ac_shortcode_ac_header_process',
		),
	);
}

/**
 * Implements edit form of {{ac_fancy_header}} shortcode
 */
function ac_shortcode_ac_fancy_header_form($form, &$form_state) {
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
	$form['content'] = array(
		'#type' => 'textarea',
		'#title' => t('title'),
		'#description' => t('Enter your header title here'),
		'#default_value' => isset($values['content']) ? $values['content'] : t('Title here'),
	);

	$tags = array();
	for ($i = 1; $i<=6; $i++) {
		$tags['h' . $i . ''] = t('H' . $i  . '');
	}

	$form['tag'] = array(
		'#type' => 'select',
		'#title' => t('tag'),
		'#description' => t('Select the tag which will be used with your header.'),
		'#options' => $tags,
		'#default_value' => isset($values['tag']) ? $values['tag'] : 'h4',
	);

	$ops = acquia_fancy_header_styles();
	add_default_option($ops);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('header style'),
		'#description' => t('Select the fancy header style.'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form['align'] = array(
		'#type' => 'select',
		'#title' => t('Header alignment'),
		'#description' => t('Choose the alignment of your header here'),
		'#default_value' => isset($values['align']) ? $values['align'] : (acquia_variable_get('doc_direction') == 'LTR' ? 'left' : 'right'),
		'#options' => $op,
	);

	$ops = array_merge(array('' => t('Inherit'), 'custom' => t('Custom Color')), acquia_skins_list());
	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Color'),
		'#description' => t('Select a color for your Fancy Header here.'),
		'#options' => $ops,
		'#default_value' => isset($values['color']) ? $values['color'] : '',
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Color'),
		'#description' => t('Select a custom color for your Fancy Header here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	return $form;
}

/**
 * Implements edit form of {{ac_page_header}} shortcode
 */
function ac_shortcode_ac_page_header_form($form, &$form_state) {
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
	$form['content'] = array(
		'#type' => 'textarea',
		'#title' => t('title'),
		'#description' => t('Enter your header title here'),
		'#default_value' => isset($values['content']) ? $values['content'] : t('Title here'),
	);

	$form['tag'] = array(
		'#type' => 'select',
		'#title' => t('tag'),
		'#description' => t('Select the tag which will be used with your header.'),
		'#options' => acquia_header_tags(),
		'#default_value' => isset($values['tag']) ? $values['tag'] : 'h4',
	);

	$form['block_title'] = array(
		'#attributes' => array('data-help' => t('Turn it on if to apply block title style to this header.')),
		'#type' => 'checkbox',
		'#title' => t('Block Title Style?'),
		'#description' => t('Turn it on if to apply block title style to this header.'),
		'#default_value' => isset($values['block_title']) && $values['block_title'] == 'true' ? TRUE : FALSE,
	);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('style'),
		'#description' => t('Select the style of this header.'),
		'#options' => acquia_header_styles(),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);
	$form['align'] = array(
		'#type' => 'select',
		'#title' => t('Header alignment'),
		'#description' => t('Choose the alignment of your header here'),
		'#default_value' => isset($values['align']) ? $values['align'] : (acquia_variable_get('doc_direction') == 'LTR' ? 'left' : 'right'),
		'#options' => $op,
	);

	$form['margin'] = array(
		'#type' => 'select',
		'#title' => t('Header Margin'),
		'#description' => t('Select a margin type for your Header here.'),
		'#options' => acquia_margin(),
		'#default_value' => isset($values['margin']) ? $values['margin'] : 'default',
	);

	$ops = array_merge(array('' => t('Inherit'), 'custom' => t('Custom Color')), acquia_skins_list());

	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Header Color'),
		'#description' => t('Select a color for your Header here.'),
		'#options' => $ops,
		'#default_value' => isset($values['color']) ? $values['color'] : '',
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Color'),
		'#description' => t('Select a custom color for your Header here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['bg_enabled'] = array(
		'#type' => 'checkbox',
		'#title' => t('Highlighted header?'),
		'#description' => t('Turn it on if to select header background color.'),
		'#default_value' => isset($values['bg_color']) || $values['custom_bgcolor'] ? TRUE : FALSE,
	);

	$form['bg_color'] = array(
		'#type' => 'select',
		'#title' => t('Header background color'),
		'#description' => t('Select a background color for your Header here.'),
		'#options' => $ops,
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="bg_enabled"]' => array('checked' => TRUE),
			),
		),
	);
	$form['custom_bgcolor'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Color'),
		'#description' => t('Select a custom color for your Header here'),
		'#default_value' => isset($values['custom_bgcolor']) ? $values['custom_bgcolor'] : '#fff',
		'#states' => array(
			'visible' => array(
				':input[name="bg_color"]' => array('value' => 'custom'),
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
 * preprocess {{ac_page_header}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_page_header_preprocess(&$values) {
	if (isset($values['block_title']) && $values['block_title']) {
		$values['block_title'] = 'true';
	}else{
		unset($values['block_title']);
	}

	if (!isset($values['color']) || $values['color'] !='custom') {
		unset($values['custom_color']);
	}

	if (!isset($values['bg_enabled']) || !$values['bg_enabled']) {
		unset($values['bg_enabled']);
		unset($values['bg_color']);
		unset($values['custom_bgcolor']);
	}else if (isset($values['bg_color']) && $values['bg_color'] !='custom') {
		unset($values['custom_bgcolor']);
	}
	unset($values['bg_enabled']);
}

/**
 * preprocess {{ac_fancy_header}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_fancy_header_preprocess(&$values) {
	if (!isset($values['color']) || $values['color'] !='custom') {
		unset($values['custom_color']);
	}

}

/**
 * process {{ac_fancy_header}} and {{ac_page_header}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_header_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'tag' => 'h2',
		'color' => '',
		'custom_color' => '',
		'margin' => '',
		'style' => '',
		'align' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attrs_to_class = array('align', 'color', 'margin', 'style');
	if ($shortcode != 'ac_page_header') {
		acquia_include('utility');
		$_attrs['style'] = ($_attrs['style'] == 'sw') ? acquia_theme_get_settings('ac_fancy_header_style', null, 'shortcodes') : $_attrs['style'];
	}

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = acquia_get_class_by_args($attrs_to_class, $_attrs, CHECK_LENGTH);
	$attributes['class'][] = isset($attrs['block_title']) && $attrs['block_title'] == 'true' ? 'block__title' : NULL;

	$inner_attrs = array('class' => array('bt-i'));

	if (isset($attrs['bg_color'])) {
		$attributes['class'][] = 'ac-bg-header';
		if ($attrs['bg_color'] != 'custom') {
			$inner_attrs['class'][] = acquia_get_class_by_args(array('bg_color'), $attrs, CHECK_LENGTH);
		}else if (isset($attrs['custom_bgcolor'])){
			$inner_attrs['style'] ='background:' .$attrs['custom_bgcolor'];
		}
	}

	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	//---------------------------------------

	if ($color == 'custom' && !empty($custom_color)) {
		$attributes['style'] = 'color: ' .$custom_color;
	}

	$tags = array();
	for ($i = 1; $i<=6; $i++) {
		$tags[] = 'h' . $i . '';
	}

	$tag = in_array($tag, $tags) ? $tag : 'h2';

	$out  = '';

	if ($shortcode == 'ac_fancy_header') {
		$out .= '<div class="'.$sc_name.'-wrap clearfix '.$style.'">';
	}

	$out .= '<'.$tag.drupal_attributes($attributes).'>';
	$out .= '<span'.drupal_attributes($inner_attrs).'><span class="be"></span>' .$text. '<span class="ar"></span></span>';
	$out .= '</'.$tag.'>';

	if ($shortcode == 'ac_fancy_header') {
		$out .= '</div>';
	}

	return $out;
}


/**
 * Defines {{ac_callout}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_fancy_header_sitewide_settings() {
	acquia_include('options');
	$ops = array_merge(array('none' => t('theme default')), acquia_fancy_header_styles());

	return array(
		'ac_fancy_header_style' => array(
			'#type' => 'select',
			'#title' => t('header style'),
			'#description' => t('Select the fancy header style.'),
			'#options' => $ops,
		),
	);
}