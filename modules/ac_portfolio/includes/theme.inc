<?php

/**
 * @file
 *  Contains helper functions to build and override theme functions
 */
define('ac_portfolio_path', drupal_get_path('module', 'ac_portfolio'));

/**
 * Implements hook_theme().
 */
function ac_portfolio_theme() {
  $path = drupal_get_path('module', 'ac_portfolio') . '/theme';
  $items = array();
  $items['portfolio_preview_media'] = array(
    'variables' => array(
      'items' => NULL,
    ),
    'template' => 'portfolio-preview-media',
    'path' => $path,
  );

  $items['portfolio_nav'] = array(
    'variables' => array(
      'node' => NULL,
    ),
    'file' => 'includes/theme.inc',
  );

  $items['portfolio_sortings'] = array(
    'variables' => array(
      'tags' => NULL,
      'style' => NULL,
    ),
    'template' => 'portfolio-sortings',
    'path' => $path,
  );

  acquia_include('options', 'ac_portfolio');

  // portfolio Layouts
  foreach (array_keys(ac_portfolio_node_layouts()) as $layout) {
    $items['node__portfolio_l_' . $layout] = array(
      'variables' => array(),
      'template' => 'node--portfolio-l-'.$layout,
      'path' => $path . '/layouts',
    );
  }

  // item view
  foreach (array_keys(ac_portfolio_item_view_styles()) as $view) {
    $items['portfolio_thumb_view_' . $view] = array(
      'variables' => array(
        'item' => array(),
        'settings' => array(),
      ),
      'template' => 'portfolio-thumb-view-'.$view,
      'path' => $path . '/item',
    );
  }

  // Custom Slider view
  $items['portfolio_thumb_view_slider'] = array(
    'variables' => array(
      'item' => array(),
      'settings' => array(),
    ),
    'template' => 'portfolio-thumb-view-slider',
    'path' => $path . '/item',
  );

  // Custom Slider view
  $items['portfolio_thumb_view_thumb'] = array(
    'variables' => array(
      'item' => array(),
      'settings' => array(),
    ),
    'template' => 'portfolio-thumb-view-thumb',
    'path' => $path . '/item',
  );
  return $items;
}

/**
 * Implements hook_theme_registry_alter()
 */
function ac_portfolio_theme_registry_alter(&$theme_registry) {
  $theme = variable_get('ACQUIA_BASE_THEME', NULL);
  $path = drupal_get_path('module', 'acquia');
  $theme_registry_copy = $theme_registry;
  _theme_process_registry($theme_registry_copy, 'phptemplate', 'theme_engine', $theme, $path);
  $theme_registry += array_diff_key($theme_registry_copy, $theme_registry);
  // A list of templates the module will provide templates for
  $hooks = array('page');
  foreach ($hooks as $h) {
    // Add the key 'theme paths' if it doesn't exist in this theme's registry
    if (!isset($theme_registry[$h]['theme paths'])) {
      $theme_registry[$h]['theme paths'] = array();
    }
    //Shift this module's directory to the top of the theme path list
    if(is_array($theme_registry[$h]['theme paths'])) {
      $first_element = array_shift($theme_registry[$h]['theme paths']);
      if ($first_element) {
        array_unshift($theme_registry[$h]['theme paths'], $first_element, $path);
      } else {
        array_unshift($theme_registry[$h]['theme paths'], $path);
      }
    }
  }
}

//----------------------------------------------------------------
// preprocess Functions
//----------------------------------------------------------------

/**
 * teaser view of portfolio nodes
 */
function ac_portfolio_teaser_page_view(&$vars){

  $vars['container_attributes'] = array();
  $vars['container_attributes']['class'] = '';
  $vars['attributes_array']['id'] = 'node-' .$vars['node']->nid;
  $vars['attributes_array']['class'][]= 'ac-node-'.AC_PORTFOLIO_MN;
  $vars['attributes_array']['class'][]= ' ac-teaser-view';
  $vars['attributes_array']['class'][]= ' block';

  $vars['media_classes'] = 'media ac-col ac-one-third clearfix';
  $vars['desc_classes'] = 'description ac-col ac-two-third clearfix';
  //ac_portfolio_prepare_view
  // Media HTML and view project

  if (isset($vars['node']->nodemeta)) {
    acquia_include('media', 'ac_portfolio');
    // Create media HTML
    $settings = isset($vars['settings']) ? $vars['settings'] : array();
    $settings += array('style' => 'rectangle-medium');
    ac_portfolio_item_prepare_settings($settings);
    unset($vars['date']);
    $vars +=ac_portfolio_get_teaser_extra((array)$vars['node'], $settings);
  }
}
/**
 * Full page view of portfolio pages
 */
