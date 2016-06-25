<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_contact}} shortcode
 */
function ac_composer_contact_composer(){
	return array(
		'ac_contact' => array(
			'category' => array(t('Content')),
			'icon' => 'sprite-contact-form',
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => __("Category"),
					"param_name" => "type_title",
				),
				array(
					"heading" => __("Styles"),
					"param_name" => "style",
				)
			),
		),
	);
}
