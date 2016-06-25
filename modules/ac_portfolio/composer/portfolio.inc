<?php
/**
 * @file
 *  Diamond Builder settings for {{portfolio}} shortcode
 */
function ac_portfolio_portfolio_composer(){
	return array(
		'ac_portfolio' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-portfolio",
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
		'ac_portfolio_tags' => array(
			'category' => array(t('Content')),
			"icon" => "sprite-portfolio-tags",
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => __("View"),
					"param_name" => "view",
				),
			),
		),
	);
}
