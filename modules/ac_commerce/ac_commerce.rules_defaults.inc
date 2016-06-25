<?php
/**
 * @file
 * test.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ac_commerce_default_rules_configuration() {
  $items = array();
  $items['rules_apply_sale_price'] = entity_import('rules_config', '{ "rules_apply_sale_price" : {
      "LABEL" : "Apply Sale price",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Sale price" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : { "commerce_product_calculate_sell_price" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "commerce-line-item" ], "field" : "commerce_product" } },
        { "entity_has_field" : {
            "entity" : [ "commerce-line-item:commerce-product" ],
            "field" : "field_sale_price"
          }
        },
        { "NOT data_is_empty" : { "data" : [ "commerce-line-item:commerce-product:field-sale-price" ] } }
      ],
      "DO" : [
        { "commerce_line_item_unit_price_amount" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "amount" : [ "commerce-line-item:commerce-product:field-sale-price:amount" ],
            "component_name" : "discount",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  return $items;
}