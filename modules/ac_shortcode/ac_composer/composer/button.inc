<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_button}} shortcode
 */
function ac_composer_button_composer(){
	return array(
		'ac_button' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-button",
			"modal" => array(
				'modal_size' => 'big',
			),
			'wrapper_class' => 'ac-full-height',
			"params" => array(
				array(
					"heading" => t("Caption"),
					"param_name" => "label",
				),
				array(
					"heading" => t("Style"),
					"param_name" => "style",
				),
				array(
					"heading" => t("Type"),
					"param_name" => "type",
				),
			),
		),
	);
}
