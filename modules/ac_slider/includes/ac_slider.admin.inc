<?php
/**
 * @file DiamondLayers slideshow admin
 */

/**
 * Create overview page for acquia slider
 */
function ac_slider_admin_overview() {
	acquia_include('utility', 'ac_slider');
	acquia_include('slider', 'ac_slider');
	
  $header = array(t('Title'), t('type'), array('data' => t('Operations'), 'colspan' => '4'));
  $rows = array();
  $results = acquiaSlider::get_all();
  foreach ($results as $slider) {
    $row = array(theme('ac_slider_overview', array('title' => $slider->title, 'description' => $slider->description)));
    $row[] = array('data' => t(get_slider_types($slider->type)));
    $row[] = array('data' => l(t('Edit'), SLIDER_LIST_PATH . '/'. $slider->slid . '/edit'));
    $row[] = array('data' => l(t('Configure'), SLIDER_LIST_PATH . '/'. $slider->slid . '/configure'));
    $row[] = array('data' => l(t('Delete'), SLIDER_LIST_PATH . '/slider/delete/confirm', array('query' => array('slid' => $slider->slid))));
    if (user_access('delete md_slider'))
      $row[] = array('data' => l(t('Clone'), SLIDER_LIST_PATH . '/'.  $slider->slid . '/clone', array('query'=> drupal_get_destination())));
    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}


/**
 * Create form to configure slideshow
 */
function ac_slider_configure_form($form, &$form_state, $slid = NULL) {
	acquia_include('utility');
	acquia_include('utility', 'ac_slider');
	acquia_include('slider', 'ac_slider');
	
	acquia_load_resources();
	
  $slider = NULL;
  $module_path = drupal_get_path('module', 'ac_slider');

	// load given slider settings
  if ($slid) {
    $slider = acquiaSlider::get_by_id($slid);
  }

  $form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Slider title'),
		'#default_value' => ($slider) ? $slider->title : '',
		'#description' => t('The title is not shown on the public site, just for the administrator to identify this slideshow.'),
		'#required' => TRUE,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine name'),
    '#default_value' => ($slider) ? $slider->machine_name : '',
    '#maxlength' => MENU_MAX_MENU_NAME_LENGTH_UI,
    '#description' => t('A unique name to identify for the menu. It must only contain lowercase letters, numbers and hyphens.'),
    '#machine_name' => array(
      'exists' => 'ac_slider_check_machine_name',
      'source' => array('title'),
      'label' => t('Machine name'),
      'replace_pattern' => '[^a-z0-9-]+',
      'replace' => '-',
    ),
    '#disabled' => ($slider && $slider->machine_name != ''),
  );

  $form['desc'] = array(
		'#type' => 'textarea',
		'#title' => t('Description'),
		'#default_value' => ($slider) ? $slider->description : '',
		'#resizable' => FALSE,
		'#description' => t('The description about this slider.'),
  );

  $form['type'] = array(
		'#type' => 'select',
		'#options' => array_merge(array('none' => t('select slider type')) , get_slider_types()),
		'#title' => t('Type'),
		'#default_value' => ($slider) ? $slider->type : '',
		'#description' => t('slider type.'),
		'#ajax' => array(
			'callback' => 'ac_slider_type_callback',
			'wrapper' => 'slider-settings',
		),
  );

  $form['settings'] = array(
		'#type' => 'fieldset',
		'#title' => t('settings'),
		'#description' => t('please select a slider type'),
		'#prefix' => '<div id="slider-settings">',
		'#suffix' => '</div>',
		'#collapsible' => true,
  ); 

	$default = array();
	$type = @$form_state['values']['type'];
	if ($slider) {
		$type = $slider->type;
		$default = array_merge((array)@$form_state['values'], $slider->settings);
	}
	
	if (isset($type) && in_array($type, array_keys(get_sliders_info()))){
		
		$settings = get_slider_info($type);
		if (isset($settings['#path']) && isset($settings['#file'])) {
			include_once $settings['#path'] .'/'. $settings['#file'];
		}

		// add settings form elements
		if (function_exists($settings['#form'])) {
			$settings = call_user_func_array($settings['#form'], array($default));
			if (is_array($settings)) {
				$form['settings'] += $settings;
			}
		}
		
		// add submit handlers
		if (isset($settings['#submit']) && function_exists($settings['#submit'])) {			
			$form['#submit'] +=$settings['#submit'];
		}

		// @todo add validator handlers
	}
	
	$form['id'] = array(
		'#type' => 'hidden',
		'#default_value' => ($slider) ? $slider->slid : -1,
  );

  $form['create'] = array(
		'#type' => 'submit',
		'#value' => ($slider) ? t('Save') : t('Create'),
  );

  if ($slider) {
    $form['save_edit'] = array(
      '#type' => 'submit',
      '#value' => t('Save & Edit'),
    );

    # Check user permission to show delete button
    if (user_access('delete ac_slider')) {
      $form['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
      );
    }
  }

  return $form;
}

