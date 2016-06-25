<?php
$out = '';
$thumb = array ();
if (is_array ( $slides )) {
	$sliderStyle = isset ( $slides ['properties'] ['sliderstyle'] ) ? $slides ['properties'] ['sliderstyle'] : '';
	$width = isset ( $slides ['properties'] ['fullwidth'] ) && $slides ['properties'] ['fullwidth'] =='true' ? '100%' : $slides ['properties'] ['width'];

	// Video Layer type options
	$video['options'] = array('width' => $width);
	if (isset($slides ['properties'] ['height'])) {
		$video['height'] = $slides ['properties'] ['height'];
	}

    $style = FALSE;
	if (isset($slides['properties']['bg_style']) && !empty($slides['properties']['bg_style'])) {
	   $style = $slides['properties']['bg_style'];
		$video['style']['video_style'] = $style;
	}

	$class = 'flexslider';
	if (isset($slides['properties']['compact']) && $slides['properties']['compact'] == 'true') {
		$class .= ' ac-compact-slider';
	}

	if (isset($slides['properties']['free_caption']) && $slides['properties']['free_caption'] == 'true') {
		$class .= ' ac-cption-free';
	}

	if (ac_slider_getParam("controlNav","false", $slides['properties']) == 'false') {
		$class .= ' ac-no-pager';
	}


	if (isset($slides['properties']['bgColor']) && !empty($slides['properties']['bgColor'])) {
		$out .= '<div class="flex-wrap clearfix" style="background-color:'.$slides['properties']['bgColor'].'">';
	}

	$out .= '<div id="' . $slide_id . '" class="'.$class.'" style="width: ' . ac_check_unit ( $width ) . '; max-width:100%; margin-left: auto; margin-right: auto; ' . $sliderStyle . '">';
	$out .= '<ul class="slides">';
	if (is_array($slides['layers'] )) {
		foreach ( $slides ['layers'] as $layerkey => $layer ) {
			$layer_attrs = array();
			// ID
			if (!empty($layer['properties']['id'])){
				$layer_attrs['id'] = $layer['properties']['id'];
			}

			// Layer thumbnail
			if (isset($slides ['properties']['thumbNav']) && $slides['properties']['thumbNav'] == 'true' && isset($layer['properties']['thumbnail_formatted'])){
				$layer_attrs['data-thumb'] = $layer['properties']['thumbnail_formatted'];
			}

			$out .= '<li' . drupal_attributes($layer_attrs) . '>';
			// Layer background
			$media_type = '';

			if (isset($layer['properties']['background_fid']) && !empty($layer['properties']['background_fid'])) {
				$file = file_load($layer['properties']['background_fid']);
				if (isset($file->uri)) {
					if ($style) {
						$bg = image_style_url($style, $file->uri);
					}else{
						$bg = file_create_url($file->uri);
					}
					$media = '<img src="' . $bg . '" alt="' . t ( 'Slide background' ) . '">';
				}
			}else if (!empty($layer['properties']['background'])) {
				$media_type = 'image';
				$media = '<img src="' . $layer ['properties'] ['background'] . '" alt="' . t ( 'Slide background' ) . '">';
			}else if (!empty($layer['properties']['video_fid'])) {
				acquia_include('media');
				$video['fid'] = $layer['properties']['video_fid'];
				$media = acquia_video_format_extended($video);
			}

			if (isset($layer['properties']['link']) &&
				!empty($layer['properties']['link']) &&
				$media_type == 'image') {
				$options = array('html' => TRUE, 'absolute' => TRUE);
				$options['target'] = isset($layer['properties']['link_open_in']) ? $layer['properties']['link_open_in'] : '_self';
				$media = l($media, $layer['properties']['link'], $options);
			}
			$out .= $media;
			if (isset($layer['properties']['caption']) && !empty($layer['properties']['caption'])) {
				$out .= '<div class="flex-caption ac-type-hidden-phone"><div class="caption-inner">';
				$out .= check_markup($layer['properties']['caption'], 'full_html');
				$out .= '</div></div>';
			}

			$out .= '</li>';
		}
	}
	$out .= '</ul>';
	$out .= '</div>';
	if (isset($slides['properties']['bgColor']) && !empty($slides['properties']['bgColor'])) {
		$out .= '</div>';
	}
}

print $out;

if (isset($slides['properties']['thumbNav']) && $slides['properties']['thumbNav'] == 'true') {
	$slides['properties']['controlNav'] = 'thumbnails';
}
?>
<script type="text/javascript">

(function ($) {

	$(document).ready(function() {

    if (jQuery().flexslider) {

      $('#<?php echo $slide_id?>').flexslider({
        animation:<?php echo ac_slider_getParam("animation","fade", $slides['properties']) ?>,
        easing:<?php echo ac_slider_getParam("easing","swing", $slides['properties']) ?>,
        direction:<?php echo ac_slider_getParam("direction","horizontal", $slides['properties']) ?>,
        animationLoop:<?php echo ac_slider_getParam("animationLoop","false", $slides['properties']) ?>,
        startAt:<?php echo ac_slider_getParam("startAt","0", $slides['properties']) ?>,
        slideshow:<?php echo ac_slider_getParam("slideshow","false", $slides['properties']) ?>,
        slideshowSpeed:<?php echo ac_slider_getParam("slideshowSpeed","7000", $slides['properties']) ?>,
        animationSpeed:<?php echo ac_slider_getParam("animationSpeed","600", $slides['properties']) ?>,
        initDelay:<?php echo ac_slider_getParam("initDelay","0", $slides['properties']) ?>,
        pauseOnAction:<?php echo ac_slider_getParam("pauseOnAction","false", $slides['properties']) ?>,
        useCSS:<?php echo ac_slider_getParam("useCSS","true", $slides['properties']) ?>,
        touch:<?php echo ac_slider_getParam("touch","true", $slides['properties']) ?>,
        controlNav:<?php echo ac_slider_getParam("controlNav","false", $slides['properties']) ?>,
        thumbNav:<?php echo ac_slider_getParam("thumbNav","false", $slides['properties']) ?>,
        directionNav:<?php echo ac_slider_getParam("directionNav","false", $slides['properties']) ?>,
        itemWidth:<?php echo ac_slider_getParam("itemWidth","0", $slides['properties']) ?>,
        itemMargin:<?php echo ac_slider_getParam("itemMargin","0", $slides['properties']) ?>,
        minItems:<?php echo ac_slider_getParam("minItems","1", $slides['properties']) ?>,
        maxItems:<?php echo ac_slider_getParam("maxItems","0", $slides['properties']) ?>,
        move:<?php echo ac_slider_getParam("move","0", $slides['properties']) ?>,
        prevText: '<i class="icon-left-open-big"></i>',
        nextText: '<i class="icon-right-open-big"></i>',
				start: function(){
					if (jQuery().waypoint) {
					}
				},
      });
    }
  });

})(jQuery);

</script>