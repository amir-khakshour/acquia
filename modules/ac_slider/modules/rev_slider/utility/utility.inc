<?php
/**
 * @todo
 */

function rev_slider_start_animation(){
	return array(
		"tp-fade"=>"Fade",
		"sft"=>"Short from Top",
		"sfb"=>"Short from Bottom",
		"sfr"=>"Short from Right",
		"sfl"=>"Short from Left",
		"lft"=>"Long from Top",
		"lfb"=>"Long from Bottom",
		"lfr"=>"Long from Right",
		"lfl"=>"Long from Left",
		"skewfromright"=>"Skew From Long Right",
		"skewfromleft"=>"Skew From Long Left",
		"skewfromleftshort"=>"Skew From Short Right",
		"skewfromrightshort"=>"Skew From Short Left",
		"randomrotate"=>"Random Rotate"
	);
}

function rev_slider_end_animation(){
	return array(
		"auto"=>"Choose Automatic",
		"fadeout"=>"Fade Out",
		"stt"=>"Short to Top",
		"stb"=>"Short to Bottom",
		"stl"=>"Short to Left",
		"str"=>"Short to Right",
		"ltt"=>"Long to Top",
		"ltb"=>"Long to Bottom",
		"ltl"=>"Long to Left",
		"ltr"=>"Long to Right",
		"skewtoright"=>"Skew To Right",
		"skewtoleft"=>"Skew To Left",
		"skewtorightshort"=>"Skew To Right Short",
		"skewtoleftshort"=>"Skew To Left Short",
		"randomrotateout"=>"Random Rotate Out"
	);
}

/**
 *
 */
function rev_slider_end_easing(){
  return array_merge(array("nothing" => "No Change"), rev_slider_easing());
}

/**
 *
 */
function rev_slider_easing(){
	return array(
		"Linear.easeNone" => "Linear.easeNone",
		"Power0.easeIn" => "Power0.easeIn  (linear)",
		"Power0.easeInOut" => "Power0.easeInOut  (linear)",
		"Power0.easeOut" => "Power0.easeOut  (linear)",
		"Power1.easeIn" => "Power1.easeIn",
		"Power1.easeInOut" => "Power1.easeInOut",
		"Power1.easeOut" => "Power1.easeOut",
		"Power2.easeIn" => "Power2.easeIn",
		"Power2.easeInOut" => "Power2.easeInOut",
		"Power2.easeOut" => "Power2.easeOut",
		"Power3.easeIn" => "Power3.easeIn",
		"Power3.easeInOut" => "Power3.easeInOut",
		"Power3.easeOut" => "Power3.easeOut",
		"Power4.easeIn" => "Power4.easeIn",
		"Power4.easeInOut" => "Power4.easeInOut",
		"Power4.easeOut" => "Power4.easeOut",
		"Quad.easeIn" => "Quad.easeIn  (same as Power1.easeIn)",
		"Quad.easeInOut" => "Quad.easeInOut  (same as Power1.easeInOut)",
		"Quad.easeOut" => "Quad.easeOut  (same as Power1.easeOut)",
		"Cubic.easeIn" => "Cubic.easeIn  (same as Power2.easeIn)",
		"Cubic.easeInOut" => "Cubic.easeInOut  (same as Power2.easeInOut)",
		"Cubic.easeOut" => "Cubic.easeOut  (same as Power2.easeOut)",
		"Quart.easeIn" => "Quart.easeIn  (same as Power3.easeIn)",
		"Quart.easeInOut" => "Quart.easeInOut  (same as Power3.easeInOut)",
		"Quart.easeOut" => "Quart.easeOut  (same as Power3.easeOut)",
		"Quint.easeIn" => "Quint.easeIn  (same as Power4.easeIn)",
		"Quint.easeInOut" => "Quint.easeInOut  (same as Power4.easeInOut)",
		"Quint.easeOut" => "Quint.easeOut  (same as Power4.easeOut)",
		"Strong.easeIn" => "Strong.easeIn  (same as Power4.easeIn)",
		"Strong.easeInOut" => "Strong.easeInOut  (same as Power4.easeInOut)",
		"Strong.easeOut" => "Strong.easeOut  (same as Power4.easeOut)",
		"Back.easeIn" => "Back.easeIn",
		"Back.easeInOut" => "Back.easeInOut",
		"Back.easeOut" => "Back.easeOut",
		"Bounce.easeIn" => "Bounce.easeIn",
		"Bounce.easeInOut" => "Bounce.easeInOut",
		"Bounce.easeOut" => "Bounce.easeOut",
		"Circ.easeIn" => "Circ.easeIn",
		"Circ.easeInOut" => "Circ.easeInOut",
		"Circ.easeOut" => "Circ.easeOut",
		"Elastic.easeIn" => "Elastic.easeIn",
		"Elastic.easeInOut" => "Elastic.easeInOut",
		"Elastic.easeOut" => "Elastic.easeOut",
		"Expo.easeIn" => "Expo.easeIn",
		"Expo.easeInOut" => "Expo.easeInOut",
		"Expo.easeOut" => "Expo.easeOut",
		"Sine.easeIn" => "Sine.easeIn",
		"Sine.easeInOut" => "Sine.easeInOut",
		"Sine.easeOut" => "Sine.easeOut",
		"SlowMo.ease" => "SlowMo.ease",
		//add old easings
		"easeOutBack" => "easeOutBack",
		"easeInQuad" => "easeInQuad",
		"easeOutQuad" => "easeOutQuad",
		"easeInOutQuad" => "easeInOutQuad",
		"easeInCubic" => "easeInCubic",
		"easeOutCubic" => "easeOutCubic",
		"easeInOutCubic" => "easeInOutCubic",
		"easeInQuart" => "easeInQuart",
		"easeOutQuart" => "easeOutQuart",
		"easeInOutQuart" => "easeInOutQuart",
		"easeInQuint" => "easeInQuint",
		"easeOutQuint" => "easeOutQuint",
		"easeInOutQuint" => "easeInOutQuint",
		"easeInSine" => "easeInSine",
		"easeOutSine" => "easeOutSine",
		"easeInOutSine" => "easeInOutSine",
		"easeInExpo" => "easeInExpo",
		"easeOutExpo" => "easeOutExpo",
		"easeInOutExpo" => "easeInOutExpo",
		"easeInCirc" => "easeInCirc",
		"easeOutCirc" => "easeOutCirc",
		"easeInOutCirc" => "easeInOutCirc",
		"easeInElastic" => "easeInElastic",
		"easeOutElastic" => "easeOutElastic",
		"easeInOutElastic" => "easeInOutElastic",
		"easeInBack" => "easeInBack",
		"easeInOutBack" => "easeInOutBack",
		"easeInBounce" => "easeInBounce",
		"easeOutBounce" => "easeOutBounce",
		"easeInOutBounce" => "easeInOutBounce",
	);
}