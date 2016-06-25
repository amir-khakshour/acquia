<?php

/**
 * @file
 *  Contains helper functions to build and override theme functions
 */

/**
 * Implements hook_preprocess_node()
 */
function ac_blog_preprocess_node(&$vars){
  if (isset($vars['node']->type) && $vars['node']->type == 'blog') {
    // Different template for each view mode
    $vars['theme_hook_suggestions'][] = 'node__blog_' . $vars['view_mode'];
    if ($vars['view_mode'] != 'teaser') {
      ac_blog_full_page_view($vars);
    }else {
      ac_blog_teaser_page_view($vars);
    }
  }
}

/**
 * Implements hook_theme().
 */
function ac_blog_theme() {
  $path = drupal_get_path('module', 'ac_blog') . '/theme';
  $items = array();

  $items['blog_recent'] = array(
      'variables' => array(
          'settings' => array(),
      ),
      'template' => 'blog-block',
      'path' => $path,
  );

  $items['blog_related'] = array(
      'variables' => array(
          'nid' => NULL,
      ),
      'template' => 'blog-block',
      'path' => $path,
  );

  $items['ac_blog_preview_media'] = array(
      'variables' => array(
          'items' => NULL,
      ),
      'template' => 'ac-blog--preview-media',
      'path' => $path,
  );

  $items['ac_blog_about_author'] = array(
      'variables' => array(
          'items' => NULL,
      ),
      'template' => 'ac-blog--about-author',
      'path' => $path,
  );

  acquia_include('options', 'ac_blog');
  // item view
  foreach (array_keys(ac_blog_appearance()) as $style) {
    $items['blog_appearance_' . $style] = array(
        'variables' => array(
            'item' => array(),
            'settings' => array(),
        ),
        'template' => 'blog-appearance-'.$style,
        'path' => $path . '/appearance',
    );
  }

  // item view
  foreach (array_keys(ac_blog_appearance()) as $style) {
    $items['blog_view_' . $style] = array(
        'variables' => array(
            'item' => array(),
            'settings' => array(),
        ),
        'template' => 'blog-view-'.$style,
        'path' => $path . '/view',
    );
  }
  return $items;
}

/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_related(&$vars){
  acquia_include('content');
  acquia_include('utility', 'ac_blog');
  acquia_include('media', 'ac_blog');
  acquia_include('options', 'ac_blog');

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
  ac_blog_prepare_block_settings($settings);
  $items = ac_blog_get_related_items($node);
  if ($items && !empty($items)) {
    foreach ($items as $item) {
      $item = ac_blog_prepare_view($item, $settings);
      if (isset($settings['view'])) {
        $vars['items'][] = theme('blog_view_' .$settings['view'], $item );
      }
    }
  }

  $vars['items'] = array_filter($vars['items'], 'strlen');

  $vars['wrapper_attrs']['id'] = 'ac-related-news';
  $vars['wrapper_attrs']['class'] = array('ac-related-news');
  $vars['wrapper_attrs']['class'][] = 'ac-s-li';
  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('cols'), $settings, CHECK_LENGTH);
  $vars['wrapper_attrs']['data-columns'] = acquia_variable_get('related_news_cols', 4);

  $vars['outter_attrs']['class']   = array('blog-items');
  $vars['outter_attrs']['class'][] = 'ac-view-thumb';
  $vars['outter_attrs']['class'][] = 'blog-view-' . $settings['view'];
  $vars['outter_attrs']['class'][] = acquia_variable_get('related_news_spaced', TRUE) ? 'ac-spaced' : 'ac-no-spaced';
  if ($settings['view'] == 'circled') {
    $vars['wrapper_attrs']['class'][] = 'ac-grid';
    $vars['wrapper_attrs']['class'][] = 'ac-mini-feature';
  }
}

/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_appearance_masonry(&$vars){
  ac_blog_preprocess_blog_recent($vars);
}
/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_appearance_grid(&$vars){
  ac_blog_preprocess_blog_recent($vars);
}
/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_appearance_timeline(&$vars){
  ac_blog_preprocess_blog_recent($vars);
}
/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_appearance_scroller(&$vars){
  ac_blog_preprocess_blog_recent($vars);
}
/**
 * @TODO document here
 */
