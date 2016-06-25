<?php
$out = '';
if (is_array ( $slides )) {
	$slide_bg_style = FALSE;
	$slider_captions = '';
	$slider_bg_html = '';

	if (isset($slides['properties']['bg_style']) && !empty($slides['properties']['bg_style'])) {
		$slide_bg_style = $slides['properties']['bg_style'];
	}
	foreach ( $slides ['layers'] as $layerkey => $layer ) {
		$prop = $layer['properties'];
		if (!isset($prop['background_fid']) || empty($prop['background_fid'])) {
			continue;
		}

		$file = file_load($prop['background_fid']);
		if (isset($file->uri)) {
			if ($slide_bg_style) {
				$bg_src = image_style_url($slide_bg_style, $file->uri);
			}else{
				$bg_src = file_create_url($file->uri);
			}
			$slider_bg_html .= '<div style="background-image:url('.$bg_src.');"></div>';
		}

		if (empty($prop['buy_link'])) {
			$prop['buy_link'] = '#';
		}
		$slider_captions .= theme('showcase_slider_slide_caption', $prop);
	}

	$out .= '<div'.drupal_attributes($container_attrs).'>';

	$out .= '<div class="ps-contentwrapper"><!-- [contentwrapper] -->';
	$out .=  $slider_captions;
	$out .= '</div><!-- [/contentwrapper] -->';

	$out .= '<div class="ps-slidewrapper"><!-- [slidewrapper] -->';
	$out .= '<div class="ps-slides"><!-- [slides] -->';
	$out .=  $slider_bg_html;
	$out .= '</div><!-- [/slides] -->';
	$out .= '<nav><a href="#" class="ps-prev"></a><a href="#" class="ps-next"></a></nav>';
	$out .= '</div><!-- [/slidewrapper] -->';

	$out .= '</div><!-- slider container-->';
}
print $out;
?>
