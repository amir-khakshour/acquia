<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_counter}} shortcode
 */
function ac_composer_counter_composer(){
	return array(
		'ac_counter' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-counter",
			"modal" => array(
				'modal_size' => 'big',
			),
			'wrapper_class' => 'ac-full-height',
			"params" => array(
				array(
					"heading" => t("Title"),
					"param_name" => "title",
				),
				array(
					"heading" => t("Counter value"),
					"param_name" => "value",
				),
				array(
					"heading" => t("Units"),
					"param_name" => "units",
				),
			),
		),
	);
}
