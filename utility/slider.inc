<?php
//$Id
/**
 *
 */

function acquia_carousel_slider_prepeare_vars(&$vars) {
  if (isset($vars['items']) && !empty($vars['items'])) {
	// Build slider content
	$vars['settings'] = isset($vars['settings']) ? (array)$vars['settings'] : array();
	$vars['settings'] += array(
	  'id' => uniqid('ac-carousel-'),
	  'preview' => array(),
	  'thumb' => array(),
	  'style' => 'light',
	  'carousel_type' => 'horizontial',
	  'auto' => FALSE,
	  'pager' => FALSE,
	  'nav' => TRUE,
	);
	$vars['settings']['preview'] += array(
	  'cols' => 1,
	  'style' => '',
	  'frame' => '',
	  'lightbox' => FALSE,
	  'lightbox_style' => FALSE,
	);
	$vars['settings']['thumb'] += array(
	  'cols' => 4,
	  'style' => '',
	  'frame' => '',
	);

	$vars['wrap_attrs'] = array('class' => array($vars['settings']['id'] . '-container'));
	if ($vars['settings']['carousel_type'] == 'vertical') {
	  $vars['wrap_attrs']['class'][] = 'ac-vertical-carousel';
	}

	$vars['preview_attrs'] = array();
	$vars['preview_attrs']['id'] = $vars['settings']['id'];
	$vars['preview_attrs']['class'] = array('ac-thumb-slider', 'ac-master', 'ac-init-hidden', 'ac-preload-me');
	$vars['preview_attrs']['class'][] = $vars['settings']['style'] == 'dark' ? 'ac-darkstyle' : 'ac-lightstyle';
	if (isset($vars['settings']['class']) && !empty($vars['settings']['class'])) {
	  $vars['preview_attrs']['class'] = array_merge($vars['preview_attrs']['class'], $vars['settings']['class']);
	}
	// @todo settings
	$vars['preview_attrs']['data-sid']  = $vars['settings']['id'];
	$vars['preview_attrs']['data-auto']  = $vars['settings']['auto'];
	$vars['preview_attrs']['data-pager'] = $vars['settings']['pager'];
	$vars['preview_attrs']['data-nav']   = $vars['settings']['nav'];
	$vars['preview_attrs']['data-columns']  = $vars['settings']['preview']['cols'];
	$vars['preview_attrs']['data-thumbNav']  = TRUE;
	if (isset($vars['settings']['speed'])) {
	  $vars['preview_attrs']['data-speed'] = $vars['settings']['speed'];
	}
	if (isset($vars['settings']['timeout'])) {
	  $vars['preview_attrs']['data-timeout'] = $vars['settings']['timeout'];
	}

	// Inner attributes
	$vars['preview_i_attrs'] = array();
	$vars['preview_i_attrs']['class'] = array('slides');
	if ($vars['settings']['preview']['lightbox']) {
	  $vars['preview_i_attrs']['class'][] = 'ac-gallery-container';
	}

	$vars['preview_slides'] = array();
	$vars['thumb_slides'] = array();

	foreach ($vars['items'] as &$item) {

	  if (!isset($item['uri'])) {
		$item['uri'] = file_load($item['fid']);
	  }

	  if ($vars['settings']['preview']['lightbox']) {
		acquia_include('media');
		$image = array(
		  'fid' => $item['fid'],
		  'style' => array(
			'image_style' => $vars['settings']['preview']['style'],
			'lightbox' => TRUE,
			'lightbox_style' => $vars['settings']['preview']['lightbox_style'],
		  ),
		);
		$vars['preview_slides'][] = acquia_image_format_extended($image);
	  }else	if (!empty($vars['settings']['preview']['style'])) {
		$vars['preview_slides'][] = theme_image(array('path' => image_style_url($vars['settings']['preview']['style'], $item['uri'])));
	  }else {
		$vars['preview_slides'][] = theme_image(array('path' => file_create_url($vars['settings']['preview']['style'], $item['uri'])));
	  }

	  // Thumb slides
	  if (!empty($vars['settings']['thumb']['style'])) {
		$vars['thumb_slides'][] = image_style_url($vars['settings']['thumb']['style'], $item['uri']);
	  }else {
		$vars['thumb_slides'][] = file_create_url($item['uri']);
	  }

	}
	$vars['thumbs_slider'] = get_thumb_slider_js($vars['settings'], $vars['thumb_slides']);
  }

}

/**
 * @TODO document here
 */
function get_thumb_slider_js($settings, $thumbs){
  $slider_id = $settings['id'];
  $carousel_id = $slider_id . '-thumb';
  $direction = isset($settings['carousel_type']) && $settings['carousel_type'] == 'vertical' ? 'vertical' : 'horizontial';

  $max_items = '';
  if ($direction == 'vertical') {
	$max_items = 1;
  }
  $slider_attrs = array();
  $slider_attrs['id'] = $carousel_id;
  $slider_attrs['class'] = array('ac-thumb-slider', 'ac-slave', 'ac-init-hidden', 'ac-preload-me');
  $slider_attrs['data-sid'] = $slider_id;
  $slider_attrs['data-max'] = $max_items;

  $out = '<div'.drupal_attributes($slider_attrs).'>';
  foreach ($thumbs as $thumb) {
	$out .= '<img src="'.$thumb.'" />';
  }
  $out .= '</div>';
  return $out;
}