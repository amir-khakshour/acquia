<?php
/**
 * @file
 *  Diamond Builder settings for {{quote}} shortcode
 */
function ac_composer_quote_composer(){
	return array(
		'ac_quote' => array(
			'class' =>  'ac_quote_composerView',
			'category' => array(t('Content')),
			'wrapper_class' => 'ac-full-height ac-no-icon',
			"icon" => "sprite-fancy-quote",
			"show_settings_on_create" => TRUE,
			'header_title' => FALSE,
			"modal" => array(
				'modal_size' => 'small',
			),
			//"order" => 94,
			'asset' => array(
				'library' => array(
					array('acquia', 'fontello'),
				),
				'css' => array(
					ACQUIA_COMPOSER_ASSET_PATH . '/css/ac_quote.css' => array(),
				),
			),
			"views" => 'DiamondBuilderShortcodeView',
		),
	);
}

// {{ac_quote}} Composer View Class
if (class_exists('DiamondBuilderCustomView')) {
	class ac_quote_composerView extends DiamondBuilderCustomView {
		public function elementLabels($atts, $content) {
			$title_template = $this->update_template("title", '<h4 class="title">{{title}}</h4>');
			$content_template = $this->update_template("content", '<div class="content">{{content}}</span>');
			$output = "<blockquote class='ac-fancy-quote'>";
			$output .= "		<div class='fancy-quote-content' {$content_template}><span class='content'>".t('Be sure you put your feet in the right place, then stand firm.')."</span></div>";
			$output .= "</blockquote>";
			return $output;
		}
	}
}