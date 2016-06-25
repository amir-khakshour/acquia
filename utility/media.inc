<?php

/**
 * @file Image theme, manipulation functions
 */

/**
 * Extended video Format
 *
 * @TODO Document here
 */
function acquia_video_format_extended($video){
	// we use fid for drupal managed files or scr for not managed files
	if (!isset($video['fid']) && !isset($video['src'])) {
		drupal_set_message('ACQUIA: given video uri is not valid');
		$video['fid'] = isset($video['fid']) && !empty($video['fid']) ? $video['fid'] : 'no file id';
		watchdog('ACQUIA', 'given video uri is not valid: @uri', array('@uri' => $video['fid']));
		return false;
	}
	acquia_include('utility');
	acquia_include('content');

	$video += array(
		'options' => array(),
		'wrapper' => array(),
		'inner' => array(),
		'style' => array(),
		'animate' => array(),
		'caption' => array(),
		'suffix' => '',// @TODO add prefix
	);

	$defaults = array(
		// Image attributes
		'options' => array(
			'width' => acquia_variable_get('video_width'), // video width
			'height' => acquia_variable_get('video_height'), // video height
			'autoplay' => FALSE, // video class
			'loop' => FALSE, // video class
			'class' => array(), // video class
			'fluid' => TRUE, // Fluid Video
		),

		// wrapper settings
		'wrapper' => array(
			'tag' => 'div',
			'attributes' => array(),
		),

		// wrapper settings
		'inner' => array(
			'attributes' => array('class' => array('media-i')),
		),

		// image style
		'style' => array(
			'frame' => '', // image frame
			'align' => '', // image align
			'thumb' => FALSE, // generate thumbnail video style?
		),

		// Animate
		'animate' => array(
			'type' => '', // Animate type
			'when' => '', // Animate when?
		),

		// image caption
		'caption' => array(
			'text' => '',
			'attributes' => array(),
		),
		// image caption
		'suffix' => ''
	);

	foreach($defaults as $attr => $vals) {
		$video[$attr] += $vals;
	}

	if (isset($video['style']['video_style']) && !empty($video['style']['video_style'])) {
		$d = acquia_get_image_style_dimension($video['style']['video_style']);
		if (isset($d['width']) && !empty($d['width'])) {
			$video['options']['width'] = $d['width'];
		}

		if (isset($d['height']) && !empty($d['height'])) {
			$video['options']['height'] = $d['height'];
		}
	}

	$video['wrapper']['attributes']['class'] = !empty($video['wrapper']['attributes']['class']) ? $video['wrapper']['attributes']['class'] : array();
	array_unshift($video['wrapper']['attributes']['class'], 'ac-media');

	// Frame
	if (!empty($video['style']['frame'])) {
		$video['wrapper']['attributes']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $video['style']['frame'])) . '-wrap';
		$video['inner']['attributes']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $video['style']['frame']));
	}else{
		$video['wrapper']['attributes']['class'][] = 'ac-nf';
	}

	if (!empty($video['animate']['type'])) {
		$video['wrapper']['attributes']['class'][] = 'ac-animate';
	}

	if (!empty($video['caption']['text'])) {
		$video['wrapper']['attributes']['class'][] = 'caption-enabled';
	}

	if($video['options']['fluid']) {
		$video['wrapper']['attributes']['class'][] = 'ac-fluid-video';
	}else if(!empty($video['options']['align'])) {
		$video['wrapper']['attributes']['class'][] = acquia_get_class_by_args(array('align'), array('align' => $video['options']['align']));
	}else {
		$video['wrapper']['attributes']['class'][] = 'ac-static-video';
	}

	if (!empty($video['caption']['text'])) {
		$video['inner']['attributes']['style'] = 'width:' .ac_check_unit($video['options']['width']);
	}

	$video_html = '';
	$file = file_load($video['fid']);
	switch ($file->filemime) {
		case 'video/vimeo':
			// do vimeo styling
			if (module_exists('media_vimeo')) {
				$theme = 'media_vimeo_video';
			}else {
				$theme = 'acquia_vimeo_video';
			}

			if ($video['style']['thumb']) {
				$image = array();
				$image['fid'] = acquia_external_video_thumb($video['fid']);
				$image['style'] = $video['style'];
				$image['style']['image_style'] = isset($video['style']['video_style']) ? $video['style']['video_style'] : NULL;
				$image['style']['lightbox'] = TRUE;
				$image['style']['video'] = $video['fid'];
				$video_html = acquia_image_format_extended($image);
			}else {
				$video_html .= theme($theme, array_merge(array('uri' => $file->uri, 'simple_style' => TRUE), $video['options']));
			}
			break;
		case 'video/youtube':
			if (module_exists('media_youtube')) {
				$theme = 'media_youtube_video';
				// @TODO move to UI
				$video['options'] += array(
					'theme' => 'dark',
					'color' => 'red',
					'autohide' => '2',
					'showinfo' => 1,
					'modestbranding' => 0,
					'rel' => 1,
					'nocookie' => 0,
					'protocol_specify' => 0,
					'protocol' => 'https:',
					'enablejsapi' => 0,
					'origin' => '');
			}else {
				$theme = 'acquia_youtube_video';
			}

			if ($video['style']['thumb']) {
				$image = array();
				$image['fid'] = acquia_external_video_thumb($video['fid']);

				$image['style'] = $video['style'];
				$image['style']['image_style'] = isset($video['style']['video_style']) ? $video['style']['video_style'] : NULL;
				$image['style']['lightbox'] = TRUE;
				$image['style']['video'] = $video['fid'];
				$video_html = acquia_image_format_extended($image);
			}else {
				$video_html = theme($theme, array('uri' => $file->uri, 'options' => $video['options']));
			}

			// do youtube styling
			break;

		default:
			if (!strstr($file->uri, 'public://') && !strstr($file->uri, 'private://')) {
				// @TODO return poster or link to file
				return false;
			}

			$video_html = theme('acquia_local_video', array('uri' => $file->uri, 'options' => $video['options']));
			// else do local file styles
			break;
	}

	if ($video['style']['frame'] == 'bottomshadow') {
		$video_html .= '<div class="shadow"><span class="shadow-left"></span><span class="shadow-right"></span></span></div>';
	}


	// Container attributes
	$video['container'] = array();
	$video['container']['class'] = array('ac-vid-wrap');

	// build Video
	$image['container']['class'] = implode(' ', $video['container']['class']);
	$video_html = '<div'.drupal_attributes($video['container']).'>'. $video_html.'</div>';

	// video wrapper tag
	$out = '<' .$video['wrapper']['tag'] .drupal_attributes($video['wrapper']['attributes']) .'>';
	if (!empty($video['style']['frame'])) {
		$out .= '	<div'.drupal_attributes($video['inner']['attributes']).'>';
	}
	$out .= $video_html;
	if (!empty($video['caption']['text'])) {
		$out .= '		<div'.drupal_attributes($video['caption']['attributes']).'>' .$video['caption']['text']. '</div>';
	}
	if (!empty($video['style']['frame'])) {
		$out .='</div>';
	}
	$out.= '</' .$video['wrapper']['tag'] .'>';

	return $out;
}

