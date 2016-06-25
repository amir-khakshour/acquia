<?php
/**
 * @file working with drupal taxonomy objects
 */

/**
 * Get available vocabularies in an array as an form select options
 */
function ac_get_taxonomies_option(){
  $cache = &drupal_static(__FUNCTION__, NULL);

  if (!isset($cache)) {
    foreach (taxonomy_get_vocabularies() as $vocab) {
      $cache[$vocab->machine_name] = t($vocab->name);
    }   
  }

  return $cache;
}

/**
 *
 */
function ac_get_all_terms(){
  $cache = &drupal_static(__FUNCTION__, array());
  
  if (!isset($cache)) {
   $vocabularies = taxonomy_get_vocabularies();
   
   foreach ($vocabularies as $vocab) {
     $terms = taxonomy_get_tree($vocab->vid,  0, -1, 1);
     foreach($terms as $term){
       $items[]= l($term->name, "taxonomy/term/$term->tid");
       }
     }
   
    if(count($items)) {
      return theme('item_list', $items);
    }
  }

}

/**
 * get vocabulary id by name
 */
function _ac_get_taxonomy_vid_by_name($name){
  $vocabulary  = taxonomy_vocabulary_machine_name_load($name);
  if (is_object($vocabulary) && isset($vocabulary->vid)) {
    return $vocabulary->vid;
  }
  return 0;
}



/**
 * Remove taxonomy by name
 * @param {string}  $name
 *   taxonomy name to be deleted
 */
function _ac_remove_taxonomy_by_name($name, $t = NULL) {
  $t = !is_null($t) ? $t : get_t();
  $vocabulary  = taxonomy_vocabulary_machine_name_load($name);
  if (is_object($vocabulary) && isset($vocabulary->vid)) {
    $status = taxonomy_vocabulary_delete($vocabulary->vid);
    $t_args = array('%name' => $vocabulary->name);
   if ($status == SAVED_DELETED) { // Successfully delete
     drupal_set_message($t('The %name taxonomy has been deleted!', $t_args));
   }else{
     drupal_set_message(t('There was an error deleting %name taxonomy.', $t_args));
   } 
  }else{
    //drupal_set_message(t('There was an error deleting %name taxonomy.', $vocabulary->name));
  }
}