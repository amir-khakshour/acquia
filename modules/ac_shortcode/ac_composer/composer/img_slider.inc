<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_iconlist}} shortcode
 */

function ac_composer_img_slider_composer(){
	return array(
		'img_slider' => array(
			'class' =>  'DiamondBuilderContainerView',
			"icon" => "sprite-image-slider",
			'category' => array(t('Sliders')),
			'add_tab' => FALSE,
			"is_container" => TRUE,
			'header_title' => FALSE,
			"child_sortable" => FALSE,
			'bottom_controls' => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll db-accordion',
			"clone_tag" => "img_slider_item",
			"modal" => array(
				'modal_size' => 'small',
			),
			'as_parent' => array(
				'only' => 'img_slider_item',
			),
			"allowed_container_element" => 'ac_row',
			"custom_markup" => '
				<div class="db_img_slider_holder db-holder clearfix db-parent">
				%content%
				</div>
				<div class="img_slider_controls">
				<button class="add_tab" title="'.__("Add new slide item", "js_composer").'">'.__("Add new slide", "js_composer").'</button>
				</div>
				',
			'default_content' => '
				[img_slider_item fid="0"]Caption Here[/img_slider_item]
				[img_slider_item fid="0"]Caption Here[/img_slider_item]
				',
			'views' => 'AcItemsList',
			"clone_tag" => "img_slider_item",
		),
		'img_slider_item' => array(
			'class' =>  'DiamondBuilderImageSliderItemView',
			'required' => array('ac_accordion_tab'),
			"allowed_container_element" => 'img_slider',
			"icon" => "sprite-image-slider",
			"wrapper_class" => "default-params",
			'header_title' => FALSE,
			"is_container" => FALSE,
			"content_element" => FALSE,
			"modal" => array(
				'modal_size' => 'small',
			),
			"visual_values" => array(
				"style" => ACQUIA_COMPOSER_IMAGE_STYLE,
			),
			'as_child' => array(
				'only' => 'img_slider',
			),
			'views' => 'DiamondBuilderImageView',
		),
	);
}

if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderImageSliderItemView extends DiamondBuilderCustomView {
		public function elementLabels($param, $value) {
			acquia_include('media');
			$icon = parent::iconTemplate();
			$template = $this->update_template("src", "<img src='{{src}}' alt=''/>");
			$default_img_src = acquia_get_empty_thumb(ACQUIA_COMPOSER_IMAGE_STYLE);
			$img = "<img class='default-param-val' src='".file_create_url($default_img_src, array('absolute' => TRUE))."' alt=''  />";

			$content_template = $this->update_template("content", '<span class="content">{{content}}</span>');

			$output  = $icon . "<div class='db-img-container' {$template}>{$img}</div>";
			$output .= "<h4 class='iconlist_content' {$content_template}><span class='content'>".t('Item Caption Here.')."</span></h4>";
			return $output;
		}
	}
}
