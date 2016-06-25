<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_stick}} shortcode
 */
function ac_composer_stick_composer(){
	return array(
		'ac_stick' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Utility')),
			"is_container" => true,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'header_title' => FALSE,
			"icon" => "sprite-sticky",
			"modal" => array(
				'modal_size' => 'small',
			),
			'views' => 'DiamondBuilderColumnView',
		),
	);
}


