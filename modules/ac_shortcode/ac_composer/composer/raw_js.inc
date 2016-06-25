<?php
/**
 * @file
 *  Diamond Builder settings for {{raw_js}} shortcode
 */
function ac_composer_raw_js_composer(){
	return array(
		'ac_raw_js' => array(
			'class' =>  'ac_raw_js_composerView',
			'category' => array(t('Structure')),
			"icon" => "sprite-js",
			"modal" => array(
				'modal_size' => 'small',
			),
			"show_settings_on_create" => TRUE,
			"params" => array(
				array(
					"type" => "textarea_raw_html",
					"holder" => "div",
					"heading" => __("Raw js", "js_composer"),
					"param_name" => "content",
					"value" => __(base64_encode("<script type='text/javascript'> alert('Enter your js here!'); </script>"), "js_composer"),
					"description" => __("Enter your JS code.", "js_composer")
				),
			),
		),
	);
}

// ac_row_composerView Class
if (class_exists('DiamondBuilderView')) {
	class ac_raw_js_composerView extends DiamondBuilderView {
		public function elementLabels($param, $value) {
			$output = '';
			// Compatibility fixes
			//TODO: check $old_names & &new_names. Leftover from copypasting?
			$old_names = array('yellow_message', 'blue_message', 'green_message', 'button_green', 'button_grey', 'button_yellow', 'button_blue', 'button_red', 'button_orange');
			$new_names = array('alert-block', 'alert-info', 'alert-success', 'btn-success', 'btn', 'btn-info', 'btn-primary', 'btn-danger', 'btn-warning');
			$value = str_ireplace($old_names, $new_names, $value);
			//$value = __($value, "js_composer");
			//
			$param_name = isset($param['param_name']) ? $param['param_name'] : '';
			$type = isset($param['type']) ? $param['type'] : '';
			$class = isset($param['class']) ? $param['class'] : '';

			if ( isset($param['holder']) == true && $param['holder'] != 'hidden' ) {
				if($param['type'] == 'textarea_raw_html')
					$output .= '<'.$param['holder'].' class="db-param-val ' . $param_name . ' ' . $type . ' ' . $class . '" name="' . $param_name . '">'.htmlentities(rawurldecode(base64_decode(strip_tags($value))), ENT_COMPAT, 'UTF-8' ).'</'.$param['holder'].'><input type="hidden" name="' . $param_name . '_code" class="' . $param_name . '_code" value="' .strip_tags($value) . '" />';
				else
					$output .= '<'.$param['holder'].' class="db-param-val ' . $param_name . ' ' . $type . ' ' . $class . '" name="' . $param_name . '">'.$value.'</'.$param['holder'].'>';
			}
			return $output;
		}
	}
}