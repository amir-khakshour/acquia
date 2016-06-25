<?php
/**
 * @file Amin DiamondLayers portfolio blocks
 */
function _related_portfolio_admin_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('options', 'ac_portfolio');
	$form = array ();
	$form['#prefix'] = '<div class="ac-admin">';
	$form['#suffix'] = '</div>';
	acquia_load_resources();

	$form['related_works'] = array(
		'#type' => 'fieldset',
		'#title' => t('related works settings'),
		'#tree' => TRUE,
	);

	$form['related_works']['block_title'] = array (
		'#type' => 'textfield',
		'#title' => t('title'),
		'#description' => t ( 'Block Title ; e.g., related works' ),
		'#default_value' => acquia_variable_get('portfolio_related_block_title', 'related works'),
	);

	$form['related_works']['nums'] = array (
		'#type' => 'select',
		'#title' => t('Items'),
		'#description' => t ( 'Number of related Items to display; e.g., 8' ),
		'#default_value' => acquia_variable_get('portfolio_related_nums', 8),
		'#options' => drupal_map_assoc ( range (1, 20) )
	);

	$form['related_works']['cols'] = array (
		'#type' => 'select',
		'#title' => t('columns'),
		'#description' => t ( 'Number of visible related Items to display; e.g., 4' ),
		'#default_value' => acquia_variable_get('portfolio_related_cols', 4),
		'#options' => drupal_map_assoc ( range (1, 20) )
	);

	$form['related_works']['spaced'] = array(
		'#type' => 'checkbox',
		'#title' => t('Spaced Items?'),
		'#default_value' => acquia_variable_get('portfolio_related_spaced', TRUE),
	);

	$form['related_works']['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => acquia_variable_get('portfolio_related_padding', 20),
		'#states' => array(
			'visible' => array(
				':input[name="related_works[spaced]"]' => array('checked' => TRUE),
			),
		),
	);

	$form['related_works']['view'] = array (
		'#type' => 'select',
		'#title' => t('view style'),
		'#description' => t ( 'Select default view style for your related works items.' ),
		'#default_value' => acquia_variable_get('portfolio_related_view', 'simple-sep'),
		'#options' => ac_portfolio_item_view_styles (),
	);

	$form['related_works']['style'] = array (
		'#type' => 'select',
		'#title' => t('related Items image style'),
		'#description' => t ( 'Select <none> to use the original image dimension.' ),
		'#default_value' => acquia_variable_get('portfolio_related_style', 'rectangle-medium'),
		'#options' => image_style_options ()
	);

	$form['related_works']['frame'] = array(
		'#type' => 'select',
		'#title' => t('Image frame'),
		'#description' => t('Select the image frame style from the list.'),
		'#default_value' => acquia_variable_get('portfolio_related_frame', null),
		'#options' => acquia_image_frame_list(),
	);

	$effect = acquia_image_effects();
	unset($effect['overlay']);

	$form['related_works']['effect'] = array(
		'#type' => 'select',
		'#title' => t('Image Effect'),
		'#description' => t('Apply an Effect to the image on mouse hover.'),
		'#options' => $effect,
		'#default_value' => acquia_variable_get('portfolio_related_effect', null),
	);

	$form['related_works']['fullwidth'] = array(
		'#type' => 'checkbox',
		'#title' => t('Full page width block?'),
		'#description' => t ( 'Full page width block?.' ),
		'#default_value' => acquia_variable_get('portfolio_related_fullwidth', TRUE),
	);

	$form['related_works']['nav_pager'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider pager?'),
		'#description' => t ( 'Check it to Display slider pager.' ),
		'#default_value' => acquia_variable_get('portfolio_related_nav_pager', FALSE),
	);

	$form['related_works']['nav_prev_next'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider prev/next navigation?'),
		'#description' => t ( 'Check it to Display Navigation.' ),
		'#default_value' => acquia_variable_get('portfolio_related_nav_prev_next', TRUE),
	);

	$form['related_works']['media'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display media?'),
		'#description' => t ( 'Turn it On to display media.' ),
		'#default_value' => acquia_variable_get('portfolio_related_media', TRUE),
	);

	$form['related_works']['title'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display title?'),
		'#description' => t ( 'Turn it On to display title.' ),
		'#default_value' => acquia_variable_get('portfolio_related_title', TRUE),
	);

	$form['related_works']['tags'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Tags?'),
		'#description' => t ( 'Turn it On to display tags.' ),
		'#default_value' => acquia_variable_get('portfolio_related_tags', TRUE),
	);

	$form['related_works']['date'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Date?'),
		'#description' => t ( 'Turn it On to display date.' ),
		'#default_value' => acquia_variable_get('portfolio_related_date', TRUE),
	);

	$form['related_works']['date_format'] = array (
		'#type' => 'textfield',
		'#title' => t('Date Format?'),
		'#description' => t ( 'You can use PHP date formats ; e.g., M/j/Y' ),
		'#default_value' => acquia_variable_get('portfolio_relatedt_date_format', 'M j, Y'),
	);

	$form['related_works']['proj_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Project Link?'),
		'#description' => t ( 'Turn it On to display Project Link.' ),
		'#default_value' => acquia_variable_get('portfolio_related_proj_link', FALSE),
	);

	$form['related_works']['details_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Details link?'),
		'#description' => t ( 'Turn it On to display Details link.' ),
		'#default_value' => acquia_variable_get('portfolio_related_details_link',FALSE),
	);

	$form['related_works']['excerpt'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display excerpt?'),
		'#description' => t ( 'Turn it On to display excerpt.' ),
		'#default_value' => acquia_variable_get('portfolio_related_excerpt', TRUE),
	);
	$form['submit'] = array (
		'#type' => 'submit',
		'#value' => t('submit'),
	);
	return $form;
}

