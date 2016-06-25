<?php
/**
 * @file
 * Contains helper functions to build and override theme functions
 */

/**
 * Implements hook_theme().
 */
function ac_commerce_theme() {
  $path = drupal_get_path('module', 'ac_commerce') . '/theme';

  return array(
    'ac_commerce_price_formatted_sale' => array(
      'variables' => array('prices' => array(), 'price_direction' => NULL),
      'file' => 'includes/theme.inc',
    ),
    'ac_commerce_price_formatted_sale_inline' => array(
      'variables' => array('prices' => array(), 'price_direction' => NULL),
      'file' => 'includes/theme.inc',
    ),
    'ac_commerce_quantity_plusminus' => array(
      'render element' => 'form',
      'file' => 'includes/theme.inc',

    ),
    'ac_commerce_quantity_plusminus_link' => array(
      'variables' => array('way' => NULL, 'quantity' => NULL, 'quantity_input_element' => NULL),
      'file' => 'includes/theme.inc',
    ),
    'ac_commerce_brand_info' => array(
      'variables' => array('term' => NULL, 'language' => 'und'),
      'template' => 'ac-commerce-brand-info',
      'path' => $path,
    ),
  );
}


function ac_commerce_preprocess_ac_commerce_brand_info(&$vars) {
  if (isset($vars['term']->field_image[$vars['language']][0])) {
    acquia_include('media');
    $image = $vars['term']->field_image[$vars['language']][0];
    $media = array('fid' => $image['fid'], 'style' => array('image_style' => variable_get('ac_commerce_brand_image_style', 'equal-width-t')));
    $vars['image'] = acquia_image_format_simple($media);
  }
}

/**
 * Returns HTML for quantity textfield having links wrapping the textfield.
 */
function theme_ac_commerce_quantity_plusminus($variables) {
  $decrease = theme('ac_commerce_quantity_plusminus_link', array('way' => COMMERCE_EXTRA_QUANTITY_DECREASE, 'quantity' => $variables['form']['#value'], 'quantity_input_element' => $variables['form']['#id']));
  $increase = theme('ac_commerce_quantity_plusminus_link', array('way' => COMMERCE_EXTRA_QUANTITY_INCREASE, 'quantity' => $variables['form']['#value'], 'quantity_input_element' => $variables['form']['#id']));
  return $decrease . $variables['form']['#children'] . $increase;
}


/**
 * Returns HTML for link which increases/decreases quantity value.
 */
function theme_ac_commerce_quantity_plusminus_link($variables) {
  switch ($variables['way']) {
    case COMMERCE_EXTRA_QUANTITY_DECREASE:
      $text = '-';
      $class = 'quantity-minus';
      $js_callback = "Drupal.commerce_extra_quantity_quantity('#" . $variables['quantity_input_element'] . "', " . $variables['way'] . ")";
      break;
    case COMMERCE_EXTRA_QUANTITY_INCREASE:
      $text = '+';
      $class = 'quantity-up';
      $js_callback = "Drupal.commerce_extra_quantity_quantity('#" . $variables['quantity_input_element'] . "', " . $variables['way'] . ")";
      break;
  }
  if ($variables['quantity'] <= 1) {
    $class .= ' disabled';
  }
  $options = array(
    'attributes' => array('class' => 'button', 'onclick' => $js_callback . '; return false;'),
    'html' => FALSE,
  );
  $element = array(
    '#theme' => 'link',
    '#text' => $text,
    '#path' => current_path(),
    '#options' => $options,
  );
  return render($element);
}



/**
 * Theme callback: display prices in a table.
 */
function theme_ac_commerce_price_formatted_sale($vars) {
  // Build an array of table rows based on the prices passed in.
  $rows = array();

  // exit if no prices
  if (empty($vars['prices'])) {
    return '';
  }

  // store prices count
  $prices_count = count($vars['prices']);

  // extract price direction
  $price_direction = !empty($vars['price_direction']) ? $vars['price_direction'] . ' sale' : 'unchanged';

  // build rows individually
  $output = '<div class="global-price price-'.$price_direction.' price-count-'.$prices_count.'">';
  $price = $vars['prices']['price'];
  unset($vars['prices']['price']);
  $output .= '<div class="price-price">' . drupal_render($price) . '</div>';

  if (count($vars['prices'])) {
    $output .= '<span class="prices-meta">';
    foreach ($vars['prices'] as $key => $price_element) {
      $output .= '<span class="price-'.$key.'">' . drupal_render($price_element) . '</span>';
    }
    $output .= '</span>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Theme callback: display prices as a list.
 */
function theme_ac_commerce_price_formatted_sale_inline($vars) {
  // Build an array of table rows based on the prices passed in.
  $rows = array();

  // exit if no prices
  if (empty($vars['prices'])) {
    return '';
  }

  // store prices count
  $prices_count = count($vars['prices']);

  // extract price direction
  $price_direction = !empty($vars['price_direction']) ? $vars['price_direction'] . ' sale' : 'unchanged';

  // build rows individually
  $output = '<div class="global-price global-price-inline price-'.$price_direction.'">';
  foreach ($vars['prices'] as $key => $price_element) {
    $output .= '<span class="price-'.$key.'">' . drupal_render($price_element) . '</span>';
  }
  $output .= '</div>';

  return $output;
}


/**
 * Implements hook_preprocess_node()
 */
function ac_commerce_preprocess_node(&$vars){
  // Share links
  if ($vars['view_mode'] == 'full') {
    $vars['share_links'] = theme('acquia_share_links', array('node' => $vars['node'], 'socials' => array_filter(array_values(variable_get('ac_commerce_share_links', array())))));
  }
}


/**
 * Add more variables to shopping cart block.
 *
 * Default template: ajax-shopping-cart.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - order: Order object of the current user.
 *   - line_items: Line items wrapper.
 *   - quantity: Number of items in the cart.
 *   - total: Array containing the total amount and the default currency you
 *     are in the site.
 */
function ac_commerce_preprocess_dc_ajax_shopping_cart(&$vars) {
  dpm($vars);
  if (isset($vars['checkout_url'])){
    $vars['checkout_link']['attributes']['class'] = array_merge($vars['checkout_link']['attributes']['class'], array(
      'ac-button',
      'ac-style-sw',
      'ac-type-sw',
      'ac-bg_color-sw',
      'ac-block_level-true')
    );
    $vars['checkout_url'] = l($vars['checkout_link']['text'], $vars['checkout_link']['path'], array(
      'attributes' => $vars['checkout_link']['attributes'],
      'query' => $vars['checkout_link']['query'],
      'fragment' => $vars['checkout_link']['fragment'],
      'html' => $vars['checkout_link']['html'],
    ));
  }
}
