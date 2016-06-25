<?php
/**
 *
 */

/**
 * @TODO Get blog Cateogries from node
 */
function ac_blog_get_category_tids($node) {
  if (!is_object($node) && isset($node->nid)) {
    $node = node_load($node->nid);
  }
  $tids = array();
  $terms = field_get_items('node', $node, AC_BLOG_CAT_FIELD);
  if (is_array($terms)) {
    foreach ($terms as $term) {
      $tids[] = $term['tid'];
    }
  }
  return $tids;
}

/**
 * Get recent blog items
 */
function ac_blog_get_recent_items($settings = array()) {
  $cache = &drupal_static(__FUNCTION__, NULL);

  $total = isset($settings['total']) ? (int)$settings['total'] : acquia_variable_get('blog_recent_total', -1);
  $num_per_page = isset($settings['num_per_page']) ? (int)$settings['num_per_page'] : acquia_variable_get('blog_num_per_page', 12);
    
  if (!isset($cache[$settings['id']])) {
    $query = db_select('node', 'n')
     ->extend('PagerDefault')
      ->fields('n')
      ->orderBy('created', 'DESC');

    // if pager enabled
    if ($num_per_page >0) {
      $query->limit($num_per_page);
    }
    
    $query
     ->condition('n.status', 1)
     ->condition('n.type', 'blog');

    // Extract Comment Count
    $query->leftJoin('comment', 'c', 'c.nid = n.nid');
    $query->addExpression('COUNT(c.cid)', 'comments');
    $query->groupBy('n.nid');
    
    // Extract User Picture
    $query->leftJoin('users', 'u', 'u.uid = n.uid');
    $query->fields('u', array('picture'));

    $nodes = $query->execute()
    ->fetchAllAssoc('nid', PDO::FETCH_ASSOC);
    if (empty($nodes)) {
      return array();
    }
    
    // Extract just the chunk we needed
    if ($total >0 && count($nodes) > $total) {
     $i =-1;
     foreach ($nodes as $id => $node) {
       $i++;
       if ($i < $total) {
         continue;
       }
       unset($nodes[$id]);
     }
    }

    if ($settings['tags'] == TRUE) {
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
        $nodes[$term['nid']]['terms'][$term['vid']][$term['tid']] = $term['name'];
      }
    }
    
    //// extract comment count
    //$query = db_select('comment', 'c')->orderBy('created', 'DESC');
    //$query->addExpression('COUNT(n.nid)', 'nids');
    
    // extract metas
    $query = db_select('acquia_node_meta', 'nm')
    ->fields('nm');
    
    $query
      ->condition('nm.nid', array_keys($nodes), 'IN')
      ->condition('nm.meta_key', array('thumb', 'misc'), 'IN');
    
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
  $build['pager_nodes'] = $cache[$settings['id']];
  if ($num_per_page > 0) {
    $build['pager_pager'] = theme('pager');
  }
  return $build;
}

/**
 * Get related blog items
 */
function ac_blog_get_related_items($node, $reset = FALSE) {
  $cache = &drupal_static(__FUNCTION__, array());
  if ($reset) {
    $cache = array();
  }
  
  if (!isset($cache[$node->nid])) {
    $terms = ac_blog_get_category_tids($node);
    
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
      ->range(0, acquia_variable_get('related_news_nums', 8));
      
    $nodes = $query->execute()
    ->fetchAllAssoc('nid', PDO::FETCH_ASSOC);
    
    if (empty($nodes)) {
      $cache[$node->nid] = array();
    }else {
     
      // Extract Terms
      $query = db_select('taxonomy_index', 'ti');
      
      $query->join('taxonomy_term_data', 'td', 'td.tid = ti.tid');
      
      $query
       ->fields('ti')
       ->fields('td');
      $query
        ->condition('ti.nid', array_keys($nodes) + array($node->nid), 'IN')
        ->condition('td.tid', $terms, 'IN');

      $terms = $query->execute()
       ->fetchAll(PDO::FETCH_ASSOC);

      foreach($terms as $term) {
        if (!isset($nodes[$term['nid']])) {
          continue;
        }
        $nodes[$term['nid']]['terms'][$term['vid']][$term['tid']] = $term['name'];
      }
      
      // extract metas
      $query = db_select('acquia_node_meta', 'nm')
      ->fields('nm');
      
      $query
        ->condition('nm.nid', array_keys($nodes), 'IN')
        ->condition('nm.meta_key', array('thumb', 'misc'), 'IN');
    
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
