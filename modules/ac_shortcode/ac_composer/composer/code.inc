
<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_code}} shortcode
 */
function ac_composer_code_composer(){
	return array(
		'ac_code' => array(
			'category' => array(t('Structure')),
			'class' =>  'ac_raw_html_composerView',
			"wrapper_class" => "clearfix",
			"required" => array('raw_html'),
			'icon' => 'sprite-code',
			"views" => 'dbBase64EncodedView',
			"params" => array(
				array(
					"type" => "textarea_raw_html",
					"holder" => "div",
					"heading" => t("Code"),
					"param_name" => "content",
					"value" => base64_encode("[ac_code]I'm inside a code view tag[ac_code]"),
				),
			),
		),
	);
}
