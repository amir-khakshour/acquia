<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_testimonials}} shortcode
 */

function ac_composer_testimonial_composer(){
	return array(
		'ac_testimonials' => array(
			'class' =>  'DiamondBuilderContainerView',
			"is_container" => TRUE,
			'header_title' => FALSE,
			"child_sortable" => FALSE,
			'bottom_controls' => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			'category' => array(t('Content')),
			"icon" => "sprite-testimonials",
			"modal" => array(
				'modal_size' => 'small',
			),
			'as_parent' => array(
				'only' => 'ac_testimonial',
			),
			"allowed_container_element" => 'ac_row',
			"custom_markup" => '
				<div class="db_testimonial_holder db-holder clearfix db-parent">
				%content%
				</div>
				<div class="testimonial_controls">
				<button class="add_tab" title="'.__("Add testimonial item", "js_composer").'">'.__("Add testimonial section", "js_composer").'</button>
				</div>
				',
			'default_content' => '
				[ac_testimonial name="'.t('John Doe').'" position="CEO"][/ac_testimonial]
				[ac_testimonial name="'.t('Sarah Doe').'" position="marketing director"][/ac_testimonial]
				',
			"clone_tag" => "ac_testimonial",
			'views' => 'AcItemsList',
		),
		'ac_testimonial' => array(
			'class' =>  'DiamondBuilderTestimonialItemView',
			'required' => array('ac_accordion_tab'),
			"allowed_container_element" => 'ac_testimonials',
			'header_title' => FALSE,
			"is_container" => FALSE,
			"icon" => 'sprite-testimonials',
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
			"visual_values" => array(
				"style" => ACQUIA_COMPOSER_IMAGE_STYLE,
			),
			'as_child' => array(
				'only' => 'ac_testimonials',
			),
			'views' => 'DiamondBuilderImageView',
		),
	);
}

if (class_exists('DiamondBuilderCustomView')) {
	class DiamondBuilderTestimonialItemView extends DiamondBuilderCustomView {
		public function elementLabels($param, $value) {
			acquia_include('media');
			$icon = parent::iconTemplate();
			$template = $this->update_template("src", "<img class='db-img-container' src='{{src}}' alt=''/>");
			$default_img_src = acquia_get_empty_thumb(ACQUIA_COMPOSER_IMAGE_STYLE);
			$img = "<img class='default-param-val db-img-container' src='".file_create_url($default_img_src, array('absolute' => TRUE))."' alt=''  />";

			$title_template = $this->update_template("name,position", "<h4 class='header-title'>{{name}}<br/><span>{{position}}</span></h4>");
			$output  = $icon . "<div class='author-image-container' {$template}>{$img}</div>";
			$output .= "<h4 class='header-wrapper' {$title_template}><span class='header-title'>".t('Author Name.')."</span></h4>";
			return $output;
		}
	}
}
