<?php

/**
 * @file
 * Add new helper functions to build and manipulate fields
 */

/*==============================================================*/
// Animate field
/*==============================================================*/
/**
 * Get structured form elements of aniamtion selector
 * @param {array} $context
 * 		An array of form elements for attaching required assets
 * @param {array} $field_name
 *   An associative array containing the following settings keys:
 *   - %field_name: The unique key name for building field form element.
 *   - %title: The font selector element title.
 *   - %description: The description of font selector element.
 *   - %enabled: Whether animate fieldset enabled or not
 *   - %collapsible: Render animation settings fields collapsible 
 * @return {array}
 * 		array of form elements
 */
function acquia_field_tooltip(&$context, $settings = array()) {
  acquia_include('options');

	if (isset($settings['info'])) {
		$settings['enabled'] = TRUE;
	}
	
	$settings += array(
		'field_name' => 'tooltip',
		'parents' => array(),
		'title' => 'Tooltip - Popover item',
		'description' => t('Build an Tooltip - Popover behaviour for your item.'),
		'enabled' => FALSE,
		'add_title' => FALSE,
		'info' => 'tooltip',// “popover” or “tooltip.”
		'info_place' => 'top',// “top,” “right,” “bottom,” or “left.”
		'info_trigger' => 'hover',//  “hover,” “click,” or “focus.”
		'info_content' => 'extra content for the popover',// extra content for the popover.
		'collapsible' => TRUE,
	);
	$context += acquia_field_tooltip_elements($settings);
}

/**
 * Make an instance of attachment select aniamte elements
 * @todo Document here
 */
function acquia_field_tooltip_elements($settings) {
  acquia_include('options');
  acquia_include('content');
  acquia_include('utility');

	$field_name = $settings['field_name'];
	
	if (count($settings['parents'])) {
		$active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array($field_name, 'enabled') );
    $active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
	}else {
		$active_trail = $field_name .'[enabled]';
	}
	
	$elements[$field_name .'-enabled'] = array(
		'#type' => 'checkbox',
		'#title' => t('Build an Tooltip - Popover behaviour for your %field.', array('%field' =>  $settings['title'])),
		'#default_value' => $settings['enabled'],
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'enabled') ),
	);
	
	$elements[$field_name] = array(
		'#type' => 'fieldset',
		'#title' => t('Tooltip - Popover %field', array('%field' => $settings['title'])),
		'#description' => $settings['description'],
		'#collapsible' => $settings['collapsible'],
		'#collapsed' => $settings['enabled'] ? FALSE : TRUE,
		'#states' => array(
			'enabled' => array(
					':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
			),
			'visible' => array(
					':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
			),
		),
	);
	
	$elements[$field_name]['info'] = array(
		'#type' => 'select',
		'#title' => t('select tooltip type'),
		'#default_value' => $settings['info'],
		'#description' => t('popover or tooltip.'),
		'#options' => (array)acquia_tooltip_info(),
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'info') ),
	);
	
	$elements[$field_name]['info_place'] = array(
		'#type' => 'select',
		'#title' => t('Where to dispaly tootltip?'),
		'#description' => '',
		'#default_value' => $settings['info_place'],
		'#options' => (array)acquia_directions(),
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'info_place') ),
	);
	
	$elements[$field_name]['info_trigger'] = array(
		'#type' => 'select',
		'#title' => t('When Dispaly tooltip?'),
		'#description' => '',
		'#default_value' => $settings['info_trigger'],
		'#options' => (array)acquia_tooltip_info_triggers(),
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'info_trigger') ),
	);
	
	if ($settings['add_title'] === TRUE) {
		$elements[$field_name]['info_title'] = array(
			'#type' => 'textfield',
			'#title' => t('place your Title for the popover here.'),
			'#description' => '',
			'#default_value' => $settings['info_title'],
			'#tree' => TRUE,
			'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'info_title') ),
		);
	}
	
	$elements[$field_name]['info_content'] = array(
		'#type' => 'textarea',
		'#title' => t('place your extra content for the popover here.'),
		'#description' => '',
		'#default_value' => $settings['info_content'],
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'info_content') ),
	);

	return $elements;
}


/*==============================================================*/
// Animate field
/*==============================================================*/
/**
 * Get structured form elements of aniamtion selector
 * @param {array} $context
 * 		An array of form elements for attaching required assets
 * @param {array} $field_name
 *   An associative array containing the following settings keys:
 *   - %field_name: The unique key name for building field form element.
 *   - %anim_css_file: The CSS file name under your libs/animate.css folder to extract list of supported animations
 *   - %title: The font selector element title.
 *   - %description: The description of font selector element.
 *   - %enabled: Whether animate fieldset enabled or not
 *   - %default: The default selected value, in our case it should be the string representation of animation.
 *   - %when: Animation display offset
 *   - %collapsible: Render animation settings fields collapsible 
 *   - %delay_enabled: Whether display delay settings or not
 *   - %delay: Aniamtion delay in miliseconds
 * @return {array}
 * 		array of form elements
 */
