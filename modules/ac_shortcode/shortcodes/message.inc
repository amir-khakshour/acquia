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

function ac_shortcode_message_shortcode() {
	 return array(
		 'ac_message' => array(
				 'title' => t('Message box'),
				 'description' => t('Creates a colored message box for notification purpose.'),
				 'form callback' => 'ac_shortcode_ac_message_form',
				 'values process callback' => 'ac_shortcode_ac_message_preprocess',
				 'process callback' => 'ac_shortcode_ac_message_process',
				 'sitewide settings' => 'ac_shortcode_ac_message_sitewide_settings',
			),
	 );
}

/**
 * Implements edit form of {{ac_message}} shortcode
 */
function ac_shortcode_ac_message_form($form, &$form_state) {
	 $cid = &drupal_static(__FUNCTION__);
	 acquia_include('options');
	 acquia_include('fields');
	 
	 // saving and restoring cid we we use don't want
	 //	to rebuild after adding new tabs
	 if (isset($form_state['cid'])) {
		 $cid = $form_state['cid'];
	 }else if (!isset($cid)) {
		 $cid = uniqid('content_');
		 $form_state['cid'] = $cid;
	 }
	
	 $values = isset($form_state['values']) ? $form_state['values'] : array();
	 $form['title'] = array(
		 '#type' => 'textfield',
		 '#title' => t('title'),
		 '#description' => t('This is the small title at the top of your Notification.'),
		 '#default_value' => isset($values['title']) ? $values['title'] : t('Note'),
	 );
	 
	 $form['text_format_cid'] = array(
		 '#type' => 'value',
		 '#value' => array($cid => 'content'),// key of cids and related real form id
	 );
	 $form[$cid] = array(
		 '#type' => 'text_format',
		 '#title' => t('Message text'),
		 '#description' => t('Enter the image caption content here.'),
		 '#default_value' => isset($values['content']) ? $values['content'] : array(),
		 '#format' => NULL,
		 '#rows' => 15,
	 );
	
	 
	 $ops = array_merge(
			acquia_message_box_types(),
			array('custom' => t('Custom Color'))
	 );
	 add_default_option($ops);
	 
	 $form['type'] = array(
		 '#type' => 'select',
		 '#title' => t('Message box type'),
		 '#description' => t('Select message type.'),
		 '#options' => $ops,
		 '#default_value' => isset($values['type']) ? $values['type'] : NULL,
	 );
	 
	 $form['custom_bg'] = array(
		 '#attributes' => array('class' => array('field-colorpicker')),
		 '#type' => 'textfield',
		 '#title' => t('Custom Background Color'),
		 '#description' => t('Select a custom background color for your Message box here'),
		 '#default_value' => isset($values['custom_bg']) ? $values['custom_bg'] : '#444444',
		 '#states' => array(
			 'visible' => array(
					 ':input[name="type"]' => array('value' => 'custom'),
			 ),
		 ),
	 );
	 
	$form['custom_font'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Font Color'),
		'#description' => t('Select a custom font color for your Message box here'),
		'#default_value' => isset($values['custom_font']) ? $values['custom_font'] : '#ffffff',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'custom'),
			),
		),
	);
	
	 $form['border'] = array(
		 '#type' => 'select',
		 '#title' => t('Message Box Border'),
		 '#description' => t('Choose the border for your Box here'),
		 '#options' => array(
				 'none' => t('None'),
				 'solid' => t('Solid'),
				 'dashed' => t('Dashed'),
			),
		 '#default_value' => isset($values['border']) ? $values['border'] : '',
	 );
	 
	 $form['size'] = array(
		 '#type' => 'select',
		 '#title' => t('Box Size'),
		 '#description' => t('Choose the size of your Box here'),
		 '#options' => array(
				 'normal' => t('Normal'),
				 'large' => t('Large'),
			),
		 '#default_value' => isset($values['size']) ? $values['size'] : 'normal',
	 );

	// add icon fields
	  acquia_field_iconfont($form, $form, array(
		 'title' => t('Message Box'),
		 'default' => $values['icon'],
	 ));

	 $settings = array(
		 'title' => t('Message Box'),
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
 * preprocess {{ac_message}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_message_preprocess(&$values) {
	 if (isset($values['type']) && $values['type'] != 'custom') {
			unset($values['custom_bg']);
			unset($values['custom_font']);
	 }
}
/**
 * process {{ac_message}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_message_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('fonts');
	acquia_include('utility');
	acquia_include('process', 'ac_shortcode');
	
	$_attrs = ac_shortcode_attrs(array(
		'title' => '',
		'type' => 'green',
		'border' => 'solid',
		'custom_bg' => '',
		'custom_font' => '',
		'size' => 'large',
		'icon' => '',
		), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$styles = array();
	$_attrs['type'] = ($_attrs['type'] == 'sw') ? acquia_theme_get_settings('ac_message_type', null, 'shortcodes') : $_attrs['type'];
	
	if ($_attrs['type'] == 'custom') {
			$styles['background-color'] = $custom_bg;
			$styles['color'] = $custom_font;
	}
	
	$type = ($type == 'sw') ? acquia_theme_get_settings('ac_message_type', null, 'shortcodes') : $type;

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('type', 'size', 'border'), $_attrs, CHECK_LENGTH);;
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
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
	$attributes['style'] = acquia_style_arr_to_tag(	$styles );
	
	// title attributes
	$title_attrs['class'] = $sc_name.'-title';
	$title_attrs['style'] = acquia_style_arr_to_tag(	$styles );
	
	// Data attributes
	if (isset($attrs['animate'])){
	 	$attributes += acquia_get_anim_data_by_attrs($attrs);
	}
	
	 $out = '';
	 $out .= '<div'.drupal_attributes($attributes).'>';
	 $out .= '<div class="'.$sc_name.'-content">';
	 if (!empty($icon)) {
		 $class = acquia_fontello_glyph_get_code($icon);
		 $out .= '<span class="'.$sc_name.'-icon '.$class.'">&nbsp;</span>';
	 }
	 if (trim($title) != '') {
		 $text = '<strong'.drupal_attributes($title_attrs).'>'.strip_tags($title).': </strong>' . $text;
	 }
	 $out .=  '<p class="'.$sc_name.'-message">'.ac_shortcode_remove_autop($text).'</p>';
	 $out .= '</div>';
	 $out .= '</div>';
	 return $out;
}
	 
/**
 * Defines {{ac_message}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_message_sitewide_settings() {
	acquia_include('options');
	$ops = acquia_message_box_types();
	 return array(
			'ac_message_type' => array(
				 '#type' => 'select',
				 '#title' => t('Message box type'),
				 '#description' => t('Select message type.'),
				 '#options' => $ops,
				 '#default_value' => NULL,
		),
	);
}
