<?php

/**
 * @file Image theme, manipulation functions
 */

/**
 * prepare portfolio item settings
 */
function ac_portfolio_item_prepare_settings(&$settings) {
	$settings += array(
		'id' => uniqid('ac-portfolio-'), // Portfolio appearance
		'appearance' => acquia_variable_get('portfolio_blocks_appearance', 'masonry'), // Portfolio appearance
		'total' => acquia_variable_get('portfolio_blocks_total', -1), // Number of items to extract from db
		'pager' => acquia_variable_get('portfolio_blocks_pager', 'simple'), // Pager type
		'pager_nums' => acquia_variable_get('portfolio_blocks_num_per_page', 12), // Number of items in each page, in case of pager enabled
		// @todo add pager
		'spaced' => acquia_variable_get('portfolio_blocks_spaced', false), // spaced
		'padding' => acquia_variable_get('portfolio_blocks_padding', 20), // padding between items in Pixel

		'cols' => acquia_variable_get('portfolio_blocks_cols', 3), // Custom width of items
		'view'   => acquia_variable_get('portfolio_blocks_view', 'simple-sep'), // Portfolio view type
		'frame'   => acquia_variable_get('portfolio_blocks_frame', NULL), // Portfolio Thumbs style

		'width'   => acquia_variable_get('portfolio_blocks_width', 'equal'), // Portfolio items width type
		'style'   => acquia_variable_get('portfolio_blocks_style', 'rectangle-hr-large'), // Portfolio Thumbs style
		'effect'   => acquia_variable_get('portfolio_blocks_effect', 'blur'), // Portfolio Thumbs style

		'sorting' => acquia_variable_get('portfolio_blocks_sorting', TRUE), // Sorting based on tags
		'filter_style' => acquia_variable_get('portfolio_blocks_filter_style', 'fancy'), // Filter style
		'sort' => acquia_variable_get('portfolio_blocks_sort_type', 'date'), //
		'order' => acquia_variable_get('portfolio_blocks_order_type', 'DESC'), //
		'term' => acquia_variable_get('portfolio_blocks_term', '*'), //

		'fullwidth' => acquia_variable_get('portfolio_blocks_fullwidth', FALSE), // Full width container
		'spaced' => acquia_variable_get('portfolio_blocks_spaced', TRUE), // Spaced item style?
		'media'   => acquia_variable_get('portfolio_blocks_media', TRUE), // Display tags by default

		'title' => acquia_variable_get('portfolio_blocks_title', TRUE), // Display Title link by default
		'date'   => acquia_variable_get('portfolio_blocks_date', TRUE), // Display date by default
		'date_format' => acquia_variable_get('portfolio_blocks_date_format', 'M j, Y'), // Date format if date enabled
		'tags'   => acquia_variable_get('portfolio_blocks_tags', TRUE), // Display tags by default

		'proj_link'   => acquia_variable_get('portfolio_blocks_proj_link', TRUE), // Display Project link by default
		'details_link' => acquia_variable_get('portfolio_blocks_details_link', TRUE), // Display Details link by default
		'excerpt' => acquia_variable_get('portfolio_blocks_excerpt', FALSE), // Display excerpt link by default
		'counter' => acquia_variable_get('portfolio_blocks_counter', TRUE), // Display node view count by default

		'flag' => acquia_variable_get('portfolio_blocks_like_enabled', TRUE) ?
			flag_get_flag(AC_PORTFOLIO_LIKE_FLAG_MN) :
			NULL, // Display falg by default
	);

	if ($settings['appearance'] == 'scroller') {
		$settings['sorting'] = FALSE;
	}

}


/**
 * prepare portfolio item settings
 */
