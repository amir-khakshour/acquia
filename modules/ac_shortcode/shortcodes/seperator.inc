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

function ac_shortcode_seperator_shortcode() {
	 return array(
		 'vc_text_separator' => array(
				 'title' => t('Separator with Text'),
				 'description' => t('Creates a delimiter by a text to separate elements.'),
				 'form callback' => 'ac_shortcode_vc_text_separator_form',
				 'process callback' => 'ac_shortcode_vc_text_separator_process',
			),
	 );
}

/**
 * Implements edit form of {{vc_text_separator}} shortcode
 */
function ac_shortcode_vc_text_separator_form($form, &$form_state) {
	 acquia_include('options');
	 acquia_include('fields');
	 
	 $values = isset($form_state['values']) ? $form_state['values'] : array();
	
	 $form['title'] = array(
		 '#type' => 'textfield',
		 '#title' => t('Title'),
		 '#description' => t('Separator title.'),
		 '#default_value' => isset($values['title']) ? $values['title'] : t('Title'),
	 );
	 
	 $ops = array();
	 foreach (acquia_align_list() as $align => $title) {
			$ops['separator_align_' . $align] = $title;
	 }
	 
		$form['title_align'] = array(
			'#type' => 'select',
			'#title' => t('Title position'),
			'#description' => t('Select title location.'),
			'#options' => $ops,
			'#default_value' => isset($values['title_align']) ? $values['title_align'] : NULL,
		);
		
		$settings = array(
			'title' => t('Seperator Text'),
		);
		if (isset($values['animate'])) {
			$settings['animate'] = $values['animate'];
			$settings['when'] = $values['when'];
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
 * process {{vc_text_separator}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_vc_text_separator_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'title' => 'shadow',
		'title_align' => '',
		), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$attrs_to_class = array();
	
	$title_align = str_replace('separator_align_', '', $title_align);
	
	$classes = array();
	$classes[] = $sc_name;
	$classes[]= acquia_get_class_by_args(array('align'), array('align' => $title_align));
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

	/** Title Attributes **/
	$title_attrs = array();
	$title_attrs['class'] = array();
	$title_attrs['class'][] = 'inner';
	$title_attrs['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	
	$title_attrs['class'] = array_filter($title_attrs['class'], 'strlen');
	$title_attrs['class'] = implode(' ', $title_attrs['class']);
	// Animate data 
	$title_attrs += acquia_get_anim_data_by_attrs($attrs);
	
	$out = '';
	$out .= '<div'.drupal_attributes($attributes).'>';
	$out .= '  <div'.drupal_attributes($title_attrs).'>';
	$out .= '    '.$title;
	$out .= '  </div>';
	$out .= '</div>';

	return $out;
}