<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_iconbox}} shortcode
 */
function ac_composer_iconbox_composer(){
	return array(
		'ac_iconbox' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Utility')),
			"is_container" => true,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'header_title' => FALSE,
			"icon" => "sprite-icon-box",
			"modal" => array(
				'modal_size' => 'small',
			),
			'asset' => array(
				'library' => array(
					array('acquia', 'fontello'),
				),
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/global.css' => array(),
				),
			),
			'views' => 'DiamondBuilderColumnView',
		),
	);
}