/**
 * Handle submit form configure slider
 */
function ac_slider_configure_form_validate($form, &$form_state) {
	acquia_include('utility', 'ac_slider');
	$type = $form_state['values']['type'];
	if (!in_array($type, array_keys(get_sliders_info()))){
		form_set_error('type', t('you must choose a slider type!'));
	}
}

/**
 * Handle submit form configure slider
 */
function ac_slider_configure_form_submit($form, &$form_state) {
	acquia_include('utility', 'ac_slider');
  $custom = $form_state['values'];
	
  if ($custom['op'] == t('Delete')) {
    $form_state['redirect'] =  array(SLIDER_LIST_PATH .'/slider/delete/confirm', array('query' => array('slid' => $custom['id'])));
    return;
  }
	
	$info = get_sliders_info($custom['type']);
	require_once $info['#path'] . '/'. $info['#file'];

	// prepare settings;
	$settings = $info['#class']::prepare_settings($custom);

	// update
  if ($custom['id'] != -1) {
    $slider = acquiaSlider::get_by_id((int)$custom['id']);
    $slider->title = $custom['title'];
    $slider->description = $custom['desc'];
    //$slider->settings = $settings;
    $slider->type = $custom['type'];
    $slider->save();

    if ($custom['op'] == t('Save')) {
      $form_state['redirect'] = SLIDER_LIST_PATH;
    }
    else {
      $_GET['destination'] = NULL;
      $form_state['redirect'] = SLIDER_LIST_PATH. '/' . $custom['id'] . '/edit';
    }

    $action = "updated configurations.";
  }
  else {
    $slider = $info['#class']::create($custom['title'], $custom['desc'], $custom['type'], $settings, $custom['machine_name']);
    $form_state['redirect'] = SLIDER_LIST_PATH. '/' . $slider->slid . '/edit';

    if ($slider)
      $action = "created.";
    else
      $action = "created fail.";
  }
	
  if ($slider)
    drupal_set_message(t("acquiaSlider: '{$slider->title}' has been {$action}"));
  else
    drupal_set_message(t("acquiaSlider: '{$custom['title']}' has been {$action}"));
}

/**
 * Manage form for slider
 */
function ac_slider_manage($slid, $option='configure') {
	acquia_include('utility', 'ac_slider');
	acquia_include('slider', 'ac_slider');
	
  $form['ac_slider'] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
  );
  if ($option == 'edit') {
    drupal_set_title(t('Edit Slider: ' . $slid[0]));
		$slider = acquiaSlider::get_by_id((int)$slid[0]);
		$info = get_slider_info($slider->type, null, '#slides');
		// clear the cache of sliders
		if (isset($_POST['slider_edit']) && $_POST['slider_edit'] == 1) {
			acquia_include('debug');

			$cids = array(
				'content' => ac_slider_generate_cid((int)$_POST['slid']),
				'js' => ac_slider_generate_cid((int)$_POST['slid'], 'js'),
				'css' => ac_slider_generate_cid((int)$_POST['slid'], 'css'),
			);

			foreach ($cids as $cid) {
				cache_clear_all($cid, 'cache_acquia_sliders');
			}
		}
		
		return call_user_func_array($info['#edit'], array($slider->slid));
  }
  elseif ($option == 'configure') {
    drupal_set_title(t('Configure - acquia Slider: ' . $slid[0]));
    $data = drupal_get_form('ac_slider_configure_form', $slid);
		 return array(
      '#type' => 'markup',
      'markup' => $data,
    );
  }

}

/**
 * Create slider edit form
 */
