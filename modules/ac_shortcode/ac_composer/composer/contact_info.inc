<?php

/**
 * @file
 *  Diamond Builder settings for {{ac_contact_info}} and {{ac_contact_info_icon}} shortcode
 */
function ac_composer_contact_info_composer(){
	return array(
		'ac_contact_info' => array(
			'element_class' => 'db-full-controll',
			"show_settings_on_create" => TRUE,
			"icon" => "sprite-contact",
			"category" => array(__('Content', 'js_composer')),
			"params" => array(
				array(
					"heading" => t("Style"),
					"param_name" => "style",
				),
				array(
					"heading" => t("person"),
					"param_name" => "person",
				),

				array(
					"heading" => t("company"),
					"param_name" => "company",
				),
				array(
					"heading" => t("address"),
					"param_name" => "address",
				),
				array(
					"heading" => t("phone"),
					"param_name" => "phone",
				),
				array(
					"heading" => t("fax"),
					"param_name" => "fax",
				),
				array(
					"heading" => t("email"),
					"param_name" => "email",
				),
				array(
					"heading" => t("website"),
					"param_name" => "website",
				),
			),
			"views" => 'DiamondBuilderShortcodeView',
		),
	);
}
