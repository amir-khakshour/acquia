<?php
/**
 * @file
 *  Diamond Builder settings for {{vc_message}} shortcode
 */
function ac_composer_message_composer(){
	 return array(
		 'vc_message' => array(
				 'class' =>  'vc_message_composerView',
				 'category' => array(t('Content')),
				 "icon" => "sprite-message",
				 "wrapper_class" => "alert",
				 "params" => array(
					 array(
						 "type" => "dropdown",
						 "heading" => __("Message box type", "js_composer"),
						 "param_name" => "type",
						 "value" => array(__('Informational', "js_composer") => "alert-info", __('Warning', "js_composer") => "alert-block", __('Success', "js_composer") => "alert-success", __('Error', "js_composer") => "alert-error"),
						 "description" => __("Select message type.", "js_composer")
					 ),
					 array(
						 "type" => "textarea_html",
						 "holder" => "div",
						 "class" => "messagebox_text",
						 "heading" => __("Message text", "js_composer"),
						 "param_name" => "content",
						 "value" => __("<p>I am message box. Click edit button to change this text.</p>", "js_composer")
					 ),
					 array(
						 "type" => "textfield",
						 "heading" => __("Extra class name", "js_composer"),
						 "param_name" => "el_class",
						 "description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
					 )
				 ),
				 "views" => 'VcMessageView'
			),
	 );
}


// {{vc_message}} shortcode composer Class
if (class_exists('DiamondBuilderView')) {
	 class vc_message_composerView extends DiamondBuilderView {
			public function outputTitle($title) {
				 return '';
			}
	 }
}
