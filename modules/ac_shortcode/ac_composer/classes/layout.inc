<?php
/**
 * @file
 * The Diamond Template Builder, which creates HTML outputs of shortcode for visual Builder.
 */

/**
 * Interface for Diamond Builder templates.
 */
class DiamondBuilderTemplate {
  /**
   * Whther reset cached tempaltes data from DB or not
   */
  protected $reset = FALSE;

  /**
   * Array of Button attributes
   */
  protected $attrs = array();

  /**
   * Shortcode collection
   * @var array
   */
  protected $collection = NULL;

  /**
   * Shortcode Composer
   * @var array
   */
  protected $composer = NULL;

  /**
   * HTML which object builds
   * @var string
   */
  public $htmlOut = '';

  /**
   * Costructor for AcquiaComposerButton
   * @param {array} $attrs
   *   An array of button attributes, including these keys:
   *   - %title : title attribute of button anchor link
   *   - %id : id attribute of button anchor link
   * @return {object} $this
   */
  public function __construct($attrs = array()) {
    // add required files
    $this->add_files();
    // Validate Attributes
    $this->validate_attrs($attrs);
    // Assign Attributes
    $this->attrs = $attrs;

    return $this;
  }

  /**
   * Validate Given attributes array
   */
  protected function add_files() {

    // base ac_shortcode classes
    require_once ACQUIA_SHORTCODE_CLASSES_PATH . '/base.inc';

  }

  /**
   * Validate Given attributes array
   */
  protected function validate_attrs($attrs) {
  }

  /**
   * Setter method
   */
  public function set($name, $value) {
    switch ($name) {
      case 'reset':
        $this->reset = $value;
        break;
      case 'collection':
        $this->collection = $value;
        break;
      case 'composer':
        $this->composer = $value;
        break;
    }

    return $this;
  }

  /**
   * Getter method
   */
  public function get($name) {
    switch ($name) {
      case 'reset':
        return $this->reset;
      case 'collection':
        return $this->collection;
      case 'composer':
        return $this->composer;
    }
  }

  /**
   * HTML builder method
   *
   * use this method to build and assign $htmlOut variable of object
   * @return string
   */
  protected function buildHtml(){
    $out = '';
    // your code here to populate $out
    return $out;
  }

  /**
   * HTML getter method
   */
  public function getHTMLOut(){
    // Assign Out
    $this->htmlOut = $this->buildHtml();
    return $this->htmlOut;
  }

  /**
   * Get Mapped Composer to shortcodes array
   */
  public function mapComposerToShortcodes(){
    $mapped = &drupal_static(__FUNCTION__, NULL);
    if (!isset($mapped)) {
      $mapped = array();
      $shortcodes = $this->collection->getEnabledShortcodes();
      if ( isset($this->composer) && !empty($this->composer) ){
        foreach ($this->composer as $tag => $info) {
          if (!isset($shortcodes[$tag])) {
            continue;
          }
          $mapped[$tag] = $this->composer[$tag];
          $mapped[$tag]['title'] = isset($shortcodes[$tag]['title']) ? $shortcodes[$tag]['title'] : '';
          $mapped[$tag]['description'] = isset($shortcodes[$tag]['description']) ? $shortcodes[$tag]['description'] : '';
          if ( isset($shortcodes[$tag]['nested shortcodes']) && !empty($shortcodes[$tag]['nested shortcodes']) ) {
            $mapped[$tag]['nested shortcodes'] = $shortcodes[$tag]['nested shortcodes'];
          }
        }
      }
    }
    return $mapped;
  }
  /**
   * Get Shortcode categories
   */
  public function getShortcodeCateggories() {
    $shortcodes_cat = &drupal_static(__FUNCTION__, NULL);

    if (!isset($shortcodes_cat)) {
      $shortcodes_cat = array();
      foreach ( $this->mapComposerToShortcodes() as $tag => $info) {
        $info['category'] = isset($info['category']) ? $info['category'] : '_other_category_';
        foreach((array)$info['category'] as $category) {
          $shortcodes_cat[$category] = $category;
        }
      }
    }
    return $shortcodes_cat;
  }
}


/**
 * Template List HTML generator
 *	This class outputs saved composer template items.
 * @see DiamondBuilderTemplate
 */
