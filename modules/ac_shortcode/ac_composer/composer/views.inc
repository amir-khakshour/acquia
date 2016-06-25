<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_views}} shortcode
 */
function ac_composer_views_composer(){
	return array(
		'ac_views' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-embed",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("View Name"),
					"param_name" => "view",
				),
				array(
					"heading" => t("Display Name"),
					"param_name" => "display",
				),
			),
		),
	);
}
