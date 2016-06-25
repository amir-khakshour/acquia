<?php

/**
 * Form builder; Configure acquia blog settings.
 *
 * @ingroup forms
 */
function ac_blog_settings($form, &$form_state) {
 acquia_include('taxonomy');
 acquia_include('options');
acquia_include('context');
 $form = array();
 $form['#prefix'] = '<div class="ac-admin">';
 $form['#suffix'] = '</div>';
 acquia_load_resources();
	
  // Default blog context
 $form['general'] = array(
   '#type' => 'fieldset',
   '#title' => t('General Settings'),
  );

	$ops = acquia_image_frame_list();
	add_default_option($ops);
  
  // Default image frame of gallery images
  $form['general']['ac_blog_image_frame'] = array(
   '#type' => 'select',
   '#title' => t('Frame style'),
   '#options' => $ops,
   '#default_value' => variable_get('ac_blog_image_frame', NULL),
  );
  
  $form['general']['ac_blog_thumb_style'] = array(
   '#type' => 'select',
   '#title' => t('Blog Image Thumbnail style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_blog_thumb_style', NULL),
  );
	
	$form['general']['ac_blog_preview_style'] = array(
   '#type' => 'select',
   '#title' => t('Blog Image preview style'),
   '#options' => image_style_options(),
   '#default_value' => variable_get('ac_blog_preview_style', NULL),
  );

  //$form['general']['ac_blog_link_title'] = array(
  //  '#type' => 'textfield',
  //  '#title' => t('view project link text'),
  //  '#description' => '',
  //  '#default_value' => variable_get('ac_blog_link_title', 'view project'),
  //);
  //
  //$form['general']['ac_blog_nav_index'] = array(
  //  '#type' => 'textfield',
  //  '#title' => t('Ente the url of blog navigation index'),
  //  '#description' => t('Leave it blank to exclude index button from blog navigation.'),
  //  '#default_value' => variable_get('ac_blog_nav_index', 'blog/4-columns'),
  //);
    
  $form['general']['ac_blog_about_author'] = array(
   '#type' => 'checkbox',
   '#title' => t('Display about author block?'),
   '#default_value' => variable_get('ac_blog_preview_style', TRUE),
  );
	
  $form['general']['ac_blog_share_links'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled share links'),
    '#description' => t('select share links to display on blog page.'),
    '#options' => acquia_social_icons(),
    '#default_value' => variable_get('ac_blog_share_links', array()),
  );

  // This form allows page compression settings to be changed, which can
  // invalidate the page cache, so it needs to be cleared on form submit.
 //$form['#submit'][] = 'acquia_clear_cache_submit';
 return system_settings_form($form);
}

/**
 * admin DiamondLayers related news block
 */
function _related_news_admin_form($form, &$form_state) {
	acquia_include('options', 'ac_blog');
	$form = array ();
  $form['#prefix'] = '<div class="ac-admin">';
  $form['#suffix'] = '</div>';
	acquia_load_resources();
	
  $form['related_news'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Related news settings'),
  	'#tree' => TRUE,
  );

	$form['related_news']['view'] = array (
		'#type' => 'select',
		'#title' => t('Items'),
		'#description' => t ( 'Number of related Items to display; e.g., 8' ),
		'#default_value' => acquia_variable_get('related_news_view', 'simple'),
		'#options' => ac_blog_related_views(),
	);
	
	$form['related_news']['nums'] = array (
		'#type' => 'select',
		'#title' => t('Items'),
		'#description' => t ( 'Number of related Items to display; e.g., 8' ),
		'#default_value' => acquia_variable_get('related_news_nums', 8),
		'#options' => drupal_map_assoc ( range (1, 20) ) 
	);
	
	$form['related_news']['cols'] = array (
		'#type' => 'select',
		'#title' => t('columns'),
		'#description' => t ( 'Number of visible related Items; e.g., 4' ),
		'#default_value' => acquia_variable_get('related_news_cols', 4),
		'#options' => drupal_map_assoc ( range (1, 20) ) 
	);

	$form['related_news']['style'] = array (
		'#type' => 'select',
		'#title' => t('image style'),
		'#description' => t ( 'Select <none> to use the original image dimension.' ),
		'#default_value' => acquia_variable_get('related_news_style', 'rectangle-medium'),
		'#options' => image_style_options () 
	);

	$form['related_news']['spaced'] = array(
		'#type' => 'checkbox',
		'#title' => t('Spaced Items?'),
		'#description' => t ( 'Turn it On to display horizontally spaced.' ),
		'#default_value' => acquia_variable_get('related_news_spaced', TRUE),
	);
	
	$form['related_news']['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => acquia_variable_get('related_news_padding', TRUE),
		'#states' => array(
			'visible' => array(
				':input[name="spaced"]' => array('checked' => TRUE),
			),
		),
	);
	
	$form['related_news']['media'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display media?'),
		'#description' => t ( 'Turn it On to display media.' ),
		'#default_value' => acquia_variable_get('related_news_media', TRUE),
	);
	
	$form['related_news']['author'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display author?'),
		'#description' => t ( 'Turn it On to display author.' ),
		'#default_value' => acquia_variable_get('related_news_author', TRUE),
	);
	
	$form['related_news']['title'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display title?'),
		'#description' => t ( 'Turn it On to display title.' ),
		'#default_value' => acquia_variable_get('related_news_title', TRUE),
	);
	
	$form['related_news']['tags'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Tags?'),
		'#description' => t ( 'Turn it On to display tags.' ),
		'#default_value' => acquia_variable_get('related_news_tags', TRUE),
	);
	
	$form['related_news']['date'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Date?'),
		'#description' => t ( 'Turn it On to display date.' ),
		'#default_value' => acquia_variable_get('related_news_date', TRUE),
	);
	
	$form['submit'] = array (
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	return $form;
}

/**
 * submit handler for _related_news_admin_form()
 */
function _related_news_admin_form_submit($form, &$form_state) {
	$values = isset($form_state['values']['related_news']) ? $form_state['values']['related_news'] : array();
	foreach ($values as $key => $val) {
		acquia_variable_set('related_news_' . $key, $val);
	}
}