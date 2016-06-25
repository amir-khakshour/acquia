<?php

/**
 * @file
 *  Diamond Builder settings for {{ac_team}} and {{ac_team_icon}} shortcode
 */
function ac_composer_team_composer(){
	return array(
		'ac_team' => array(
			'class' => 'DiamondBuilderTeamView',
			'category' => array(t('Content')),
			'wrapper_class' => 'ac-full-height default-params',
			"icon" => "sprite-team",
			"is_parent" => true,
			"modal" => array(
				'modal_size' => 'small',
			),
			"visual_values" => array(
				"style" => ACQUIA_COMPOSER_IMAGE_STYLE,
			),
			"params" => array(
				array(
					"heading" => t("name"),
					"param_name" => "name",
				),
				array(
					"heading" => t("job"),
					"param_name" => "job",
				),
			),
			"views" => 'DiamondBuilderImageView',
		),
	);
}

if (class_exists('DiamondBuilderView')) {
	class DiamondBuilderTeamView extends DiamondBuilderView {
		protected function iconTemplate() {
			acquia_include('media');
			$icon = parent::iconTemplate();
			$template = $this->update_template("src", "<img src='{{src}}' alt=''/>");
			$default_img_src = acquia_get_empty_thumb(ACQUIA_COMPOSER_IMAGE_STYLE);
			$img = "<img class='default-param-val' src='".file_create_url($default_img_src, array('absolute' => TRUE))."' alt=''  />";
			$output = $icon . "<div class='db-img-container' {$template}>{$img}</div>";
			return $output;
		}
	}
}