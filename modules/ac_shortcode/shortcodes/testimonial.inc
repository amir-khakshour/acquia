<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_testimonial_shortcode() {
	return array(
		'ac_testimonials' => array (
			'title' => t('Testimonials'),
			'description' => t('Creates a list of Testimonials'),
			'form callback' => 'ac_shortcode_ac_testimonials_form',
			'values process callback' => 'ac_shortcode_ac_testimonials_preprocess',
			'process callback' => 'ac_shortcode_ac_testimonials_process',
			'sitewide settings' => 'ac_shortcode_ac_testimonials_sitewide_settings',
		),
		'ac_testimonial' => array(
			'title' => t('Testimonial'),
			'description' => t('Creates a Testimonail item.'),
			'hidden' => TRUE,
			'enabled' => array('ac_testimonials' => true),
			'process callback' => 'ac_shortcode_ac_testimonial_process',
			'values process callback' => 'ac_shortcode_ac_testimonial_preprocess',
			'form callback' => 'ac_shortcode_ac_testimonial_form',
		)
	);
}

/**
 * Implements edit form of {{ac_testimonials}} shortcode
 */
function ac_shortcode_ac_testimonials_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();
//	$form['style'] = array(
//		'#type' => 'select',
//		'#title' => t('Style'),
//		'#description' => t('Set the style of your testimonial items.'),
//		'#default_value' => isset($values['style']) ? $values['style'] : 'fancy',
//		'#options' => array(
//			'simple' => t('Simple - no border and avatar'),
//			'simple_avatar' => t('Simple with avatar'),
//			'fancy' => t('Fancy - Border enabled'),
//		),
//	);
	$form['appearance'] = array(
		'#type' => 'select',
		'#title' => t('Appearance'),
		'#description' => t('Set the appearance of your testimonial items.'),
		'#default_value' => isset($values['appearance']) ? $values['appearance'] : '',
		'#options' => array(
			'' => t('None'),
			'masonry' => t('Masonry'),
			'grid' => t('Grid'),
			'scroller' => t('Scroller'),
		),
	);

	$form['columns'] = array (
		'#type' => 'select',
		'#title' => t('Columns'),
		'#description' => t ( 'Number of Columns for grid layout; e.g. 4' ),
		'#default_value' => isset($values['columns']) ? $values['columns'] : 4,
		'#options' => drupal_map_assoc ( range (1, 6) )
	);

	$form['break'] = array (
		'#type' => 'textfield',
		'#title' => t('Responsive Width'),
		'#description' => t('By default 150px.'),
		'#default_value' => isset($values['break']) ? $values['break'] : 150,
	);

	$form['font'] = array(
		'#type' => 'select',
		'#title' => t('Testimonials Font size'),
		'#description' => t('Font size of Testimonial\'s  text.'),
		'#default_value' => isset($values['font']) ? $values['font'] : 'sw',
		'#options' => array_merge(array('' => t('Theme Default')), acquia_font_sizes()),
	);
	$form['slider'] = array(
		'#type' => 'fieldset',
		'#title' => t('Scroller Settings'),
		//'#description' => t('Select width of Carousel Items based on pixel format.'),
		'#states' => array(
			'enabled' => array(
				':input[name="appearance"]' => array('value' => 'scroller'),
			),
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'scroller'),
			),
		),
	);

	$form['slider']['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => isset($values['padding']) ? $values['padding'] : acquia_variable_get('portfolio_blocks_padding', 20),
	);
	$values['auto'] = isset($values['auto']) && $values['auto'] == 'true' ? TRUE : FALSE;
	$form['slider']['auto'] = array(
		'#type' => 'checkbox',
		'#title' => t('Carousel should scroll automatically or not?'),
		'#default_value' => $values['auto'],
	);
	$values['nav'] = isset($values['nav']) && $values['nav'] == 'true' ? TRUE : FALSE;
	$form['slider']['nav'] = array(
		'#type' => 'checkbox',
		'#title' => t('Display Prev and Next navigation buttons.?'),
		'#default_value' => $values['nav'],
	);

	$values['controls'] = isset($values['controls']) && $values['controls'] == 'true' ? TRUE : FALSE;
	$form['slider']['controls'] = array(
		'#type' => 'checkbox',
		'#title' => t('Display pager controls buttons?'),
		'#default_value' => $values['controls'],
	);

	$settings = array(
		'title' => t('Testimonials'),
		'delay_enabled' => TRUE
	);
	if (isset($values['animate'])) {
		$settings['animate'] = $values['animate'];
		$settings['when'] = $values['when'];
		$settings['delay'] = $values['dely'];
	}

	// add animate fields
	acquia_field_animate($form, $settings);

	$form['where'] = array(
		'#type' => 'select',
		'#title' => t('Animate Section'),
		'#description' => t('Choose which section to animate?'),
		'#default_value' => isset($values['where']) ? $values['where'] : 'icon',
		'#options' => array(
			'block' => t('Testimonial items'),
			'icon' => t('Testimonial icons'),
		),
		'#states' => array(
			'visible' => array(
				':input[name="cssanimate[enabled]"]' => array('checked' => TRUE),
			),
			'enabled' => array(
				':input[name="cssanimate[enabled]"]' => array('checked' => TRUE),
			),
		),
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
 * preprocess {{ac_testimonials}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_testimonials_preprocess(&$values) {
	if (isset($values['type']) && $values['type'] != 'scroller') {
		unset($values['auto']);
		unset($values['nav']);
		unset($values['controls']);
		unset($values['easing']);
		unset($values['padding']);
		unset($values['speed']);
		unset($values['spans']);
	}

	if (isset($values['auto']) && $values['auto'] == TRUE) {
		$values['auto'] = 'true';
	}else{
		unset($values['auto']);
	}

	if (isset($values['nav']) && $values['nav'] == TRUE) {
		$values['nav'] = 'true';
	}else{
		unset($values['nav']);
	}
	if (isset($values['controls']) && $values['controls'] == TRUE) {
		$values['controls'] = 'true';
	}else{
		unset($values['controls']);
	}
}
/**
 * Implements edit form of {{ac_testimonial}} shortcode
 */
function ac_shortcode_ac_testimonial_form($form, &$form_state) {
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

	$form['avatar_pos'] = array(
		'#type' => 'select',
		'#title' => t('Avatar Position'),
		'#description' => t('Set the position of the Avatar'),
		'#default_value' => isset($values['avatar_pos']) ? $values['avatar_pos'] : 'left',
		'#options' => array(
			'headshot' => t('Headshot'),
			'right' => t('Right side of testimonial'),
			'bottom' => t('Bottom side of testimonial'),
			'left' => t('Left side of testimonial'),
		),
	);

	$form['fid'] = array(
		'#type' => 'media',
		'#title' => t('Author Avatar'),
		'#description' => t('Either upload a new, or choose an existing image from your media library.'),
		'#default_value' => isset($values['fid']) ? array('fid' => $values['fid']) : NULL,
		'#media_options' => array(
			'global' => array(
				'types' => array('image'),
				'file_directory' => acquia_variable_get('public_path', 'acquia') . '/shortcodes/img',
			),
		),
	);

	$ops = image_style_options();
	add_default_option($ops);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Author Avatar Style'),
		'#description' => t('Apply an image style to the Author Avatar.'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : 'sw',
	);

	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Author Name'),
		'#description' => t('Enter the Author first and last name here.'),
		'#default_value' => isset($values['name']) ? $values['name'] : t('John Doe'),
	);

	$form['position'] = array(
		'#type' => 'textfield',
		'#title' => t('Author position'),
		'#description' => t('Enter the Author position here.'),
		'#default_value' => isset($values['position']) ? $values['position'] : '',
	);

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Testimonial'),
		'#description' => t('Enter the Testimonial text here.'),
		'#default_value' => isset($values['content']) ? $values['content'] : t('Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.'),
		'#format' => NULL,
		'#rows' => 15,
	);

	$form['link'] = array(
		'#type' => 'textfield',
		'#title' => t('Auhtor Home Page?'),
		'#description' => t('Leave it blank if you don\'t want to include author home page.?'),
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
 * preprocess {{ac_testimonial}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_testimonial_preprocess(&$values) {
	if (!isset($values['link']) || $values['link'] =='') {
		unset($values['link']);
		unset($values['link_target']);
	}

	if (!isset($values['animate'])) {
		unset($values['where']);
	}
}
/**
 * process {{ac_testimonial}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_testimonial_process($attrs, $text = null, $shortcode = '') {
	// Add required libs
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'avatar_pos' => 'headshot',
		'name' => '',
		'position' => '',
		'fid' => '',
		'style' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	// Build Teammate Picture
	$avatar = '';
	if (!empty($fid) && is_numeric($fid)) {
		if (!empty($style)) {
			$style = ($style == 'sw') ? acquia_theme_get_settings('ac_testimonial_style', null, 'shortcodes') : $style;
			$file = file_load($fid);
			if (isset($file->uri)){
				$avatar = image_style_url($style, $file->uri);
			}
		}else {
			$avatar = file_create_url(file_load($fid)->uri);
		}
	}

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'ac-grid-item';
	$classes[] = 'clearfix';
	$classes[] = acquia_get_class_by_args(array('avatar_pos'), $_attrs, CHECK_LENGTH);

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$container_attrs = array();
	$container_attrs['class'] = $classes;

	$avatar = !empty($avatar) ? '<img src="'.$avatar.'" alt="'.$name.'" class="author-avatar"/>' : '';
	$name = !empty($name) ? '<span class="name">'.$name.'</span>' : NULL;

	if (isset($attrs['link']) && !empty($attrs['link'])) {
		$attrs['link'] = $attrs['link'] == 'front' ? '<front>' : $attrs['link'];
		$attrs['link_target'] = isset($attrs['link_target']) ? $attrs['link_target'] : '_self';
		$avatar = l($avatar, $attrs['link'], array('html' => true, 'attributes' => array('target' => $attrs['link_target'])));
		$name = !empty($name) ? l($name, $attrs['link'], array('html' => true, 'attributes' => array('target' => $attrs['link_target']))) : NULL;
	}

//	$avatar = !empty($avatar) ? '<span class="a-avatar ac-cell">'.$avatar.'</span>' : NULL;
	$sep = !empty($name) && !empty($position) ? '<span class="sep">-</span>' : NULL;
//	$name = !empty($name) ? '<div class="a-info ac-cell"><h5 class="s-title cell-i">'.$name.'</h5><p class="pos cell-i">'.$sep.$position.'</p></div>' : NULL;


	$theme = sprintf('ac_shortcode_testimonials_%s', $avatar_pos);
	return theme($theme, array(
		'avatar' => $avatar,
		'testimonial' => $text,
		'name' => $name,
		'position' => $position,
		'container_attrs' => $container_attrs
	));

}

/**
 * process {{ac_testimonials}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_testimonials_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');

	$_attrs = ac_shortcode_attrs(array(
//		'style' => 'simple',
		'appearance' => '',
		'columns' => '4',
		'break' => '150',
		'auto' => 'false',
		'nav' => 'false',
		'controls' => 'false',
		'padding' => '',
		'font' => 'normal',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'clearfix';
	$classes[] = acquia_get_class_by_args(array('appearance', 'font'), $_attrs, CHECK_LENGTH);
	$classes[] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$classes[] = $appearance == 'masonry' ? 'ac-init-hidden' : null;

	if ($appearance == 'slider') {
		$classes[] = $appearance == 'slider' ? 'ac-min-slider dark_nav' : null;
	}
	else if ($appearance == 'grid') {
		// Data attributes
		acquia_include('utility', 'ac_shortcode');
		$classes[] = 'ac-grid';
		$data_attrs = array();
		$data_attrs['columns'] = $_attrs['columns'];
		$data_attrs['break'] = $_attrs['break'];
		$data_attrs['cols-width'] = ac_shortcode_col_to_width($_attrs['columns']);
		$attributes += acquia_data_arr_to_tag_arr($data_attrs);
	}

	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	//---------------------------------------

	// Animate data
	if (isset($attrs['animate'])) {
		$attributes += acquia_get_anim_data_by_attrs($attrs);
	}

	if ($appearance == 'masonry') {
		acquia_load_resources('isotope');
		$classes[] = 'ac-grid';
		$data_attrs = array();
		$data_attrs['columns'] = $_attrs['columns'];
		$data_attrs['cols-width'] = ac_shortcode_col_to_width($_attrs['columns']);
		$attributes += acquia_data_arr_to_tag_arr($data_attrs);

	}else if ($appearance  == 'scroller') {
		// Callout Button 
		$tag = 'ac_carousel'; // button shortcode
		$tag_info = ac_shortcode_get_sc_info($tag);
		ac_shortcode_add_sc_files($tag_info);
		if (isset($tag_info['process callback']) && function_exists($tag_info['process callback'])){
			$text = call_user_func($tag_info['process callback'], $attrs, $text, $tag);
		}
	}

	$attributes['class'] = $classes;

	$out = '';
	$out .= '<ul'.drupal_attributes($attributes).'>';
	$out .= $text;
	$out .= '</ul>';

	return $out;
}

/**
 * Defines {{ac_testimonials}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_testimonials_sitewide_settings() {
	acquia_include('options');
	return array(
		'ac_testimonial_style' => array(
			'#type' => 'select',
			'#title' => t('Author Avatar Style'),
			'#description' => t('Apply an image style to the Author Avatar.'),
			'#options' => image_style_options(),
		),
		'ac_testimonial_cols' => array(
			'#type' => 'select',
			'#title' => t('Columns'),
			'#description' => t('Number of Testimonial Columns.'),
			'#options' => drupal_map_assoc ( range (1, 6) )
		),
	);
}