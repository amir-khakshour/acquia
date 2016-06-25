<?php
$out = '';
$thumb = array ();
if (is_array ( $slides )) {
	
	$sliderStyle = isset ( $slides ['properties'] ['sliderstyle'] ) ? $slides ['properties'] ['sliderstyle'] : '';
	$width = isset ( $slides ['properties'] ['fullwidth'] ) && $slides ['properties'] ['fullwidth'] =='true' ? '100%' : $slides ['properties'] ['width'];
	$out .= '<div id="' . $slide_id . '" class="ei-slider" style="width: ' . ac_check_unit ( $width ) . '; height: ' . ac_check_unit ( $slides ['properties'] ['height'] ) . '; margin: 0px auto; ' . $sliderStyle . '">';
	$out .= '<ul class="ei-slider-large">';
  
	if (is_array ( $slides ['layers'] )) {
    
		foreach ( $slides ['layers'] as $layerkey => $layer ) {
			$layer_attrs = array();
			// ID
			if (isset($layer['properties']['id']) && !empty($layer['properties']['id'])) {
				$layer_attrs['id'] = $layer['properties']['id'];
			}
			
			// ID
			if ($layerkey == 0) {
				$layer_attrs['class'][] = 'first';
			}else if ($layerkey == count($slides ['layers'])-1) {
				$layer_attrs['class'][] = 'last';
			}
      
			$out .= '<li' .drupal_attributes($layer_attrs). '>';
			// Layer background
			if (isset($layer ['properties'] ['background_fid']) && ! empty ( $layer ['properties'] ['background_fid'] )) {
				$file = file_load($layer['properties']['background_fid']);
				if (isset($file->uri)) {
					$layer ['properties'] ['background'] = file_create_url($file->uri);
				}
				$out .= '<img src="' . $layer ['properties'] ['background'] . '" alt="' . t ( 'Slide background' ) . '">';
			}else if (isset($layer ['properties'] ['background']) && ! empty ( $layer ['properties'] ['background'] )) {
				$out .= '<img src="' . $layer ['properties'] ['background'] . '" alt="' . t ( 'Slide background' ) . '">';
			}
			
			// Layer thumbnail
			if (! empty ( $layer ['properties'] ['thumbnail_formatted'] )) {
				$thumb [] = $layer ['properties'] ['thumbnail_formatted'];
			} else {
				$thumb [] = '<image src="'.$layer ['properties'] ['background'].'" alt="'.t('thumb @num', array('@num' => $layerkey)).'"/>';
			}
			
			if (isset ( $layer ['sublayers'] ) && is_array ( $layer ['sublayers'] )) {
        $out .='<div class="ei-title">';
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
						$sublayerClass = ' class="' . $sublayer ['class'] . '"';
					} else {
						$sublayerClass = '';
					}
					
					// Show until
					if (empty ( $sublayer ['showuntil'] )) {
						$sublayer ['showuntil'] = '0';
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
						if (! empty ( $sublayer ['image'] )) {
							$out .= '<img' . $sublayerClass . $sublayerID . ' src="' . $sublayer ['image'] . '" ' . $sublayerAlt . ' style="' . $sublayerStyle . '' . $customStyles . '">';
						}
					} else {
            if (in_array($sublayer ['type'], array('p', 'div'))) {
              $sublayer ['html'] = check_markup($sublayer ['html'], 'full_html');
            }
						$out .= '<' . $sublayer ['type'] . ' ' . $sublayerID . $sublayerClass . ' style="'.$sublayerStyle . ' ' . $customStyles . '"> ' . $sublayer ['html'] . ' </' . $sublayer ['type'] . '>';
					}
				}
        $out .= '</div>';
      }
			
			$out .= '</li>';
		}
	}
	$out .= '</ul><!-- ei-slider-large -->';
	
	if (count($thumb) >1) {
		$out .= '<ul class="ei-slider-thumbs">';
		$out .= '  <li class="ei-slider-element">'.t('Current').'</li>';
		foreach ($thumb as $id => $image) {
			
			$out .= '<li><a href="#">'.t('Slide @num', array('@num' => $id)).'</a>'.$image.'</li>';
		}
		$out .= '</ul>';
	}

  $out .= '</div><!-- ei-slider -->';
}
print $out;
?>

<script type="text/javascript">

(function ($) {
  
	$(document).ready(function() {
    
    if (jQuery().eislideshow) {
      
      $('#<?php echo $slide_id?>').eislideshow({
        animation:<?php echo ac_slider_getParam("animation","sides", $slides ['properties']) ?>,
        autoplay:<?php echo ac_slider_getParam("autoplay","false", $slides ['properties']) ?>,
        slideshow_interval:<?php echo (int)ac_slider_getParam("slideshow_interval","3000", $slides ['properties'])?>,
        speed:<?php echo (int)ac_slider_getParam("speed","800", $slides ['properties'])?>,
        easing:<?php echo (int)ac_slider_getParam("easing","easeOutExpo", $slides ['properties'])?>,
        titlesFactor:<?php echo (float)ac_slider_getParam("titlesFactor","0.60", $slides ['properties'])?>,
        titleeasing:<?php echo ac_slider_getParam("titleeasing","easeOutExpo", $slides ['properties']) ?>,
        titlespeed:<?php echo ac_slider_getParam("titlespeed","1200", $slides ['properties']) ?>,
        thumbMaxWidth:<?php echo (int)ac_slider_getParam("thumbMaxWidth","150", $slides ['properties']) ?>,
      });
    }
  });
  
})(jQuery);
	
</script>