<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_iconlist}} shortcode
 */

function ac_composer_iconlist_composer(){
	return array(
		'ac_iconlist' => array(
			'class' =>  'DiamondBuilderContainerView',
			'category' => array(t('Content')),
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			"icon" => "sprite-icon-list",
			"clone_tag" => "ac_iconlist_item",
			"modal" => array(
				'modal_size' => 'small',
			),
			'as_parent' => array(
				'only' => 'ac_iconlist_item',
			),
			'header_title' => FALSE,
			"allowed_container_element" => 'ac_row',
			"custom_markup" => '
				<div class="db_iconlist_holder db-holder clearfix db-parent">
				%content%
				</div>
				<div class="iconlist_controls">
				<button class="add_tab" title="'.__("Add iconlist item", "js_composer").'">'.__("Add iconlist section", "js_composer").'</button>
				</div>
				',
			'default_content' => '
				[ac_iconlist_item title="'.__('Section 1', "js_composer").'"]List Content Here[/ac_iconlist_item]
				[ac_iconlist_item title="'.__('Section 2', "js_composer").'"]List Content Here[/ac_iconlist_item]
				',
			'views' => 'AcItemsList',
			"clone_tag" => "ac_iconlist_item",
		),
		'ac_iconlist_item' => array(
			"class" => 'DiamondBuilderIconlistItemView',
			"allowed_container_element" => 'ac_iconlist',
			'wrapper_class' => 'ac-full-height default-params',
			'icon' => FALSE,
			'header_title' => FALSE,
			"is_container" => FALSE,
			"content_element" => FALSE,
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
				'only' => 'ac_iconlist',
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
                     ACQUIA_COMPOSER_ASSET_PATH . '/ac_iconlist.css' => array(),
                ),*/
			)
		),
	);
}

if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderIconlistItemView extends DiamondBuilderCustomView {
		public function elementLabels($param, $value) {
			$img = "<span class='ac-icon visual-icon default-param-val font-icon icon-heart'></span>";
			$icon_template = $this->update_template("icon", "<span class='ac-icon visual-icon font-icon icon-{{icon}}'></span>");
			$title_template = $this->update_template("title", "<h4 class='header-title'>{{title}}</h4>");
			$content_template = $this->update_template("content", '<span class="content">{{content}}</span>');

			$output  = "<div class='db-img-container header-title' {$icon_template}>{$img}</div>";
			$output .= "<div class='header-title' {$title_template}><h4 class='header-title'>".t('Item Title Here')."</h4></div>";
			$output .= "<div class='iconlist_content' {$content_template}><span class='content'>".t('List Content Here.')."</span></div>";
			return $output;
		}
	}
}