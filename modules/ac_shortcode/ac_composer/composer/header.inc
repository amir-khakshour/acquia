<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_fancy_header}} and {{ac_page_header}} shortcode
 */
function ac_composer_header_composer(){
	return array(
		'ac_fancy_header' => array(
			'class' => 'DiamondBuilderPageHeaderView',
			'category' => array(t('Content')),
			"icon" => "sprite-fancy-header",
			'header_title' => FALSE,
			"modal" => array(
				'modal_size' => 'small',
			),
			"visual_params" => array(
				'modal_size' => 'small',
			),
			"views" => 'DiamondBuilderShortcodeView',
		),
		'ac_page_header' => array(
			'class' => 'DiamondBuilderPageHeaderView',
			'category' => array(t('Content')),
			"icon" => "sprite-page-header",
			'header_title' => FALSE,
			"modal" => array(
				'modal_size' => 'small',
			),
			"visual_params" => array(
				'modal_size' => 'small',
			),
			"views" => 'DiamondBuilderShortcodeView',
		),
	);
}


if (class_exists('DiamondBuilderView')) {
	class DiamondBuilderPageHeaderView extends DiamondBuilderView {
		public function getInner($content) {
			$icon = parent::iconTemplate();
			$template = $this->update_template("tag,content", '<{{tag}} class="header">{{content}}</{{tag}}>');
			$default_content = '<h3 class="header">'.t('page Header text here').'</h3>';
			$output = $icon . "<div {$template}>{$default_content}</div>";
			return $output;
		}
	}
}