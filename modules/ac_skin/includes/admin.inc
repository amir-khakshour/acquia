<?php
/**
 * Provide a single block from the administration menu as a page.
 *
 * This function is often a destination for these blocks.
 * For example, 'admin/structure/types' needs to have a destination to be valid
 * in the Drupal menu system, but too much information there might be
 * hidden, so we supply the contents of the block.
 *
 * @return
 *   The output HTML.
 */
function ac_skin_generator_form($form, &$form_state) {
  acquia_include('utility');
  acquia_include('theme');
  acquia_include('skin', 'ac_skin');
  // Load resources
  acquia_load_resources('admin');
  drupal_add_js(drupal_get_path('module', 'ac_skin') . '/js/admin.js');
  drupal_add_css(drupal_get_path('module', 'ac_skin') . '/css/skin-admin.css');

  acquia_add_vertical_tabs_style($form);
  acquia_theme_wrap_acquia_admin_style($form, array('title' => t('Diamond skin generator')));

  $form['ac_skin_generator'] = array(
	'#type' => 'vertical_tabs',
	'#title' =>'',
  );

  if ($skins = acquia_theme_skin_info()) {
	$form['acquia_skin'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Use built-in skins'),
	  '#description' => t('You can set your default skin to one of the built-in skins.'),
	  '#tree' => TRUE,
	  '#group' => 'ac_skin_generator',
	);

	$form['acquia_skin']['skin'] = array(
	  '#type' => 'radios',
	  '#options' => array(),
	  '#title' => t('Choose a skin'),
	  '#default_value' => acquia_variable_get('default_skin'),
	);
	foreach ($skins as $skin => $info) {
	  $form['acquia_skin']['skin']['#options'][$skin] = $info['name'];
	  $form['acquia_skin']['skin'][$skin]['#description'] = $info['description'];

	  if (isset($info['uri']) && isset($info['screenshot']) && is_string($info['screenshot'])) {
		$screenshot = file_create_url($info['uri'] . '/' . $info['screenshot']);
		$form['acquia_skin']['skin'][$skin]['#prefix'] = '<div class="ac-skin-selection-wrapper">';
		$form['acquia_skin']['skin'][$skin]['#suffix'] = '<span class="skin-accent-color" style="background:'.$info['accent-color'].'"></span>';
		$form['acquia_skin']['skin'][$skin]['#suffix'] .= '<spa class="skin-accent-title">'.t($info['name']).'</span>';
		$form['acquia_skin']['skin'][$skin]['#suffix'] .= '<span class="ac-skin-screenshot"><i></i><img src="' . $screenshot . '" /></div>';
	  }
	}

	$form['acquia_skin']['submit'] = array(
	  '#prefix' => '<div class="form-actions form-wrapper" id="edit-actions">',
	  '#suffix' => '</div>',
	  '#type' => 'submit',
	  '#value' => t('Use skin'),
	  '#submit' => array('acquia_use_skin'),
	);
  }

  /** Genertor */
  $defaults = acquia_variable_get('skin_generator', array());
  $defaults += array(
	'name' => '',
	'description' => '',
	'version' => '',
	'author' => '',
	'screenshot' => array(),
  );

  $form['skin_generator'] = array(
	'#type' => 'fieldset',
	'#title' => t('Skin Generator'),
	'#description' => t('You can save current theme settings as a Skin for AURA.'),
	'#tree' => TRUE,
	'#group' => 'ac_skin_generator',
  );

  $form['skin_generator']['name'] = array(
	'#type' => 'textfield',
	'#title' => t('name'),
	'#description' => t('Example: Minimal (Do not begin name with numbers.)'),
	'#default_value' => $defaults['name'],
  );

  $form['skin_generator']['description'] = array(
	'#type' => 'textfield',
	'#title' => t('description'),
	'#description' => t('Provide a short description of how skin looks like!'),
	'#default_value' => $defaults['description'],
  );

  $form['skin_generator']['version'] = array(
	'#type' => 'textfield',
	'#title' => t('Version'),
	'#description' => t('Examples: 1.x.0'),
	'#default_value' => $defaults['version'],
  );

  $form['skin_generator']['author'] = array(
	'#type' => 'textfield',
	'#title' => t('Author'),
	'#description' => '',
	'#default_value' => $defaults['author'],
  );

  $form['skin_generator']['screenshot'] = array(
	'#type' => 'media',
	'#title' => t('A screenshot of your skin'),
	'#description' => '',
	'#default_value' => $defaults['screenshot'],
	'#media_options' => array(
	  'global' => array(
		'types' => array('image'),
	  ),
	),
  );

  $form['skin_generator']['submit'] = array(
	'#prefix' => '<div class="form-actions form-wrapper" id="edit-actions">',
	'#suffix' => '</div>',
	'#type' => 'submit',
	'#value' => t('Generate skin'),
	'#submit' => array('acquia_generate_skin'),
  );

  return $form;
}