class DiamondBuilderSavedTemplatesMenuItem extends DiamondBuilderTemplate {
  protected function validate_attrs($attrs) {
    if ( !isset($attrs['title']) || !isset($attrs['id'])) {
      throw new AcquiaShortcodeException("Not enough attributes for building saved template item!");
    }
  }

  /**
   * Outputs HTML for composer button layout
   */
  protected function buildHtml() {
    $id = $this->attrs['id'];
    $title = t($this->attrs['title']);
    $out  = '<li class="template-item">';
    $out .= '  <a data-template_id="'.$id.'" href="#">';
    $out .= '    <i class="admin-icon icon-admin-load"></i>';
    $out .= '    <span class="label">'.htmlspecialchars($title) .'</span>';
    $out .= '  <span class="remove-template" rel="'.$id.'">';
    $out .= '    <i class="admin-icon icon-admin-icon-cancel"></i>';
    $out .= '  </span>';
    $out .= '  </a>';
    $out .= '</li>';
    return $out;
  }
}

/**
 * DiamondBuilder Saved Templates
 *
 * Generates List of saved templates as a menu
 */
class DiamondBuilderSavedTemplatesMenu extends DiamondBuilderTemplate {
  /**
   * Whether reset cached templates data from DB or not
   */
  protected $reset = FALSE;

  /**
   * @param bool|FALSE $reset
   */
  public function __construct($reset = FALSE) {
    parent::__construct();
    $this->reset = $reset;
  }

  /**
   * Build HTML of saved templates
   * @return string
   */
  private function _BuildSavedTemplatesHTML() {
    $cache = &drupal_static(__FUNCTION__, NULL, $this->reset);

    if (!isset($cache)) {
      $cache = '';

      // Get saved templates
      $templates = new DiamondBuilderSavedTemplates();

      foreach($templates->GetSavedTemplates() as $template) {
        if( is_array( $template) ) {
          $link = new DiamondBuilderSavedTemplatesMenuItem(array('id' => $template['tid'], 'title' => $template['title']));
          $cache .= $link->getHTMLOut();
        }
      }
    }

    return $cache;
  }

  /**
   * Getter method
   * @return string
   * @see _BuildSavedTemplatesHTML
   */
  public function getSavedTempaltesHTML(){
    return $this->_BuildSavedTemplatesHTML();
  }

  /**
   * Outputs HTML for saved composer templates menu
   */
  protected function buildHtml() {
    $templates = $this->getSavedTempaltesHTML();
    if (empty($templates)) {
      $templates = '<li class="db_no_templates"><span>'.t('No custom templates yet.').'</span></li>';
    }
    $out  = '<li>';
    $out .= '  <ul class="clearfix">';
    $out .= '    <li class="save-template"><a href="#" id="save-template-btn" class="save-template-btn button" >'.t('Save current page as a Template').'</a></li>';
    $out .= '    <li class="templates-list"><ul class="template-items"><li class="items-header">'.t('Load Template').'</li><ul>'.$templates.'</ul></ul></li>';
    $out .= '  </ul>';
    $out .= '</li>';
    return $out;
  }
}


/**
 * Diamond Builder Navigation bar
 *
 * Generates navigation bar of Composer
 */
class DiamondBuilderNavbar extends DiamondBuilderTemplate {
  /**
   * Outputs HTML for saved composer templates menu
   */
  protected function buildHtml() {
    // Get Nav Buttons
    return $this->_BuildButtons();
  }

  /**
   * Returns the HTML of VC templates list
   */
  private function _GetTemplatesMenu() {
    $templates = new DiamondBuilderSavedTemplatesMenu($this->reset);
    return $templates->getHTMLOut();
  }

  /**
   * Returns the HTML of main VC buttons Add element / Add row / Templates
   */
  private function _BuildButtons() {
    return theme('builder_nav', array('submenu_links' => $this->_GetTemplatesMenu()));
  }

}

/**
 * Class DiamondBuilderModalItem
 *
 * Item generator for Builder Modal
 * @see DiamondBuilderModal
 */
