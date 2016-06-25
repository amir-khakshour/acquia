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
function ac_shortcode_img_frame_shortcode() {
	return array(
		'ac_img_frame' => array(
			'title' => t('Image frame'),
			'description' => t('Creates a framed image style.'),
			'form callback' => 'ac_shortcode_ac_img_frame_form',
			'values process callback' => 'ac_shortcode_ac_img_frame_preprocess',
			'process callback' => 'ac_shortcode_ac_img_frame_process',
			'sitewide settings' => 'ac_shortcode_ac_img_frame_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_img_frame}} shortcode
 */
function ac_shortcode_ac_img_frame_form($form, &$form_state) {
	// Add required files
	acquia_include('utility');
	acquia_include('options');
	acquia_include('fields');

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

	$ops = acquia_image_frame_list();
	add_default_option($ops);

	$form['frame'] = array(
		'#type' => 'select',
		'#title' => t('Image frame'),
		'#description' => t('Select the image frame style from the list.'),
		'#default_value' => isset($values['frame']) ? $values['frame'] : 'sw',
		'#options' => $ops,
	);

	$form['fid'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose image from media library or upload image to your media library.'),
		'#title' => t('Image source'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
	);

	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Image Link?'),
		'#description' => t('Where should your image link to? Enter "front" without quotation marks to link in front page.'),
		'#default_value' => isset($values['link']) ? $values['link'] : '',
	);

	$form['link_target'] = array(
		'#type' => 'select',
		'#title' => t('Open Link in new Window?'),
		'#description' => t('Select here if you want to open the linked page in a new window'),
		'#default_value' => isset($values['link_target']) ? $values['link_target'] : '_self',
		'#options' => array(
			'_blank' => t('Yes, open in new window'),
			'_self' => t('No, open in same window'),
		),
		'#states' => array(
			'disabled' => array(
				':input[name="link"]' => array('value' => ''),
			),
			'invisible' => array(
				':input[name="link"]' => array('value' => ''),
			),
		),
	);

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Image title/Alternate text?'),
		//'#description' => t('Add title o.'),
		'#default_value' => isset($values['title']) ? $values['title'] : '',
	);
	$form['hover_text'] = array(
		'#type' => 'textfield',
		'#title' => t('Hover text'),
		'#description' => t('text to display on hover.'),
		'#default_value' => isset($values['hover_text']) ? $values['hover_text'] : t('Click to open'),
		'#states' => array(
			'visible' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
			'enabled' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
		),
	);

	$ops = acquia_image_effects();
	add_default_option($ops);
	$form['effect'] = array(
		'#type' => 'select',
		'#title' => t('Image Effect'),
		'#description' => t('Apply an Effect to the image on mouse hover.'),
		'#options' => $ops,
		'#default_value' => isset($values['effect']) ? $values['effect'] : 'sw',
	);

	$ops = image_style_options();
	add_default_option($ops);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Image Style'),
		'#description' => t('Apply an image style to the image'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);

	$form['gridy'] = array(
		'#attributes' => array('data-help' => t('turn it on if this item is in grid shortcode.')),
		'#type' => 'checkbox',
		'#title' => t('Enable gridy image?'),
		//'#description' => t('chenge to On if you want to enable lightbox on this image.'),
		'#default_value' => isset($values['gridy']) && $values['gridy'] == 'true' ? TRUE :FALSE,
	);

	$values['lightbox'] = isset($values['lightbox']) && $values['lightbox'] == 'true' ? TRUE : FALSE;
	$form['lightbox'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable lightbox effect?'),
		'#description' => t('chenge to On if you want to enable lightbox on this image.'),
		'#default_value' => $values['lightbox'],
	);

	$form['lightbox_style'] = array(
		'#type' => 'select',
		'#title' => t('Lightbox Image Style'),
		'#description' => t('Style of image in lightbox page.'),
		'#options' => $ops,
		'#default_value' => isset($values['lightbox_style']) ? $values['lightbox_style'] : 'sw',
		'#states' => array(
			'visible' => array(
				':input[name="lightbox"]' => array('checked' => TRUE),
			),
		),
	);

	$form['video'] = array(
		'#type' => 'fieldset',
		'#tree' => TRUE,
		'#description' => t('You can set a video to be shown in lightbox window instead of image.'),

	);
	$form['video']['fid'] = array(
		'#type' => 'media',
		'#title' => t('video source'),
		'#default_value' => isset($values['video']) ? array('fid' => $values['video']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('video'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/vids',
			),
		),
		'#states' => array(
			'visible' => array(
				':input[name="lightbox"]' => array('checked' => TRUE),
			),
		),
	);


	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form['align'] = array(
		'#type' => 'select',
		'#title' => t('Image alignment'),
		'#description' => t('How to align your image.'),
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
		'#description' => t('Enter the image caption content here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : array(),
		'#format' => NULL,
		'#rows' => 15,
		'#states' => array(
			'invisible' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
			'disabled' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
		),
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form['caption_align'] = array(
		'#type' => 'select',
		'#title' => t('Caption alignment'),
		'#description' => t('How to align your caption.'),
		'#default_value' => isset($values['caption_align']) ? $values['caption_align'] : '',
		'#options' => acquia_align_list(),
		'#states' => array(
			'invisible' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
			'disabled' => array(
				':input[name="frame"]' => array('value' => 'simple-linked'),
			),
		),
	);


	$settings = array(
		'title' => t('Image'),
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	/** Add popOver Tooltips **/
	$settings = array(
		'title' => t('Image Frame'),
		'add_title' => TRUE,
	);
	if (isset($values['info'])) {
		$settings['info'] = $values['info'];
		if (isset($values['info_title'])) {
			$settings['info_title'] = $values['info_title'];
		}
		if (isset($values['info_place'])) {
			$settings['info_place'] = $values['info_place'];
		}
		if (isset($values['info_trigger'])) {
			$settings['info_trigger'] = $values['info_trigger'];
		}
		if (isset($values['info_title'])) {
			$settings['info_title'] = $values['info_title'];
		}
		if (isset($values['info_content'])) {
			$settings['info_content'] = $values['info_content'];
		}
	}

	// add animate fields
	acquia_field_tooltip($form, $settings);

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
 * preprocess {{ac_img_frame}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_img_frame_preprocess(&$values) {
	if (isset($values['video']) && isset($values['video']['fid'])) {
		$values['video'] = $values['video']['fid']['fid'];
	}

	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link']);
		unset($values['link_target']);
	}

	if (isset($values['src'])) {
		unset($values['src']);
	}

	if (isset($values['lightbox']) && $values['lightbox'] == TRUE) {
		$values['lightbox'] = 'true';
	}else{
		$values['lightbox'] = 'false';
	}

	if (isset($values['gridy']) && $values['gridy'] == TRUE) {
		$values['gridy'] = 'true';
	}else{
		unset($values['gridy']);
	}

	if (isset($values['caption_align']) && $values['caption_align'] == '') {
		unset($values['caption_align']);
	}

	if (isset($values['frame']) && $values['frame'] == 'simple-linked') {
		unset($values[$values['cid']]);
		unset($values['caption_align']);
	}else{
		unset($values['hover_text']);
	}

}

/**
 * process Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_img_frame_process($attrs, $text = null, $shortcode = '') {
	acquia_include('utility');
	acquia_include('content');
	acquia_include('media');

	$_attrs = ac_shortcode_attrs(array(
		'fid' => '',
		'frame' => '',
		'align' => '',
		'link' => '',
		'link_target' => '',
		'style' => '',
		'title' => '',
		'gridy' => FALSE,
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	if (empty($fid) || !is_numeric($fid)) {
		drupal_set_message('ACQUIA: shortcode '.$shortcode.' must have value fid.');
		return '';
	}

	$frame = $frame != 'none' ? $frame : '';

	$image = array();
	$image['fid'] = $fid;
	$image['style'] = array();
	$image['style']['frame'] = ($frame == 'sw') ? acquia_theme_get_settings('image_frame', null, 'shortcodes') : $frame;
	$image['style']['image_style'] = ($style == 'sw') ? acquia_theme_get_settings('image_style', null, 'shortcodes') : $style;
	$image['style']['align'] = $align;
	$image['style']['gridy'] = $gridy;

	if (isset($attrs['effect']) && $attrs['effect'] !='' && $attrs['effect'] !='none') {
		// Get sitewide settings
		$image['style']['effect'] = ($attrs['effect'] == 'sw') ? acquia_theme_get_settings('image_effect', null, 'shortcodes') : $attrs['effect'];
	}

	if (isset($attrs['lightbox']) && $attrs['lightbox'] == 'true') {
		$image['style']['lightbox'] = TRUE;
		if (isset($attrs['lightbox_style']) && !empty($attrs['lightbox_style'])) {
			if (isset($attrs['video']) && !empty($attrs['video'])) {
				$image['style']['video'] = $attrs['video'];
			}
			$image['style']['lightbox_style'] = ($attrs['lightbox_style'] == 'sw') ?
				acquia_theme_get_settings('image_lightbox_style', null, 'shortcodes') : $attrs['lightbox_style'];
		}
	}

	// image classes
	$image['attributes'] = array();
	$image['attributes']['alt'] = $title;
	$image['attributes']['class'] = array();
	$image['attributes']['class'][] = $sc_name;


	if (isset($attrs['animate'])){
		$image['animate'] = array();
		$image['animate']['type'] = $attrs['animate'];
		$image['animate']['when'] = $attrs['when'];
	}

	// Image wrapper wrapper data
	$image['wrapper']['attributes'] = array();
	$image['wrapper']['attributes']['class'][] = $sc_name.'-wrap';
	$image['wrapper']['attributes']['class'][] = 'clearfix';

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$image['wrapper']['attributes']['class'][] = $class;
		}
	}
	$image['wrapper']['attributes']['class'] = array_filter($image['wrapper']['attributes']['class'], 'strlen');
	//---------------------------------------

	// image data attributes
	if (isset($attrs['animate'])){
		$image['wrapper']['attributes'] += (array)acquia_get_anim_data_by_attrs($attrs);
	}

	if (isset($attrs['info'])){
		acquia_add_tooltip_libs_by_type($attrs['info']);
		$image['wrapper']['attributes'] += (array)acquia_get_tooltip_data_by_attrs($attrs);
	}

	if (!empty($link)) {
		$image['link'] = array('path' => $link);
		$image['link']['options'] = array('target' => $link_target);
	}

	$text = trim($text);
	if (!empty($text)) {
		$image['caption'] = array('text' => $text);
		$image['caption']['attributes']['class'][] = 'caption';
		$image['caption']['attributes']['class'][] = 'clearfix';

		if (isset($attrs['caption_align'])) {
			$attrs['align'] = $attrs['caption_align'];
			$image['caption']['attributes']['class'][] = acquia_get_class_by_args(array('align'), $attrs, CHECK_LENGTH);
		}
	}

	return acquia_image_format_extended($image);
}

/**
 * Defines {{ac_img_frame}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_img_frame_sitewide_settings() {
	acquia_include('options');
	return array(
		'image_frame' => array(
			'#type' => 'select',
			'#title' => t('Image frame type'),
			'#description' => t('Select the default sitewide image frame type from the list.'),
			'#options' => acquia_image_frame_list(),
		),
		'image_style' => array(
			'#type' => 'select',
			'#title' => t('Image style'),
			'#description' => t('Select the default sitewide image style to apply to your image frames.'),
			'#options' => image_style_options(),
		),
		'image_lightbox_style' => array(
			'#type' => 'select',
			'#title' => t('lightbox style'),
			'#description' => t('Select the default sitewide lightbox style to apply to your image frames.'),
			'#options' => image_style_options(),
		),
		'image_effect' => array(
			'#type' => 'select',
			'#title' => t('Image Effect'),
			'#description' => t('Apply an Effect to the image on mouse hover.'),
			'#options' => acquia_image_effects(),
		),
	);
}
