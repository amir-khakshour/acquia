<?php
// $Id
/**
 * Helper methods to work with forms
 */

/**
 * text transform form structure
 */
function ac_skin_format_transform_element($group, $element, $attr, $values = array(), $type = 'typo'){
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element][$type][$attr];
	$defaults['title'] = isset($defaults['title']) ? $defaults['title'] : t('text transform');

	return array(
		'#attributes' => array('class' => array('ac-transform'), 'data-target' => $element),
		'#type' => 'select',
		'#options' => acquia_theme_text_transforms(),
		'#title' => t('@type %title', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]) ? $values[$attr] : $defaults['default'],
		'#description' => t('default text transform is @val', array('@val' => acquia_theme_text_transforms($defaults['default']))),
	);
}

/**
 * Slider form structure
 */
function ac_skin_format_slider_element($group, $element, $attr, $values = array(), $type = 'typo'){
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element][$type][$attr];
	$item = array(
		'#attributes' => array('class' => array('ac-slider')),
		'#type' => 'textfield',
		'#title' => t('@type %title', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]) ? $values[$attr] : $defaults['default'],
		'#description' => t('Default value is @val', array('@attr' => $attr, '@val' => $defaults['default'])),
	);

	if (isset($defaults['css-attr'])) {
		$item['#attributes']['data-target'] = $element;
		$item['#attributes']['data-css-attr'] = $defaults['css-attr'];
		$item['#attributes']['data-val-suffix'] = isset($defaults['suffix']) ? $defaults['suffix'] : '';
	}
	
	$item['#attributes']['data-min'] = isset($defaults['min']) ? $defaults['min'] : 0;
	$item['#attributes']['data-max'] = isset($defaults['max']) ? $defaults['max'] : 100;
	$item['#attributes']['data-step'] = isset($defaults['step']) ? $defaults['step'] : 1;

	if (isset($values[$element][$attr]['data']) && is_array($values[$element][$attr]['data'])) {
		foreach($values[$element][$attr]['data'] as $data => $value) {
			$item['#attributes']['data-' . $data] = $value;
		}
	}
	
	if (isset($defaults['suffix'])) {
		$item['#field_suffix'] = $defaults['suffix'];
	}

	return $item;
}

/**
 * Font family form structure
 */
function ac_skin_format_font_element($group, $element, $attr, $values = array()){
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element]['typo'][$attr];
	
	$item = array(
		'#attributes' => array('class' => array('ac-g-fonts')),
		'#type' => 'select',
		'#title' => t('@type %title', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#options' => array(
			'' => t('Theme Default'),
			'theme fonts' => ac_skin_get_theme_fonts_option(),
			'Websafe' => acquia_websafe_fonts(),
			t('Google Fonts') => acquia_google_fonts()
		),
		'#default_value' => isset($values[$attr]) ? $values[$attr] : $defaults['default'],
		'#description' => t('Default font is @val', array('@val' => $defaults['default'])),
	);
	if (isset($defaults['css-attr'])) {
		$item['#attributes']['data-target'] = $element;
		$item['#attributes']['data-css-attr'] = $defaults['css-attr'];
	}
	return $item;
}

/**
 * color form structure
 */
function ac_skin_format_hex_color_element($group, $element, $attr, $values = array()){
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element]['scheme'][$attr];
	$type = isset($style[$element]['title']) ? $style[$element]['title'] : '';
	$item = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('@type %title', array('@type' => $type, '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]) ? $values[$attr] : $defaults['default'],
		'#description' => t('Default color is @val', array('@val' => $defaults['default'])),
	);
	
	if (isset($defaults['css-attr'])) {
		$item['#attributes']['class'][] = 'ac-skin-color';
		$item['#attributes']['data-target'] = $element;
		$item['#attributes']['data-css-attr'] = $defaults['css-attr'];
	}

	if (isset($defaults['invisible'])) {
		foreach ($defaults['invisible'] as $attr => $condition) {
			$item['#states']['invisible'] = array(':input[name="skin['.$element.']['.$attr.']"]' => $condition);
			$item['#states']['disabled'] = array(':input[name="skin['.$element.']['.$attr.']"]' => $condition);
		}
	}
	return $item;
}

/**
 * Background form structure
 */
