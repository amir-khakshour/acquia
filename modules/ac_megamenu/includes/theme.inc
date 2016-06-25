<?php

function template_preprocess_ac_megamenu(&$vars) {
  acquia_include('media');

  $menu_name = $vars['menu_name'];
  if($vars['section'] == 'backend') {
    $items = ac_megamenu_get_tree($menu_name);
  }
  else {
    $items = menu_tree_all_data($menu_name);
  }
  if (function_exists('i18n_menu_localize_tree')) {
    $items = i18n_menu_localize_tree($items);
  }
  $items_page = menu_tree_page_data($menu_name);
  $trail = ac_megamenu_build_page_trail($items_page);
  $menu_config = ac_megamenu_get_menu_config($menu_name);
  $block_config = ac_megamenu_get_block_config($menu_name);
  ac_megamenu_sync_config_all($items, $menu_config, $vars['section']);
  ac_megamenu_edit_block_config($block_config);

  $vars['attributes_array']['id'] = "ac-megamenu-" . str_replace('_', '-', $menu_name);
  $vars['classes_array'][] = "ac-megamenu-" . str_replace('_', '-', $menu_name);
  $vars['classes_array'][] =  str_replace('_', '-', $menu_name);
  $vars['classes_array'][] =  'main-menu';

  if($vars['section'] == 'frontend' && $block_config['style'] != '') {
    drupal_add_css(drupal_get_path("module", "ac_megamenu") . "/css/styles/" . $block_config['style'] . ".css", array(
        'basename' => "ac-megamenu-style-" . $block_config['style'] . ".css",
    ));
    $vars['classes_array'][] = "style-" . $block_config['style'];
  }


  if($block_config['animation'] != 'none') {
    $vars['classes_array'][] = "animate";
    $vars['classes_array'][] = $block_config['animation'];
    $vars['attributes_array']['data-duration'] = $block_config['duration'];
    $vars['attributes_array']['data-delay'] = $block_config['delay'];
  }


  $vars['content'] = theme('ac_megamenu_nav', array(
      'menu_name' => $vars['menu_name'],
      'level' => 0,
      'menu_config' => $menu_config,
      'block_config' => $block_config,
      'items' => $items,
      'trail' => $trail,
      'section' => $vars['section'],
  ));
  $vars['block_config'] = $block_config;
  if($vars['section'] == 'frontend' && $block_config['animation'] != 'none') {
    $css = array();
    $css[] = '.ac-megamenu.animate .mega > .mega-dropdown-menu, .ac-megamenu.animate.slide .mega > .mega-dropdown-menu > div {';
    $css[] = '  transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -webkit-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -ms-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -o-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -webkit-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -ms-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -o-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '}';
    drupal_add_css(implode("\n", $css), array('type' => 'inline'));
  }
}

function template_preprocess_ac_megamenu_nav(&$vars) {
  $items = $vars['items'];
  $level = $vars['level'];
  $lis = array();
  foreach ($items as $item) {
    if(!$item['link']['hidden']) {
      $lis[] = theme('ac_megamenu_item', array(
          'menu_name' => $vars['menu_name'],
          'level' => $level + 1,
          'item' => $item,
          'menu_config' => $vars['menu_config'],
          'block_config' => $vars['block_config'],
          'trail' => $vars['trail'],
          'section' => $vars['section'],
      ));
    }
  }
  $vars['lis'] = implode("\n", $lis);

  if ($vars['section'] == 'frontend') {
    $vars['classes_array'] = array("menu");
    $vars['classes_array'][] = "l-" . $level;
    $vars['classes_array'][] = "c-" . count($items);
    $vars['classes_array'][] = "clearfix";
  }else{
    $vars['classes_array'][] = "nav";
    $vars['classes_array'][] = "l-" . $level;
    $vars['classes_array'][] = "items-" . count($items);
  }
}