/**
 * Simple Image Format
 *
 * @TODO Document here
 */
function acquia_image_format_simple($image) {
	// we use fid for drupal managed files or scr for not managed files
	if (!isset($image['fid']) && !isset($image['src'])) {
		drupal_set_message('ACQUIA: given image uri is not valid');
		watchdog('ACQUIA', 'given image uri is not valid: @uri', array('@uri' => $image['fid']));
		return false;
	}

	$out = '';
	$image['path'] = @file_load($image['fid'])->uri;
	if (isset($image['style']['image_style']) && !empty($image['style']['image_style'])) {
		$image['style_name'] = $image['style']['image_style'];
		$out = theme('image_style', $image);
	}else {
		$out = theme('image', $image);
	}

	if (isset($image['link']['path']) && !empty($image['link']['path'])) {
		$image['link']['options'] = isset($image['link']['options']) ? $image['link']['options'] : array();
		$image['link']['options']['html'] = TRUE;
		$out = l($out, $image['link']['path'], $image['link']['options']);
	}

	return $out;
}

/**
 * Extended Image Format
 *
 * @param $variables
 *   An associative array containing:
 *   - fid: file if of image or absolute path to image
 *   - width: The width of the image (if known).
 *   - height: The height of the image (if known).
 *   - alt: The alternative text for text-based browsers. HTML 4 and XHTML 1.0
 *     always require an alt attribute. The HTML 5 draft allows the alt
 *     attribute to be omitted in some cases. Therefore, this variable defaults
 *     to an empty string, but can be set to NULL for the attribute to be
 *     omitted. Usually, neither omission nor an empty string satisfies
 *     accessibility requirements, so it is strongly encouraged for code calling
 *     theme('image') to pass a meaningful value for this variable.
 *     - http://www.w3.org/TR/REC-html40/struct/objects.html#h-13.8
 *     - http://www.w3.org/TR/xhtml1/dtds.html
 *     - http://dev.w3.org/html5/spec/Overview.html#alt
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 */
function acquia_image_format_extended($image, $reset=FALSE) {
	$cache = &drupal_static(__FUNCTION__, array(), $reset);
	acquia_include('utility');
	$cid = ac_gen_cid($image);
	if (isset($cache[$cid])) {
		return $cache[$cid];
	}

	static $no_image_uri;

	if (!isset($no_image_uri)) {
		$no_image_uri = acquia_variable_get('empty_image_uri');
	}

	// we use fid for drupal managed files or scr for not managed files
	if (!isset($image['fid']) && !isset($image['src'])) {
		$image['fid'] = acquia_variable_get('empty_thumb_fid', 0);
		unset($image['style']['effect']);
		if (!$image['fid']) {
			return;
		}
		//drupal_set_message('ACQUIA: given image uri is not valid');
		//watchdog('ACQUIA', 'given image uri is not valid: @uri', array('@uri' => $image['uri']));
		//return false;
	}

	acquia_include('utility');
	acquia_include('content');

	$image += array(
		'attributes' => array(),
		'link' => array(),
		'wrapper' => array(),
		'inner' => array(),
		'style' => array(),
		'animate' => array(),
		'caption' => array(),
		'suffix' => '',// @TODO add prefix
	);
	$defaults = array(
		// Image attributes
		'attributes' => array(
			'alt' => '', // image alt attribute
			'title' => '', // image title attribute
			'class' => array(), // image class attribute
		),

		// image Link
		'link' => array(
			'path' => '',
			'options' => array(),
		),

		// wrapper settings
		'wrapper' => array(
			'tag' => 'div',
			'attributes' => array(),
		),

		// wrapper settings
		'inner' => array(
			'attributes' => array('class' => array('media-i')),
		),

		// image style
		'style' => array(
			'image_style' => '', // image class attribute
			'effect' => '', // image effect
			'frame' => '', // image frame
			'align' => '', // image align
			'style' => '', // image style
			'lightbox' => FALSE, // lightbox
			'lightbox_fid' => '', // Custom Lightbox image instead of original image
			'lightbox_caption' => '', // lightbox Caption
			'lightbox_style' => '', // lightbox image style
			'video' => '', // video
			'preload' => TRUE, // video
			'no_features' => FALSE, // video
			'gridy' => FALSE, // gridy
		),

		// Animate
		'animate' => array(
			'type' => '', // Animate type
			'when' => '', // Animate when?
		),

		// image caption
		'caption' => array(
			'text' => '',
			'attributes' => array('class' => array('caption', 'clearfix')),
		),
		// image caption
		'suffix' => ''
	);

	foreach($defaults as $attr => $vals) {
		if (is_array($vals)) {
			$image[$attr] += $vals;
		}
	}
	if (isset($image['fid']) && !empty($image['fid'])) {
		$file = file_load($image['fid']);
		$image_uri = isset($file->uri) ? $file->uri : $no_image_uri;
	}elseif (isset($image['src']) && !empty($image['src'])) {
		$image_uri = $image['src'];
	}else {
		$image_uri = '';
	}

	$features = 0;
	$features = $image['style']['lightbox'] ? $features+=1 : $features;
	$features = !empty($image['link']['path']) ? $features+=1 : $features;
	$features = !empty($image['suffix']) ? $features+=1 : $features;

	// add image suffix HTML
	$suffix = !empty($image['suffix']) ? $image['suffix'] : '';
	$image['wrapper']['attributes']['class'] = !empty($image['wrapper']['attributes']['class']) ? $image['wrapper']['attributes']['class'] : array();
	array_unshift($image['wrapper']['attributes']['class'], 'ac-media');

	if ($features <= 1) {
		$image['wrapper']['attributes']['class'][] = 'ac-sf';
	}else{
		$image['wrapper']['attributes']['class'][] = 'ac-mf';
	}

	if (!empty($image['style']['frame'])) {
		$image['wrapper']['attributes']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $image['style']['frame'])) . '-wrap';
		$image['inner']['attributes']['class'][] = 'ac-frame-on';
		$image['inner']['attributes']['class'][] = acquia_get_class_by_args(array('frame'), array('frame' => $image['style']['frame']));
	}else{
		$image['wrapper']['attributes']['class'][] = 'ac-nf';
	}

	if (!empty($image['style']['align'])) {
		$image['wrapper']['attributes']['class'][] = acquia_get_class_by_args(array('align'), array('align' => $image['style']['align']));
	}

	if (!empty($image['animate']['type'])) {
		$image['wrapper']['attributes']['class'][] = 'ac-animate';
	}

	if (!empty($image['caption']['text'])) {
		$image['wrapper']['attributes']['class'][] = 'caption-enabled';
	}

	// Preload
	if ($image['style']['preload']) {
		$image['attributes']['class'][] = 'ac-preload';
	}

	// default by scr
	$image_path = isset($image['src']) ? $image['src'] : '';

	// overriding from managed files
	if (!empty($image['style']['image_style'])) {
		$image_path = image_style_url($image['style']['image_style'], $image_uri);
	}else {
		$image_path = file_create_url($image_uri);
	}

	// Try PHP built in function to get image dimension
	if (!isset($image['attributes']['width']) || !isset($image['attributes']['height'])) {
		list($image['attributes']['width'], $image['attributes']['height']) = @getimagesize($image_path);
	}

	if (isset($image['attributes']['width']) && isset($image['attributes']['height'])) {
		if ($image['attributes']['width'] > 600 && $image['attributes']['height'] > 300) {
			$image['wrapper']['attributes']['class'][] = 'l-img';// large sized image
		}elseif ($image['attributes']['width'] > 100 && $image['attributes']['height'] > 100) {
			$image['wrapper']['attributes']['class'][] = 'm-img';// medium sized image
		}else{
			$image['wrapper']['attributes']['class'][] = 's-img';//small sized image
		}
	}

	if (!empty($image['caption']['text'])) {
		list($width) = @getimagesize($image_path);
		$image['inner']['attributes']['style'] = 'width:' .$width .'px;';
	}

	if (!empty($image['attributes']['title'])) {
		$title = '<h5 class="i-t"><span>' .strip_tags($image['attributes']['title']) .'</span></h5>';
		$image['wrapper']['attributes']['class'][]  = 'ac-title-enabled';
	}else{
		$title ='';
	}
	if ($features > 1) {
		// lightbox
		if ($image['style']['lightbox'] == TRUE) {
			$vars['item']['uri'] = !empty($image['style']['lightbox_fid']) ? file_load($image['style']['lightbox_fid'])->uri : $image_uri;
			if (!empty($image['style']['lightbox_caption'])) {
				$caption = $image['style']['lightbox_caption'];
			}else if (!empty($image['caption']['text'])){
				$caption = $image['caption']['text'];
			}else {
				$caption = '';
			}
			$vars['item']['caption'] = check_plain(strip_tags($caption));
			$vars['item'] += $image['attributes'];
			$vars['image_style'] = $image['style']['image_style'];
			if (!empty($image['style']['video'])) {
				$vars['lightbox_video'] = file_load($image['style']['video'])->uri;
			}
			if ( !empty($image['style']['lightbox_style']) ) {
				$vars['lightbox_style'] = $image['style']['lightbox_style'];
			}
			$suffix .= theme('acquia_popup', $vars);
			$image['wrapper']['attributes']['class'][] = 'ac-lightbox-image';
		}

		// Linked Image
		if (!empty($image['link']['path'])) {
			$image['link']['path'] = $image['link']['path'] == 'front' ? '<front>' : $image['link']['path'];
			$image['link']['options'] = array_merge($image['link']['options'], array('html' => true));

			$suffix .= l(theme('acquia_media_feature', array('type' => 'link')), $image['link']['path'], $image['link']['options']);
			$image['wrapper']['attributes']['class'][] = 'ac-linked-image';
		}

		$suffix = '<i class="ac-f features"><span class="ac-t"><span class="ac-c">' .$suffix .$title .'</span></span></i>';
		$image_html = theme_image(array('path' => $image_path, 'attributes' => $image['attributes']));

	}else if ($image['style']['lightbox'] == TRUE) {
		acquia_load_resources('popup');
		$vars = array();
		$vars['item']['uri'] = $image_uri;
		if (!empty($image['style']['lightbox_caption'])) {
			$caption = $image['style']['lightbox_caption'];
		}else if (!empty($image['caption']['text'])){
			$caption = $image['caption']['text'];
		}else {
			$caption = '';
		}
		$vars['item']['caption'] = check_plain(strip_tags($caption));
		$vars['item'] += $image['attributes'];
		$vars['image_style'] = $image['style']['image_style'];
		if (!empty($image['style']['video'])) {
			$vars['lightbox_video'] = file_load($image['style']['video'])->uri;
			$vars['type'] = 'video';
			$extra_class = 'video';
			$b_title = !empty($image['attributes']['title']) ? $image['attributes']['title'] : "Lunch Video";
		}else{
			$vars['type'] = 'image';
			$extra_class = 'image';
			$b_title = !empty($image['attributes']['title']) ? $image['attributes']['title'] : "View Photo";
		}

		$vars['node_id'] = 'undefined';// @todo
		$vars['field_name'] = 'NA';// @todo
		if ( !empty($image['style']['lightbox_style']) ) {
			$vars['lightbox_style'] = $image['style']['lightbox_style'];
		}
		$image_html = theme('acquia_popup', $vars);
		$image['wrapper']['attributes']['class'][] = 'ac-lightbox-image';
		// add rollover effect HTML
		$feature = theme('acquia_media_feature', array('type' => 'popup', 'extra_class' => array($extra_class)));
		$suffix .= '<i class="ac-f features">'.$feature.$title.'</i>';
	}else {
		$image_html = theme_image(array('path' => $image_path, 'attributes' => $image['attributes']));
	}

	$image_html = preg_replace('/(<img\s+[^>)]*>)/', '$1'.$suffix, $image_html);

	// Container attributes
	$image['container'] = array();
	$image['container']['class'] = array('img-wrap', 'clearfix');

	if (!empty($image['style']['effect'])) {
		$image['wrapper']['attributes']['class'][] = 'ac-effect-container';
		$image['container']['class'][] = acquia_get_class_by_args(array('effect'), array('effect' => $image['style']['effect']));
		if ($image['style']['effect'] == 'overlay') {
			$image_html = preg_replace('/(<img\s+[^>)]*>)/', '$1<span class="ac-overlay from-left"></span>', $image_html);
		}
	}

	// Linked Image
	if ($features <=1 && !empty($image['link']['path'])) {
		$image['link']['path'] = $image['link']['path'] == 'front' ? '<front>' : $image['link']['path'];
		$image['link']['options'] = array_merge($image['link']['options'], array('html' => true));
		$link_f = !$image['style']['no_features'] ? '<i class="ac-f features">'.theme('acquia_media_feature', array('type' => 'link')) . $title.'</i>' : '';
		$image_html = l($image_html . $link_f, $image['link']['path'], $image['link']['options']);
		$image['wrapper']['attributes']['class'][] = 'ac-linked-image';
	}


	if ($image['style']['frame'] == 'bottomshadow') {
		$image_html .= '<div class="shadow"><span class="shadow-left"></span><span class="shadow-right"></span></span></div>';
	}else if ($image['style']['frame'] == 'glow_circled') {
		$image_html = preg_replace('/(<img\s+[^>)]*>)/', '$1<span class="shadow"></span>', $image_html);
	}

	// build image
	$image['container']['class'] = implode(' ', $image['container']['class']);
	$image_html = '<div'.drupal_attributes($image['container']).'>'. $image_html.'</div>';

	$out = '';
	/** Wrap Grid HTML **/
	if ($image['style']['gridy'] == TRUE) {
		$out .= '<div class="ac-grid-item">';
		$out .= '	<div class="g-i">';
		$out .= '		<div class="g-i-i clearfix">';
	}

	$out .= '<' .$image['wrapper']['tag'] .drupal_attributes($image['wrapper']['attributes']) .'>';

	if (!empty($image['style']['frame'])) {
		$out .= '	<div'.drupal_attributes($image['inner']['attributes']).'>';
	}
	$out .= $image_html;
	if (!empty($image['caption']['text'])) {
		$out .= '		<div'.drupal_attributes($image['caption']['attributes']).'>' .$image['caption']['text']. '</div>';
	}
	if (!empty($image['style']['frame'])) {
		$out .='</div>';
	}

	$out.= '</' .$image['wrapper']['tag'] .'>';
	/** Wrap Grid HTML **/
	if ($image['style']['gridy'] == TRUE) {
		$out .= '		</div>';
		$out .= '	</div>';
		$out .= '</div>';
	}
	$cache[$cid] = $out;

	return $cache[$cid];
}


