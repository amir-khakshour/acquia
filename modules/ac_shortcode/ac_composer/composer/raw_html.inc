<?php
/**
 * @file
 *  Diamond Builder settings for {{raw_html}} shortcode
 */
function ac_composer_raw_html_composer(){
	return array(
		'ac_raw_html' => array(
			'category' => array(t('Structure')),
			'class' =>  'ac_raw_html_composerView',
			"wrapper_class" => "clearfix",
			"icon" => "sprite-html",
			"views" => 'dbBase64EncodedView',
			"params" => array(
				array(
					"type" => "textarea_raw_html",
					"holder" => "div",
					"heading" => __("Raw HTML", "js_composer"),
					"param_name" => "content",
					"value" => base64_encode("<p>I am raw html block.<br/>Click edit button to change this html</p>"),
					"description" => __("Enter your HTML content.", "js_composer")
				),
			),
		),
	);
}

// ac_row_composerView Class
if (class_exists('DiamondBuilderView')) {
	class ac_raw_html_composerView extends DiamondBuilderView {
		public function elementLabels($param, $value) {
			$template = $this->update_template("content", "<div class='db-param-val'>{{content}}</div>");
			return "<div class='db-param-container' {$template}'></div>";
		}
	}
}