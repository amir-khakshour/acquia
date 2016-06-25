<?php

/**
 * Load resource
 */
function rev_slider_load_resources($section = 'slider') {
	switch($section) {
	
		default:
		case 'slider':
			drupal_add_library('rev_slider', 'revolutionslider');
			break;	
		
		case 'admin_slider':
			acquia_include('utility');
			acquia_load_resources('admin');
			include_once drupal_get_path('module', 'media') . '/wysiwyg_plugins/media.inc';
			media_include_browser_js();
			drupal_add_library('system', 'ui');
			drupal_add_library('system', 'farbtastic');
			drupal_add_library('system', 'ui.sortable');
			drupal_add_library('system', 'ui.draggable');
			drupal_add_library('system', 'ui.menu');
			drupal_add_library('system', 'ui.position');
			drupal_add_library('system', 'ui.button');
			drupal_add_library('system', 'ui.dialog');
			drupal_add_library('system', 'ui.autocomplete');
			drupal_add_library('system', 'ui.resizable');
			drupal_add_library('ac_slider', 'acquia_slider.admin');
			drupal_add_library('rev_slider', 'revolutionslider.admin');
			break;
	}
}

/**
 * 
 * get array of slide classes.
 */
function rev_slider_get_caption_array($path = "", $startText = "",$endText=""){
	$arrClasses = &drupal_static(__FUNCTION__, array());
	
	if (count($arrClasses)) {
		return $arrClasses;
	}
	
	if (!file_exists($path)) {
		return false;
	}
	
	$content = file_get_contents($path);
	
	//trim from top
	if(!empty($startText)){
		$posStart = strpos($content, $startText);
		if($posStart !== false)
			$content = substr($content, $posStart,strlen($content)-$posStart);
	}
	
	//trim from bottom
	if(!empty($endText)){
		$posEnd = strpos($content, $endText);
		if($posEnd !== false)
			$content = substr($content,0,$posEnd);
	}
	
	//get styles
	$lines = explode("\n",$content);
	$arrClasses = array();
	foreach($lines as $key=>$line){
		$line = trim($line);
		
		if(strpos($line, "{") === false)
			continue;

		//skip unnessasary links
		if(strpos($line, ".caption a") !== false)
			continue;
			
		if(strpos($line, ".tp-caption a") !== false)
			continue;
			
		//get style out of the line
		$class = str_replace("{", "", $line);
		$class = trim($class);
		
		//skip captions like this: .tp-caption.imageclass img
		if(strpos($class," ") !== false)
			continue;
		
		$class = str_replace(".caption.", ".", $class);
		$class = str_replace(".tp-caption.", ".", $class);
		
		$class = str_replace(".", "", $class);
		$class = trim($class);
		$arrWords = explode(" ", $class);
		$class = $arrWords[count($arrWords)-1];
		$class = trim($class);
		
		$arrClasses[] = $class;	
	}
	
	return($arrClasses);
}


/**
 * Returning string format of given data array
 */
function rev_slider_getNextTime($sublayers, $suid){
	if (!is_array($sublayers) || count($sublayers) < 1) {
		return false;
	}
	
	$maxTime = 0;

	//get max time
	foreach ($sublayers as $_suid => $sublayer){
	
		if ($_suid == $suid) 
			break;
			
		$sublayerTime = isset($sublayer['start']) ? (int)$sublayer['start'] :0;
		if($sublayerTime > $maxTime) {
				$maxTime = $sublayerTime;
		}
		
	}
	return $maxTime == 0 ? 500 : (int)($maxTime + 500);
}


function rev_slider_get_thumb($fid, $width = 100, $height = 50) {
	if ($thumb = image_load($url)) {
		$thumb = image_scale_and_crop($thumb, $width, $height);
		print '<img src="'.$thumb.'">';
	} 
	else {
		print 'error';
	}
}

/**
 * prepare revolution slider settings before rendering slider
 */
