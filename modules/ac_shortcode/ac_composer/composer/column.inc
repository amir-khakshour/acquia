<?php
/**
 * @file
 *  Diamond Builder settings for {{ac_col}} and {{ac_col_inner}} shortcode
 */
function ac_composer_column_composer(){
	return array(
		'ac_col' => array(
			'class' =>  'dbColumnView',
			"is_container" => TRUE,
			'header_title' => FALSE,
			"content_element" => FALSE,
			"views" => 'DiamondBuilderColumnView',
			"modal" => array(
				'modal_size' => 'small',
			),
		),
		'ac_col_inner' => array(
			'class' =>  'dbColumnInnerView',
			"icon" => "",
			"wrapper_class" => "",
			"controls"	=> "full",
			"content_element" => FALSE,
			"is_container" => TRUE,
			'header_title' => FALSE,
			"views" => 'DiamondBuilderColumnView',
			"modal" => array(
				'modal_size' => 'small',
			),
		),
	);
}

// Composer View Class
if (class_exists('DiamondBuilderContainerView')) {
	class dbColumnView extends DiamondBuilderContainerView {
		protected  $predefined_atts = array(
			'el_class' => '',
			'el_position' => '',
			'width' => '1/1'
		);

		public function getControls($controls, $extended_css = '') {
			$controls_start = '<div class="db-controls db-controls-column'.(!empty($extended_css) ? " {$extended_css}" : '').'">';
			$controls_end = '</div>';

			if ($extended_css=='bottom-controls') $control_title = __('Append to this column', 'js_composer');
			else $control_title = __('Prepend to this column', 'js_composer');

			$controls_add = ' <a class="db-control col-add" href="#" title="'.$control_title.'"><i class="admin-icon icon-admin-plus"></i></a>';
			$controls_edit = ' <a class="db-control col-edit" href="#" title="'.__('Edit this column', 'js_composer').'"><i class="admin-icon icon-admin-pencil"></i></a>';

			return $controls_start .  $controls_add . $controls_edit . $controls_end;
		}

		protected function getHolderClasses() {
			$classes = parent::getContainerClasses();
			$classes[] = 'db_content_holder';
			$classes[] = '<%= window.vc_convert_column_size(params.width) %>';
			return $classes;
		}

		public function containerAttributes() {
			$attrs['class'] = array('db-column-container');
			$attrs['class'][] = 'db-parent';
			return $attrs;
		}

		protected function getContainerClasses() {
			$classes = parent::getContainerClasses();
			$classes[] = 'db-visual-col';
			return $classes;
		}
	}

	// Composer View Class
	class dbColumnInnerView extends dbColumnView {
		protected function getFileName() {
			return 'ac_col';
		}
	}

}