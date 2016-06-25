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
function ac_shortcode_image_shortcode() {
  return array(
	'ac_image' => array(
	  'title' => t('Simple Image'),
	  'description' => t('Creates a simple image HTML.'),
	  'form callback' => 'ac_shortcode_ac_image_form',
	  'values process callback' => 'ac_shortcode_ac_image_preprocess',
	  'process callback' => 'ac_shortcode_ac_image_process',
	),
  );
}

/**
 * Implements edit form of {{ac_image}} shortcode
 */
function ac_shortcode_ac_image_form($form, &$form_state) {
  // Add required files
  acquia_include('utility');
  acquia_include('options');
  acquia_include('fields');

  $values = isset($form_state['values']) ? $form_state['values'] : array();

  $form = array();

  $ops = acquia_image_frame_list();
  add_default_option($ops);

  $form['fid'] = array(
	'#type' => 'media',
	'#description' => t('click on to choose image from media library or upload image to your media library.'),
	'#title' => t('Image source'),
	'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
  );

  $form['src'] = array(
	'#type' => 'textfield',
	'#description' => t('Insert your image URL here if it\'s out of Drupal public files directory.'),
	'#title' => t('Image source from web'),
	'#default_value' => isset($values['src']) && !isset($values['fid']) ? $values['src'] : NULL,
  );

  $ops = image_style_options();
  add_default_option($ops);

  $form['style'] = array(
	'#type' => 'select',
	'#title' => t('Image Style'),
	'#description' => t('Apply an image style to the image. this will be ignored in case of image source is not on public directory'),
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

  $form['title'] = array(
	'#type' => 'textfield',
	'#title' => t('Image title/Alternate text?'),
	//'#description' => t('Add title o.'),
	'#default_value' => isset($values['title']) ? $values['title'] : '',
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
	'title' => t('Image'),
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
 * preprocess {{ac_image}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_image_preprocess(&$values) {

  if (!isset($values['link']) || $values['link'] =='') {
	unset($values['link']);
	unset($values['link_target']);
  }

  if (isset($values['fid']) && $values['fid'] != 0) {
	unset($values['src']);
  }elseif (isset($values['src']) && !empty($values['src'])){
	unset($values['fid']);
  }


  if (isset($values['gridy']) && $values['gridy'] == TRUE) {
	$values['gridy'] = 'true';
  }else{
	unset($values['gridy']);
  }

}

/**
 * process Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_image_process($attrs, $text = null, $shortcode = '') {
  acquia_include('utility');
  acquia_include('content');
  acquia_include('media');

  $_attrs = ac_shortcode_attrs(array(
	'fid' => '',
	'src' => '',
	'link' => '',
	'link_target' => '',
	'style' => '',
	'title' => '',
  ), $attrs);
  extract($_attrs);
  $sc_name = str_replace('_', '-', $shortcode);
  if ((empty($fid) || !is_numeric($fid)) && empty($src) ) {
	drupal_set_message('ACQUIA: shortcode '.$shortcode.': no valid file id or source provided.');
	return '';
  }

  $attributes = array('title' => $title, 'alt' => '');
  $attributes['class'][] = $sc_name;
  $attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : NULL;

  //---------------------------------------
  if ( isset($attrs['class']) && !empty($attrs['class']) ) {
	foreach (explode(' ', $attrs['class']) as $class) {
	  $attributes['class'][] = trim($class);
	}
  }
  //---------------------------------------

  if (isset($attrs['animate'])) {
	// Animate data
	$attributes += acquia_get_anim_data_by_attrs($attrs);
  }

  if (!empty($fid)){
	$image = file_load($fid);
	$image_uri = isset($image->uri) ? $image->uri : acquia_variable_get('empty_image_uri');
	if (!empty($style)) {
	  $attributes['src'] = image_style_url($style, $image_uri);
	}else{
	  $attributes['src'] = file_create_url($image_uri);
	}
  }else{
	$attributes['src'] = $src;
  }

  $image = '<img'.drupal_attributes($attributes).' />';

  if (isset($attrs['info'])) {
	$link_attrs = array();
	acquia_add_tooltip_libs_by_type($attrs['info']);
	$link_attrs += (array)acquia_get_tooltip_data_by_attrs($attrs);
	$link = $link == 'front' ? '<front>' : $link;
	$image = l($image, $link, array('html' => true, 'attributes' => $link_attrs));
  }elseif (!empty($link)){
	$image = l($image, $link, array('html' => true));
  }

  /** Wrap Grid HTML **/
  if (isset($attrs['gridy']) && strtolower($attrs['gridy']) == 'true') {
	$temp  = '<div class="ac-grid-item">';
	$temp .= '	<div class="g-i clearfix">';
	$temp .= '		<div class="g-i-i clearfix">';
	$temp .= $image;
	$temp .= '		</div>';
	$temp .= '	</div>';
	$temp .= '</div>';

	$image = $temp;
  }
  return $image;
}

