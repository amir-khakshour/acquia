<?php

/**
 * @file Image theme, manipulation functions
 */

/**
 * prepare block of blog settings
 */
function ac_blog_prepare_block_settings(&$settings) {
  $settings += array(
	'appearance' => acquia_variable_get('blog_blocks_appearance', 'grid'), // blog appearance
	'view' => acquia_variable_get('blog_blocks_view', 'thumb'), // blog view type
	'total' => acquia_variable_get('blog_blocks_total', -1), // Number of items to extract from db
	'pager_nums' => acquia_variable_get('blog_blocks_num_per_page', 12), // Number of items in each page, in case of pager enabled

	// @todo add pager
	'padding' => acquia_variable_get('blog_blocks_padding', 20), // padding between items in Pixel
	'cols' => acquia_variable_get('blog_blocks_cols', 3), // Custom width of items
	'spaced' => acquia_variable_get('blog_blocks_spaced', TRUE), // Spaced item style?
	'width'   => acquia_variable_get('blog_blocks_width', 'equal'), // blog items width type

	'style'   => acquia_variable_get('blog_blocks_style', 'rectangle-large'), // blog Thumbs style
	'frame'   => acquia_variable_get('blog_blocks_frame', NULL), // blog Thumbs style
	'effect'   => acquia_variable_get('blog_blocks_effect', ''), // blog Thumbs style

	'media'   => acquia_variable_get('blog_blocks_media', TRUE), // Display media by default
	'picture'   => acquia_variable_get('blog_blocks_picture', FALSE), // Display user picture by default
	// Meta
	'title'   => acquia_variable_get('blog_blocks_title', TRUE), // Display title by default
	'author'   => acquia_variable_get('blog_blocks_author', TRUE), // Display author by default
	'tags'   => acquia_variable_get('blog_blocks_tags', FALSE), // Display tags by default
	'categories'   => acquia_variable_get('blog_blocks_categories', TRUE), // Display categories by default
	'date'   => acquia_variable_get('blog_blocks_date', TRUE), // Display date by default
	'date_format' => acquia_variable_get('blog_blocks_date_format', 'M j, Y'), // Date format if date enabled
	'excerpt' => acquia_variable_get('blog_blocks_excerpt', FALSE), // Display excerpt by default?
  );

  $settings['vid'] = array(
	AC_BLOG_TAGS_MN => @taxonomy_vocabulary_machine_name_load(AC_BLOG_TAGS_MN)->vid,
	AC_BLOG_CAT_MN => @taxonomy_vocabulary_machine_name_load(AC_BLOG_CAT_MN)->vid
  );
}

/**
 * prepare blog item vars
 */
