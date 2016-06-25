<?php
/**
 * Basic class for acquia styles plugin.
 *
 * All Example operation classes should inherit this basic class.
 */
abstract class acquia_styles {

  // style form values
  protected $form;
  protected $form_state;
  protected $values;

  /**
   * Save arguments locally.
   */
  function __construct($values) {
    $this->values = $values;
  }

  /**
   * Validate style form
   */
  public function style_form_validate() {}

  /**
   * get style form
   */
  public function get_style_form() {
   
  }

  /**
   * style form defenition
   */
  public function style_form() {
  }
}