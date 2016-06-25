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

function ac_shortcode_pricing_table_shortcode() {
	 return array(
		 'pt' => array(
				 'title' => t('pricing table'),
				 'description' => t('Creates a pricing table.'),
				 'form callback' => 'ac_shortcode_ac_pricing_table_form',
				 'values process callback' => 'ac_shortcode_ac_pricing_table_preprocess',
				 'process callback' => 'ac_shortcode_ac_pricing_table_process',
			),
		 'pt_col' => array(
				 'hidden' => TRUE,
				 'enabled' => array('pt' => TRUE),
				 'title' => t('pricing table column'),
				 'description' => t('Creates a pricing table column.'),
				 'process callback' => 'ac_shortcode_ac_pt_col_process',
			),
		 'pt_row' => array(
				 'hidden' => TRUE,
				 'enabled' => array('pt' => TRUE),
				 'title' => t('pricing table row'),
				 'description' => t('Creates a pricing table row.'),
				 'process callback' => 'ac_shortcode_ac_pt_row_process',
			),
		 'pt_price' => array(
				 'hidden' => TRUE,
				 'enabled' => array('pt' => TRUE),
				 'title' => t('pricing table price'),
				 'description' => t('Creates a pricing table price cell.'),
				 'process callback' => 'ac_shortcode_ac_pt_el_process',
			),
		 'pt_package' => array(
				 'hidden' => TRUE,
				 'enabled' => array('pt' => TRUE),
				 'title' => t('pricing table package'),
				 'description' => t('Creates a pricing table package cell.'),
				 'process callback' => 'ac_shortcode_ac_pt_el_process',
			),
		 'pt_details' => array(
				 'hidden' => TRUE,
				 'enabled' => array('pt' => TRUE),
				 'title' => t('pricing table details'),
				 'description' => t('Creates a pricing table details cell.'),
				 'process callback' => 'ac_shortcode_ac_pt_el_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_pricing_table}} shortcode
 */
function ac_shortcode_ac_pricing_table_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');
	
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
	
	$ops = acquia_pricing_table_types();
	add_default_option($ops);
	
	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('type'),
		'#description' => t('Choose the styling for the pricing table.'),
		'#options' => $ops,
		'#default_value' => isset($values['type']) ? $values['type'] : '',
	);
	
	$form['cols'] = array(
		'#type' => 'textfield',
		'#title' => t('Columns'),
		'#description' => t('How much Columns do you need?'),
		'#default_value' => isset($values['cols']) ? $values['cols'] : '2',
	);

	 $form['text_format_cid'] = array(
		 '#type' => 'value',
		 '#value' => array($cid => 'content'),// key of cids and related real form id
	 );
	 $form[$cid] = array(
		 '#type' => 'text_format',
		 '#title' => t('Pricing Table Content'),
		 '#description' => t('Enter the Pricing Table content here.'),
		 '#default_value' => isset($values['content']) ? $values['content'] : array(),
		 '#format' => NULL,
		 '#rows' => 15,
	 );
	 
	 $settings = array(
		 'title' => t('Pricing Table'),
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
 * Process {{ac_pricing_table}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_pricing_table_preprocess(&$values) {

}

/**
 * process {{ac_pt_row}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_pt_row_process($attrs, $text = null, $shortcode = '') {
	$_attrs = ac_shortcode_attrs(array(
		'alt' => 'true',
		'btn' => 'true',
		), $attrs);
	
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$classes = array();
	$classes[] = $sc_name;
	$classes[] = isset($attrs['alt']) ? 'ac-alt' : NULL;
	$classes[] = isset($attrs['btn']) ? 'ac-pt-btn' : NULL;

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

	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '		'.$text;
	$out .= '</div>';

	return $out;
}

/**
 * process {{ac_pricing_table}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_pt_el_process($attrs, $text = null, $shortcode = '') {
	//$_attrs = ac_shortcode_attrs(array(
	//	'label' => 'false',
	//	'highlight' => 'false',
	//	), $attrs);
	//
	//extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$classes = array();
	$classes[] = $sc_name;
	$classes[] = $shortcode == 'pt_details' ? 'clearfix' : NULL;

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
	
	if ($shortcode == 'pt_price') {
	  $text = '<div class="inner">' .$text .'</div>';
	}else if($shortcode == 'pt_package') {
	  $text = '<span class="inner">' .$text .'</span>';
	}
	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '		'.$text;
	$out .= '</div>';

	return $out;
}

/**
 * process {{ac_pricing_table}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_pt_col_process($attrs, $text = null, $shortcode = '') {
	$_attrs = ac_shortcode_attrs(array(
		'label' => 'false',
		'highlight' => 'false',
		), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'ac-col';
	$classes[] = $label == 'true' ? 'ac-label-col' : NULL;
	$classes[]= $highlight == 'true' ? 'ac-highlight-col' : NULL;
	$classes[] = 'ac-frame-on';
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
	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '	<div class="inner">';
	$out .= '		'.$text;
	$out .= '	</div>';
	$out .= '</div>';

	return $out;
}

/**
 * process {{ac_pricing_table}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_pricing_table_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'type' => 'standard',
		'cols' => '2',
		), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$classes = array();
	$classes[] = 'ac-'.$sc_name;
	$classes[]= acquia_get_class_by_args(array('type', 'cols'), $_attrs);
	$classes[]= isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
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
	
	// Data attributes
	if (isset($attrs['animate'])){
	 	$attributes += acquia_get_anim_data_by_attrs($attrs);
	}
	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '		'.$text;
	$out .= '</div>';

	return $out;
}