function template_preprocess_ac_megamenu_item(&$vars) {
  $front = $vars['section'] == 'frontend' ? TRUE : FALSE;
  $level = $vars['level'];
  $item = $vars['item'];
  $mlid = $item['link']['mlid'];
  $trail = $vars['trail'];
  $menu_config = $vars['menu_config'];
  $item_config = isset($menu_config[$mlid]['item_config']) ? $menu_config[$mlid]['item_config'] : array();
  ac_megamenu_edit_item_config($item_config);
  $vars['item_config'] = $item_config;
  if(isset($menu_config[$mlid]['rows_content']) && !empty($menu_config[$mlid]['rows_content'])
      && (!$front || !$item_config['hidesub'])) {
    $vars['submenu'] = theme('ac_megamenu_submenu', array(
        'menu_name' => $vars['menu_name'],
        'parent' => $item,
        'level' => $level,
        'menu_config' => $vars['menu_config'],
        'block_config' => $vars['block_config'],
        'trail' => $vars['trail'],
        'section' => $vars['section'],
    ));
  }
  else {
    $vars['submenu'] = NULL;
  }
  if(!$front) {
    $vars['attributes_array']['title'] = t("Menu Item");
    $vars['attributes_array']['data-id'] = $mlid;
    $vars['attributes_array']['data-level'] = $level;
    $vars['attributes_array']['data-type'] = 'menu_item';
    $vars['attributes_array']['data-class'] = $item_config['class'];
    $vars['attributes_array']['data-xicon'] = $item_config['xicon'];
    $vars['attributes_array']['data-caption'] = $item_config['caption'];
    $vars['attributes_array']['data-alignsub'] = $item_config['alignsub'];
    $vars['attributes_array']['data-group'] = $item_config['group'];
    $vars['attributes_array']['data-hidewcol'] = $item_config['hidewcol'];
    $vars['attributes_array']['data-hidesub'] = $item_config['hidesub'];
    $vars['classes_array'][] = 'l-' . $level;
    $vars['classes_array'][] = 'mega';

  }else{
    $vars['classes_array'] = array('menu-item');
    $vars['classes_array'][] = 'l-' . $level;
    if (isset($item_config['xicon']) && !empty($item_config['xicon'])) {
      $vars['classes_array'][] = 'ac-icon-enabled';
    }
    if (isset($item_config['caption']) && !empty($item_config['caption'])) {
      $vars['classes_array'][] = 'ac-caption-enabled';
    }elseif ($level == 1){
      $vars['classes_array'][] = 'ac-no-caption';
    }
  }


  if ($item_config['group'] && $vars['submenu']) {
    $vars['classes_array'][] = "mega-group";
    $vars['a_classes'][] = 'mega-group-title';
  }
  elseif ($vars['submenu'] && !$item_config['hidesub']) {
    $vars['a_classes'][] = 'dropdown-toggle';
    if($level == 1) {
      $vars['classes_array'][] = 'dropdown';
    }
    else {
      $vars['classes_array'][] = 'dropdown-submenu';
    }
  }

  if ($vars['submenu']) {
    $vars['classes_array'][] = "menu-item-has-children";
  }

  if (isset($trail[$mlid])) {
    $vars['classes_array'][] = 'active';
    $vars['classes_array'][] = $vars['a_classes'][] = 'active-trail';
  }

  if(!empty($item_config['class'])) {
    $vars['classes_array'][] = $item_config['class'];
  }
  if(!empty($item_config['alignsub'])) {
    $vars['classes_array'][] = "mega-align-" . $item_config['alignsub'];
  }
  if($item_config['hidewcol']) {
    $vars['classes_array'][] = "sub-hidden-collapse";
  }
  if(isset($menu_config[$mlid]['submenu_config']['fullwidth']) && $menu_config[$mlid]['submenu_config']['fullwidth']) {
    $vars['classes_array'][] = 'mega-full-width';
  }else{
    $vars['classes_array'][] = 'mega-auto-width';
  }

}