function ac_portfolio_related_settings() {
	return array(
		'id' => 'ac-portfolio-releated', // Display Title link by default
		'title' => acquia_variable_get('portfolio_related_block_title', TRUE), // Display Title link by default
		'appearance' => 'scroller', // Display Title link by default
		'view' => acquia_variable_get('portfolio_related_view', 'simple-sep'),
		'nav_prev_next' =>  acquia_variable_get('portfolio_related_nav_prev_next', TRUE),
		'nav_pager' =>  acquia_variable_get('portfolio_related_nav_pager', FALSE),
		'spaced' => acquia_variable_get('portfolio_related_spaced', false), // spaced
		'padding' => acquia_variable_get('portfolio_related_padding', 20), // padding between items in Pixel

		'cols' => acquia_variable_get('portfolio_related_cols', 3), // Custom width of items

		'style'   => acquia_variable_get('portfolio_related_style', 'rectangle-hr-large'), // Portfolio Thumbs style
		'effect'   => acquia_variable_get('portfolio_related_effect', 'blur'), // Portfolio Thumbs style

		'fullwidth' => acquia_variable_get('portfolio_related_fullwidth', FALSE), // Full width container
		'media'   => acquia_variable_get('portfolio_related_media', TRUE), // Display tags by default

		'date'   => acquia_variable_get('portfolio_related_date', TRUE), // Display date by default
		'date_format' => acquia_variable_get('portfolio_related_date_format', 'M j, Y'), // Date format if date enabled
		'tags'   => acquia_variable_get('portfolio_related_tags', TRUE), // Display tags by default

		'proj_link'   => acquia_variable_get('portfolio_related_proj_link', TRUE), // Display Project link by default
		'details_link' => acquia_variable_get('portfolio_related_details_link', TRUE), // Display Details link by default
		'excerpt' => acquia_variable_get('portfolio_related_excerpt', FALSE), // Display excerpt link by default
		'counter' => acquia_variable_get('portfolio_related_counter', TRUE), // Display node view count by default
		'sorting' => FALSE,
		'frame' => FALSE,
		'width' => 'equal',
		'flag' => acquia_variable_get('portfolio_blocks_like_enabled', TRUE) ?
			flag_get_flag(AC_PORTFOLIO_LIKE_FLAG_MN) :
			NULL, // Display falg by default
	);

}

/**
 * Rounded borders frame type
 * @param $item
 * @param $settings
 */
function ac_portfolio_frame_rounded_borders($item, $settings){
	$item['attrs']['class'] = array('ac-col');

	if (isset($item['thumb']) && !empty($item['thumb']['media'])) {
		$thumb = $item['thumb'];// slider | image | video
	}else if (isset($item['preview']) && !empty($item['preview']['media'])) {
		$thumb = $item['preview'];
	}

	// Image Thumb
	if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {
		acquia_include('media');
		if (!empty($settings['frame']) && $settings['frame'] !='none') {
			acquia_include('content');
			$item['attrs']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $settings['frame']), CHECK_LENGTH) . '-wrap';
		}

		$effect = isset($settings['effect']) ? $settings['effect'] : NULL;
		$image = array('frame' => $settings['frame']);
		if ($settings['width'] == 'equal') {
			$image['image_style'] = $settings['style'];
		}elseif ($settings['width'] == 'equal_height') {
			$image['image_style'] = acquia_variable_get('equal_height_style', 'equal-height');
		}else {
			$image['image_style'] = acquia_variable_get('image_medium_ratio_style', 'default-image-medium');
		}

		foreach ($thumb['media'] as $file) {
			$media = array(
				'fid' => $file['fid'],
				'style' => $image,
				'caption' => array(
					'text' => $item['title'],
				),
				'link' => array(
					'path' => 'node/' . $item['nid'],
				)
			);
			$item['media'] = acquia_image_format_extended($media);
		}
	}

	// Tags
	if (isset($item['terms']) && !empty($item['terms'])) {
		if ($settings['tags']) {
			$item['tags'] = theme('acquia_tags', array('tags' => $item['terms']));
		}

		if (isset($settings['sorting']) && $settings['sorting']) {
			$item['tags-raw'] = $item['terms'];
			$item['attrs']['class'][] = 'tid-' . implode(' tid-', array_keys($item['terms']));
		}
	}else{
		$item['tags-raw'] = array();
	}

	if (isset($settings['sorting']) && $settings['sorting']) {
		$item['attrs']['data-date'] = $item['created'];
		$item['attrs']['data-title'] = drupal_strtolower($item['title']);
	}

	return $item;
}


/**
 * prepare portfolio item vars
 */
