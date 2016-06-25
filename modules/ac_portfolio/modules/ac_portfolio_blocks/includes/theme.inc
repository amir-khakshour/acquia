<?php

/**
 * @file
 *  Contains helper functions to build and override theme functions
 */

/**
 * Implements hook_theme().
 */
function ac_portfolio_blocks_theme() {
  acquia_include('options', 'ac_portfolio');

  $path = drupal_get_path('module', 'ac_portfolio_blocks') . '/theme';

  $items = array();
  $items['portfolio_recent'] = array(
      'variables' => array(
          'settings' => array(),
      ),
      'template' => 'portfolio-recent',
      'path' => $path,
  );

  $items['portfolio_related'] = array(
      'variables' => array(
          'nid' => NULL,
      ),
      'template' => 'portfolio-related',
      'path' => $path,
  );

  return $items;
}

/**
 * @TODO document here
 */
function ac_portfolio_blocks_preprocess_portfolio_recent(&$vars){
  acquia_include('utility');
  acquia_include('slider');
  acquia_include('utility', 'ac_portfolio');
  acquia_include('media', 'ac_portfolio');
  acquia_include('utility', 'ac_portfolio_blocks');
  $vars['items'] = array();

  $settings = isset($vars['settings']) ? $vars['settings'] : array();
  $settings+= drupal_get_query_parameters();
  ac_portfolio_item_prepare_settings($settings);

  if ($settings['appearance'] == 'slider') {
    $settings['num_per_page'] = $settings['total'];
    $settings['view'] = 'slider';
  }elseif ($settings['appearance'] == 'thumb') {
    $settings['view'] = 'thumb';
  }

  $items = ac_portfolio_get_recent_items($settings);
  $vars['pager'] = $items['pager_pager'];
  $items = $items['pager_nodes'];

  $tags = array();
  $thumbs = array();

  if ($items && !empty($items)) {
    foreach ($items as $item) {
      $item = ac_portfolio_prepare_view($item, $settings);
      $item['frame'] = isset($settings['frame']) ? $settings['frame'] : '';
      if (isset($item['thumb'])) {
        $thumbs[] = $item['thumb'];
      }

      if (isset($settings['view'])) {
        $settings['view'] = $settings['frame'] == 'rounded_borders' ? 'thumb' : $settings['view'];
        $tags += isset($item['tags-raw']) ? $item['tags-raw'] : array();
        $vars['items'][] = theme('portfolio_thumb_view_' .$settings['view'], $item );
      }
    }
  }

  // tag sorting
  if ($settings['sorting']) {
    $vars['sortings'] = theme('portfolio_sortings', array(
        'tags' => $tags,
        'style' => $settings['filter_style'],
        'filter_type' => $settings['appearance'] == 'multigrid' ? 'ajax' : 'isotope',
    ));
  }

  $settings['framed'] = $settings['frame'];
  $vars['items'] = array_filter($vars['items'], 'strlen');
  $vars['wrap_attrs']['id'] = $settings['id'];
  $vars['wrap_attrs']['class'][] = 'ac-portfolio';
  $vars['wrap_attrs']['class'][] =  acquia_get_class_by_args(array('pager'), $settings, CHECK_LENGTH);
  $vars['wrap_attrs']['class'][] =  $settings['appearance'] == 'multigrid' ? 'ac-filter-ajax' : 'ac-filter-isotope';
  $vars['wrap_attrs']['class'][] = 'ac-s-li';
  $vars['wrap_attrs']['class'][] = isset($settings['fullwidth']) && $settings['fullwidth'] ? 'ac-full-container-width' : NULL;
  $vars['fullwidth'] = $settings['fullwidth'];

  // -- Container
  $vars['outter_attrs']['class'][] = 'p-items-outter';


  // -- Wrapper
  $vars['wrapper_attrs']['class'][] = 'p-items';
  $vars['wrapper_attrs']['class'][] = 'ac-preload-me';
  $vars['wrapper_attrs']['class'][] = 'ac-init-hidden';
  $vars['wrapper_attrs']['class'][] = 'clearfix';
  $vars['wrapper_attrs']['class'][] = 'pager-target';

  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('view', 'framed'), $settings, CHECK_LENGTH);
  $vars['wrapper_attrs']['class'][] = isset($settings['spaced']) && $settings['spaced'] ? 'ac-spaced' : 'ac-no-sapced';
  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('appearance'), $settings, CHECK_LENGTH);
  $vars['wrapper_attrs']['data-padding'] = $settings['spaced'] ? $settings['padding'] : 0;

  if ($settings['appearance'] != 'slider') {
    $vars['wrapper_attrs']['data-columns'] = isset($settings['cols']) ? $settings['cols'] : acquia_variable_get('portfolio_recent_cols', 4);

    if (!isset($settings['width']) || $settings['width'] != 'equal_height'){
      $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('cols'), $settings, CHECK_LENGTH);
    }
  }


  /** Scroller **/
  if ($settings['appearance'] == 'scroller') {
    acquia_load_resources('carousel');
    $vars['wrapper_attrs']['class'][] = 'ac-carousel';
    $vars['wrapper_attrs']['class'][] = 'owl-carousel';
    $vars['wrapper_attrs']['class'][] = 'owl-theme';
    $vars['wrapper_attrs']['class'][]= 'ac-darkstyle';

    if (!isset($settings['width']) || $settings['width'] != 'equal_height'){
      $vars['wrapper_attrs']['class'][] = 'ac-appearance-grid';
    }else if($settings['width'] == 'equal_height'){
      $vars['wrapper_attrs']['class'][] = 'ac-auto-width';
    }
    $vars['wrapper_attrs']['data-padding'] = $settings['spaced'] ? $settings['padding'] : 0;

    if (isset($settings['nav_prev_next']) && !$settings['nav_prev_next']) {
      $vars['wrapper_attrs']['data-directionnav'] = 'false';
    }else{
      $vars['wrapper_attrs']['data-directionnav'] = 'true';
      $vars['wrapper_attrs']['class'][]= 'ac-prev-next-enabled';
    }

    if (isset($settings['nav_pager']) && !$settings['nav_pager']) {
      $vars['wrapper_attrs']['data-controlnav'] = 'false';
    }else{
      $vars['wrapper_attrs']['data-controlnav'] = 'true';
      $vars['wrapper_attrs']['class'][]= 'ac-pager-enabled';
    }

    if (isset($settings['auto_scroll']) && $settings['auto_scroll']) {
      $vars['wrapper_attrs']['data-auto'] = 'true';
    }

    $vars['pager'] = '';
  }
  /** Slider **/
  else if ($settings['appearance'] == 'slider') {
    acquia_load_resources('slider');

    $vars['wrapper_attrs']['class'][] = 'slides';
    $vars['outter_attrs']['data-columns'] = 1;

    $vars['pager'] = '';
    if (isset($settings['thumb']) && $settings['thumb']) {
      $vars['footer'] = get_thumb_slider_js(array('id' => $vars['wrap_attrs']['id']), $thumbs);
      $vars['wrapper_attrs']['data-thumbNav'] = 'true';
      $vars['wrapper_attrs']['class'][]= 'ac-thumb-slider';
    }else{
      $vars['outter_attrs']['class'][]= 'ac-slider';
      $vars['outter_attrs']['class'][] = 'flexslider';
    }

    if (isset($settings['pager']) && $settings['pager']) {
      $vars['wrapper_attrs']['class'][]= 'ac-pager-enabled';
    }

    if ($settings['excerpt'] == false) {
      $vars['outter_attrs']['data-controlnav'] = 'false';
      $vars['wrap_attrs']['class'][]= 'ac-simple-style';
    }else{
      $vars['outter_attrs']['class'][]= 'ac-mini-nav';
    }

  }
  /** Thumb **/
  else if($settings['appearance'] == 'thumb'){
    $vars['wrapper_attrs']['class'][]= 'ac-appearance-grid';
  }
  /** MultiGrid **/
  else{
    if ($settings['appearance'] == 'multigrid'){
      // Add lib
      drupal_add_library('acquia', 'collageplus');
      if (isset($settings['gplus_height']) && !empty($settings['gplus_height'])) {
        $vars['wrapper_attrs']['data-gplus_height'] = $settings['gplus_height'];
      }
      if (isset($settings['gplus_effect']) && !empty($settings['gplus_effect'])) {
        $vars['wrapper_attrs']['data-gplus_effect'] = $settings['gplus_effect'];
      }
    }else{
      // Masonry and Grid view
      acquia_load_resources('isotope');
    }

    if (isset($settings['ajax_type']) && $settings['pager'] == 'ajax') {
      $vars['outter_attrs']['data-ajax_type'] = $settings['ajax_type'];
    }
    if (isset($vars['pager']) && !empty($vars['pager']) && $settings['pager'] == 'ajax' && $settings['num_per_page'] !=-1) {

      /**
       * slider for items
       *  when pager enabled and infinite scroll paging some libraries won't load so we need to load them manually
       */
      acquia_load_resources('minslider');
      $js = array(
          'pager' => '.ac-pager-ajax .pager',
          'pagerNext' => '.ac-pager-ajax .pager .pager-next a',
          'doneText' => 'all is loaded!',
      );

      drupal_add_js(array('infscr' => $js), 'setting');
      acquia_load_resources('infscroller');
      $vars['pager'] .= theme('acquia_ajax_load_btn');
    }
  }

  $vars['wrap_attrs']['class'] = array_filter($vars['wrap_attrs']['class'], 'strlen');
  $vars['wrap_attrs']['class'] = implode(' ', $vars['wrap_attrs']['class']);

  $vars['outter_attrs']['class'] = array_filter($vars['outter_attrs']['class'], 'strlen');
  $vars['outter_attrs']['class'] = implode(' ', $vars['outter_attrs']['class']);

  $vars['wrapper_attrs']['class'] = array_filter($vars['wrapper_attrs']['class'], 'strlen');
  $vars['wrapper_attrs']['class'] = implode(' ', $vars['wrapper_attrs']['class']);
}

