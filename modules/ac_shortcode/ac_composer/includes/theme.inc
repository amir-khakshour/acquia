<?php
/**
 * @file
 *  Contains helper functions to build and override theme functions
 */
 
 /**
 * Theme function for wrapping the template as needed for Backbone.View.render.
 *
 * By default, Drupal.Backbone.View uses Underscore templating and the
 * element's DOM ID to extract the template source.
 *
 * @param Array $variables
 *   Variables array containing the id and source for the template.
 *
 *   Note: all template sources provided by modules should be provided by theme
 *   functions as well, so they can be overridden at the theme level as desired.
 *
 * @return String
 *   The HTML for the wrapped template.
 */
function theme_backbone_template($variables = array()) {
  $template_id = $variables['template']['#template_id'];
  $template_source = $variables['template']['#template_source'];

  return <<<TEMPLATE
<script id="{$template_id}" type="text/underscore-template">
{$template_source}
</script>
TEMPLATE;
}

/**
 * Theme function for wrapping bootstrap modal templates for VC.
 */
function theme_db_bootstrap_modals($vars = array()){
 	// Include required libs
	acquia_include('interface', 'ac_visual_composer');
  
  $shortcodes = isset($vars['shortcodes']) ? $vars['shortcodes'] : array();
  
  $out = '<div class="db_bootstrap_modals">';
  
  $out .= theme('backbone_template', array(
    'template' => array(
       '#template_id' => 'db-elements-list-modal-template',
       '#template_source' => theme('db_elements_list_modal_template', array(
         'contentCategoriesLayouts' => ac_vc_getContentCategoriesLayouts($shortcodes),
         'contentLayouts' => ac_vc_getContentLayouts($shortcodes),
        )),
    ),

  ));
  
  $out .= theme('backbone_template', array(
    'template' => array(
       '#template_id' => 'db-element-settings-modal-template',
       '#template_source' => theme('db_element_settings_modal_template'),
    ),
  ));

  $out .= '</div>';

  return $out;
}

function theme_composer_swith_btn(){
 return '<a class="db-switch button-primary" href="#">'. t('Visual Composer') .'</a>';
}