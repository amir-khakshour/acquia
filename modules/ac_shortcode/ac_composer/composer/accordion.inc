<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_accordion}} and {{ac_accordion_tab}} shortcode
 */
function ac_composer_accordion_composer(){
	return array(
		'ac_accordion' => array(
			'class' =>  'DiamondBuilderContainerView',
			"category" => t('Content'),
			"is_container" => true,
			"icon" => "sprite-accordion",
			'required' => array('ac_tab'),
			'header_title' => FALSE,
			"child_sortable" => FALSE,
			'bottom_controls' => FALSE,
			'add_tab' => TRUE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll db-accordion',
			'as_parent' => array(
				'only' => 'ac_accordion_tab',
			),
			'default_content' => '
				[ac_accordion_tab title="'.t('Section 1').'"][/ac_accordion_tab]
				[ac_accordion_tab title="'.t('Section 2').'"][/ac_accordion_tab]
				',
			'views' => 'VcAccordionView',
		),
		'ac_accordion_tab' => array(
			'required' => array('ac_tab'),
			'class' => 'DiamondBuilderAccordionTabView',
			"allowed_container_element" => 'ac_accordion',
			"is_container" => TRUE,
			"content_element" => FALSE,
			'header_title' => FALSE,
			'wrapper_class' => 'ac-full-height',
			'element_class' => 'db-full-controll db-accordion-tab',
			'as_child' => array(
				'only' => 'ac_accordion',
			),
			'views' => 'VcAccordionTabView',
		),
	);
}

if (class_exists('DiamondBuilderContainerView')) {
	class DiamondBuilderAccordionTabView extends DiamondBuilderContainerView {
		public function elementAdmin($atts, $content = null) {
			acquia_include('utility', 'ac_composer');
			acquia_include('wp_bridge', 'ac_composer');
			acquia_include('process', 'ac_shortcode');

			extract(shortcode_atts($this->predefined_atts, $atts));
			$output = '';
			$column_controls = $this->getControls($this->settings('controls'), 'top-controls');
			$column_controls_bottom = $this->getControls('append', 'bottom-controls');
			$output .= '<div '.$this->mainHtmlBlockParams().'>';
			$output .= '<div class="db-visual-sc">';

			$title_template = $this->update_template("title", "<span class='header-inner'>{{title}}</span>");
			$output .= "<h4 class='section-header' {$title_template}><i class='admin-icon icon-admin-plus'></i><span class='header-inner'>".t('Section title')."</span></h4>";
			$output .= '<div class="section-body">';
			$output .= $column_controls;
			$output .= '<div '.drupal_attributes($this->containerAttributes()).'>';
			$output .= $content;
			$output .= '</div>';
			if ( isset($this->settings['params']) ) {
				$inner = '';
				foreach ($this->settings['params'] as $param) {
					$param_value = isset($$param['param_name']) ? $$param['param_name'] : '';
					if ( is_array($param_value)) {
						// Get first element from the array
						reset($param_value);
						$first_key = key($param_value);
						$param_value = $param_value[$first_key];
					}
					$inner .= $this->elementLabels($param, $param_value);
				}
				$output .= $inner;
			}
			$output .= '</div>';
			$output .= $column_controls_bottom;
			$output .= '</div>';
			$output .= '</div>';
			return $output;
		}

		public function containerAttributes() {
			$attrs = parent::containerAttributes();
			$attrs['class'][] = 'db-accordion-content';
			return $attrs;
		}
	}
}