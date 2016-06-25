<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_progressbar}} shortcode
 */

function ac_composer_progressbar_composer(){
	return array(
		'ac_progressbar' => array(
			'class' =>  'DiamondBuilderContainerView',
			"is_container" => TRUE,
			'header_title' => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'category' => array(t('Content')),
			"icon" => "sprite-progress-bars",
			"modal" => array(
				'modal_size' => 'small',
			),
			'add_tab' => TRUE,
			'as_parent' => array(
				'only' => 'ac_progressbar_item',
			),
			"custom_markup" => '
				<div class="db_progressbar_holder db-holder clearfix db-parent">
				%content%
				</div>
				<div class="progressbar_controls">
				<button class="add_tab" title="'.__("Add progressbar item", "js_composer").'">'.__("Add progressbar item", "js_composer").'</button>
				</div>
				',
			'default_content' => '
				[ac_progressbar_item title="'.__('Skill or Task 1', "js_composer").'" progress="50"][/ac_progressbar_item]
				[ac_progressbar_item title="'.__('Skill or Task 2', "js_composer").'" progress="50"][/ac_progressbar_item]
				',
			"clone_tag" => "ac_progressbar_item",
			'views' => 'AcItemsList',
		),

		'ac_progressbar_item' => array(
			'class' =>  'DiamondBuilderProgressbarItemView',
			'required' => array('ac_accordion_tab'),
			"allowed_container_element" => 'ac_row',
			"is_container" => FALSE,
			"content_element" => FALSE,
			'header_title' => FALSE,
			'as_child' => array(
				'only' => 'ac_progressbar',
			),
			'views' => 'AcprogressbarItemView',
			'asset' => array(
				'library' => array(
					array('acquia', 'fontello'),
				),
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/ac_progressbar.css' => array(),
				),
				/*
                'js' => array(
                     ACQUIA_COMPOSER_ASSET_PATH . '/ac_progressbar.css' => array(),
                ),*/
			)
		),
	);
}

if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderProgressbarItemView extends DiamondBuilderCustomView {
		public function elementLabels($param, $value) {
			$img = "<span class='visual-icon ac-icon default-param-val font-icon icon-heart'></span>";
			$icon_template = $this->update_template("icon", "<span class='visual-icon ac-icon font-icon icon-{{icon}}'></span>");

			$title_template = $this->update_template("title", '<h4 class="title">{{title}}</h4>');
			$bar_template = $this->update_template("progress", '<div class="progress" style="width:{{progress}}%;"></div>');

			$output  = "<div class='ac-progressbar-item ac-sortable-item clearfix'>";
			$output .= "	<div class='progressbar_content_wrap'>";
			$output  = "		<div class='header-title' {$icon_template}>{$img}</div>";
			$output .= "		<div class='progressbar_title' {$title_template}><h4 class='title'>".t('Skill or Task')."</h4></div>";
			$output .= "		<div class='progressbar_progress' {$bar_template}><div class='progress'><span class='inner' style='width:{{progress}}%;'></span></div></div>";
			$output .= "	</div>";
			$output .= "</div>";
			return $output;
		}
	}
}
