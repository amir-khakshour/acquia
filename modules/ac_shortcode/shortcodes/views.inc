<?php
/**
 * @file shortcode defenition of views
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

function ac_shortcode_views_shortcode() {
	 return array(
		'ac_views' => array(
			'title' => t('views'),
			'description' => t('Embed views in content or blocks.'),
			'form callback' => 'ac_shortcode_ac_views_form',
			'values process callback' => 'ac_shortcode_ac_views_preprocess',
			'process callback' => 'ac_shortcode_ac_views_process',
		),
	 );
}

/**
 * Implements edit form of {{ac_views}} shortcode
 */
function ac_shortcode_ac_views_form($form, &$form_state) {
	 $values = isset($form_state['values']) ? $form_state['values'] : array();
	 $form = array();
	 
	 if (!module_exists('views')) {
			return form_set_error('acquiaShortcode', t('to use this shortcode you need to enabled Views module.'));
	 }
	 
	 $selected = isset($values['view']) ? $values['view'] : null;
	 $form['view'] = array(
			'#type' => 'select',
			'#title' => t('View name'),
			'#description' => t('select view name, you can find a list of views from here: !link', array('!link' => l(t('Views list'), 'admin/structure/views'))),
			'#options' => ac_shortcode_get_views_list(),
			'#default_value' => isset($values['view']) ? $values['view'] : '', 
			'#ajax' => array(
				'callback' => 'ac_shortcode_view_ajax_dispaly_callback',
				'wrapper' => 'views-display-list',
			),
	 );

	 $form['display'] = array(
			'#type' => 'select',
			'#title' => t('Display'),
			'#prefix' => '<div id="views-display-list">',
			'#suffix' => '</div>',
			'#options' => !empty($selected) ? ac_shortcode_get_view_display_list($selected) : array(t('plese select a view first')),
			'#default_value' => isset($values['display']) ? $values['display'] : '',
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

function ac_shortcode_view_ajax_dispaly_callback(&$form, &$form_state) {
	 return $form['display'];
}

/**
 * preprocess {{ac_views}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_views_preprocess(&$values) {

}

/**
 * process {{ac_views}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_views_process($attrs, $text = null, $shortcode = '') {
	$_attrs = ac_shortcode_attrs(array(
		'view'      => '',
		'display'     => 'false', /* Enable repeating views: True/False */
	), $attrs);
	extract($_attrs);

	$sc_name = str_replace('_', '-', $shortcode);
	
	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	//---------------------------------------
	if (!empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------

			//load the view by name
  $view = views_get_view($view);
  if (!$view || !$view->access($display)) {
		return drupal_set_message('You don\'t have enough permission to access this view!', 'warning');
  }

	$view->set_display($display);
	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= '  '.$view->preview();
	$out .= '</div>';
	
	return $out;
}


/**
 *
 */
function ac_shortcode_get_views_list(){
	 $views = array();
	 foreach(ac_shortcode_view_get_enabled_views() as $view_id => $info) {
			$views[$view_id] = isset($info->human_name) && !empty($info->human_name) ? $info->human_name : $info->name;
	 }
	 return $views;
}

/**
 *
 */
function ac_shortcode_get_view_display_list($view_id){
	 $displays = array();
	 
	 $view = views_get_view($view_id);
	 if (!isset($view->display) || empty($view->display)) {
			return $displays;
	 }
	 $displays['default'] = t('Default');
	 foreach ($view->display as &$display) {
		 if ($display->display_plugin == 'page' || $display->display_plugin == 'block') {
			 $displays[$display->id] = $display->display_title;
		 }
	 }
  return $displays;
}

/**
 *
 */
function ac_shortcode_view_get_enabled_views(){
	 $views = views_get_all_views();
	 return array_filter($views, 'views_view_is_enabled');
}