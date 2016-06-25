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

function ac_shortcode_contact_info_shortcode() {
	return array(
		'ac_contact_info' => array(
			'title' => t('Contact Info'),
			'description' => t('Displaying a list of contact details.'),
			'form callback' => 'ac_shortcode_ac_contact_info_form',
			'values process callback' => 'ac_shortcode_ac_contact_info_preprocess',
			'process callback' => 'ac_shortcode_ac_contact_info_process',
			'nested shortcodes' => array('socials' => 'ac_font_icon'),
		),
	);
}

/**
 * Implements edit form of {{ac_fancy_contact_info}} shortcode
 */
function ac_shortcode_ac_contact_info_form($form, &$form_state) {
	acquia_include('fields');
	acquia_include('options');

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
		'info_title' => '',
		'fonticon ' => array('icon' => NULL),
	);

	$form = array();

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Style'),
		'#description' => '',
		'#options' => array('compact' => t('Compact style'), 'list' => t('List style'), '2-col' => t('2 columns')),
		'#default_value' => isset($values['style']) ? $values['style'] : 'list',
	);

	$form['person'] = array(
		'#type' => 'textfield',
		'#title' => t('Person'),
		'#description' => '',
		'#default_value' => isset($values['person']) ? $values['person'] : NULL,
	);

	$form['company'] = array(
		'#type' => 'textfield',
		'#title' => t('Company'),
		'#description' => '',
		'#default_value' => isset($values['company']) ? $values['company'] : NULL,
	);

	$form['address'] = array(
		'#type' => 'textfield',
		'#title' => t('Address'),
		'#description' => '',
		'#default_value' => isset($values['address']) ? $values['address'] : NULL,
	);

	$form['phone'] = array(
		'#type' => 'textfield',
		'#title' => t('Phone'),
		'#description' => '',
		'#default_value' => isset($values['phone']) ? $values['phone'] : NULL,
	);

	$form['fax'] = array(
		'#type' => 'textfield',
		'#title' => t('Fax'),
		'#description' => '',
		'#default_value' => isset($values['fax']) ? $values['fax'] : NULL,
	);

	$form['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#description' => '',
		'#default_value' => isset($values['email']) ? $values['email'] : NULL,
	);

	$form['website'] = array(
		'#type' => 'textfield',
		'#title' => t('Website'),
		'#description' => '',
		'#default_value' => isset($values['website']) ? $values['website'] : NULL,
	);

	$form['skype'] = array(
		'#type' => 'textfield',
		'#title' => t('Skype Username'),
		'#description' => '',
		'#default_value' => isset($values['skype']) ? $values['skype'] : NULL,
	);

	// use tree structure as we use multiple tabs
	$form['#tree'] = TRUE;

	if (empty($form_state['social_nums'])) {
		$form_state['social_nums'] = 1;
	}

	$form['socials'] = array(
		'#type' => 'fieldset',
		'#title' => t('Add/Edit socials Service or Icon Links'),
		'#description' => t('You can add Icons that link to destinations like facebook page, twitter account etc.'),
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
		'#submit' => array('ac_shortcode_ac_contact_info_add_social'),
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
function ac_shortcode_ac_contact_info_add_social($form, &$form_state) {
	$form_state['social_nums']++;
	$form_state['rebuild'] = TRUE;
}

/**
 * preprocess {{ac_team}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_contact_info_preprocess(&$values) {
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
}


/**
 * process {{ac_fancy_contact_info}} and {{ac_page_contact_info}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_contact_info_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
		'style' => 'list',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = acquia_get_class_by_args(array('style'), $_attrs, CHECK_LENGTH, 'contact');
	$attributes['class'][] = 'ac-s-li';
	$attributes['class'][] = 'ac-li-bordered';
	$attributes['class'][] = 'clearfix';

	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	//---------------------------------------

	$contact_attrs = array(
		'person' => t('person'),
		'company' => t('company'),
		'address'=> t('address'),
		'phone' => t('phone number'),
		'fax' => t('fax'),
		'email' => t('e-mail'),
		'website' => t('website'),
		'skype' => t('skype'),
	);

	if (isset($attrs['skype']) && !empty($attrs['skype'])) {
		$attrs['skype'] = '<a href="skype:'.$attrs['skype'].'?call">' .$attrs['skype'] .'</a>';
	}

	$items = array();
	$i = $count = 0;

	foreach($contact_attrs as $key => $title) {
		if (isset($attrs[$key]) && !empty($attrs[$key])) {
			$count++;
		}
	}

	foreach($contact_attrs as $key => $title) {
		$item = '';
		if (isset($attrs[$key]) && !empty($attrs[$key])) {
			$class = '';
			if ($i== 0){
				$class =' first';
			}else if($i == $count-1) {
				$class =' last';
			}
			$item .= '<li class="ac-'.$key.'-detail detail'.$class.'">';
			if ($style !='list') {
				$item .= '	<span class="font-icon icon-'.$key.'"></span>';
			}else{
				$item .= '	<span class="label">'.$title.':&nbsp;</span>';
			}
			$item .= '	<span class="detail">'.$attrs[$key].'</span>';
			$item .= '</li>';
			$items[] =$item;
			$i++;
		}
	}
	$text = trim($text);
	// Generate output
	$out  = '<ul'.drupal_attributes($attributes).'>';
	if ($style == '2-col') {
		$fraction = ceil(count($items) /2);
		$out .= '<li class="ac-col ac-one-half first"><ul class="ac-s-li">'. implode('', array_slice($items, 0, $fraction)) .'</ul></li>';
		$out .= '<li class="ac-col ac-one-half"><ul class="ac-s-li">'. implode('', array_slice($items, $fraction)) .'</ul></li>';
	}else{
		$out .= implode('', $items);
	}
	if (!empty($text)) {
		$out .= '<li class="acquia-share-links">' .$text .'</li>';
	}
	$out .= '</ul>';

	return $out;
}
