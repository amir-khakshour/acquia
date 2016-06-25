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

function ac_shortcode_pie_shortcode() {
	 return array(
		 'ac_pie' => array(
				 'title' => t('Pie chart'),
				 'description' => t('Display a fancy pie chart for infographics purposes.'),
				 'form callback' => 'ac_shortcode_ac_pie_form',
				 'values process callback' => 'ac_shortcode_ac_pie_preprocess',
				 'process callback' => 'ac_shortcode_ac_pie_process',
			),
	 );
}

/**
 * Implements edit form of {{ac_fancy_pie}} shortcode
 */
function ac_shortcode_ac_pie_form($form, &$form_state) {
  acquia_include('options');
  acquia_include('fields');
	 
  $values = isset($form_state['values']) ? $form_state['values'] : array();
	 
  $form = array();
	
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('title'),
    '#description' => t('What text use as a pie/Pie title. Leave blank if no title is needed.'),
    '#default_value' => isset($values['title']) ? $values['title'] : '',
  );
  
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie value'),
    '#description' => t('Input graph value here. please enter Witihn a range 0-100 for pie chart.'),
    '#default_value' => isset($values['value']) ? $values['value'] : '',
  );
  
  $form['units'] = array(
    '#type' => 'textfield',
    '#title' => t('Units'),
    '#description' => t('Enter measurement units (if needed) Eg. %, px, points, etc. Graph value and unit will be appended to the graph title.'),
    '#default_value' => isset($values['units']) ? $values['units'] : '',
  );
	
  $form['unit_pos'] = array(
    '#type' => 'select',
    '#title' => t('Units position'),
		'#options' => array(
			'tc' => t('Top center'),
			'tr' => t('Top right'),
			'cc' => t('center center'),
			'bc' => t('bottom center'),
			'br' => t('bottom right'),
		),
    '#description' => '',
    '#default_value' => isset($values['unit_pos']) ? $values['unit_pos'] : 'center-center',
  );

	$form['fill'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('fill Color'),
		'#description' => t('Select a fill color for your pie chart here'),
		'#default_value' => isset($values['fill']) ? $values['fill'] : '#444444',
	);
  
  $form['bg_style'] = array(
		'#type' => 'select',
		'#title' => t('Pie background type'),
		'#description' => t('Select a background type for your Pie chart here; e.g. light for dark section.'),
		'#options' => array('light' => t('light'), 'dark' => t('Dark')),
		'#default_value' => isset($values['bg_style']) ? $values['bg_style'] : 'dark',
	);

	$ops = array_merge(array('' => t('Inherit'), 'custom' => t('Custom Color')), acquia_skins_list());

	$form['color'] = array(
		'#type' => 'select',
		'#title' => t('text Color'),
		'#description' => t('Select text color.'),
		'#options' => $ops,
		'#default_value' => isset($values['color']) ? $values['color'] : '',
	);
	
	$form['custom_color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom text Color'),
		'#description' => t('Select a custom color for your text here'),
		'#default_value' => isset($values['custom_color']) ? $values['custom_color'] : '#444444',
		'#states' => array(
			'visible' => array(
					':input[name="color"]' => array('value' => 'custom'),
			),
		),
	);
  
  // add icon fields
  acquia_field_iconfont($form, $form, array(
     'title' => t('pie Icon'),
     'default' => isset($values['icon']) ? $values['icon'] : '',
     'parents' => array(),
     'animate' => FALSE,
     'always_enabled' =>FALSE,
  ));
  
   $settings = array(
     'title' => t('pie'),
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
 * preprocess {{ac_pie}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_pie_preprocess(&$values) {
  if (isset($values['bg_color']) && $values['bg_color'] !='custom') {
    unset($values['bg_color_custom']);
  }else if (!isset($values['bg_color'])) {
    unset($values['bg_color_custom']);
  }
  
  if (isset($values['color']) && $values['color'] !='custom') {
    unset($values['custom_color']);
  }else if (!isset($values['color'])) {
    unset($values['custom_color']);
  }
	 if (isset($values['gridy']) && $values['gridy'] == TRUE) {
			$values['gridy'] = 'true';
	 }else{
			unset($values['gridy']);
	 }
}

/**
 * process {{ac_fancy_pie}} and {{ac_page_pie}} Shortcodes
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_pie_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	acquia_include('utility');

	$_attrs = ac_shortcode_attrs(array(
   'title' => '',
   'value' => '75',
   'units' => '',
   'fill' => '',
   'bg_style' => 'dark',
   'icon' => '',
   'unit_pos' => 'tr',
	), $attrs);
	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	$attributes['class'][] = acquia_get_class_by_args(array('bg_style', 'unit_pos'), $_attrs, CHECK_LENGTH);
	$attributes['class'][] = isset($attrs['animate']) && !empty($attrs['animate']) ? 'ac-animate' : null;
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
  
  $attributes['data-pie-value'] = isset($attrs['value']) ? $attrs['value'] : '';
  $attributes['data-pie-color'] = isset($attrs['fill']) ? $attrs['fill'] : 'rgba(0,0,0,5)';
 
	if (!empty($icon)) {
   	acquia_include('fonts');
    $ico_class = array(acquia_fontello_glyph_get_code($icon));
    $icon = theme('acquia_iconfont', array('class' => $ico_class));
	}

  drupal_add_library('acquia', 'progress-circle');
  drupal_add_js(drupal_get_path('module', 'ac_shortcode') . '/shortcodes/assets/jquery.vc_chart.js');
 
  $text_attrs = array('class' => array('ac-pie-fill'));
	if (isset($attrs['custom_color']) && !empty($attrs['custom_color'])) {
		$text_attrs['style'] = 'color: '. $attrs['custom_color'];
	}else if (isset($attrs['color']) && $attrs['color'] != 'custom') {
		$text_attrs['class'][] = acquia_get_class_by_args(array('color'), $attrs, CHECK_LENGTH);
	}
	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= '  <div class="ac-pie-wrap">';
	$out .= '    <span class="ac-pie-bg"></span>';
	$out .= '    <h3'.drupal_attributes($text_attrs).'><span class="label"></span><span class="unit">'.$_attrs['units'].'</span></h3>';
	$out .= '    <canvas width="101" height="101"></canvas>';
	$out .= '  </div>';
	$out .= '  <h4 class="'.$sc_name.'-title">'.$title.'</h4>';
	$out .= '  ' .$icon;
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