function ac_skin_format_bg_element($group, $element, $attr, $values = array()){
  acquia_include('theme');
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element]['scheme'][$attr];

	$form = array(
		'#type' => 'container',
	);
	
	$default_bg = isset($values[$attr]['image']) ? $values[$attr]['image'] : (isset($defaults['image']) ? $defaults['image'] : '');
	$src = '';
	if (!empty($default_bg)) {
		$src = ac_skin_get_absolute_image_url($default_bg);
	}
	$form['image'] = array(
		'#attributes' => array('class' => array('ac-img-sel-target ac-upload'), 'data-target' => $element, 'data-src' => $src),
		'#type' => 'textfield',
		'#title' => t('@type background', array('@type' => $style[$element]['title'])),
		'#default_value' => $default_bg,
		'#full_description' => '<div class="ac-bg-sel">' .acquia_theme_generate_pattern_list() . '</div>',
		'#field_suffix' => '<span class="ac-reset">x</span><a href="#" title="'.t('upload file').'" class="button upload-btn">'.t('Upload file').'</a>',
		'#description' => t('click on to choose image from media library or upload image to your media library')
	);
	
	$form['repeat'] = array(
		'#type' => 'select',
		'#title' => t('repeat'),
		'#options' => array(
			'no-repeat' => t('no repeat'),
			'repeat-x' => t('repeat x'),
			'repeat-y' => t('repeat y'),
			'repeat' => t('repeat'),
		),
		'#default_value' => isset($values[$attr]['repeat']) ? $values[$attr]['repeat'] : (isset($defaults['repeat']) ? $defaults['repeat'] : NULL),
	);
	$form['posx'] = array(
		'#type' => 'select',
		'#title' => t('position-x'),
		'#options' => array(
			'left' => t('left'),
			'right' => t('right'),
			'center' => t('center'),
		),
		'#default_value' => isset($values[$attr]['posx']) ? $values[$attr]['posx'] : (isset($default['posx']) ? $default['posx'] : NULL),
	);
	$form['posy'] = array(
		'#type' => 'select',
		'#title' => t('position-y'),
		'#options' => array(
			'top' => t('top'),
			'bottom' => t('bottom'),
			'center' => t('center'),
		),
		'#default_value' => isset($values[$attr]['posy']) ? $values[$attr]['posy'] : (isset($defaults['posy']) ? $defaults['posy'] : NULL),
	);
	
	$form['full'] = array(
		'#type' => 'checkbox',
		'#title' => t('Fullscreen'),
		'#default_value' => isset($values[$attr]['full']) ? $values[$attr]['full'] : (isset($defaults['full']) ? $defaults['full'] : FALSE),
	);
	return $form;
}

/**
 * rgba_color form structure
 */
function ac_skin_format_rgba_color_element($group, $element, $attr, $values = array()){
  acquia_include('theme');
  acquia_include('options', 'ac_skin');
  acquia_include('utility', 'ac_skin');
	
	$style = ac_skin_get_group_styles($group);
	$defaults = $style[$element]['scheme'][$attr];
	$form = array(
		'#type' => 'container',
	);
	
	$form['color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('@type %title', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]['color']) ? $values[$attr]['color'] : (isset($defaults['color']) ? $defaults['color'] : ''),
		'#field_suffix' => '<span class="ac-reset">x</span>',
		//'#description' => t('click on to choose image from media library or upload image to your media library')
	);
	
	$form['opacity'] = array(
		'#attributes' => array(
			'class' => array('ac-slider'),
			'data-min' => 0,
			'data-max' => 100,
			'data-step' => 1,
		),
		'#type' => 'textfield',
		'#title' => t('@type %title depth', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]['opacity']) ? $values[$attr]['opacity'] : (isset($defaults['opacity']) ? $defaults['opacity'] : '100'),
	);
	
	if (isset($defaults['css-attr'])) {
		$form['color']['#attributes']['class'][] = 'ac-skin-color';
		$form['color']['#attributes']['data-css-attr'] = $defaults['css-attr'];
		$form['color']['#attributes']['data-target'] = $element;
		
		$form['opacity']['#attributes']['data-target'] = $element;
		$form['opacity']['#attributes']['data-css-attr'] = 'opacity';
	}
	
	$form['ie'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('@type IE %title', array('@type' => $style[$element]['title'], '%title' => $defaults['title'])),
		'#default_value' => isset($values[$attr]['ie']) ? $values[$attr]['ie'] : (isset($defaults['ie']) ? $defaults['ie'] : ''),
		'#field_suffix' => '<span class="ac-reset">x</span>',
	);
	
	return $form;
}