function rev_slider_get_slider_prop($settings) {
	
	$prop = array();
	
  if (empty($settings)) {
		return;// @todo fallback to default settings
  }

	// prepare profile settings
	/*if (!empty($settings['start_with_slide'])){
		if (is_numeric($settings['start_with_slide'])) {
			$settings['start_with_slide'] = (int)$settings['start_with_slide'] - 1;
			if ($settings['start_with_slide'] < 0) {
				$settings['start_with_slide'] = 0;
			}else if ($settings['start_with_slide'] >=$num_slides) {
				$settings['start_with_slide'] = 0;
			}
		} else {
			$settings['start_with_slide'] = 0;
		}
	}
// set hide navigation after
	if(!is_numeric($settings['hide_thumbs'])){
		$settings['hideThumbs'] = '0';
	}
	else{
		$settings['hide_thumbs'] = (int)$settings['hide_thumbs'];
		if($settings['hide_thumbs'] < 10) {
			$settings['hide_thumbs'] = 10;
		}
	}
	
	if($settings['navigaion_always_on'] == true){ 
		$settings['hide_thumbs'] = '0';
	}
	
	$settings['fullWidth'] = $settings['slider_type'] == 'fullwidth' ? 'on' : 'off';
	$settings['fullScreen'] = 'off';
	
	if ($settings['slider_type'] == "fullscreen"){
		$settings['fullWidth'] = 'on';
		$settings['fullscreen'] = 'on';
	}*/	
	
	
	//edit html before slider
	$prop["htmlBeforeSlider"] = "";
	if ($settings["load_googlefont"] == "on" && !empty($settings["google_font"])) {
		$googleFont = $settings["google_font"];
		$prop["htmlBeforeSlider"] = "<link rel='stylesheet' id='rev-google-font' href='http://fonts.googleapis.com/css?family={$googleFont}' type='text/css' media='all' />";
	}

	
	// Add the attributes to the settings array.
  $prop['wrapper'] = array();
  $prop['container'] = array();
	
	
	// IDs
  $containerID = &drupal_static('rev_slider_container_id', 0);
  $prop['container']['attributes']['id'] = isset($settings['id']) && !empty($settings['id']) ? $settings['id'] : 'acquia_rev_slider-' . $containerID++;	
  $prop['wrapper']['attributes']['id'] = $prop['container']['attributes']['id'] . '_wrapper';
	
	// Set wrapper and container class:
	$prop['wrapper']['attributes']['class'] = 'rev_slider_wrapper';
	$prop['container']['attributes']['class'] = 'rev_slider';
	
	
	// Add Style
	$prop['wrapper']['attributes']['style'] = '';
	$prop['container']['attributes']['style'] = "display: none;";	

	if ($settings['slider_type'] != 'fullscreen') {
		// Set position:
		switch ($settings['position']) {
			case "center":
			default:
				$prop['wrapper']['attributes']['style'] .= 'margin: 0px auto;';
				break;
				
			case "left":
				$prop['wrapper']['attributes']['style'] .= 'float: left;';
				break;
			
			case "right":
				$prop['wrapper']['attributes']['style'] .= 'float: right;';
				break;
		}

		
		// Set marginsS:
		if($settings['position'] != 'center'){
			$prop['wrapper']['attributes']['style'] .= 'margin-left: ' .$settings['margin_left']. 'px;';
			$prop['wrapper']['attributes']['style'] .= 'margin-right: ' .$settings['margin_right']. 'px;';
		}
		
		$prop['wrapper']['attributes']['style'] .= 'margin-top: '.$settings['margin_top']. 'px;';
		$prop['wrapper']['attributes']['style'] .= 'margin-bottom: '.$settings['margin_bottom']. 'px;';
	}

	
	// add background color
	$backgrondColor = trim($settings['background_color']);
	if(!empty($backgrondColor)) {
		$prop['wrapper']['attributes']['style'] .= 'background-color:' .$backgrondColor. ';';
	}
	

	// set padding			
	$prop['wrapper']['attributes']['style'] .= 'padding: ' .$settings['padding']. 'px;';

	
	// add background image
	if($settings['show_background_image'] == 'on'){		
		$bg = $settings['background_image'];
		$prop['container']['attributes']['style'] .= "background-image: url($bg);background-repeat: no-repeat;";
	}
	
	
	//set height and width:
	$bannerWidth = $settings['width'];
	$bannerHeight = $settings['height'];
	
	$prop['putResponsiveStyles'] = false;
	switch ($settings['slider_type']) {
		default:
		case 'fixed':
			$prop['container']['attributes']['style'] .= "height:{$bannerHeight}px;width:{$bannerWidth}px;";
			$prop['wrapper']['attributes']['style'] .= "height:{$bannerHeight}px;width:{$bannerWidth}px;";
			break;
		
		case 'responsitive':
			$prop['putResponsiveStyles'] = true;
			break;
			
		case 'fullwidth':
			$prop['container']['attributes']['class'] .= ' fullwidthabanner';
			$prop['container']['attributes']['style'] .= 'max-height:'.$bannerHeight.'px;height:{'.$bannerHeight.';';
			
			$prop['wrapper']['attributes']['class']   .= ' fullwidthbanner-container';
			$prop['wrapper']['attributes']['style']   .= 'max-height:{'.$bannerHeight.'px;';						
			break;
		
		case 'fullscreen':
			$prop['wrapper']['attributes']['class']   .= ' fullscreen-container';
			$prop['container']['attributes']['class'] .= ' fullscreenbanner';
			break;
	}

	// Timebar
	$prop['htmlTimerBar'] = '';
	switch ($settings['show_timerbar']) {
		case 'top':
			$prop['htmlTimerBar'] = '<div class="tp-bannertimer"></div>';
		break;
		case 'bottom':
			$prop['htmlTimerBar'] = '<div class="tp-bannertimer tp-bottom"></div>';
		break;
	}
	
	// Responsive Styles
	if ($prop['putResponsiveStyles'] == true) {
		$prop['responsiveStyles'] = '<style type="text/css">'
		. '#' .$prop['wrapper']['attributes']['id']. ', #' .$prop['container']['attributes']['id']
		. '{ width:' .$bannerWidth. '; height:'.$bannerHeight.';}';
		
		foreach (rev_slider_getResponsitiveValues($settings) as $item) {
			$strMaxWidth = $item["maxWidth"] >= 0 ? 'and (max-width: ' .$item["maxWidth"]. 'px)' : '';
			$prop['responsiveStyles'] .= '@media only screen and (min-width: ' .$item["minWidth"]. 'px) ' .$strMaxWidth. '{'
			. '#' .$prop['wrapper']['attributes']['id']. ', #' .$prop['container']['attributes']['id']. '{ width:' .$item["sliderWidth"]. 'px; height:' .$item["sliderHeight"]. 'px;}'
			. '}';
		}		
		$prop['responsiveStyles'] .= "</style>";
	}
	
	return $prop;
}


