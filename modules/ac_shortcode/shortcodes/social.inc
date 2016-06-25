<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_social_shortcode() {
	return array(
		'ac_socials' => array (
			'title' => t('Social Icons'),
			'description' => t('Creates a list of social icons'),
			'form callback' => 'ac_shortcode_ac_socials_form',
			'values process callback' => 'ac_shortcode_ac_socials_preprocess',
			'process callback' => 'ac_shortcode_ac_socials_process',
		),
		'ac_social' => array(
			'title' => t('Icon list item'),
			'description' => t('Creates a list item with nice icon beside'),
			'hidden' => TRUE,
			'enabled' => array('ac_socials' => true),
			'process callback' => 'ac_shortcode_ac_social_process',
      'values process callback' => 'ac_shortcode_ac_social_preprocess',
      'form callback' => 'ac_shortcode_ac_social_form',
		)
	);
}

/*==============================================================*/
// {{ac_socials}} shortcode
/*==============================================================*/
/**
 * Implements edit form of {{ac_socials}} shortcode
 */
function ac_shortcode_ac_socials_form($form, &$form_state) {
  acquia_include('fields');
  acquia_include('options');
 
  $values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
  
	 $settings = array(
     'title' => t('Social Icon'),
     'delay_enabled' => TRUE
	 );
	 if (isset($values['animate'])) {
     $settings['animate'] = $values['animate'];
     $settings['when'] = $values['when'];
     $settings['delay'] = $values['dely'];
	 }
	 
	 // add animate fields
	 acquia_field_animate($form, $settings);

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
 * preprocess {{ac_socials}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_socials_preprocess(&$values) {
	 if (isset($values['cssanimate']) && $values['cssanimate']['enabled'] == 0) {
     unset($values['cssanimate']);
	 }
}

/**
 * process {{ac_socials}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_socials_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	//$_attrs = ac_shortcode_attrs(array(
	//), $attrs);
	//extract($_attrs);
	
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
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
  
	if (isset($attrs['animate']) && !empty($attrs['animate'])) {
		// Animate data 
		$attributes += acquia_get_anim_data_by_attrs($attrs);
		$attributes['data-anim-childs'] = '.ac-social';
	}
  
	$out = '';
	$out .= '<ul'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</ul>';
	
	return $out;
}


/*==============================================================*/
// {{ac_social}} shortcode
/*==============================================================*/
/**
 * Implements edit form of {{ac_social}} shortcode
 */
function ac_shortcode_ac_social_form($form, &$form_state) {
  acquia_include('options');
  
  $values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
	
  $form['icon'] = array(
		'#type' => 'select',
		'#title' => t('Icon'),
		'#description' => t('Select social icon from the list'),
		'#default_value' => isset($values['icon']) ? $values['icon'] : '',
		'#options' => acquia_social_icons(),
	);

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Icon Title'),
    '#description' => t('Enter the social icon Title here.'),
    '#default_value' => isset($values['title']) ? $values['title'] : t('Follow Me!'),
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
		'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : '',
		'#options' => array_merge(array(
			'' => t('Theme Color'),
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
	
	$values['subtle'] = isset($values['subtle']) && $values['subtle'] == 'true' ?  TRUE : FALSE;
	$form['subtle'] = array(
		'#type' => 'checkbox',
		'#title' => t('Subtle style'),
		'#default_value' => isset($values['subtle']) ? $values['subtle'] : FALSE,
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
 * preprocess {{ac_social}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_social_preprocess(&$values) {
	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link']);
		unset($values['link_target']);
	}
	
	if (!isset($values['color']) || (isset($values['color']) && $values['color'] !='custom')) {
		unset($values['custom_color']);
	}

	if (!isset($values['bg_color']) || (isset($values['bg_color']) && $values['bg_color'] !='custom')) {
		unset($values['custom_bg_color']);
	}
	
	if (isset($values['subtle']) && $values['subtle'] == TRUE) {
		 $values['subtle'] = 'true';
	}else{
		 unset($values['subtle']);
	}
}

/**
 * process {{ac_social}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_social_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('content');
  acquia_include('fonts');
	$_attrs = ac_shortcode_attrs(array(
		'icon' => '', 
		'title' => '',
		'color' => '',
		'custom_color' => '',
		'bg_color' => '',
		'custom_bg_color' => '',
		'size' => 'medium', 
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$title = !empty($title) ? $title : $icon;
	$style = array();
	$attrs_to_class = array('size');
	
	if (!empty($custom_color)) {
		$style['color'] = $custom_color;
	}elseif (!empty($color) && $color != 'custom'){
		$attrs_to_class[] = 'color';
	}
	
	if (isset($attrs['subtle']) && $attrs['subtle'] == 'true') {
		if (!empty($custom_bg_color)) {
			$style['border-color'] = $custom_bg_color;
		}elseif (!empty($bg_color) && $bg_color != 'custom'){
			$attrs_to_class[] = 'border_color';
			$_attrs['border_color'] = $bg_color;
		}
	}else{
		if (!empty($custom_bg_color)) {
			$style['background'] = $custom_bg_color;
		}elseif (!empty($bg_color) && $bg_color != 'custom'){
			$attrs_to_class[] = 'bg_color';
		}
	}

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'ac-font-icon';
	$classes[] = 'ac-bg-enabled';
	$classes[]= isset($attrs['subtle']) && $attrs['subtle'] == 'true' ? 'ac-subtle-style' : '';
	$classes[] = acquia_get_class_by_args($attrs_to_class, $_attrs);

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
	$attributes['style'] = acquia_style_arr_to_tag($style);
	if (!isset($attrs['link']) || empty($attrs['link'])) {
		$attributes['title'] = $title;
	}

 	// Build Icon
	$ico_class = array('icon-' . $icon);
	$icon = '    <span'.drupal_attributes($attributes).'>';
	$icon .= '      '.theme('acquia_iconfont', array('class' => $ico_class));
	$icon .= '    </span>';
  
 if (isset($attrs['link']) && !empty($attrs['link'])) {
		acquia_include('utility');
		
		$link_opts =  array('html' => true, 'attributes' => array('target' => $attrs['link_target'], 'title' => $title));
		acquia_add_tooltip_libs_by_type();
		$attrs['info_title'] = $title;
		$link_opts['attributes'] += (array)acquia_get_tooltip_data_by_attrs($attrs);
		$attrs['link'] = $attrs['link'] == 'front' ? '<front>' : $attrs['link'];
		$icon = l($icon, $attrs['link'], $link_opts);
	}
  
	$out  = '<li class="'.$sc_name.'-wrap clearfix">';
	$out .= $icon;
	$out .= '</li>';
	
	return $out;
}

