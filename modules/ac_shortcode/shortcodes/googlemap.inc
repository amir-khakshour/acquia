<?php
/**
 * @file shortcode defenition of audio
 */
/**
 * Implements ac_shortcode_SHORTCODE_shortcode()
 * @return an array of shortcodes defenition
 *
 * 	Shortcode settings array consists of below values:
 * 	 %tag : Shortcode tag
 * 	 %title: Shortcode title
 * 	 %description: Shortcode description
 * 	 %category: An array of categories that this shortcode belongs to
 * 	 %class: A class name that contains methods to process the tag
 * 	 %file: Shortcode class file name
 * 	 %path: Relative path to shortcode class file
 * 	 %nested shortcodes: Array of shortcode tags that can be nested
 *    	in this shortcode and processed as a value of current shortcode
 * 	 %hidden: A Boolean value indicating whether this shortcode must
 *    	be hidden in the shortcodes list or not. it works in conjunction
 *    	with %enabled key.
 * 	 %enabled: Array of shortcode tags and a Boolean value that represents
 *    	the circumstances that the shortcode can be enabled based on the
 *    	status of other shortcodes.
 */

function ac_shortcode_googlemap_shortcode() {
	return array(
		'ac_gmap' => array(
			'title' => t('Google Maps'),
			'description' => t('Adds Maps from map.google.com to your content.'),
			'form callback' => 'ac_shortcode_ac_gmap_form',
			'values process callback' => 'ac_shortcode_ac_gmap_preprocess',
			'process callback' => 'ac_shortcode_ac_gmap_process',
			'nested shortcodes' => array('markers' => 'ac_gmap_marker'),
		),
		'ac_gmap_marker' => array(
			'hidden' => TRUE,
			'enabled' => array('ac_gmap' => TRUE),
			'title' => t('Google Maps marker'),
			'description' => t('Adds Marker to your map.'),
			'values process callback' => 'ac_shortcode_ac_gmap_marker_preprocess',
			'process callback' => 'ac_shortcode_ac_gmap_marker_process',
		),
	);
}

/**
 * Implements edit form of {{ac_gmap}} shortcode
 */