/**
 * Get remote video thumbnail uri
 */
function acquia_get_remote_video_thumb_uri($video_uri) {
	if (empty($video_uri)) {
		drupal_set_message(t('<ACQUAI::MEDIA>: Error while generating video thumbnail. no uri is provided!'));
		return;
	}

	$scheme = file_uri_scheme($video_uri);
	if (in_array($scheme, array('vimeo', 'youtube'))) {
		$wrapper = file_stream_wrapper_get_instance_by_uri($video_uri);
		return $wrapper->getOriginalThumbnailPath();
	}else {
		drupal_set_message(t('<ACQUAI::MEDIA>: Error while generating video thumbnail. the given video is not supported: @uri', array('@uri' => $video_uri)));
		return;
	}

}


/**
 * Add video fid and corresponding thumbail image fid
 */
function acquia_add_video_thumb_fid($vfid, $ifid) {
	if (!empty($vfid) && !empty($ifid)) {
		db_insert('acquia_video_thumb')
			->fields(array(
				'ifid' => $ifid,
				'vfid' => $vfid,
			))
			->execute();
	}
}

/**
 * Uploading externl video thumbnail to database
 */
function acquia_external_video_thumb($video_fid) {
	if (empty($video_fid) || !is_numeric($video_fid)) {
		drupal_set_message(t('<ACQUAI::MEDIA>: Invalid video URL provided.'));
		return;
	}

	$image_fid = acquia_get_video_thumb_fid($video_fid);

	if (!$image_fid) {
		$image_uri = FALSE;
		$file = file_load($video_fid);

		switch ($file->filemime) {
			case 'video/vimeo':
				if (module_exists('media_vimeo')) {
					$image_uri = acquia_get_remote_video_thumb_uri($file->uri);
				}
				break;
			case 'video/youtube':
				if (module_exists('media_youtube')) {
					$image_uri = acquia_get_remote_video_thumb_uri($file->uri);
				}
				break;
		}

		if (!empty($image_uri)) {
			$image_fid = acquia_upload_remote_file($image_uri, array('permanent' => 1));
			acquia_add_video_thumb_fid($video_fid, $image_fid);
		}
	}
	return $image_fid;
}