function template_preprocess_ac_megamenu_submenu(&$vars) {
  acquia_include('utility', 'ac_megamenu');

  $front = $vars['section'] == 'frontend' ? TRUE : FALSE;
  $parent = $vars['parent'];
  $mlid = $parent['link']['mlid'];
  $menu_config = $vars['menu_config'];
  $item_config = isset($menu_config[$mlid]) ? $menu_config[$mlid] : array();
  $submenu_config = isset($item_config['submenu_config']) ? $item_config['submenu_config'] : array();
  $vars['submenu_config'] = $submenu_config;
  ac_megamenu_edit_submenu_config($submenu_config);
  $rows = array();
  $vars['sub_attributes']['class'] = array('sub-nav-rows');

  foreach($item_config['rows_content'] as $row) {
    $rows[] = theme('ac_megamenu_row', array(
        'menu_name' => $vars['menu_name'],
        'row' => $row,
        'parent' => $vars['parent'],
        'level' => $vars['level'],
        'menu_config' => $vars['menu_config'],
        'block_config' => $vars['block_config'],
        'trail' => $vars['trail'],
        'section' => $vars['section'],
        'width' => $submenu_config['width'],
        'fullwidth' => isset($submenu_config['fullwidth']) ? $submenu_config['fullwidth'] : FALSE,
    ));
  }
  $vars['rows'] = implode("\n", $rows);

  if ($front) {
    $vars['classes_array'] = array('sub-nav');
    if(!empty($submenu_config['fid']) && $submenu_config['fid']!='') {
      $bg_src = acquia_get_image($submenu_config['fid']);
      $vars['sub_attributes']['style'] = "background-image: url('".$bg_src."')";
      $vars['sub_attributes']['class'][] = 'ac-bg';
    }
  }else{
    if($submenu_config['class'] != "") {
      $vars['classes_array'][] = $submenu_config['class'];
    }
    if($submenu_config['group']) {
      $vars['classes_array'][] = 'mega-group-ct';
    }
    else {
      $vars['classes_array'][] = 'dropdown-menu';
      $vars['classes_array'][] = 'mega-dropdown-menu';
    }
    $vars['classes_array'][] = 'nav-child';
    $vars['attributes_array']['data-class'] = $submenu_config['class'];
    $vars['attributes_array']['data-width'] = isset($submenu_config['fullwidth']) && $submenu_config['fullwidth'] !=1 ? $submenu_config['width'] : '100%';
    $vars['attributes_array']['data-fullwidth'] = isset($submenu_config['fullwidth']) ? $submenu_config['fullwidth'] : FALSE;

    $fid = '';
    if (isset($submenu_config['fid'])) {
      $fid = $submenu_config['fid'];
    }
    $vars['attributes_array']['data-fid'] = $fid;
    if($fid != '') {
      $bg_src = acquia_get_image($fid);
      $vars['attributes_array']['data-src'] = $bg_src;
      $vars['attributes_array']['style'] = "background-image: url('".$bg_src."')";
    }
  }

  if (!empty($submenu_config['width']) && !$submenu_config['fullwidth']) {
    $vars['attributes_array']['style'] = "width: " . ($submenu_config['fullwidth'] ? '100%' : $submenu_config['width'] . "px;");
  }else if ($submenu_config['fullwidth']) {
  }
}

/**
 * Theme Row of submenus
 */
function template_preprocess_ac_megamenu_row(&$vars) {
  $front = $vars['section'] == 'frontend' ? TRUE : FALSE;

  $row = $vars['row'];
  $cols = array();
  foreach($row as $id => $col) {
    $cols[] = theme('ac_megamenu_column', array(
        'menu_name' => $vars['menu_name'],
        'col' => $col,
        'parent' => $vars['parent'],
        'level' => $vars['level'],
        'menu_config' => $vars['menu_config'],
        'block_config' => $vars['block_config'],
        'trail' => $vars['trail'],
        'section' => $vars['section'],
        'order' => $id == 0 ? 'first' : ($id == count($row)-1 ? 'last' : ''),
    ));
  }
  $vars['columns'] = implode("\n", $cols);

  if ($front) {
    acquia_include('theme');
    $vars['classes_array'] = array('sub-nav-row', 'clearfix', 'menu');
  }else{
    $vars['classes_array'][] = 'row-fluid';
  }

  if (count($row) > 1) {
    $vars['classes_array'][] = 'ac-multi-cols';
  }
}

