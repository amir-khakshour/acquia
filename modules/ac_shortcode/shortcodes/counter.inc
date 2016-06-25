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

function ac_shortcode_counter_shortcode() {
	 return array(
		 'ac_counter' => array(
				 'title' => t('Counter'),
				 'description' => t('Display a fancy counter for infographics purposes.'),
				 'form callback' => 'ac_shortcode_ac_counter_form',
				 'values process callback' => 'ac_shortcode_ac_counter_preprocess',
				 'process callback' => 'ac_shortcode_ac_counter_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_fancy_counter}} shortcode
 */
function ac_shortcode_ac_counter_form($form, &$form_state) {
  acquia_include('options');
  acquia_include('fields');
	 
  $values = isset($form_state['values']) ? $form_state['values'] : array();
	 
  $form = array();
	
  $values = isset($form_state['values']) ? $form_state['values'] : array();

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('title'),
    '#description' => t('What text use as a Counter/Pie title. Leave blank if no title is needed.'),
    '#default_value' => isset($values['title']) ? $values['title'] : '',
  );
  
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Counter value'),
    '#description' => t('Input graph value here. please enter Witihn a range 0-100 for pie chart.'),
    '#default_value' => isset($values['value']) ? $values['value'] : '',
  );
  
  $form['units'] = array(
    '#type' => 'textfield',
    '#title' => t('Units'),
    '#description' => t('Enter measurement units (if needed) Eg. %, px, points, etc. Graph value and unit will be appended to the graph title.'),
    '#default_value' => isset($values['units']) ? $values['units'] : '',
  );
	
	$form['style'] = array(
    '#type' => 'select',
    '#title' => t('Counter style'),
    '#description' => '',
    '#options' => array('simple' => t('Simple'), 'bordered' => t('Bordered')),
    '#default_value' => isset($values['style']) ? $values['style'] : 'bordered',
  );
  
  $form['bg_style'] = array(
		'#type' => 'select',
		'#title' => t('Counter background type'),
		'#description' => t('Select a background type for your Counter here; e.g. light for dark section!'),
		'#options' => array('light' => t('light'), 'dark' => t('Dark')),
		'#default_value' => isset($values['bg_style']) ? $values['bg_style'] : 'dark',
	);

  $ops = array_merge(array('' => t('theme default')), acquia_skins_list());
	$form['border_color'] = array(
		'#type' => 'select',
		'#title' => t('Border color'),
		'#description' => t('Select Counter border color.'),
		'#options' => $ops,
		'#default_value' => isset($values['border_color']) ? $values['border_color'] : '',
	);

	$ops = array_merge(array('' => t('theme default'), 'custom' => t('Custom Color')), acquia_skins_list());

	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('Counter Color'),
		'#description' => t('Select Counter color.'),
		'#options' => $ops,
		'#default_value' => isset($values['color']) ? $values['color'] : '',
	);
	
	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Counter Color'),
		'#description' => t('Select a custom color for your Counter  here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
					':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);
	
	$op = acquia_align_list();
	$form['align'] = array(
		'#type' => 'select',
		'#title' => t('Counter alignment'),
		'#description' => t('Choose the alignment of your Counter text here'),
		'#default_value' => isset($values['align']) ? $values['align'] : 'center',
		'#options' => $op,
	);
	
  // add icon fields
  acquia_field_iconfont($form, $form, array(
     'title' => t('Counter Icon'),
     'default' => isset($values['icon']) ? $values['icon'] : '',
     'parents' => array(),
     'animate' => FALSE,
     'always_enabled' =>FALSE,
  ));
  
   $settings = array(
     'title' => t('Counter'),
   );
   if (isset($values['animate'])) {
     $settings['animate'] = $values['animate'];
     $settings['when'] = $values['when'];
   }
   
  // add animate fields
  acquia_field_animate($form, $settings);
	$form['gridy'] = array(
		'#attributes' => array('data-help' => t('turn it on if this item is in grid shortcode.')),
		'#type' => 'checkbox',
		'#title' => t('Enable gridy?'),
		//'#description' => t('chenge to On if you want to enable lightbox on this image.'),
		'#default_value' => isset($values['gridy']) && $values['gridy'] == 'true' ? TRUE :FALSE,
	);
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
 * preprocess {{ac_counter}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_counter_preprocess(&$values) {
  //if (isset($values['border_color']) && $values['border_color'] !='custom') {
  //  unset($values['border_color_custom']);
  //}else if (!isset($values['border_color'])) {
  //  unset($values['border_color_custom']);
  //}
  //
  if (isset($values['color']) && $values['color'] !='custom') {
    unset($values['custom_color']);
  }else if (!isset($values['color'])) {
    unset($values['custom_color']);
  }
	
	if (isset($values['align']) && $values['align'] =='center') {
    unset($values['align']);
  }
	
	 if (isset($values['gridy']) && $values['gridy'] == TRUE) {
			$values['gridy'] = 'true';
	 }else{
			unset($values['gridy']);
	 }
}

/**
 * process {{ac_fancy_counter}} and {{ac_page_counter}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_counter_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');
	$_attrs = ac_shortcode_attrs(array(
   'title' => '',
   'value' => '75',
   'units' => '',
   'color' => '',
   'border_color' => '',
   'bg_style' => 'dark',
   'style' => 'dark',
   'align' => '',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);
	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = acquia_get_class_by_args(array('border_color', 'bg_style', 'align', 'style'), $_attrs, CHECK_LENGTH);
	$attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
	$attributes['class'][] = 'ac-frame-on';
	$attributes['class'][] = 'clearfix';
	
	//---------------------------------------
	if ( isset($attrs['class']) && !empty($attrs['class']) ) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------
	
	if (isset($attrs['animate'])) {
    // Animate data 
    $attributes += acquia_get_anim_data_by_attrs($attrs);
	}
 
  drupal_add_library('acquia', 'jquery.countTo');
  
  $counter_attrs = array('class' => array($sc_name.'-counter'));
  if (isset($attrs['color']) && $attrs['color'] !='custom') {
    $counter_attrs['class'][] = acquia_get_class_by_args(array('color'), $_attrs, CHECK_LENGTH);
  }else if(isset($attrs['custom_color'])) {
    $counter_attrs['style'] = 'color:' .$attrs['custom_color'];
  }
  
	$out  = '<div'.drupal_attributes($attributes).'>';
  
	if (isset($attrs['icon']) && !empty($attrs['icon'])) {
   	acquia_include('fonts');
    $ico_class = array(acquia_fontello_glyph_get_code($attrs['icon']));
    $out .= theme('acquia_iconfont', array('class' => $ico_class));
	}
	
	$out .= '  <h3'.drupal_attributes($counter_attrs).'>';
	$out .= '   <span class="display-counter" data-value="'.$attrs['value'].'"></span>';
  if (!empty($units)) {
   $out .= '  <span class="units">'.$units.'</span>';
  }
	$out .= '  </h3>';
	$out .= '  <span class="sep"></span>';
	$out .= '  <h4 class="'.$sc_name.'-title">'.$title.'</h4>';

	$out .= '</div>';

	/** Wrap Grid HTML **/
	if (isset($attrs['gridy']) && strtolower($attrs['gridy']) == 'true') {
		$temp  = '<div class="ac-grid-item">';
		$temp .= '	<div class="g-i clearfix">';
		$temp .= '		<div class="g-i-i clearfix">';
		$temp .= $out;
		$temp .= '		</div>';
		$temp .= '	</div>';
		$temp .= '</div>';
		
		$out = $temp;
	}
	return $out;
}
