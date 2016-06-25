<?php
/**
 * @file
 *  Diamond Builder settings for {{callout}} shortcode
 */
function ac_composer_callout_composer(){
	return array(
		'ac_callout' => array(
			'class' =>  'DiamonBuilderCalloutView',
			'category' => array(t('Content')),
			"required" => array('raw_html'),
			"icon" => "sprite-callout",
			"views" => 'dbBase64EncodedView',
			"modal" => array(
				'modal_size' => 'big',
			),
			"params" => array(
				array(
					"type" => "textarea_raw_html",
					"holder" => "div",
					"heading" => __("Code View", "js_composer"),
					"param_name" => "content",
					"value" => base64_encode("<p>I am a Callout block.<br/>Click edit button to change this html</p>"),
					"description" => __("Enter your HTML content.", "js_composer")
				),
			),
		),
	);
}

// ac_row_composerView Class
if (class_exists('DiamondBuilderView')) {
	class DiamonBuilderCalloutView extends DiamondBuilderView {
		public function elementLabels($param, $value) {
			$template = $this->update_template("content", "<div class='db-param-val'>{{content}}</div>");
			return "<div class='db-param-container' {$template}'></div>";
		}
	}
}