/**
 * Theme Cols in submenu
 */
function template_preprocess_ac_megamenu_column(&$vars) {
  $front = $vars['section'] == 'frontend' ? TRUE : FALSE;

  $col = $vars['col']['col_content'];
  $col_config = $vars['col']['col_config'];
  ac_megamenu_edit_col_config($col_config);
  $vars['col_config'] = $col_config;
  $vars['close_button'] = FALSE;
  $ac_items = array();
  foreach($col as $ac_item) {
    if($ac_item['type'] == 'menu_item') {
      $ac_items[] = theme('ac_megamenu_subnav', array(
          'menu_name' => $vars['menu_name'],
          'col' => $col,
          'items' => $vars['parent']['below'],
          'level' => $vars['level'],
          'menu_config' => $vars['menu_config'],
          'block_config' => $vars['block_config'],
          'trail' => $vars['trail'],
          'section' => $vars['section'],
      ));
      break;
    }
    else {
      $ac_items[] = theme('ac_megamenu_block', array(
          'block_key' => $ac_item['block_key'],
          'section' => $vars['section'],
          'showblocktitle' => $col_config['showblocktitle']
      ));
      if (!$front) {
        $vars['attributes_array']['data-showblocktitle'] = $col_config['showblocktitle'];
        $vars['close_button'] = '<span class="close icon-remove" title="' . t("Remove this block") . '">&nbsp;</span>';
      }
    }
  }

  $vars['ac_items'] = implode("\n", $ac_items);

  if (!$front) {
    $vars['classes_array'][] = 'mega-col-nav';

    $vars['attributes_array']['data-class'] = $col_config['class'];
    $vars['attributes_array']['data-width'] = $col_config['width'];
    $vars['attributes_array']['data-hidewcol'] = $col_config['hidewcol'];

    $fid = '';
    if (isset($col_config['fid'])) {
      $fid = $col_config['fid'];
    }
    $vars['attributes_array']['data-fid'] = $fid;
    if($fid != '') {
      $bg_src = acquia_get_image($fid);
      $vars['attributes_array']['data-src'] = $bg_src;
      $vars['classes_array'][] = 'ac-bg';
      $vars['attributes_array']['style'] = "background-image: url('".$bg_src."')";
    }
  }else{
    $vars['classes_array'] = array('menu-item');
    if(!empty($col_config['fid']) && $col_config['fid'] != '') {
      $bg_src = acquia_get_image($col_config['fid']);
      $vars['classes_array'][] = 'ac-bg';
      $vars['attributes_array']['style'] = "background-image: url('".$bg_src."')";
    }
  }

  $vars['classes_array'][] = "menu-col";
  $vars['classes_array'][] = 'span' . $col_config['width'];

  if (empty($ac_items)) {
    $vars['classes_array'][] = 'empty-col';
  }

  if (!empty($vars['order'])) {
    $vars['classes_array'][] = $vars['order'];
  }

  if(!empty($col_config['class'])) {
    $vars['classes_array'][] = $col_config['class'];
  }
  if(!empty($col_config['hidewcol'])) {
    $vars['classes_array'][] = $col_config['class'];
  }
  if($col_config['hidewcol']) {
    $vars['classes_array'][] = 'hidden-collapse';
  }

  $vars['classes_array'][] = "menu-item-has-children";
  $vars['attributes_array']['id'] = ac_megamenu_get_counter("col");
}

function template_preprocess_ac_megamenu_subnav(&$vars) {
  $col = $vars['col'];
  $items = $vars['items'];
  $level = $vars['level'];
  $lis = array();
  foreach($col as $ac_item) {
    $item = ac_megamenu_get_menu_item($vars['menu_name'], $ac_item['mlid']);
    $lis[] = theme('ac_megamenu_item', array(
        'menu_name' => $vars['menu_name'],
        'level' => $level + 1,
        'item' => $item,
        'menu_config' => $vars['menu_config'],
        'block_config' => $vars['block_config'],
        'trail' => $vars['trail'],
        'section' => $vars['section'],
    ));
  }
  $vars['lis'] = implode("\n", $lis);
  $vars['classes_array'][] = "mega-nav";
  $vars['classes_array'][] = "l-" . $level;
  $vars['classes_array'][] = "items-" . count($col);
}

