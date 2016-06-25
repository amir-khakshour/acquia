<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_tabs}} and {{ac_tab}} shortcode
 */
function ac_composer_text_block_composer(){
	return array(
		'ac_col_text' => array(
			"class" => 'ac_col_text_composerView',
			"icon" => "sprite-text-block",
			"wrapper_class" => "clearfix",
			"category" => array(t('Content')),
			"always_enabled" => TRUE,
			"header_title" => FALSE,
			"params" => array(
				array(
					"type" => "textarea_html",
					"holder" => "div",
					"heading" => t("Text"),
					"param_name" => "content",
					"value" => t("<p>I am text block. Click edit button to change this text.</p>")
				)
			),
		),
	);
}

// Shortcode Model Class
if (class_exists('DiamondBuilderView')) {
	class ac_col_text_composerView extends DiamondBuilderView {
		public function outputTitle($title) {
			return '';
		}
	}
}
