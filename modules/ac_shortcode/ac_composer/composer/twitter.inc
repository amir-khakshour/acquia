<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_twitter}} shortcode
 */
function ac_composer_twitter_composer(){
	return array(
		'ac_twitter' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-twitter",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("Twitter key"),
					"param_name" => "key",
				),
				array(
					"heading" => t("items count"),
					"param_name" => "items",
				),
				array(
					"heading" => t("display style"),
					"param_name" => "style",
				),
			),
		),
	);
}
