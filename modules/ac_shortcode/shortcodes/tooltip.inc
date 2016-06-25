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

function ac_shortcode_tooltip_shortcode() {
	 return array(
		 'ac_tooltip' => array(
				 'title' => t('tooltip'),
				 'description' => t('Creates a customizable, themeable tooltips.'),
				 'process callback' => 'ac_shortcode_ac_tooltip_process',
				 'js callback' => 'ac_shortcode_ac_tooltip_js_settings',
			),
	 );
}

/**
 * Defines {{ac_highlight}} shortcode js settings
 */
function ac_shortcode_ac_tooltip_js_settings() {
	$settings['order']			= 100;
	$settings['tinymce'] 		= array('instantInsert' => '[ac_tooltip link="#example" title="Hello, I\'m a tooltip!" info="tooltip" info_place="top" info_trigger="hover" info_content="Place a little extra content in here for informational purposes."]{{CONTENTHERE}}[/ac_tooltip]');
	$settings['group']			= t('Misc');
	$settings['group_mn']		= 'misc';
	return $settings;
}

/**
 * process {{ac_tooltip}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_tooltip_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'link' => '#',
		'title' => '#',
		), $attrs);

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$attributes = array('href' => $link);
	$attributes['class'] = $sc_name;
	$attributes['title'] = $title;

	if (isset($attrs['info'])){
		acquia_add_tooltip_libs_by_type($attrs['info']);
		$attributes += (array)acquia_get_tooltip_data_by_attrs($attrs);
	}

	return '<a'.drupal_attributes($attributes).'>'.$text.'</a>';
}