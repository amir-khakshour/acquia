<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_img_slider_shortcode() {
	return array(
		'img_slider' => array (
			'title' => t('Image Slider'),
			'description' => t('Creates image slider'),
			'form callback' => 'ac_shortcode_img_slider_form',
			'values process callback' => 'ac_shortcode_img_slider_preprocess',
			'process callback' => 'ac_shortcode_img_slider_process',
			'sitewide settings' => 'ac_shortcode_img_slider_sitewide_settings',
		),
		'img_slider_item' => array(
			'title' => t('image slider item'),
			'description' => t('An item for image slider'),
			'hidden' => TRUE,
			'enabled' => array('img_slider' => true),
			'process callback' => 'ac_shortcode_img_slider_item_process',
      'values process callback' => 'ac_shortcode_img_slider_item_preprocess',
      'form callback' => 'ac_shortcode_img_slider_item_form',
		)
	);
}

/**
 * Implements edit form of {{img_slider}} shortcode
 */
function ac_shortcode_img_slider_form($form, &$form_state) {
  acquia_include('utility');
  acquia_include('fields');
  acquia_include('options');
 
  $values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
	
	$form['id'] = array(
		'#type' => 'textfield',
		'#title' => t('Slider ID'),
		'#description' => t('for styling purpose you can change it to your own id.'),
		'#default_value' => isset($values['id']) ? $values['id'] : acquia_get_unique_id('img-slider'),
	);
	
	 $form['animation'] = array(
		 '#type' => 'select',
		 '#title' => t('animation'),
		 '#description' => t('Select your animation type.'),
		 '#options' => array('fade' => t('Fade'), 'slide' => t('Slide')),
		 '#default_value' => isset($values['animation']) ? $values['animation'] : NULL,
	 );
	 
	 $form['easing'] = array(
		 '#type' => 'select',
		 '#title' => t('Easing'),
		 '#description' => t('Select easing type for animating slider items.'),
		 '#options' => acquia_easing_types(),
		 '#default_value' => isset($values['easing']) ? $values['easing'] : 'swing',
	 );

  $form['slideshow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animate slider automatically?'),
    '#default_value' => isset($values['slideshow']) && $values['slideshow'] == 'true' ? TRUE : FALSE,
  );

  $form['controlnav'] = array(
	 '#type' => 'checkbox',
	 '#title' => t('Pager?'),
	 '#default_value' => isset($values['controlnav']) && $values['controlnav'] == 'true' ? TRUE : FALSE,
  );
	
	$form['directionnav'] = array(
	 '#type' => 'checkbox',
	 '#title' => t('previous/next navigation?'),
	 '#default_value' => isset($values['directionnav']) && $values['directionnav'] == 'true' ? TRUE : FALSE,
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
 * Implements edit form of {{img_slider_item}} shortcode
 */
/**
 * preprocess {{img_slider}} values from shortcode form before making shortcode string
 */
function ac_shortcode_img_slider_preprocess(&$values) {
  if (!isset($values['id'])) {
		acquia_include('utility');
    $values['id'] = acquia_get_unique_id('img-slider');
  }
	
	if (isset($values['slideshow']) && $values['slideshow'] == TRUE) {
    $values['slideshow'] = 'true';
  }else{
    unset($values['slideshow']);
  }
	 
  if (isset($values['controlnav']) && $values['controlnav'] == TRUE) {
    $values['controlnav'] = 'true';
  }else{
    unset($values['controlnav']);
  }	 
	 
  if (isset($values['directionnav']) && $values['directionnav'] == TRUE) {
    $values['directionnav'] = 'true';
  }else{
    unset($values['directionnav']);
  }
}

function ac_shortcode_img_slider_item_form($form, &$form_state) {
  acquia_include('fields');
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
	
	$form['fid'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose image from media library or upload image to your media library.'),
		'#title' => t('Slide Image'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
	);
	
	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Image Style'),
		'#description' => t('Apply an image style to your slides images'),
		'#options' => image_style_options(),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);
	
	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Link slide'),
		'#description' => t('enter the slide link'),
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

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);
  
  $form[$cid] = array(
    '#type' => 'text_format',
    '#title' => t('Caption'),
    '#description' => t('Enter the slide caption here.'),
    '#default_value' => isset($values['content']) ? $values['content'] : '',
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
 * preprocess {{img_slider_item}} values from shortcode form before making shortcode string
 */
function ac_shortcode_img_slider_item_preprocess(&$values) {
	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link']);
		unset($values['link_target']);
	}
}


/**
 * process {{img_slider_item}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_img_slider_item_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('content');
	acquia_include('utility');
	acquia_include('media');
	
	$_attrs = ac_shortcode_attrs(array(
		'fid' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	//---------------------------------------
	
	$attributes = array();
	$attributes['class'] = $classes;

	
	$media = array('fid' => $fid);
	if (isset($attrs['link']) && !empty($attrs['link'])) {
		$media['link']['path'] = $attrs['link'];
		$media['link']['options']['attributes']['target'] = isset($attrs['link_target']) ? $attrs['link_target'] : '_self';
	}
	
	if (isset($attrs['style']) && !empty($attrs['style'])) {
		$media['style']['image_style'] = $attrs['style'];
	}
	
	$out  = '<li class="slide-item">';
	$out .= acquia_image_format_simple($media);
	if (trim(	$text) != '') {
		$out .= '    <p class="flex-caption ac-type-hidden-phone">';
		$out .=       '<span class="caption-inner">' .$text .'</span>';
		$out .= '    </p>';
	}
	$out .= '</li>';
	
	return $out;
}

/**
 * process {{img_slider}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_img_slider_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
		'animation' => 'fade',
		'easing' => 'swing',
		'slideshow' => 'false',
		'controlnav' => 'false',
		'directionnav' => 'false',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	
	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = 'flexslider';
	$attributes['class'][] = $_attrs['controlnav'] != 'false' ? 'ac-pager-enabled' : null;

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	//---------------------------------------
	
  if (!isset($attrs['id'])) {
		acquia_include('utility');
    $attrs['id'] = acquia_get_unique_id('img-slider');
  }
	$attributes['id'] = $attrs['id'];

	// Animate data
	if (isset($attrs['animate'])) {
		$attrs['where'] = isset($attrs['where']) ? $attrs['where'] : 'block';
		$attributes += acquia_get_anim_data_by_attrs($attrs);
		$attributes['data-anim-childs'] = $attrs['where'] == 'block' ? '.item' : '.icon';
	}
  
	
	drupal_add_library('acquia', 'flexslider');
	
	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= '	<ul class="slides">';
	$out .= '		'.$text;
	$out .= '	</ul>';
	$out .= '</div>';
	
	$out .='<script type="text/javascript">
	(function ($) {
		$(document).ready(function() {
			if (jQuery().flexslider) {
				$("#'.$attrs['id'].'").flexslider({
					animation: "'.$animation.'",
					easing: "'.$easing.'",
					slideshow: '.$slideshow.',
					touch: true,
					controlNav: '.$controlnav.',
					directionNav: '.$directionnav.',
					prevText: \'<i class="icon-left-open-big"></i>\',
					nextText: \'<i class="icon-right-open-big"></i>\',
				});
			}
		});
	})(jQuery);
	</script>';

	return $out;
}

/**
 * Defines {{img_slider}} vars that can be set from theme settings form
 */
function ac_shortcode_img_slider_sitewide_settings() {
	
	$ops = image_style_options();
	$form['ac_img_slider_style'] = array(
		'#type' => 'select',
		'#title' => t('Image Style'),
		'#description' => t('default image style for your slider images'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : '',
	);
	
	return $form;
}

