<?php
/**
 * @file
 *  Diamond Builder settings for {{teaser}} shortcode
 */
function ac_composer_teaser_composer(){
	return array(
		'ac_teaser' => array(
			'class' =>  'ac_teaser_composerView',
			'category' => array(t('Content')),
			'wrapper_class' => 'ac-full-height ac-no-icon',
			"icon" => "sprite-banner",
			"is_parent" => true,
			"modal" => array(
				'modal_size' => 'big',
			),
			//"order" => 94,
			"params" => array(
				array(
					"type" => "attach_images",
					"heading" => __("Image File id", "js_composer"),
					"param_name" => "fid",
					"description" => __("If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.", "js_composer")
				)
			),
			"views" => 'DiamondBuilderImageView',
		),
	);
}

// {{ac_teaser}} Composer View Class
if (class_exists('DiamondBuilderCustomView')) {
	class ac_teaser_composerView extends DiamondBuilderCustomView {
		public function elementLabels($atts, $content) {
			$atts['align'] = isset($atts['align']) ? $atts['align'] : 'left';
			$img_template = $this->update_template("src", "<img src='{{src}}' alt=''/>");
			$content_template = $this->update_template("content", "<div class='teaser-content'>{{content}}</div>");

			acquia_include('media');
			$default_img_src = acquia_get_empty_thumb(ACQUIA_COMPOSER_IMAGE_STYLE);

			$img = "<img src='".file_create_url($default_img_src)."' alt=''  />";
			$content = "";

			$output  = "<div class='ac-image'>";
			$output .= "<div ".$this->class_by_arguments('align' ,$atts).">";
			$output .= "<div class='ac-teaser-image' {$img_template}>{$img}</div>";
			$output .= "<div class='ac-teaser-content' {$content_template}>{$content}</div>";
			$output .= "</div>";
			$output .= "</div>";
			return $output;
		}
	}
}