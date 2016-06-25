<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_video}} shortcode
 */
function ac_composer_video_composer(){
	return array(
		'ac_video' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-video",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("File ID"),
					"param_name" => "fid",
				),
				array(
					"heading" => t("style"),
					"param_name" => "style",
				),
				array(
					"heading" => t("frame"),
					"param_name" => "frame",
				),

			),
		),
	);
}
