<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_socials}} shortcode
 */

function ac_composer_social_composer(){
	return array(
		'ac_socials' => array(
			'class' =>  'DiamondBuilderContainerView',
			"is_container" => TRUE,
			'header_title' => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'category' => array(t('Content')),
			"icon" => "sprite-social",
			"modal" => array(
				'modal_size' => 'small',
			),
			'as_parent' => array(
				'only' => 'ac_social',
			),
			"allowed_container_element" => 'ac_row',
			"custom_markup" => '
				<div class="db_iconlist_holder db-holder clearfix db-parent">
				%content%
				</div>
				<div class="iconlist_controls">
				<button class="add_tab" title="'.__("Add Icon", "js_composer").'">'.__("Add Icon", "js_composer").'</button>
				</div>
				',
			'default_content' => '
				[ac_social icon="facebook" title="facebook"][/ac_social]
				[ac_social icon="twitter" title="twitter"][/ac_social]
				',
			"clone_tag" => "ac_social",
			'views' => 'AcItemsList',
		),
		'ac_social' => array(
			'class' =>  'DiamondBuilderSocialItemView',
			'required' => array('ac_accordion_tab'),
			"allowed_container_element" => 'ac_socials',
			"is_container" => FALSE,
			"content_element" => FALSE,
			'header_title' => FALSE,
			"modal" => array(
				'modal_size' => 'small',
			),
			"params" => array(
				array(
					"heading" => t("Title"),
					"param_name" => "title",
				),
			),
			'as_child' => array(
				'only' => 'ac_socials',
			),
			'views' => 'acIconView',
			'asset' => array(
				'library' => array(
					array('acquia', 'fontello'),
				),
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/global.css' => array(),
				),
				/*
                'js' => array(
                     ACQUIA_COMPOSER_ASSET_PATH . '/ac_socials.css' => array(),
                ),*/
			)
		),
	);
}

if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderSocialItemView extends DiamondBuilderCustomView {
		public function elementLabels($param, $value) {
			$img = "<span class='visual-icon ac-icon default-param-val font-icon icon-heart'></span>";
			$icon_template = $this->update_template("icon", "<span class='visual-icon ac-icon font-icon icon-{{icon}}'></span>");
			$title_template = $this->update_template("title", "<h4 class='header-title'>{{title}}</h4>");

			$output  = "<div class='db-img-container header-title' {$icon_template}>{$img}</div>";
			$output .= "<div class='header-title' {$title_template}><h4 class='header-title'>".t('Item Title Here')."</h4></div>";
			return $output;
		}
	}
}