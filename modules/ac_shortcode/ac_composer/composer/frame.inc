<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_frame}} shortcode
 */
function ac_composer_frame_composer(){
	return array(
		'ac_frame' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Utility')),
			"is_container" => true,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'header_title' => FALSE,
			"icon" => "sprite-image-frame",
			"modal" => array(
				'modal_size' => 'small',
			),
			'views' => 'DiamondBuilderColumnView',
		),
	);
}