/**
 * @TODO document here
 */
function ac_portfolio_blocks_preprocess_portfolio_related(&$vars){
  acquia_include('content');
  acquia_include('utility', 'ac_portfolio');
  acquia_include('media', 'ac_portfolio');
  acquia_include('utility', 'ac_portfolio_blocks');

  if (!isset($vars['nid']) || $vars['nid'] == 0) {
    $node = menu_get_object();
  }else {
    $node = node_load($vars['nid']);
  }

  $vars['items'] = array();
  if (!is_object($node) || !isset($node->nid)) {
    return;
  }

  $settings = isset($vars['settings']) ? $vars['settings'] : array();
  $vars['settings'] = $settings;

  $items = ac_portfolio_get_related_items($node);
  if ($items && !empty($items)) {
    foreach ($items as $item) {
      $item = ac_portfolio_prepare_view($item, $settings);
      if (isset($settings['view'])) {
        $item['frame'] = isset($settings['frame']) ? $settings['frame'] : '';
        $vars['items'][] = theme('portfolio_thumb_view_' .$settings['view'], $item );
      }
    }
  }
  $vars['items'] = array_filter($vars['items'], 'strlen');

  // Load resources

  // Wrapper attributes
  $vars['wrap_attrs']['class'][] = 'ac-portfolio';
  $vars['wrap_attrs']['class'][] = 'block';

  // Inner attributes
  $vars['wrapper_attrs']['class'][] = 'p-items';
  $vars['wrapper_attrs']['class'][] = 'ac-preload-me';
  $vars['wrapper_attrs']['class'][] = 'ac-init-hidden';
  $vars['wrapper_attrs']['class'][] = 'clearfix';
  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('view'), $settings, CHECK_LENGTH);

  acquia_load_resources('carousel');
  $vars['wrapper_attrs']['class'][] = 'ac-carousel';
  $vars['wrapper_attrs']['class'][] = 'owl-carousel';
  $vars['wrapper_attrs']['class'][] = 'owl-theme';
  $vars['wrapper_attrs']['class'][]= 'ac-darkstyle';
  $vars['wrapper_attrs']['class'][]= 'ac-appearance-grid';

  if (isset($settings['nav_prev_next']) && !$settings['nav_prev_next']) {
    $vars['wrapper_attrs']['data-directionnav'] = 'false';
  }else{
    $vars['wrapper_attrs']['data-directionnav'] = 'true';
    $vars['wrapper_attrs']['class'][]= 'ac-prev-next-enabled';
  }
  if (isset($settings['nav_pager']) && !$settings['nav_pager']) {
    $vars['wrapper_attrs']['data-controlnav'] = 'false';
  }else{
    $vars['wrapper_attrs']['class'][]= 'ac-pager-enabled';
  }

  if (isset($settings['auto_scroll']) && $settings['auto_scroll']) {
    $vars['wrapper_attrs']['data-auto'] = 'true';
  }

  // container attributes
  $vars['wrapper_attrs']['data-columns'] = isset($settings['cols']) ? $settings['cols'] : acquia_variable_get('portfolio_related_cols', 4);
  $vars['wrapper_attrs']['data-padding'] = $settings['spaced'] ? $settings['padding'] : 0;

  $vars['outter_attrs']['class'][] = 'p-items-outter';

  $vars['pager'] = '';
}