class DiamondBuilderModalItem extends DiamondBuilderTemplate {
  protected function validate_attrs($attrs) {
    parent::validate_attrs($attrs);
    if ( !isset($attrs['title'])) {
      throw new AcquiaShortcodeException("title is not defined for shortcode button!");
    }

    if (!isset($attrs['category'])) {
      throw new AcquiaShortcodeException("Each Shortcode must have at least one category!");
    }

    if (!isset($attrs['tag'])) {
      throw new AcquiaShortcodeException("Shortcode tag is required to build shortcode button!");
    }
  }

  /**
   * Get Shortcode Icon
   */
  protected function getIcon() {
    if (isset($this->attrs['icon'])) {
      $icon = '<i class="ac-icon '.$this->attrs['icon'].'"></i>';
    }else if (isset($this->attrs['icon_image'])) {
      $icon = '<img class="ac-icon" src="'.$this->attrs['icon_image'].'"/>';
    }else {
      $icon = '<i class="ac-icon icon-'.str_replace('_', '-', $this->attrs['tag']).'"></i>';
    }
    return  $icon;
  }

  /**
   * Outputs HTML for composer button layout
   */
  protected function buildHtml() {
    // HTML attributes array
    $li_attrs = array();
    $li_attrs['class'] = array('db-shortcode-sel');

    // Anchor Attributes
    $a_attrs = array();
    $a_attrs['href'] = '#';
    $a_attrs['id'] = $this->attrs['tag'];
    $a_attrs['class'] = array('dropable_el');

    if ( !empty($this->attrs['class']) ) {
      $classes = is_array($this->attrs['class']) ? $this->attrs['class'] : explode(' ', $this->attrs["class"]);

      for ($n=0; $n<count($classes); $n++) {
        $li_attrs['class'][] = $classes[$n] . '_o';
        $a_attrs['class'][]  = $classes[$n] .'_nav';
      }
    }


    $this->attrs['category'] = (array) $this->attrs['category'];
    foreach($this->attrs['category'] as $id) {
      $li_attrs['class'][] = 'category-'.md5($id);
    }

    $a_attrs['class'] = implode(' ', array_filter($a_attrs['class'], 'strlen'));
    $li_attrs['class'] =implode(' ',  array_filter($li_attrs['class'], 'strlen'));

    // Build Data array
    $li_attrs['data-element'] = $this->attrs['tag'];
    if ( isset($this->attrs['is_container']) && $this->attrs['is_container'] === TRUE ) {
      $li_attrs['data-is-container'] = "true";
    }

    $out  = '<li'.drupal_attributes($li_attrs).'>';
    $out .= '<div class="db-shortcode-wrapper">';
    $out .= '  <a'.drupal_attributes($a_attrs).'>';
    $out .= '    '.$this->getIcon();
    $out .= '    '.htmlspecialchars(stripslashes($this->attrs["title"]));
    if (isset($this->attrs['description'])){
      $out .= '    <i class="vc-element-description">'.t($this->attrs['description']).'</i>';
    }
    $out .= '  </a>';
    $out .= '  </div>';
    $out .= '</li>';
    return $out;
  }
}

/**
 * Class DiamondBuilderModal
 *
 * Generates Modal Items for Builder
 * @see DiamondBuilderModalItem
 */
class DiamondBuilderModal extends DiamondBuilderTemplate {
  /**
   * Builds and returns the HTML for shortcode categories
   */
  private function _getShortcodeCategoriesHTML() {
    $out  = '	<ul class="isotope-filter">';
    $out .= '		<li class="active"><a href="#" data-filter="*">'.t('Show all').'</a></li>';
    $show_other = FALSE;
    $categories = $this->getShortcodeCateggories();
    foreach($categories as $key => $title) {
      if($title === '_other_category_') {
        $_other_category_index = $key;
        $show_other = TRUE;
      } else {
        $out .='<li><a href="#" data-filter=".category-'.md5($key).'">'.t($title).'</a></li>';
      }
    }

    if ($show_other) {
      $out .= '<li><a href="#" data-filter=".category-'.$_other_category_index.'">' .t('Other').'</a></li>';
    }
    $out .= '	</ul>';
    return $out;
  }

