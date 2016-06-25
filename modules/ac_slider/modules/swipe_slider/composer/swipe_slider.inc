<?php
/**
 * @file
 *  Diamond Builder settings for {{portfolio}} shortcode
 */
function swipe_slider_swipe_slider_composer(){
	return array(
		'swipe_slider' => array(
			'category' => array(t('Sliders')),
			"icon_image" => file_create_url(drupal_get_path('module', 'ac_slider') . '/images/slider.png', array('absolute'=> TRUE)),
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => __("Slider ID"),
					"param_name" => "id",
				),
			),
		),
	);
}
