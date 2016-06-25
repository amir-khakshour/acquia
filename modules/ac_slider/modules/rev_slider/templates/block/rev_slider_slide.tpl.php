<?php
$sliderType = $settings["slider_type"];

$thumbWidth = $settings["thumb_width"];
$thumbHeight = $settings["thumb_height"];

$slideWidth = $settings["width"];
$slideHeight = $settings["height"];

$navigationType = $settings["navigaion_type"]; 
$isThumbsActive = ($navigationType == "thumb" || $navigationType == "both") ? true : false;

// Transparent Image URL
$urlImageTransparent = file_create_url(REVSLIDER_PLUGIN_PATH ."/images/transparent.png", array('absolute' => true));

$transition = $slide["properties"]["slide_transitions"];
if (empty($transition)) {
  $transition = 'fade';
}

$slotAmount = $slide["properties"]["slot_amount"];

if (isset($slide['properties']['background_fid']) && !empty($slide['properties']['background_fid'])) {
	$file = file_load($slide['properties']['background_fid']);
	if (isset($file->uri)) {
		$slide["properties"]["background"] = file_create_url($file->uri);
	}
}
$urlSlideImage = $slide["properties"]["background"];

if (empty($urlSlideImage)) {
	$urlSlideImage = $urlImageTransparent;
	$bgType = 'transparent';
}else{
	$bgType = 'image';
}

//get thumb url
$htmlThumb = "";
if($isThumbsActive == true){

	if (isset($slider['properties']['thumbnail_fid']) && !empty($slider['properties']['thumbnail_fid'])) {
		$file = file_load($slider['properties']['thumbnail_fid']);
		if (isset($file->uri)) {
			$slide["properties"]["thumbnail"] = file_create_url($file->uri);
		}
	}
	
  if (isset($slide["properties"]["thumbnail"]) && $slide["properties"]["thumbnail"] !='') {
    $urlThumb = $slide["properties"]["thumbnail"];
  }else if (!empty($urlSlideImage)) {
    $urlThumb = $urlSlideImage;
  }else {
    $urlThumb = $urlImageTransparent;
  }

	$htmlThumb = 'data-thumb="'.$urlThumb.'" ';
}

//get link
$htmlLink = "";
$enableLink = isset($slide["properties"]["enable_link"]) ? $slide["properties"]["enable_link"] : 'off' ;
if($enableLink == "on" && !empty($slide["properties"]["link"])){
	$linkType = $slide["properties"]["link_type"];
	switch($linkType){
		
		//---- normal link
		
		default:		
		case "regular":
			$link = $slide["properties"]["link"];
			$linkOpenIn = $slide["properties"]["link_open_in"];
			$htmlLink = "data-link=\"$link\" data-target=\"$linkOpenIn\" ";	
		break;		
		
		//---- link to slide
		
		case "slide":
			$slideLink = $slide["properties"]["link"];
			if(!empty($slideLink) && $slideLink != "nothing" && (preg_match('/^[0-9]*$/i', $slideLink) || in_array($slideLink, array('next', 'prev')))){
				$htmlLink = "data-link=\"slide\" data-linktoslide=\"$slideLink\" ";
			}
		break;
	}
	
	//set link position:
	$linkPos = $slide["properties"]["link_pos"];
	if($linkPos == "back")
		$htmlLink .= ' data-slideindex="back"';	
}

//set delay
$htmlDelay = "";
$delay = $slide["properties"]["delay"];
if(!empty($delay) && is_numeric($delay))
	$htmlDelay = "data-delay=\"$delay\" ";

//get duration
$htmlDuration = "";
$duration = $slide["properties"]["transition_duration"];
if(!empty($duration) && is_numeric($duration))
	$htmlDuration = "data-masterspeed=\"$duration\" ";

//get rotation
$htmlRotation = "";
$rotation = $slide["properties"]["transition_rotation"];
if(!empty($rotation)){
	$rotation = (int)$rotation;
	if($rotation != 0){
		if($rotation > 720 && $rotation != 999)
			$rotation = 720;
		if($rotation < -720)
			$rotation = -720;
	}
	$htmlRotation = "data-rotate=\"$rotation\" ";
}

//$fullWidthVideoData = $this->getSlideFullWidthVideoData($slide);

//set full width centering.
$htmlImageCentering = "";
$fullWidthCentering = $slide["properties"]["fullwidth_centering"];
if($sliderType == "fullwidth" && $fullWidthCentering == "on")
	$htmlImageCentering = ' data-fullwidthcentering="on"';
	
