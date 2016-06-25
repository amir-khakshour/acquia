<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_accordion}} and {{ac_accordion_tab}} shortcode
 */
function ac_composer_banner_composer(){
	return array(
		'ac_banner' => array(
			'class' =>  'DiamondBuilderContainerView',
			"category" => __('Content', 'js_composer'),
			"icon" => "sprite-banner",
			'required' => array('ac_accordion'),
			'add_tab' => FALSE,
			"is_container" => TRUE,
			'header_title' => FALSE,
			"child_sortable" => FALSE,
			'bottom_controls' => FALSE,
			'controls' => 'edit_popup_delete',
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll db-accordion',
			'as_parent' => array(
				'only' => 'ac_banner_item',
			),
			"custom_markup" => '
				<div class="db_accordion_holder db-holder clearfix db-parent">
				%content%
				</div>
				',
			'default_content' => '
				[ac_banner_item][/ac_banner_item]
				[ac_banner_item second="true"][/ac_banner_item]
				',
			'views' => 'VcAccordionView',
		),
		'ac_banner_item' => array(
			'class' =>  'DiamondBuilderAccordionTabView',
			'required' => array('ac_accordion'),
			"allowed_container_element" => 'ac_banner',
			"is_container" => TRUE,
			"is_sortable" => FALSE,
			"content_element" => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll db-accordion-tab',
			'header_title' => FALSE,
			'as_child' => array(
				'only' => 'ac_accordion',
			),
			'views' => 'VcAccordionTabView',
		),
	);
}
