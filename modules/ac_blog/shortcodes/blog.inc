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

function ac_blog_blog_shortcode() {
	 return array(
		 'ac_blog' => array(
				 'title' => t('Blog'),
				 'description' => t('Display blog items in fancy way!'),
				 'form callback' => 'ac_shortcode_ac_blog_form',
				 'values process callback' => 'ac_shortcode_ac_blog_preprocess',
				 'process callback' => 'ac_shortcode_ac_blog_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_blog}} shortcode
 */
function ac_shortcode_ac_blog_form($form, &$form_state) {
	acquia_include('options');
  acquia_include('fields');
	acquia_include('options', 'ac_blog');
	
	$values = isset($form_state['values']) ? $form_state['values'] : array();

	$form['id'] = array (
		'#type' => 'textfield',
		'#title' => t('ID'),
		'#description' => '',
		'#default_value' => isset($values['id']) ? $values['id'] : uniqid('blog-items-'),
	);
	
	$form['appearance'] = array (
		'#type' => 'select',
		'#title' => t('Appearance'),
		'#description' => '',
		'#default_value' => isset($values['appearance']) ? $values['appearance'] : acquia_variable_get('blog_blocks_appearance', 'masonry'),
		'#options' => ac_blog_appearance(),
	);
	
	
	$form['nav_pager'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider pager?'),
		'#description' => t ( 'Check it to Display slider pager.' ),
		'#default_value' => isset($values['nav_pager']) && $values['nav_pager'] == 'true' ? TRUE : FALSE,
     '#states' => array(
       'visible' => array(
         ':input[name="appearance"]' => array('value' => 'scroller'),
       ),
     ),
	);
	
	$form['nav_prev_next'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display slider prev/next navigation?'),
		'#description' => t ( 'Check it to Display Navigation.' ),
		'#default_value' => isset($values['nav_prev_next']) && $values['nav_prev_next'] == 'true' ? TRUE : FALSE,
     '#states' => array(
       'visible' => array(
         ':input[name="appearance"]' => array('value' => 'scroller'),
       ),
     ),
	);
	
	$form['total'] = array (
		'#type' => 'textfield',
		'#title' => t('Total Number of Items'),
		'#description' => t ( 'Number of portoflio items to extract from database. Enter -1 to extract all portoflio items.' ),
		'#default_value' => isset($values['total']) ? $values['total'] : acquia_variable_get('blog_blocks_total', -1),
	);

	$form['num_per_page'] = array (
		'#type' => 'textfield',
		'#title' => t('Pager items'),
		'#description' => t ( 'Number of items in each page. Enter -1 to disable pager view.' ),
		'#default_value' => isset($values['num_per_page']) ? $values['num_per_page'] : acquia_variable_get('blog_blocks_num_per_page', 12),
	);
	
	$form['spaced'] = array(
		 '#type' => 'checkbox',
		 '#title' => t('Spaced Items?'),
	 );
	if (isset($values['spaced'])) {
    $form['spaced']['#default_value'] = $values['spaced'] == 'true' ? TRUE : FALSE;
	}else {
    $form['spaced']['#default_value'] = acquia_variable_get('blog_blocks_spaced', TRUE);
	}
	$form['padding'] = array (
		'#type' => 'textfield',
		'#field_suffix' => t('(px)'),
		'#title' => t('padding between items'),
		'#description' => t ( 'Items paddings (e.g. 5 pixel padding will give you 10 pixel paddings between items)' ),
		'#default_value' => isset($values['padding']) ? $values['padding'] : acquia_variable_get('blog_blocks_padding', 20),
		'#states' => array(
			'visible' => array(
				':input[name="spaced"]' => array('checked' => TRUE),
			),
		),
	);

	$form['cols'] = array (
    '#type' => 'select',
    '#title' => t('Columns'),
    '#description' => t ( 'Number of Columns to show. in slider appearance type this is the number of items visible in each slides loop; e.g., 4' ),
    '#default_value' => isset($values['cols']) ? $values['cols'] : acquia_variable_get('blog_blocks_cols', 4),
		'#options' => drupal_map_assoc ( range (1, 6) ) 
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
		'#title' => t('Items width'),
		'#description' => '',
		'#default_value' => isset($values['width']) ? $values['width'] : acquia_variable_get('blog_blocks_width', 'equal'),
		'#options' => array('pre' => t('Preserve original item width'), 'equal' => t('Make Items same width')),
	);
	
	$form['style'] = array (
		'#type' => 'select',
		'#title' => t('image style'),
		'#description' => t ( 'Select <none> to use the original image dimension.' ),
		'#default_value' => isset($values['style']) ? $values['style'] : acquia_variable_get('blog_blocks_style', 'blog-recent'),
		'#options' => image_style_options (),
		'#states' => array(
			'visible' => array(
				':input[name="width"]' => array('value' => 'equal'),
			),
		),
	);
	
	$effect = acquia_image_effects();
	unset($effect['overlay']);
	$form['effect'] = array(
		'#type' => 'select',
		'#title' => t('Image Effect'),
		'#description' => t('Apply an Effect to the image on mouse hover.'),
		'#options' => $effect,
		'#default_value' => isset($values['effect']) ? $values['effect'] : NULL,
	);

	 $form['fullwidth'] = array(
		 '#type' => 'checkbox',
		 '#title' => t('Full page width style?'),
	 );
	if (isset($values['fullwidth'])) {
    $form['fullwidth']['#default_value'] = $values['fullwidth'] == 'true' ? TRUE : FALSE;
	}else {
    $form['fullwidth']['#default_value'] = acquia_variable_get('blog_blocks_fullwidth', FALSE);
	}

	$form['media'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display media?'),
		'#description' => t ( 'Turn it On to display media.' ),
	);
	if (isset($values['media'])) {
    $form['media']['#default_value'] = $values['media'] == 'false' ? FALSE : TRUE;
	}else {
    $form['media']['#default_value'] = acquia_variable_get('blog_blocks_media', TRUE);
	}
	
	$form['title'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display title?'),
		'#description' => t ( 'Turn it On to display title.' ),
	);
	if (isset($values['title'])) {
    $form['title']['#default_value'] = $values['title'] == 'false' ? FALSE : TRUE;
	}else {
    $form['title']['#default_value'] = acquia_variable_get('blog_blocks_title', TRUE);
	}

	 // Date
	$form['author'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display author?'),
		'#description' => t ( 'Check it to Display author.' ),
	);
	if (isset($values['date'])) {
    $form['author']['#default_value'] = $values['author'] == 'true' ? TRUE : FALSE;
	}else {
    $form['author']['#default_value'] = acquia_variable_get('blog_blocks_author', FALSE);
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
    $form['date']['#default_value'] = acquia_variable_get('blog_blocks_date', FALSE);
	}
	
	$form['date_format'] = array (
		'#type' => 'textfield',
		'#title' => t('Date Format?'),
		'#description' => '',
		'#default_value' => isset($values['date_format']) ? $values['date_format'] : acquia_variable_get('blog_blocks_date_format', 'M j, Y'),
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
    $form['tags']['#default_value'] = acquia_variable_get('blog_blocks_tags', TRUE);
	}
	
	// subtitle
	$form['excerpt'] = array (
		'#type' => 'checkbox',
		'#title' => t('Display Excerpt?'),
		'#description' => t ( 'Check it to Display Excerpt.' ),
	);
	if (isset($values['excerpt'])) {
    $form['excerpt']['#default_value'] = $values['excerpt'] == 'true' ? TRUE : FALSE;
	}else {
    $form['excerpt']['#default_value'] = acquia_variable_get('blog_blocks_excerpt', FALSE);
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
 * Process {{ac_blog}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_blog_preprocess(&$values) {
   if (isset($values['appearance']) && $values['appearance'] == 'scroller') {
			if (isset($values['nav_pager']) && $values['nav_pager'] == TRUE) {
				$values['nav_pager'] = 'true';
			}else{
				unset($values['nav_pager']);
			}
			
			if (isset($values['nav_prev_next']) && $values['nav_prev_next'] == TRUE) {
				$values['nav_prev_next'] = 'true';
			}else{
				unset($values['nav_prev_next']);
			}
	 }
	 
   if (isset($values['width']) && $values['width'] == 'pre') {
		 unset($values['style']);
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
	 
	 if (isset($values['author']) && $values['author'] == TRUE) {
		 $values['author'] = 'true';
	 }else{
		 $values['author'] = 'false';
	 }
	 
	 if (isset($values['tags']) && $values['tags'] == TRUE) {
		 $values['tags'] = 'true';
	 }else{
		 $values['tags'] = 'false';
	 }
 
	 if (isset($values['excerpt']) && $values['excerpt'] == TRUE) {
		 $values['excerpt'] = 'true';
	 }else{
		 $values['excerpt'] = 'false';
	 }
}

/**
 * process {{ac_blog}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_blog_process($attrs, $text = null, $shortcode = '') {
	acquia_include('options', 'ac_blog');
	$sc_name = str_replace('_', '-', $shortcode);

  foreach($attrs as $key => &$val){
    if ($val == 'true') {
      $val = TRUE;
    }else if ($val == 'false') {
      $val = FALSE;
    }
  }
  if (in_array($attrs['appearance'], array_keys(ac_blog_related_views()))) {
    $block = theme('blog_recent', array('settings' => $attrs));
  }else {
    $block = theme('blog_appearance_' . $attrs['appearance'], array('settings' => $attrs));
  }
	return $block;
}