  /**
   * Generates list of shortcodes that is shown in the popUp menu
   */
  private function _getShortcodesListHTML() {
    $out = '<ul class="db-shortcode-items clearfix">';
    foreach ( $this->mapComposerToShortcodes() as $tag => $info) {
      if (isset($info['content_element']) && $info['content_element'] == FALSE) {
        continue;
      }
      $sc_button = new DiamondBuilderModalItem($info);

      $out .= $sc_button->getHTMLOut();
    }

    $out .= '</ul>';

    return $out;
  }

  /**
   * Outputs HTML for saved composer templates menu
   */
  protected function buildHtml() {
    return theme('builder_shortcodes_modal', array(
        'categories' => $this->_getShortcodeCategoriesHTML(),
        'shortcodes' => $this->_getShortcodesListHTML()
    ));
  }
}

/**
 * Diamond Builder Layout
 *
 * Generates the composer HTML layout
 * @package AcquiaComposer
 */
class DiamondBuilderLayout extends DiamondBuilderTemplate {
  /**
   * display composer box or not
   */
  protected $enabled = FALSE;

  /**
   * @TODO document here
   */
  public function set($name, $value) {
    parent::set($name, $value);
    if ($name == 'enabled') {
      $this->$enabled = $value;
    }
  }

  /**
   * Helper Method that returns Composer Navbar
   */
  private function GetComposerNavbar() {
    $out = &drupal_static(__FUNCTION__, NULL);

    if (!isset($modal)) {
      $out = new DiamondBuilderNavbar($this->reset);
      $out = $out->getHTMLOut();

    }
    return $out;
  }

  /**
   * Helper Method that returns Composer Modal
   */
  private function GetComposerModal() {
    $out = &drupal_static(__FUNCTION__, NULL);

    if (!isset($out)) {
      $out = new DiamondBuilderModal();

      $out->set('collection', $this->get('collection'))
          ->set('reset', $this->get('reset'));

      $out = $out->getHTMLOut();

    }
    return $out;
  }

  /**
   * @TODO document here
   */
  private function GetHiddenInputs() {
    $enabled = $this->enabled === TRUE ? "true" : "false";

    $out  = '';
    $out .= '<input type="hidden" id="db_vc_js_status" name="db_vc_js_status" value="'. $enabled .'" />';
    $out .= '<input type="hidden" id="db_vc_loading" name="db_vc_loading" value="'. t("Loading, please wait...") .'" />';
    $out .= '<input type="hidden" id="db_vc_loading_row" name="db_vc_loading_row" value="'. t("Crunching...") .'" />';
    $out .= '<input type="hidden" id="db_vc_js_interface_version" name="db_vc_js_interface_version" value="'. ACQUIA_COMPOSER_VERSION .'" />';

    return $out;
  }

  /**
   * Init shortcode builder tempaltes for views here
   *
   * @return string
   */
  private function GetShortcodeTemplates() {

    acquia_include('utility', 'ac_shortcode');
    acquia_include('utility', 'ac_composer');

    $out = '<script type="text/html" id="vc-settings-image-block">
				<li class="added">
						<div class="inner" style="width: 75px; height: 75px; overflow: hidden;text-align: center;">
								<img rel="<%= id %>" src="<%= url %>" />
						</div>
						<a href="#" class="icon-remove"></a>
				</li>
		</script>';

    $composer_class = ACQUIA_COMPOSER_VIEW_CLASS;
    $default_composer = new $composer_class();
    $shortcode_composers = $this->mapComposerToShortcodes();

    foreach ($shortcode_composers as $tag => $info) {
      ac_composer_add_sc_composer_files($info);

      if (isset($info['class']) && class_exists($info['class'])) {
        $class = new $info['class']();
      }else {
        $class = $default_composer;
      }
      $class->setSettings($info);
      $out .=	'<script type="text/template" id="db-sc-template-'.$tag.'">';
      $out .= $class->template();
      $out .= '</script>';
    }
    return $out;
  }

  /**
   * Helper method to get composer main content
   */
  private function GetComposerBox() {
    // Add js settings
    // @TODO move to ac_shortcode module
    $this->add_js_assets();

    $out  = '';
    $out .= $this->GetComposerModal();
    $out .= $this->GetComposerNavbar();
    $out .= theme('composer_main_content');
    $out .= $this->GetHiddenInputs();
    $out .= $this->GetShortcodeTemplates();

    return $out;
  }

