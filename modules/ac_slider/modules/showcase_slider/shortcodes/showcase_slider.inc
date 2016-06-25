<?php
/**
 * @file shortcode defenition of audio
 */
/**
 * Implements ac_shortcode_SHORTCODE_shortcode()
 * @return an array of shortcodes defenition
 *
 * 	Shortcode settings array consists of below values:
 * 	 %tag : Shortcode tag
 * 	 %title: Shortcode title
 * 	 %description: Shortcode description
 * 	 %category: An array of categories that this shortcode belongs to
 * 	 %class: A class name that contains methods to process the tag
 * 	 %file: Shortcode class file name
 * 	 %path: Relative path to shortcode class file
 * 	 %nested shortcodes: Array of shortcode tags that can be nested
 *    	in this shortcode and processed as a value of current shortcode
 * 	 %hidden: A Boolean value indicating whether this shortcode must
 *    	be hidden in the shortcodes list or not. it works in conjunction
 *    	with %enabled key.
 * 	 %enabled: Array of shortcode tags and a Boolean value that represents
 *    	the circumstances that the shortcode can be enabled based on the
 *    	status of other shortcodes.
 */

function showcase_slider_showcase_slider_shortcode() {
  return array(
      'showcase_slider' => array(
          'title' => t('Showcase slider'),
          'description' => t('Display showcase slider in post'),
          'form callback' => 'ac_shortcode_showcase_slider_form',
          'values process callback' => 'ac_shortcode_showcase_slider_preprocess',
          'process callback' => 'ac_shortcode_showcase_slider_process',
      ),
  );
}

/**
 * Implements edit form of {{showcase_slider}} shortcode
 */
function ac_shortcode_showcase_slider_form($form, &$form_state) {
  acquia_include('utility', 'ac_slider');
  $values = isset($form_state['values']) ? $form_state['values'] : array();

  $form['id'] = array (
      '#type' => 'select',
      '#title' => t('Slider'),
      '#description' => t('please select your slider to be placed into your post from the list.'),
      '#default_value' => isset($values['id']) ? $values['id'] : '',
      '#options' => get_sliders_by_type(showcase_slider_MN),
  );

  $form['no_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide Title?'),
      '#default_value' => isset($values['no_title']) && $values['no_title'] == 'true' ? TRUE : FALSE,
  );

  $form['custom_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Custom title?'),
      '#default_value' => isset($values['block_title']) && !empty($values['block_title']) ? TRUE : FALSE,
  );

  $form['block_title'] = array (
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#description' => t ( 'Enter the custom title to be placed before slider.' ),
      '#default_value' => isset($values['block_title']) ? $values['block_title'] : '',
      '#states' => array(
          'visible' => array(
              ':input[name="custom_title"]' => array('checked' => TRUE),
          ),
      ),
  );

  /** Global shortcode elements **/
  $form['class'] = array(
      '#type' => 'textfield',
      '#title' => t('Extra class name'),
      '#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
      '#default_value' => isset($values['class']) ? $values['class'] : '',
  );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('submit'),
  );

  return $form;
}

/**
 * Process {{showcase_slider}} shortcode values before making shortcode string
 */
function ac_shortcode_showcase_slider_preprocess(&$values) {
  unset($values['custom_title']);
  if (isset($values['no_title']) && $values['no_title'] == TRUE) {
    $values['no_title'] = 'true';
  }else{
    $values['no_title'] = 'false';
  }
}

/**
 * process {{showcase_slider}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_showcase_slider_process($attrs, $text = null, $shortcode = '') {
  $block = '';
  if (isset($attrs['id']) && is_numeric($attrs['id'])) {
    acquia_include('block');
    $block = block_load('ac_slider', $attrs['id']);
    acquia_prepare_block_display($block);

    $block = array($block);
    $block_array = _block_render_blocks($block);
    if (isset($attrs['block_title']) && !empty($attrs['block_title'])) {
      foreach($block_array as &$_block){
        $_block->subject = t($attrs['block_title']);
      }
    }else if (isset($attrs['no_title']) && $attrs['no_title'] == 'true') {
      foreach($block_array as &$_block){
        $_block->subject = '';
      }
    }
    $block_array = _block_get_renderable_array($block_array);
    $block = render($block_array);
  }

  return $block;
}