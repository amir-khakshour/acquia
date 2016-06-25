<?php

// Tabs
define('TAB_TITLE', __("Tab", "js_composer"));

/**
 * @file
 *  Diamond Builder settings for {{ac_tabs}} and {{ac_tab}} shortcode
 */
function ac_composer_tabs_composer(){
	return array(
		'ac_tabs' => array(
			'class' =>  'DiamondBuilderTabsView',
			'header_title' => FALSE,
			"child_sortable" => FALSE,
			'bottom_controls' => FALSE,
			'add_tab' => TRUE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll',
			"icon" => "sprite-tabs",
			"category" => array(__('Content', 'js_composer')),
			"custom_markup" => '
						<div class="db_tabs_holder db-holder db-parent">
						<ul class="tabs_controls">
						</ul>
						%content%
						</div>'
		,
			'default_content' => '
						[ac_tab title="'.t('Tab 1').'" tab_id="'.time().'-1-'.rand(0, 100).'"][/ac_tab]
						[ac_tab title="'.t('Tab 2').'" tab_id="'.time().'-2-'.rand(0, 100).'"][/ac_tab]
						',
			"views" => 'VcTabsView',
			'as_parent' => array(
				'only' => 'ac_tab',
			),
		),

		// tabs inner
		'ac_tab' => array(
			'class' =>  'DiamondBuilderContainerView',
			'required' => array('ac_col'),
			'enabled' => array('ac_tabs' => TRUE),
			'header_title' => FALSE,
			// Composer Settings
			'element_class' => 'db-full-controll',
			"allowed_container_element" => 'ac_row',
			"is_container" => true,
			"content_element" => false,
			'views' => 'VcTabView',
			'as_child' => array(
				'only' => 'ac_tabs',
			),
		),
	);
}

if (class_exists('DiamondBuilderContainerView')) {
	class DiamondBuilderTabsView extends DiamondBuilderContainerView
	{
		public function prependVisual(){
			return '<ul class="ui-tabs-nav"></ul>';
		}

		public function containerAttributes() {
			$attrs = parent::containerAttributes();
			$attrs['class'][] = 'db-tabs-content';
			return $attrs;
		}
	}
}