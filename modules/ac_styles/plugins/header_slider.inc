<?php

/**
 * style plugin for ac_style module.
 *
 * @todo move to ac_slider module
 */

$plugin = array(
  'label' => t('Header Slider'),
  'handler' => array(
	'class' => 'header_slider',
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
class header_slider extends acquia_styles {
  /**
   *  style form
   */
  public function style_form($settings = array()) {

	acquia_include('options');
	acquia_include('utility', 'ac_slider');

	$settings+= array(
	  'parents' => array(''),
	);
	if (count($settings['parents'])) {
	  acquia_include('utility');
	  $active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array('hs-enabled') );
	  $active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
	}else {
	  $active_trail = 'hs-enabled';
	}

	$values = isset($this->values['header_slider']) && is_array($this->values['header_slider']) ? $this->values['header_slider'] : array();

	$values += array(
	  'hs-enabled' => 0,
	  'slider' => acquia_variable_get('header_slider'),
	  'bg_fallback' => 0,
	  'bg_fallback_style' => '',
	  'slid' => '',
	);

	$form['hs-enabled'] = array(
	  '#type' => 'checkbox',
	  '#title' => t('Customize Header Slider?'),
	  '#default_value' => $values['hs-enabled'],
	  '#tree' => true,
	  '#parents' => array_merge($settings['parents'], array('hs-enabled')),
	);

	$form['header_slider'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Header slider settings'),
	  '#collapsible' => TRUE,
	  '#states' => array(
		'visible' => array(
		  ':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
		),
	  ),
	  //'#tree' => true,
	  //'#parents' => $settings['parents'],
	);
	$form['header_slider']['bg_fallback'] = array(
	  '#type' => 'media',
	  '#title' => t('Slider Fallback Image'),
	  '#description' => t('The image should be between 1600px - 2000px wide and have a minimum height of 475px for best results.'),
	  '#default_value' => acquia_get_media_field($values['bg_fallback']),
	  '#media_options' => array(
		'global' => array(
		  'types' => array('image'),
		  'file_directory' => acquia_variable_get('public_path', 'acquia') . '/masthead/',
		),
	  ),
	);

	$form['header_slider']['bg_fallback_style'] = array(
	  '#type' => 'select',
	  '#title' => t('Slider Fallback Style'),
	  '#description' => t('Apply an image style to the Slider Fallback Image.'),
	  '#options' => image_style_options(),
	  '#default_value' => $values['bg_fallback_style'],
	);

	$sliders = get_all_sliders();
	if (empty($sliders)) {
	  $form['header_slider']['no_slider_hint'] = array(
		'#markup' => t('No slider is created. please add one slider from !link!', array('!link' => url(SLIDER_LIST_PATH, array('absolute' => TRUE)))),
		'#prefix' => '<div class="message warning">',
		'#suffix' => '</div>',
	  );
	}else{
	  $opts = array();
	  $slider_types = get_slider_types();
	  foreach ($sliders as $slider) {
		$opts[$slider->slid] = t($slider_types[$slider->type] .' - ' . $slider->title);
	  }
	  $form['header_slider']['slid'] = array(
		'#type' => 'select',
		'#title' => t('Select Slider'),
		'#description' => t('Select a slider for your header from the list.'),
		'#default_value' => $values['slid'],
		'#options' => $opts,
	  );
	}

	return $form;
  }
}


/**
 * Implements hook_plugins_PLUGIN_theme_registry_alter().
 */
function ac_styles_plugins_header_slider_theme_registry_alter(&$registry, $file) {
  if ($file == false) {
	return false;
  }

  $funcs_arr = $registry['page']['preprocess functions'];
  $pos = array_search('contextual_preprocess', $funcs_arr);
  $portion = array_splice($funcs_arr , $pos);
  $portion = array_merge(array('ac_styles_plugins_header_slider_preprocess_page'), $portion);

  $registry['page']['includes'][] = $file;
  $registry['page']['preprocess functions'] = array_merge($funcs_arr, $portion);
}

/**
 * Implements hook_plugins_PLUGIN_preproces_region().
 */
function ac_styles_plugins_header_slider_preprocess_page(&$vars) {
  acquia_include('utility', 'ac_styles', 'includes');
  acquia_include('content');

  // Get styles from merging context and node meta
  $ac_styles = ac_styles_merge_nodemeta_by_context('ac_style');
  $header_slider = isset($ac_styles['header_slider']) ? $ac_styles['header_slider'] : array();
  if (isset($header_slider['hs-enabled']) && $header_slider['hs-enabled'] !=0) {
	acquia_include('block');
	$block = block_load('ac_slider', $header_slider['slid']);
	acquia_prepare_block_display($block);

	$block = array($block);
	$block_array = _block_render_blocks($block);

	foreach($block_array as &$_block){
	  $_block->subject = '';
	}
	$vars['page']['slider'][] = _block_get_renderable_array($block_array);
	// generate fallback image

	if (isset($vars['bg_fallback']) && $vars['bg_fallback'] !=0){
//	  $vars['page']['slider'][] = array('#markup' => theme('ac_styles_bg_fallback_slider', $header_slider));
	  $vars['classes_array'][] = 'ac-bg-fallback-enabled';
	}
  }
}

