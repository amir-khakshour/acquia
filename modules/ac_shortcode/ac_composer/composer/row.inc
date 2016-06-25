<?php
/**
 * @file
 *  Diamond Builder settings for {{img_frame}} shortcode
 */
function ac_composer_row_composer(){
	return array(
		'ac_row' => array(
			'class' =>  'dbRowView',
			"base" => "ac_row",
			"is_container" => true,
			"icon" => "sprite-row",
			"show_settings_on_create" => false,
			"category" => t('Content'),
			"views" => 'VcRowView'
		),
		'ac_row_inner' => array(
			'class' =>  'dbRowInnerView',
			"content_element" => false,
			"is_container" => true,
			"icon" => "icon-db-row",
			"show_settings_on_create" => false,
			"views" => 'VcRowView'
		),
	);
}

// dbRowView Class
if (class_exists('DiamondBuilderView')) {
	/**
	 * Class dbRowView
	 */
	class dbRowView extends DiamondBuilderView {
		protected $predefined_atts = array(
			'el_class' => '',
		);

		public function getControls($controls, $extended_css = '') {
			acquia_include('utility', 'ac_composer');

			$controls_start = '<div class="db-controls db-controls-row clearfix">';
			$controls_end = '</div>';

			$right_part_start = '';//'<div class="controls_right">';
			$right_part_end = '';//'</div>';

			//Create columns
			$controls_center_start = '<span class="db-control db-row-layouts">';
			$controls_layout = '<a class="set-layout custom_columns" data-cells="custom" data-layout="custom" title="'.__('Custom layout', 'js_composer').'">'.__('Custom layout', 'js_composer').'</a>';
			foreach(ac_composer_row_layouts() as $layout) {
				$controls_layout .= '<a class="set-layout '.$layout['icon_class'].'" data-cells="'.$layout['cells'].'" data-layout="'.$layout['mask'].'" title="'.$layout['title'].'"></a>';
			}
			$controls_move = ' <a class="db-control col-move" href="#" title="'.t('Drag to move the row').'"><i class="admin-icon icon-admin-move"></i></a>';
			$controls_delete = '<a class="db-control col-delete" href="#" title="'.t('Delete this row').'"><i class="admin-icon icon-admin-trash"></i></a>';
			$controls_edit = ' <a class="db-control col-edit" href="#" title="'.t('Edit this row').'"><i class="admin-icon icon-admin-pencil"></i></a>';
			$controls_clone = ' <a class="db-control col-clone" href="#" title="'.t('Clone this row').'"><i class="admin-icon icon-admin-docs"></i></a>';
			$controls_toggle = '<a class="db-control col-toggle" href="#" title="'.t('Toggle this row').'"><i class="admin-icon icon-admin-up-dir"></i></a>';
			$controls_code_view = '<a class="db-control col-codeview" href="#" title="'.t('Copy shortcode into your clipboard').'"><i class="admin-icon icon-admin-icon-embed"></i></a>';
			$controls_center_end = '</span>';

			$row_edit_clone_delete = '<span class="db-row-edit">';
			$row_edit_clone_delete .= $controls_delete . $controls_clone . $controls_edit . $controls_toggle . $controls_code_view;
			$row_edit_clone_delete .= '</span>';

			//$column_controls_full =  $controls_start. $controls_move . $controls_center_start . $controls_layout . $controls_delete . $controls_clone . $controls_edit . $controls_center_end . $controls_end;
			$column_controls_full =  $controls_start. $controls_move . $controls_center_start . $controls_layout . $controls_center_end . $row_edit_clone_delete .$controls_end;

			return $column_controls_full;
		}

		public function elementAdmin($atts, $content = null) {
			extract(shortcode_atts($this->predefined_atts, $atts));
			acquia_include('utility', 'ac_composer');
			acquia_include('process', 'ac_shortcode');
			$output = '';

			$column_controls = $this->getControls($this->settings('controls'));

			$classes = array_filter($this->getHolderClasses(), 'strlen');
			$classes = implode(' ', $classes);

			$output .= '<section data-sc="'.$this->settings["base"].'" class="'.$classes.'">';
			$output .= str_replace("%column_size%", 1, $column_controls);
			$output .= '<div class="db-visual-sc">';
			$output .= '<div class="db-row db_row_container db-parent">';
			if($content=='' && !empty($this->settings["default_content_in_template"])) {
				$output .= shortcode_unautop($this->settings["default_content_in_template"]);
			} else {
				$output .= shortcode_unautop($content);
			}
			$output .= '</div>';
			if ( isset($this->settings['params']) ) {
				$inner = '';
				foreach ($this->settings['params'] as $param) {
					$param_value = isset($param['param_name']) ? $param['param_name'] : '';
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
			$output .= '</section>';

			return $output;
		}
		public function customAdminBockParams() {
			return '';
		}
	}

	/**
	 * Class dbRowInnerView
	 */
	class dbRowInnerView extends dbRowView {
		protected function getFileName() {
			return 'ac_row';
		}
		public function template($content = '') {
			return $this->elementAdmin($this->atts);
		}
	}
}
