<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_flickr}} shortcode
 */
function ac_composer_flickr_composer(){
	return array(
		'ac_flickr' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-flickr",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("Flickr Id"),
					"param_name" => "id",
				),
				array(
					"heading" => t("Number of Items"),
					"param_name" => "nums",
				),
				array(
					"heading" => t("Size"),
					"param_name" => "size",
				),
			),
		),
	);
}