function ac_blog_prepare_view($item, $settings) {
  $cache = &drupal_static(__FUNCTION__, array());

  if (!isset($cache[$settings['appearance']][$item['nid']])) {
	acquia_include('options', 'ac_blog');
	$video = FALSE;
	$item['attrs']['class'] = array('ac-col');

	$item['item_i_attrs']['class'] = array('item-i');

	// Grid on circled view
	if ($settings['view'] == 'circled') {
	  $item['attrs']['class'][] = 'ac-grid-item';
	  $item['item_i_attrs']['class'][] = 'g-i';
	  $item['item_i_attrs']['class'][] = 'clearfix';
	}

	if ($settings['cols'] == 1){
	  $item['item_i_attrs']['class'] = array('col-inner');
	}
	// Date
	if ($settings['date']) {
	  $item['date'] = theme('html5_tools_time', array('date' => format_date($item['created'], "custom", $settings['date_format']), 'isodate' => format_date($item['created'], 'html5_tools_iso8601')));
	}

	// Tags
	if (isset($item['terms']) && !empty($item['terms'])) {
	  if ($settings['tags'] && isset($item['terms'][$settings['vid'][AC_BLOG_TAGS_MN]])) {
		$tags_vid =
		$item['tags'] = theme('acquia_tags', array('tags' => $item['terms'][$settings['vid'][AC_BLOG_TAGS_MN]]));
	  }
	  if ($settings['categories'] && isset($item['terms'][$settings['vid'][AC_BLOG_CAT_MN]])) {
		$item['categories'] = theme('acquia_tags', array('tags' => $item['terms'][$settings['vid'][AC_BLOG_CAT_MN]]));
	  }
	}

	// Title
	if ($settings['title'] && isset($item['title']) && !empty($item['title'])) {
	  $item['title'] = l($item['title'], 'node/' . $item['nid'], array('absolute' => TRUE));
	}else{
	  unset($item['title']);
	}

	// picture
	if ($settings['picture'] && isset($item['picture']) && !empty($item['picture'])) {
	  $item['picture'] = theme('user_picture', array('account' => user_load($item['uid'])));
	}else if ($settings['picture']){
	  $item['picture'] = NULL;
	}

	// excerpt
	if ($settings['excerpt'] && isset($item['misc']['excerpt']) && !empty($item['misc']['excerpt']['value'])) {
	  $item['excerpt'] = check_markup($item['misc']['excerpt']['value'], $item['misc']['excerpt']['format']);
	}else if ($settings['excerpt']){
	  $teaser = node_view(node_load($item['nid']),'teaser');
	  $item['excerpt'] = isset($teaser['body']) ? $teaser['body'] : '';
	}
	// author
	if ($settings['author']) {
	  $item['author'] = theme('username', array('account' => user_load($item['uid'])));
	}

	// Comment Count
	if (isset($item['comments'])) {
	  $item['comment_count_formatted'] = l('<span class="icon-comment-empty"></span>' . t('@count', array('@count' => $item['comments'])),
		'node/' . $item['nid'],
		array('html' => TRUE,
		  'external' => TRUE,
		  'fragment' => 'comments',
		  'attributes' => array('class' => array('comment-link')),
		)
	  );
	}else{
	  $item['comments'] = '';
	}

	// read more
	$item['read_more'] = l('<span class="icon-readmore"></span>' . t('read more'), 'node/' . $item['nid'], array('html' => TRUE, 'attributes' => array('class' => array('read-more'))));

	// Media
	if ($settings['media']) {

	  if (isset($item['thumb']) && !empty($item['thumb']['media'])) {
		$thumb = $item['thumb'];
	  }

	  if (!empty($settings['frame'])) {
		acquia_include('content');
		$item['attrs']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $settings['frame']), CHECK_LENGTH) . '-wrap';
		if ($settings['frame'] == 'simple-bordered' || $settings['frame'] == 'bordered') {
		  $item['item_i_attrs']['class'][] = 'ac-frame-on';
		}
	  }
	  $opts = array();
	  $opts['style'] = array('frame' => $settings['frame'], 'effect' => isset($settings['effect']) ? $settings['effect'] : NULL);
	  if ($settings['width'] == 'equal') {
		$opts['style']['image_style'] = $settings['style'];
		$opts['style']['video_style'] = $settings['style'];
	  }else {
		$opts['style']['image_style'] = acquia_variable_get('image_medium_ratio_style', 'default-image-medium');
		$opts['style']['video_style'] = acquia_variable_get('image_medium_ratio_style', 'default-image-medium');
	  }

	  $opts['link'] = array('path' => url('node/' . $item['nid'], array('absolute' => TRUE)));

	  acquia_include('media');
	  acquia_include('utility');
	  if (isset($thumb)) {
		$item['media'] = array();
		// Image Thumb
		if ($thumb['type'] == 'image' || $thumb['type'] == 'slider') {
		  foreach ($thumb['media'] as $id => $file) {
			$media = array('fid' => $file);
			$media += $opts;
			$item['media'][]['file'] = acquia_image_format_extended($media);
		  }
		}
		// Video Thumb
		else{
		  $video = TRUE;
		  foreach ($thumb['media'] as $id => $file) {
			$media = array('fid' => $file['fid']);
			$media += $opts;
			if (in_array($settings['view'], array_keys(ac_blog_related_views())) || in_array($settings['appearance'], array_keys(ac_blog_related_views()))) {
			  $media['style']['thumb'] = TRUE;
			}
			$item['media'][]['file'] = acquia_video_format_extended($media);
		  }
		}
	  }else{

		$media = $opts;
		$item['media'][]['file'] = acquia_image_format_extended($media);
	  }
	}else {
	  $item['media'] = array();
	}

	if (isset($item['media']) && count($item['media']) > 1 && $settings['view'] !='thumb') {
	  $slider_settings =array();
	  if (isset($settings['view']) && $settings['view'] != 'simple-sep') {
		$slider_settings['pager'] = 'false';
		$slider_settings['nav'] = 'true';
		$slider_settings['auto'] = 'false';
	  }

	  $item['media'] = theme('acquia_slider', array('items' => $item['media'], 'settings' => $slider_settings));
	}else if (!empty($item['media'])) {
	  $item['media'] = $item['media'][0]['file'];
	}else {
	  $item['media'] = '';
	}

	$cache[$settings['appearance']][$item['nid']] = $item;
  }

  return $cache[$settings['appearance']][$item['nid']];
}


/**
 * prepare blog item vars
 */
function ac_blog_get_teaser_extra($node, $settings) {
  $cache = &drupal_static(__FUNCTION__, array());
  if (!isset($cache[$node['nid']])) {
	acquia_include('utility');

	$meta = $node['nodemeta'];
	$item = array();
	$video = FALSE;
	$item['attrs']['class'] = 'ac-col';
	$item['media'] = array();
	// read more
	//$item['read_more'] = acquia_button(array('link' => 'node/' . $node['nid'], 'label' => t('details'), 'icon' => 'readmore', 'style' => 'subtle'));

	// Details
	if ($settings['date']) {
	  $item['date'] = theme('html5_tools_time', array('date' => format_date($node['created'], "custom", $settings['date_format']), 'isodate' => format_date($node['created'], 'html5_tools_iso8601')));
	}

	// Media
	if (isset($meta['thumb']) && !empty($meta['thumb']['media'])) {
	  $thumb = $meta['thumb'];// slider | image | video
	}

	// author
	if (!$settings['author']) {
	  unset($item['author']);
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

		$image['link']['path'] = url('node/' . $node['nid'], array('absolute' => TRUE));

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
		'nav' => 'false',
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