function ac_blog_preprocess_blog_recent(&$vars){
  acquia_include('utility', 'ac_blog');
  acquia_include('media', 'ac_blog');
  $vars['items'] = array();

  $settings = isset($vars['settings']) ? $vars['settings'] : array();
  if ($settings['appearance'] == 'timeline') {
    $settings['picture'] = TRUE;
  }
  ac_blog_prepare_block_settings($settings);
  $items = ac_blog_get_recent_items($settings);
  $vars['pager'] = isset($items['pager_pager']) ? $items['pager_pager'] : '';
  if (!isset($items['pager_nodes']) || empty($items['pager_nodes'])){
    return;
  }
  $items = $items['pager_nodes'];

  $tags = array();
  $i =0;
  if ($items && !empty($items)) {
    foreach ($items as $item) {
      $item = ac_blog_prepare_view($item, $settings);
      if (isset($settings['appearance'])) {
        if ($settings['appearance'] == 'timeline') {
          $classes = array();
          $classes[] = 'node-' . $item['type'];
          $classes[] = 'node-' . $item['nid'];
          $classes[] = $i%2 == 0? 'odd' : 'even';
          $classes[] = 'ac-col';
          $classes[] = 'ac-animate';
          if ($i == 0) {
            $classes[] = 'first';
          }else if ($i == count($items)-1) {
            $classes[] = 'last';
          }
          $classes = array_filter($classes, 'strlen');
          $classes = implode(' ', $classes);
          $vars['items'][] = array('date' => $item['created'], 'content' => theme('blog_view_' .$settings['appearance'], $item), 'class' => $classes);
        }else {
          $vars['items'][] = theme('blog_view_' .$settings['appearance'], $item );
        }
        $i++;
      }
    }
  }

  $settings['framed'] = $settings['frame'];

  //$vars['items'] = array_filter($vars['items'], 'strlen');
  $vars['outter_attrs']['class'][] = 'ac-blog';
  $vars['outter_attrs']['class'][] = isset($settings['spaced']) && $settings['spaced'] ? 'ac-spaced' : 'ac-no-sapced';
  $vars['outter_attrs']['class'][] = 'ac-s-li';
  $vars['outter_attrs']['class'][] = isset($settings['fullwidth']) && $settings['fullwidth'] ? 'ac-full-container-width' : NULL;
  $vars['outter_attrs']['class'][] = 'blog-view-' . $settings['appearance'];
  acquia_include('content');
  // -- Container
  $vars['wrapper_attrs']['id'] = $settings['id'];
  $vars['wrapper_attrs']['class'] = array('blog-items', 'clearfix');
  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('framed'), $settings, CHECK_LENGTH);

  if ($settings['appearance'] != 'timeline') {
    $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('cols'), $settings, CHECK_LENGTH);
  }
  // in case of infscroller
  $vars['wrapper_attrs']['class'][] = 'pager-target';
  $vars['wrapper_attrs']['class'][] = acquia_get_class_by_args(array('appearance'), $settings, CHECK_LENGTH);

  if (isset($settings['appearance']) && $settings['appearance'] == 'scroller') {
    // Scroller
    acquia_load_resources('carousel');
    $vars['wrapper_attrs']['class'][] = 'ac-carousel';
    $vars['wrapper_attrs']['class'][] = 'owl-carousel';
    $vars['wrapper_attrs']['class'][] = 'owl-theme';
    $vars['wrapper_attrs']['class'][] = 'ac-init-hidden';
    $vars['wrapper_attrs']['class'][]= 'ac-appearance-grid';
    $vars['wrapper_attrs']['data-columns'] = isset($settings['cols']) ? $settings['cols'] : acquia_variable_get('blog_recent_cols', 4);
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

    $vars['pager'] = '';
    if ($settings['cols'] == 1) {
      $vars['outter_attrs']['class'][] = 'ac-mini-nav';
    }
  }elseif($settings['appearance'] == 'masonry') {
    $vars['wrapper_attrs']['class'][] = 'ac-init-hidden';
    // Masonry view
    acquia_load_resources('isotope');
  }elseif($settings['appearance'] == 'grid' || $settings['appearance'] == 'teaser') {
    $vars['wrapper_attrs']['class'][] = 'ac-init-hidden';
    $vars['wrapper_attrs']['class'][]= 'ac-appearance-masonry';
    // Grid view
    acquia_load_resources('isotope');
  }else if ($settings['appearance'] == 'circled') {
    $vars['wrapper_attrs']['class'][] = 'ac-mini-feature';
  }

  if ($settings['appearance'] != 'timeline') {
    $vars['wrapper_attrs']['data-padding'] = $settings['spaced'] ? $settings['padding'] : 0;
    $vars['wrapper_attrs']['data-columns'] = $settings['cols'];
  }

  $vars['outter_attrs']['class'] = array_filter($vars['outter_attrs']['class'], 'strlen');
  $vars['outter_attrs']['class'] = implode(' ', $vars['outter_attrs']['class']);

  $vars['wrapper_attrs']['class'] = array_filter($vars['wrapper_attrs']['class'], 'strlen');
  $vars['wrapper_attrs']['class'] = implode(' ', $vars['wrapper_attrs']['class']);
}

/**
 * Implements hook_theme_registry_alter()
 */
