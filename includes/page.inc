<?php
// $Id
/**
 * DiamondLayers normal page callbacks
 *
 */

/**
 * Main search function.
 * Started with: http://drupal.org/node/12668
 * Updated to be more similar to search_view
 */
function acquia_error404_page() {

   // Load the context
  $context = context_load(ACQUIA_CONTEXT_404_MN);
  context_set('context', "context_node", $context);
    
  $output = '<div id="ac-404-page" class="ac-404-page">';
  $output .='<h2 class="ac-404-title block__title">' .t(acquia_variable_get('404_page_title', '404 - not found')) .'</h2>';
  
  // Add custom text before the search form and results if custom text has been set
  $search404_page_text = acquia_variable_get('404_page_text', '');
  if (!empty($search404_page_text)) {
    $output .= '<div id="ac-404-text" class="ac-404-text"><div class="col-inner">' . check_markup($search404_page_text, 'full_html') . '</div></div>';
  }
  // @todo move to ui
  drupal_set_title(acquia_variable_get('404_page_title', t('Page not found')));
//  if (module_exists('search') && (user_access('search content') || user_access('search by page'))) {
//    $results = array();
//
//    // Get and use the default search engine for the site.
//    $default_search = search_get_default_module_info();
//    $type_search = $default_search['module'];
//
//      // Get the default search form
//    $form = drupal_get_form('search_form', NULL, $keys = NULL, $type_search);
//    $output .= '<div class="ac-col ac-one-half"><div class="col-inner">' .drupal_render($form) . drupal_render($results) . '</div></div>';
//  }
  // If the user does not have search permissions $output would be empty.
  if ($output == '') {
    $output .= t('The page you requested does not exist.');
  }
  
  $output .='</div>';
  return $output;
}