<?php
/**
 * @file shortcode defenition of block_embed
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

function ac_shortcode_block_embed_shortcode() {
	 return array(
		'ac_block_embed' => array(
			'title' => t('Block Embed'),
			'description' => t('Embeding blocks in content.'),
			'form callback' => 'ac_shortcode_ac_block_embed_form',
			'values process callback' => 'ac_shortcode_ac_block_embed_preprocess',
			'process callback' => 'ac_shortcode_ac_block_embed_process',
		),
	 );
}

/**
 * Implements edit form of {{ac_block_embed}} shortcode
 */
function ac_shortcode_ac_block_embed_form($form, &$form_state) {
	 $values = isset($form_state['values']) ? $form_state['values'] : array();
	 $form = array();
	 $form['id'] = array(
			'#type' => 'select',
			'#title' => t('Block'),
			'#description' => t('select block, you can find a list of views from here: !link', array('!link' => l(t('Views list'), 'admin/structure/block/'))),
			'#options' => ac_shortcode_get_block_list(),
			'#default_value' => isset($values['id']) ? $values['id'] : '', 
	 );
  $form['custom_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom title?'),
    '#default_value' => isset($values['block_title']) && !empty($values['block_title']) ? TRUE : FALSE,
  );
	 
  $form['block_title'] = array (
		'#type' => 'textfield',
		'#title' => t('Title'),
		'#description' => t ( 'Enter the custom title.' ),
		'#default_value' => isset($values['block_title']) ? $values['block_title'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="custom_title"]' => array('checked' => TRUE),
			),
		),
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
 * preprocess {{ac_block_embed}} values from shortcode form before making shortcode string
 */
function ac_shortcode_ac_block_embed_preprocess(&$values) {
	 unset($values['custom_title']);
}

/**
 * process {{ac_block_embed}} Shortcode 
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_block_embed_process($attrs, $text = null, $shortcode = '') {
	$sc_name = str_replace('_', '-', $shortcode);

	$attributes = array();
	$attributes['class'] = array();
	$attributes['class'][] = $sc_name;
	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$attributes['class'][] = $class;
		}
	}
	$attributes['class'] = array_filter($attributes['class'], 'strlen');
	$attributes['class'] = implode(' ', $attributes['class']);
	//---------------------------------------

	$attrs['id'] = explode('||', $attrs['id']);
	 acquia_include('block');
	 $block = block_load($attrs['id'][0], $attrs['id'][1]);
	 acquia_prepare_block_display($block);
	 
	 $block_array = _block_render_blocks(array($block));
	 if (isset($attrs['block_title']) && !empty($attrs['block_title'])) {
		 foreach($block_array as &$_block){
			 $_block->subject = t($attrs['block_title']);
		 }
	 }
	 $block_array = _block_get_renderable_array($block_array);
	 
	$out = '<div'.drupal_attributes($attributes).'>';
	$out .= '  '.render($block_array);
	$out .= '</div>';
	
	return $out;
}

/**
 *
 */
function ac_shortcode_get_block_list(){
  $query = db_select('block', 'b');
  $result = $query->fields('b')->orderBy('b.region')->condition('b.theme', variable_get('theme_default'))->orderBy('b.weight')->orderBy('b.module')->addTag('block_load')->addTag('translatable')->execute();

  $block_info = $result->fetchAllAssoc('bid');
  // Allow modules to modify the block list.
  drupal_alter('block_list', $block_info);
	 
  // Load menus
  $menus = menu_load_all();
	
	// Load sliders
	$sliders = array();
	if (module_exists('ac_slider')){
    acquia_include('utility', 'ac_slider');
    $sliders = get_sliders_by_id();
	}
  $blocks = array();
	$end_blocks = array();
  foreach ($block_info as $block) {
	 
	  if (empty($block->title)) {
			if ($block->module == 'menu') {
				$block->title = $menus[$block->delta]['title'];
			}elseif ($block->module == 'ac_slider') {
				$block->title = $sliders[$block->delta];
			}else {
				$end_blocks[$block->module]["{$block->module}||{$block->delta}"] = "{$block->module} > {$block->delta}";
				continue;
			}
		}
    $blocks[$block->module]["{$block->module}||{$block->delta}"] = $block->title;
  }

	$blocks += $end_blocks;
  return $blocks;
}
