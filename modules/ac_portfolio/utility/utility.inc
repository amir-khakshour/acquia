<?php
/**
 *
 */

/**
 * Get the total count of items flagged within a flag.
 *
 * @param $nid
 *   The node id of entity.
 * @param $reset
 *   (optional) Reset the internal cache and execute the SQL query another time.
 */
function ac_portfolio_get_likes_counts($nid, $reset = FALSE) {
  $counts = &drupal_static(__FUNCTION__, array());
  if ($reset) {
    $counts = array();
  }
  if (!isset($counts[$nid])) {
    $flag = flag_get_flag(AC_PORTFOLIO_LIKE_FLAG_MN);
    $counts[$nid] = db_select('flag_counts', 'fc')
      ->fields('fc', array('count'))
      ->condition('fid', $flag->fid)
      ->condition('entity_type', 'node')
      ->condition('entity_id', $nid)
      ->execute()
      ->fetchField();
  }
  return $counts[$nid];
}

/**
 * @TODO document here
 */
function ac_portfolio_get_preview_media_from_meta($meta) {
  $vars = array();
  if (isset($meta['preview']['use_thumb']) && $meta['preview']['use_thumb'] == 1) {
    if ($meta['thumb']['type'] == 'video') {
      $vars['media_type'] = $meta['thumb']['type'];
    }else {
      $vars['media_type'] = 'image';
    }
    $vars['items'] = $meta['thumb']['media'];
  }else if (isset($meta['preview'])){
    $vars['items'] = $meta['preview']['media'];
    $vars['media_type'] = $meta['preview']['type'];
  }
  $vars['view'] = isset($meta['misc']['view']) ? $meta['misc']['view'] : 'list';
  
  if (isset($meta['misc']['custom_frame']) && $meta['misc']['custom_frame']) {
    $vars['frame'] = $meta['misc']['frame'];
  }
  
  return $vars;
}

/**
 * @TODO Get Portfolio Cateogries from node
 */
function ac_portfolio_get_category_tids($node) {
  if (!is_object($node) && isset($node->nid)) {
    $node = node_load($node->nid);
  }
  $tids = array();
  $terms = field_get_items('node', $node, AC_PORTFOLIO_FIELD);
  if (is_array($terms)) {
    foreach ($terms as $term) {
      $tids[] = $term['tid'];
    }
  }

  return $tids;
}

/**
 *
 */
function ac_portfolio_extract_meta(&$meta){
  foreach ($meta as $key => $values) {
    if (!is_array($values)) {
      unserialize($values);
    }
  }
}

/**
 *
 */
function ac_portfolio_get_all_tags(){
  if (!module_exists('tagclouds')){
    drupal_set_message(t('AcquiaPortfolio: !module module need to be installed and enabled in order to get tags!', array('!module' => l('tagcloud', 'https://www.drupal.org/project/tagclouds'))), 'error');
    return array();
  }
  acquia_include('taxonomy');
  $vid = _ac_get_taxonomy_vid_by_name(AC_PORTFOLIO_TAX_MN);
  return tagclouds_get_tags(array($vid));
}
