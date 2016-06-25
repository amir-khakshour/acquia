<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_visibility}} shortcode
 */
function ac_composer_visibility_composer(){
	return array(
		'ac_visibility' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Utility')),
			"is_container" => true,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'header_title' => FALSE,
			"icon" => "sprite-visibility",
			"modal" => array(
				'modal_size' => 'small',
			),
			'views' => 'DiamondBuilderColumnView',
		),
	);
}