/**
 *
 */
function acquia_use_skin($form, &$form_state){
  acquia_include('skin', 'ac_skin');

  $values = $form_state['values'];
  $skin = isset($form_state['values']['acquia_skin']['skin']) ? $form_state['values']['acquia_skin']['skin'] : NULL;
  acquia_variable_set('default_skin', $skin);
  if (empty($skin)) {
	return form_set_error('acquia_skin', t('Please select a skin!'));
  }

  $skins = acquia_theme_skin_info();

  if (!isset($skins[$skin])) {
	return form_set_error('acquia_skin', t('Selected skin is not valid!'));
  }
  $info = $skins[$skin];

  $cofig_path = drupal_realpath($info['uri'] . 'config.json');
  if (is_file($cofig_path) && $file_contents = file_get_contents($cofig_path)) {
	$config = @drupal_json_decode($file_contents);
	if (is_array($config) && !empty($config)) {
	  acquia_skin_override_theme_settings($config);
	}
  }

  // override skin css content to the skin.css file
  $css_path =  drupal_realpath($info['uri'] . 'skin.css');
  if (is_file($css_path) && $css = file_get_contents($css_path)) {
	$file = variable_get('acquia_theme_custom_css', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/css/skin.css');

	if (!file_unmanaged_save_data($css, $file, FILE_EXISTS_REPLACE)) {
	  drupal_set_message('Overriding auto generated skin file to the theme skin.css file was unsucesful!');
	}
  }

  // override custom-skin.css file to the theme custom-skin.css file
  $css_path =  drupal_realpath($info['uri'] . 'custom-skin.css');
  if (is_file($css_path) && $css = file_get_contents($css_path)) {
	$file = variable_get('acquia_theme_custom_skin_css', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/css/custom-skin.css');

	if (!file_unmanaged_save_data($css, $file, FILE_EXISTS_REPLACE)) {
	  drupal_set_message('Overriding Custom skin file to the theme skin.css file was unsucesful!');
	}
  }

  // override custom-skin.sass file to the theme custom-skin.sass file
  $css_path =  drupal_realpath($info['uri'] . 'custom-skin.scss');
  if (is_file($css_path) && $css = file_get_contents($css_path)) {
	$file = variable_get('acquia_theme_custom_skin_sass', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/sass/custom-skin.scss');

	if (!file_unmanaged_save_data($css, $file, FILE_EXISTS_REPLACE)) {
	  drupal_set_message('Overriding Custom skin file to the theme skin.css file was unsucesful!');
	}else{
	  drupal_set_message(t('Changed default skin to @skin!', array('@skin' => $skin)));
	}
  }

}


function ac_skin_generator_form_submit($form, &$form_state) {
  //$values = $form_state['values'];
}

/**
 * @todo
 */
function ac_skin_config_skin_settings_form_submit($form, &$form_state) {
  // Interpolate group skin styles with old skin styles
  acquia_include('skin', 'ac_skin');
  ac_skin_save_new_skin_styles($form_state['values']['acquia']['skin']);
  drupal_set_message(t('Your skin settings has been successfully saved!'), 'status');
}
/**
 * @todo
 */
function ac_skin_config_skin_settings_form($form, &$form_state, $group) {
  acquia_include('utility');
  acquia_include('theme');
  acquia_include('utility', 'ac_skin');
  acquia_include('form', 'ac_skin');

  // Load resources
  acquia_load_resources('admin');
  drupal_add_js(drupal_get_path('module', 'ac_skin') . '/js/admin.js');
  drupal_add_css(drupal_get_path('module', 'ac_skin') . '/css/skin-admin.css');
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'ui.slider');

  drupal_add_js('
    (function ($) {
      Drupal.AC_SKIN = Drupal.AC_SKIN || {};
      Drupal.AC_SKIN.ajax_URL = "' . ACQUIA_SKIN_AJAX_URL . '";
    })(jQuery);
  ', 'inline');

  $forms = ac_skin_get_all_group_styles();
  $def = ac_skin_get_theme_skin_items();
  if (isset($forms[$group]) && !empty($forms[$group])) {
	$group_form_arr = $forms[$group];
	// load assets
	ac_skin_add_skin_assets();
	ac_skin_styles_wrap_acquia($form);

	// wrap acquia options style
	acquia_add_vertical_tabs_style($form);
	acquia_theme_wrap_acquia_admin_style($form, array('title' => t('@group skin settings', array('@group' => $def[$group]['title']))));


	$form['ac_skin_group_' .$group] = array(
	  '#type' => 'vertical_tabs',
	  '#title' => t('@group Settings', array('@group' => $def[$group]['title'])),
	);

	// saved values
	$scheme_values = acquia_theme_get_settings('scheme', array(), 'skin');

	$typo_values = acquia_theme_get_settings('typo', array(), 'skin');
	foreach ($group_form_arr as $element => $settings) {
	  // Add scheme styles
	  if (isset($settings['scheme']) && is_array($settings['scheme'])) {

		$form[$element] = array(
		  '#type' => 'fieldset',
		  '#title' => t('@type', array('@type' => $settings['title'])),
		  '#collapsible' => TRUE,
		  '#collapsed' => TRUE,
		  '#group' => 'ac_skin_group_' .$group,
		);

		$form[$element]['scheme'] = array(
		  '#type' => 'fieldset',
		  '#title' => t('Scheme'),
		  '#parents' => array('acquia', 'skin', 'scheme', $element),
		  '#tree' => TRUE,
		  '#collapsible' => TRUE,
		  '#collapsed' => FALSE,
		  '#description' => ac_skin_demo_box(array($element)),
		);

		foreach ($settings['scheme'] as $attr => $def) {
		  if (isset($def['type']) && function_exists('ac_skin_format_' . $def['type'] . '_element')) {
			$sub = call_user_func_array('ac_skin_format_' . $def['type'] . '_element', array($group, $element, $attr, $scheme_values[$element], 'scheme'));
			if ($def['type'] == 'rgba_color' && isset($sub['ie'])) {
			  $sub['ie']['#states']['invisible'] = array(':input[name="acquia[skin][scheme]['.$element.']['.$attr.'][opacity]"]' => 100);
			  $sub['ie']['#states']['disabled'] = array(':input[name="acquia[skin][scheme]['.$element.']['.$attr.'][opacity]"]' => 100);
			}
			$form[$element]['scheme'][$attr] = $sub;
		  }
		}
	  }

	  if (isset($settings['typo']) && is_array($settings['typo'])) {

		if (!isset($form[$element])) {
		  $form[$element] = array(
			'#type' => 'fieldset',
			'#title' => t('@type', array('@type' => $settings['title'])),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
			'#group' => 'ac_skin_group_' .$group,
		  );
		}

		$form[$element]['typo'] = array(
		  '#type' => 'fieldset',
		  '#title' => t('Typography'),
		  '#parents' => array('acquia', 'skin', 'typo', $element),
		  '#tree' => TRUE,
		  '#collapsible' => TRUE,
		  '#collapsed' => FALSE,
		  '#description' => ac_skin_demo_box(array($element)),
		);

		foreach ($settings['typo'] as $attr => $def) {
		  if (isset($def['type']) && function_exists('ac_skin_format_' . $def['type'] . '_element')) {
			$sub = call_user_func_array('ac_skin_format_' . $def['type'] . '_element', array($group, $element, $attr, $typo_values[$element], 'typo'));
			$form[$element]['typo'][$attr] = $sub;
			//if (isset($settings['parent'])) {
			//	$form[$settings['parent']][$element][$attr] = $sub;
			//}else{
			//	$form[$element]['container'][$attr] = $sub;
			//}
		  }
		}

	  }
	}

	$form['submit'] = array(
	  '#prefix' => '<div class="form-actions form-wrapper" id="edit-actions">',
	  '#suffix' => '</div>',
	  '#type' => 'submit',
	  '#value' => t('Save settings'),
	  //'#submit' => array('acquia_use_skin'),
	);
	return $form;
  }
}

/**
 * AJAX callback for acquia skin
 */
function ac_skin_ajax_callback(){
  $action = isset($_POST['action']) ? $_POST['action'] : '';
  switch ($action) {
	case 'load_theme_font':
	  if (!isset($_POST['font'])) {
		return;
	  }
	  acquia_include('utility', 'ac_skin');
	  $fonts = ac_skin_load_theme_font($_POST['font']);
	  $styles = drupal_get_css();
	  $output[] = ajax_command_prepend('head', $styles);
	  print ajax_render($output);
	  break;
  }
}