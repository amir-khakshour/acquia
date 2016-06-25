<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_audio}} shortcode
 */
function ac_composer_audio_composer(){
	return array(
		'ac_audio' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-audio",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("Source Type"),
					"param_name" => "type",
				)
			),
		),
	);
}
