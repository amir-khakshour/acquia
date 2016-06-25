<?php

/**
 * Form builder; Configure acquia portfolio settings.
 *
 * @ingroup forms
 */
function ac_portfolio_settings($form, &$form_state) {
 acquia_include('taxonomy');
 acquia_include('options');
 acquia_include('options', 'ac_portfolio');

 $form = array();
 $form['#prefix'] = '<div class="ac-admin">';
 $form['#suffix'] = '</div>';
 acquia_load_resources();
	
  // Default portfolio context
 $form['general'] = array(
   '#type' => 'fieldset',
   '#title' => t('General Settings'),
  );
 
  // Default portfolio Taxonomy
  $form['general']['ac_portfolio_taxonomy_mn'] = array(
   '#type' => 'select',
   '#title' => t('Default vocabolary'),
   '#options' => ac_get_taxonomies_option(),
   '#default_value' => variable_get('ac_portfolio_taxonomy_mn', NULL),
  );
  
	$ops = acquia_image_frame_list();
	add_default_option($ops);
  
  // Default image frame of gallery images
  $form['general']['ac_portfolio_image_frame'] = array(
   '#type' => 'select',
   '#title' => t('Frame style'),
   '#options' => $ops,
   '#default_value' => variable_get('ac_portfolio_image_frame', NULL),
  );
  
	$ops = acquia_image_effects();
	add_default_option($ops);
	$form['general']['ac_portfolio_image_effect'] = array(
		'#type' => 'select',
		'#title' => t('Image Effect'),
		'#description' => t('Apply an Effect to the gallery images on mouse hover.'),
		'#options' => $ops,
		'#default_value' => variable_get('ac_portfolio_image_effect', NULL),
	);
  
  $form['general']['ac_portfolio_thumb_style'] = array(
   '#type' => 'select',
   '#title' => t('Thumbnail view image style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_portfolio_thumb_style', NULL),
  );
	
	$form['general']['ac_portfolio_gallery_style'] = array(
   '#type' => 'select',
   '#title' => t('Gallery view image style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_portfolio_gallery_style', NULL),
  );
  
  $form['general']['ac_portfolio_slideshow_style'] = array(
   '#type' => 'select',
   '#title' => t('Slider view image style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_portfolio_slideshow_style', NULL),
   '#description' => t('leave it blank to use the original image dimension.'),
  );
  
  $form['general']['ac_portfolio_list_style'] = array(
   '#type' => 'select',
   '#title' => t('List view image style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_portfolio_list_style', NULL),
   '#description' => t('leave it blank to use the original image dimension.'),
  );

  $form['general']['ac_portfolio_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('view project link text'),
    '#description' => '',
    '#default_value' => variable_get('ac_portfolio_link_title', 'view project'),
  );
  
  $form['general']['ac_portfolio_nav_index'] = array(
    '#type' => 'textfield',
    '#title' => t('Ente the url of portfolio navigation index'),
    '#description' => t('Leave it blank to exclude index button from portfolio navigation.'),
    '#default_value' => variable_get('ac_portfolio_nav_index', 'portfolio/4-columns'),
  );
  
  $form['general']['ac_portfolio_enabled_share_links'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled share links'),
    '#description' => t('select share links to display on portfolio page.'),
    '#options' => acquia_social_icons(),
    '#default_value' => variable_get('ac_portfolio_enabled_share_links', NULL),
  );
	
//	$form['general']['share_icons'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Related portfolio block'),
//  );
//	
//	$form['general']['related'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Related portfolio block'),
//  );
	
  // This form allows page compression settings to be changed, which can
  // invalidate the page cache, so it needs to be cleared on form submit.
  //$form['#submit'][] = 'acquia_clear_cache_submit';
 return system_settings_form($form);
}