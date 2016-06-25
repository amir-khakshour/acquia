<?php
if (isset($sublayer["skip"]) && $sublayer["skip"] == "on") {
  return;
}

$type = $sublayer["type"];

//set if video full screen
$isFullWidthVideo = false;
if($type == "video"){
  $videoData = $sublayer["video_data"];
  if(!empty($videoData)){
    $videoData = (array)drupal_json_decode($videoData);
    $isFullWidthVideo = $videoData["fullwidth"] ;
  }else
    $videoData = array();
}

$class = $sublayer["class"];
$animation = $sublayer["animation"];

//set output class:
$outputClass = "tp-caption ". trim($class);
  $outputClass = trim($outputClass) . " ";
  
$outputClass .= trim($animation);

$left = $sublayer["left"];
$top = $sublayer["top"];
$speed = $sublayer["speed"];
$time = $sublayer["start"];
$easing = $sublayer["easing"];
$randomRotate = isset($sublayer["transition_rotation"]) && (int)$sublayer["transition_rotation"] == 999 ? "true" : "false";

$text = $sublayer["html"];

$htmlVideoAutoplay = "";
$htmlVideoNextSlide = "";

$layerHTMLParams = "";

// ID
if(!empty($sublayer['id'])) {
  $sublayerID = ' id="'.$sublayer['id'].'"';
} else {
  $sublayerID = '';
}

// Title
if(!empty($sublayer['title'])) {
  $sublayerTitle = ' title="'.$sublayer['title'].'"';
} else {
  $sublayerTitle = '';
}

// Alt
if(!empty($sublayer['alt'])) {
  $sublayerAlt = ' alt="'.$sublayer['alt'].'"';
} else {
  $sublayerAlt = '';
}

// Rel
if(!empty($sublayer['rel'])) {
  $sublayerRel = ' rel="'.$sublayer['rel'].'"';
} else {
  $sublayerRel = '';
}

$sublayerStyle ='';
// WordWrap
if(!isset($sublayer['wordwrap'])) {
  $sublayerStyle .= ' white-space: nowrap;';
}

// Custom style
if(!empty($sublayer['style'])) {
  $sublayerStyle .= preg_replace('/\s\s+/', ' ', stripslashes($sublayer['style']));
}

// Build style settings if any
if(!empty($sublayer['styles'])) {

  // Get custom style settings
  $styles = json_decode(stripslashes($sublayer['styles']), true);

  // Build custom style string
  foreach($styles as $key => $val) {
    if(is_numeric($val)) {
      $sublayerStyle .= ''.$key.': '.ac_check_unit($val).'; ';
    } else {
      $sublayerStyle .= ''.$key.': '.$val.'; ';
    }
  }
}

if (!empty($sublayerStyle)) {
  $sublayerStyle = ' style="'.$sublayerStyle.'"';
}

$layerHTMLParams = $sublayerID.$sublayerTitle.$sublayerAlt.$sublayerRel.$sublayerStyle;
if (!empty($layerHTMLParams)) {
  $layerHTMLParams = ' '.$layerHTMLParams;
}

