<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_iconbox_shortcode() {
	return array(
		'ac_iconbox' => array (
			'title' => t('Icon Box'),
			'description' => t('Creates a content block with icon to the left or above.'),
			'form callback' => 'ac_shortcode_ac_iconbox_form',
			'values process callback' => 'ac_shortcode_ac_iconbox_preprocess',
			'process callback' => 'ac_shortcode_ac_iconbox_process',
			'sitewide settings' => 'ac_shortcode_ac_iconbox_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_iconbox}} shortcode
 */
function ac_shortcode_ac_iconbox_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	$ops = acquia_iconbox_types();
	add_default_option($ops);

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('IconBox Type'),
		'#description' => t('Set the Type of the IconBox'),
		'#default_value' => isset($values['type']) ? $values['type'] : '',
		'#options' => $ops,
	);

	$form['size'] = array(
		'#type' => 'select',
		'#title' => t('Icon Size'),
		'#description' => t('select the size of icon.'),
		'#default_value' => isset($values['size']) ? $values['size'] : 'medium',
		'#options' => acquia_sizes_list() + array('full' => 'Full width'),
	);

	$form['front'] = array(
		'#type' => 'textarea',
		'#title' => t('First side content'),
		'#description' => t('Set the content of first side of IconBox.'),
		'#default_value' => isset($values['front']) ? $values['front'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'boxed-animated'),
			),
			'enabled' => array(
				':input[name="type"]' => array('value' => 'boxed-animated'),
			),
		)
	);

	$form['icon_type'] = array(
		'#type' => 'select',
		'#title' => t('Icon Type'),
		'#description' => t('Set the Type of icon for your IconBox Here'),
		'#default_value' => isset($values['icon_type']) ? $values['icon_type'] : 'simple',
		'#options' => array('image' => t('Image'), 'icon' => t('Font Icon'), 'text' => t('Text')),
	);

	// add icon fields
	acquia_field_iconfont($form, $form, array(
		'title' => t('Icon'),
		'default' => $values['icon'],
		'parents' => array(),
		'animate' => FALSE,
		'always_enabled' =>TRUE,
	));

	$form['fonticon']['#states'] = array(
		'visible' => array(
			':input[name="icon_type"]' => array('value' => 'icon'),
		),
		'enabled' => array(
			':input[name="icon_type"]' => array('value' => 'icon'),
		),
	);

	$form['fid'] = array(
		'#type' => 'media',
		'#description' => t('click on to choose image from media library or upload image to your media library.'),
		'#title' => t('Image icon source'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('image'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/img',
			),
		),
		'#states' => array(
			'visible' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
			'enabled' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
		),
	);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Image icon Style'),
		'#description' => t('Apply an image style to the Image icon'),
		'#options' => image_style_options(),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
			'enabled' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
		),
	);

	$form['text'] = array(
		'#type' => 'textfield',
		'#title' => t('Text Icon'),
		'#description' => t('Enter your text icon here. e.g. 1'),
		'#default_value' => isset($values['text']) ? $values['text'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="icon_type"]' => array('value' => 'text'),
			),
			'enabled' => array(
				':input[name="icon_type"]' => array('value' => 'text'),
			),
		),
	);

	$ops = acquia_iconbox_border_types();
	add_default_option($ops);

	$form['border'] = array(
		'#type' => 'select',
		'#title' => t('border type?'),
		//'#description' => t('Select the Icon type here.'),
		'#default_value' => isset($values['border']) ? $values['border'] : '',
		'#options' => $ops,
	);
	$form['icon_position'] = array(
		'#type' => 'select',
		'#title' => t('Icon Position'),
		'#description' => t('Set the Position and alignment of icon for your IconBox Here.'),
		'#default_value' => isset($values['icon_position']) ? $values['icon_position'] : '',
		'#options' => acquia_align_list() + array('bottom' => 'bottom'),
	);
	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Icon Color'),
		'#description' => t('Choose a color for your Icon Box icon here'),
		'#default_value' => isset($values['color']) ? $values['color'] : '',
		'#options' => array_merge(array(
			'' => t('Theme Default'),
			'custom' => t('Custom Color'),
		),
			acquia_skins_list()),
		'#states' => array(
			'invisible' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
			'disabled' => array(
				':input[name="icon_type"]' => array('value' => 'image'),
			),
		),
	);

	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom icon color'),
		'#description' => t('Select a custom color for your Icon Box icon here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Icon Box Title'),
		'#description' => t('Enter the Icon Box Title here.'),
		'#default_value' => isset($values['title']) ? $values['title'] : '',
	);

	$form['tag'] = array(
		'#type' => 'select',
		'#title' => t('Tag'),
		'#description' => t('Select the tag which will be used with your Icon Box Title.'),
		'#options' => acquia_header_tags(),
		'#default_value' => isset($values['tag']) ? $values['tag'] : 'h4',
	);

	$form['color_clone'] = array(
		'#type' => 'checkbox',
		'#title' => t('Use the icon color for the title?'),
		//'#description' => t('chenge to On if you want to enable toggle sorting.'),
		'#default_value' =>isset($values['color_clone']) && $values['color_clone'] == 'true' ? TRUE : FALSE,
	);

	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Icon Box Title Link?'),
		'#description' => t('Where should your Icon Box Title link to?'),
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
		'title' => t('Icon'),
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
 * preprocess {{ac_iconbox}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_iconbox_preprocess(&$values) {
	if (isset($values['icon_type'])) {
		if ($values['icon_type'] == 'image') {
			unset($values['fonticon']);
			unset($values['text']);
		}else if ($values['icon_type'] == 'text') {
			unset($values['fid']);
			unset($values['src']);
			unset($values['fonticon']);
		}else{
			unset($values['text']);
			unset($values['fid']);
			unset($values['src']);
		}
	}


	if (!isset($values['link']) || empty($values['link'])) {
		unset($values['link']);
		unset($values['link_target']);
	}

	if ($values['color'] != 'custom') {
		unset($values['custom_color']);
	}

	if (isset($values['color_clone']) && $values['color_clone'] == TRUE) {
		$values['color_clone'] = 'true';
	}else{
		unset($values['color_clone']);
	}
}

/**
 * process {{ac_iconbox_item}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_iconbox_process($attrs, $text = null, $shortcode = '') {
// Add required libs
	acquia_include('content');
	acquia_include('fonts');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'type' => '',
		'icon_type' => '',
		'title' => '',
		'tag' => 'h4',
		'icon_position' => 'center',
		'border' => 'rounded',
		'color_clone' => 'false',
		'front' => '',
		'size' => 'medium',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	$type = trim($_attrs['type']);

	$_attrs['type'] = ($_attrs['type'] == 'sw') ? acquia_theme_get_settings('ac_iconbox_type', null, 'shortcodes') : $_attrs['type'];
	$_attrs['border'] = ($_attrs['border'] == 'sw') ? acquia_theme_get_settings('ac_iconbox_border', null, 'shortcodes') : $_attrs['border'];
	$_attrs['border_type'] = $_attrs['border'];

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = acquia_get_class_by_args(array('type', 'border_type', 'icon_position', 'size'), $_attrs, CHECK_LENGTH);
	$classes[] = isset($attrs['fid']) && !empty($attrs['fid']) ? $sc_name . '-img' : null;
	$classes[] = 'ac-grid-item';
	$classes[] = 'clearfix';

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;


	// Icon Wrap
	$ico_wrap_attrs = $ico_attrs = $title_attrs = array();
	$ico_wrap_attrs['class'] = array($sc_name.'-icon');

	if (isset($attrs['animate']) && !empty($attrs['animate'])) {
		$ico_wrap_attrs['class'][] = 'ac-animate';
		$ico_wrap_attrs += acquia_get_anim_data_by_attrs($attrs);
	}


	$title_attrs['class'] = array($sc_name.'-title');
	$title_attrs['class'][] = $type == 'top_simple' && !empty($color) && $color != 'custom' ? acquia_get_class_by_args(array('color'), $attrs, CHECK_LENGTH) : NULL;
	if ($_attrs['icon_type'] != 'image') {
		if (!empty($attrs['custom_color'])) {
			if ($type !='simple full') {
				$ico_wrap_attrs['style']['color'] = $attrs['custom_color'];
				if ($type != 'inline-sep' && $_attrs['color_clone'] != 'false') {
					$title_attrs['style']['color'] = $attrs['custom_color'];
				}
			}else{
				$ico_wrap_attrs['style']['background'] = $attrs['custom_color'];
			}
			$ico_wrap_attrs['style']['border-color'] = $attrs['custom_color'];

		}elseif (!empty($attrs['color']) && $attrs['color'] != 'custom'){
			if (in_array($type, array('simple full', 'boxed-simple', 'boxed-fancy', 'boxed-animated'))) {
				$ico_wrap_attrs['class'][] = acquia_get_class_by_args(array('bg_color'), array('bg_color' => $attrs['color']), CHECK_LENGTH);
			}else{
				$ico_wrap_attrs['class'][] = acquia_get_class_by_args(array('color'), $attrs, CHECK_LENGTH);
				if ($_attrs['color_clone'] != 'false') {
					$title_attrs['class'][] = acquia_get_class_by_args(array('color'), $attrs, CHECK_LENGTH);
				}
			}
			$ico_wrap_attrs['class'][] = acquia_get_class_by_args(array('border_color'), array('border_color' => $attrs['color']));
		}
	}
	$icon = '';

	if (isset($ico_wrap_attrs['style'])){
		$ico_wrap_attrs['style'] = acquia_style_arr_to_tag($ico_wrap_attrs['style']);
	}

	if (isset($attrs['icon']) && !empty($attrs['icon'])) {
		// Icon Attributes
		$ico_attrs['class'][] = acquia_fontello_glyph_get_code($attrs['icon']);
		$icon = theme('acquia_iconfont', $ico_attrs);
		if ( isset($attrs['link']) && !empty($attrs['link']) ) {
			$attrs['link'] = $attrs['link'] == 'front' ? '<front>' : $attrs['link'];
			$icon = l($icon, $attrs['link'], array('html' => true, 'attributes' => array('target' => $attrs['link_target'])));
		}

	}else if (isset($attrs['fid']) && !empty($attrs['fid'])){
		$bg_path = '';
		if (!empty($attrs['fid']) && is_numeric($attrs['fid'])) {
			// Build background image path
			if (isset($attrs['style']) && !empty($attrs['style'])) {
				$bg_path = image_style_url($attrs['style'], file_load($attrs['fid'])->uri);
			}else{
				$bg_path = file_create_url(file_load($attrs['fid'])->uri);
			}
		}

		$icon = '<img class="font-icon" src="'.$bg_path.'" alt="'.t('title').'" />';
	}else if (isset($attrs['text']) && !empty($attrs['text'])){

		$ico_attrs['class'][] = 'font-icon';
		$ico_attrs['class'][] = 'text-icon';
		$ico_attrs['class'] = array_filter($ico_attrs['class'], 'strlen');
		$ico_attrs['class'] = implode(' ', $ico_attrs['class']);
		if (isset($ico_attrs['style'])) {
			$ico_attrs['style'] = acquia_style_arr_to_tag($ico_attrs['style']);
		}
		$icon = '<span'.drupal_attributes($ico_attrs).'>'.$attrs['text'].'</span>';
	}

	if (!in_array($type, array('inline', 'boxed-inline', 'boxed-animated'))) {
		$icon = '<div class="icon-wrap"><span'.drupal_attributes($ico_wrap_attrs).'>' .$icon. '</span></div>';
	}else{
		$icon = '<span'.drupal_attributes($ico_wrap_attrs).'>' .$icon. '</span>';
	}

	$title_attrs['class'] = array_filter($title_attrs['class'], 'strlen');
	$title_attrs['class'] = implode(' ', $title_attrs['class']);

	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= '<div class="g-i">';
	$out .= '<div class="g-i-i">';

	if ($type == 'boxed-animated') {
		$out .='<div class="ac-front ac-frame-on">';
		$out .= $icon;
		$out .= '<'.$_attrs['tag'].''.drupal_attributes($title_attrs).'>' .$_attrs['title']. '</'.$_attrs['tag'].'>';
		$out .= '<p>'. strip_tags($_attrs['front']) .'</p>';
		$out .='</div>';
		$out .='<div class="ac-back ac-frame-on">';
		$out .= $text;
		$out .='</div>';
	}else {
		if ($type == 'inline' || $type =='boxed-inline') {
			$title = $icon . '<span class="icon-title">' . $_attrs['title'] . '</span>';
		} else if ($type != 'simple' || $_attrs['icon_position'] !='bottom') {
			$out .= $icon;
		}

		$out .= '<div class="'.$sc_name.'-content-wrap">';
		if (!empty($title)) {
			$out .= '<'.$_attrs['tag'].''.drupal_attributes($title_attrs).'>' .$title. '</'.$_attrs['tag'].'>';
			if ($type == 'simple' && $_attrs['icon_position'] =='bottom') {
				$out .= $icon;
			}
		}
		if (!empty($text)) {
			$out .= '    	<div class="'.$sc_name.'-content">';
			$out .=       	$text;
			$out .= '    	</div>';
		}
		$out .= '		</div>';
	}

	$out .= '</div>';
	$out .= '</div>';
	$out .= '</div>';
	return $out;
}

/**
 * Defines {{ac_iconbox}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_iconbox_sitewide_settings() {
	acquia_include('options');
	return array(
		'ac_iconbox_type' => array(
			'#type' => 'select',
			'#title' => t('IconBox Type'),
			'#description' => t('Set the Type of the IconBox'),
			'#options' => acquia_iconbox_types(),
		),
		'ac_iconbox_border' => array(
			'#type' => 'select',
			'#title' => t('border type'),
			//'#description' => t('Set the Type of the IconBox'),
			'#options' => acquia_iconbox_border_types(),
		),
	);
}
