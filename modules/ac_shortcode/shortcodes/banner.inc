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

function ac_shortcode_banner_shortcode() {
	 return array(
		 'ac_banner' => array(
				 'title' => t('Banner'),
				 'description' => t('Creates interactive banners'),
				 'form callback' => 'ac_shortcode_ac_banner_form',
				 'values process callback' => 'ac_shortcode_ac_banner_preprocess',
				 'process callback' => 'ac_shortcode_ac_banner_process',
			),
		 'ac_banner_item' => array(
				 'hidden' => TRUE,
				 'enabled' => array('ac_banner' => true),
				 'title' => t('banner Item'),
				 'description' => t('Creates interactive banner item'),
				 'values process callback' => 'ac_shortcode_ac_banner_preprocess',
				 'form callback' => 'ac_shortcode_ac_banner_item_form',
				 'process callback' => 'ac_shortcode_ac_banner_item_process',
			),
	 );
}

/*==============================================================*/
// {{ac_banner}} shortcode
/*==============================================================*/
/**
 * Implements edit form of {{ac_banner}} shortcode
 */
function ac_shortcode_ac_banner_form($form, &$form_state) {
	acquia_include('options');
	
	$values = isset($form_state['values']) ? $form_state['values'] : array();
	
	$form['fid'] = array(
		'#type' => 'media',
		'#description' => t('Select Banner Background Image..'),
		'#title' => t('Banner Image'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('image'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/img',
			),
		),
	);
	
	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Image Style'),
		'#description' => t('Apply an image style to the banner image'),
		'#options' => image_style_options(),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);
	
	
	$ops = array_merge(array('' => t('Transparent'), 'custom' => t('Custom Color')), acquia_skins_list());
	$form['bg_color'] = array(
		'#type' => 'select',
		'#title' => t('Background Color'),
		'#description' => t('Choose a Background color for your Banner here'),
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : '',
		'#options' => $ops,
	);
	
	$form['custom_bg_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Background Color'),
		'#description' => t('Select a custom Background color for your Banner here.'),
		'#default_value' => isset($values['custom_bg_color']) ? $values['custom_bg_color'] : '#444444',
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
 * Process {{ac_banner}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_banner_preprocess(&$values) {
	 if (!isset($values['bg_color']) || $values['bg_color'] !='custom') {
		 unset($values['custom_bg_color']);
	 }
	 
	 if (isset($values['second']) && $values['second'] == TRUE) {
		 $values['second'] = 'true';
	 }else{
			unset($values['second']);
	 }
}

/**
 * process {{ac_banner}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_banner_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'fid' => '',
		'custom_bg_color' => '',
		'bg_color' => '',
		'style' => '',
		), $attrs);

	extract($_attrs);
	 $bg = '';
	 if (!empty($fid) && is_numeric($fid)) {
		 // Build background image path
			if (!empty($style)) {
				$bg = image_style_url($style, file_load($fid)->uri);
			}else {
				$bg = file_create_url(file_load($fid)->uri);
			}
	 }
	 $bg = '<img src="'.$bg.'" alt="'.t('title').'" />';
	 
	$sc_name = str_replace('_', '-', $shortcode);
	$classes = array();
	$classes[] = $sc_name;
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
	
	$attributes = array();
	$attributes['class'] = $classes;

	/** Shader
	-----------------------------------------*/
	$style = array();
	$attrs_to_class = array();
  if (!empty($custom_bg_color) && $bg_color == 'custom') {
    $style['background'] = $custom_bg_color;
  }elseif (!empty($bg_color) && $bg_color != 'custom'){
    $attrs_to_class[] = 'bg_color';
  }
	$shader_attrs['class'] = array('shader');
	$shader_attrs['class'][] = acquia_get_class_by_args($attrs_to_class, $_attrs);
	$shader_attrs['class'] = array_filter($shader_attrs['class'], 'strlen');
	$shader_attrs['class'] = implode(' ', $shader_attrs['class']);
	
	$shader_attrs['style'] = acquia_style_arr_to_tag($style);

	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '		<div'.drupal_attributes($shader_attrs).'></div>';
	$out .= '		'.$bg;
	$out .= '		<div class="banner-i">';
	$out .= '		'.	$text;
	$out .= '		</div>';
	$out .= '</div>';

	return $out;
}

/*==============================================================*/
// {{ac_banner_item}} shortcode
/*==============================================================*/
/**
 * Implements edit form of {{ac_banner_item}} shortcode
 */
function ac_shortcode_ac_banner_item_form($form, &$form_state) {
	acquia_include('options');

	$values['second'] = isset($values['second']) && $values['second'] == 'true' ? TRUE : FALSE;
	$form['second'] = array(
		'#type' => 'checkbox',
		'#title' => t('Visible when hover - second box?'),
		//'#description' => t('chenge to On if you want to enable toggle sorting.'),
		'#default_value' => $values['second'],
	);
	
	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$ops = array_merge(array('' => t('Inherit')), acquia_skins_list());
	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Banner Item text color'),
		'#description' => t('Choose a color for your Banner Item text here'),
		'#default_value' => isset($values['color']) ? $values['color'] : '',
		'#options' => $ops,
	);
	
	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom text Color'),
		'#description' => t('Select a custom color for your Banner Item text here.'),
		'#default_value' => isset($values['custom_bg_color']) ? $values['custom_bg_color'] : '#ffffff',
		'#states' => array(
			'visible' => array(
					':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);
	
	$form['bg_color'] = array(
		'#type' => 'select',
		'#title' => t('Banner Item background color'),
		'#description' => t('Choose a Background color for your Banner Item here'),
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : '',
		'#options' => $ops,
	);
	
	$form['custom_bg_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Background Color'),
		'#description' => t('Select a custom Background color for your Banner Item here.'),
		'#default_value' => isset($values['custom_bg_color']) ? $values['custom_bg_color'] : '#444444',
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
 * process {{ac_banner}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_banner_item_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'custom_bg_color' => '',
		'bg_color' => '',
		'color' => '',
		'custom_color' => '',
		), $attrs);

	extract($_attrs);
	
	$style = array();
	$attrs_to_class = array();
  if (!empty($custom_bg_color) && $bg_color == 'custom') {
    $style['background'] = $custom_bg_color;
  }elseif (!empty($bg_color) && $bg_color != 'custom'){
    $attrs_to_class[] = 'bg_color';
  }
	
	if ($color == 'custom' && !empty($custom_color)) {
    $style['color'] = $custom_color;
  }elseif (!empty($color)){
    $attrs_to_class[] = 'color';
  }


	$sc_name = str_replace('_', '-', $shortcode);
	$classes = array();
	$classes[] = $sc_name;
	$classes[] = isset($attrs['second']) ? 'sec' : NULL;
	$classes[] = acquia_get_class_by_args($attrs_to_class, $_attrs);

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
	if (!empty($style)) {
	  $attributes['style'] = acquia_style_arr_to_tag($style);
	}

	$out  = '<table'.drupal_attributes($attributes).'>';
	$out .= '  <tbody><tr><td>';
	$out .= '    '.$text;
	$out .= '  </td></tr></tbody>';
	$out .= '</table>';
	
	return $out;
}