/**
 * save recent items block settings
 */
function _related_portfolio_admin_form_submit($form, &$form_state) {
	$values = isset($form_state['values']['related_works']) ? $form_state['values']['related_works'] : array();
	foreach ($values as $key => $val) {
		acquia_variable_set('portfolio_related_' . $key, $val);
	}
}


/**
 * @file Amin DiamondLayers recent works blocks
 */
function _recent_portfolio_admin_form($form, &$form_state) {
	acquia_include('options', 'ac_portfolio');

	$form = array ();
	$form['#prefix'] = '<div class="ac-admin">';
	$form['#suffix'] = '</div>';
	acquia_load_resources();

	$form['recent_works'] = array(
		'#type' => 'fieldset',
		'#title' => t('recent works settings'),
		'#tree' => TRUE,
	);

	$form['recent_works']['block_title'] = array (
		'#type' => 'textfield',
		'#title' => t('title'),
		'#description' => t ( 'Block Title ; e.g., recent works' ),
		'#default_value' => acquia_variable_get('portfolio_recent_block_title', 'recent works'),
	);

	$form['recent_works']['date_format'] = array (
		'#type' => 'textfield',
		'#title' => t('Date Format?'),
		'#description' => t ( 'You can use PHP date formats ; e.g., M/j/Y' ),
		'#default_value' => acquia_variable_get('portfolio_recent_date_format', 'M j, Y'),
	);

	$form['recent_works']['nums'] = array (
		'#type' => 'select',
		'#title' => t('Items'),
		'#description' => t ( 'Number of related Items to display; e.g., 8' ),
		'#default_value' => acquia_variable_get('portfolio_recent_nums', 8),
		'#options' => drupal_map_assoc ( range (1, 20) )
	);

	$form['recent_works']['cols'] = array (
		'#type' => 'select',
		'#title' => t('Visible Items'),
		'#description' => t ( 'Number of Columns to show; e.g., 4' ),
		'#default_value' => acquia_variable_get('portfolio_recent_cols', 4),
		'#options' => drupal_map_assoc ( range (1, 20) )
	);

	$form['recent_works']['view'] = array (
		'#type' => 'select',
		'#title' => t('view style'),
		'#description' => t ( 'Select default view style for your recent works items.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_view', 'simple-sep'),
		'#options' => ac_portfolio_item_view_styles (),
	);

	$form['recent_works']['style'] = array (
		'#type' => 'select',
		'#title' => t('Recent Items image style'),
		'#description' => t ( 'Select <none> to use the original image dimension.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_style', 'portfolio-recent'),
		'#options' => image_style_options ()
	);

	$form['recent_works']['spaced'] = array(
		'#type' => 'checkbox',
		'#title' => t('Spaced Items?'),
		'#description' => t ( 'Turn it On to display horizontally spaced.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_spaced', TRUE),
	);

	$form['recent_works']['media'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display media?'),
		'#description' => t ( 'Turn it On to display media.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_media', TRUE),
	);

	$form['recent_works']['title'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display title?'),
		'#description' => t ( 'Turn it On to display title.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_title', TRUE),
	);

	$form['recent_works']['tags'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Tags?'),
		'#description' => t ( 'Turn it On to display tags.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_tags', TRUE),
	);

	$form['recent_works']['date'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Date?'),
		'#description' => t ( 'Turn it On to display date.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_date', TRUE),
	);

	$form['recent_works']['proj_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Project Link?'),
		'#description' => t ( 'Turn it On to display Project Link.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_proj_link', FALSE),
	);

	$form['recent_works']['details_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Details link?'),
		'#description' => t ( 'Turn it On to display Details link.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_details_link',FALSE),
	);

	$form['recent_works']['excerpt'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display excerpt?'),
		'#description' => t ( 'Turn it On to display excerpt.' ),
		'#default_value' => acquia_variable_get('portfolio_recent_excerpt', TRUE),
	);

	$form['submit'] = array (
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * save recent items block settings
 */
function _recent_portfolio_admin_form_submit($form, &$form_state) {
	$values = isset($form_state['values']['recent_works']) ? $form_state['values']['recent_works'] : array();
	foreach ($values as $key => $val) {
		acquia_variable_set('portfolio_recent_' . $key, $val);
	}
}