/*
 * fill the responsitive slider values for further output
 */
function rev_slider_getResponsitiveValues($settings){

	$sliderWidth = $settings['width'];
	$sliderHeight = $settings['height'];
	
	$percent = $sliderHeight / $sliderWidth;
	
	$w1 = (int) $settings["responsitive_w1"];
	$w2 = (int) $settings["responsitive_w2"];
	$w3 = (int) $settings["responsitive_w3"];
	$w4 = (int) $settings["responsitive_w4"];
	$w5 = (int) $settings["responsitive_w5"];
	$w6 = (int) $settings["responsitive_w6"];
	
	$sw1 = (int) $settings["responsitive_sw1"];
	$sw2 = (int) $settings["responsitive_sw2"];
	$sw3 = (int) $settings["responsitive_sw3"];
	$sw4 = (int) $settings["responsitive_sw4"];
	$sw5 = (int) $settings["responsitive_sw5"];
	$sw6 = (int) $settings["responsitive_sw6"];
	
	$arrItems = array();
	
	//add main item:
	$arr = array();				
	$arr["maxWidth"] = -1;
	$arr["minWidth"] = $w1;
	$arr["sliderWidth"] = $sliderWidth;
	$arr["sliderHeight"] = $sliderHeight;
	$arrItems[] = $arr;
	
	//add item 1:
	if(empty($w1))
		return($arrItems);
		
	$arr = array();				
	$arr["maxWidth"] = $w1-1;
	$arr["minWidth"] = $w2;
	$arr["sliderWidth"] = $sw1;
	$arr["sliderHeight"] = floor($sw1 * $percent);
	$arrItems[] = $arr;
	
	//add item 2:
	if(empty($w2))
		return($arrItems);
	
	$arr["maxWidth"] = $w2-1;
	$arr["minWidth"] = $w3;
	$arr["sliderWidth"] = $sw2;
	$arr["sliderHeight"] = floor($sw2 * $percent);
	$arrItems[] = $arr;
	
	//add item 3:
	if(empty($w3))
		return($arrItems);
	
	$arr["maxWidth"] = $w3-1;
	$arr["minWidth"] = $w4;
	$arr["sliderWidth"] = $sw3;
	$arr["sliderHeight"] = floor($sw3 * $percent);
	$arrItems[] = $arr;
	
	//add item 4:
	if(empty($w4))
		return($arrItems);
	
	$arr["maxWidth"] = $w4-1;
	$arr["minWidth"] = $w5;
	$arr["sliderWidth"] = $sw4;
	$arr["sliderHeight"] = floor($sw4 * $percent);
	$arrItems[] = $arr;

	//add item 5:
	if(empty($w5))
		return($arrItems);
	
	$arr["maxWidth"] = $w5-1;
	$arr["minWidth"] = $w6;
	$arr["sliderWidth"] = $sw5;
	$arr["sliderHeight"] = floor($sw5 * $percent);
	$arrItems[] = $arr;
	
	//add item 6:
	if(empty($w6))
		return($arrItems);
	
	$arr["maxWidth"] = $w6-1;
	$arr["minWidth"] = 0;
	$arr["sliderWidth"] = $sw6;
	$arr["sliderHeight"] = floor($sw6 * $percent);
	$arrItems[] = $arr;
	
	return($arrItems);
}



