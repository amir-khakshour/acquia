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
function acquia_general_setting($form, &$form_state) {
  $form = array();
  acquia_load_resources('admin');

  $form['general_settings'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('ac-admin')),
  );

  $form['general_settings']['404_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('404 page settings'),
    '#collaspible' => TRUE,
  );

  $form['general_settings']['404_page']['404_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('enter 404 pages title.'),
    '#default_value' => acquia_variable_get('404_page_title', 'Page Not Found'),
  );

  $form['general_settings']['404_page']['404_page_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Text'),
    '#description' => t('Enter a descriptive text for 404 text.'),
    '#default_value' => acquia_variable_get('404_page_text', 'The page you requested does not exist'),
    '#rows' => 10,
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save settings'),
  );
  return $form;
}

function acquia_general_setting_submit($form, &$form_state) {
  $values = $form_state['values'];
  acquia_variable_set('404_page_title', $values['404_page_title']);
  acquia_variable_set('404_page_text', $values['404_page_text']);
}


function acquia_refresh_setting($form, &$form_state) {

  //refresh theme settings
  if (variable_get('ACQUIA_BASE_THEME')) {
    // DiamondLayers theme framework base path
    variable_set('ACQUIA_TF_BASE_PATH', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/includes/acquia');

    // Skin Path
    acquia_variable_set('theme_presets', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/includes/acquia/presets');

    // Skin Path
    acquia_variable_set('theme_skins_dir', drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/includes/acquia/presets/skins');

    // DiamondLayers framework base URL
    variable_set('ACQUIA_BASE_URL', url(drupal_get_path('theme', variable_get('ACQUIA_BASE_THEME')) . '/includes/acquia',
      array('absolute' => true)));
  }

  drupal_flush_all_caches();

  drupal_set_message('DiamondLayers settings refreshed successfully!');
  drupal_goto('admin');
}