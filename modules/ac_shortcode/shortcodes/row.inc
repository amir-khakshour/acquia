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
function ac_shortcode_row_shortcode() {
  return array(
	'ac_row' => array(
	  'title' => t('Row'),
	  'description' => t('This is a wrapper for an DiamondLayers shortcode.'),
	  'form callback' => 'ac_shortcode_ac_row_form',
	  'values process callback' => 'ac_shortcode_ac_row_preprocess',
	  'process callback' => 'ac_shortcode_ac_row_process',
	  'category' => 'structure',
	),
	'ac_row_inner' => array(
	  'title' => t('Row Inner'),
	  'description' => t('This is an inner wrapper for an DiamondLayers shortcode.'),
	  'process callback' => 'ac_shortcode_ac_row_inner_process',
	  'values process callback' => 'ac_shortcode_ac_row_inner_preprocess',
	  'form callback' => 'ac_shortcode_ac_row_inner_form',
	  'hidden' => TRUE,
	  'category' => 'structure',
	  "enabled" => array('ac_row' => TRUE),
	),
	'vc_row' => array(
	  'title' => t('Row'),
	  'description' => t('This is a wrapper for an DiamondLayers shortcode.'),
	  'form callback' => 'ac_shortcode_ac_row_form',
	  'values process callback' => 'ac_shortcode_ac_row_preprocess',
	  'process callback' => 'ac_shortcode_ac_row_process',
	  'category' => 'structure',
	  'hidden' => TRUE,
	  "enabled" => array('ac_row' => TRUE),
	),
	'vc_row_inner' => array(
	  'title' => t('Row Inner'),
	  'description' => t('This is an inner wrapper for an DiamondLayers shortcode.'),
	  'process callback' => 'ac_shortcode_ac_row_inner_process',
	  'values process callback' => 'ac_shortcode_ac_row_inner_preprocess',
	  'form callback' => 'ac_shortcode_ac_row_inner_form',
	  'hidden' => TRUE,
	  'category' => 'structure',
	  "enabled" => array('ac_row' => TRUE),
	),
  );
}

/**
 * Implements edit form of {{ac_row_inner}} shortcode
 */