/**
 * Get external video source thumbnail file id
 */
function acquia_get_video_thumb_fid($video_fid){
	$thumb_fid = &drupal_static(__FUNCTION__, NULL);

	if (!isset($cache)) {
		$query = db_select('acquia_video_thumb', 'v')
			->fields('v');
		$query
			->condition('v.vfid', $video_fid);

		$image_fid = $query->execute()->fetchAll(PDO::FETCH_ASSOC);
		$image_fid = isset($image_fid[0]['ifid']) ? $image_fid[0]['ifid'] : FALSE;
	}

	return $image_fid;
}

/**
 * A #filefield_value_callback function.
 * @return $file->fid if upload was successfull.
 */
function acquia_upload_remote_file($uri, $settings = array()) {
	if (empty($uri)) {
		return;
	}

	acquia_include('file');
	$file = acquia_upload_remote_uri($uri, $settings);
	if (is_object($file) && !empty($file->fid)) {
		return $file->fid;
	}

	return FALSE;
}

/**
 *
 */
function acquia_get_image_style_dimension($style){
	$cache = &drupal_static(__FUNCTION__, NULL);

	if (!isset($cache[$style])) {

		module_load_include('inc', 'image', 'image.effects');
		$style_arr = image_style_load($style);
		if (!is_array($style_arr)) {
			$cache[$style] = array();
		}else{
			foreach ($style_arr['effects'] as $effect) {
				if (isset($effect['data']['width']) && isset($effect['data']['height'])) {
					$cache[$style]['width'] = $effect['data']['width'];
					$cache[$style]['height'] = $effect['data']['height'];
				}
			}
		}
	}

	return $cache[$style];
}

