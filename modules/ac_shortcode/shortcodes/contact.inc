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

function ac_shortcode_contact_shortcode() {
	return array(
		'ac_contact' => array(
			'title' => t('Contact'),
			'description' => t('Creates a contact us form.'),
			'form callback' => 'ac_shortcode_ac_contact_form',
			'values process callback' => 'ac_shortcode_ac_contact_preprocess',
			'process callback' => 'ac_shortcode_ac_contact_process',
		),
	);
}

/**
 * Implements edit form of {{ac_contact}} shortcode
 */
function ac_shortcode_ac_contact_form($form, &$form_state) {
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

	$cats = ac_shortcode_ac_contact_get_contact_categories();
	if (count($cats) == 1){
		drupal_set_message(t('No Contact categories available. please create at least one category from !link.', array('!link' => l('here', 'admin/structure/contact'))), 'error');
	}

	$form['cid'] = array(
		'#type' => 'select',
		'#title' => t('Contact Category'),
		'#description' => t('Select a contact category to display.'),
		'#options' => ac_shortcode_ac_contact_get_contact_categories(),
		'#default_value' => isset($values['cid']) ? $values['cid'] : NULL,
	);

	$form['style'] = array(
		'#type' => 'select',
		'#title' => t('Style'),
		'#description' => t('Set the contact form style.'),
		'#default_value' => isset($values['style']) ? $values['style'] : '',
		'#options' => array('simple' => t('Simple'), 'centered' => 'Centered'),
	);

	$form['bg_style'] = array(
		'#type' => 'select',
		'#title' => t('Form background type'),
		'#description' => t('Select a background type for your contact form here; e.g. light for a dark section!'),
		'#options' => array('light' => t('light'), 'dark' => t('Dark')),
		'#default_value' => isset($values['bg_style']) ? $values['bg_style'] : 'dark',
	);

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('title'),
		'#description' => t('Set this field empty if you want default category title to be used.'),
		'#default_value' => isset($values['title']) ? $values['title'] : '',
	);

	$form['text_format_cid'] = array(
		'#type' => 'value',
		'#value' => array($cid => 'content'),// key of cids and related real form id
	);

	$form[$cid] = array(
		'#type' => 'text_format',
		'#title' => t('Content'),
		'#description' => t('Enter the text to place before contact form.'),
		'#default_value' => isset($values['content']) ? $values['content'] :
			array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	$form['hide_labels'] = array(
		'#type' => 'checkbox',
		'#title' => t('Hide labels?'),
		'#description' => t('.'),
		'#default_value' => isset($values['hide_labels'])&& $values['hide_labels'] == 'true' ? TRUE : FALSE,
	);

	$form['minimal'] = array(
		'#type' => 'checkbox',
		'#title' => t('minimal style?'),
		'#description' => t('.'),
		'#default_value' => isset($values['minimal'])&& $values['minimal'] == 'true' ? TRUE : FALSE,
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
 * Process {{ac_contact}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_contact_preprocess(&$values) {
	if(isset($values['cid']) && !empty($values['cid'])) {
		$cats = ac_shortcode_ac_contact_get_contact_categories();
		$values['type_title'] = t($cats[$values['cid']]);
	}

	if (isset($values['hide_labels']) && $values['hide_labels']) {
		$values['hide_labels'] = 'true';
	}else{
		unset($values['hide_labels']);
	}

	if (isset($values['minimal']) && $values['minimal']) {
		$values['minimal'] = 'true';
	}else{
		unset($values['minimal']);
	}
}

/**
 * process {{ac_contact}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_contact_process($attrs, $text = null, $shortcode = '') {
	if (!module_exists('contact')) {
		return;
	}
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'cid' => '',
		'title' => '',
		'style' => '',
		'bg_style' => '',
		'hide_labels' => 'true',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'clearfix';
	$classes[] = $hide_labels != 'false' ? 'ac-fancy-form' : '';
	$classes[] = isset($attrs['minimal']) && $attrs['minimal'] != 'false' ? 'ac-minimal-style' : '';
	$classes[] = acquia_get_class_by_args(array('style', 'bg_style'), $_attrs, CHECK_LENGTH);


	$cats = ac_shortcode_ac_contact_get_contact_categories();
	$cid = in_array($cid, array_keys($cats)) ? $cid : array_shift(array_keys($cats));

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;

	/** Build Form **/
	module_load_include('inc', 'contact', 'contact.pages');

	// Get Additional Info
	//if (empty($title)) {
	//  $title = ($cid !=0) ? t('You can send @category a message using the contact form below.',
	//													array('@category' => $cats[$cid])) : t('send us a message using the contact form below.');
	//}
	//

	$form_state = array('values' => array('cid' => $cid));
	$form = drupal_build_form('contact_site_form', $form_state);

	if (!empty($title)) {
		$form['contact_information'] = array(
			'#markup' => '<h4>' . filter_xss_admin($title) . '</h4>',
			'#weight' => -1,
			'#prefix' => '<div class="form-item">',
			'#suffix' => '</div>',
		);
	}
	if (!empty($text)) {
		$form['contact_text'] = array(
			'#markup' => '<div class="contact_text">' . filter_xss_admin($text) . '</div>',
			'#weight' => -1,
			'#prefix' => '<div class="form-item">',
			'#suffix' => '</div>',
		);
	}

	if ($cid !=0) {
		$form['cid']['#value'] = $cid;
		$form['cid']['#prefix'] = '<div class="ac-no-display">';
		$form['cid']['#suffix'] = '</div>';
	}
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '		'. drupal_render($form);
	$out .= '</div>';

	return $out;
}

/**
 * Get Contact Categories from DB
 */
function ac_shortcode_ac_contact_get_contact_categories($reset = false) {
	$categories = &drupal_static(__FUNCTION__, NULL);

	if (!isset($categories) || $reset) {
		$cid = 'acquia:contact:categories';
		if (!$reset && ($cache = cache_get($cid)) && !empty($cache->data)) {
			$categories = $cache->data;
		}else{
			$categories[0] = t('All - Display Category list');
			// Get all the contact categories from the database.
			$cat = db_select('contact', 'c')
				->addTag('translatable')
				->fields('c', array('cid', 'category', 'recipients', 'selected'))
				->orderBy('weight')
				->orderBy('category')
				->execute()
				->fetchAll();

			// Loop through the categories and add them to the table.
			foreach ($cat as $category) {
				$categories[$category->cid] = check_plain($category->category);
			}
			cache_set($cid, $categories);
		}
	}

	return $categories;
}