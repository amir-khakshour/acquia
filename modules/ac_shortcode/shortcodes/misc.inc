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

function ac_shortcode_misc_shortcode() {
	 return array(
		 'ac_highlight' => array(
				 'title' => t('Highlight'),
				 'description' => t('Highlight content.'),
				 'process callback' => 'ac_shortcode_ac_highlight_process',
				 'js callback' => 'ac_shortcode_ac_highlight_js_settings',
			),
		 'ac_dropcap' => array(
				 'title' => t('Dropcap'),
				 'description' => t('Dropcap letter.'),
				 'process callback' => 'ac_shortcode_ac_dropcap_process',
				 'js callback' => 'ac_shortcode_ac_dropcap_js_settings',
			),
	 );
}

/*==============================================================*/
// {{ac_highlight}} shortcode
/*==============================================================*/
/**
 * Defines {{ac_highlight}} shortcode js settings
 */
function ac_shortcode_ac_highlight_js_settings() {
	$settings['order']			= 100;
	$settings['tinymce'] 		= array('instantInsert' => "[ac_highlight color='']{{CONTENTHERE}}[/ac_highlight]");
	$settings['group']			= t('Misc');
	$settings['group_mn']		= 'misc';
	return $settings;
}

/**
 * process {{ac_highlight}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_highlight_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	
	$_attrs = ac_shortcode_attrs(array(
		'color',
	), $attrs);
	
	extract($_attrs);
	
	$sc_name = str_replace('_', '-', $shortcode);

	$attrs['bg_color'] = isset($attrs['color']) ? $attrs['color'] : NULL;
	
	$attributes = array();

	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = acquia_get_class_by_args(array('bg_color'), $attrs, CHECK_LENGTH);
	
	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------
	
	$html  = '';
	$html .= '<span'.drupal_attributes($attributes).'>';
	$html .= $text;
	$html .= '</span>';
	
	return $html;
}

/*==============================================================*/
// {{ac_dropcap}} shortcode
/*==============================================================*/
/**
 * Defines {{ac_dropcap}} shortcode js settings
 */
function ac_shortcode_ac_dropcap_js_settings() {
	$settings['order']			= 100;
	$settings['tinymce'] 		= array('instantInsert' => "[ac_dropcap color='' bg_color='' border='circled|rounded|square' subtle='true|false']{{CONTENTHERE}}[/ac_dropcap]");
	$settings['group']			= t('Misc');
	$settings['group_mn']		= 'misc';
	return $settings;
}

/**
 * process {{ac_dropcap}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_dropcap_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('options');
	
	$_attrs = ac_shortcode_attrs(array(
		'border' => 'rounded',
		'subtle' => 'false',
		'color' => '',
		'bg_color' => '',
	), $attrs);
	extract($_attrs);
	
	$sc_name = str_replace('_', '-', $shortcode);

	$skins = array_keys(acquia_skins_list());
	
	$attrs_to_class = array('border');
	$styles = array();
	
	if (isset($attrs['color'])) {
		if(in_array($attrs['color'], $skins)) {
			$attrs_to_class[] = 'color';
		}else{
			$styles['color'] = $attrs['color'];
		}
	}

	if (isset($attrs['bg_color'])) {
		if (in_array($attrs['bg_color'], $skins)) {
			if ($subtle == 'true') {
				 $_attrs['border_color'] = $attrs['bg_color'];
				 $attrs_to_class[] = 'border_color';
			}else{
				 $attrs_to_class[] = 'bg_color';
			}
		}else{
			if ($subtle == 'true') {
				 $styles['border-color'] = $attrs['bg_color'];
			}else{
				 $styles['background'] = $attrs['bg_color'];
			}
		}
	}
	
	if ($subtle == 'true') {
	  unset($attrs_to_class['bg_color']);
	  unset($styles['background']);
	}
	
	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = $subtle == 'true' ? 'ac-subtle-style' : NULL; 
	$attributes['class'][] = acquia_get_class_by_args($attrs_to_class, $_attrs, CHECK_LENGTH);
	
	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------
	
	$attributes['style'] = acquia_style_arr_to_tag(	$styles );
	
	$html  = '';
	$html .= '<span'.drupal_attributes($attributes).'>';
	$html .= $text;
	$html .= '</span>';
	
	return $html;
}