//set first slide transition
$htmlFirstTrans = "";
$startWithSlide = $settings["start_with_slide"]-1;


if($index == $startWithSlide){

	$firstTransActive = $settings["first_transition_active"];
	if($firstTransActive == "on"){
		
		$firstTransition = $settings["first_transition_type"];						
		$htmlFirstTrans .= " data-fstransition=\"$firstTransition\"";
		
		$firstDuration = $settings["first_transition_duration"];
		if(!empty($firstDuration) && is_numeric($firstDuration))
			$htmlFirstTrans .= " data-fsmasterspeed=\"$firstDuration\"";
			
		$firstSlotAmount = $settings["first_transition_slot_amount"];
		if(!empty($firstSlotAmount) && is_numeric($firstSlotAmount))						
		$htmlFirstTrans .= " data-fsslotamount=\"$firstSlotAmount\"";
			
	}
}//first trans

$htmlParams = $htmlDuration.$htmlLink.$htmlThumb.$htmlDelay.$htmlRotation.$htmlFirstTrans;


$styleImage = "";

if (!empty($slide["properties"]["bgColor"])) {
	$slideBGColor = $slide["properties"]["bgColor"];
	$styleImage = "style='background-color:{$slideBGColor}'";
}
//additional params
$imageAddParams = "";
$lazyLoad = $settings["lazy_load"];
if($lazyLoad == "on"){
	$imageAddParams .= "data-lazyload=\"$urlSlideImage\"";
	$urlSlideImage = REVSLIDER_PLUGIN_PATH ."/images/dummy.png";
}

$bgPosition = ac_slider_getParam("bg_position", "center top", $slide["properties"]);
$bgPositionX = intval(ac_slider_getParam("bg_position_x", "0", $slide["properties"]));
$bgPositionY = intval(ac_slider_getParam("bg_position_y", "0", $slide["properties"]));

if($bgPosition == 'percentage'){
	$imageAddParams .= ' data-bgposition='.$bgPositionX.'% '.$bgPositionY.'%';
}else{
	$imageAddParams .= ' data-bgposition='.$bgPosition.'';
}
//check for kenburn & pan zoom
$kenburn_effect = ac_slider_getParam("kenburn_effect","false", $slide["properties"]);

//$kb_rotation_start = intval($slide->getParam("kb_rotation_start","0"));
//$kb_rotation_end = intval($slide->getParam("kb_rotation_end","0"));
$kb_duration = (int)ac_slider_getParam("kb_duration", 9000, $slide["properties"]);
$kb_ease = ac_slider_getParam("kb_easing", "Linear.easeNone", $slide["properties"]);
$kb_start_fit = ac_slider_getParam("kb_start_fit", "100", $slide["properties"]);
$kb_end_fit = ac_slider_getParam("kb_end_fit", "100", $slide["properties"]);

$kb_pz = '';
if($kenburn_effect == 'true' && ($bgType == 'image')){
	$kb_pz.= ' data-kenburns="on"';
	//$kb_pz.= ' data-rotationstart="'.$kb_rotation_start.'"';
	//$kb_pz.= ' data-rotationend="'.$kb_rotation_end.'"';
	$kb_pz.= ' data-duration="'.$kb_duration.'"';
	$kb_pz.= ' data-ease='.$kb_ease;
	$kb_pz.= ' data-bgfit="'.$kb_start_fit.'"';
	$kb_pz.= ' data-bgfitend="'.$kb_end_fit.'"';
	
	$bgEndPosition = ac_slider_getParam("bg_end_position","center top", $slide["properties"]);
	$bgEndPositionX = (int)ac_slider_getParam("bg_end_position_x","0", $slide["properties"]);
	$bgEndPositionY = (int)ac_slider_getParam("bg_end_position_y","0", $slide["properties"]);
	
	if($bgEndPosition == 'percentage'){
		$kb_pz.= ' data-bgpositionend="'.$bgEndPositionX.'% '.$bgEndPositionY.'%"';
	}else{
		$kb_pz.= ' data-bgpositionend='.$bgEndPosition.'';
	}
}

//Html
?>
<li data-transition="<?php echo $transition?>" data-slotamount="<?php echo $slotAmount?>" <?php echo $htmlParams?>>
	<img src="<?php echo $urlSlideImage?>" <?php echo $styleImage?> alt="" <?php echo $imageAddParams .$kb_pz?>>
	<?php print theme('rev_slider_sublayers', array('sublayers' => $slide['sublayers'], 'settings' => $settings)); ?>
</li>


