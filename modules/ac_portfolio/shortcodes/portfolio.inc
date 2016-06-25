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

function ac_portfolio_portfolio_shortcode() {
	return array(
		'ac_portfolio' => array(
			'title' => t('portfolio'),
			'description' => t('Outputs portfolio items'),
			'form callback' => 'ac_shortcode_ac_portfolio_form',
			'values process callback' => 'ac_shortcode_ac_portfolio_preprocess',
			'process callback' => 'ac_shortcode_ac_portfolio_process',
		),
		'ac_portfolio_tags' => array(
			'title' => t('portfolio tags'),
			'description' => t('Outputs portfolio tags'),
			'form callback' => 'ac_shortcode_ac_portfolio_tags_form',
			'values process callback' => 'ac_shortcode_ac_portfolio_tags_preprocess',
			'process callback' => 'ac_shortcode_ac_portfolio_tags_process',
		),
	);
}

/**
 * Implements edit form of {{ac_portfolio_tags}} shortcode
 */
function ac_shortcode_ac_portfolio_tags_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');
	acquia_include('options', 'ac_portfolio');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	/** Global shortcode elements **/
	$form['view'] = array(
		'#type' => 'select',
		'#title' => t('view type'),
		'#description' => t('select a view type from the list to render the tags.'),
		'#options' => ac_portfolio_tags_view(),
		'#default_value' => isset($values['view']) ? $values['view'] : '',
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
 * Process {{ac_portfolio_tags}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_portfolio_tags_preprocess(&$values) {

}

/**
 * process {{ac_portfolio_tags}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_portfolio_tags_process($attrs, $text = null, $shortcode = '') {
	$_attrs = ac_shortcode_attrs(array(
		'view' => 'list',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$vars = array();
	if ($_attrs['view'] != 'tagclouds') {
		acquia_include('utility', 'ac_portfolio');
		$vars['tags'] = ac_portfolio_get_all_tags();
	}

	$vars['vocabulary'] = AC_PORTFOLIO_TAX_MN;
	$block  = theme('acquia_tags_view_' . $_attrs['view'], $vars);
	return $block;
}

/**
 * Implements edit form of {{ac_portfolio}} shortcode
 */
function ac_shortcode_ac_portfolio_form($form, &$form_state) {
	acquia_include('options');
	acquia_include('fields');
	acquia_include('options', 'ac_portfolio');

	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['id'] = array (
		'#type' => 'textfield',
		'#title' => t('ID'),
		'#description' => '',
		'#default_value' => isset($values['id']) ? $values['id'] : uniqid('p-items-'),
	);

	$form['appearance'] = array (
		'#type' => 'select',
		'#title' => t('Appearance'),
		'#description' => '',
		'#default_value' => isset($values['appearance']) ? $values['appearance'] : acquia_variable_get('portfolio_blocks_appearance', 'masonry'),
		'#options' => ac_portfolio_appearance(),
	);

	// auto_scroll
	$form['gplus_effect'] = array (
		'#type' => 'select',
		'#title' => t('Album effect?'),
		'#description' => t ( 'which effect you want to use for revealing the images (note CSS3 browsers only).' ),
		'#options' => ac_portfolio_gplus_effects(),
		'#default_value' => isset($values['gplus_effect']) ? $values['gplus_effect'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'multigrid'),
			),
		),
	);

	$form['gplus_height'] = array (
		'#type' => 'textfield',
		'#title' => t('Row target height (px)'),
		'#description' => t('The ideal height you want your row to be.'),
		'#default_value' => isset($values['gplus_height']) ? $values['gplus_height'] : 350,
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'multigrid'),
			),
		),
	);

	// auto_scroll
	$form['auto_scroll'] = array (
		'#type' => 'checkbox',
		'#title' => t('auto scroll?'),
		'#description' => t ( 'Check it to enabled auto scrolling.' ),
		'#default_value' => isset($values['auto_scroll']) && $values['auto_scroll'] == 'true' ? TRUE : FALSE,
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'scroller'),
			),
		),
	);

	$form['nav_pager'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider pager?'),
		'#description' => t ( 'Check it to Display slider pager.' ),
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'scroller'),
			),
		),
	);
	if (isset($values['nav_pager'])) {
		$form['nav_pager']['#default_value'] = $values['nav_pager'] == 'false' ? FALSE : TRUE;
	}else {
		$form['nav_pager']['#default_value'] = acquia_variable_get('portfolio_blocks_nav_pager', TRUE);
	}

	$form['nav_prev_next'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider prev/next navigation?'),
		'#description' => t ( 'Check it to Display Navigation.' ),
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'scroller'),
			),
		),
	);
	if (isset($values['nav_prev_next'])) {
		$form['nav_prev_next']['#default_value'] = $values['nav_prev_next'] == 'false' ? FALSE : TRUE;
	}else {
		$form['nav_prev_next']['#default_value'] = acquia_variable_get('portfolio_blocks_prev_next', TRUE);
	}

	// Thumb of appreance
	$form['thumb'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable thumbnails?'),
		'#states' => array(
			'visible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);
	if (isset($values['thumb'])) {
		$form['thumb']['#default_value'] = $values['thumb'] == 'true' ? TRUE : FALSE;
	}else {
		$form['thumb']['#default_value'] = acquia_variable_get('portfolio_blocks_thumb', FALSE);
	}

	$form['total'] = array (
		'#type' => 'textfield',
		'#title' => t('Total Number of Items'),
		'#description' => t ( 'Number of portoflio items to extract from database. Enter -1 to extract all portoflio items.' ),
		'#default_value' => isset($values['total']) ? $values['total'] : acquia_variable_get('portfolio_blocks_total', -1),
	);

	$form['pager'] = array (
		'#type' => 'select',
		'#title' => t('Pager type'),
		'#description' => t ( 'Number of items in each page. Enter -1 to disable pager view.' ),
		'#default_value' => isset($values['pager']) ? $values['pager'] : acquia_variable_get('portfolio_blocks_pager', 'simple'),
		'#options' => array('ajax' => t('Ajax paginator'), 'simple' => t('Simple paginator')),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
			'disabled' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$form['ajax_type'] = array (
		'#type' => 'select',
		'#title' => t('load event'),
		'#description' => t ( 'how load extra items?' ),
		'#default_value' => isset($values['ajax_type']) ? $values['ajax_type'] : acquia_variable_get('portfolio_blocks_ajax_type', 'click'),
		'#options' => array('click' => t('click on load more button'), 'scroll' => t('when scrolling at the end of page')),
		'#states' => array(
			'visible' => array(
				':input[name="pager"]' => array('value' => 'ajax'),
			),
			'enabled' => array(
				':input[name="pager"]' => array('value' => 'ajax'),
			),
		),
	);

	$form['num_per_page'] = array (
		'#type' => 'textfield',
		'#title' => t('Pager items'),
		'#description' => t ( 'Number of items in each page. Enter -1 to disable pager view.' ),
		'#default_value' => isset($values['num_per_page']) ? $values['num_per_page'] : acquia_variable_get('portfolio_blocks_num_per_page', 12),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
			'disabled' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$form['spaced'] = array(
		'#type' => 'checkbox',
		'#title' => t('Spaced Items?'),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);
	if (isset($values['spaced'])) {
		$form['spaced']['#default_value'] = $values['spaced'] == 'true' ? TRUE : FALSE;
	}else {
		$form['spaced']['#default_value'] = acquia_variable_get('portfolio_blocks_spaced', TRUE);
	}
	$form['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => isset($values['padding']) ? $values['padding'] : acquia_variable_get('portfolio_blocks_padding', 20),
		'#states' => array(
			'visible' => array(
				':input[name="spaced"]' => array('checked' => TRUE),
			),
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$form['cols'] = array (
		'#type' => 'select',
		'#title' => t('Columns'),
		'#description' => t ( 'Number of Columns to show. in slider appearance type this is the number of items visible in each slides loop; e.g., 4' ),
		'#default_value' => isset($values['cols']) ? $values['cols'] : acquia_variable_get('portfolio_blocks_cols', 4),
		'#options' => drupal_map_assoc ( range (1, 6) ),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$ops = ac_portfolio_item_view_styles();
	add_default_option($ops);
	$form['view'] = array (
		'#type' => 'select',
		'#title' => t('Items view type'),
		'#description' => t ( 'Select default view type for your portoflio items.' ),
		'#default_value' => isset($values['view']) ? $values['view'] : acquia_variable_get('portfolio_blocks_view', 'simple-sep'),
		'#options' => $ops,
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$ops = acquia_image_frame_list();
	add_default_option($ops);
	$form['frame'] = array(
		'#type' => 'select',
		'#title' => t('Image frame'),
		'#description' => t('Select the image frame style from the list.'),
		'#default_value' => isset($values['frame']) ? $values['frame'] : 'none',
		'#options' => $ops,
	);

	$form['width'] = array (
		'#type' => 'select',
		'#title' => t('Items dimension'),
		'#description' => '',
		'#default_value' => isset($values['width']) ? $values['width'] : acquia_variable_get('portfolio_blocks_width', 'equal'),
		'#options' => array('pre' => t('Preserve original item width'), 'equal' => t('Make Items same width'), 'equal_height' => t('Make Items same height (for multigrid appearance)')),
	);

	$form['style'] = array (
		'#type' => 'select',
		'#title' => t('image style'),
		'#description' => t ( 'Select <none> to use the original image dimension.' ),
		'#default_value' => isset($values['style']) ? $values['style'] : acquia_variable_get('portfolio_blocks_style', 'portfolio-recent'),
		'#options' => image_style_options (),
	);

	$effect = acquia_image_effects();
	unset($effect['overlay']);

	$form['effect'] = array(
		'#type' => 'select',
		'#title' => t('Image Effect'),
		'#description' => t('Apply an Effect to the image on mouse hover.'),
		'#options' => $effect,
		'#default_value' => isset($values['effect']) ? $values['effect'] : NULL,
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$form['sorting'] = array(
		'#type' => 'checkbox',
		'#title' => t('Display tag sorting?'),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
			'disabled' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);
	if (isset($values['sorting'])) {
		$form['sorting']['#default_value'] = $values['sorting'] == 'false' ? FALSE : TRUE;
	}else {
		$form['sorting']['#default_value'] = acquia_variable_get('portfolio_blocks_sorting', TRUE);
	}

	$form['filter_style'] = array(
		'#type' => 'select',
		'#title' => t('Filter style'),
		'#description' => t('Change the appearance of filter area.'),
		'#options' => ac_portfolio_filter_styles(),
		'#default_value' => isset($values['filter_style']) ? $values['filter_style'] : acquia_variable_get('portfolio_blocks_filter_style', TRUE),
		'#states' => array(
			'invisible' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
			'disabled' => array(
				':input[name="appearance"]' => array('value' => 'slider'),
			),
		),
	);

	$form['fullwidth'] = array(
		'#type' => 'checkbox',
		'#title' => t('Full page width style?'),
	);
	if (isset($values['fullwidth'])) {
		$form['fullwidth']['#default_value'] = $values['fullwidth'] == 'true' ? TRUE : FALSE;
	}else {
		$form['fullwidth']['#default_value'] = acquia_variable_get('portfolio_blocks_fullwidth', FALSE);
	}

	$form['media'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display media?'),
		'#description' => t ( 'Turn it On to display media.' ),
	);
	if (isset($values['media'])) {
		$form['media']['#default_value'] = $values['media'] == 'false' ? FALSE : TRUE;
	}else {
		$form['media']['#default_value'] = acquia_variable_get('portfolio_blocks_media', TRUE);
	}

	$form['title'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display title?'),
		'#description' => t ( 'Turn it On to display title.' ),
	);
	if (isset($values['title'])) {
		$form['title']['#default_value'] = $values['title'] == 'false' ? FALSE : TRUE;
	}else {
		$form['title']['#default_value'] = acquia_variable_get('portfolio_blocks_title', TRUE);
	}

	// Date
	$form['date'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Date?'),
		'#description' => t ( 'Check it to Display date.' ),
	);
	if (isset($values['date'])) {
		$form['date']['#default_value'] = $values['date'] == 'true' ? TRUE : FALSE;
	}else {
		$form['date']['#default_value'] = acquia_variable_get('portfolio_blocks_date', FALSE);
	}

	$form['date_format'] = array (
		'#type' => 'textfield',
		'#title' => t('Date Format?'),
		'#description' => '',
		'#default_value' => isset($values['date_format']) ? $values['date_format'] : acquia_variable_get('portfolio_blocks_date_format', 'M j, Y'),
	);

	// Tags
	$form['tags'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Tags?'),
		'#description' => t ( 'Check it to Display tags.' ),
	);
	if (isset($values['tags'])) {
		$form['tags']['#default_value'] = $values['tags'] == 'true' ? TRUE : FALSE;
	}else {
		$form['tags']['#default_value'] = acquia_variable_get('portfolio_blocks_tags', FALSE);
	}

	// Project Link
	$form['proj_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Project Link?'),
		'#description' => t ( 'Check it to Display Project Link.' ),
	);
	if (isset($values['proj_link'])) {
		$form['proj_link']['#default_value'] = $values['proj_link'] == 'false' ? FALSE : TRUE;
	}else {
		$form['proj_link']['#default_value'] = acquia_variable_get('portfolio_blocks_proj_link', TRUE);
	}

	// Details Link
	$form['details_link'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Details link?'),
		'#description' => t ( 'Check it to Display Details link.' ),
	);
	if (isset($values['details_link'])) {
		$form['details_link']['#default_value'] = $values['details_link'] == 'false' ? FALSE : TRUE;
	}else {
		$form['details_link']['#default_value'] = acquia_variable_get('portfolio_blocks_details_link', TRUE);
	}

	// excerpt
	$form['excerpt'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display excerpt?'),
		'#description' => t ( 'Check it to Display excerpt.' ),
	);
	if (isset($values['excerpt'])) {
		$form['excerpt']['#default_value'] = $values['excerpt'] == 'true' ? TRUE : FALSE;
	}else {
		$form['excerpt']['#default_value'] = acquia_variable_get('portfolio_blocks_excerpt', FALSE);
	}

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
 * Process {{ac_portfolio}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_portfolio_preprocess(&$values) {
	if (isset($values['appearance']) && $values['appearance'] == 'scroller') {
		if (isset($values['nav_pager']) && $values['nav_pager'] == TRUE) {
			$values['nav_pager'] = 'true';
		}else{
			$values['nav_pager'] = 'false';
		}

		if (isset($values['nav_prev_next']) && $values['nav_prev_next'] == TRUE) {
			$values['nav_prev_next'] = 'true';
		}else{
			$values['nav_prev_next'] = 'false';
		}

		if (isset($values['auto_scroll']) && $values['auto_scroll'] == TRUE) {
			$values['auto_scroll'] = 'true';
		}else{
			unset($values['auto_scroll']);
		}
	}
	if (isset($values['width']) && $values['width'] == 'pre') {
		unset($values['style']);
	}

	if (isset($values['view']) && $values['view'] == 'dribbble') {
		unset($values['frame']);
	}

	if (isset($values['sorting']) && $values['sorting'] == TRUE) {
		$values['sorting'] = 'true';
	}else{
		$values['sorting'] = 'false';
	}

	if (isset($values['fullwidth']) && $values['fullwidth'] == TRUE) {
		$values['fullwidth'] = 'true';
	}else{
		$values['fullwidth'] = 'false';
	}

	if (isset($values['spaced']) && $values['spaced'] == TRUE) {
		$values['spaced'] = 'true';
	}else{
		$values['spaced'] = 'false';
		$values['padding'] = 0;
	}

	if (isset($values['media']) && $values['media'] == TRUE) {
		$values['media'] = 'true';
	}else{
		$values['media'] = 'false';
	}

	if (isset($values['title']) && $values['title'] == TRUE) {
		$values['title'] = 'true';
	}else{
		$values['title'] = 'false';
	}

	if (isset($values['date']) && $values['date'] == TRUE) {
		$values['date'] = 'true';
	}else{
		$values['date'] = 'false';
	}

	if (isset($values['tags']) && $values['tags'] == TRUE) {
		$values['tags'] = 'true';
	}else{
		$values['tags'] = 'false';
	}

	if (isset($values['proj_link']) && $values['proj_link'] == TRUE) {
		$values['proj_link'] = 'true';
	}else{
		$values['proj_link'] = 'false';
	}

	if (isset($values['details_link']) && $values['details_link'] == TRUE) {
		$values['details_link'] = 'true';
	}else{
		$values['details_link'] = 'false';
	}

	if (isset($values['excerpt']) && $values['excerpt'] == TRUE) {
		$values['excerpt'] = 'true';
	}else{
		$values['excerpt'] = 'false';
	}

	if (isset($values['thumb']) && $values['thumb'] == TRUE) {
		$values['thumb'] = 'true';
	}else{
		unset($values['thumb']);
	}
}

/**
 * process {{ac_portfolio}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_portfolio_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$sc_name = str_replace('_', '-', $shortcode);

	if (!module_exists('ac_portfolio_blocks')) {
		return;
	}
	foreach($attrs as $key => &$val){
		if ($val == 'true') {
			$val = TRUE;
		}else if ($val == 'false') {
			$val = FALSE;
		}
	}

	$out = theme('portfolio_recent', array('settings' => $attrs));
	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		$wrap_attrs = array();
		foreach (explode(' ', $attrs['class']) as $class) {
			$wrap_attrs['class'][] = $class;
		}
		$wrap_attrs['class'] = array_filter($wrap_attrs['class'], 'strlen');

		$out = '<div' .drupal_attributes($wrap_attrs) .'>' .$out .'</div>';
	}
	//---------------------------------------

	return $out;
}