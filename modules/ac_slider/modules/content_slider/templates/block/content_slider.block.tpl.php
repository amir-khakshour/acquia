<?php
$out = '';
if (is_array ( $slides )) {
	$sliderStyle = isset ( $slides ['properties'] ['sliderstyle'] ) ? $slides ['properties'] ['sliderstyle'] : '';

	if (isset($slides['properties']['bg_fid']) && !empty($slides['properties']['bg_fid'])) {
		$bg = '';
		$file = file_load($slides['properties']['bg_fid']);
		if (isset($slides['properties']['bg_style']) && !empty($slides['properties']['bg_style'])){
			$bg = image_style_url($slides['properties']['bg_style'], $file->uri);
		}else{
			if (isset($file->uri)) {
				$bg = file_create_url($file->uri);
			}
		}
		$sliderStyle .='background-image: url('.$bg.');';
	}elseif (isset($slides['properties']['bg']) && !empty($slides['properties']['bg'])) {
		$bg = $slides['properties']['bg'];
		$sliderStyle .='background-image: url('.$bg.');';
	}

	if (isset($slides['properties']['bgColor']) && !empty($slides['properties']['bgColor'])) {
		$sliderStyle .='background-color: '.$slides['properties']['bgColor'].';';
	}

	$width = isset ( $slides ['properties'] ['fullwidth'] ) && $slides ['properties'] ['fullwidth'] =='true' ? '100%' : $slides ['properties'] ['width'];

	$out .= '<div style="'. $sliderStyle . '">';
	$out .= '<div class="contentSlider-wrap ac-preload-me ac-init-hidden" style="width: ' . ac_check_unit ( $width ) . '; margin: 0px auto;">';
	$out .= '<ul id="' . $slide_id . '" class="contentSlider ac-s-li" style="width: ' . ac_check_unit ( $slides ['properties'] ['width'] ) . '; height: ' . ac_check_unit ( $slides ['properties'] ['height'] ) . '; max-width:100%; margin: 0px auto;">';
	if (is_array ( $slides ['layers'] )) {

		foreach ( $slides ['layers'] as $layerkey => $layer ) {
			// ID
			if (! empty ( $layer ['properties'] ['id'] )) {
				$layerID = ' id="' . $layer ['properties'] ['id'] . '"';
			} else {
				$layerID = '';
			}

			$style = '';

			// ID
			if (! empty ( $layer ['properties'] ['background_fid'] )) {
				$file = file_load($layer ['properties'] ['background_fid']);
				if (isset($file->uri)) {
					$bg = file_create_url($file);
					$style .= 'background-image:url(\''.file_create_url($file).'\')";';
				}
			} else if (! empty ( $layer ['properties'] ['background'] )) {
				$style .= 'background-image:url(\''.$layer ['properties'] ['background'].'\')";';
			}

			if (! empty ( $layer ['properties'] ['bgColor'] )) {
				$style .= 'background-color:'.$layer ['properties'] ['bgColor'].';';
			}

			if (!empty($style)) {
				$style = ' style="' .$style .'"';
			}

			$out .= '<li' . $layerID . $style . '>';
			$out .= ' <div class="slide-inner" style="width: ' . ac_check_unit ( $width ) . '; max-width: 100%;">';

			if (isset ( $layer ['sublayers'] ) && is_array ( $layer ['sublayers'] )) {
				$slide_media = '';
				foreach ( $layer ['sublayers'] as $sid => $sublayer ) {
					if ($sublayer ['type'] == 'img') {
						$slide_media = $sublayer;
						unset($layer ['sublayers'][$sid]);
						break;
					}
				}

				$out .='<div class="ac-col ac-one-half slider-text clearfix">';
				$out .= ' <div class="col-inner">';

				foreach ( $layer ['sublayers'] as $sublayer ) {

					// Skip sublayer?
					if (isset ( $sublayer ['skip'] )) {
						continue;
					}

					// ID
					if (! empty ( $sublayer ['id'] )) {
						$sublayerID = 'id="' . $sublayer ['id'] . '"';
					} else {
						$sublayerID = '';
					}

					// Title
					if (! empty ( $sublayer ['title'] )) {
						$sublayerTitle = 'title="' . $sublayer ['title'] . '"';
					} else {
						$sublayerTitle = '';
					}

					// Alt
					if (! empty ( $sublayer ['alt'] )) {
						$sublayerAlt = 'alt="' . $sublayer ['alt'] . '"';
					} else {
						$sublayerAlt = '';
					}

					// Rel
					if (! empty ( $sublayer ['rel'] )) {
						$sublayerRel = 'rel="' . $sublayer ['rel'] . '"';
					} else {
						$sublayerRel = '';
					}

					// Custom style
					if (! empty ( $sublayer ['style'] )) {
						$sublayerStyle = preg_replace ( '/\s\s+/', ' ', stripslashes ( $sublayer ['style'] ) );
					} else {
						$sublayerStyle = '';
					}

					// Custom classes
					if (! empty ( $sublayer ['class'] )) {
						$sublayerClass = ' ' . $sublayer ['class'] . '';
					} else {
						$sublayerClass = '';
					}

					// Build style settings if any
					if (! empty ( $sublayer ['styles'] )) {

						// String to hold custom style settings
						$customStyles = '';

						// Get custom style settings
						$styles = json_decode ( stripslashes ( $sublayer ['styles'] ), true );

						// Build custom style string
						foreach ( $styles as $key => $val ) {
							if (is_numeric ( $val )) {
								$customStyles .= '' . $key . ': ' . ac_check_unit ( $val ) . '; ';
							} else {
								$customStyles .= '' . $key . ': ' . $val . '; ';
							}
						}
					} else {
						$customStyles = '';
					}

					if (empty ( $sublayer ['type'] ) || $sublayer ['type'] == 'img') {
						if (isset($sublayer['image_fid']) && ! empty ( $sublayer ['image_fid'] )) {
							$file = file_load($sublayer['image_fid']);
							if (isset($file->uri)) {
								$sublayer ['image'] = file_create_url($file->uri);
							}
						}
						if (!empty($sublayer['image'])){
							$out .= '<img' . $sublayerClass . $sublayerID . ' src="' . $sublayer ['image'] . '" ' . $sublayerAlt . ' style="' . $sublayerStyle . '' . $customStyles . '">';
						}
					} else {
						if (in_array($sublayer ['type'], array('p', 'div'))) {
							$sublayer ['html'] = check_markup($sublayer ['html'], 'full_html');
						}
						$out .= '<' . $sublayer ['type'] . ' ' . $sublayerID . $sublayerClass . ' style="'.$sublayerStyle . ' ' . $customStyles . '"> ' . $sublayer ['html'] . ' </' . $sublayer ['type'] . '>';
					}
				}

				$out .= ' </div>';
				$out .= '</div>';

				$out .= '<div class="ac-col ac-one-half slide-media clearfix">';
				$out .= ' <div class="col-inner">';

				if (!empty($slide_media)) {
					if (! empty ( $slide_media ['image'] )) {
						// ID
						if (! empty ( $slide_media ['id'] )) {
							$sublayerID = 'id="' . $slide_media ['id'] . '"';
						} else {
							$sublayerID = '';
						}

						// Title
						if (! empty ( $slide_media ['title'] )) {
							$sublayerTitle = 'title="' . $slide_media ['title'] . '"';
						} else {
							$sublayerTitle = '';
						}

						// Alt
						if (! empty ( $slide_media ['alt'] )) {
							$sublayerAlt = 'alt="' . $slide_media ['alt'] . '"';
						} else {
							$sublayerAlt = '';
						}

						// Rel
						if (! empty ( $slide_media ['rel'] )) {
							$sublayerRel = 'rel="' . $slide_media ['rel'] . '"';
						} else {
							$sublayerRel = '';
						}

						// Custom style
						if (! empty ( $slide_media ['style'] )) {
							$sublayerStyle = preg_replace ( '/\s\s+/', ' ', stripslashes ( $slide_media ['style'] ) );
						} else {
							$sublayerStyle = '';
						}

						// Custom classes
						if (! empty ( $slide_media ['class'] )) {
							$sublayerClass = ' ' . $slide_media ['class'] . '';
						} else {
							$sublayerClass = '';
						}

						// Build style settings if any
						if (! empty ( $slide_media ['styles'] )) {

							// String to hold custom style settings
							$customStyles = '';

							// Get custom style settings
							$styles = json_decode ( stripslashes ( $slide_media ['styles'] ), true );

							// Build custom style string
							foreach ( $styles as $key => $val ) {
								if (is_numeric ( $val )) {
									$customStyles .= '' . $key . ': ' . ac_check_unit ( $val ) . '; ';
								} else {
									$customStyles .= '' . $key . ': ' . $val . '; ';
								}
							}
						} else {
							$customStyles = '';
						}
						if (isset($slide_media['image_fid'])) {
							$file = file_load($slide_media['image_fid']);
							if (isset($file->uri)) {
								$slide_media ['image'] = file_create_url($file->uri);
							}
						}
						$out .= '<img' . $sublayerClass . $sublayerID . ' src="' . $slide_media ['image'] . '" ' . $sublayerAlt . ' style="' . $sublayerStyle . '' . $customStyles . '">';
					}
				}

				$out .= ' </div>';
				$out .= '</div>';
			}

			$out .= '</div>';
			$out .= '</li>';
		}
	}
	$out .= '</ul><!-- slider -->';
	$out .= '</div><!-- slider container -->';
	$out .= '</div><!-- preloader -->';
}
print $out;
?>

<script type="text/javascript">

(function ($) {

	$(document).ready(function() {

    if (jQuery().contentSlider) {
				var doContentSlider = function() {
					 $('#<?php echo $slide_id?>').contentSlider({
						auto:<?php echo ac_slider_getParam("auto","true", $slides['properties']) ?>,
						speed:<?php echo ac_slider_getParam("speed","500", $slides['properties']) ?>,
						timeout:<?php echo ac_slider_getParam("timeout","4000", $slides['properties']) ?>,
						pager:<?php echo ac_slider_getParam("pager","false", $slides['properties']) ?>,
						nav:<?php echo ac_slider_getParam("nav","false", $slides['properties']) ?>,
						random:<?php echo ac_slider_getParam("random","false", $slides['properties']) ?>,
						pause:<?php echo ac_slider_getParam("pause","false", $slides['properties']) ?>,
						pauseControls:<?php echo ac_slider_getParam("pauseControls","true", $slides['properties']) ?>,
					});
				}

			 if (jQuery().imagesLoaded) {
					$('#<?php echo $slide_id?>').imagesLoaded(function () {
						doContentSlider();
					});
			 }else{
					doContentSlider();
			 }
    }
  });

})(jQuery);

</script>