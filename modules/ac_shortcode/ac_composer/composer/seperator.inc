<?php
/**
 * @file
 *  Diamond Builder settings for {{vc_text_separator}} shortcode
 */
function ac_composer_seperator_composer(){
	 return array(
		 'vc_text_separator' => array(
				 'category' => array(t('Content')),
				 "icon" => "sprite-divider",
				 "modal" => array(
						'modal_size' => 'small',
				 ),
				 "params" => array(
					 array(
						 "type" => "textfield",
						 "heading" => __("Title", "js_composer"),
						 "param_name" => "title",
						 "holder" => "div",
						 "value" => __("Title", "js_composer"),
						 "description" => __("Separator title.", "js_composer")
					 ),
					 array(
						 "type" => "dropdown",
						 "heading" => __("Title position", "js_composer"),
						 "param_name" => "title_align",
						 "value" => array(__('Align center', "js_composer") => "separator_align_center", __('Align left', "js_composer") => "separator_align_left", __('Align right', "js_composer") => "separator_align_right"),
						 "description" => __("Select title location.", "js_composer")
					 ),
					 array(
						 "type" => "textfield",
						 "heading" => __("Extra class name", "js_composer"),
						 "param_name" => "el_class",
						 "description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
					 )
				 ),
				 "header_title" => FALSE,
				 "views" => 'VcTextSeparatorView',
			),
	 );
}