function ac_portfolio_prepare_view($item, $settings) {
	$cache = &drupal_static(__FUNCTION__, array());
	if (!isset($cache[$settings['id']][$item['nid']])) {
		// @TODO move each view type to the corresponding template function
		if (isset($settings['frame']) && $settings['frame'] == 'rounded_borders'){
			$item = ac_portfolio_frame_rounded_borders($item, $settings);
		}else{
			acquia_include('utility', 'ac_portfolio');
			$video = FALSE;
			$item['attrs']['class'] = array('ac-col');
			if (isset($item['misc']['layout']) && in_array($item['misc']['layout'], array('before', 'after'))) {
				$item['attrs']['class'][] = 'wide-item';
			}

			// All styles except Thumb - Prepare info
			if ($settings['appearance'] != 'thumb') {
				// excerpt
				if ($settings['excerpt'] && isset($item['misc']['excerpt']) && !empty($item['misc']['excerpt'])) {
					$item['excerpt'] = check_markup($item['misc']['excerpt']['value'], $item['misc']['excerpt']['format']);
				}
				// proj_link
				if ($settings['details_link']) {
					if ($settings['appearance'] != 'slider') {
						$item['details'] = l('<i class="icon-readmore"></i>' . t('details'), 'node/' . $item['nid'], array('absolute' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('read-more'))));
					} else {
						$item['details'] = acquia_button(array(
							'link' => 'node/' . $item['nid'],
							'label' => t('details'),
							'style' => 'subtle',
							'type' => 'sw',
							'class' => 'read-more',
							'size' => 'small',
						));
					}
				}
				// View Project
				if ($settings['proj_link'] && isset($item['misc']['link']) && !empty($item['misc']['link'])) {
					$label = isset($item['misc']['link_title']) && !empty($item['misc']['link_title']) ? $item['misc']['link_title'] : variable_get('ac_portfolio_link_title');
					if ($settings['appearance'] != 'slider') {
						$item['link'] = l(
							'<i class="icon-link"></i>'.$label,
							$item['misc']['link'],
							array(
								'html' => TRUE,
								'absolute' => TRUE,
								'attributes' => array('title' => $label, 'class' => 'ac-proj-link ac-style-sw a')
							)
						);
					} else {
						$item['link'] = acquia_button(array(
							'link' => $item['misc']['link'],
							'label' => t($label),
							'style' => 'subtle',
							'type' => 'sw',
							'class' => 'ac-proj-link',
							'size' => 'small',
						));
					}
				}

				// date
				if (isset($settings['date']) && $settings['date']) {
					$item['date'] = theme('html5_tools_time', array('date' => format_date($item['created'], "custom", $settings['date_format']), 'isodate' => format_date($item['created'], 'html5_tools_iso8601')));
				}
				// totalcount
				if ($settings['counter']) {
					$item['totalcount'] = isset($item['totalcount']) && !is_null($item['totalcount']) ? $item['totalcount'] : 0;
					$item['counter'] = l('<i class="icon-eye"></i>' . $item['totalcount'], 'node/' . $item['nid'], array('absolute' => TRUE, 'html' => TRUE));
				}
				if (isset($settings['sorting']) && $settings['sorting']) {
					$item['attrs']['data-date'] = $item['created'];
					$item['attrs']['data-title'] = drupal_strtolower($item['title']);
				}
				// Title
				if (isset($settings['title']) && $settings['title'] && isset($item['title']) && !empty($item['title'])) {
					$item['title'] = l($item['title'], 'node/' . $item['nid'], array('absolute' => TRUE));
				}else{
					unset($item['title']);
				}

				// Tags
				if (isset($item['terms']) && !empty($item['terms'])) {
					if ($settings['tags']) {
						$item['tags'] = theme('acquia_tags', array('tags' => $item['terms']));
					}

					if (isset($settings['sorting']) && $settings['sorting']) {
						$item['tags-raw'] = $item['terms'];
						$item['attrs']['class'][] = 'tid-' . implode(' tid-', array_keys($item['terms']));
					}
				}else{
					$item['tags-raw'] = array();
				}

				$item['features'] = '';
				if (is_object($settings['flag'])) {
					$item['features'] .= $settings['flag']->theme($settings['flag']->is_flagged($item['nid']) ? 'unflag' : 'flag', $item['nid']);
				}
			}

			// Prepare Media
			if ($settings['media']) {
				if (isset($item['thumb']) && !empty($item['thumb']['media'])) {
					$thumb = $item['thumb'];// slider | image | video
				}else if (isset($item['preview']) && !empty($item['preview']['media'])) {
					$thumb = $item['preview'];
				}

				$item['media'] = array();
				// Style the thumb
				if (isset($thumb)) {
					acquia_include('media');
					// @style: Slider
					if ($settings['appearance'] == 'slider') {
						if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {
							$file = array_shift($thumb['media']);

							$media = array(
								'fid' => $file['fid'],
								'style' => array('image_style' => $settings['style'], 'frame' => $settings['frame']),
								//'link' => array('path' => 'node/' . $item['nid']),
							);
							$item['media'][] = array('file' => acquia_image_format_extended($media));

							if (isset($settings['thumb']) && $settings['thumb']) {
								$item['thumb'] = image_style_url(acquia_variable_get('portfolio_slider_thumb_style', 'rectangle-thumb'), file_load($file['fid'])->uri);
							}
						}else{
							// @todo
						}
					}
					// @style: Thumb
					else if ($settings['appearance'] == 'thumb') {
						if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {
							$file = array_shift($thumb['media']);
							$media = array(
								'fid' => $file['fid'],
								'style' => array('image_style' => $settings['style'], 'frame' => $settings['frame']),
								'link' => array('path' => 'node/' . $item['nid']),
							);
							$item['media'][] = array('file' => acquia_image_format_extended($media));
						}
					}
					// @style: All except slider and thumb
					else {
						acquia_include('utility');
						// Image Thumb
						if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {
							if (!empty($settings['frame']) && $settings['frame'] !='none') {
								acquia_include('content');
								$item['attrs']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $settings['frame']), CHECK_LENGTH) . '-wrap';
							}

							$effect = isset($settings['effect']) ? $settings['effect'] : NULL;
							$image = array(
								'effect' => $effect,
								'frame' => $settings['frame'],
								'image_style' => $settings['style'],
							);

//							if ($settings['width'] == 'equal') {
//								$image['image_style'] = $settings['style'];
//							}elseif ($settings['width'] == 'equal_height') {
//								$image['image_style'] = acquia_variable_get('equal_height_style', 'equal-height');
//							}else {
//								$image['image_style'] = acquia_variable_get('image_medium_ratio_style', 'default-image-medium');
//							}

							foreach ($thumb['media'] as $file) {
								$media = array('fid' => $file['fid'], 'style' => $image);
								$item['media'][]['file'] = acquia_image_format_extended($media);
							}

						}
						// Video Thumb
						else{
							$video = TRUE;
							foreach ($thumb['media'] as $file) {
								$media = array('fid' => $file['fid']);
								$media['style']['video_style'] = $settings['style'];
								$media['style']['frame'] = $settings['frame'];
								$item['media'][]['file'] = acquia_video_format_extended($media);
							}
						}
						if ($settings['view'] != 'dribbble' && isset($thumb['link_type']) && (!isset($settings['view']) || $settings['view'] != 'overlaid-left')) {
							if (in_array($thumb['link_type'], array('item', 'url', 'lightbox_link'))) {
								$link = $thumb['link_type'] == 'url' ? $thumb['link_url'] : url('node/' . $item['nid'], array('absolute' => TRUE));
								if (!empty($link)) {
									$item['features'] .= l(theme('acquia_media_feature', array('type' => 'link')), $link, array('target' => '_blank', 'html' => TRUE, 'attributes' => array('class' => array('linked'))));
								}
							}

							if (count($thumb['media']) == 1 && in_array($thumb['link_type'], array('lightbox_link', 'lightbox_thumb', 'lightbox_image', 'video'))) {
								$popup = array('item');
								if (isset($item['title'])) {
									$popup['item']['title'] = t($item['title']);
								}

								// get fid by link type
								if ($thumb['link_type'] == 'lightbox_image') {
									$popup['item']['uri'] = file_load($thumb['link_image']['fid'])->uri;
								}
								else if ($thumb['link_type'] == 'video') {
									$popup['lightbox_video'] = file_load($thumb['link_video']['fid'])->uri;
								}
								else {
									$thumb = array_shift($thumb['media']);
									$popup['item']['uri'] = file_load($thumb['fid'])->uri;
								}

								$popup['lightbox_style'] = acquia_theme_get_settings('image_lightbox_style', null, 'shortcodes');
								$item['features'] .= theme('acquia_popup', $popup);
							}
						}
					}
				}
			}

			if ($video && isset($settings['view']) && in_array($settings['view'], array('simple-sep', 'fade-in-bottom'))) {
				$item['features'] = '';
			}

			if (count($item['media']) > 1) {
				$slider_settings =array();
				if (isset($settings['view']) && $settings['view'] != 'simple-sep') {
					$slider_settings['pager'] = 'false';
					$slider_settings['nav'] = 'true';
					$slider_settings['auto'] = 'true';
				}
				$item['media'] = theme('acquia_slider', array('items' => $item['media'], 'settings' => $slider_settings));
			}else if (!empty($item['media'])) {
				$item['media'] = $item['media'][0]['file'];
			}else {
				$item['media'] = '';
			}
		}
		$cache[$settings['id']][$item['nid']] = $item;
	}

	return $cache[$settings['id']][$item['nid']];
}


