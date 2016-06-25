<?php

function ac_megamenu_request() {
  $action = isset($_POST['action']) ? $_POST['action'] : NULL;

  switch($action) {
    case 'load':
      $block = ac_megamenu_render_block($_POST['menu_name']);
      print($block['content']['#markup']);
      break;
    case 'save':
      $menu_config = isset($_POST['menu_config']) ? $_POST['menu_config'] : NULL;
      $block_config = isset($_POST['block_config']) ? $_POST['block_config'] : NULL;
      $menu_name = isset($_POST['menu_name']) ? $_POST['menu_name'] : NULL;
      if($menu_config && $menu_name) {
        $ac_megamenu = db_select('acquia_megamenus', 't')->fields('t')->condition('menu_name', $menu_name)->execute()->fetchObject();
        if($ac_megamenu) {
          db_update('acquia_megamenus')->fields(array('menu_config' => $menu_config, 'block_config' => $block_config))->condition('menu_name', $menu_name)->execute();
        }
        else {
          db_insert('acquia_megamenus')->fields(array('menu_name' => $menu_name, 'block_config' => $block_config, 'menu_config' => $menu_config))->execute();
        }
      }
      break;
    case 'load_block':
      $block_key = isset($_POST['block_key']) ? $_POST['block_key'] : NULL;
      $id = isset($_POST['id']) ? $_POST['id'] : NULL;
      $showblocktitle = isset($_POST['showblocktitle']) ? $_POST['showblocktitle'] : NULL;
      if($block_key) {
        $content = json_encode(array('content' => theme('ac_megamenu_block', array('block_key' => $block_key, 'section' => 'backend', 'showblocktitle' => $showblocktitle)), 'id' => $id));
        print($content);
      }
      break;
    case 'load_font_icons':
      ctools_include('ajax');
      acquia_include('modal');
      acquia_include('utility', 'ac_shortcode');
      $form_state = array(
        'ajax' => TRUE,
        'cache' => TRUE,
        'title' => t("Select icon for menu item"),
      );
    
      if (isset($_POST['icon']) && !empty($_POST['icon'])) {
        $form_state['values']['icon'] = $_POST['icon'];
      }
      
      if (isset($_POST['mid']) && !empty($_POST['mid'])) {
        $form_state['values']['mid'] = $_POST['mid'];
      }
    
      $output = array();
    
      $form_id = 'ac_megamenu_icon_fonts_form';
      $form = $form_id(array(), $form_state);
      
      if ( isset($form['#attached']) && isset($form['#attached']['css']) ) {
        $styles = $form['#attached']['css'];
        $styles = drupal_get_css($styles);
        $output[] = ajax_command_prepend('head', $styles);
      }
      
      if ( isset($form['#attached']) && isset($form['#attached']['js']) ) {
        $scripts = $form['#attached']['js'];
        $scripts = drupal_get_js('header', $scripts);
        $output[] = ajax_command_prepend('head', $scripts);
      }
      
      $modal = acquia_modal_form_wrapper($form_id, $form_state);
      $output[] = array_shift($modal);
    
      if (!empty($form_state['executed']) && $form_state['clicked_button']['#value'] == t('submit')) {
        acquia_include('process', 'ac_shortcode');
        // We'll just overwrite the form output if it was successful.
        $output = array();
        $values = $form_state['values'];
        $mid = isset($values['mid']) ? $values['mid'] : '';
        $icon = isset($values['fonticon']['icon']) ? $values['fonticon']['icon'] : '';
        $output[] = ac_megamenu_command_update_fonticon($mid, $icon);
        $output[] = acquia_modal_command_dismiss();
      }
      
      print ajax_render($output);
      break;
  }
  exit;
}

function ac_megamenu_icon_fonts_form($form, $form_state){
  acquia_include('fields');
  acquia_include('options');

  $values = isset($form_state['values']) ? $form_state['values'] : array();

	$form = array();

	 // add icon fields
	 acquia_field_iconfont($form, $form, array(
		 'title' => t('Megamenu menu item icon'),
		 'default' => isset($values['icon']) ? $values['icon'] : '',
		 'parents' => array(),
		 'animate' => FALSE,
		 'always_enabled' => TRUE,
	 ));
   
  $form['action'] = array(
    '#type' => 'hidden',
    '#value' => 'load_font_icons',
  );
  
  $form['mid'] = array(
    '#type' => 'hidden',
    '#value' => isset($values['mid']) ? $values['mid'] : '',
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('submit'),
  );
   return $form;
}


function ac_megamenu_command_update_fonticon($mid, $icon){
  return array(
    'command' => 'acMegamenuUpdateFontIcon',
    'icon' => $icon,
    'mid' => $mid,
  );
}