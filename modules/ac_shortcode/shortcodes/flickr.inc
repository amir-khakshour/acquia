<?php
/**
 * @file shortcode defenition of flickr photo
 */

// You can use your own if you like
if (!defined('FLICKR_API_KEY')) {
	 define('FLICKR_API_KEY', "d348e6e1216a46f2a4c9e28f93d75a48");
}

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

function ac_shortcode_flickr_shortcode() {
	 return array(
		 'ac_flickr' => array(
				 'title' => t('flickr'),
				 'description' => t('Extracting image stream from flickr.'),
				 'form callback' => 'ac_shortcode_ac_flickr_form',
				 'values process callback' => 'ac_shortcode_ac_flickr_preprocess',
				 'process callback' => 'ac_shortcode_ac_flickr_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_flickr}} shortcode
 */
function ac_shortcode_ac_flickr_form($form, &$form_state) {
	acquia_include('options');
	$values = isset($form_state['values']) ? $form_state['values'] : array();
	$form['id'] = array(
		'#type' => 'textfield',
		'#title' => t('Flickr ID'),
		'#description' => t('To find your flickID visit !idGettr.', array('!idGettr' => l('idGettr', 'http://idgettr.com/'))),
		'#default_value' => isset($values['id']) ? $values['id'] : '',
	);
	
	$form['nums'] = array (
    '#type' => 'select',
    '#title' => t('Number of photos'),
    '#description' => t ( 'Number of photos; e.g., 4' ),
    '#default_value' => isset($values['nums']) ? $values['nums'] : 9,
		'#options' => drupal_map_assoc ( range (1, 9) ),
  );
	
	$form['size'] = array (
    '#type' => 'select',
    '#title' => t('Size'),
    '#description' => t ( 'Photo size.' ),
    '#default_value' => isset($values['size']) ? $values['size'] : 's',
		'#options' => array('s'=> t('Small'), 't' => t('Thumbnail'), 'm' => t('Medium')),
  );
	
	$form['type'] = array (
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t ( 'Photo stream type.' ),
    '#default_value' => isset($values['type']) ? $values['type'] : 'user',
		'#options' => array('user'=> t('user'), 'group' => t('group')),
  );
	
	$form['display'] = array (
    '#type' => 'select',
    '#title' => t('Display'),
    '#description' => t ( 'Photo stream type.' ),
    '#default_value' => isset($values['display']) ? $values['display'] : 'latest',
		'#options' => array('latest'=> t('Latest'), 'random' => t('Random')),
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
 * Process {{ac_flickr}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_flickr_preprocess(&$values) {

}

/**
 * process {{ac_flickr}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_flickr_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
    'id' => '95572727@N00',
    'nums' => '6',
    'type' => 'user',
    'display' => 'latest',
    'size' => 's',
  ), $attrs);
	
	extract($_attrs);
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
	
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= "\n\t\t\t".'<script type="text/javascript" src="http://www.flickr.com/badge_code_v2.gne?count='. $nums . '&amp;display='. $display . '&amp;size='. $size .'&amp;layout=x&amp;source='. $type .'&amp;'. $type .'='. $id .'"></script>';
	$out .= "\n\t\t\t".'<p class="flickr_stream_wrap"><a class="db_follow_btn db_flickr_stream" href="http://www.flickr.com/photos/'. $id .'">'.t("View stream on flickr").'</a></p>';
	$out .= '</div>';

	return $out;
}

