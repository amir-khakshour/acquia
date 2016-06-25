<?php
/**
 * @file
 * Contains general utility functions for acquia styles that do not need to be
 * in the module file.
 *
 */


/**
 * get region machine name by region alias
 * 	@todo move it to UI
 */
function ac_styles_get_regions_mn_by_alias($alias = null) {
	
  $regions = array(
    'title section' => 'highlighted',
  );
  
  return isset($regions[$alias]) ? $regions[$alias] : false;
}

/**
 *
 */
function ac_styles_merge_nodemeta_by_context($context) {
  $styles = &drupal_static(__FUNCTION__, array());
  
  if (!isset($styles[$context])) {
		acquia_include('meta');
    $node_meta = ac_get_node_meta_from_current();

		$context_meta = array();
    if ($plugin = context_get_plugin('reaction', $context))  {
      $context_meta = $plugin->execute($vars);
    }
		// unserialize styles
    if (!empty($node_meta) || !empty($context_meta)) {
      $styles[$context] = array_replace_recursive((array)$context_meta, (array)$node_meta);
    }else {
     $styles[$context] = null;
    }
    
  }
  return $styles[$context];
}