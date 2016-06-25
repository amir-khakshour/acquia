<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_misc}} shortcode
 */
function ac_composer_misc_composer(){
	 return array(
		 'ac_highlight' => array(
				 'category' => array(t('Content')),
				 "content_element" => false,
				 "params" => array(
						array(
							"type" => "textfield",
							"heading" => __("Extra class name", "js_composer"),
							"param_name" => "el_class",
							"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
						),
				 ),
			),
		 'ac_dropcap' => array(
				 'category' => array(t('Content')),
				 "content_element" => false,
				 "params" => array(
						array(
							"type" => "textfield",
							"heading" => __("Extra class name", "js_composer"),
							"param_name" => "el_class",
							"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
						),
				 ),
			),
	 );
}
