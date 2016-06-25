<?php
/**
 * @file shortcode defenition of teaser
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

function ac_shortcode_teaser_shortcode() {
	 return array(
		'ac_teaser' => array(
			'title' => t('teaser'),
			'description' => t('Adding video or image content as teaser box style.'),
			'form callback' => 'ac_shortcode_ac_teaser_form',
			'values process callback' => 'ac_shortcode_ac_teaser_preprocess',
			'process callback' => 'ac_shortcode_ac_teaser_process',
		),
	 );
}

/**
 * Implements edit form of {{ac_teaser}} shortcode
 */
function ac_shortcode_ac_teaser_form($form, &$form_state) {
	acquia_include('utility');
	acquia_include('options');
	
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
		'#description' => t('Select content type.'),
		'#title' => t('Type'),
		'#options' => array('image' => t('Image'), 'video' => t('Video') ),
		'#default_value' => isset($values['type']) ? $values['type'] : NULL,
	);

	$form['media'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose teaser media from media library or upload media to your media library.'),
		'#title' => t('Media'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/misc',
			),
		),
	);
	
	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Image title/Alternate text?'),
		//'#description' => t('Add title o.'),
		'#default_value' => isset($values['title']) ? $values['title'] : '',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'image'),
			),
		),
	);
	
	$form['alt'] = array(
		'#type' => 'textfield',
		'#title' => t('Image alt?'),
		//'#description' => t('Add title o.'),
		'#default_value' => isset($values['alt']) ? $values['alt'] : '',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'image'),
			),
		),
	);

	
	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Image Link?'),
		'#description' => t('Where should your image link to? Enter "front" without quotation marks to link in front page.'),
		'#default_value' => isset($values['link']) ? $values['link'] : '',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'image'),
			),
		),
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
	
	$ops = image_style_options();
	add_default_option($ops);
	
	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('media Style'),
		'#description' => t('Apply an style to the media'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);
	
	$ops = acquia_image_frame_list();
	add_default_option($ops);
	
	$form['frame'] = array(
		'#type' => 'select',
		'#title' => t('teaser frame'),
		'#description' => t('Select the frame style from the list.'),
		'#default_value' => isset($values['frame']) ? $values['frame'] : 'sw',
		'#options' => $ops,
	);
	
	$form['gridy'] = array(
		'#attributes' => array('data-help' => t('turn it on if this item is in grid shortcode.')),
		'#type' => 'checkbox',
		'#title' => t('Enable gridy?'),
		//'#description' => t('chenge to On if you want to enable lightbox on this image.'),
		'#default_value' => isset($values['gridy']) && $values['gridy'] == 'true' ? TRUE :FALSE,
	);
	
	$values['lightbox'] = isset($values['lightbox']) && $values['lightbox'] == 'true' ? TRUE : FALSE;
	$form['lightbox'] = array(
		'#type' => 'checkbox',
		'#title' => t('open in lightbox?'),
		'#description' => t('chenge to On if you want to enable lightbox.'),
		'#default_value' => $values['lightbox'],
	);
	
	$form['lightbox_container'] = array(
		'#type' => 'container',
		'#states' => array(
			'visible' => array(
					':input[name="type"]' => array('value' => 'image'),
			),
		),
	);
	
	$form['lightbox_container']['lightbox_style'] = array(
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
	
	$form['lightbox_container']['video'] = array(
	  '#type' => 'fieldset',
	  '#tree' => TRUE,
		'#description' => t('You can set a video to be shown in lightbox window instead of image.'),
		'#states' => array(
			'visible' => array(
					':input[name="lightbox"]' => array('checked' => TRUE),
			),
		),
	);
	$form['lightbox_container']['video']['fid'] = array(
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
		 '#title' => t('Content'),
		 '#description' => t('Enter the teaser content.'),
		 '#default_value' => isset($values['content']) ? $values['content'] : array(),
		 '#format' => NULL,
		 '#rows' => 15,
	 );

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);
	
	$form['caption_align'] = array(
		'#type' => 'select',
		'#title' => t('Caption alignment'),
		'#description' => t('How to align your caption.'),
		'#default_value' => isset($values['caption_align']) ? $values['caption_align'] : '',
		'#options' => acquia_align_list(),
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
 * preprocess {{ac_teaser}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_teaser_preprocess(&$values) {
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
 * process {{ac_teaser}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_teaser_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
		'fid'      => '',
		'loop'     => 'false', /* Enable repeating teaser: True/False */
		'autoplay' => 'false', /* Automatically start teaser: True/False */
		'preload'  => 'false', /* Preload teaser before playing: True/False */
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
		 if ( $file_type != 'teaser' ) {
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
	
	$attributes['id'] = !empty($id) ? $id : uniqid('ac-teaser-');

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
		$out  = "<!--[if lt IE 9]><script>document.createElement('teaser');</script><![endif]-->\n";
		$out .= '<teaser'.drupal_attributes($attributes).'>';
		$out .= sprintf( '<source type="%s" src="%s" />', $meta, $src );
		$out .= sprintf( '<a href="%1$s">%1$s</a>', $src );
		$out .= '</teaser>';
	}else {
		$out = '<div'.drupal_attributes($attributes).'>';
		$out .= '  '.$text;
		$out .= '</div>';
	}
	return $out;
}