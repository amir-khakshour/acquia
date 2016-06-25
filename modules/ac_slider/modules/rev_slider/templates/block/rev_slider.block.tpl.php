<?php
/**
 * @file
 * Default output for a rev_slider object.
*/

if($prop['putResponsiveStyles']){
  print $prop['responsiveStyles'];
}
print $prop['htmlBeforeSlider'];
?>

<div<?php print drupal_attributes($prop['wrapper']['attributes'])?>>
	<div<?php print drupal_attributes($prop['container']['attributes'])?>>
			<?php print theme('rev_slider_slides', array('slides' => $slides, 'settings' => $settings))?>
			<?php print $prop['htmlTimerBar']?>
	</div>
</div>


<?php

$sliderType = $settings["slider_type"];
$optFullWidth = ($sliderType == "fullwidth") ? "on" : "off";

$optFullScreen = "off";
if($sliderType == "fullscreen"){
	$optFullWidth = "on";
	$optFullScreen = "on";
}

$noConflict = ac_slider_getParam("jquery_noconflict", "on", $settings);

//set thumb amount
$numSlides = count($slides);
$thumbAmount = (int)ac_slider_getParam("thumb_amount","5", $settings);
if($thumbAmount > $numSlides)
	$thumbAmount = $numSlides;
	

//get stop slider options
 $stopSlider = ac_slider_getParam("stop_slider","off", $settings);
 $stopAfterLoops = ac_slider_getParam("stop_after_loops","0", $settings);
 $stopAtSlide = ac_slider_getParam("stop_at_slide","2", $settings);
 
 if($stopSlider == "off"){
	 $stopAfterLoops = "-1";
	 $stopAtSlide = "-1";
 }

// set hide navigation after
$hideThumbs = ac_slider_getParam("hide_thumbs","200", $settings);
if(is_numeric($hideThumbs) == false)
	$hideThumbs = "0";
else{
	$hideThumbs = (int)$hideThumbs;
	if($hideThumbs < 10)
		$hideThumbs = 10;
}

$alwaysOn = ac_slider_getParam("navigaion_always_on","off", $settings);
if($alwaysOn == "on")
	$hideThumbs = "0";

$sliderID =$prop['container']['attributes']['id'];

//treat hide slider at limit
$hideSliderAtLimit = (int)ac_slider_getParam("hide_slider_under","0", $settings);
if(!empty($hideSliderAtLimit))
	$hideSliderAtLimit++;

//this option is disabled in full width slider
if($sliderType == "fullwidth")
	$hideSliderAtLimit = "0";

$hideCaptionAtLimit = (int)ac_slider_getParam("hide_defined_layers_under","0", $settings);
if(!empty($hideCaptionAtLimit))
	$hideCaptionAtLimit++;

$hideAllCaptionAtLimit = (int)ac_slider_getParam("hide_all_layers_under","0", $settings);
if(!empty($hideAllCaptionAtLimit))
	$hideAllCaptionAtLimit++;

//start_with_slide
$startWithSlide = ac_slider_getParam("start_with_slids","0", $settings);

//modify navigation type (backward compatability)
$arrowsType = ac_slider_getParam("navigation_arrows","nexttobullets", $settings);
switch($arrowsType){
	case "verticalcentered":
		$arrowsType = "solo";
	break;
}

$videoJsPath = REVSLIDER_PLUGIN_PATH."/videojs/";			
?>

