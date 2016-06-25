<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_misc}} shortcode
 */
function ac_composer_pricing_table_composer(){
	return array(
		'pt' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-price-table",
			"modal" => array(
				'modal_size' => 'big',
			),
			"params" => array(
				array(
					"heading" => t("Type"),
					"param_name" => "type",
				),
				array(
					"heading" => t("Columns"),
					"param_name" => "cols",
				),
			),
		),

		'pt_col' => array(
			'category' => array(t('Content')),
			"content_element" => FALSE,
			"params" => array(
				array(
					"type" => "textfield",
					"heading" => __("Extra class name", "js_composer"),
					"param_name" => "el_class",
					"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
				),
			),
		),

		'pt_row' => array(
			'category' => array(t('Content')),
			"content_element" => FALSE,
			"params" => array(
				array(
					"type" => "textfield",
					"heading" => __("Extra class name", "js_composer"),
					"param_name" => "el_class",
					"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
				),
			),
		),

		'pt_price' => array(
			'category' => array(t('Content')),
			"content_element" => FALSE,
			"params" => array(
				array(
					"type" => "textfield",
					"heading" => __("Extra class name", "js_composer"),
					"param_name" => "el_class",
					"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
				),
			),
		),

		'pt_package' => array(
			'category' => array(t('Content')),
			"content_element" => FALSE,
			"params" => array(
				array(
					"type" => "textfield",
					"heading" => __("Extra class name", "js_composer"),
					"param_name" => "el_class",
					"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
				),
			),
		),

		'pt_details' => array(
			'category' => array(t('Content')),
			"content_element" => FALSE,
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
