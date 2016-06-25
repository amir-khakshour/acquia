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

function ac_shortcode_audio_shortcode() {
	 return array(
		'ac_audio' => array(
			'title' => t('Audio'),
			'description' => t('Adding Audio in mp3 format.'),
			'form callback' => 'ac_shortcode_ac_audio_form',
			'values process callback' => 'ac_shortcode_ac_audio_preprocess',
			'process callback' => 'ac_shortcode_ac_audio_process',
		),
	 );
}

/**
 * Implements edit form of {{ac_audio}} shortcode
 */
function ac_shortcode_ac_audio_form($form, &$form_state) {
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
	
	$form = array();

	$form['type'] = array(
		'#type' => 'select',
		'#description' => t('Select embed for internet source files and local for uploading audio file to your server.'),
		'#title' => t('Source type'),
		'#options' => array('local' => t('Local file - from medial library'), 'embed' => t('Embed file - internet sources') ),
		'#default_value' => isset($values['type']) ? $values['type'] : NULL,
	);

	 $form['text_format_cid'] = array(
		 '#type' => 'value',
		 '#value' => array($cid => 'content'),// key of cids and related real form id
	 );
	 
	 $form['embed'] = array(
		 '#type' => 'fieldset',
		 '#title' => t('Embed Audio settings'),
		 '#states' => array(
			 'visible' => array(
					 ':input[name="type"]' => array('value' => 'embed'),
			 ),
		 ),
	 );
	 
	 $form['embed'][$cid] = array(
		 '#type' => 'text_format',
		 '#title' => t('Content'),
		 '#description' => t('Enter the audio embed code here.'),
		 '#default_value' => isset($values['content']) ? $values['content'] : array(),
		 '#format' => NULL,
		 '#rows' => 15,
	 );
	 
	$form['local'] = array(
		'#type' => 'fieldset',
		'#title' => t('Local Audio settings'),
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'local'),
			),
		),
	);
	
	$form['local']['fid'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose Audio from media library or upload Audio to your media library.'),
		'#title' => t('Audio source'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('audio'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/audio',
			),
		),
	);
	
	$values['loop'] = isset($values['loop']) && $values['loop'] == 'true' ? TRUE : FALSE;
	$form['local']['loop'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable repeating Video?'),
		'#description' => t('chenge to On if you want to enable repeating Video.'),
		'#default_value' => $values['loop'],
	);
	
	$values['autoplay'] = isset($values['autoplay']) && $values['autoplay'] == 'true' ? TRUE : FALSE;
	$form['local']['autoplay'] = array(
		'#type' => 'checkbox',
		'#title' => t('Automatically start Video?'),
		'#description' => t('chenge to On if you want to auto play the Video.'),
		'#default_value' => $values['autoplay'],
	);
	
  $values['preload'] = isset($values['preload']) && $values['preload'] == 'true' ? TRUE : FALSE;
	$form['local']['preload'] = array(
		'#type' => 'checkbox',
		'#title' => t('Preload Audio before playing?'),
		'#description' => t('chenge to On if you want this Video preloads before playing.'),
		'#default_value' => $values['preload'],
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
 * preprocess {{ac_audio}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_audio_preprocess(&$values) {
	 if (isset($values['type']) && $values['type'] == 'embed') {
			unset($values['loop']);
			unset($values['autoplay']);
			unset($values['preload']);
	 }else{
			if (isset($values['loop']) && $values['loop'] == TRUE) {
				$values['loop'] = 'true';
			}else{
				$values['loop'] = 'false';
			}
			
			if (isset($values['autoplay']) && $values['autoplay'] == TRUE) {
				$values['autoplay'] = 'true';
			}else{
				$values['autoplay'] = 'false';
			}
			
			if (isset($values['preload']) && $values['preload'] == TRUE) {
				$values['preload'] = 'true';
			}else{
				$values['preload'] = 'false';
			}
	 }

}

/**
 * process {{ac_audio}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_audio_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
		'fid'      => '',
		'loop'     => 'false', /* Enable repeating Audio: True/False */
		'autoplay' => 'false', /* Automatically start Audio: True/False */
		'preload'  => 'false', /* Preload Audio before playing: True/False */
		'id'  => '',
		'type'  => '',
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', $shortcode);
	
	$attributes = array();
	
	if ($type == 'local') {
	 if (empty($fid) || !is_numeric($fid)) {
			 return;
		 }
	 
		 $uri	= file_load($fid)->uri;
		 $meta = file_get_mimetype($uri);
		 $src	= file_create_url($uri);
		 
		 $file_type = substr( $meta, 0, strpos($meta, '/') );
		 if ( $file_type != 'audio' ) {
			 return sprintf( '<a class="ac-embedded-video" href="%s">%s</a>', $src, $src);
		 }
		 

		 if ($loop == 'true') {
			 $attributes['loop'] ='true';
		 }
		 if ($autoplay == 'true') {
			 $attributes['autoplay'] ='true';
		 }
		 if ($preload == 'true') {
			 $attributes['preload'] ='true';
		 }
	}else{
	 
	}
	
	$attributes['id'] = !empty($id) ? $id : uniqid('ac-audio-');

	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------
	
	if ($type == 'local') {
		$attributes['style'] = array();
		$attributes['style']['width'] = '100%';
		$attributes['style'] = acquia_style_arr_to_tag(	$attributes['style'] );
		$attributes['controls'] = 'controls';
	}
	
	foreach ($attributes as $attr => $val) {
		if ( empty($val) ) {
			unset( $attributes[$attr] );
		}
	}
	
		// Add assets
	acquia_load_resources('video');
	
	if ($type == 'local') {
		$out  = "<!--[if lt IE 9]><script>document.createElement('audio');</script><![endif]-->\n";
		$out .= '<audio'.drupal_attributes($attributes).'>';
		$out .= sprintf( '<source type="%s" src="%s" />', $meta, $src );
		$out .= sprintf( '<a href="%1$s">%1$s</a>', $src );
		$out .= '</audio>';
	}else {
		$out = '<div'.drupal_attributes($attributes).'>';
		$out .= '  '.$text;
		$out .= '</div>';
	}
	return $out;
}