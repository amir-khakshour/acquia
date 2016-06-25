<?php
/**
 * @file
 *  options helper functions 
 */

/**
 * Get list of supported image frames
 */
function ac_portfolio_get_recent_items($settings = array()) {
  $cache = &drupal_static(__FUNCTION__, NULL);
  $total = isset($settings['total']) ? (int)$settings['total'] : acquia_variable_get('portfolio_recent_total', -1);
  $num_per_page = isset($settings['num_per_page']) ? (int)$settings['num_per_page'] : acquia_variable_get('portfolio_num_per_page', 12);

  if (!isset($cache[$settings['id']])) {
    
    // filter by term
    $valid_nids = -1;
    if ($settings['term'] != '*') {
      $nids_query = db_select('taxonomy_index', 'ti');
            
      $nids_query
        ->fields('ti', array('nid'))
        ->condition('ti.tid', intval($settings['term']));
        
      $nids = $nids_query->execute()
       ->fetchAllAssoc('nid');
      $valid_nids = array_keys($nids);
      // correct pager values
      //if ($num_per_page > 0 && count($valid_nids) < $num_per_page) {
      //  $total = count($valid_nids);
      //  $num_per_page = count($valid_nids);
      //}
    }
    
    if ($num_per_page >0) {
      $query = db_select('node', 'n')
        ->extend('PagerDefault');
    }else {
      $query = db_select('node', 'n');
    }
    
    $sortBy = $settings['sort'] == 'date' ? 'created' : 'title';
    $sortType = strtolower($settings['order']) == 'desc' ? 'DESC' : 'ASC';
    
    $query
      ->fields('n')
      ->orderBy($sortBy, $sortType);
      
    // Get node view counter
    if (module_exists('statistics')) {
      $query->leftJoin('node_counter', 'nc', 'nc.nid = n.nid');
      $query->fields('nc', array('totalcount'));
    }

    // if pager enabled
    if ($num_per_page >0) {
      if ($total == -1) {
        $total_query = db_select('node', 'n')->orderBy('created', 'DESC');
        $total_query->addExpression('COUNT(n.nid)', 'nids');
        $total_query
         ->condition('n.status', 1)
         ->condition('n.type', AC_PORTFOLIO_MN);
         
        $total = $total_query->execute()->fetchAll(PDO::FETCH_ASSOC);
        $total = $total[0]['nids'];
      }

      $query->limit($num_per_page);
    }elseif ($total >0){
      $query->range(0, $total);
    }
    
    $query
     ->condition('n.status', 1)
     ->condition('n.type', AC_PORTFOLIO_MN);

    $nodes = $query->execute()
    ->fetchAllAssoc('nid', PDO::FETCH_ASSOC);
    if (empty($nodes)) {
      return array();
    }

    // All nodes
    $all_nids = array_keys($nodes);

    // remove unfiltered nodes
    if ($valid_nids >0) {
      foreach($all_nids as $nid) {
        if (!in_array($nid, $valid_nids)) {
          unset($nodes[$nid]);
        }
      }
    }

    
    // Extract Terms
    if ($settings['tags'] || $settings['sorting']) {
      $query = db_select('taxonomy_index', 'ti');
      
      $query->join('taxonomy_term_data', 'td', 'td.tid = ti.tid');
      
      $query
       ->fields('ti')
       ->fields('td');
       
      $query
        ->condition('ti.nid', $all_nids, 'IN');
        
      $terms = $query->execute()
       ->fetchAll(PDO::FETCH_ASSOC);
       
      foreach($terms as $term) {
        if (!isset($nodes[$term['nid']])) {
          continue;
        }
        $nodes[$term['nid']]['terms'][$term['tid']] = $term['name'];
      }
    }
  
    // extract metas
    $query = db_select('acquia_node_meta', 'nm')
    ->fields('nm');
    
    $query
      ->condition('nm.nid', $all_nids, 'IN')
      ->condition('nm.meta_key', array('thumb', 'preview', 'misc'), 'IN');
    
    $metas = $query->execute()
    ->fetchAll(PDO::FETCH_ASSOC);
    
    foreach($metas as $meta) {
      if (!isset($nodes[$meta['nid']])) {
        continue;
      }
      $nodes[$meta['nid']][$meta['meta_key']] = unserialize($meta['meta_value']);
    }
    $cache[$settings['id']] = $nodes;
  }
  // attach the pager theme
  if ($num_per_page > 0 && $total > $num_per_page) {
    $build['pager_pager'] = theme('pager', array('style' => $settings['filter_style']));
  }else{
    $build['pager_pager'] = '';
  }

  $build['pager_nodes'] = $cache[$settings['id']];
  return $build;
}

/**
 * Get list of supported image frames
 */
function ac_portfolio_get_related_items($node, $reset = FALSE) {
  $cache = &drupal_static(__FUNCTION__, array());
  if ($reset) {
    $cache = array();
  }
  
  if (!isset($cache[$node->nid])) {
    $terms = ac_portfolio_get_category_tids($node);
    
    if (empty($terms)) {
      return array();
    }
    
    $query = db_select('node', 'n')
    ->fields('n')
    ->distinct();
    
    $query->join('taxonomy_index', 't', 't.nid = n.nid');
    
    $query
      ->condition('n.nid', $node->nid, '<>')
      ->condition('n.type', $node->type)
      ->condition('n.status', 1)
      ->condition('t.tid', $terms, 'IN')
      ->range(0, acquia_variable_get('portfolio_related_nums', 8));
      
    $nodes = $query->execute()
    ->fetchAllAssoc('nid', PDO::FETCH_ASSOC);
    
    if (empty($nodes)) {
      $cache[$node->nid] = array();
    }else {
     
      if (!acquia_variable_get('portfolio_related_no_tags', TRUE)) {
        // Extract Terms
        $query = db_select('taxonomy_index', 'ti');
        
        $query->join('taxonomy_term_data', 'td', 'td.tid = ti.tid');
        
        $query
         ->fields('ti')
         ->fields('td');
         
        $query
          ->condition('ti.nid', array_keys($nodes), 'IN');
          
        $terms = $query->execute()
         ->fetchAll(PDO::FETCH_ASSOC);
         
        foreach($terms as $term) {
          if (!isset($nodes[$term['nid']])) {
            continue;
          }
          $nodes[$term['nid']]['terms'][$term['tid']] = $term['name'];
        }
      }
      
      // extract metas
      $query = db_select('acquia_node_meta', 'nm')
      ->fields('nm');
      
      $query
        ->condition('nm.nid', array_keys($nodes), 'IN')
        ->condition('nm.meta_key', array('thumb', 'preview', 'misc'), 'IN');
    
      $metas = $query->execute()
      ->fetchAll(PDO::FETCH_ASSOC);
      
      foreach($metas as $meta) {
        if (!isset($nodes[$meta['nid']])) {
          continue;
        }
        $nodes[$meta['nid']][$meta['meta_key']] = unserialize($meta['meta_value']);
      }
      
      $cache[$node->nid] = $nodes;
    }
  }
  
  return $cache[$node->nid];
}

