<?php
/**
 * @file shortcode defenition of video
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

function ac_shortcode_video_shortcode() {
	 return array(
			'ac_video' => array(
				'title' => t('Video'),
				'description' => t('Adding vide file to post.'),
				'form callback' => 'ac_shortcode_ac_video_form',
				'values process callback' => 'ac_shortcode_ac_video_preprocess',
				'process callback' => 'ac_shortcode_ac_video_process',
				'sitewide settings' => 'ac_shortcode_ac_video_sitewide_settings',
			),
	 );
}

/**
 * Implements edit form of {{ac_video}} shortcode
 */
function ac_shortcode_ac_video_form($form, &$form_state) {
	acquia_include('utility');
	acquia_include('options');
	acquia_include('fields');
	acquia_load_resources('mediabrowser');
	
	$cid = &drupal_static(__FUNCTION__, NULL);

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

	$form['fid'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose Video.'),
		'#title' => t('Video source'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('video'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/video',
			),
		),
	);
	
	$ops = image_style_options();
	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('video Style'),
		'#description' => t('Apply an style to the video'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);
	
	$ops = acquia_video_frame_list();
	add_default_option($ops);
	
	$form['frame'] = array(
		'#type' => 'select',
		'#title' => t('Video frame'),
		'#description' => t('Select the Video frame style from the list.'),
		'#default_value' => isset($values['frame']) ? $values['frame'] : 'sw',
		'#options' => $ops,
	);
	
	$form['poster'] = array(
		'#attributes' => array('class' => array('ac-upload')),
		'#type' => 'textfield',
		'#description' => t('click on to choose Video poster.'),
		'#title' => t('poster'),
		'#default_value' => isset($values['poster']) ? $values['poster'] : '',
	);
	
	$values['loop'] = isset($values['loop']) && $values['loop'] == 'true' ? TRUE : FALSE;
	$form['loop'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable repeating Video?'),
		'#description' => t('chenge to On if you want to enable repeating Video.'),
		'#default_value' => $values['loop'],
	);
	
	$values['autoplay'] = isset($values['autoplay']) && $values['autoplay'] == 'true' ? TRUE : FALSE;
	$form['autoplay'] = array(
		'#type' => 'checkbox',
		'#title' => t('Automatically start Video?'),
		'#description' => t('chenge to On if you want to auto play the Video.'),
		'#default_value' => $values['autoplay'],
	);
	
  $values['preload'] = isset($values['preload']) && $values['preload'] == 'true' ? TRUE : FALSE;
	$form['preload'] = array(
		'#type' => 'checkbox',
		'#title' => t('Preload Video before playing?'),
		'#description' => t('chenge to On if you want this Video preloads before playing.'),
		'#default_value' => $values['preload'],
	);
	
	
	$values['fluid'] = isset($values['fluid']) && $values['fluid'] == 'false' ? FALSE : TRUE;
	$form['fluid'] = array(
		'#type' => 'checkbox',
		'#title' => t('fluid width video?'),
		'#description' => t('chenge to On if you want fluid width video.'),
		'#default_value' => $values['fluid'],
	);
	
	$form['width'] = array(
		'#type' => 'textfield',
		'#title' => t('Video width'),
		'#field_suffix' => t('px'),
		'#description' => t('Enter an integer value for your video width.'),
		'#default_value' => isset($values['width']) ? $values['width'] : '',
		'#states' => array(
			'invisible' => array(
					':input[name="fluid"]' => array('checked' => TRUE),
			),
			'disabled' => array(
					':input[name="fluid"]' => array('checked' => TRUE),
			),
		),
	);
	
	$form['height'] = array(
		'#type' => 'textfield',
		'#title' => t('Video height'),
		'#field_suffix' => t('px'),
		'#description' => t('Enter an integer value for your video height.'),
		'#default_value' => isset($values['height']) ? $values['height'] : '',
		'#states' => array(
			'invisible' => array(
					':input[name="fluid"]' => array('checked' => TRUE),
			),
			'disabled' => array(
					':input[name="fluid"]' => array('checked' => TRUE),
			),
		),
	);
	
	$form['align'] = array(
		'#type' => 'select',
		'#title' => t('Video alignment'),
		'#description' => t('How to align your Video.'),
		'#default_value' => isset($values['align']) ? $values['align'] : (acquia_variable_get('doc_direction') == 'LTR' ? 'left' : 'right'),
		'#options' => acquia_align_list(),
	);
	
	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);
	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Caption'),
		'#description' => t('Enter the video caption here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	 $settings = array(
		 'title' => t('Video'),
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
 * preprocess {{ac_video}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_video_preprocess(&$values) {
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
	
	if (isset($values['fluid']) && $values['fluid'] == TRUE) {
    $values['fluid'] = 'true';
    unset($values['width']);
    unset($values['height']);
	}else{
     $values['fluid'] = 'false';
	}
}

/**
 * process {{ac_video}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_video_process($attrs, $text = null, $shortcode = '') {
	acquia_include('media');

	$sc_name = str_replace('_', '-', $shortcode);
	
	if (empty($attrs['fid']) || !is_numeric($attrs['fid'])) {
		return;
	}
	$video = array();
	$video['fid'] = $attrs['fid'];
	$video['options'] = $attrs;
	$video['options']['autoplay'] = isset($video['options']['autoplay']) && $video['options']['autoplay'] == 'true' ? TRUE : FALSE;
	$video['options']['loop'] = isset($video['options']['loop']) && $video['options']['loop'] == 'true' ? TRUE : FALSE;
	$video['options']['preload'] = isset($video['options']['preload']) && $video['options']['preload'] == 'true' ? TRUE : FALSE;
	$video['options']['class'] = $sc_name . '-wrap clearfix';
	if (isset($attrs['fluid']) && $attrs['fluid'] == 'true') {
			$video['options']['fluid'] = TRUE;
  }else {
			$video['options']['fluid'] = FALSE;
	}
	
  if (isset($attrs['frame']) && !empty($attrs['frame'])) {
	 	acquia_include('utility');
    $video['style']['frame'] = ($attrs['frame'] == 'sw') ? acquia_theme_get_settings('video_frame', null, 'shortcodes') : $attrs['frame'];
  }
	
	if (isset($attrs['style']) && !empty($attrs['style'])) {
    $video['style']['video_style'] = $attrs['style'];
  }

	$video['wrapper']['attributes'] = array();
	if (isset($attrs['animate'])){
		$video['animate']['type'] = $attrs['animate'];
		$video['animate']['when'] = isset($attrs['when']) ? $attrs['when'] : NULL;
		// image data attributes
		$video['wrapper']['attributes'] += (array)acquia_get_anim_data_by_attrs($attrs);
	}
	
	$text = trim($text);
	if (!empty($text)) {
		$video['caption'] = array('text' => $text);
		$video['caption']['attributes'] = array('class' => array('caption'));
	}

	return acquia_video_format_extended($video);
}

/**
 * Defines {{ac_video}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_video_sitewide_settings() {
	acquia_include('options');
	return array(
		'video_frame' => array(
			'#type' => 'select',
			'#title' => t('Video frame type'),
			'#description' => t('Select the default sitewide video frame type from the list.'),
			'#options' => acquia_video_frame_list(),
		),
	);
}
