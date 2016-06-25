<?php
/**
 * @file
 * image.api.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function acquia_image_default_styles() {
  $styles = array();

  // Exported image style: default-image
  $styles['default-image'] = array(
    'name' => 'default-image',
    'label' => 'Default Image - No Style',
    'effects' => array(),
  );

  // Exported image style: default-image
  $styles['default-image-medium'] = array(
    'name' => 'default-image-medium',
    'label' => 'Default Image - Medium Width size (940xY)',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 940,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );


  $styles['default-image-h-medium'] = array(
    'name' => 'default-image-h-medium',
    'label' => 'Default Image - Medium Height size (Xx640)',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 640,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: default-image
  $styles['page-title'] = array(
    'name' => t('page-title-region'),
    'label' => 'Page title (1600x350)',
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
          'height' => '350',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['square-tiny'] = array(
    'name' => 'square-tiny',
    'label' => 'Square - tiny (75x75)',
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
          'width' => '75',
          'height' => '75',
        ),
        'weight' => '1',
      ),
    ),
  );
  // Exported image style: portrait-mobile
  $styles['square-thumb'] = array(
    'name' => 'square-thumb',
    'label' => 'Square - Thumb (180x180)',
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
          'width' => '180',
          'height' => '180',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['square-x-thumb'] = array(
    'name' => 'square-x-thumb',
    'label' => 'Square - X-Thumb (240x240)',
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
          'width' => '240',
          'height' => '240',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['square-small'] = array(
    'name' => 'square-small',
    'label' => 'Square - Small (320x320)',
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
          'width' => '320',
          'height' => '320',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['square-medium'] = array(
    'name' => 'square-medium',
    'label' => 'Square - Medium (640x640)',
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
          'width' => '640',
          'height' => '640',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['square-large'] = array(
    'name' => 'square-large',
    'label' => 'Square - Large (940x940)',
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
          'height' => '940',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-thumb'] = array(
    'name' => 'rectangle-thumb',
    'label' => 'Rectangle - Thumb (75x46)',
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
          'width' => '115',
          'height' => '70',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-small'] = array(
    'name' => 'rectangle-small',
    'label' => 'Rectangle - Small (280x175)',
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
          'width' => '280',
          'height' => '175',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-medium'] = array(
    'name' => 'rectangle-medium',
    'label' => 'Rectangle - Medium (640x395)',
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
          'width' => '640',
          'height' => '395',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-large'] = array(
    'name' => 'rectangle-large',
    'label' => 'Rectangle - Large (940x705)',
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
          'height' => '705',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style:
  $styles['rectangle-v-thumb'] = array(
    'name' => 'rectangle-vertical-thumb',
    'label' => 'Vertical Rectangle - Thumb (68x110)',
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
          'width' => '68',
          'height' => '110',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-v-small'] = array(
    'name' => 'rectangle-vertical-small',
    'label' => 'Vertical Rectangle - Small (110x175)',
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
          'width' => '110',
          'height' => '175',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-v-medium'] = array(
    'name' => 'rectangle-vertical-medium',
    'label' => 'Vertical Rectangle - Medium (270x380)',
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
          'width' => '270',
          'height' => '380',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-v-large'] = array(
    'name' => 'rectangle-vertical-large',
    'label' => 'Vertical Rectangle - Large (705x940)',
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
          'width' => '705',
          'height' => '940',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-hr-thumb'] = array(
    'name' => 'rectangle-horizontal-thumb',
    'label' => 'Horizontal Rectangle - Thumb (102x68)',
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
          'width' => '102',
          'height' => '68',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-hr-small'] = array(
    'name' => 'rectangle-horizontal-small',
    'label' => 'Horizontal Rectangle - Small (204x136)',
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
          'width' => '204',
          'height' => '136',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-hr-medium'] = array(
    'name' => 'rectangle-horizontal-medium',
    'label' => 'Horizontal Rectangle - Medium (307x204)',
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
          'width' => '307',
          'height' => '204',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: portrait-mobile
  $styles['rectangle-hr-large'] = array(
    'name' => 'rectangle-horizontal-large',
    'label' => 'Horizontal Rectangle - Large (614x408)',
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
          'width' => '614',
          'height' => '408',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: node-default
  $styles['node-default'] = array(
    'name' => 'node-default',
    'label' => 'Node - Full (890x560)',
    'effects' => array(
      7 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '890',
          'height' => '560',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: node-default-half
  $styles['node-default-half'] = array(
    'name' => 'node-default-half',
    'label' => 'Node - Half (450x260)',
    'effects' => array(
      11 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '450',
          'height' => '260',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['user-thumb'] = array(
    'name' => 'User Thumbnail',
    'label' => 'User Thumbnail - (75x75)',
    'effects' => array(
      8 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '75',
          'height' => '75',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['h-slider'] = array(
    'name' => 'Horizontial slider',
    'label' => 'Horizontial slider - Half (1140x450)',
    'effects' => array(
      8 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '1140',
          'height' => '450',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['equal-height-t'] = array(
    'name' => 'Equal height',
    'label' => 'Equal height - Tiny (Xx75)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 75,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['equal-height-s'] = array(
    'name' => 'Equal height',
    'label' => 'Equal height - Small (Xx200)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 200,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['equal-height'] = array(
    'name' => 'Equal height',
    'label' => 'Equal height - medium (Xx350)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 350,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );


  // Exported image style: user-thumb
  $styles['equal-width-t'] = array(
    'name' => 'Equal Width',
    'label' => 'Equal Width - Tiny (Xx75)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 75,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['equal-width-s'] = array(
    'name' => 'Equal Width',
    'label' => 'Equal width - Small (Xx200)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 200,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: user-thumb
  $styles['equal-width'] = array(
    'name' => 'Equal Width',
    'label' => 'Equal width - medium (Xx350)',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 350,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );
  return $styles;
}