  /**
   * Outputs HTML for saved composer templates menu
   */
  protected function buildHtml() {
    $out  = '<div id="db-wrapper" class="db-wrapper ac-admin">';
    $out .= '  <div id="db-container" class="db-container postbox db_vc_box" style="display: none;">';
    $out .= '    <h3 class="db-title"><span>'.t("Diamond Builder").'</span></h3>';
    $out .= '    <div class="inside">';
    $out .= '	    '.$this->GetComposerBox();
    $out .= '    </div>';
    $out .= '  </div>';
    $out .= '</div>';

    return $out;
  }

  /**
   * Addings required js settings
   */
  private function add_js_assets() {
    // Add required libs
    acquia_include('utility');
    $shortcode_composers = $this->mapComposerToShortcodes();
    $composer_js = array();
    $composer_js['shortcodes'] = $this->GetPreparedComposersJS($shortcode_composers);
    $composer_js['ajaxurl'] = acquia_variable_get('path_prefix') . ACQUIA_COMPOSER_AJAX_URL;
    $composer_js['i18n'] = $this->localized_strings();
    $composer_js['copy_clipboard_swf'] = ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/jquery.clipboard/jquery.clipboard.swf';
    drupal_add_js(array('DiamondBuilder' => $composer_js), 'setting');
    $libs_path = acquia_variable_get('libs_path', 'sites/all/libraries');

    // 01 - Load required system Libs
    drupal_add_library('system', 'ui');
    drupal_add_library('system', 'farbtastic');
    drupal_add_library('system', 'ui.tabs');
    drupal_add_library('system', 'ui.sortable');
    drupal_add_library('system', 'ui.droppable');
    drupal_add_library('system', 'ui.draggable');
    drupal_add_library('system', 'ui.accordion');
    drupal_add_library('system', 'ui.autocomplete');
    acquia_load_resources('modal');
    acquia_load_resources('admin-shortcodes');

    // 02 - Load Backend and underscore
    drupal_add_js($libs_path . '/underscore/underscore.js', array(
        'group' => -1000,
        'weight' => -1000,
    ));

    drupal_add_js($libs_path . '/backbone/backbone.js', array(
        'group' => JS_LIBRARY,
        'weight' => -999,
    ));

    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/builder.base.js', array(
        'group' => JS_LIBRARY,
        'weight' => -880,
    ));

    drupal_add_js(drupal_get_path('module', 'ac_composer') . '/assets/js/vc_custom.js', array(
        'group' => JS_LIBRARY,
        'weight' => -1,
    ));

    drupal_add_js(drupal_get_path('module', 'ac_composer') . '/assets/js/shortcode.js', array(
        'group' => JS_LIBRARY,
    ));

    // 03 - Main VC CSS file
    drupal_add_css(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/css/ui-custom-theme/jquery-ui-' . ACQUIA_COMPOSER_JQUERY_UI_VERSION . '.custom.css');
    drupal_add_css(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/css/animate.css');
    drupal_add_css(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/css/js_composer.css');

    drupal_add_library('ac_composer', 'autosuggest');
    drupal_add_library('ac_composer', 'autosuggest');
    drupal_add_library('acquia', 'isotope');

    drupal_add_css(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/bootstrap_modals/css/bootstrap.modals.css');
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/bootstrap_modals/js/bootstrap.min.js');
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/scrollTo/jquery.scrollTo.min.js');
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/php.default/php.default.min.js');
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/json-js/json2.js');
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/lib/jquery.clipboard/jquery.clipboard.js');

    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/builder.utils.js', array('weight' => 18));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/builder.storage.js', array('weight' => 21));

    // Add Models
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/models/models.shortcode.js', array('weight' => 24));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/collections/collections.shortcode.js', array('weight' => 25));

    // Add Views
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/views/views.base.js', array('weight' => 25));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/views/views.block.js', array('weight' => 26));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/views/views.settings.js', array('weight' => 27));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/views/views.shortcode.js', array('weight' => 28));
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/backend/views/views.custom.js', array('weight' => 29));

    // @TODO MOVE TO DRUPAL
    drupal_add_js(ACQUIA_COMPOSER_COMPOSER_ASSET_PATH . '/js/theme_admin.js');
    drupal_add_js(drupal_get_path('module', 'ac_composer') . '/assets/js/composer_ui.js', array('weight' => 17));

    // 04 - Load custom assets
    acquia_load_resources('mediabrowser');
    acquia_load_resources('admin');
    drupal_add_css(drupal_get_path('module', 'ac_composer') . '/assets/css/ac_composer.css');

    drupal_add_css(drupal_get_path('module', 'ac_composer') . '/assets/css/builder.css');
    drupal_add_css(drupal_get_path('module', 'ac_composer') . '/assets/css/sprites.css');

    // @TODO load required shortcodes assets
    $this->AddShortcodeComposersAssets($shortcode_composers);
  }

  /**
   * load required shortcodes assets
   */
  private function AddShortcodeComposersAssets($shortcode_composers = array()) {
    foreach($shortcode_composers as $tag => $info) {
      if ( isset($info['asset']) && !empty($info['asset']) ) {
        $elements['#attached'] = $info['asset'];
        drupal_process_attached($elements, JS_LIBRARY, TRUE, $every_page = FALSE);
      }
    }
  }

  /**
   * Prepare shortcodes for addings to js settings
   */
  private function GetPreparedComposersJS($shortcode_composers = array()) {
    $shortcodes_js = &drupal_static(__FUNCTION__, NULL);

    if (!isset($shortcodes_js)) {
      $filter = array('class', 'module', 'file', 'path');
      $shortcodes_js = $shortcode_composers;

      foreach($shortcodes_js as $tag => $info) {
        foreach($filter as $key) {
          if (in_array($key, $filter)) {
            unset($shortcodes_js[$tag][$key]);
          }
        }
      }
      $shortcodes_js = json_encode($shortcodes_js);
    }
    return $shortcodes_js;
  }

  /**
   * @TODO document here
   */
  private function localized_strings() {
    return array(
        'n_a' => t( 'N/A'),
        'add_remove_picture' => t( 'Add/remove picture'),
        'finish_adding_text' => t( 'Finish Adding Images'),
        'add_image' => t( 'Add Image'),
        'add_images' => t( 'Add Images'),
        'builder_switch_btn' => t( 'Builder Mode'),
        'classic_switch_btn' => t( 'Classic Mode'),
        'please_enter_templates_name' => t('Please enter templates name'),
        'confirm_deleting_template' => t('Confirm deleting "{template_name}" template, press Cancel to leave. This action cannot be undone.'),
        'elements_list_modal_header' => t('Add Element'),
        'copy_section_shortcodes' => t('Copy section shortcodes'),
        'press_ok_to_delete_section' => t('Press OK to delete section, Cancel to leave'),
        'drag_drop_me_in_column' => t('Drag and drop me in the column'),
        'press_ok_to_delete_tab' => t('Press OK to delete "{tab_name}" tab, Cancel to leave'),
        'slide' => t('Slide'),
        'tab' => t('Tab'),
        'section' => t('Section'),
        'please_enter_new_tab_title' => t('Please enter new tab title'),
        'press_ok_delete_section' => t('Press OK to delete "{tab_name}" section, Cancel to leave'),
        'section_default_title' => t('Section'),
        'please_enter_section_title' => t('Please enter new section title'),
        'error_please_try_again' => t('Error. Please try again.'),
        'if_close_data_lost' => t('If you close this window all shortcode settings will be lost. Close this window?'),
        'header_select_sc' => t('Select Shortcode'),
        'header_media_gallery' => t('Media gallery'),
        'header_element_settings' => t('Element settings'),
        'add_tab' => t('Add tab'),
        'add_section' => t('Add Section'),
        'are_you_sure_convert_to_new_version' => t('Are you sure you want to convert to new version?'),
        'loading' => t('Loading...'),
      // Media editor
        'set_image' => t('Set Image'),
        'are_you_sure_reset_css_classes' => t('Are you sure taht you want to remove all your data?'),
        'loop_frame_title' => t('Loop settings'),
        'enter_custom_layout' => t('Enter custom layout for your row:'),
        'wrong_cells_layout' => t('Wrong row layout format! Example: 1/2 + 1/2 or span6 + span6.'),
    );
  }

}