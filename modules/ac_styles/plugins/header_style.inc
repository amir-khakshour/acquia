<?php

/**
 * style plugin for ac_style module.
 *
 * @todo move to ac_slider module
 */

$plugin = array(
	'label' => t('Header style'),
	'handler' => array(
		'class' => 'header_style',
	),
);

/**
 * @file
 * Contains the unformatted summary style plugin.
 */

/**
 * The default style plugin for Hero section.
 *
 * @ingroup views_style_plugins
 */
class header_style extends acquia_styles {
	/**
	 *  style form
	 */
	public function style_form($settings = array()) {

		acquia_include('options');

		$settings+= array(
			'parents' => array(''),
		);
		if (count($settings['parents'])) {
			acquia_include('utility');
			$active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array('header-enabled') );
			$active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
		}else {
			$active_trail = 'header-enabled';
		}

		$values = isset($this->values['header_style']) && is_array($this->values['header_style']) ? $this->values['header_style'] : array();

		$values += array(
			'header-enabled' => 0,
			'transparent_header' => FALSE,
			'bg_fallback' => array(),
			'bg_fallback_style' => '',
			'slid' => '',
			'tr_bg_type' => 'light',
			'tr_depth' => 'full',
			'header_layout' => '',
			'main_menu_style' => '',
			'boxed_page' => FALSE,
		);

		$form['header-enabled'] = array(
			'#type' => 'checkbox',
			'#title' => t('Customize Header?'),
			'#default_value' => $values['header-enabled'],
			'#tree' => true,
			'#parents' => array_merge($settings['parents'], array('header-enabled')),
		);

		$form['header_style'] = array(
			'#type' => 'fieldset',
			'#title' => t('Header style settings'),
			'#collapsible' => TRUE,
			'#states' => array(
				'visible' => array(
					':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
			),
			//'#tree' => true,
			//'#parents' => $settings['parents'],
		);

		$form['header_style']['transparent_header'] = array(
			'#type' => 'checkbox',
			'#title' => t('Enable Trasparent header on hero?'),
			'#default_value' => $values['transparent_header'],
			'#tree' => true,
			'#parents' => array_merge($settings['parents'], array('transparent_header')),
		);

		$form['header_style']['tr_bg_type'] = array(
			'#type' => 'select',
			'#title' => t('Transparent header color type'),
			'#default_value' => $values['tr_bg_type'],
			'#options' => array('dark' => t('Dark'), 'light' => t('Light')),
			'#tree' => true,
			'#parents' => array_merge($settings['parents'], array('tr_bg_type')),
		);

		$form['header_style']['tr_depth'] = array(
			'#type' => 'select',
			'#title' => t('Transparency depth'),
			'#default_value' => $values['tr_depth'],
			'#options' => array('full' => t('full - transparent'), 'semi' => t('Semi transparent - Gradient'), 'semi-soft' => t('Semi transparent - solid')),
			'#tree' => true,
			'#parents' => array_merge($settings['parents'], array('tr_depth')),
		);

		// Only for demo website
		if (acquia_variable_get('demo_site')) {
			$form['header_style']['boxed_page'] = array(
				'#type' => 'checkbox',
				'#title' => t('Boxed layout?'),
				'#default_value' => $values['boxed_page'],
				'#parents' => array_merge($settings['parents'], array('boxed_page')),
			);
			$form['header_style']['header_layout'] = array(
				'#type' => 'select',
				'#options' => array_merge(array('' => t('Theme Default')), acquia_header_layouts()),
				'#title' => t('Choose a header layout'),
				'#default_value' => $values['header_layout'],
				'#parents' => array_merge($settings['parents'], array('header_layout')),
			);
			$form['header_style']['main_menu_style'] = array(
				'#type' => 'select',
				'#title' => t('Main menu style'),
				'#description' => t('Select a style for your main menu navigation.'),
				'#default_value' => $values['main_menu_style'],
				'#options' => array_merge(array('' => t('Theme Default')), acquia_menu_types()),
				'#parents' => array_merge($settings['parents'], array('main_menu_style')),
			);
		}

		return $form;
	}
}


/**
 * Implements hook_plugins_PLUGIN_theme_registry_alter().
 */
function ac_styles_plugins_header_style_theme_registry_alter(&$registry, $file) {
	if ($file == false) {
		return false;
	}
	$registry['html']['includes'][] = $file;
	$registry['html']['preprocess functions'][] = 'ac_styles_plugins_header_style_preprocess_html';

	// Only for demo website
	if (acquia_variable_get('demo_site')) {
		$registry['page']['includes'][] = $file;
		$registry['page']['preprocess functions'][] = 'ac_styles_plugins_header_style_preprocess_page';
	}
}

/**
 * Implements hook_plugins_PLUGIN_preproces_html().
 */
function ac_styles_plugins_header_style_preprocess_html(&$vars) {
	acquia_include('utility', 'ac_styles', 'includes');
	acquia_include('content');

	// Get styles from merging context and node meta
	$ac_styles = ac_styles_merge_nodemeta_by_context('ac_style');
	$header_style = isset($ac_styles['header_style']) ? $ac_styles['header_style'] : array();
	if (isset($header_style['transparent_header']) && $header_style['transparent_header'] !=0) {
		$vars['classes_array'][] = 'ac-transparent-header';
		$vars['classes_array'][] = $header_style['tr_bg_type'] == 'light' ? 'light-header' : 'dark-header';
		$vars['classes_array'][] = 'ac-transparent-depth-' . $header_style['tr_depth'];
	}

	if (acquia_variable_get('demo_site')) {
		if (isset($header_style['header_layout']) && !empty($header_style['header_layout'])) {
			$vars['attributes_array']['class'][] = 'header-l-' .$header_style['header_layout'];
		}elseif(!module_exists('ac_demo')){
			$vars['attributes_array']['class'][] = 'header-l-' .acquia_theme_get_settings('header_layout', 'left');
		}else{
			acquia_t_include('utility');
			$vars['attributes_array']['class'][] = 'header-l-' .acquia_t_get_skin_header_layout();
		}

		if (isset($header_style['boxed_page']) && $header_style['boxed_page']) {
			$vars['attributes_array']['class'][] = 'ac-boxed-layout';
		}
	}else{
		$vars['attributes_array']['class'][] = 'header-l-' .acquia_theme_get_settings('header_layout', 'left');
	}

}

/**
 * Implements hook_plugins_PLUGIN_preproces_html().
 */
function ac_styles_plugins_header_style_preprocess_page(&$vars) {

	acquia_include('utility', 'ac_styles', 'includes');
	acquia_include('content');

	// Get styles from merging context and node meta
	$ac_styles = ac_styles_merge_nodemeta_by_context('ac_style');
	$header_style = isset($ac_styles['header_style']) ? $ac_styles['header_style'] : array();

	if (isset($header_style['header_layout']) && !empty($header_style['header_layout'])){
		$vars['h_layout'] = $header_style['header_layout'];
		if ($header_style['header_layout'] == 'classic' && acquia_theme_get_settings('header_content', '') != ''){
			$vars['header_content'] = acquia_theme_get_settings('header_content', '');
		}
	}
//
//	if ($vars['h_layout'] == 'classic' && acquia_theme_get_settings('header_content', '') != '') {
//		$vars['header_content'] = acquia_theme_get_settings('header_content', '');
//	}

}

