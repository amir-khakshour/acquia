<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_divider}} shortcode
 */
function ac_composer_divider_composer(){
	 return array(
		 'ac_divider' => array(
				 'category' => array(t('Content')),
				 "icon" => "sprite-divider",
				 "modal" => array(
						'modal_size' => 'small',
				 ),
				 "params" => array(
					 array(
						 "type" => "dropdown",
						 "class" => "",
						 "heading" => __("Divider Type"),
						 "admin_label" => true,
						 "param_name" => "type",
					 ),
				 ),
			),
	 );
}
