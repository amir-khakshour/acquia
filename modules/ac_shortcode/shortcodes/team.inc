<?php

/**
 * Implements hook_shortcodes
 */
function ac_shortcode_team_shortcode() {
	return array(
		'ac_team' => array (
			'title' => t('Team Member'),
			'description' => t('Display a team members image with additional information.'),
			'form callback' => 'ac_shortcode_ac_team_form',
			'values process callback' => 'ac_shortcode_ac_team_preprocess',
			'process callback' => 'ac_shortcode_ac_team_process',
			'nested shortcodes' => array('socials' => 'ac_font_icon'),
			'sitewide settings' => 'ac_shortcode_ac_team_sitewide_settings',
		),
	);
}

/**
 * Implements edit form of {{ac_team}} shortcode
 */
function ac_shortcode_ac_team_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');
	$cid = &drupal_static(__FUNCTION__);

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	// Convert socials from editor to form compatible.
	if (isset($values['socials']) && is_array($values['socials']) && !isset($values['socials']['social'])) {
		foreach($values['socials'] as &$social){
			$social['fonticon'] = array('icon' => $social['icon'], 'font' => $social['font']);
		}
		$form_state['social_nums'] = count($values['socials']);
		$values['socials'] = array('social' => $values['socials']);
	}

	$default = array(
		'icon' => '',
		'title' => '',
		'link' => '',
		'link_target' => '_self',
		'socials' => array(),
	);

	$form = array();

	$form['type'] = array(
		'#type' => 'select',
		'#title' => t('Team Member box type'),
		'#description' => t('Select the style of team member box.'),
		'#default_value' => isset($values['type']) ? $values['type'] : NULL,
		'#options' => acquia_team_types(), // @TODO add sitewide settings
	);

	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Team Member Name'),
		'#description' => t('Name of the person'),
		'#default_value' => isset($values['name']) ? $values['name'] : t('John Doe'),
	);

	$form['job'] = array(
		'#type' => 'textfield',
		'#title' => t('Team Member Job title'),
		'#description' => t('Job title of the person.'),
		'#default_value' => isset($values['job']) ? $values['job'] : t('Team Member Job title'),
	);

	$form['fid'] = array(
		'#type' => 'media',
		'#title' => t('Team Member Image'),
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
		'#title' => t('Team Member Image Style'),
		'#description' => t('Apply an image style to the Team Member Image.'),
		'#options' => $ops,
		'#default_value' => isset($values['style']) ? $values['style'] : 'sw',
	);

	// use tree structure as we use multiple tabs
	$form['#tree'] = TRUE;

	$form['bio'] = array(
		'#type' => 'text_format',
		'#title' => t('Team Member Description'),
		'#description' => t('Enter a few words that describe the person.'),
		'#default_value' => isset($values['bio']) ? rawurldecode(base64_decode(strip_tags($values['bio']))) : array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	if (empty($form_state['social_nums'])) {
		$form_state['social_nums'] = 1;
	}

	$form['socials'] = array(
		'#type' => 'fieldset',
		'#title' => t('Add/Edit socials Service or Icon Links'),
		'#description' => t('Bellow each Team Member you can add Icons that link to destinations like facebook page, twitter account etc.'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);

	for ($i = 0; $i < $form_state['social_nums']; $i++) {
		$icon_defaults = isset($values['socials']['social']) ? $values['socials']['social'] : array();
		$icon_defaults[$i] = isset($icon_defaults[$i]) ? $icon_defaults[$i] : array();
		$icon_defaults[$i] += $default;
		$form['socials']['social'][$i] = array(
			'#type' => 'fieldset',
			'#title' => t('social #@num', array('@num' => $i+1)),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
		);

		$form['socials']['social'][$i]['delete'] = array (
			'#type' => 'checkbox',
			'#title' => t('delete this icon?'),
			'#description' => t ( 'Turn it On to delete item.' ),
		);

		acquia_field_iconfont($form['socials']['social'][$i], $form, array(
			'title' => t('social Icon'),
			'default' => $icon_defaults[$i]['fonticon']['icon'],
			'collapsed' => !empty($icon_defaults[$i]['fonticon']['icon']) ? FALSE : TRUE,
			'parents' => array('socials', 'social', $i),
			'always_enabled' =>TRUE,
		));

		// Adding Tooltip Values		
		$form['socials']['social'][$i]['info_title'] = array(
			'#type' => 'textfield',
			'#title' => t('Hover Text'),
			'#description' => t('Text that appears if you place your mouse above the Icon.'),
			'#default_value' => $icon_defaults[$i]['info_title'],
		);

		$form['socials']['social'][$i]['info'] = array(
			'#type' => 'value',
			'#value' => 'tooltip',
		);

		$form['socials']['social'][$i]['info_place'] = array(
			'#type' => 'value',
			'#value' => 'top',
		);

		$form['socials']['social'][$i]['info_trigger'] = array(
			'#type' => 'value',
			'#value' => 'hover',
		);

		$form['socials']['social'][$i]['link'] = array(
			'#type' => 'textfield',
			'#title' => t('Icon Link?'),
			'#description' => t('Where should your Icon link to?'),
			'#default_value' => $icon_defaults[$i]['link'],
		);

		$form['socials']['social'][$i]['link_target'] = array(
			'#type' => 'select',
			'#title' => t('Open Link in new Window?'),
			'#description' => t('Select here if you want to open the linked page in a new window'),
			'#default_value' => $icon_defaults[$i]['link'],
			'#options' => array(
				'_blank' => t('Yes, open in new window'),
				'_self' => t('No, open in same window'),
			),
			'#states' => array(
				'disabled' => array(
					':input[name="socials[social]['.$i.'][link]"]' => array('value' => ''),
				),
				'invisible' => array(
					':input[name="socials[social]['.$i.'][link]"]' => array('value' => ''),
				),
			),
		);
	}

	$form['socials']['add_social'] = array(
		'#prefix' => '<div class="form-actions">',
		'#suffix' => '</div>',
		'#type' => 'submit',
		'#value' => t('Add another social'),
		'#submit' => array('ac_shortcode_ac_team_add_social'),
	);

	$form['gridy'] = array(
		'#attributes' => array('data-help' => t('turn it on if this item is in grid shortcode.')),
		'#type' => 'checkbox',
		'#title' => t('Enable gridy?'),
		//'#description' => t('chenge to On if you want to enable lightbox on this image.'),
		'#default_value' => isset($values['gridy']) && $values['gridy'] == 'true' ? TRUE :FALSE,
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
 * Submit handler for "Add another social" button on ac_shortcode_form_accordion().
 */
function ac_shortcode_ac_team_add_social($form, &$form_state) {
	$form_state['social_nums']++;
	$form_state['rebuild'] = TRUE;
}

/**
 * preprocess {{ac_team}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_team_preprocess(&$values) {
	// manually extract fid because we use #tree for the form
	if (isset($values['fid']) && isset($values['fid']['fid'])) {
		$values['fid'] = $values['fid']['fid'];
	}
	if (isset($values['bio']) && isset($values['bio']['value'])) {
		$values['bio'] = base64_encode($values['bio']['value']);
	}
	if (isset($values['src'])) {
		unset($values['src']);
	}
	$socials = $values['socials'];
	unset($values['socials']);
	$values['socials'] = $socials['social'];
	foreach($values['socials'] as $id => &$social){
		if ($social['delete'] || !isset($social['fonticon']['icon']) || empty($social['fonticon']['icon'])) {
			unset($values['socials'][$id]);
		}else{
			$social += $social['fonticon'];
			unset($social['fonticon']);
		}
		unset($social['delete']);
		$social['info'] = 'tooltip';
	}

	if (isset($values['gridy']) && $values['gridy'] == TRUE) {
		$values['gridy'] = 'true';
	}else{
		unset($values['gridy']);
	}
}

/**
 * process {{ac_team_item}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_team_process($attrs, $text = null, $shortcode = '') {
	$cid = ac_shortcode_gen_cid($shortcode, $attrs, $text);
//	$cache = cache_get($cid, 'cache_ac_shortcode');
	$cache = null;
	if (!empty($cache)) {
		$out = $cache->data;
	}
	else{
		// Add required libs
		acquia_include('content');
		acquia_include('utility');
		$_attrs = ac_shortcode_attrs(array(
			'name' => '',
			'job' => '',
			'fid' => '',
			'style' => '',
			'bio' => '',
			'type' => 'simple',
		), $attrs);
		extract($_attrs);
		$sc_name = str_replace('_', '-', $shortcode);

		// Get sitewide settings
		$type = ($type == 'sw') ? acquia_theme_get_settings('ac_team_type', null, 'shortcodes') : $type;

		// Build Teammate Picture
		$team_pic = '';
		if (!empty($fid) && is_numeric($fid)) {
			$file = file_load($fid);
			if (isset($file->uri)) {
				if (!empty($style)) {
					$style = ($style == 'sw') ? acquia_theme_get_settings('ac_team_style', null, 'shortcodes') : $style;
					$team_pic = image_style_url($style, $file->uri);
				} else {
					$team_pic = file_create_url($file->uri);
				}
			} else {
				$team_pic = file_create_url(acquia_variable_get('empty_image_uri'));
			}

		}

		$classes = array();
		$classes[] = $sc_name . '-wrap';
		$classes[] = 'clearfix';
		$classes[] = acquia_get_class_by_args(array('type'), $attrs, CHECK_LENGTH);
		$classes[] = !empty($type) ? 'ac-effect-container' : NULL;
		$classes[] = 'clearfix';

		if ($type == 'blur') {
			$classes[] = acquia_get_class_by_args(array('effect'), array('effect' => $type), CHECK_LENGTH);
		}

		//---------------------------------------
		if (!empty($attrs['class'])) {
			foreach (explode(' ', $attrs['class']) as $class) {
				$classes[] = $class;
			}
		}
		$classes = array_filter($classes, 'strlen');
		//---------------------------------------
		$attributes['class'] = $classes;

//			list($width) = @getimagesize($team_pic);

		$out = '<div' . drupal_attributes($attributes) . '>';
		$out .= '<figure class="' . $sc_name . ' item-i ac-frame-on clearfix">';
		$out .= '<div class="' . $sc_name . '-profile clearfix">';

		if ($type == 'blur') {
			if (!empty($text)) {
				$out .= '<div class="socials-wrap"><table class="socials"><tbody><tr><td>' . $text . '</td></tr></tbody></table></div>';
			}
		}

		// Add teammate image
		$out .= '<div class="img-wrap"><img alt="' . $name . '" src="' . $team_pic . '" class="clearfix"/></div>';
		$out .= '</div>';

		// [ac-team-profile] ends

		// name starts
		$out .= '<figcaption class="' . $sc_name . '-name">';

		if ($type == 'simple compact' && !empty($text)) {
			$out .= '<div class="ac-table">';
			$out .= '<div class="ac-cell teammate-info">';
		}

		if (!empty($name)) {
			$out .= '<h4 class="title">' . $name . '</h4>';
		}
		if (!empty($job)) {
			$out .= '<p class="job">' . $job . '</p>';
		}

		if ($type == 'simple compact' && !empty($text)) {
			$out .= '</div>';
			$out .= '<div class="socials ac-cell clearfix"><div class="inner">' . $text . '</div></div>';
			$out .= '</div>';
		} else if ($type == 'columns') {
			$out .= '<div class="socials clearfix"><div class="inner">' . $text . '</div></div>';
		}
		if (!empty($bio)) {
			$bio = check_markup(base64_decode($bio), 'full_html');
			$out .= '<div class="bio">' . $bio . '</div>';
		}
		if (in_array($type, array('simple', 'simple glow', 'overlaid', 'simple circled')) && !empty($text)) {
			$out .= '<div class="socials clearfix"><div class="inner">' . $text . '</div></div>';
		}
		$out .= '</figcaption>';
		// name ends

		$out .= '</figure>';
		$out .= '</div>';

		/** Wrap Grid HTML **/
		if (isset($attrs['gridy']) && strtolower($attrs['gridy']) == 'true') {
			$temp = '<div class="ac-grid-item">';
			$temp .= '	<div class="g-i clearfix">';
			$temp .= '		<div class="g-i-i clearfix">';
			$temp .= $out;
			$temp .= '		</div>';
			$temp .= '	</div>';
			$temp .= '</div>';

			$out = $temp;
		}

		cache_set($cid, $out, 'cache_ac_shortcode');
	}
	return $out;
}

/**
 * Defines {{ac_team}} vars that can be set from theme settings form
 */
function ac_shortcode_ac_team_sitewide_settings() {
	acquia_include('options');
	return array(
		'ac_team_style' => array(
			'#type' => 'select',
			'#title' => t('Team Member Image style'),
			'#description' => t('Select the default sitewide image style to apply to your Team Member Images.'),
			'#options' => image_style_options(),
		),
		'ac_team_type' => array(
			'#type' => 'select',
			'#title' => t('Team Member box style'),
			'#description' => t('Select the style of team member box.'),
			'#options' => acquia_team_types(),
		),
	);
}