/**
 *
 */
function acquia_get_empty_thumb($style = 'NONE'){
	static $drupal_static_fast;
	if (!isset($drupal_static_fast)) {
		$drupal_static_fast['cache'] = &drupal_static(__FUNCTION__, array());
	}
	$cache = &$drupal_static_fast['cache'];

	if (!empty($style) && !isset($cache[$style])) {
		$fid = acquia_variable_get('empty_thumb_fid', 0);
		if (!$fid) {
			$fid = acquia_add_empty_thumb();
		}

		$file = file_load($fid);
		if (isset($file->uri)) {
			if ($style != 'NONE') {
				$cache[$style] = image_style_url($style, $file->uri);
			}else{
				$cache[$style] = file_create_url($file->uri);
			}
		}
	}
	return $cache[$style];
}

/**
 *
 */
function acquia_add_empty_thumb() {
	$file = drupal_get_path('module', 'acquia') . '/images/empty-thumb.png';

	if (!file_exists($file)) {
		drupal_set_message(t('Acquia::Media: empty thumbnail image not exists!'));
		return 0;
	}

	$file_temp = file_get_contents($file);


	//Saves a file to the specified destination and creates a database entry.
	$file_temp = file_save_data($file_temp, acquia_variable_get('upload_location') . '/ac-empty-thumb.png', FILE_EXISTS_RENAME);

	if ($file_temp && isset($file_temp->fid)) {
		acquia_variable_set('empty_thumb_fid', $file_temp->fid);
		return $file_temp->fid;
	}

	return 0;
}

/**
 * Get absolute source url from fid
 * @param $fid
 * @return bool|string
 */
function acquia_get_image($fid) {
	if (is_numeric($fid)&& $fid !=0) {
		$file = file_load((int)$fid);
		return isset($file->uri) ? file_create_url($file->uri, array('absolute' => TRUE)) : '';
	}
	return '';
}