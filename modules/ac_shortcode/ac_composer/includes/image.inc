<?php
/**
 * @file
 * image.api.php
 */

/**
 * Implements hook_image_default_styles().
 */
function ac_composer_image_default_styles() {
  $styles = array();

  // Exported image style: composer-image-preview
  $styles[ACQUIA_COMPOSER_IMAGE_STYLE] = array(
    'name' => ACQUIA_COMPOSER_IMAGE_STYLE,
    'label' => 'Diamond Builder - image (32x32)',
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
          'width' => '32',
          'height' => '32',
        ),
        'weight' => '1',
      ),
    ),
  ); 

  return $styles;
}
