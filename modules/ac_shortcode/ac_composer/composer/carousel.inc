<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_carousel}} shortcode
 */
function ac_composer_carousel_composer(){
	return array(
		'ac_carousel' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Sliders')),
			"is_container" => true,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'header_title' => FALSE,
			"icon" => "sprite-carousel",
			"modal" => array(
				'modal_size' => 'small',
			),
			'views' => 'DiamondBuilderColumnView',
		),
	);
}

