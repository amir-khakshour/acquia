<?php
/**
 * Expose page title section as context reactions.
 */
class ac_styles_reaction_ac_style extends context_reaction {
  /**
   * Allow admins to provide additional body classes.
   */
  function options_form($context) {
	ctools_include('plugins');
	$meta = !empty($context->reactions['ac_style']) ? $context->reactions['ac_style'] : array();
	$values = $this->fetch_from_context($context);
	foreach (array_keys(ac_styles_get_styles_plugins()) as $plugin_name) {
	  $plugin = ac_style_get_plugin($plugin_name, $meta);
	  $form = $plugin->style_form(array('parents' => array('reactions', 'plugins', 'ac_style', $plugin_name)));
	}
	return $form;
  }

  /**
   * Override of submit handler.
   */
//  function options_form_submit($values) {
//	$options = parent::options_form_submit($values);
//
//	foreach($values as $plugin_name => $_values) {
//	  if (isset($_values['enabled']) && $_values['enabled'] != 0) {
//		foreach ($_values as $key => $value) {
//		  if (is_array($value) || is_object($value)) {
//			if (isset($value['fid']) && $value['fid'] == 0) {
//			  unset($_values[$key]);
//			  continue;
//			}
//			$_values[$key] = serialize($value);
//		  }
//		}
//		$options[$plugin_name] = $_values;
//	  }else{
//		unset($options[$plugin_name]);
//	  }
//	}
//	return $options;
//  }

  /**
   * Set additional classes onto the 'body_classes'.
   */
  function execute(&$vars) {
	// Here we apply styles based on some priority as following:
	//  * 1st: node add/edit form styles settings
	//  * 2nd: node content type style settings from theme settings form @todo
	//  * 3rd: from current active context style settings
	//  in each case if we encounter an empty value we go to the next level.
	//  also we use default node title from node add/edit in the first priority.

	// Extract node styles meta

	$ac_styles = array();
	// 2nd priority
	foreach ($this->get_contexts() as $k => $v) {
	  if (!empty($v->reactions[$this->plugin])) {
		$ac_styles = $v->reactions[$this->plugin];
	  }
	}
	return $ac_styles;
  }

}
