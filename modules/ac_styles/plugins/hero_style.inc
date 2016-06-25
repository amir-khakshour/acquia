<?php

/**
 * style plugin for ac_style module.
 *
 * Calculate sum of two numbers.
 */

$plugin = array(
	'label' => t('Hero style'),
	'handler' => array(
		'class' => 'hero_style',
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
class hero_style extends acquia_styles {
	/**
	 *  style form
	 */
	public function style_form($settings = array()) {

		acquia_include('options');
		acquia_include('utility');

		$settings+= array(
			'parents' => array(''),
		);
		if (count($settings['parents'])) {
			$active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array('enabled') );
			$active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
		}else {
			$active_trail = 'enabled';
		}

		$values = isset($this->values['hero_style']) && is_array($this->values['hero_style']) ? $this->values['hero_style'] : array();

		$values += acquia_theme_get_settings('hero_style', array());

		$values += array(
			'enabled' => 0,
			'disabled' => 0,
			'style' => 'fancy',
			'bg' => 0,
			'bg_style' => '',
			'bg_repeat' => acquia_variable_get('hero_bg_repeat'),
			'bg_type' => 'light',
			'height' => '',
			'title_hide' => acquia_variable_get('hero_title_hide'),
			'title' => '',
			'subtitle' => '',
			'breadcrumb_style' => 'fancy',
		);

		$form = array();

		$form['enabled'] = array(
			'#type' => 'checkbox',
			'#title' => t('Customize hero region?'),
			'#default_value' => $values['enabled'],
			'#tree' => true,
			'#parents' => array_merge($settings['parents'], array('enabled')),
		);

		$form['hero_style'] = array(
			'#type' => 'fieldset',
			'#title' => t('Hero region settings'),
			'#collapsible' => TRUE,
			'#states' => array(
				'visible' => array(
					':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
			),
			//'#tree' => true,
			//'#parents' => $settings['parents'],
		);
		$form['hero_style']['disabled'] = array(
			'#type' => 'checkbox',
			'#title' => t('Disable hero region?'),
			'#default_value' => $values['disabled'],
			'#description' => t('make checkbox checked, if you want to remove hero region from your page.'),
		);

		$form['hero_style']['style'] = array(
			'#type' => 'select',
			'#title' => t('Hero region style'),
			'#description' => t('Choose the hero region style.'),
			'#options' => array(
				'fancy' => t('Fancy - Centered content'),
				'simple' => t('Simple - Corner aligned content'),
			),
			'#default_value' => $values['style'],
		);

		$form['hero_style']['bg_type'] = array(
			'#type' => 'select',
			'#title' => t('Background type'),
			'#description' => t('what color range is your background image?'),
			'#options' => array(
				'dark' => t('Dark'),
				'light' => t('Light'),
			),
			'#default_value' => $values['bg_type'],
		);

		$form['hero_style']['bg'] = array(
			'#type' => 'media',
			'#title' => t('Background Image'),
			'#description' => t('The image should be between 1600px - 2000px wide and have a minimum height of 475px for best results.'),
			'#default_value' => acquia_get_media_field($values['bg']),
			'#media_options' => array(
				'global' => array(
					'types' => array('image'),
					'file_directory' => acquia_variable_get('public_path', 'acquia') . '/masthead/',
				),
			),
		);

		$form['hero_style']['bg_style'] = array(
			'#type' => 'select',
			'#title' => t('Background image Style'),
			'#description' => t('Apply an image style to the image.'),
			'#options' => image_style_options(),
			'#default_value' => $values['bg_style'],
		);

		$form['hero_style']['bg_repeat'] = array(
			'#type' => 'select',
			'#title' => t('Background Repeat'),
			'#default_value' => $values['bg_repeat'],
			'#options' => acquia_css_background_repeat(),
		);

		$form['hero_style']['height'] = array(
			'#type' => 'textfield',
			'#title' => t('Height'),
			'#description' => t('How tall do you want your hero region? Don\'t include "px" in the string. e.g. 350 This only applies when you are using an image.'),
			'#default_value' => $values['height'],
		);

		$form['hero_style']['title_hide'] = array(
			'#type' => 'checkbox',
			'#title' => t('Disable the display of page title in hero?'),
			'#default_value' => $values['title_hide'],
			'#description' => t('make checkbox checked, if you want to hide the page title from your hero region.'),
		);

		$form['hero_style']['title'] = array(
			'#type' => 'textfield',
			'#title' => t('Title'),
			'#description' => t('Here you can change the Hero region title. leave it blank to set it as the default node title.'),
			'#default_value' => $values['title'],
		);

		$form['hero_style']['subtitle'] = array(
			'#type' => 'textfield',
			'#title' => t('Subtitle'),
			'#description' => t('Subtitle will be placed under the hero region title.'),
			'#default_value' => $values['subtitle'],
		);

		$form['hero_style']['breadcrumb_style'] = array(
			'#type' => 'select',
			'#title' => t('Breadcrumb style'),
			'#description' => t('You can override the global breadcrumb style for this page.'),
			'#default_value' => $values['breadcrumb_style'],
			'#options' => acquia_breadcrumb_styles(),
		);

		return $form;
	}


}

/**
 * Implements hook_plugins_PLUGIN_theme_registry_alter().
 */
function ac_styles_plugins_hero_style_theme_registry_alter(&$registry, $file) {
	if ($file == false) {
		return false;
	}

	if (isset($registry['ac_blocks_page_title'])) {
		$registry['ac_blocks_page_title']['preprocess functions'][] = 'ac_styles_plugins_preprocess_ac_hero_title_block';
		$registry['ac_blocks_page_title']['includes'][] = $file;
	}

	$funcs_arr = $registry['page']['preprocess functions'];
	$pos = array_search('contextual_preprocess', $funcs_arr);
	$portion = array_splice($funcs_arr , $pos);
	$portion = array_merge(array('ac_styles_plugins_hero_style_preprocess_page'), $portion);

	$registry['page']['includes'][] = $file;
	$registry['page']['preprocess functions'] = array_merge($funcs_arr, $portion);

}

/**
 * Implements hook_plugins_PLUGIN_preproces_region().
 */
function ac_styles_plugins_hero_style_preprocess_page(&$vars) {
	acquia_include('utility', 'ac_styles', 'includes');
	acquia_include('content');

	// Get styles from merging context and node meta
	$hero_styles = ac_styles_merge_nodemeta_by_context('ac_style');
	$hero_styles = isset($hero_styles['hero_style']) ? $hero_styles['hero_style'] : array();
	if (isset($hero_styles['disabled']) && $hero_styles['disabled']) {
		$vars['page']['highlighted'] = array();
	}
	else if (isset($hero_styles['enabled']) && $hero_styles['enabled'] !=0) {
		$vars['hero_attrs'] = array();
		$vars['hero_attrs']['class'] = array('l-hero');
		$vars['hero_attrs']['style'] = array();

		// Hero style
		$hero_styles['style'] = isset($hero_styles['style']) &&
		!empty($hero_styles['style']) ? $hero_styles['style'] : acquia_variable_get('hero_style');
		$vars['hero_attrs']['class'][] = ' l-hero-' .$hero_styles['style'];

		$hero_styles['bg_type'] = isset($hero_styles['bg_type']) &&
		!empty($hero_styles['bg_type']) ? $hero_styles['bg_type'] : acquia_variable_get('hero_bg_type');
		$vars['hero_attrs']['class'][] = ' l-hero-' .$hero_styles['bg_type'];

		// Background Image
		if (isset($hero_styles['bg']) && !empty($hero_styles['bg'])) {
			if ($hero_styles['bg']> 0) {
				$vars['hero_attrs']['class'][] = 'custom-bg';
				if (isset($hero_styles['bg_style']) && !empty($hero_styles['bg_style'])) {
					$bg = image_style_url($hero_styles['bg_style'], file_load($hero_styles['bg'])->uri);
				}else{
					$bg = file_create_url(file_load($hero_styles['bg'])->uri);
				}

				$vars['hero_attrs']['style']['background-image'] = "url('" .$bg. "')";
				// background repeat
				if ( isset($hero_styles['bg_repeat']) && !empty($hero_styles['bg_repeat']) ) {
					if ($hero_styles['bg_repeat'] == 'stretch') {
						$vars['hero_attrs']['class'][] = 'ac-full-stretch';
					}else {
						$vars['hero_attrs']['style']['background-repeat'] = $hero_styles['bg_repeat'];
					}
				}

			}

			// Height
			if (isset($hero_styles['height']) && !empty($hero_styles['height'])) {
				$vars['hero_attrs']['class'][] = 'custom-height';

				$hero_styles['height'] = preg_match('/^([0-9])*/i', $hero_styles['height'], $matches);
				$hero_styles['height'] = !empty($matches[0]) ?  $matches[0] . 'px' : '';
				$vars['hero_attrs']['style']['height'] = $hero_styles['height'];
				$vars['hero_attrs']['data-height'] = $hero_styles['height'];
			}
		}else{
			$vars['hero_attrs']['class'][] = 'no-custom-bg';
		}
		if (isset($hero_styles['breadcrumb_style'])) {
			$vars['hero_attrs']['class'][] = 'l-hero-breadcrumb-' .$hero_styles['breadcrumb_style'];
		}

		$vars['hero_attrs']['class'] = array_filter($vars['hero_attrs']['class'], 'strlen');
		$vars['hero_attrs']['style'] = acquia_style_arr_to_tag($vars['hero_attrs']['style']);

		// hide main title in content  region
		if (isset($hero_styles['title_hide']) && $hero_styles['title_hide'] != 0) {
			$vars['classes_array'][] = 'ac-title-in-content';
		}
		$vars['hero_attrs']['class'] = implode(' ', $vars['hero_attrs']['class']);
	}
	else{
		$theme_hero_style = (array)acquia_theme_get_settings('hero_style');
		$theme_hero_style+= array(
			'style' => 'fancy',
			'bg_type' => 'light',
			'breadcrumb_style' => 'fancy',
		);

		$vars['hero_attrs'] = array('class' => array('l-hero', 'l-hero-' .$theme_hero_style['style']));
		$vars['hero_attrs']['class'][] = 'l-hero-' .$theme_hero_style['bg_type'];
		$vars['hero_attrs']['class'][] = 'l-hero-breadcrumb-' .$theme_hero_style['breadcrumb_style'];
		unset($vars['ac_hero_title_hide']);
	}

}

/**
 * Implements hook_plugins_PLUGIN_preproces_region().
 */
function ac_styles_plugins_preprocess_ac_hero_title_block(&$vars) {
	// clearfix
	acquia_include('utility', 'ac_styles', 'includes');
	$hero_styles = ac_styles_merge_nodemeta_by_context('ac_style');
	$hero_styles = isset($hero_styles['hero_style']) ? $hero_styles['hero_style'] : array();

	if (isset($hero_styles['enabled']) && $hero_styles['enabled'] !=0) {
		if (isset($hero_styles['title']) && !empty($hero_styles['title'])) {
			$vars['page_title'] = $hero_styles['title'];
		}

		if (isset($hero_styles['style']) && $hero_styles['style'] == 'fancy'
			&& isset($hero_styles['bg']['fid']) && $hero_styles['bg']['fid'] !=0) {
			$vars['fancy'] = TRUE;
		}

		if (isset($hero_styles['subtitle']) && !empty($hero_styles['subtitle'])) {
			$vars['page_subtitle'] = $hero_styles['subtitle'];
		}
	}
}

