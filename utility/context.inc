<?php

/**
 * @file
 *
 * Contains routines to work with drupal Context module
 *
 */

/**
 * Return a formatted list of all contexts
 */
function acquia_get_contexts() {
  $contexts = context_enabled_contexts();
  ksort($contexts);
  $con = array();
  foreach ($contexts as $context) {
    $con[$context->name] = $context->name;

    $cons[] = $con;
  }

  return $con;
}

/**
 * Return a formatted list of all contexts
 */
function acquia_get_layout_contexts() {
  $con = &drupal_static(__FUNCTION__, NULL);

  if (!isset($con)) {
    $contexts = context_enabled_contexts();
    ksort($contexts);
    $con = array();
    foreach ($contexts as $context) {
      if($context->tag != 'DiamondLayers page layout') {
        continue;
      }
      $con[$context->name] = $context->name;

      $cons[] = $con;
    }
  }

  return $con;
}

/**
 * Return an option format list of all contexts
 */
function acquia_get_layouts_options() {
  $contexts = acquia_get_layout_contexts();
  foreach ($contexts as $layout => &$info) {
    $info = t(str_replace(array("-", "_"), " ", $info));
  }

  return $contexts;
}