<?php
// $Id
/**
 * @file
 *  
 */

 /**
  *
  */
function acquia_add_grid_attributes($settings, &$vars){
  $vars['data-columns'] = isset($settings['columns']) ? $settings['columns'] : 4;
  $vars['data-padding'] = isset($settings['padding']) ? $settings['padding'] : 0;
  $vars['class'][] = 'ac-appearance-grid';
}