function ac_portfolio_full_page_view(&$vars){
  acquia_include('utility');
  acquia_node_sibling('next', $vars['node']);
  $media_vars = array();
  $vars['container_attributes'] = array();
  $vars['container_attributes']['class'] = '';
  $vars['wrap_attributes'] = array();
  $vars['wrap_attributes']['class'] = 'ac-node-'.AC_PORTFOLIO_MN;
  $vars['wrap_attributes']['class'] .= ' ac-full-view';
  $vars['media_classes'] = 'media clearfix';
  $vars['desc_classes'] = 'description clearfix';

  $vars['body_extra_class'] = array();

  // Media HTML and view project
  if (isset($vars['node']->nodemeta)) {
    acquia_include('utility', 'ac_portfolio');
    // View Project
    if (isset($vars['node']->nodemeta['misc']['link']) && !empty($vars['node']->nodemeta['misc']['link'])) {
      $label = !empty($vars['node']->nodemeta['misc']['link_title']) ? $vars['node']->nodemeta['misc']['link_title'] : variable_get('ac_portfolio_link_title');
      $vars['link'] = acquia_button(array(
        'link' => $vars['node']->nodemeta['misc']['link'],
        'label' => t($label),
        'icon' => 'link',
        'type' => 'sw',
        'class' => 'ac-proj-link',
      ));
    }

    // Create media HTML
    $media = ac_portfolio_get_preview_media_from_meta($vars['node']->nodemeta);
    $vars['media'] = theme('portfolio_preview_media', $media);

    $vars += isset($vars['node']->nodemeta['misc']) ? $vars['node']->nodemeta['misc'] : array();
    $vars['wrap_attributes']['class'] .= ' ac-mode-'.$vars['view'];
    $vars['wrap_attributes']['class'] .= ' ac-layout-'.$vars['layout'];
    $vars['wrap_attributes']['class'] .= isset($media['media_type']) &&
    !empty($media['media_type']) ? ' ac-'.$media['media_type'].'-media' : '';

    if (isset($vars['columns']) && $vars['columns'] > 1) {
      $vars['wrap_attributes']['class'] .= ' ac-cols';
      $vars['wrap_attributes']['class'] .= ' ac-'.$vars['columns'].'-cols';
    }

    $vars['display'] = isset($vars['display']) ? $vars['display'] : 'normal';

    if ($vars['view'] == 'gallery') {
      $vars['media_classes'] .= ' ac-gallery-container';
    }
    else if ($vars['view'] == 'slideshow' && $vars['display'] == 'fullwidth') {
      $vars['body_extra_class'][] = 'portfolio-fullwidth-slider';
    }

    if ($vars['view'] !='slideshow' && isset($vars['spaced']) && $vars['spaced']) {
      $vars['wrap_attributes']['class'] .= ' ac-spaced';
    }

    $vars['container_attributes']['class'] .= ' ac-display-'.$vars['display'];
    if ($vars['display'] == 'fullwidth') {
      $vars['media_classes'] .= ' ac-full-container-width';
      $vars['desc_classes'] .= ' ac-page-section-container';
    }else{
      $vars['wrap_attributes']['class'] .= ' ac-page-section-container';
      if ($vars['layout'] == 'left' || $vars['layout'] == 'right') {
        $vars['media_classes'] .= ' ac-col ac-two-third';
        $vars['desc_classes'] .= ' ac-col ac-one-third';
      }else{
        $vars['media_classes'] .= ' ac-full-media';
      }
    }

  }else {
    $vars['media'] = '';
    $vars['link'] = '';
  }

  // Date
  $vars['date'] = format_date($vars['created'], "custom", "F j, Y");

  // Share links
  if (isset($vars['social']) && $vars['social']) {
    $vars['share_links'] = theme('acquia_share_links', array('node' => $vars['node'], 'socials' => array_filter(array_values(variable_get('ac_portfolio_enabled_share_links', array())))));
  }else {
    $vars['share_links'] = '';
  }

  // Like button
  if (variable_get('ac_portfolio_like_enabled', TRUE)) {
    $flag = flag_get_flag(AC_PORTFOLIO_LIKE_FLAG_MN);
    $vars['like_btn'] = '';
    if ($flag) {
      $vars['like_btn'] = $flag->theme($flag->is_flagged($vars['node']->nid) ? 'unflag' : 'flag', $vars['node']->nid);
    }
  }
  // Prev Next Links
  $vars['portfolio_nav'] = theme('portfolio_nav', array('node' => $vars['node']));
  $vars['layout'] = isset($vars['layout']) ? $vars['layout'] : 'left';
  $vars['theme_hook_suggestions'][] = 'node__portfolio_l_' . $vars['layout'];
}

/**
 * Implements hook_preprocess_node()
 */
