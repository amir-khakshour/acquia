<?php
/**
 * @file
 * image.api.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function elastic_slider_image_default_styles() {
  $styles = array();

	// Exported image style: default-image
  $styles['elastic_slider_thumb'] = array(
    'name' => 'elastic-slider-thumb',
		'label' => 'Elastic Slider - Thumbnail size (150x60)',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '150',
          'height' => '60',
        ),
        'weight' => '1',
      ),
    ),
  );
  return $styles;
}
