<?php

/**
 * Form builder; Configure acquia blog settings.
 *
 * @ingroup forms
 */
function ac_store_settings($form, &$form_state) {
  acquia_include('taxonomy');
  acquia_include('options');
  acquia_include('context');
  acquia_include('theme');

  // wrap acquia options style
  acquia_theme_wrap_acquia_admin_style($form, array('vtabs' => TRUE));
  acquia_load_resources();

  $form['ac_store_vtabas'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('General settings'),
  );

  // Default blog context
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#group' => 'ac_store_vtabas',
  );

  $form['general']['ac_ubercart_product_carousel_thumb_style'] = array(
    '#type' => 'select',
    '#title' => t('Product carousel - image thumbnail style'),
    '#options' => image_style_options(),
    '#default_value' => acquia_variable_get('ubercart_product_carousel_thumb_style', NULL),
  );

  // Default blog context
  $form['product_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Product Page'),
    '#group' => 'ac_store_vtabas',
  );

  $form['product_page']['ac_commerce_product_page_show_brand_info'] = array(
    '#title' => t('Display brand info?'),
    '#type' => 'checkbox',
    '#description' => t ( 'Display brand info on product page?' ),
    '#default_value' => acquia_variable_get('ac_commerce_product_page_show_brand_info', TRUE),
  );

  $form['product_page']['ac_commerce_brand_field'] = array (
    '#type' => 'textfield',
    '#title' => t('brand field name'),
    '#description' => t ( 'Machine name of brand field to extract.' ),
    '#default_value' => acquia_variable_get('ac_commerce_brand_field', 'field_brand'),
    '#states' => array(
      'visible' => array(
        ':input[name="ac_commerce_product_page_show_brand_info"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['product_page']['ac_commerce_brand_image_style'] = array (
    '#type' => 'select',
    '#title' => t('brand field name'),
    '#options' => image_style_options(),
    '#description' => t ( 'Machine name of brand field to extract.' ),
    '#default_value' => acquia_variable_get('ac_commerce_brand_image_style', 'equal-width-t'),
    '#states' => array(
      'visible' => array(
        ':input[name="ac_commerce_product_page_show_brand_info"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Default blog context
  $form['Social'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social'),
    '#group' => 'ac_store_vtabas',
  );
  $form['Social']['ac_commerce_share_links'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Share links'),
    '#description' => t('select share links to display on product page.'),
    '#options' => acquia_social_icons(),
    '#default_value' => acquia_variable_get('ac_commerce_share_links', array()),
  );

  // Default blog context
  $form['related_products'] = array(
    '#type' => 'fieldset',
    '#title' => t('Related Products'),
    '#group' => 'ac_store_vtabas',
  );

  // Catalog
  $form['catalog_terms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Catalog terms'),
    '#group' => 'ac_store_vtabas',
  );

  // Catalog
  $form['catalog_products'] = array(
    '#type' => 'fieldset',
    '#title' => t('Catalog products'),
    '#group' => 'ac_store_vtabas',
  );

  // This form allows page compression settings to be changed, which can
  // invalidate the page cache, so it needs to be cleared on form submit.
  //$form['#submit'][] = 'acquia_clear_cache_submit';
  $form = system_settings_form($form);
  return $form;
}