function ac_portfolio_preprocess_node(&$vars){
  if (isset($vars['node']->type) && $vars['node']->type == AC_PORTFOLIO_MN) {
    // Different template for each view mode
    $vars['theme_hook_suggestions'][] = 'node__portfolio_' . $vars['view_mode'];
    if ($vars['view_mode'] != 'teaser') {
      ac_portfolio_full_page_view($vars);
    }else {
      ac_portfolio_teaser_page_view($vars);
    }
  }
}

/**
 * A preprocess function for our theme('flag'). It generates the
 * variables needed there.
 *
 * The $variables array initially contains the following arguments:
 * - $flag
 * - $action
 * - $entity_id
 * - $after_flagging
 * - $errors
 * - $needs_wrapping_element
 *
 * See 'flag.tpl.php' for their documentation.
 */
function ac_portfolio_preprocess_flag(&$vars) {
  if (isset($vars['flag']->name) && $vars['flag']->name == AC_PORTFOLIO_LIKE_FLAG_MN) {
    $entity_id = $vars['entity_id'];
    acquia_include('utility', 'ac_portfolio');
    $vars['likes'] = ac_portfolio_get_likes_counts($entity_id);
    $vars['flag_classes_array'][] = 'portfolio-like-btn';
    if (isset($vars['status']) && $vars['status'] == 'unflagged') {
      $vars['flag_classes_array'][] = 'unlikes';
    }else{
      $vars['flag_classes_array'][] = 'likes';
    }
  }
}

/**
 * @TODO document here
 */
function ac_portfolio_preprocess_portfolio_preview_media(&$vars) {
  if (isset($vars['items']) && !empty($vars['items'])) {

    if (isset($vars['view']) && $vars['view'] == 'slideshow') {
      acquia_load_resources('slider');
    }

    acquia_include('media');
    acquia_include('utility');
    foreach($vars['items'] as &$item) {
      if (isset($item['fid']) && $item['fid'] != 0) {
        $file_path =  '';
        if ($vars['media_type'] == 'image') {
          $item['style']['image_style'] = isset($vars['view']) ? variable_get('ac_portfolio_'.$vars['view'].'_style', NULL) : NULL;

          if (!empty($vars['frame'])) {
            $item['style']['frame'] = $vars['frame'];
          }else if (variable_get('ac_portfolio_image_frame', NULL)) {
            $item['style']['frame'] = variable_get('ac_portfolio_image_frame', NULL);
            $item['style']['frame'] = ($item['style']['frame'] == 'sw') ? acquia_theme_get_settings('image_frame', null, 'shortcodes') : $item['style']['frame'];
          }

          if ($vars['view'] == 'gallery' && variable_get('ac_portfolio_image_effect', NULL)) {
            $item['style']['effect'] = variable_get('ac_portfolio_image_effect', NULL);
            $item['style']['effect'] = ($item['style']['effect'] == 'sw') ? acquia_theme_get_settings('image_effect', null, 'shortcodes') : $item['style']['effect'];
          }

          if ($vars['view'] == 'gallery') {
            $item['style']['lightbox'] = TRUE;
            $item['style']['lightbox_caption'] = isset($item['description']) ? $item['description'] : NULL;
          }else if (isset($item['description']) && !empty($item['description'])) {
            $item['caption']['text'] = '<div class="c-i">'.$item['description'].'</div>';
            $item['caption']['attributes']['class'] = 'ac-caption';
          }

          $item['file'] = acquia_image_format_extended($item);
        }else {
          $item['style']['video_style'] = isset($vars['view']) ? variable_get('ac_portfolio_'.$vars['view'].'_style', NULL) : NULL;
          $item['file'] = acquia_video_format_extended($item);
        }
      }
    }

  }
}

//----------------------------------------------------------------
// Theme Functions
//----------------------------------------------------------------

/**
 * Preprocess portfolio tags
 */
