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

function ac_shortcode_stick_shortcode() {
	 return array(
		 'ac_stick' => array(
				 'title' => t('Stick to container'),
				 'description' => t('Stick content to container shortcode.'),
				 'form callback' => 'ac_shortcode_ac_stick_form',
				 'values process callback' => 'ac_shortcode_ac_stick_preprocess',
				 'process callback' => 'ac_shortcode_ac_stick_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_fancy_stick}} shortcode
 */
function ac_shortcode_ac_stick_form($form, &$form_state) {
	 acquia_include('fields');
	 
	 $values = isset($form_state['values']) ? $form_state['values'] : array();
	 
	 $form = array();
	 
	 $settings = array(
			'title' => t('Sticky Content'),
	 );
	 if (isset($values['animate'])) {
			$settings['animate'] = $values['animate'];
			$settings['when'] = $values['when'];
	 }
	 
	 // add animate fields
	 acquia_field_animate($form, $settings);
	 
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
 * preprocess {{ac_stick}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_stick_preprocess(&$values) {

}

/**
 * process {{ac_fancy_stick}} and {{ac_page_stick}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_stick_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(

	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$attributes['class'][] = 'clearfix';
	
	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------
	
	if (isset($attrs['animate'])) {
	 // Animate data 
	 $attributes += acquia_get_anim_data_by_attrs($attrs);
	}
	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '	<div class="ac-stick-wrap">';
	$out .= '		<div class="ac-stick-inner">';
	$out .= '			'.$text;
	$out .= '		</div>';
	$out .= '	</div>';
	$out .= '</div>';

	return $out;
}