<script type="text/javascript">

	var tpj=jQuery;
	
	
	tpj(document).ready(function() {
	
	if (tpj.fn.cssOriginal != undefined)
		tpj.fn.css = tpj.fn.cssOriginal;
	
	if(tpj('#<?php echo $sliderID?>').revolution == undefined)
		revslider_showDoubleJqueryError('#<?php echo $sliderID?>');
	else
		 tpj('#<?php echo $sliderID?>').show().revolution(
		{
			<?php if ($settings['show_timerbar'] == 'hide'):?>hideTimerBar:"on",<?php endif?>
			dottedOverlay:<?php echo ac_slider_getParam("background_dotted_overlay","none", $settings)?>,
			delay:<?php echo (int)ac_slider_getParam("delay","9000", $settings)?>,
			startwidth:<?php echo ac_slider_getParam("width","900", $settings)?>,
			startheight:<?php echo ac_slider_getParam("height","300", $settings)?>,
			hideThumbs:<?php echo $hideThumbs?>,
			
			thumbWidth:<?php echo (int)ac_slider_getParam("thumb_width","100", $settings)?>,
			thumbHeight:<?php echo (int)ac_slider_getParam("thumb_height","50", $settings)?>,
			thumbAmount:<?php echo $thumbAmount?>,
			
			navigationType: <?php echo ac_slider_getParam("navigaion_type","none", $settings)?>,
			navigationArrows: <?php echo $arrowsType?>,
			navigationStyle:<?php echo ac_slider_getParam("navigation_style","round", $settings)?>,
			
			touchenabled: <?php echo ac_slider_getParam("touchenabled","on", $settings, false)?>,
			onHoverStop: <?php echo ac_slider_getParam("stop_on_hover","on", $settings, false)?>,
			
			navigationHAlign: <?php echo ac_slider_getParam("navigaion_align_hor","center", $settings)?>,
			navigationVAlign: <?php echo ac_slider_getParam("navigaion_align_vert","bottom", $settings)?>,
			navigationHOffset:<?php echo (int)ac_slider_getParam("navigaion_offset_hor","0", $settings)?>,
			navigationVOffset:<?php echo (int)ac_slider_getParam("navigaion_offset_vert","20", $settings)?>,

			soloArrowLeftHalign:<?php echo ac_slider_getParam("leftarrow_align_hor","left", $settings)?>,
			soloArrowLeftValign:<?php echo ac_slider_getParam("leftarrow_align_vert","center", $settings)?>,
			soloArrowLeftHOffset:<?php echo (int)ac_slider_getParam("leftarrow_offset_hor","20", $settings)?>,
			soloArrowLeftVOffset:<?php echo (int)ac_slider_getParam("leftarrow_offset_vert","0", $settings)?>,

			soloArrowRightHalign:<?php echo ac_slider_getParam("rightarrow_align_hor","right", $settings)?>,
			soloArrowRightValign:<?php echo ac_slider_getParam("rightarrow_align_vert","center", $settings)?>,
			soloArrowRightHOffset:<?php echo (int)ac_slider_getParam("rightarrow_offset_hor","20", $settings)?>,
			soloArrowRightVOffset:<?php echo (int)ac_slider_getParam("rightarrow_offset_vert","0", $settings)?>,
					
			shadow:<?php echo ac_slider_getParam("shadow_type","2", $settings)?>,
			fullWidth:"<?php echo $optFullWidth?>",
			fullScreen:"<?php echo $optFullScreen?>",

			stopLoop:<?php echo $stopSlider?>,
			stopAfterLoops:<?php echo $stopAfterLoops?>,
			stopAtSlide:<?php echo $stopAtSlide?>,

			shuffle:<?php echo ac_slider_getParam("shuffle","off", $settings, false) ?>,
			autoHeight:"off",						
			forceFullWidth:"on",
			hideSliderAtLimit:<?php echo $hideSliderAtLimit?>,
			hideCaptionAtLimit:<?php echo $hideCaptionAtLimit?>,
			hideAllCaptionAtLilmit:<?php echo $hideAllCaptionAtLimit?>,
			startWithSlide:<?php echo $startWithSlide?>,
			videoJsPath:"<?php echo $videoJsPath?>",
			fullScreenOffsetContainer: <?php echo ac_slider_getParam("fullscreen_offset_container","", $settings);?>
		});
	
	});	//ready
	
</script>

<?php			