function ac_slider_edit_form($form, &$form_state, $slid) {
	acquia_include('slider', 'ac_slider');
	
  $module_path = drupal_get_path('module', 'ac_slider');

  # Remove last breadcrumb
  $breadcrumb = drupal_get_breadcrumb();
  unset($breadcrumb[count($breadcrumb)-1]);
  drupal_set_breadcrumb($breadcrumb);

  $slider = acquiaSlider::get_by_id($slid);
  $settings = acquiaSlider::get_default_settings();
  if ($slider == NULL) {
    $form['slider_msg'] = array(
      '#markup' => '<h3>This slider not exist. Please try again!</h3>',
    );

    return $form;
  }
  $settings = array_merge($settings, $slider->settings);

  $form['slider_main'] = array(
    '#markup' => theme('slider_edit_form', array('slider' => $slider)),
  );

  $form['slider_id'] = array(
    '#type' => 'hidden',
    '#default_value' => $slid,
  );

  $form['slider_data_save'] = array(
    '#type' => 'textarea',
    '#default_value' => '',
    '#resizable' => FALSE,
  );

  $form['color_saved'] = array(
    '#type' => 'hidden',
    '#default_value' => $settings['color_saved'],
  );

  $form['slider_save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['slider_save_continue'] = array(
    '#type' => 'submit',
    '#value' => t('Save & Continue'),
  );

  return $form;
}

/**
 * Import and export form
 */
function ac_slider_import_export_form($form, &$form_state) {
	acquia_include('theme');
	acquia_include('utility', 'ac_slider');
	acquia_include('slider', 'ac_slider');
	// Load resources
	acquia_load_resources('admin');
	acquia_add_vertical_tabs_style($form);
	acquia_theme_wrap_acquia_admin_style($form, array('title' => t('DiamondLayers Sliders Import/Export')));
	
	$form['ac_slider_export_import'] = array(
		'#type' => 'vertical_tabs',
		'#title' =>'',
	);
	
  # Get all CuteSliders are existing
  $sliders = acquiaSlider::get_all();
  $sliders_options = array();
  foreach ($sliders  as $slider) {
    $sliders_options[$slider->slid] = $slider->title;
  }
	
  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export'),
    '#collapsible' => true,
		'#group' => 'ac_slider_export_import',
  );
 
  $form['export']['sliders'] = array(
    '#type' => 'radios',
    '#title' => t('Choose sliders to export'),
    '#options' => $sliders_options,
    '#default_value' => array(),
    '#ajax' => array(
      'callback' => 'ajax_export_slider_callback',
      'wrapper' => 'export-data',
		),
  );

  $form['export']['export-data'] = array(
    '#title' => t("Export Data"),
    '#prefix' => '<div id="export-data" style="max-width: 960px">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
    '#description' => t('Please select some sliders to export.'),
  );

 
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import'),
    '#collapsible' => true,
    '#collapsed' => true,
		'#group' => 'ac_slider_export_import',
  );

  $form['import']['machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#default_value' => '',
    '#description' => t('Enter the machine name to use for this acquiaSlider. It must only contain lowercase letters, numbers and hyphens.'),
    '#resizable' => FALSE,
  );

  $form['import']['slider_type'] = array(
    '#type' => 'select',
    '#title' => t('slider type'),
    '#default_value' => isset($form_state['values']['slider_type']) ? $form_state['values']['slider_type'] : '',
    '#description' => t('select the slider type of the data.'),
    '#options' => array_merge(array('none' => t('select slider type')) , get_slider_types()),
  );

	$form['import']['import_data'] = array(
    '#type' => 'textarea',
    '#title' => t('Import data'),
    '#default_value' => isset($form_state['values']['import_data']) ? $form_state['values']['import_data'] : '',
    '#description' => t('Paste acquiaSlider data export from another site here to import in this site.'),
    '#resizable' => FALSE,
  );

  $form['import']['import_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#submit' => array('ac_slider_import_submit'),
  );

  $form['sample_import'] = array(
    '#type' => 'fieldset',
    '#title' => t('sample sliders'),
    '#description' => t('Here you can import sample sliders'),
    '#collapsible' => true,
    '#collapsed' => true,
		'#group' => 'ac_slider_export_import',
  );
	
	$sliders = array();
	foreach (ac_slider_get_import_sample_slider_list() as $type => $info) {
		$sliders[$type] = $info['title'];
	}
	
  $form['sample_import']['import_slider'] = array(
    '#type' => 'select',
    '#title' => t('Select slider type to import'),
		'#options' => $sliders,
  );

  $form['sample_import']['import_sample'] = array(
    '#type' => 'submit',
    '#value' => t('Import sample'),
    '#submit' => array('ac_slider_import_sample'),
  );
	
  //drupal_add_js(drupal_get_path('module', 'ac_slider') . '/js/acquia-slider-export.js');

  return $form;
}

/**
 * Handle submit import form
 */