function ac_portfolio_preprocess_portfolio_sortings(&$vars){
  $tags = array();
  $path = current_path();
  $query = drupal_get_query_parameters();
  $query +=array(
    'sort' => 'date',
    'order' => 'DESC',
  );

  $active_delta = isset($query['term']) ? $query['term'] : '*';
  $l_query = array('term' => $active_delta, 'sort' => $query['sort'], 'order' => $query['order']);

  $vars['tags'] = array('*' => t('View All')) + $vars['tags'];
  $i =0;

  foreach($vars['tags'] as $delta => $term) {
    $li_class = array();
    if ($i == 0) {
      $li_class[] = 'first';
    }else if ($i == count($vars['tags']) -1) {
      $li_class[] = 'last';
    }

    if ($delta == '*') {
      $filter = '*';
      $a_class = array('cat-all');
    }else {
      $filter = '.tid-'.$delta;
      $a_class = array('term-'.str_replace(' ', '_', $term));
    }

    $link = l($term, $path, array(
      'query' => array_merge($l_query, array('term' => $delta)),
      'options' => array(
        'absolute' => TRUE,
      ),
      'attributes' => array('data-filter' => $filter, 'class' => $a_class),
    ));
    if ($delta !=$active_delta) {
      $link = str_replace(' active', '', $link);
    }else {
      $li_class[] = 'selected';
    }

    $tags[] = array(
      'data' => $link,
      'class' => $li_class,
    );
    $i++;
  }

  $vars['attributes_array']['class'] = array('filter');
  $vars['attributes_array']['class'][] = isset($vars['filter_type']) ? ($vars['filter_type'] == 'ajax' ? 'with-ajax' : 'with-isotope') : 'with-isotope';
  $vars['attributes_array']['class'][] = 'ac-tabs';
  $vars['attributes_array']['class'][] = 'clearfix';

  $vars['style'] = explode(' ', $vars['style']);
  if (!empty($vars['style'])) {
    foreach ($vars['style'] as $style) {
      $vars['attributes_array']['class'][] = $style . '-style';
    }
  }
  $vars['tags_attrs']['class'] = array('tag-sortings');
  $vars['tags_attrs']['class'][] = 'clearfix';

  $vars['tags'] = theme('item_list', array('items' => $tags, 'attributes' => array('class'=> array('ac-tabs-tabs'))));


  $vars['extra_attrs']['class'] = array('ex-sortings');
  $vars['extra_attrs']['class'][] = 'clearfix';

  $ex_items = array();

  // @todo change 
  $date = l(t('date'), $path, array(
    'query' => array_merge($l_query, array('sort' => 'date')),
    'options' => array(
      'absolute' => TRUE,
    ),
    'attributes' => array('data-filter' => array('date')),
  ));

  if ($query['sort'] != 'date') {
    $date = str_replace('active', '', $date);
  }

  $title = l(t('title'), $path, array(
    'query' => array_merge($l_query, array('sort' => 'title')),
    'options' => array(
      'absolute' => TRUE,
    ),
    'attributes' => array('data-filter' => array('title')),
  ));

  if ($query['sort'] != 'title') {
    $title = str_replace('active', '', $title);
    $sep = '<span class="ac-switch left-active"></span>';
  }else {
    $sep = '<span class="ac-switch right-active"></span>';
  }

  $ex_items[] = array(
    'data' => $date . $sep . $title,
    'class' => array('date-title-filter', 'first'),
  );

  // @todo change
  $asc = l(t('Asc'), $path, array(
    'query' => array_merge($l_query, array('order' => 'ASC')),
    'options' => array(
      'absolute' => TRUE,
    ),
    'attributes' => array('data-filter' => array('asc')),
  ));
  if ($query['order'] != 'ASC') {
    $asc = str_replace('active', '', $asc);
  }

  $desc = l(t('Desc'), $path, array(
    'query' => array_merge($l_query, array('order' => 'DESC')),
    'options' => array(
      'absolute' => TRUE,
    ),
    'attributes' => array('data-filter' => array('desc')),
  ));
  if ($query['order'] != 'DESC') {
    $desc = str_replace('active', '', $desc);
    $sep = '<span class="ac-switch left-active"></span>';
  }else {
    $sep = '<span class="ac-switch right-active"></span>';
  }

  $ex_items[] = array(
    'data' => $asc .$sep .$desc,
    'class' => array('sort-order', 'last'),
  );

  $vars['extra_sortings'] = theme('item_list', array('items' => $ex_items, 'attributes' => array('class'=> array('ac-tabs-tabs'))));
}

/**
 * portfolio Nav
 */
function theme_portfolio_nav($vars){
  $out = '';
  if (isset($vars['node'])) {
    acquia_include('utility');
    $prev = acquia_node_sibling('prev', $vars['node']);
    $next = acquia_node_sibling('next', $vars['node']);

    $nav_index = variable_get('ac_portfolio_nav_index', NULL);
    if (!empty($nav_index)) {
      $label = '<span>' . t('portfolio') . '</span>';
      $label .= '<i class="icon-index"></i>';
      $index = l($label, $nav_index, array('absolute' => TRUE, 'html' => TRUE));
    }

    $out  = '<ul class="ac-portfolio-nav clearfix">';
    $out .= !empty($prev) ? '<li class="prev">'.$prev.'</li>' : NULL;
    $out .= !empty($index) ? '<li class="index">'.$index.'</li>' : NULL;
    $out .= !empty($next) ? '<li class="next">'.$next.'</li>' : NULL;
    $out .= '</ul>';
  }
  return $out;
}

