<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_grid}} shortcode
 */
function ac_composer_grid_composer(){
	return array(
		'ac_grid' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Utility')),
			"is_container" => TRUE,
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