function ac_slider_import_sample($form, &$form_state) {
  if (!isset($form_state['values']['slider_type'])) {
    return form_set_error('machine_name', t('No slider type is selected for sample import!'));
  }
	$slider = $form_state['values']['slider_type'];
	$sample_import_list = ac_slider_get_import_sample_slider_list();
  if (!isset($sample_import_list[$slider])) {
    return form_set_error('selected slider is not valid!');
  }
	
	if (function_exists($sample_import_list[$slider]['import'])) {
		if(call_user_func($sample_import_list[$slider]['import'])) {
			drupal_set_message('importing sample slider was sucessful.');
		}else{
			form_set_error('importing sample slider failed!');
		}
	}
}

function ac_slider_get_import_sample_slider_list(){
	$cache = &drupal_static(__FUNCTION__, null);
	
	if (!isset($cache)) {
		foreach (module_implements('ac_slider_import_sample') as $module) {
			$sample_info = module_invoke($module, 'ac_slider_import_sample');
			foreach ($sample_info as $type => $info) {
				$cache[$type] = $info;
			}
		}
	}
	
	return $cache;
}

/**
 * Handle submit import form
 */
function ac_slider_import_submit($form, &$form_state) {
  if ($form_state['values']['machine_name'] != '' && !preg_match('/^[a-z0-9\-]{1,}$/', $form_state['values']['machine_name'])) {
    return form_set_error('machine_name', t('Machine name do not valid.'));
  }
	acquia_include('utility');
	acquia_include('slider', 'ac_slider');
	acquia_include('utility', 'ac_slider');

  $import_data = $form_state['values']['import_data'];
  $mn = isset($form_state['values']['machine_name']) ? $form_state['values']['machine_name'] : NULL;
  $type = $form_state['values']['slider_type'];
  if ($import_data == '') {
    drupal_set_message(t('acquiaSlider: Data import is invalided.'), 'error');
    return;
  }
	
	if ( isset($type) && $type != 'none' ) {
		$info = get_slider_info( $type, null, '#import_export' );

		// add settings form elements
		if ( isset($info['#import']) && function_exists($info['#import']) ) {
			$slider_data = call_user_func_array($info['#import'], array($import_data, $type, $mn));
		}else {
			drupal_set_message(t('acquiaSlider: function %f for import is not exists!', array('%f' => $info['#import'])));
		}
	}else {
		$slider_data = drupal_json_decode($import_data);
	}
	
	if (empty($mn) && isset($slider_data['title']) && !empty($slider_data['title'])) {
		$mn = machine_name($slider_data['title']);
	}

  if (!isset($slider_data['title']) || !isset($slider_data['machine_name']) || !isset($slider_data['description'])
		|| !isset($slider_data['type']) || !isset($slider_data['settings']) || !isset($slider_data['slides'])) {
    drupal_set_message(t('acquiaSlider: Data import is invalided.'), 'error');
    return;
  }

  # Check machine name
  if ($mn == '' && ac_slider_check_machine_name($slider_data['machine_name'])) {
    drupal_set_message(t('A acquiaSlider by that machine name already exists; please choose a different machine name'), 'error');
    return;
  }
  # Add slider in database
  $slider = acquiaSlider::create($slider_data['title'], $mn,  $slider_data['type'], $slider_data['settings']);
  if (!$slider) {
    drupal_set_message(t('acquiaSlider: Import ' . $slider_data['title'] . ' was unsuccessful.'), 'error');
    return;
  }

  foreach ($slider_data['slides'] as $index => $slide_data) {
    if (!isset($slide_data['position']) || !isset($slide_data['settings']) || !isset($slide_data['layers']))
      continue;
    acquiaSlide::create($slider->slid, $slide_data['position'], $slide_data['settings'], $slide_data['layers']);
  }
	
  drupal_set_message(t('acquiaSlider: Import successfull.'));
}


/************************************************************************/
/* AJAX CALLBACKS */
/************************************************************************/

/**
 * Clone slider callback
 */
function ajax_export_slider_callback(&$form, &$form_state) {
	$form['export']['export-data']['data'] = array(
    '#type' => 'textarea',
    '#title' => t('data'),
    '#value' => (string) ac_slider_get_export_data($form_state['values']['sliders']),
    '#resizable' => true,
  );
	
	return $form['export']['export-data'];
}

/**
 * Implements theme md_slider_overview
 */
function ac_slider_type_callback(&$form, $form_state) {
	return $form['settings'];
}

/************************************************************************/
/* UTILS */
/************************************************************************/


/**
 * Get Export data of given slider(s)
 * 
 * @param array $slid
 * 	array of sliders id
 *
 * @return An String of sliders data
 */
