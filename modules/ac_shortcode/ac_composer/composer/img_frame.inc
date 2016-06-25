<?php
/**
 * @file
 *  Diamond Builder settings for {{img_frame}} shortcode
 */
function ac_composer_img_frame_composer(){
	return array(
		'ac_img_frame' => array(
			'class' =>  'DiamondBuilderImageView',
			'category' => array(t('Content')),
			'wrapper_class' => 'ac-full-height default-image',
			"icon" => "sprite-image-frame",
			"is_parent" => true,
			"modal" => array(
				'modal_size' => 'small',
			),
			"visual_values" => array(
				"style" => ACQUIA_COMPOSER_IMAGE_STYLE,
			),
			//"order" => 94,
			"params" => array(
				array(
					"heading" => t("frame"),
					"param_name" => "frame",
				),
				array(
					"heading" => t("style"),
					"param_name" => "style",
				),
				array(
					"heading" => t("title"),
					"param_name" => "title",
				),
			),
			"views" => 'DiamondBuilderImageView',
		),
	);
}