/**
 * get video layer object from video data
 */
function rev_slider_get_videoArrLayer($videoData){
	
	if (!$videoData) {
		return false;
	}
	
	$arrLayer = array(
		'type' => "video",
		'style' => "",
		'video_type' => $videoData["video_type"],
		'video_width'=> $videoData["width"],
		'video_height' => $videoData["height"],
		'video_data' => $videoData
	);
	
	if($arrLayer["video_type"] == "youtube" || $arrLayer["video_type"] == "vimeo"){
		$arrLayer["video_id"] = $videoData["id"];
		$arrLayer["video_title"] = $videoData["title"];
		$arrLayer["video_image_url"] = $videoData["thumb_medium"]["url"];
		$arrLayer["video_args"] = $videoData["args"];
	}
	
	//set sortbox text
	switch($arrLayer["video_type"]){			
		case "youtube":
			$arrLayer["text"] = "Youtube: " + $videoData["title"];
		break;
		case "vimeo":
			$arrLayer["text"] = "Vimeo: " + $videoData["title"];
		break;
		case "html5":
			$arrLayer["text"] = "Html5 Video";
			$arrLayer["video_title"] = $arrLayer["text"];
			$arrLayer["video_image_url"] = "";
			$arrLayer["video_args"] = $videoData["args"];
			if($videoData["urlPoster"] != "")
				$arrLayer["video_image_url"] = $videoData["urlPoster"];
				
		break;
	}
	
	return $arrLayer;
}
 
/**
 * get html5 layer html from data
 */
function rev_slider_get_Html5LayerHtml($data){
	if (empty($data)) {
		drupal_set_message("Given HTML5 video data is invalid.");
		return false;
	}
	
	$urlPoster = $data["urlPoster"];
	$urlMp4 = $data["urlMp4"];
	$urlWebm = $data["urlWebm"];
	$urlOgv = $data["urlOgv"];
	$width = $data["width"];
	$height = $data["height"];
	
	$fullwidth = $data["fullwidth"] == "true" ? true : false;
	
	if($fullwidth == true){
		$width = "100%";
		$height = "100%";
	}
	
	$htmlPoster = "";
	if(!empty($urlPoster))
		$htmlPoster = "poster='{$urlPoster}'";
		
	$htmlMp4 = "";
	if(!empty($urlMp4))
		$htmlMp4 = "<source src='{$urlMp4}' type='video/mp4' />";

	$htmlWebm = "";
	if(!empty($urlWebm))
		$htmlWebm = "<source src='{$urlWebm}' type='video/webm' />";
		
	$htmlOgv = "";
	if(!empty($urlOgv))
		$htmlOgv = "<source src='{$urlOgv}' type='video/ogg' />";
			
	$html =	"<video class=\"video-js vjs-default-skin\" controls preload=\"none\" width=\"{$width}\" height=\"{$height}\" \n";
		$html .=  $htmlPoster ." data-setup=\"{}\"> \n";
			$html .=  $htmlMp4."\n";
			$html .=  $htmlWebm."\n";
			$html .=  $htmlOgv."\n";
	$html .=  "</video>\n";
	
	return($html);
}