//set html:
$html = "";
$tag = "div";
switch($type){
  case "img":
    if (isset($sublayer['image_fid']) && ! empty ( $sublayer ['image_fid'] )) {
        $file = file_load($sublayer['image_fid']);
        if (isset($file->uri)) {
          $sublayer ['image'] = file_create_url($file->uri);
        }
    }
    $urlImage = $sublayer["image"];
    $html = '<img src="'.$urlImage.'" alt=""'.$layerHTMLParams.'>';
    $imageLink = $sublayer["url"];
    if(!empty($imageLink)){
      $target = $sublayer["target"];
      $html = '<a href="'.$imageLink.'"'.$target.'>'.$html.'</a>';
    }
  break;
  case "video":
    if (empty($videoData))
      break;

    $videoArr = rev_slider_get_videoArrLayer($videoData);
    $videoType = trim($videoArr["video_type"]);
    $videoID = isset($videoArr["video_id"]) ? trim($videoArr["video_id"]) : '';
    $videoWidth = trim($videoArr["video_width"]);
    $videoHeight = trim($videoArr["video_height"]);	
    $videoArgs = trim($videoArr["video_args"]);
    
    if($isFullWidthVideo == true){
      $videoWidth = "100%";
      $videoHeight = "100%";
    }
    
    switch($videoType){
      case "youtube":
        if(empty($videoArgs))
          $videoArgs = DEFAULT_YOUTUBE_ARGUMENTS;
        $html = "<iframe src='http://www.youtube.com/embed/{$videoID}?{$videoArgs}' width='{$videoWidth}' height='{$videoHeight}' style='width:{$videoWidth}px;height:{$videoHeight}px;'></iframe>";
      break;
    
    
      case "vimeo":
        if(empty($videoArgs))
          $videoArgs = DEFAULT_VIMEO_ARGUMENTS;
        $html = "<iframe src='http://player.vimeo.com/video/{$videoID}?{$videoArgs}' width='{$videoWidth}' height='{$videoHeight}' style='width:{$videoWidth}px;height:{$videoHeight}px;'></iframe>";
      break;
    
    
      case "html5":
        $html = rev_slider_get_Html5LayerHtml($videoData);									
      break;
      default:
        drupal_set_message('Video type is invalid!');
      break;
    }
    
    //set video autoplay, with backward compatability
    if(array_key_exists("autoplay", $videoData))
      $videoAutoplay = $videoData["autoplay"];
    else	//backword compatability
      $videoAutoplay = false;

    if($videoAutoplay == true)
      $htmlVideoAutoplay = ' data-autoplay="true"';								
    
    $videoNextSlide = isset($videoData["nextslide"]) ? $videoData["nextslide"] : FALSE;
    
    if($videoNextSlide == true)
      $htmlVideoNextSlide = ' data-nextslideatend="true"';								
      
  break;

  
  default:
    $tag = $type;
    $html =check_markup($text, 'full_html');
  break;

}

//handle end transitions:
$endTime = trim($sublayer["endtime"]);
$htmlEnd = "";
if(!empty($endTime)){
  $htmlEnd = "data-end=\"$endTime\"";
  $endSpeed = trim($sublayer["endspeed"]);
  if(!empty($endSpeed))
     $htmlEnd .= " data-endspeed=\"$endSpeed\"";
     
  $endEasing = trim($sublayer["endeasing"]);
  if(!empty($endSpeed) && $endEasing != "nothing")
     $htmlEnd .= " data-endeasing=\"$endEasing\"";
  
  //add animation to class
  $endAnimation = trim($sublayer["endanimation"]);
  if(!empty($endAnimation) && $endAnimation != "auto")
    $outputClass .= " ".$endAnimation;	
}

//slide link
$htmlLink = "";
$slideLink = is_int($sublayer["url"]) || in_array($sublayer["url"], array("prev", "next")) ? $sublayer["url"] : false;
if($slideLink && !empty($slideLink)){
  $htmlLink = " data-linktoslide=\"$slideLink\"";
}

//scroll under the slider
/* @todo 
 if($slideLink == "scroll_under"){
  $outputClass .= " tp-scrollbelowslider";
  $scrollUnderOffset = UniteFunctionsRev::getVal($layer, "scrollunder_offset");
  if(!empty($scrollUnderOffset))
    $htmlLink .= " data-scrolloffset=\"{$scrollUnderOffset}\"";
}
*/		

$htmlParams = $htmlEnd.$htmlLink.$htmlVideoAutoplay.$htmlVideoNextSlide;
if ($type !='img' ) {
  $htmlParams .= $layerHTMLParams;
}

//set positioning options
$left = (int)str_replace(array("%", "px"), "", $left);
$top = (int)str_replace(array("%", "px"), "", $top);
$htmlPosX = "data-x=\"{$left}\" \n";
$htmlPosY = "data-y=\"{$top}\" ";
if($type == "div"){
  //add resizeme class
  if(isset($sublayer["resizeme"]) && $sublayer["resizeme"] == 'true')
    $outputClass .= ' tp-resizeme';
}
  
if($isFullWidthVideo == true)
  $outputClass = 'tp-caption fade fullscreenvideo';
?>
<<?php print $tag?> class="<?php echo $outputClass?>"
   <?php echo $htmlPosX?>
   <?php echo $htmlPosY?>
   data-speed="<?php echo $speed?>" 
   data-start="<?php echo $time?>" 
   data-easing="<?php echo $easing?>" <?php echo $htmlParams?> ><?php echo $html?>
</<?php print $tag?>>
