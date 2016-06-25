<?php
/**
 * @file DiamondLayers Node meta inserting, Updating and querying
 */

 /**
 * Implements hook_node_load().
 *
 * Loads the node styles information if available for any of the nodes in the
 * argument list.
 */
function ac_get_node_meta($nid) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['cache'] = &drupal_static(__FUNCTION__, array());
  }
	$cache = &$drupal_static_fast['cache'];

	$nid = !is_array($nid) ? array($nid) : $nid;
	
	$cache_id = implode('|', $nid);
	if (!isset($cache[$cache_id])) {
		$where = 'nid IN (:nids)';
		$args = array(':nids' =>  $nid);
		$metas = array();
		
		$result = db_query("SELECT * FROM {".ACQUIA_NODE_META_TABLE."} WHERE ".$where."", $args, array('fetch' => PDO::FETCH_ASSOC));
		foreach ($result as $record) {
			$meta_value = @unserialize($record['meta_value']);
			if ($meta_value !== false) {
				$metas[$record['nid']][$record['meta_key']] = $meta_value;
			} else {
				$metas[$record['nid']][$record['meta_key']] = $record['meta_value'];
			}		
		}
		$cache[$cache_id] = $metas;
	}

  return $cache[$cache_id];
}

/**
 * Save/Update Node mata
 */
function ac_save_node_meta($node, $meta) {
	// Check first if this node has a saved rating.
	$old_meta = db_query("SELECT mid, meta_key FROM {".ACQUIA_NODE_META_TABLE."} WHERE nid = :nid",
	array(':nid' => $node->nid))
	->fetchAllAssoc('meta_key');
	
	$keys_to_delete = array();

	if (!is_array($meta)) {
		$meta = array($meta);
	}
	
	foreach($meta as $mkey => $value) {
		if (empty($value) || (is_array($value) && isset($value['fid']) && $value['fid'] == 0)) {
			$keys_to_delete [] = $mkey;
			continue;
		}
		
		if (is_array($value) || is_object($value)) {
			$value = serialize($value);
		}
		
		$rec = array(
			'nid' => $node->nid,
			'meta_key' => $mkey,
			'meta_value' => $value,
		);

		if (is_array($old_meta) && in_array($mkey, array_keys($old_meta))) {
			// do update
			$rec['mid'] = $old_meta[$mkey]->mid;
			drupal_write_record(ACQUIA_NODE_META_TABLE, $rec, 'mid');
		}else{
			// do save
			drupal_write_record(ACQUIA_NODE_META_TABLE, $rec);
		}
	}

	
	if (!empty($keys_to_delete)) {
    ac_delete_node_meta($node, $keys_to_delete);
	}
}


/**
 * Delete Node mata
 */
function ac_delete_node_meta($node, $meta = NULL) {
  $obj = db_delete(ACQUIA_NODE_META_TABLE)
  ->condition('nid', $node->nid);
  
  if (!empty($meta)) {
   $obj = $obj->condition('meta_key', $meta, 'IN');
  }
  
  $obj->execute();
}


/**
 * Get node meta from currently viewd node object
 *
 */
 function ac_get_node_meta_from_current() {
  $node_meta = &drupal_static(__FUNCTION__);
  
  if (!isset($node_meta)) {
    // Extract node styles meta
    $object = menu_get_object();
    
    if (isset($object->nid) && $object->nid > 0) {
      $node_meta = isset($object->nodemeta) ? $object->nodemeta : ac_get_node_meta($object->nid);
    }else {
      $node_meta = false;
    }
  }
  return $node_meta;
}