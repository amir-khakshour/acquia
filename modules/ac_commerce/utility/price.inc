<?php
/**
 * @file
 *
 */

/**
 * Formats a price for a particular currency.
 *
 * @param $amount
 *   A numeric price amount value.
 * @param $currency_code
 *   The three character code of the currency.
 * @param $object
 *   When present, the object to which the price is attached.
 * @param $convert
 *   Boolean indicating whether or not the amount needs to be converted to a
 *   decimal price amount when formatting.
 *
 * @return
 *   A fully formatted currency.
 */
function ac_commerce_currency_format($amount, $currency_code, $object = NULL, $convert = TRUE, $display_type = 'teaser_view') {
  // First load the currency array.
  $currency = commerce_currency_load($currency_code);

  // Then convert the price amount to the currency's major unit decimal value.
  if ($convert == TRUE) {
    $amount = commerce_currency_amount_to_decimal($amount, $currency_code);
  }

  // Invoke the custom format callback if specified.
  if (!empty($currency['format_callback'])) {
    return $currency['format_callback']($amount, $currency, $object);
  }

  // Format the price as a number.
  $price = number_format(commerce_currency_round(abs($amount), $currency), $currency['decimals'], $currency['decimal_separator'], $currency['thousands_separator']);
  // Establish the replacement values to format this price for its currency.
  $replacements = array(
    '@code_before' => $currency['code_placement'] == 'before' ? $currency['code'] : '',
    '@symbol_before' => $currency['symbol_placement'] == 'before' ? $currency['symbol'] : '',
    '@price' => $price,
    '@symbol_after' => $currency['symbol_placement'] == 'after' ? $currency['symbol'] : '',
    '@code_after' => $currency['code_placement'] == 'after' ? $currency['code'] : '',
    '@negative' => $amount < 0 ? '-' : '',
    '@symbol_spacer' => $currency['symbol_spacer'],
    '@code_spacer' => $currency['code_spacer'],
  );
  if ($display_type == 'node_view') {
    $replacements['!code_before'] = '';
    if (!empty($replacements['@code_before'])) {
      $replacements['!code_before'] = '<i>' .$replacements['@code_before'] . '</i>';
    }
    $replacements['!symbol_before'] = '';
    if (!empty($replacements['@symbol_before'])) {
      $replacements['!symbol_before'] = '<sup>' .$replacements['@symbol_before'] . '</sup>';
    }
    $replacements['!price'] = '<span>' .$currency['code'].' '.$price . '</span>';
    return trim(t('!code_before@code_spacer@negative!symbol_before!price@symbol_spacer@symbol_after@code_spacer@code_after', $replacements));
  }else{
    return trim(t('@code_before@code_spacer@negative@symbol_before@price@symbol_spacer@symbol_after@code_spacer@code_after', $replacements));
  }
}