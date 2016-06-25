<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_divider}} shortcode
 */
function ac_composer_googlemap_composer(){
	return array(
		'ac_gmap' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-map",
			"modal" => array(
				'modal_size' => 'bigger',
			),
			"params" => array(
				array(
					"heading" => t("Address"),
					"param_name" => "address",
				),
			),
			'asset' => array(
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/googlemap.css' => array(),
				),
				'js' => array(
					'http://maps.google.com/maps/api/js?sensor=true' => array('external' => TRUE),
				),
			),
			"views" => 'DiamondBuilderShortcodeView',
		),
		'ac_gmap_marker' => array(
			// Composer Settings
			"content_element" => FALSE,
		),
	);
}

