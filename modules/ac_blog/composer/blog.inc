<?php
/**
 * @file
 *  Diamond Builder settings for {{portfolio}} shortcode
 */
function ac_blog_blog_composer(){
	return array(
		'ac_blog' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-blog",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => __("Appearance"),
					"param_name" => "appearance",
				),
				array(
					"heading" => __("Number of items"),
					"param_name" => "total",
				),
				array(
					"heading" => __("Columns"),
					"param_name" => "cols",
				),
			),
		),
	);
}