function ac_shortcode_ac_gmap_form($form, &$form_state) {
	acquia_include('utility');
	acquia_include('options');
	acquia_include('theme');

	$values = isset($form_state['values']) ? $form_state['values'] : array();
	// Convert socials from editor to form compatible.
	if (isset($values['markers']) && is_array($values['markers']) && !isset($values['markers']['marker'])) {
		$form_state['marker_nums'] = count($values['markers']);
		$values['markers'] = array('marker' => $values['markers']);
	}

	$form['#prefix'] = '<div id="ac-google-map-generator" class="acquia-theme-options ac-admin">';
	$form['#prefix'] .= '<div class="media-frame-outter">';
	$form['#prefix'] .= '<div class="media-frame-content">';

	$styles = '';
	if ( isset($values['width']) && !empty($values['width']) )  {
		$styles .=' width:'.$values['width'].';';
	}
	if ( isset($values['height']) && !empty($values['height']) ) {
		$styles .=' width:'.$values['height'].';';
	}

	$form['#prefix'] .='<div id="mgl_map_generator" class="mgl_map" style="'.$styles.'"></div>';
	$form['#prefix'] .='</div>';
	$form['#prefix'] .='</div>';

	$form['#suffix'] = '</div>';

	// Adds vertical tab styles	
	acquia_add_vertical_tabs_style($form);

	$loaded = drupal_add_js();
	drupal_add_library('acquia', 'gmap');
	$new = drupal_add_js(ACQUIA_COMPOSER_ASSET_PATH . '/js/googlemap/generator.js');
	$js = array_diff_key($new, $loaded);
	$form['#attached']['js'] = $js;

	$form['map_settings'] = array(
		'#type' => 'vertical_tabs',
		'#title' => t('Map Settings'),
	);

	// Map settings Tab
	$form['map'] = array(
		'#type' => 'fieldset',
		'#title' => t('Map Settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
		'#group' => 'map_settings',
	);

	$form['map']['mapid'] = array(
		'#disabled' => TRUE,
		'#type' => 'textfield',
		'#title' => t('Map ID'),
		'#default_value' => acquia_get_unique_id('ac-gmap'),
	);

	$form['map']['address'] = array(
		'#type' => 'textfield',
		'#title' => t('Address'),
		'#description' => t('You can type a valid address here, the map will update to your entered address.'),
		'#default_value' => isset($values['address']) ? $values['address'] : '',
	);

	$form['map']['lat'] = array(
		'#type' => 'textfield',
		'#title' => t('Lattitude'),
		'#description' => t('Map Latitude.'),
		'#default_value' => isset($values['lat']) ? $values['lat'] : '',
	);

	$form['map']['long'] = array(
		'#type' => 'textfield',
		'#title' => t('Longitude'),
		'#description' => t('Map Longitude.'),
		'#default_value' => isset($values['long']) ? $values['long'] : '',
	);

	$form['map']['zoom'] = array(
		'#type' => 'select',
		'#title' => t('Map Zoom'),
		'#description' => t('Here you can set the zoom level of your map.'),
		'#options' => drupal_map_assoc(range(1,20)),
		'#default_value' => isset($values['zoom']) ? $values['zoom'] : 14,
	);

	$form['map']['map_width'] = array(
		'#type' => 'select',
		'#title' => t('Map Width'),
		'#description' => t('Select Width of your map Here.'),
		'#default_value' => isset($values['map_width']) ? $values['map_width'] : '',
		'#options' => array('custom' => t('custom'), 'full' => t('window width')),
	);

	$form['map']['width'] = array(
		'#type' => 'textfield',
		'#title' => t('Custom Width'),
		'#description' => t('Set the Custom Width of your map in pixel or container percentage Here. e.g. 320px'),
		'#default_value' => isset($values['width']) ? $values['width'] : '',
		'#states' => array(
			'visible' => array(
				':input[name="map_width"]' => array('value' => 'custom'),
			),
		),
	);

	$form['map']['height'] = array(
		'#type' => 'textfield',
		'#title' => t('Height'),
		'#description' => t('Set the Height of your map in pixel or container percentage Here. e.g. 320px'),
		'#default_value' => isset($values['height']) ? $values['height'] : '',
	);

	$op = acquia_align_list();
	$op = array_merge(array('' => t('Inherit')), $op);

	$form['map']['align'] = array(
		'#type' => 'select',
		'#title' => t('Map alignment'),
		'#description' => t('Choose the alignment of your Map here'),
		'#default_value' => isset($values['align']) ? $values['align'] : (acquia_variable_get('doc_direction') == 'LTR' ? 'left' : 'right'),
		'#options' => $op,
	);

	$ops = array_merge(array('custom' => t('Custom Color')), acquia_google_map_types());

	$form['map']['type'] = array(
		'#type' => 'select',
		'#title' => t('Map type'),
		'#description' => t('Here you can set the styling of the googlemap element'),
		'#options' => $ops,
		'#default_value' => isset($values['type']) ? $values['type'] : 'roadmap',
	);

	$form['map']['caption'] = array(
		'#type' => 'text_format',
		'#title' => t('Map Caption'),
		'#description' => t('Enter a few words that describe the map.'),
		'#default_value' => isset($values['caption']) ? rawurldecode(base64_decode(strip_tags($values['caption']))) : array(),
		'#format' => NULL,
		'#rows' => 15,
	);

	$form['map']['color'] = array(
		'#attributes' => array('class' => array('field-colorpicker')),
		'#type' => 'textfield',
		'#title' => t('Custom Color'),
		'#description' => t('Select a custom color for your map here'),
		'#default_value' => isset($values['color']) ? $values['color'] : '#444444',
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'custom'),
			),
		),
	);

	/** Global shortcode elements **/
	$form['map']['class'] = array(
		'#type' => 'textfield',
		'#title' => t('Extra class name'),
		'#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
		'#default_value' => isset($values['class']) ? $values['class'] : '',
	);

	if (empty($form_state['marker_nums'])) {
		$form_state['marker_nums'] = 0;
	}

	// Map settings Tab
	$form['markers'] = array(
		'#type' => 'fieldset',
		'#title' => t('Markers'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
		'#tree' => TRUE,
		'#group' => 'map_settings',
	);

	$default = array(
		'address' => '',
		'lat' => '',
		'long' => '',
		'content' => '',
	);

	$markers = isset($values['markers']['marker']) ? $values['markers']['marker'] : array();
	for ($i = 0; $i < $form_state['marker_nums']; $i++) {
		$markers[$i] = isset($markers[$i]) ? $markers[$i] : array();
		//$markers_default[$i] += $default;

		$form['markers']['marker'][$i] = array(
			'#attributes' => array('class' => array('ac-gmap-marker', 'ac-gmap-marker-'.$i ), 'data-markerid' => $i),
			'#type' => 'fieldset',
			'#title' => t('Marker #@num', array('@num' => $i+1)),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
		);

		$form['markers']['marker'][$i]['address'] = array(
			'#attributes' => array('class' => array('ac-gmap-marker-address', 'ac-gmap-marker-address-'.$i )),
			'#type' => 'textfield',
			'#title' => t('address'),
			'#description' => t('description here.'),
			'#default_value' => isset($markers[$i]['address']) ? $markers[$i]['address'] : '',
		);

		$form['markers']['marker'][$i]['lat'] = array(
			'#attributes' => array('class' => array('ac-gmap-marker-lat', 'ac-gmap-marker-lat-'.$i )),
			'#type' => 'textfield',
			'#title' => t('Latitude'),
			'#description' => t('description here.'),
			'#default_value' => isset($markers[$i]['lat']) ? $markers[$i]['lat'] : '',
		);

		$form['markers']['marker'][$i]['long'] = array(
			'#attributes' => array('class' => array('ac-gmap-marker-long', 'ac-gmap-marker-long-'.$i )),
			'#type' => 'textfield',
			'#title' => t('Longitude'),
			'#description' => t('description here.'),
			'#default_value' => isset($markers[$i]['long']) ? $markers[$i]['long'] : '',
		);

		$form['markers']['marker'][$i]['content'] = array(
			'#attributes' => array('class' => array('ac-gmap-marker-content', 'ac-gmap-marker-content-'.$i )),
			'#type' => 'textarea',
			'#title' => t('Markers content here.'),
			'#description' => t('description here.'),
			'#default_value' => isset($markers[$i]['content']) ? $markers[$i]['content'] : '',
		);

		$form['markers']['marker'][$i]['delete'] = array(
			'#prefix' => '<div class="form-actions">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('ac-gmap-marker-delete-marker', 'ac-gmap-marker-delete-marker-'.$i )),
			'#type' => 'submit',
			'#value' => t('Delete Marker #'.($i +1) .''),
			'#submit' => array('ac_shortcode_ac_gmap_delete_marker'),
		);
	}

	$form['markers']['add_marker'] = array(
		'#prefix' => '<div id="add-marker" class="form-actions">',
		'#suffix' => '</div>',
		'#type' => 'submit',
		'#value' => $form_state['marker_nums'] >0 ? t('Add another Marker') : t('Add Marker'),
		'#submit' => array('ac_shortcode_ac_gmap_add_marker'),
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * Submit handler for "Add another Marker" button on ac_shortcode_ac_gmap_form().
 */
function ac_shortcode_ac_gmap_add_marker($form, &$form_state) {
	$form_state['marker_nums']++;
	$form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for "Delete Marker" button on ac_shortcode_ac_gmap_form().
 */
function ac_shortcode_ac_gmap_delete_marker($form, &$form_state) {
	if (isset($form_state['clicked_button']['#parents'][2])) {
		$id = $form_state['clicked_button']['#parents'][2];
		if ( isset($form_state['values']['markers']['marker'][$id]) ) {
			unset($form_state['values']['markers']['marker'][$id]);
			$form_state['values']['markers']['marker'] = array_values($form_state['values']['markers']['marker']);
			$form_state['marker_nums']--;
			$form_state['rebuild'] = TRUE;
		}
	}

}

/**
 * Process {{ac_gmap}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_gmap_preprocess(&$values) {
	if (isset($values['type']) && $values['type'] != 'custom') {
		unset($values['color']);
	}

	if (isset($values['bubble']) && $values['bubble'] == TRUE) {
		$values['bubble'] = 'true';
	}else{
		$values['bubble'] = 'false';
	}

	if (isset($values['caption']) && isset($values['caption']['value'])) {
		$values['caption'] = base64_encode($values['caption']['value']);
	}

	$markers = $values['markers'];
	unset($values['markers']);
	$values['markers'] = $markers['marker'];

	foreach($values['markers'] as &$marker) {
		unset($marker['delete']);
	}
	unset($values['map_settings__active_tab']);

	if (isset($values['map_width']) && $values['map_width'] == 'full') {
		unset($values['width']);
	}
}

/**
 * process {{ac_gmap_marker}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_gmap_marker_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'address' => '',
		'lat' => '',
		'long' => '',
	), $attrs);

	extract($_attrs);

	$marker = array();
	$marker['address'] = !empty($address) ? $address : NULL;
	$marker['latitude'] = !empty($lat) ? $lat : NULL;
	$marker['longitude'] = !empty($long) ? $long : NULL;
	$marker['html'] = !empty($text) ? $text : NULL;

	$marker = array_filter($marker, 'strlen');

	if (count($marker) == 0) {
		return ;
	}

	$out = array();
	$string_vals = array('address', 'html');
	foreach($marker as $key => $val) {
		if (in_array($key, $string_vals)) {
			$val = "'" .$val ."'";
		}
		$out[]= $key .':'. $val;
	}

	return '{' . implode(',', $out) . '},';
}

/**
 * process {{ac_gmap}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_gmap_process($attrs, $text = null, $shortcode = '') {
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'mapid' => '',
		'address' => '',
		'lat' => '',
		'long' => '',
		'zoom' => '14',
		'map_width' => 'custom',
		'width' => '640px',
		'height' => '320px',
		'align' => '',
		'type' => 'roadmap',
		'caption' => '',
		'color' => '',
	), $attrs);

	extract($_attrs);

	if (empty($mapid)) {
		return drupal_set_message('DiamondLayers Shortcode: MAP ID is needed. Set the attribute mapID in the shortcode.');
	}


	$styles = array('height' => empty($height) ? '320px' : $height);

	if ($map_width == 'custom') {
		$styles['width'] = empty($width) ? '640px' : $width;
	}


	$sc_name = str_replace('_', '-', $shortcode);

	$wrapper_attrs = array('class' => array($sc_name. '-wrapper', 'clearfix'));

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'clearfix';

	if ($map_width == 'full') {
		$classes[] = 'ac-full-container-width';
		$wrapper_attrs['class'][] = 'ac-full-container-width';
	}else{
		$classes[] = acquia_get_class_by_args(array('align'), $_attrs, CHECK_LENGTH);
	}

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;
	$attributes['id'] = $mapid;
	$attributes['style'] = acquia_style_arr_to_tag($styles);

	// Build map location
	$location = '';
	if ( !empty($address) ) {
		$location = 'address: "' . $address . '"';
	}else{
		$location = 'latitude: ' . $lat . ',longitude: ' . $long;
	}

	$location = !empty($location) ? $location . ',' : $location;
	// Build markers
	$markers = '';
	if (!empty($text)) {
		$markers = 'markers:['.$text.']';
	}

	// add libs
	drupal_add_js('http://maps.google.com/maps/api/js?sensor=true', array('external' => TRUE));
	drupal_add_library('acquia', 'gmap');

	if (!empty($caption)) {
		$caption = check_markup(base64_decode($caption), 'full_html');
		$caption = '<div class="ac-gmap-caption clearfix">' . $caption . '</div>';
	}

	$out = '<div '.drupal_attributes($wrapper_attrs).'><div'.drupal_attributes($attributes).'></div>'.$caption.'</div>';
	$out .= '<script type="text/javascript">
						jQuery(document).ready(function($){
							$("#' . $mapid . '").gMap({
								controls: { mapTypeControl: false, zoomControl: true, panControl: true, streetViewControl: true },
								zoom: ' . $zoom . ',
								' . $location . '
								' . $markers . '
							});
						});
					</script>';

	if ($type != '' && $color == '') {
		// Load skin
		switch($type) {
			case 'satellite':
			case 'roadmap':
				$out .= '
				 <script type="text/javascript">
				 jQuery(document).ready(function($){
							 $("#' . $mapid . '").data("gMap.reference").setMapTypeId("'.$type.'");
							 });
				 </script>';
				break;

			case 'hybrid':
				$out .= '
				 <script type="text/javascript">
				 jQuery(document).ready(function($){
							 $("#' . $mapid . '").data("gMap.reference").setMapTypeId("google.maps.MapTypeId.HYBRID");
							 });
				 </script>';
				break;

			case 'terrain':
				$out .= '
				 <script type="text/javascript">
				 jQuery(document).ready(function($){
							 $("#' . $mapid . '").data("gMap.reference").setMapTypeId("google.maps.MapTypeId.TERRAIN");
							 });
				 </script>';
				break;

			default:
				$out .= '
				 <script type="text/javascript">
				 jQuery(document).ready(function($){'.
					gmap_get_skin_by_name($type).'
					 var '.$type.'styledMap = new google.maps.StyledMapType('.$type.'_styles, {name: "'.$type.'"});
							 // Setup skin for the map
							 $("#' . $mapid . '").data("gMap.reference").mapTypes.set("'.$type.'_style", '.$type.'styledMap);
							 $("#' . $mapid . '").data("gMap.reference").setMapTypeId("'.$type.'_style");
							 });
				 </script>';
				break;
		}

	} else if($color != '') {
		$color_id = substr($color, 1);
		$out .= '
		 <script type="text/javascript">
		 jQuery(document).ready(function($){
       var one_color_'.$color_id.'_styles = [ 
	        { "stylers": [ { "hue": "#'.$color_id.'" }, { "saturation": 1 }, { "lightness": 1 } ] }
	      ]; 
			 var one_color_'.$color_id.'styledMap = new google.maps.StyledMapType(one_color_'.$color_id.'_styles, {name: "one_color_'.$color_id.'"});
					 // Setup skin for the map
					 $("#' . $mapid . '").data("gMap.reference").mapTypes.set("one_color_'.$color_id.'_style", one_color_'.$color_id.'styledMap);
					 $("#' . $mapid . '").data("gMap.reference").setMapTypeId("one_color_'.$color_id.'_style");
					 });
		 </script>';
	}

	return str_replace('},]', '}]', $out);
}

function gmap_get_skin_by_name($name) {
	switch ($name) {
		case 'cartoon':

			$skin =  '// Cartoon
								 var cartoon_styles = [ 
										 { "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" }] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#b1bc39" } ]
									 },{ "featureType": "landscape.man_made", "stylers": [ { "visibility": "on" }, { "color": "#ebad02" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#416d9f" } ] 
									 },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "off" }, { "color": "#ffffff" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#ebad02" } ]
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#8ca83c" } ]
									 } 
								 ];';
			break;

		case 'ultra_light':
			$skin =  'var ultra_light_styles = [{"featureType":"water","elementType":"geometry","stylers":[{"color":"#e9e9e9"},{"lightness":17}]},{"featureType":"landscape","elementType":"geometry","stylers":[{"color":"#f5f5f5"},{"lightness":20}]},{"featureType":"road.highway","elementType":"geometry.fill","stylers":[{"color":"#ffffff"},{"lightness":17}]},{"featureType":"road.highway","elementType":"geometry.stroke","stylers":[{"color":"#ffffff"},{"lightness":29},{"weight":0.2}]},{"featureType":"road.arterial","elementType":"geometry","stylers":[{"color":"#ffffff"},{"lightness":18}]},{"featureType":"road.local","elementType":"geometry","stylers":[{"color":"#ffffff"},{"lightness":16}]},{"featureType":"poi","elementType":"geometry","stylers":[{"color":"#f5f5f5"},{"lightness":21}]},{"featureType":"poi.park","elementType":"geometry","stylers":[{"color":"#dedede"},{"lightness":21}]},{"elementType":"labels.text.stroke","stylers":[{"visibility":"on"},{"color":"#ffffff"},{"lightness":16}]},{"elementType":"labels.text.fill","stylers":[{"saturation":36},{"color":"#333333"},{"lightness":40}]},{"elementType":"labels.icon","stylers":[{"visibility":"off"}]},{"featureType":"transit","elementType":"geometry","stylers":[{"color":"#f2f2f2"},{"lightness":19}]},{"featureType":"administrative","elementType":"geometry.fill","stylers":[{"color":"#fefefe"},{"lightness":20}]},{"featureType":"administrative","elementType":"geometry.stroke","stylers":[{"color":"#fefefe"},{"lightness":17},{"weight":1.2}]}]';
			break;
		case 'light_grey':
			$skin =  'var light_grey_styles = [{"featureType":"water","elementType":"geometry.fill","stylers":[{"color":"#d3d3d3"}]},{"featureType":"transit","stylers":[{"color":"#808080"},{"visibility":"off"}]},{"featureType":"road.highway","elementType":"geometry.stroke","stylers":[{"visibility":"on"},{"color":"#b3b3b3"}]},{"featureType":"road.highway","elementType":"geometry.fill","stylers":[{"color":"#ffffff"}]},{"featureType":"road.local","elementType":"geometry.fill","stylers":[{"visibility":"on"},{"color":"#ffffff"},{"weight":1.8}]},{"featureType":"road.local","elementType":"geometry.stroke","stylers":[{"color":"#d7d7d7"}]},{"featureType":"poi","elementType":"geometry.fill","stylers":[{"visibility":"on"},{"color":"#ebebeb"}]},{"featureType":"administrative","elementType":"geometry","stylers":[{"color":"#a7a7a7"}]},{"featureType":"road.arterial","elementType":"geometry.fill","stylers":[{"color":"#ffffff"}]},{"featureType":"road.arterial","elementType":"geometry.fill","stylers":[{"color":"#ffffff"}]},{"featureType":"landscape","elementType":"geometry.fill","stylers":[{"visibility":"on"},{"color":"#efefef"}]},{"featureType":"road","elementType":"labels.text.fill","stylers":[{"color":"#696969"}]},{"featureType":"administrative","elementType":"labels.text.fill","stylers":[{"visibility":"on"},{"color":"#737373"}]},{"featureType":"poi","elementType":"labels.icon","stylers":[{"visibility":"off"}]},{"featureType":"poi","elementType":"labels","stylers":[{"visibility":"off"}]},{"featureType":"road.arterial","elementType":"geometry.stroke","stylers":[{"color":"#d6d6d6"}]},{"featureType":"road","elementType":"labels.icon","stylers":[{"visibility":"off"}]},{},{"featureType":"poi","elementType":"geometry.fill","stylers":[{"color":"#dadada"}]}]';
			break;

		case 'grey':

			$skin = '// Grey Scale
								 var grey_styles = [ 
										 { "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "stylers": [ { "visibility": "on" } ] 
									 },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "poi.medical", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi.medical", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "color": "#cccccc" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#cecece" } ] 
									 },{ "featureType": "road.local", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#808080" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#808080" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#fdfdfd" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#d2d2d2" } ]
									 } 
								 ];';

			break;

		case 'bw':

			$skin = '// Black & White
						 var bw_styles = [ 
										 { "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill",  "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#cecece" } ] 
									 },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "visibility": "off" } ]
									 } 
								 ];';

			break;

		case 'night':

			$skin = '// Night
						 var night_styles = [ 
									 { "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, {  "hue": "#0008ff" }, { "lightness": -75 }, { "saturation": 10 } ]
									 },{ "elementType": "geometry.stroke", "stylers": [ { "color": "#1f1d45" } ]
									 },{ "featureType": "landscape.natural", "stylers": [ { "color": "#1f1d45" } ]
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#01001f" } ] 
									 },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#e7e8ec" } ]
									 },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#151348" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#f7fdd9" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#01001f" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#316694" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#1a153d" } ]
									 
									 } 
								 ];';

			break;

		case 'night_light':

			$skin = '// Night Light
								 var night_light_styles = [ 
										 {"elementType": "geometry", "stylers": [ { "visibility": "on" }, { "hue": "#232a57" } ]
									 },{ "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "elementType": "geometry.fill", "stylers": [ { "hue": "#0033ff" }, { "saturation": 13 }, { "lightness":-77 } ]
									 },{ "featureType": "landscape", "elementType": "geometry.stroke", "stylers": [ { "color": "#4657ab" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ] 
									 },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#d2cfe3" } ]
									 },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ff9910" } ] 
									 },{ "featureType": "road.local", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#4657ab" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#232a57" } ]
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#232a57" } ]
									 },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 } 
								 ];';

			break;

		case 'retro':

			$skin = '// Retro
									var retro_styles = [ 
									 { "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#eee8ce" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#b8cec9" } ] 
									 },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "off" }, { "color": "#ffffff" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#d3cdab" } ]
									 },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#ced09d" } ]
									 },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 } 
								 ];';

			break;

		case 'papiro':

			$skin = '// Papiro
								 var papiro_styles = [ 
										 {"elementType": "geometry", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
									 },{ "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "poi.park", "elementType": "geometry.fill",  "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
									 },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
									 },{ "featureType": "landscape", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ] 
									 },{ "featureType": "landscape", "elementType": "geometry.stroke", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ] 
									 },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#a77637" } ] 
									 },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ]
									 },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ]
									 },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
									 },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#a5630f" } ] 
									 },{ "featureType": "road.highway", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ] 
									 },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "visibility": "off" } ]
									 },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
									 } 
								 ];';

		case 'bwater':

			$skin = '// Blue Water
								 var bwater_styles = [
									{
											"featureType": "water",
											"stylers": [
													{
															"color": "#46bcec"
													},
													{
															"visibility": "on"
													}
											]
									},
									{
											"featureType": "landscape",
											"stylers": [
													{
															"color": "#f2f2f2"
													}
											]
									},
									{
											"featureType": "road",
											"stylers": [
													{
															"saturation": -100
													},
													{
															"lightness": 45
													}
											]
									},
									{
											"featureType": "road.highway",
											"stylers": [
													{
															"visibility": "simplified"
													}
											]
									},
									{
											"featureType": "road.arterial",
											"elementType": "labels.icon",
											"stylers": [
													{
															"visibility": "off"
													}
											]
									},
									{
											"featureType": "administrative",
											"elementType": "labels.text.fill",
											"stylers": [
													{
															"color": "#444444"
													}
											]
									},
									{
											"featureType": "transit",
											"stylers": [
													{
															"visibility": "off"
													}
											]
									},
									{
											"featureType": "poi",
											"stylers": [
													{
															"visibility": "off"
													}
											]
									}
							];';

			break;

		default:
			return ;
			break;
	}

	return $skin;
}