function ac_slider_get_export_data($slid) {
	acquia_include('utility', 'ac_slider');
	
	$slider = acquiaSlider::get_by_id((int)$slid);
	$slides = acquiaSlide::get_by_slider_id((int)$slid);
	$out = '';
	if ( in_array($slider->type, array_keys(get_sliders_info())) ) {
		$info = get_slider_info($slider->type, null, '#import_export');
		// add settings form elements
		if (isset($info['#export']) && function_exists($info['#export'])) {
			$out = call_user_func_array($info['#export'], array($slider, $slides));
		}else {
			drupal_set_message(t('ac_slider: function %f for export is not exists!', array('%f' => $info['#export'])));
		}
	}else {
			$slider_data = array(
			'title' => $slider->title,
			'machine_name' => $slider->machine_name,
			'description' => $slider->description,
			'type' => $slider->type,
			'settings' => $slider->settings);
			
			$slider_data['slides'] = ac_slider_get_slides_data($slider->slid, $slides);
			
			$out = drupal_json_encode($slider_data);
		}
    return $out;
}

/**
 * Get slider slides data
 */
function ac_slider_get_slides_data($slid, &$slides) {
  $output = array();
  foreach ($slides as $key => $slide) {
    if ($slide->slid == $slid) {
      $output[] = array('position' => $slide->position, 'settings' => $slide->settings, 'layers' => $slide->layers);
      unset($slides[$key]);
    }
  }

  return $output;
}

/**
 * Clone slider callback
 */
function ac_slider_clone($slid) {
	acquia_include('slider', 'ac_slider');
	
  $org_slider = acquiaSlider::get_by_id($slid[0]);
  $clone = acquiaSlider::create("clone of " . $org_slider->title, $org_slider->description, $org_slider->type, $org_slider->settings);
  $classes = array();

  $org_slides = acquiaSlide::get_by_slider_id($slid[0]);
  foreach ($org_slides as $index => $slide) {
    acquiaSlide::create($clone->slid, $slide->position, $slide->settings, $slide->layers);
  }

  drupal_set_message(t("Clone acquiaSlider: '{$org_slider->title}' successful."));
  drupal_goto(drupal_get_destination());
}

/**
 * Implements delete slide from database
 */
function delete_slide() {
	acquia_include('slider', 'ac_slider');
  $sid = $_POST['sid'];
  if (acquiaSlider::delete($sid)) {
    print "OK";
  }
  else {
    print "Can not delete slide: {$sid}";
  }
}

/**
 * Create form to confirm delete slider
 */
function confirm_delete_form($form, &$form_state) {
	if (!isset($_GET['slid']) || empty($_GET['slid'])) {
		return;
	}
	acquia_include('slider', 'ac_slider');
	
  $slider = acquiaSlider::get_by_id($_GET['slid']);

  drupal_set_title('Are you sure want to delete this slider?');
  $form['info'] = array(
    '#markup' => '<div class="info"><h3>'.$slider->title .'</h3></div>',
  );
	
	$form['confirm_del'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  $form['confirm_del_slid'] = array(
    '#type' => 'hidden',
    '#default_value' => $_GET['slid'],
  );

  $form['confirm_cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );

  return $form;
}

/**
 * Handle submit confirm delete slider form
 */
function confirm_delete_form_submit($form, &$form_state) {
  $custom = $form_state['values'];

  if ($custom['op'] == 'Delete') {
		acquia_include('slider', 'ac_slider');
    unset($_GET['destination']);
    if (acquiaSlider::delete($custom['confirm_del_slid']))
      drupal_set_message(t("Slider has been deleted."));
    else
      drupal_set_message(t("Slider has been deleted fail."));

    $form_state['redirect'] = SLIDER_LIST_PATH;
  }
  else {
    $form_state['redirect'] = SLIDER_LIST_PATH . "/{$custom['confirm_del_slid']}";
  }
}


/************************************************************************/
/* THEME FUNCTIONS */
/************************************************************************/

/**
 * Implements theme md_slider_overview
 */
function theme_ac_slider_overview($variables) {
  $output = check_plain($variables['title']);
  $output .= '<div class="despcription">' . filter_xss_admin($variables['description']) . '</div>';

  return $output;
}

/************************************************************************/
/* MISC FUNCTIONS */
/************************************************************************/

/**
 * Callback to check machine name of slider
 */
function ac_slider_check_machine_name($machine_name) {
	acquia_include('slider', 'ac_slider');
  return count(acquiaSlider::get_by_machine_name($machine_name));
}