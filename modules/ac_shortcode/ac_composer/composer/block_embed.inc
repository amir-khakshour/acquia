<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_block_embed}} shortcode
 */
function ac_composer_block_embed_composer(){
	return array(
		'ac_block_embed' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-embed",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("Block ID"),
					"param_name" => "id",
				),
				array(
					"heading" => t("Block Custom title"),
					"param_name" => "block_title",
				),
			),
		),
	);
}
