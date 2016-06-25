<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_pie}} shortcode
 */
function ac_composer_pie_composer(){
	 return array(
			'ac_pie' => array(
				'category' => array(t('Content')),
				 "icon" => "sprite-pie-chart",
				 "modal" => array(
						'modal_size' => 'big',
				 ),
				 'wrapper_class' => 'ac-full-height',
				 "params" => array(
						 array(
							 "type" => "textfield",
							 "class" => "",
							 "heading" => __("Title"),
							 "admin_label" => true,
							 "param_name" => "title",
							 "value" => t('Widget title'),
						 ),
						 array(
						   "type" => "textfield",
							 "class" => "",
							 "heading" => __("pie value"),
							 "admin_label" => true,
							 "param_name" => "value",
							 "value" => t('N/A'),
						 ),
             array(
						   "type" => "textfield",
							 "class" => "",
							 "heading" => __("Units"),
							 "admin_label" => true,
							 "param_name" => "unit",
							 "value" => t('N/A'),
						 ),
				 ),
			),
	 );
}