function template_preprocess_ac_megamenu_block(&$vars) {
  acquia_include('utility', 'ac_megamenu');
  $block = ac_megamenu_load_block($vars['block_key']);
  if($block) {
    $module = $block->module;
    $delta = $block->delta;
    $content = module_invoke($module, 'block_view', $delta);
    if(isset($vars['showblocktitle']) && $vars['showblocktitle']) {
      $block->subject = empty($content['subject']) ? $block->title : $content['subject'];
    }
    else {
      $block->subject = "";
    }
    if(empty($content) && $vars['section'] == 'backend') {
      $vars['content'] = ac_megamenu_get_block_title($vars['block_key']);
    }
    elseif($content) {
      $vars['content'] = theme("block", array('elements' => array('content' => $content['content'], '#children' => (is_array($content['content']) ? drupal_render($content['content']) : $content['content']), '#block' => $block)));
    }
    else {
      $vars['content'] = NULL;
    }
    $vars['classes_array'][] = "ac-block";
    $vars['classes_array'][] = "ac-megamenu-block";
    $vars['attributes_array']['data-type'] = "block";
    $vars['attributes_array']['data-block'] = $vars['block_key'];
  }
  else {
    $vars['content'] = NULL;
  }
}

function template_preprocess_ac_megamenu_backend(&$vars) {
  acquia_include('utility', 'ac_megamenu');
  $module_path = drupal_get_path('module', 'ac_megamenu');
  $megamenu_libs_path = url($module_path . '/libs');

  $vars['blank_image'] = $megamenu_libs_path . '/not_set.png';

  $menu_name = $vars['menu_name'];
  $block_config = ac_megamenu_get_block_config($menu_name);
  ac_megamenu_edit_block_config($block_config);
  $menu_content = ac_megamenu_render_block($menu_name);
  $vars['menu_content'] = $menu_content['content']['#markup'];
  $vars['item_toolbox'] = theme_render_template(drupal_get_path('module', 'ac_megamenu') . "/templates/backend/ac-megamenu-item-toolbox.tpl.php", array());
  $vars['submenu_toolbox'] = theme_render_template(drupal_get_path('module', 'ac_megamenu') . "/templates/backend/ac-megamenu-submenu-toolbox.tpl.php", array(
      'blank_image' => $vars['blank_image'],
  ));
  $vars['column_toolbox'] = theme_render_template(drupal_get_path('module', 'ac_megamenu') . "/templates/backend/ac-megamenu-column-toolbox.tpl.php", array(
      'blocks_options' => ac_megamenu_get_blocks_options(),
      'blank_image' => $vars['blank_image'],
  ));
  $vars['block_config'] = $block_config;
  $vars['animation_options'] = ac_megamenu_animation_options($block_config);
  $vars['style_options'] = ac_megamenu_style_options($block_config);
  $vars['edit_links'] = base_path() . "admin/structure/menu/manage/$menu_name";
  $vars['edit_menu'] = base_path() . "admin/structure/menu/manage/$menu_name/edit";

  drupal_add_js('
    (function ($) {
      Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};
      Drupal.ACMegaMenu.ajax_link = "' . (variable_get('clean_url', 0) ? '' : '?q=') . '";
      Drupal.ACMegaMenu.ajax_URL = "' . AC_MEGAMENU_AJAX_PATH . '";
      Drupal.ACMegaMenu.blank_image = "' . $vars['blank_image'] . '";
    })(jQuery);
  ', 'inline');

  $js = 'Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};
  (function ($) {
    Drupal.behaviors.acMegaMenuAction = {
      attach: function(context) {
        $("#ac-megamenu-admin-mm-container").megamenuAdmin({menu_name: "' . $menu_name . '"});
      }
    }
  })(jQuery);
  ';
  drupal_add_js($js, array('type' => 'inline'));
}
