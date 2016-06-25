<?php
/**
 * @file
 * image.api.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function ac_commerce_image_default_styles() {
  $styles = array();

  $styles['commerce-product-carousel-preview'] = array(
    'name' => 'commerce-product-carousel-preview',
    'label' => 'Commerce - Product Page - Carousel preview',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '607',
          'height' => '808',
        ),
        'weight' => '1',
      ),
    ),
  );

  $styles['commerce-product-carousel-thumb'] = array(
    'name' => 'commerce-product-carousel-thumb',
    'label' => 'Commerce - Product Page - Carousel Thumbnail',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '128',
          'height' => '170',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
