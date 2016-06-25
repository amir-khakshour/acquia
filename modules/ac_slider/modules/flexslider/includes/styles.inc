<?php
/**
 * @file
 * image.api.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function flexslider_image_default_styles() {
  $styles = array();

  // Exported image style: default-image
  $styles['flexslider_slide'] = array(
      'name' => 'flexslider-slide',
      'label' => 'FlexSlider - Slide size (940x434)',
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
                  'width' => '940',
                  'height' => '434',
              ),
              'weight' => '1',
          ),
      ),
  );

  // Exported image style: default-image
  $styles['flexslider_slider-compact'] = array(
      'name' => 'flexslider-compact',
      'label' => 'FlexSlider - Compact size (1200x540)',
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
                  'width' => '1200',
                  'height' => '540',
              ),
              'weight' => '1',
          ),
      ),
  );

  // Exported image style: default-image
  $styles['flexslider_slider-wide'] = array(
      'name' => 'flexslider-wide',
      'label' => 'FlexSlider - wide size (1600x610)',
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
                  'width' => '1600',
                  'height' => '610',
              ),
              'weight' => '1',
          ),
      ),
  );

  // Exported image style: default-image
  $styles['flexslider_slider-horizontal'] = array(
      'name' => 'flexslider-wide',
      'label' => 'FlexSlider - horizontal (1600x320)',
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
                  'width' => '1600',
                  'height' => '320',
              ),
              'weight' => '1',
          ),
      ),
  );

  return $styles;
}
