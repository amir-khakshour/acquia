<?php

function ac_megamenu_admin_settings($form) {
  acquia_include('utility', 'ac_megamenu');

  $menus = ac_megamenu_get_megamenus();
  foreach ($menus as $menu) {
    $form[$menu->menu_name]['#ac_megamenu'] = $menu;
    $form[$menu->menu_name]['menu_name'] = array('#markup' => $menu->menu_name);
    $form[$menu->menu_name]['title'] = array('#markup' => $menu->title);
    $form[$menu->menu_name]['config_megamenu'] = array('#type' => 'link', '#title' => t('Config'), '#href' => AC_MEGAMENU_ADMIN_PATH . "/$menu->menu_name");
    $form[$menu->menu_name]['config_links'] = array('#type' => 'link', '#title' => t('Edit links'), '#href' => "admin/structure/menu/manage/$menu->menu_name");
  }
  return $form;
}


function theme_ac_megamenu_admin_settings($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#ac_megamenu'])) {
      $menu = &$form[$key];
      $menu['enabled']['#parents'] = array($key, 'enabled');
      $menu['enabled']['#name'] = $key . "[enabled]";
      $row = array();
      $row[] = drupal_render($menu['menu_name']);
      $row[] = drupal_render($menu['title']);
      $row[] = drupal_render($menu['config_megamenu']);
      $row[] = drupal_render($menu['config_links']);
      $rows[] = $row;
    }
  }
  $header = array(t('Menu Name'), t('Menu Title'));
  $header[] = array('data' => t('Operations'), 'colspan' => 2);
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No MegaMenu block available. <a href="@link">Add MegaMenu Block</a>.', array('@link' => url('admin/config/user-interface/ac_megamenu/add'))), 'attributes' => array('id' => 'ac_megamenu'))) . drupal_render_children($form);
}


function ac_megamenu_configure_form($form, &$form_state, $menu_names = array()) {
  acquia_include('utility', 'ac_megamenu');

  // Load resources
  acquia_load_resources('admin');
  acquia_load_resources('modal');
  acquia_load_resources('mediabrowser');
  acquia_load_resources('admin-shortcodes');
  drupal_add_library('acquia', 'fontello');
  drupal_add_library('system', 'ui.droppable');
  drupal_add_library('system', 'ui.draggable');

  if(module_exists('chosen') && file_exists(libraries_get_path('chosen') . '/chosen/chosen.css')) {
    ac_megamenu_add_css(libraries_get_path('chosen') . '/chosen/chosen.css');
  }
  else {
    ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/chosen/chosen.css');
  }
  ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/bootstrap.css');
  ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/base.css');
  ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/admin.css');
  ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/admin_custom.css');
  ac_megamenu_add_css(drupal_get_path('module', 'ac_megamenu') . '/css/backend.css');
  if(module_exists('chosen') && file_exists(libraries_get_path('chosen') . '/chosen/chosen.jquery.js')) {
    drupal_add_js(libraries_get_path('chosen') . '/chosen/chosen.jquery.js');
  }
  else {
    drupal_add_js(drupal_get_path('module', 'ac_megamenu') . '/js/chosen.jquery.js');
  }

  drupal_add_js(drupal_get_path('module', 'ac_megamenu') . '/js/ac-megamenu-backend.js');
  drupal_add_js(drupal_get_path('module', 'ac_megamenu') . '/js/ac-megamenu-object.js');

  if(!empty($menu_names)) {
    $form['ac_megamenu'] = array(
        '#markup' => theme('ac_megamenu_backend', array(
            'menu_name' => $menu_names[0],
        )),
    );
  }
  return $form;
}
