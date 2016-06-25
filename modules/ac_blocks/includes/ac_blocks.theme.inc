<?php
/**
 * @file
 * Theme functions for the DiamondLayers blocks module.
 */

/**
 * Returns the rendered branding.
 *
 * @ingroup themeable
 */
function theme_ac_recent_posts($variables) {
  $rows = array();
  $output = '';

  foreach ($variables['nodes'] as $node) {
    $rows[] = l($node->title, 'node/'.$node->nid, array('absolute' => TRUE));
  }

  if (!empty($rows)) {
    $output = '<div class="ac-side-menu">';
    $output .= theme('item_list', array('items' => $rows, 'attributes' => array('class' => array('menu'))));
    $output .= '</div>';
  }

  return $output;
}

/**
 * Returns the rendered branding.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_branding($variables) {
  $logo = theme('ac_blocks_logo', $variables);
  $site_name = theme('ac_blocks_site_name', $variables);
  $site_slogan = theme('ac_blocks_site_slogan', $variables);

  $attributes['class'] = array('site-name-slogan');
  
  if ($variables['site_name_hidden'] && $variables['site_slogan_hidden']) {
    $attributes['class'][] = 'element-invisible';
  }
  
  return $logo . '<hgroup' . drupal_attributes($attributes) . '>' . $site_name . $site_slogan . '</hgroup>';
}

/**
 * Returns the rendered logo.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_logo($variables) {
  if ($variables['logo']) {
    $image = array(
      '#theme' => 'image',
      '#path' => $variables['logo'],
      '#alt' => $variables['site_name'],
    );
    
    $image = render($image);
  
    if ($variables['logo_linked']) {
      $options['html'] = TRUE;
      $options['attributes']['id'] = 'logo';
      $options['attributes']['title'] = t('Return to the @name home page', array('@name' => $variables['site_name']));
      
      $image = l($image, '<front>', $options);
    }
  
    return '<div class="logo-img">' . $image . '</div>';
  }
}

/**
 * Returns the rendered site name.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_site_name($variables) {
  // If there is no page title set for this page, use a h1 for the site name.
  $tag = drupal_get_title() !== '' ? 'h2' : 'h1';
  $site_name = $variables['site_name'];
  
  if ($variables['site_name_linked']) {
    $options['html'] = TRUE;
    $options['attributes']['title'] = t('Return to the @name home page', array('@name' => $variables['site_name']));

    $link = array(
      '#theme' => 'link',
      '#path' => '<front>',
      '#text' => '<span>' . $site_name . '</span>',
      '#options' => $options,
    );
    
    $site_name = render($link);
  }
  
  $attributes['class'] = array('site-name');
  
  if ($variables['site_name_hidden']) {
    $attributes['class'][] = 'element-invisible';
  }

  return '<' . $tag . drupal_attributes($attributes) . '>' . $site_name . '</' . $tag . '>';
}

/**
 * Returns the rendered site slogan.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_site_slogan($variables) {
  if ($variables['site_slogan'] !== '') {
    $attributes['class'] = array('site-slogan');
    
    if ($variables['site_slogan_hidden']) {
      $attributes['class'][] = 'element-invisible';
    }
    
    return '<h6' . drupal_attributes($attributes) . '>' . $variables['site_slogan'] . '</h6>';
  }
}

/**
 * Returns the rendered page title.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_page_title($variables) {

  if ($variables['page_title'] !== '' || $variables['page_title'] !== '' ) {
   
    $attrs['id'] = 'page-title';
    $attrs['class'][] = 'page-title';
    
    if ($variables['page_title_hidden']) {
      $attrs['class'][] = 'element-invisible';
    }
		
    $sub_attrs['id'] = 'page-subtitle';
    $sub_attrs['class'][] = 'subtitle';

    $out = '';
    if (!empty($variables['page_title'])) {
      $out.= '<h1' . drupal_attributes($attrs) . '>' . $variables['page_title'] . '</h1>';
    }
    if (!empty($variables['page_subtitle'])) {
      $out.= '<h3' . drupal_attributes($sub_attrs) . '>' . $variables['page_subtitle'] . '</h3>';
    }

    if (isset($variables['fancy']) && $variables['fancy']) {
      $out = '<div class="ac-init-hidden">' .$out .'</div>';
    }
    return $out;
  }
}

/**
 * Returns the rendered breadcrumb.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_breadcrumb($variables) {
  $output = '';
  $items = array();
  
  if (!empty($variables['breadcrumb'])) {
		if (isset($variables['breadcrumb_current'])) {
			$variables['breadcrumb'][] = l(drupal_get_title(), current_path(), array('html' => TRUE));
		}
    $output = '<div class="container"><nav id="breadcrumb" class="clearfix">';
    $switch = array('odd' => 'even', 'even' => 'odd');
    $zebra = 'even';
    $last = count($variables['breadcrumb']) - 1;   
     
    foreach ($variables['breadcrumb'] as $key => $item) {
      $zebra = $switch[$zebra];
      $attributes['class'] = array('depth-' . ($key + 1), $zebra);
       
      if ($key == 0) {
        $attributes['class'][] = 'first';
      }
       
      if ($key == $last) {
        $attributes['class'][] = 'last';
      }
 
      $items[] = $item;
    }
 
		$seperator = '<i class="sep"></i>';
		$output .= '<div class="breadcrumb">'. implode($seperator, $items) . "</div>";
    $output .= '</nav></div>';
  }
  
  return $output;
}

/**
 * Returns the rendered action items.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_action_links($variables) {
  $actions = render($variables['action_links']);
  
  if (!empty($actions)) {
    return '<div id="action-links" class="clearfix"><ul class="action-links">' . $actions . '</ul></div>';
  }
}

/**
 * Returns the rendered feed icons.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_feed_icons($variables) {
  return $variables['feed_icons'];
}

/**
 * Returns the rendered menu local tasks.
 *
 * @ingroup themeable
 */
function theme_ac_blocks_tabs($variables) {
  $tabs = theme('menu_local_tasks', $variables);
  
  if (!empty($tabs)) {
    return '<div id="tabs" class="clearfix">' . $tabs . '</div>';
  }
}

/**
 * 
 * @ingroup themeable
 */
function template_preprocess_ac_recent_posts($variables) {
}

