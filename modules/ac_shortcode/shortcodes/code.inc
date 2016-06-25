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

function ac_shortcode_code_shortcode() {
	 return array(
		 'ac_code' => array(
				 'title' => t('Code View'),
				 'description' => t('Display a raw shortcode.'),
				 'form callback' => 'ac_shortcode_ac_code_form',
				 'values process callback' => 'ac_shortcode_ac_code_preprocess',
				 'process callback' => 'ac_shortcode_ac_code_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_code}} shortcode
 */
function ac_shortcode_ac_code_form($form, &$form_state) {
	acquia_include('options');
	
  $values = isset($form_state['values']) ? $form_state['values'] : array();
  
  $cid = &drupal_static(__FUNCTION__);
  
  // saving and restoring cid we we use don't want
  //	to rebuild after adding new tabs
  if (isset($form_state['cid'])) {
    $cid = $form_state['cid'];
  }else if (!isset($cid)) {
    $cid = uniqid('content_');
    $form_state['cid'] = $cid;
  }
  
  $form['text_format_cid'] = array(
    '#type' => 'value',
    '#value' => array($cid => 'content'),// key of cids and related real form id
  );
  
  $form[$cid] = array(
    '#type' => 'text_format',
    '#title' => t('Shortcode'),
    '#description' => t('Enter Your shortcode code here.'),
    '#default_value' => isset($values['content']) ?
		 rawurldecode(base64_decode(strip_tags($values['content']))) :
		 array(),
    '#format' => NULL,
    '#rows' => 15,
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
 * Process {{ac_code}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_code_preprocess(&$values) {
  if (isset($values['text_format_cid'])) {
    $cid_arr = $values['text_format_cid'];
    foreach($cid_arr as $cid => $key) {
      if ($key == 'content') {
        break;
      }
    }
    
    if (isset($values[$cid]) && isset($values[$cid]['value'])) {
      acquia_include('process', 'ac_shortcode');
      $values[$cid]['value'] = base64_encode($values[$cid]['value']);
    }

  }
}

/**
 * process {{ac_code}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_code_process($attrs, $text = null, $shortcode = '') {
	 acquia_include('process', 'ac_shortcode');
	$_attrs = ac_shortcode_attrs(array(
		), $attrs);

	extract($_attrs);
	
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'ac-b-space';
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

	
	$out = '';
	$out .= '<pre'.drupal_attributes($attributes).'>';
	$out .= '		<code>';
	$out .= '		'.	htmlentities(ac_shortcode_remove_autop(rawurldecode(base64_decode(strip_tags($text)))));
	$out .= '		</code>';
	$out .= '</pre>';

	return $out;
}