/**
 * Slider Layouts
 */
function rev_slider_layouts() {
	return array('fixed' => t('Fixed'),
	'custom' => t('Custom'),
	'auto-responsive' => t('Auto Responsive'),
	'full-screen' => t('Full Screen)'),
	);
}
 
/**
 * 
 * get transition array
 */
function rev_slider_transitions(){
	$transitions = array(
					"notselectable1"=>"RANDOM TRANSITIONS",					
					"random-static"=>"Random Flat",
					"random-premium"=>"Random Premium",					
					"random"=>"Random Flat and Premium",
					"notselectable2"=>"SLIDING TRANSITIONS",
					"slideup"=>"Slide To Top",
					"slidedown"=>"Slide To Bottom",
					"slideright"=>"Slide To Right",
					"slideleft"=>"Slide To Left",
					"slidehorizontal"=>"Slide Horizontal (depending on Next/Previous)",
					"slidevertical"=>"Slide Vertical (depending on Next/Previous)",
					"boxslide"=>"Slide Boxes",
					"slotslide-horizontal"=>"Slide Slots Horizontal",
					"slotslide-vertical"=>"Slide Slots Vertical",					
					"notselectable3"=>"FADE TRANSITIONS",
					"notransition"=>"No Transition",
					"fade"=>"Fade",
					"boxfade"=>"Fade Boxes",
					"slotfade-horizontal"=>"Fade Slots Horizontal",
					"slotfade-vertical"=>"Fade Slots Vertical",
					"fadefromright"=>"Fade and Slide from Right",
					"fadefromleft"=>"Fade and Slide from Left",
					"fadefromtop"=>"Fade and Slide from Top",
					"fadefrombottom"=>"Fade and Slide from Bottom",
					"fadetoleftfadefromright"=>"Fade To Left and Fade From Right",
					"fadetorightfadefromleft"=>"Fade To Right and Fade From Left",
					"fadetotopfadefrombottom"=>"Fade To Top and Fade From Bottom",
					"fadetobottomfadefromtop"=>"Fade To Bottom and Fade From Top",
					"notselectable4"=>"PARALLAX TRANSITIONS",
					"parallaxtoright"=>"Parallax to Right",
					"parallaxtoleft"=>"Parallax to Left",
					"parallaxtotop"=>"Parallax to Top",
					"parallaxtobottom"=>"Parallax to Bottom",
					"notselectable5"=>"ZOOM TRANSITIONS",					
					"scaledownfromright"=>"Zoom Out and Fade From Right",
					"scaledownfromleft"=>"Zoom Out and Fade From Left",
					"scaledownfromtop"=>"Zoom Out and Fade From Top",
					"scaledownfrombottom"=>"Zoom Out and Fade From Bottom",				
					"zoomout"=>"ZoomOut",
					"zoomin"=>"ZoomIn",					
					"slotzoom-horizontal"=>"Zoom Slots Horizontal",
					"slotzoom-vertical"=>"Zoom Slots Vertical",					
					"notselectable6"=>"CURTAIN TRANSITIONS",					
					"curtain-1"=>"Curtain from Left",
					"curtain-2"=>"Curtain from Right",
					"curtain-3"=>"Curtain from Middle",					
					"notselectable7"=>"PREMIUM TRANSITIONS",					
					"3dcurtain-horizontal"=>"3D Curtain Horizontal",
					"3dcurtain-vertical"=>"3D Curtain Vertical",
					"cube"=>"Cube Vertical",
					"cube-horizontal"=>"Cube Horizontal",
					"incube"=>"In Cube Vertical",
					"incube-horizontal"=>"In Cube Horizontal",
					"turnoff"=>"TurnOff Horizontal",
					"turnoff-vertical"=>"TurnOff Vertical",
					"papercut"=>"Paper Cut",
					"flyin"=>"Fly In"			
	);

	return($transitions);
}