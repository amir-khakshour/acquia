<?php
$out = '';
if (is_array ( $slides )) {
	$out .= '<div'.drupal_attributes($slider_outter_attrs).'>';
	$out .= '<div'.drupal_attributes($slider_attrs).'>';
	$out .= '<div'.drupal_attributes($slider_wrapper_attrs).'>';
	if (is_array ( $slides ['layers'] )) {
		foreach ( $slides ['layers'] as $layerkey => $layer ) {
			$bg = '';
			$layer_attrs = array('class' => array('swiper-slide'));
			// ID
			if (isset($layer['properties']['id'])) {
				$layer_attrs['id'] = $layer['properties']['id'];
			}
			
			if (isset($layer['properties']['slide_overlay']) && $layer['properties']['slide_overlay'] != 'none') {
				$layer_attrs['class'][] = 'ac-overlay-' .$layer['properties']['slide_overlay'];
			}
			
			$layer_attrs['style'] = '';
      // style
			if (isset($layer['properties']['background_fid'])) {
				$file = file_load($layer['properties']['background_fid']);
				if (isset($file->uri)) {
					$bg = file_create_url($file->uri);
					$layer_attrs['style'] = 'background-image:url(\''.$bg.'\');';
				}
			}	else if (isset($layer['properties']['background'])) {
				$bg = $layer['properties']['background'];
				$layer_attrs['style'] = 'background-image:url(\''.$layer['properties']['background'].'\');';
			}
      
      if (isset($layer['properties']['bgColor']) && !empty($layer['properties']['bgColor'])) {
				$layer_attrs['style'] .= 'background-color:'.$layer['properties']['bgColor'];
			}
			
			if (isset($layer['properties']['bg_position'])) {
				$layer_attrs['style'] .= 'background-position:'.$layer['properties']['bg_position'].';';
			}
			
			if (isset($layer['properties']['header_style'])) {
				$layer_attrs['data-header-style'] = $layer['properties']['header_style'];
			}

			$out .= '<div'.drupal_attributes($layer_attrs).'>';
			
			// add overlay
			if (isset($layer['properties']['slide_overlay']) && $layer['properties']['slide_overlay'] != 'none') {
				$out .= '<span class="ac-overlay"></span>';
			}
			
			$out .= '	<div class="container">';

			if (isset ( $layer ['sublayers'] ) && is_array ( $layer ['sublayers'] )) {
        $out .='<div class="swiper-caption-wrap">';
        $out .='<div class="swiper-caption clearfix caption-pos-'. $layer ['properties']['caption_pos'].' swiper-'. $layer ['properties']['caption_trans'].'" >';
				if (!empty($bg)) {
					$out .='<img style="display:none;" alt="" class="swiper-bg-img" src="'.$bg.'" />';
				}
        $out .='<div class="swiper-header">';
        $out .='	<div class="sw-title">' . $layer ['properties'] ['title_formtted'] . '</div>';
        $out .='	<div class="sw-subtitle">' .$layer ['properties']['subtitle_formtted'] . '</div>';
        $out .='</div>';
				
				$out .='<div class="swiper-buttons">';
				foreach ( $layer ['sublayers'] as $sublayer ) {
					$sub_attrs = array();
					
					// Skip sublayer?
					if (isset($sublayer['skip'])) {
						continue;
					}
					
					// ID
					if (!empty($sublayer['id'])) {
						$sub_attrs['id'] = $sublayer ['id'];
					}
					
					// Title
					if (!empty($sublayer['title'])) {
						$sub_attrs['title'] = $sublayer['title'];
					}
					
					// Alt
					if (!empty($sublayer['alt'])) {
						$sub_attrs['alt'] = $sublayer['alt'];
					}
					
					// Rel
					if (!empty($sublayer['rel'])) {
						$sub_attrs['rel'] = $sublayer ['rel'];
					}
					
					// Custom style
					if (!empty($sublayer['style'])) {
						$sub_attrs['style'] = preg_replace ( '/\s\s+/', ' ', stripslashes ( $sublayer ['style'] ) );
					}
					
					// Custom classes
					if (!empty($sublayer['class'])) {
						$sub_attrs['class'][] = $sublayer['class'];
					}
					
					// Build style settings if any
					if (!empty($sublayer['styles'])) {
						
						// Get custom style settings
						$styles = json_decode ( stripslashes ( $sublayer ['styles'] ), true );
						
						// Build custom style string
						foreach ( $styles as $key => $val ) {
							if (is_numeric ( $val )) {
								$sub_attrs['style'] .= '' . $key . ': ' . ac_check_unit ( $val ) . '; ';
							} else {
								$sub_attrs['style'] .= '' . $key . ': ' . $val . '; ';
							}
						}
					}
					
					if (empty($sublayer ['type']) || $sublayer['type'] == 'img') {
						if (! empty($sublayer ['image'] )) {
							$sub_attrs['src'] = $sublayer ['image'];
							$out .= '<img'.drupal_attributes($sub_attrs).' />';
						}
					} else {
            if (in_array($sublayer['type'], array('p', 'div'))) {
              $sublayer ['html'] = check_markup($sublayer ['html'], 'full_html');
            }
						$out .= '<' . $sublayer ['type'] .drupal_attributes($sub_attrs) .'> ' . $sublayer ['html'] . ' </' . $sublayer ['type'] . '>';
					}
				}
        
        $out .= '</div>';
				
        $out .= '</div>';
        $out .= '</div>';
      }
			
			$out .= '	</div>';
			$out .= '</div>';
		}
	}
	$out .= '	</div><!-- swiper-wrapper -->';
	if (isset($slides['properties']['pager']) && $slides['properties']['pager'] == 'true' && count($slides ['layers']) >1) {
		$out .= '<div class="pagination">';
		$out .= '</div>';
	}
	
	if (isset($slides['properties']['nav']) && $slides['properties']['nav'] == 'true' && count($slides ['layers']) >1) {
		$out .= '<a class="ac-swiper-nav prev"></a>';
		$out .= '<a class="ac-swiper-nav next"></a>';
	}

	$out .= '</div><!-- swiper-container -->';
	$out .= '</div><!-- swiper-outter -->';
}
print $out;
?>