/**
 * prepare portfolio item vars
 */
function ac_portfolio_get_teaser_extra($node, $settings) {
	$cache = &drupal_static(__FUNCTION__, array());

	if (!isset($cache[$node['nid']])) {
		acquia_include('utility');

		$meta = $node['nodemeta'];
		$item = array();
		$video = FALSE;
		$item['attrs']['class'] = 'ac-col';

		// excerpt
		if ($settings['excerpt'] && isset($meta['misc']['excerpt']) && !empty($meta['misc']['excerpt']['value'])) {
			$item['excerpt'] = strip_tags($meta['misc']['excerpt']['value']);
		}else if ($settings['excerpt']){
			$item['excerpt'] = strip_tags(render($node['body']));
		}

//		// read more
//    $item['read_more'] = acquia_button(array('link' => 'node/' . $node['nid'], 'label' => t('details'), 'icon' => 'readmore', 'style' => 'subtle'));

		// Details
		if ($settings['proj_link']) {
			$item['details'] = l('<i class="icon-readmore"></i>' . t('details'), 'node/' . $node['nid'], array('absolute' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('read-more'))));
		}

		// Details
		if ($settings['date']) {
			$item['date'] = theme('html5_tools_time', array('date' => format_date($node['created'], "custom", $settings['date_format']), 'isodate' => format_date($node['created'], 'html5_tools_iso8601')));
		}

		// View Project
		if (isset($meta['misc']['link']) && !empty($meta['misc']['link'])) {
			$label = isset($meta['misc']['link_title']) && !empty($meta['misc']['link_title']) ? $meta['misc']['link_title'] : variable_get('ac_portfolio_link_title');
			$item['link'] = l('<i class="icon-link"></i>'.$label,
				$meta['misc']['link'],
				array('html' => TRUE,
					'absolute' => TRUE,
					'attributes' => array('title' => $label, 'class' => 'ac-proj-link')));
		}

		// Media
		if (isset($meta['thumb']) && !empty($meta['thumb']['media'])) {
			$thumb = $meta['thumb'];// slider | image | video
		}else if (isset($meta['preview']) && !empty($meta['preview']['media'])) {
			$thumb = $meta['preview'];
		}

		if (isset($thumb)) {
			acquia_include('media');
			$item['media'] = array();
			// Image Thumb
			if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {

				$image = array();

				$image['style'] = array('frame' => $settings['frame'], 'effect' => $settings['effect']);
				if ($settings['width'] == 'equal') {
					$image['style']['image_style'] = $settings['style'];
				}else {
					$image['style']['image_style'] = acquia_variable_get('image_medium_ratio_style', 'default-image-medium');
				}

				if (isset($thumb['link_type'])) {
					if (in_array($thumb['link_type'], array('item', 'url', 'lightbox_link'))) {
						$image['link']['path'] = $thumb['link_type'] == 'url' ? $thumb['link_url'] : url('node/' . $node['nid'], array('absolute' => TRUE));
					}

					if (count($thumb['media']) == 1 && in_array($thumb['link_type'], array('lightbox_link', 'lightbox_thumb', 'lightbox_image', 'video'))) {
						$image['style']['lightbox'] = TRUE;

						// get fid by link type
						if ($thumb['link_type'] == 'lightbox_image') {
							$image['style']['lightbox_fid'] = $thumb['link_image']['fid'];
						}
						else if ($thumb['link_type'] == 'video') {
							$image['style']['video'] = $thumb['link_video']['fid'];
						}
						else {
							$image['style']['lightbox_fid'] = $thumb['media'][0]['fid'];
						}
					}
				}

				foreach ($thumb['media'] as $id => $file) {
					$item['media'][]['file'] = acquia_image_format_extended(array_merge(array('fid' => $file['fid']), $image));
				}

			}
			// Video Thumb
			else{
				$video = TRUE;
				foreach ($thumb['media'] as $id => $file) {
					$video = array('fid' => $file['fid']);
					$video['style'] = array('frame' => $settings['frame'], 'effect' => $settings['effect'], 'thumb' => TRUE);
					$item['media'][]['file'] = acquia_video_format_extended($video);
				}
			}
		}

		if (count($item['media']) > 1) {
			$slider_settings = array(
				'pager' => 'false',
				'nav' => 'true',
				'auto' => 'false',
			);
			$item['media'] = theme('acquia_slider', array('items' => $item['media'], 'settings' => $slider_settings));
		}else if (!empty($item['media'])) {
			$item['media'] = $item['media'][0]['file'];
		}else {
			$item['media'] = '';
		}
		$cache[$node['nid']] = $item;
	}

	return $cache[$node['nid']];
}