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

function ac_shortcode_divider_shortcode() {
	 return array(
		 'ac_divider' => array(
				 'title' => t('Divider'),
				 'description' => t('Creates a delimiter to separate elements'),
				 'form callback' => 'ac_shortcode_ac_divider_form',
				 'values process callback' => 'ac_shortcode_ac_divider_preprocess',
				 'process callback' => 'ac_shortcode_ac_divider_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_divider}} shortcode
 */
function ac_shortcode_ac_divider_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');
	
	$values = isset($form_state['values']) ? $form_state['values'] : array();
	
	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('Divider type'),
		'#description' => t('Here you can set the styling of the divider element'),
		'#options' => acquia_dividers_list(),
		'#default_value' => isset($values['type']) ? $values['type'] : 'invisible',
	);
	
	$form['size'] = array(
		'#type' => 'select',
		'#title' => t('Icon Size'),
		'#description' => t('select the size of icon.'),
		'#default_value' => isset($values['size']) ? $values['size'] : 'medium',
		'#options' => acquia_sizes_list(),
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'icon'),
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
		acquia_skins_list()),
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'icon'),
			),
		),
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
	
	 // add icon fields
	 acquia_field_iconfont($form, $form, array(
			'title' => t('Divider'),
			'default' => isset($values['icon']) ? $values['icon'] : '',
			'parents' => array(),
			'animate' => isset($values['animate']) ? $values['animate'] : TRUE,
			'when' => isset($values['when']) ? $values['when'] : FALSE,
			'always_enabled' =>TRUE,
	 ));
	 $form['fonticon']['#states'] = array(
			 'visible' => array(
					 ':input[name="type"]' => array('value' => 'icon'),
			 ),
			 'enabled' => array(
					 ':input[name="type"]' => array('value' => 'icon'),
			 ),
	 );
	
	$form['styles'] = array(
		'#type' => 'fieldset',
		'#title' => t('divider style'),
		'#states' => array(
			'invisible' => array(
					':input[name="type"]' => array('value' => 'sw'),
			),
			'disabled' => array(
					':input[name="type"]' => array('value' => 'sw'),
			),
		),
	);
	
	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);
	$form['styles']['align'] = array(
		'#type' => 'select',
		'#title' => t('Divider alignment'),
		'#description' => t('Choose the alignment of your Divider here'),
		'#default_value' => isset($values['align']) ? $values['align'] : 'center',
		'#options' => $op,
	);

	$form['styles']['height'] = array(
		'#type' => 'textfield',
		'#title' => t('Height'),
		'#description' => t('How much whitespace do you need? Enter a pixel value'),
		'#default_value' => isset($values['height']) ? $values['height'] : '20',
		'#maxlength' => '5',
		'#size' => '10',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'invisible'),
			),
		),
	);
	
	$form['styles']['width'] = array(
		'#type' => 'select',
		'#title' => t('Divider width'),
		'#description' => t('Set the width of the divider based on container width'),
		'#default_value' => isset($values['width']) ? $values['width'] : 'full',
		'#options' => array(
			'page_divider' => t('full page divider'),
			'full' => t('1/1'),
			'one-half' => t('1/2'),
			'one-third' => t('1/3'),
			'one-fourth' => t('1/4'),
		),
		'#states' => array(
			'invisible' => array(
					':input[name="type"]' => array('value' => array('invisible')),
			),
			'disabled' => array(
					':input[name="type"]' => array('value' => array('invisible')),
			),
		),
	);
	
	$form['styles']['gotop_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Go to top Title'),
		'#description' => t('Set the title of the go to top divider.leave it blank to use default title.'),
		'#default_value' => isset($values['gotop_title']) ? $values['gotop_title'] : '',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'go_top'),
			),
			'enabled' => array(
					':input[name="type"]' => array('value' => 'go_top'),
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
 * Process {{ac_divider}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_divider_preprocess(&$values) {
	 if (isset($values['type'])) {
	 
			if ($values['type'] !='invisible') {
				 unset($values['height']);
			}
			
			if ($values['type'] !='go_top') {
				 unset($values['gotop_title']);
			}
			
			if ($values['type'] =='invisible') {
				 unset($values['width']);
			}
			
			if ($values['type'] != 'icon') {
				 unset($values['font']);
				 unset($values['icon']);
			}
			
			if ((isset($values['color']) && $values['color'] != 'custom') || !isset($values['color'])) {
				 unset($values['custom_color']);
			}else{
				 unset($values['color']);
			}
	 }
}

/**
 * process {{ac_divider}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_divider_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'type' => 'invisible',
		'styles' => '',
		'height' => '',
		'width' => '',
		'gotop_title' => '',
		'align' => 'center',
		'size' => '',
		), $attrs);

	extract($_attrs);
	
	$sc_name = str_replace('_', '-', $shortcode);
	$attrs_to_class = array();
	$attrs_to_class[] = 'type';
	$attrs_to_class[] = 'align';
	$attrs_to_class[] = 'size';
	$attrs_to_class = array_filter($attrs_to_class, 'strlen');
	
	$classes = array();
	$classes[] = $sc_name;
	$classes[]= !empty($width) ? 'ac-'.$width : '';
	$classes[]= acquia_get_class_by_args($attrs_to_class, $_attrs, CHECK_LENGTH);
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
	
	if (!empty($height)) {
	  $attributes['style'] = 'height:' .absint($height) .'px';
	}
	
	$inner = '';
	if ($type == 'shadow') {
	 
		$inner = '<span class="divider-shadow-left"></span><span class="divider-shadow-right"></span>';
	}else if ($type == 'go_top') {
	 
		$inner = '<a href="#" class="divider-go-top">';
		$inner.= '	'. isset($gotop_title) && !empty($gotop_title) ? $gotop_title : t('Back to top');
		$inner.= '	'.theme('acquia_iconfont', array('font' => 'fontello', 'icon' => 'icon-up-open-mini'));
		$inner.= '</a>';
	}else if($type == 'icon' && isset($attrs['icon']) && !empty($attrs['icon'])) {
	 
	 	acquia_include('fonts');
		$ico_attrs = array('class' => array(acquia_fontello_glyph_get_code($attrs['icon'])));
		$ico_attrs['class'][] = isset($attrs['size']) ? acquia_get_class_by_args(array('boxed'), array('boxed' => $attrs['size']), CHECK_LENGTH) :NULL;
		
		if (isset($attrs['custom_color']) && !empty($attrs['custom_color'])) {
			$ico_attrs['style'] = 'color:' .$attrs['custom_color'];
		}elseif (isset($attrs['color']) && $attrs['color'] != 'custom'){
			$ico_attrs['class'][] = acquia_get_class_by_args(array('color'), $attrs, CHECK_LENGTH);
		}
		
	  $inner = theme('acquia_iconfont', $ico_attrs);
		//$inner = '<span class="ac-hr">' .$inner .'</span>';
	}
	
	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '		<div class="divider-inner">';
	$out .= '		'.	$inner;
	$out .= '		</div>';
	$out .= '</div>';

	return $out;
}