function ac_blog_theme_registry_alter(&$theme_registry) {
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
/**
 * Teaser view of blog pages
 */
function ac_blog_teaser_page_view(&$vars){
  $vars['container_attributes'] = array();
  $vars['container_attributes']['class'] = '';
  $vars['attributes_array']['id'] = 'node-' .$vars['node']->nid;
  $vars['attributes_array']['class'][] = 'ac-node-blog';
  $vars['attributes_array']['class'][]= ' ac-teaser-view';
  $vars['attributes_array']['class'][]= ' block';
  $vars['media_classes'] = 'media ac-col ac-one-third clearfix';
  $vars['desc_classes'] = 'description ac-col ac-two-third clearfix';
  //ac_blog_prepare_thumb_view
  // Media HTML and view project

  if (isset($vars['node']->nodemeta)) {
    acquia_include('media', 'ac_blog');

    // Create media HTML
    $settings = isset($vars['settings']) ? $vars['settings'] : array();
    $settings += array('style' => 'rectangle-medium');
    ac_blog_prepare_block_settings($settings);
    unset($vars['date']);
    $vars +=ac_blog_get_teaser_extra((array)$vars['node'], $settings);
  }
}

/**
 * Full page view of blog pages
 */
function ac_blog_full_page_view(&$vars){
  acquia_include('utility');
  $vars['container_attributes'] = array();
  $vars['container_attributes']['class'] = '';
  $vars['attributes_array']['class'][] = 'ac-node-blog';
  $vars['attributes_array']['class'][]= ' ac-full-view';

  $vars['media_classes'] = 'media clearfix';
  $vars['desc_classes'] = 'description clearfix';

  // Media HTML and view project
  if (isset($vars['node']->nodemeta)) {
    $meta = $vars['node']->nodemeta;

    if (isset($meta['thumb']['type']) && $meta['thumb']['type'] == 'video') {
      $media['media_type'] = $meta['thumb']['type'];
    }else {
      $media['media_type'] = 'image';
    }
    $media['items'] = isset($meta['thumb']['media']) ? $meta['thumb']['media'] : array();

    if (isset($meta['misc']['custom_frame']) && $meta['misc']['custom_frame']) {
      $media['frame'] = $meta['misc']['frame'];
    }

    // Create media HTML
    $vars['media'] = theme('ac_blog_preview_media', $media);
    $vars += isset($meta['misc']) ? $meta['misc'] : array();
    $vars['attributes_array']['class'][]= isset($media['media_type']) &&
    !empty($media['media_type']) ? ' ac-'.$media['media_type'].'-media' : '';
  }else {
    $vars['media'] = '';
    $vars['link'] = '';
  }

  // Date
  $vars['date'] = format_date($vars['created'], "custom", "F jS, Y");

  // Share links
  $vars['share_links'] = theme('acquia_share_links', array('node' => $vars['node'], 'socials' => array_filter(array_values(variable_get('ac_blog_share_links')))));

  // About Author
  $vars['about_author'] = theme('ac_blog_about_author', array('uid' => $vars['uid']));
  //// Like button
  //if (variable_get('ac_blog_like_enabled', TRUE)) {
  //  $flag = flag_get_flag(AC_blog_LIKE_FLAG_MN);
  //  $vars['like_btn'] = '';
  //  if ($flag) {
  //    $vars['like_btn'] = $flag->theme($flag->is_flagged($vars['node']->nid) ? 'unflag' : 'flag', $vars['node']->nid);
  //  }
  //}
  //
  // Prev Next Links
  //$vars['blog_nav'] = theme('blog_nav', array('node' => $vars['node']));
}

/**
 * @TODO document here
 */
function ac_blog_preprocess_ac_blog_about_author(&$vars) {
  if (isset($vars['uid'])) {
    $user = user_load($vars['uid']);
    $link = 'user/' . $user->uid;
    if (isset($user->picture->fid)) {
      $picture = theme('user_picture', array('account' => $user));
    }else {
      $picture = theme('acquia_default_avatar');
    }

    $vars['picture'] = $picture;
    $vars['biography'] = field_view_field('user', $user, 'field_biography');;
  }
  else {
    $vars['picture'] = '';
    $vars['biography'] = array();
    $vars['biography'] = array();
  }
  $vars['name'] = l($user->name, $link, array('absolute' => TRUE, 'html' => TRUE));
}

/**
 * @TODO document here
 */
function ac_blog_preprocess_ac_blog_preview_media(&$vars) {
  if (isset($vars['items']) && !empty($vars['items'])) {
    acquia_include('media');
    acquia_include('utility');
    if (count($vars['items']) >1) {
      $vars['view'] = 'slideshow';
      acquia_load_resources('slider');
    }else {
      $vars['view'] = 'simple';
    }

    foreach($vars['items'] as &$item) {
      if (isset($item['fid']) && $item['fid'] != 0) {
        $file_path =  '';

        if ($vars['media_type'] == 'image') {
          $item['style']['image_style'] = isset($vars['view']) ? variable_get('ac_blog_preview_style', NULL) : NULL;
          if (!empty($vars['frame'])) {
            $item['style']['frame'] = $vars['frame'];
          }else if (variable_get('ac_blog_image_frame', NULL)) {
            $item['style']['frame'] = variable_get('ac_blog_image_frame', NULL);
            $item['style']['frame'] = ($item['style']['frame'] == 'sw') ? acquia_theme_get_settings('image_frame', null, 'shortcodes') : $item['style']['frame'];
          }
          $item['file'] = acquia_image_format_extended($item);
        }else {
          $item['style']['video_style'] = isset($vars['view']) ? variable_get('ac_blog_preview_style', NULL) : NULL;
          $item['file'] = acquia_video_format_extended($item);
        }
      }
    }
  }
}