function acquia_field_animate(&$context, $settings = array()) {
  acquia_include('options');

	if (isset($settings['animate'])) {
		$settings['enabled'] = TRUE;
	}
	
	$settings += array(
		'field_name' => 'cssanimate',
		'parents' => array(),
		'anim_css_file' => 'animate-custom.css',
		'title' => 'Animate item',
		'description' => t('Build an animation behaviour for your item.'),
		'enabled' => FALSE,
		'animate' => NULL,
		'when' => array_shift(array_keys(acquia_animate_point_list())),
		'collapsible' => TRUE,
		'delay_enabled' => FALSE,
		'delay' => acquia_variable_get('animate_delay'),
	);
	$context += acquia_field_animate_elements($settings);
}

/**
 * Make an instance of attachment select aniamte elements
 * @todo Document here
 */
function acquia_field_animate_elements($settings) {
  acquia_include('options');
  acquia_include('content');
  acquia_include('utility');

	$field_name = $settings['field_name'];
	
	if (count($settings['parents'])) {
		$active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array($field_name, 'enabled') );
    $active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
	}else {
		$active_trail = $field_name .'[enabled]';
	}
	
	$elements = array(
		$field_name .'-enabled' => array(
			'#type' => 'checkbox',
			'#title' => t('Enable animation of %field during it\'s appearance.', array('%field' =>  $settings['title'])),
			'#default_value' => $settings['enabled'],
			'#tree' => TRUE,
			'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'enabled') ),
		),
		$field_name => array(
			'#type' => 'fieldset',
			'#title' => t('Aniamte %field', array('%field' => $settings['title'])),
			'#description' => $settings['description'],
			'#collapsible' => $settings['collapsible'],
			'#collapsed' => $settings['enabled'] ? FALSE : TRUE,
			'#states' => array(
				'enabled' => array(
						':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
				'visible' => array(
						':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
			),
			'animate' => array(
				'#type' => 'select',
				'#title' => t('select animation'),
				'#default_value' => $settings['animate'],
				'#description' => t('select an animation from the list. Add a small animation to the image when the user first scrolls to the image position.'),
				'#options' => (array)acquia_css_animate_list(),
				'#tree' => TRUE,
				'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'animate') ),
			),
			'when' => array(
				'#type' => 'select',
				'#title' => t('When animate starts?'),
				'#description' => '',
				'#default_value' => $settings['when'],
				'#options' => (array)acquia_animate_point_list(),
				'#tree' => TRUE,
				'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'when') ),
			),
		),
	);
	
	if (isset($settings['delay_enabled']) && $settings['delay_enabled'] == 1) {
		$elements[$field_name]['delay'] = array(
			'#type' => 'textfield',
			'#title' => t('Animation delay.'),
			'#description' => 'how much time in milliseconds to delay after a child animates before starting next child.',
			'#default_value' => $settings['delay'],
			'#tree' => TRUE,
			'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'delay') ),
		);
	}

	return $elements;
}


/*==============================================================*/
// Iconfont field
/*==============================================================*/
/**
 * Get form structure of icon select elements
 * @param {array} $context
 * 		An array of form elements for attaching required assets
 * @param {array} $field_name
 *   An associative array containing the following settings keys:
 *   - field_name: The unique key name for building field form element.
 *   - font_name: The font identifier that is used for font folder too.
 *   - font_config: The config file name under fonts/font_name to extract list of supported fonts
 *   - title: The font selector element title.
 *   - description: The description of font selector element.
 *   - default: The default selected value, in our case it should be the numeric code of font.
 * @return {array}
 * 		array of form elements
 */
function acquia_field_iconfont(&$context, &$form, $settings = array()) {
  acquia_include('utility');
  acquia_include('content');
  acquia_include('fonts');
	
	if (isset($settings['default']) && !empty($settings['default'])) {
		$settings['enabled'] = TRUE;
	}
	
	$settings += array(
		'field_name' => 'fonticon',
		'font_name' => 'fontello',
		'font_config' => 'config.json',
		'title' => t('Button'),
		'default' => null,
		'attachment_class' => 'icons',
		'animate' => FALSE,
		'enabled' => FALSE,
		'when' => FALSE,
		'parents' => array(),
		'always_enabled' => FALSE,
	);
	$settings += array('description' => t('Select an icon for your %el bellow', array('%el' => $settings['title'])));

	
	$settings['extra_elements']	= array(
		//'font' => array(
		//	'#type' => 'value',
		//	'#value' => $settings['font_name'],
		//	'#tree' => TRUE,
		//	'#parents' => acquia_arr_push_copy( $settings['parents'], array($settings['field_name'], 'font') ),
		//),
	);

	if ($settings['animate'] == TRUE) {
		$anim_settings = array('title' => t('Icon'));
		$anim_settings['parents'] = $settings['parents'];
	 if (is_string($settings['animate'])) {
			$anim_settings['animate'] = $settings['animate'];
			$anim_settings['when'] = $settings['when'];
	 }
	 acquia_field_animate($settings['extra_elements'], $anim_settings);
	}


  $config = acquia_fontello_extract_config($settings['font_name'], $settings['font_config']);
	
	$css = acquia_get_fontello_css($settings);
	$rs = acquia_ajax_get_resources(array('admin', 'isotope', 'icon-filter'));
	$css = array_merge($css, $rs['css']);
	$js = $rs['js'];
	
	$context += acquia_iconfield_attachment($settings, acquia_field_iconfont_attachment($config, $settings['default']));
	$form['#attached'] = array('css' => $css, 'js' => $js);
}

/**
 * Makes list of icon fonts in a selectable manner
 * 
 * @param {array} $config
 * 		array of font config
 * @param {string} $default
 * 		default icon that is selected
 * @return HTML of icon fonts list
 */
function acquia_field_iconfont_attachment($config, $default){
	$out = '';
	if (!isset($config['glyphs']) || empty($config['glyphs'])) {
		return;
	}

	$out .= '<ul class="ac-el-container ac-font-'.$config['font'].'">';
	foreach($config['glyphs'] as $code => $glyph) {
		$active = $code == $default || $glyph == $default ? ' ac-active-el ' : '';
		$out .= '<li class="ico-element"><span data-inject-val="'.$glyph.'" data-help="'.$glyph.'" class="ac-inject-el tooltip '.$config['class-prefix'].$glyph.$active.'"><span class="invisible">'.$glyph.'</span></span></li>';
	}
	$out .= "</ul>";

	return $out;
}


/*==============================================================*/
// helper functions
/*==============================================================*/
/**
 * Make an instance of attachment select field elements
 * @todo Document here
 */
function acquia_iconfield_attachment($settings, $attachment){
	$settings += array(
		'default' => null,
		'collapsible' => true,
		'collapsed' => false,
		'extra_elements' => array(), // list of extra elements for attachment
		'attachment_class' => 'items', // list of hidden elements for attachment
	);
	
	$field_name = $settings['field_name'];
	if (count($settings['parents'])) {
		$active_trail = acquia_arr_push_copy(array_slice($settings['parents'], 1), array($field_name, 'enabled') );
    $active_trail = $settings['parents'][0] . '[' . implode('][', $active_trail) . ']';
	}else {
		$active_trail = $field_name .'[enabled]';
	}
	
	if ($settings['always_enabled']) {
		$elements[$field_name .'-enabled'] = array(
			'#type' => 'value',
			'#value' => 1,
		);
	}else{
		$elements[$field_name .'-enabled'] = array(
			'#type' => 'checkbox',
			'#title' => t('Enable FontIcon for %field.', array('%field' =>  $settings['title'])),
			'#default_value' => $settings['enabled'],
		);
	}
	
	$elements[$field_name .'-enabled'] += array(
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'enabled') ),
	);
		
	$elements[$field_name] = array(
		'#type' => 'fieldset',
		'#title' => $settings['title'],
		'#description' => $settings['description'],
		'#prefix' => '<div class="ac-attachment-container '.$field_name.'-field">',
		'#suffix' => '</div>',
		'#collapsible' => $settings['collapsible'],
		'#collapsed' => $settings['collapsed'],

	);
	
	if (!$settings['always_enabled']) {
		$elements[$field_name]['#states'] = array(
				'enabled' => array(
						':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
				'visible' => array(
						':input[name="'.$active_trail.'"]' => array('checked' => TRUE),
				),
		);
	}
		
	$elements[$field_name]['icon'] = array(
		'#attributes' => array('class' => array('value-inject')),
		'#type' => 'hidden',
		'#default_value' => $settings['default'],
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'icon') ),
	);
	
	$elements[$field_name]['icon-filter'] = array(
		'#attributes' => array('class' => array('value-filter'), 'placeholder' => t('Search by icon name')),
		'#type' => 'textfield',
		'#title' => t('search'),
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'icon-filter') ),
	);
	
	$elements[$field_name]['icon-clone'] = array(
		'#attributes' => array('class' => array('value-select')),
		'#markup' => $attachment,
		'#prefix' => '<div class="ac-attachment-select ac-attachment-select-'.$settings['attachment_class'].'">',
		'#suffix' => '</div>',
		'#tree' => TRUE,
		'#parents' => acquia_arr_push_copy( $settings['parents'], array($field_name, 'icon-clone') ),
	);

	$elements[$field_name] += $settings['extra_elements'];
	return $elements;
}