function ac_shortcode_ac_row_inner_form($form, $form_state) {
  acquia_include('options');
  acquia_include('fields');

  $values = isset($form_state['values']) ? $form_state['values'] : array();
  $form['padding'] = array(
	'#type' => 'select',
	'#title' => t('Row Inner Padding'),
	'#description' => t('Define the Row Inner top and bottom padding'),
	'#default_value' => isset($values['padding']) ? $values['padding'] : 'zero',
	'#options' => acquia_padding(),
  );

  $settings = array(
	'title' => t('Columns'),
	'delay_enabled' => TRUE
  );
  if (isset($values['animate'])) {
	$settings['animate'] = $values['animate'];
	$settings['when'] = $values['when'];
	$settings['delay'] = $values['delay'];
  }

  // add animate fields
  acquia_field_animate($form, $settings);

  /** Global shortcode elements **/
  $form['id'] = array(
	'#type' => 'textfield',
	'#title' => t('ID'),
	'#description' => t('you can set ID html attribute of this element here.'),
	'#default_value' => isset($values['id']) ? $values['id'] : '',
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
 * preprocess {{ac_row_inner}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_row_inner_preprocess(&$values) {

}

/**
 * Implements edit form of {{ac_row}} shortcode
 */
function ac_shortcode_ac_row_form($form, $form_state) {
  acquia_include('fields');
  acquia_include('content');
  acquia_include('options');

  $values = isset($form_state['values']) ? $form_state['values'] : array();

  if (isset($values['bg_color'])) {
	$values['row_style'] = TRUE;
  }else{
	$values['row_style'] = FALSE;
  }

  // Row Style
  $form['row_style'] = array(
	'#type' => 'checkbox',
	'#title' => t('Customize Row style?'),
	'#default_value' => $values['row_style'],
  );

  $form['style'] = array(
	'#type' => 'fieldset',
	'#title' => t('Row style'),
	'#collapsible' => true,
	'#states' => array(
	  'visible' => array(
		':input[name="row_style"]' => array('checked' => TRUE),
	  ),
	),
  );

  $form['style']['style'] = array(
	'#type' => 'select',
	'#title' => t('Section style'),
	'#description' => '',
	'#default_value' => isset($values['style']) ? $values['style'] : '',
	'#options' => array('' => t('None'), 1 => t('Section style 1'), 2 => t('Section style 2'), 3 => t('Section style 3')),
  );

  $ops = array_merge(array('custom' => t('Custom Color')), acquia_skins_list());
  add_default_option($ops);

  $form['style']['bg_type'] = array(
	'#type' => 'select',
	'#title' => t('Background type'),
	'#description' => t('Choose whether you want to use an image or video for the background of the section. This will decide what is used from the options below.'),
	'#default_value' => isset($values['bg_type']) ? $values['bg_type'] : NULL,
	'#options' => array('' => t('none'), 'img' => t('Image'), 'video' => t('video')),
  );

  $form['style']['video'] = array(
	'#type' => 'container',
	'#states' => array(
	  'visible' => array(
		':input[name="bg_type"]' => array('value' => 'video'),
	  ),
	  'enabled' => array(
		':input[name="bg_type"]' => array('value' => 'video'),
	  ),
	),
  );

  $form['style']['video']['poster'] = array(
	'#type' => 'media',
	'#title' => t('Video poster'),
	'#description' => t('click on to choose video poster from media library or upload image to your media library.'),
	'#default_value' => isset($values['poster']) ? array('fid' => $values['poster']) : NULL,
	'#media_options' => array(
	  'global' => array(
		'types' => array('image'),
		'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/img',
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('video', 'poster'),
  );

  $form['style']['video']['mp4'] = array(
	'#type' => 'media',
	'#title' => t('Background Video (MP4)'),
	'#description' => t('Provide a video URL in MP4 format to use as the background for the section area. You can upload these videos through the media library.'),
	'#default_value' => isset($values['mp4']) ? array('fid' => $values['mp4']) : NULL,
	'#media_options' => array(
	  'global' => array(
		'types' => array('mp4'),
		'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/video',
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('video', 'mp4'),
  );

  $form['style']['video']['webm'] = array(
	'#type' => 'media',
	'#title' => t('Background Video (WebM)'),
	'#description' => t('Provide a video URL in WebM  format to use as the background for the section area. You can upload these videos through the media library.'),
	'#default_value' => isset($values['webm']) ? array('fid' => $values['webm']) : NULL,
	'#media_options' => array(
	  'global' => array(
		'types' => array('webm'),
		'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/video',
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('video', 'webm'),
  );

  $form['style']['video']['ogg'] = array(
	'#type' => 'media',
	'#title' => t('Background Video (OGG)'),
	'#description' => t('Provide a video URL in OGG  format to use as the background for the section area. You can upload these videos through the media library.'),
	'#default_value' => isset($values['ogg']) ? array('fid' => $values['ogg']) : NULL,
	'#media_options' => array(
	  'global' => array(
		'types' => array('ogg'),
		'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/video',
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('video', 'ogg'),
  );

  $form['style']['img'] = array(
	'#type' => 'container',
	'#states' => array(
	  'visible' => array(
		':input[name="bg_type"]' => array('value' => 'img'),
	  ),
	  'enabled' => array(
		':input[name="bg_type"]' => array('value' => 'img'),
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('image'),
  );

  $form['style']['img']['fid'] = array(
	'#type' => 'media',
	'#title' => t('Custom Background Image'),
	'#description' => t('click on to choose image from media library or upload image to your media library.'),
	'#default_value' => isset($values['image']) ? $values['image'] : NULL,
	'#media_options' => array(
	  'global' => array(
		'types' => array('image'),
		'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/img',
	  ),
	),
	'#tree' => TRUE,
	'#parents' => array('image', 'fid'),
  );
  $form['style']['img']['bg_position'] = array(
	'#type' => 'select',
	'#title' => t('Background Image Position'),
	'#default_value' => isset($values['bg_position']) ? $values['bg_position'] : null,
	'#options' => acquia_css_background_position(),
  );

  $form['style']['img']['bg_repeat'] = array(
	'#type' => 'select',
	'#title' => t('Background Repeat'),
	'#default_value' => isset($values['bg_repeat']) ? $values['bg_repeat'] : null,
	'#options' => acquia_css_background_repeat(),
  );

  $form['style']['img']['bg_attachment'] = array(
	'#type' => 'select',
	'#title' => t('Background Attachment'),
	'#default_value' => isset($values['bg_attachment']) ? $values['bg_attachment'] : null,
	'#options' => acquia_css_background_attachment(),
  );

  $form['style']['bg_color'] = array(
	'#type' => 'select',
	'#title' => t('Background Color'),
	'#description' => t('Select a background color for your Section here.'),
	'#default_value' => isset($values['bg_color']) ? $values['bg_color'] : NULL,
	'#options' => $ops,
  );
  $form['style']['custom_bg'] = array(
	'#attributes' => array('class' => array('field-colorpicker')),
	'#type' => 'textfield',
	'#title' => t('Custom Background Color'),
	'#description' => t('Select a custom background color for your Section here'),
	'#default_value' => isset($values['custom_bg']) ? $values['custom_bg'] : '#444444',
	'#states' => array(
	  'visible' => array(
		':input[name="bg_color"]' => array('value' => 'custom'),
	  ),
	),
  );

  $form['style']['bg_opacity'] = array(
	'#type' => 'textfield',
	'#title' => t('Background opacity'),
	'#default_value' => isset($values['bg_opacity']) ? $values['bg_opacity'] : '',
	'#description' => t('Opacity of background image or video. enter a number between 0 and 100.'),
	'#states' => array(
	  'invisible' => array(
		':input[name="bg_type"]' => array('value' => ''),
	  ),
	  'disabled' => array(
		':input[name="bg_type"]' => array('value' => ''),
	  ),
	),
  );

  //$form['style']['sticky'] = array(
  //	'#type' => 'select',
  //	'#title' => t('Where to stick this section'),
  //	'#description' => t('If you need full with section change it from none to header or footer.'),
  //	'#default_value' => isset($values['sticky']) ? $values['sticky'] : 'none',
  //	'#options' => array('none' => t('None'), 'header' => t('Parent Header'), 'footer' => t('Parent Footer')),
  //);


  $values['full_width_container'] = isset($values['full_width_container']) && $values['full_width_container'] == 'true' ? TRUE : FALSE;
  $form['style']['full_width_container'] = array(
	'#type' => 'checkbox',
	'#title' => t('Full width container?'),
	'#default_value' => $values['full_width_container'],
  );

  $form['style']['padding'] = array(
	'#type' => 'select',
	'#title' => t('Section Padding'),
	'#description' => t('Define the sections top and bottom padding'),
	'#default_value' => isset($values['padding']) ? $values['padding'] : 'default',
	'#options' => acquia_padding(),
  );

  $values['remove_side_space'] = isset($values['remove_side_space']) && $values['remove_side_space'] == 'true' ? TRUE : FALSE;
  $form['style']['remove_side_space'] = array(
	'#type' => 'checkbox',
	'#title' => t('Remove Left and Right Spaces?'),
	'#default_value' => $values['remove_side_space'],
  );

  $form['style']['no_top_space'] = array(
	'#type' => 'checkbox',
	'#title' => t('remove top space?'),
	'#default_value' => isset($values['no_top_space']) && $values['no_top_space'] == 'true' ? TRUE : FALSE,
  );

  $form['style']['no_bottom_space'] = array(
	'#type' => 'checkbox',
	'#title' => t('remove bottom space?'),
	'#default_value' => isset($values['no_bottom_space']) && $values['no_bottom_space'] == 'true' ? TRUE : FALSE,
  );


  $ops = array_merge(array('' => t('Inherit')), $ops);
  $form['style']['bg_size'] = array(
	'#type' => 'select',
	'#title' => t('Background Size'),
	'#description' => t('Change how the background fits into your section.'),
	'#default_value' => isset($values['bg_size']) ? $values['bg_size'] : NULL,
	'#options' => array(
	  '' => t('Auto'),
	  '100% auto' => t('100% auto - Scale width to the container width.'),
	  'auto 100%' => t('auto 100% - Scale height to the container height.'),
	  'cover' => t('Cover - Stretched to container dimensions.'),
	  'contain' => t('Contain - Scale both width and height of the image.'),
	  'custom' => t('Custom'),
	),
	'#states' => array(
	  'invisible' => array(
		':input[name="bg_type"]' => array('value' => ''),
	  ),
	  'disabled' => array(
		':input[name="bg_type"]' => array('value' => ''),
	  ),
	),
  );

  $form['style']['custom_bg_size'] = array(
	'#type' => 'textfield',
	'#title' => t('Custom Background Size'),
	'#description' => t('Enter your background size here. e.g. 100% auto or 400px 100px'),
	'#default_value' => isset($values['custom_bg_size']) ? $values['custom_bg_size'] : '',
	'#states' => array(
	  'visible' => array(
		':input[name="bg_size"]' => array('value' => 'custom'),
	  ),
	),
  );

  $ops = array_merge(array('' => t('Inherit')), $ops);
  $form['style']['color'] = array(
	'#type' => 'select',
	'#title' => t('Section Color'),
	'#description' => t('Choose a color for your Section text here'),
	'#default_value' => isset($values['color']) ? $values['color'] : NULL,
	'#options' => $ops,
  );

  $form['style']['custom_color'] = array(
	'#attributes' => array('class' => array('field-colorpicker')),
	'#type' => 'textfield',
	'#title' => t('Custom section Color'),
	'#description' => t('Select a custom color for your Section text here'),
	'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
	'#states' => array(
	  'visible' => array(
		':input[name="color"]' => array('value' => 'custom'),
	  ),
	),
  );

  $values['bg_parallax'] = isset($values['bg_parallax']) && $values['bg_parallax'] == 'true' ? TRUE : FALSE;
  $form['style']['bg_parallax'] = array(
	'#type' => 'checkbox',
	'#title' => t('Enable Parallax effect?'),
	'#default_value' => isset($values['bg_parallax']) ? $values['bg_parallax'] : FALSE,
  );

  $values['no_border'] = isset($values['no_border']) && $values['no_border'] == 'true' ? TRUE : FALSE;
  $form['style']['no_border'] = array(
	'#type' => 'checkbox',
	'#title' => t('Disable Borders?'),
	'#description' => t('change to On if you want to disable borders of section from section style.'),
	'#default_value' => $values['no_border'],
	'#states' => array(
	  'invisible' => array(
		':input[name="style"]' => array('value' => ''),
	  ),
	),
  );

  $values['top_bordered'] = isset($values['top_bordered']) && $values['top_bordered'] == 'true' ? TRUE : FALSE;
  $form['style']['top_bordered'] = array(
	'#type' => 'checkbox',
	'#title' => t('Top bordered?'),
	'#description' => t('Enable top border.'),
	'#default_value' => $values['top_bordered'],
  );

  $values['no_overlay'] = isset($values['no_overlay']) && $values['no_overlay'] == 'true' ? TRUE : FALSE;
  $form['style']['no_overlay'] = array(
	'#type' => 'checkbox',
	'#title' => t('Disable overlay?'),
	'#description' => t('chenge to On if you want to disable Overlay background over section image.'),
	'#default_value' => $values['no_overlay'],
	'#states' => array(
	  'invisible' => array(
		':input[name="style"]' => array('value' => ''),
	  ),
	),
  );

  // Column Style
  if (isset($values['position']) || isset($values['align'])) {
	$values['col_style'] = TRUE;
  }else{
	$values['col_style'] = FALSE;
  }

  $form['col_style_enabled'] = array(
	'#type' => 'checkbox',
	'#title' => t('Customize column style?'),
	'#default_value' => $values['col_style'],
  );

  $form['col_style'] = array(
	'#type' => 'fieldset',
	'#title' => t('Column style'),
	'#collapsible' => true,
	'#states' => array(
	  'visible' => array(
		':input[name="col_style_enabled"]' => array('checked' => TRUE),
	  ),
	),
  );

  $op = acquia_align_list();
  $op = array_merge(array('' => t('Inherit')), $op);

  $form['col_style']['position'] = array(
	'#type' => 'select',
	'#title' => t('Columns Position'),
	'#description' => t('Choose the position/float of your Columns here'),
	'#default_value' => isset($values['position']) ? $values['position'] : 'left',
	'#options' => $op,
  );

  $form['col_style']['align'] = array(
	'#type' => 'select',
	'#title' => t('Column text align'),
	'#description' => t('Choose the text alignment of your column here'),
	'#default_value' => isset($values['align']) ? $values['align'] : 'left',
	'#options' => $op,
  );

  $settings = array(
	'title' => t('Columns'),
	'delay_enabled' => TRUE
  );
  if (isset($values['animate'])) {
	$settings['animate'] = $values['animate'];
	$settings['when'] = $values['when'];
	$settings['delay'] = $values['delay'];
  }

  // add animate fields
  acquia_field_animate($form['col_style'], $settings);

  /** Global shortcode elements **/
  $form['id'] = array(
	'#type' => 'textfield',
	'#title' => t('ID'),
	'#description' => t('you can set ID html attribute of this element here.'),
	'#default_value' => isset($values['id']) ? $values['id'] : '',
  );
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
 * preprocess {{ac_col_container}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_row_preprocess(&$values) {
  if (!isset($values['row_style']) || !$values['row_style']) {
	unset($values['no_top_space']);
	unset($values['no_bottom_space']);
	unset($values['style']);
	unset($values['bg_color']);
	unset($values['full_width_container']);
	unset($values['remove_side_space']);
	unset($values['custom_bg']);
	unset($values['bg_parallax']);
	unset($values['padding']);
	unset($values['color']);
	unset($values['custom_color']);
	unset($values['borders']);
	unset($values['bg_type']);
	unset($values['image']);
	unset($values['video']);
	unset($values['no_border']);
	unset($values['top_bordered']);
	unset($values['no_overlay']);
	unset($values['bg_size']);
	unset($values['custom_bg_size']);
  }else{
	if (isset($values['no_border']) && $values['no_border'] == TRUE) {
	  $values['no_border'] = 'true';
	}else{
	  unset($values['no_border']);
	}

	if (isset($values['top_bordered']) && $values['top_bordered'] == TRUE) {
	  $values['top_bordered'] = 'true';
	}else{
	  unset($values['top_bordered']);
	}
	if (isset($values['no_overlay']) && $values['no_overlay'] == TRUE) {
	  $values['no_overlay'] = 'true';
	}else{
	  unset($values['no_overlay']);
	}
	if (isset($values['bg_type']) && $values['bg_type'] == 'img') {
	  unset($values['video']);
	  $values += $values['image'];
	  if (isset($values['image']['fid']) && !empty($values['image']['fid'])) {
		$values['image'] = $values['image']['fid'];
	  }else{
		unset($values['image']);
	  }
	  unset($values['fid']);
	}else{
	  if (isset($values['video']['poster']['fid']) && !empty($values['video']['poster']['fid'])) {
		$values['poster'] = $values['video']['poster']['fid'];
	  }
	  if (isset($values['video']['mp4']['fid']) && !empty($values['video']['mp4']['fid'])) {
		$values['mp4'] = $values['video']['mp4']['fid'];
	  }
	  if (isset($values['video']['webm']['fid']) && !empty($values['video']['webm']['fid'])) {
		$values['webm'] = $values['video']['webm']['fid'];
	  }
	  if (isset($values['video']['ogg']['fid']) && !empty($values['video']['ogg']['fid'])) {
		$values['ogg'] = $values['video']['ogg']['fid'];
	  }
	  unset($values['image']);
	  unset($values['video']);
	}
	if (isset($values['no_top_space']) && $values['no_top_space'] == TRUE) {
	  $values['no_top_space'] = 'true';
	}else{
	  unset($values['no_top_space']);
	}

	if (isset($values['no_bottom_space']) && $values['no_bottom_space'] == TRUE) {
	  $values['no_bottom_space'] = 'true';
	}else{
	  unset($values['no_bottom_space']);
	}

	if (isset($values['bg_parallax']) && $values['bg_parallax'] == TRUE) {
	  $values['bg_parallax'] = 'true';
	}else{
	  unset($values['bg_parallax']);
	}

	if (isset($values['full_width_container']) && $values['full_width_container'] == TRUE) {
	  $values['full_width_container'] = 'true';
	}else{
	  unset($values['full_width_container']);
	}

	if (isset($values['remove_side_space']) && $values['remove_side_space'] == TRUE) {
	  $values['remove_side_space'] = 'true';
	}else{
	  unset($values['remove_side_space']);
	}

	if (isset($values['bg_color']) && $values['bg_color'] !='custom') {
	  unset($values['custom_bg']);
	}

	if (isset($values['color']) && $values['color'] !='custom') {
	  unset($values['custom_color']);
	}
  }

  if (!isset($values['col_style_enabled']) || !$values['col_style_enabled']) {
	unset($values['position']);
	unset($values['align']);
	unset($values['cssanimate']);
  }
}

/**
 * process {{ac_col_text}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_row_process($attrs, $text = null, $shortcode = '') {
  acquia_include('content');
  acquia_include('options');
  acquia_include('utility');

  $_attrs = ac_shortcode_attrs(array(
	'bg_type' => '',
	'custom_bg' => '',
	'full_width_container' => 'false',
	'remove_side_space' => 'false',
	'bg_parallax' => 'false',
	'padding' => 'default',
	'bg_color' => '',
	'color' => '',
	'align' => '',
	'position' => '',
	'style' => '',
	'no_top_space' => '',
	'no_bottom_space' => '',
  ), $attrs);
  extract($_attrs);
  $sc_name = str_replace('_', '-', 'ac_page_section');

  $_attrs['bg_color'] = isset($attrs['bg_color']) &&  ($attrs['bg_color'] == 'sw') ? acquia_theme_get_settings('ac_page_section_bg_color', null, 'shortcodes') : $_attrs['bg_color'];
  $_attrs['color'] = isset($attrs['color']) && ($attrs['color'] == 'sw') ? acquia_theme_get_settings('ac_page_section_color', null, 'shortcodes') : $_attrs['color'];
  $_attrs['section-style'] = $_attrs['style'];

  // Build Class array
  $attributes = array();
  $container_attrs = array();
  $attributes['style'] = array();
  $attributes['class'] = array();

  $attributes['class'][] = $sc_name;
  $attributes['class'][] = 'ac-col-container';
  $attributes['class'][] = isset($attrs['color']) ? 'ac-custom-color' : NULL;
  $attributes['class'][] = $bg_parallax == 'true' ? 'ac-parallax' : null;
  $attributes['class'][] = $full_width_container == 'true' ? 'ac-full-container' : null;
  $attributes['class'][] = $remove_side_space == 'true' ? 'ac-no-side-space' : null;
  $attributes['class'][] = $bg_type != '' ? 'ac-bg-enabled' : NULL;
  $attributes['class'][] = acquia_get_class_by_args(array('color', 'align', 'position', 'section-style'), $_attrs, CHECK_LENGTH);
//	$attributes['class'][] = $_attrs['bg_color'] !=NULL || isset($attrs['image']) ? 'ac-container-padding' : null;
  $attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
  $attributes['class'][] = isset($attrs['no_border']) && $attrs['no_border'] == 'true' ? 'ac-no-border' : null;
  $attributes['class'][] = isset($attrs['top_bordered']) && $attrs['top_bordered'] == 'true' ? 'ac-top-bordered' : null;
  $attributes['class'][] = isset($attrs['no_overlay']) && $attrs['no_overlay'] == 'true' ? 'ac-no-overlay' : null;

  //---------------------------------------
  if ( isset($attrs['class']) && !empty($attrs['class']) ) {
	foreach (explode(' ', $attrs['class']) as $class) {
	  $attributes['class'][] = $class;
	}
  }
  //---------------------------------------

  if ( isset($attrs['bg_color']) && $attrs['bg_color'] == 'custom' && !empty($custom_bg) ) {
	$attributes['style']['background-color'] = $custom_bg;
	$bg_attrs['style']['background-color'] = $custom_bg;
  }elseif (isset($attrs['bg_color'])){
	$class = acquia_get_class_by_args(array('bg_color'), $_attrs, CHECK_LENGTH);
	$attributes['class'][] = $class;
	$bg_attrs['class'][] = $class;
  }

  if ( isset($attrs['color']) && $attrs['color'] == 'custom' && isset($attrs['custom_color']) ) {
	$attributes['style']['color'] = $attrs['custom_color'];
  }

  //-----------------------------------------------------------
  // Background
  //-----------------------------------------------------------
  $bg = '';
  $overlay_type = 'default';
  if ( isset($attrs['bg_opacity']) && !empty($attrs['bg_opacity']) ) {
	$attrs['bg_opacity'] = $attrs['bg_opacity']/100;
	$bg_attrs['style']['opacity'] = $attrs['bg_opacity'];
	$bg_attrs['style']['-moz-opacity'] = $attrs['bg_opacity'];
	$bg_attrs['style']['-khtml-opacity'] = $attrs['bg_opacity'];
	$bg_attrs['style']['-webkit-opacity'] = $attrs['bg_opacity'];
  }

  if (isset($attrs['image']) && !empty($attrs['image']) && is_numeric($attrs['image'])) {
	// Build background image path
	$bg = file_create_url(file_load($attrs['image'])->uri);

	if ( !empty($bg) ) {

	  $bg_attrs['style']['background-image'] = 'url("' . $bg . '")';

	  if ( isset($attrs['bg_position']) && !empty($attrs['bg_position']) ) {
		$bg_attrs['style']['background-position'] = $attrs['bg_position'];
	  }

	  if ( isset($attrs['bg_repeat']) && !empty($attrs['bg_repeat']) ) {
		if ($attrs['bg_repeat'] == 'stretch') {
		  $bg_attrs['class'][] = 'ac-full-stretch';
		}else {
		  $bg_attrs['style']['background-repeat'] = $attrs['bg_repeat'];
		}
	  }

	  if ( $bg_parallax != 'true' && isset($attrs['bg_attachment']) && !empty($attrs['bg_attachment']) ) {
		$bg_attrs['style']['background-attachment'] = $attrs['bg_attachment'];
		$bg_attrs['class'][] = 'ac-simple-attached';
	  }

	  if ( isset($attrs['bg_size']) && !empty($attrs['bg_size'])) {
		if ($attrs['bg_size'] != 'custom') {
		  $bg_attrs['style']['background-size'] = $attrs['bg_size'];
		}
		else if (isset($attrs['custom_bg_size']) && !empty($attrs['custom_bg_size'])) {
		  $bg_attrs['style']['background-size'] = $attrs['custom_bg_size'];
		}
	  }
	}

	if ($bg_parallax == 'true'){
	  $bg_attrs['style'] = acquia_style_arr_to_tag(	$bg_attrs['style'] );
	  $bg_attrs['class'] = 'ac-parallax-asset ac-parallax-img';
	  $bg = '	<div' .drupal_attributes($bg_attrs) .'></div>';
	}else {
	  $bg ='';
	  $attributes['style'] = array_merge($attributes['style'], $bg_attrs['style']);
	  $attributes['class'] = array_merge($attributes['class'], $bg_attrs['class']);
	}
  }else if ($bg_type == 'video') {
	$bg_attrs['class'][] = 'video-overlay';
	if (isset($bg_attrs['style'])) {
	  $bg_attrs['style'] = acquia_style_arr_to_tag(	$bg_attrs['style'] );
	}
	$poster = '';
	$src = '';
	if (isset($attrs['poster']) && !empty($attrs['poster']) && is_numeric($attrs['poster'])) {
	  $poster = file_create_url(file_load($attrs['poster'])->uri);
	}
	$bg = '<div><video class="ac-parallax-asset ac-parallax-video" poster="'.$poster.'" preload="auto" autoplay loop="loop" muted="muted">';

	if (isset($attrs['mp4']) && !empty($attrs['mp4']) && is_numeric($attrs['mp4'])) {
	  $src = file_create_url(file_load($attrs['mp4'])->uri);
	  $bg .= '<source src="'.$src.'" type="video/mp4">';
	}
	if (isset($attrs['webm']) && !empty($attrs['webm']) && is_numeric($attrs['webm'])) {
	  $src = file_create_url(file_load($attrs['webm'])->uri);
	  $bg .= '<source src="'.$src.'" type="video/webm">';
	}
	if (isset($attrs['ogg']) && !empty($attrs['ogg']) && is_numeric($attrs['ogg'])) {
	  $src = file_create_url(file_load($attrs['ogg'])->uri);
	  $bg .= '<source src="'.$src.'" type="video/ogg">';
	}

	$bg .= '</video></div>';
	$bg .= '<div'.drupal_attributes($bg_attrs).'></div>';
  }

  //-----------------------------------------------------------
  // Container
  //-----------------------------------------------------------
  $container_attrs['class'][] = $sc_name.'-container';
  $container_attrs['class'][] = $remove_side_space == 'true' ? 'ac-no-side-space' : null;
  $container_attrs['class'][] = acquia_get_class_by_args(array('padding'), $_attrs);
  $container_attrs['class'][] = isset($attrs['no_bottom_space']) ? 'ac-no-b-space' : null;
  $container_attrs['class'][] = isset($attrs['no_top_space']) ? 'ac-no-t-space' : null;
  $container_attrs['class'][] = 'clearfix';
  $container_attrs['class'] = array_filter($container_attrs['class'], 'strlen');

  if (isset($attrs['id']) && !empty($attrs['id'])){
	$container_attrs['id'] = $attrs['id'];
  }

  // build attributes array
  $attributes['style'] = acquia_style_arr_to_tag(	$attributes['style'] );
  $attributes += acquia_get_anim_data_by_attrs($attrs);
  $attributes['class'] = array_filter($attributes['class'], 'strlen');

  $out  = '<div' .drupal_attributes($attributes) .'>';
  if (!empty($bg)) {
	$out.= $bg;
  }

  if (!empty($_attrs['style'])) {
	$out .= '<div class="s-overlay"></div>';
  }

  $out .= '<div class="ac-container container">';
  $out.= '	<div' .drupal_attributes($container_attrs) .'>';
  $out.= '		'.$text;
  $out.= '	</div>';
  $out.= '</div>';
  $out.= '</div>';

  return $out;
}

/**
 * process {{ac_col_text}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_row_inner_process($attrs, $text = null, $shortcode = '') {
  acquia_include('content');
  $_attrs = ac_shortcode_attrs(array(
	// Global Attributes
	'padding' => 'zero',
	// Shortcode Specific Attributes
  ), $attrs);
  extract($_attrs);
  $sc_name = str_replace('_', '-', $shortcode);

  $classes = array();
  $classes[] = $sc_name;
  $classes[] = acquia_get_class_by_args(array('padding'), $_attrs);
  $classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate ac-anim-childs' : null;


  //---------------------------------------
  if (isset($attrs['class']) && !empty($attrs['class'])) {
	foreach (explode(' ', $attrs['class']) as $class) {
	  $classes[] = $class;
	}
  }
  $classes = array_filter($classes, 'strlen');
  //---------------------------------------

  $attributes['class'] = $classes;

  if (isset($attrs['animate']) && !empty($attrs['animate'])) {
	$attributes += acquia_get_anim_data_by_attrs($attrs);
	$attributes['data-anim-childs'] = '.ac-col-inner';
  }

  if (isset($attrs['id']) && !empty($attrs['id'])){
	$attributes['id'] = $attrs['id'];
  }

  $out = '';
  $text = trim($text);
  if (empty($text)) {
	$text = '&nbsp;';
  }
  $out .= '<div'.drupal_attributes($attributes).'>';
  $out .= $text;
  $out .= '</div>';

  return $out;
}

