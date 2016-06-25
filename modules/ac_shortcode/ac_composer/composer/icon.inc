<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_font_icon}} shortcode
 */
function ac_composer_icon_composer(){
	return array(
		'ac_font_icon' => array(
			'class' =>  'DiamondBuilderIconView',
			'category' => array(t('Content')),
			"icon" => "sprite-fonticon",
			'wrapper_class' => 'ac-full-height ac-no-icon',
			"modal" => array(
				'modal_size' => 'big',
			),
			//"order" => 94,
			"params" => array(
				array(
					"type" => "textfield",
					"heading" => __("icon", "js_composer"),
					"param_name" => "icon",
					"holder" => "div",
					"value" => __("", "js_composer"),
				),
			),
			'asset' => array(
				'library' => array(
					array('acquia', 'fontello'),
				),
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/global.css' => array(),
				),
			),
			'views' => 'acIconView',
		),
	);
}

// {{ac_iconbox}} Composer View Class
if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderIconView extends DiamondBuilderCustomView {
		protected function iconTemplate() {
			acquia_include('media');
			$icon = parent::iconTemplate();
			$template = $this->update_template("icon", "<span class='ac-icon font-icon icon-{{icon}}'></span>");
			$img = "<span class='ac-icon font-icon default-param-val icon-heart'></span>";
			$output = $icon . "<div class='db-img-container' {$template}>{$img}</div>";
			return $output;
		}
	}
}
