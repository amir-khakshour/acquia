<?php
/**
 * @file
 *  Diamond Builder Abstract classes
 */

/**
 * Base Diamond Builder class
 *
 * @package AcquiaComposer
 */
class AcquiaComposer {
	/**
	 * Visual composer config
	 *  An array of Composer settings
	 */
	public static $config;

	/**
	 * Composer data
	 *  An array of Shortcode's composer list
	 */
	public static $composer = array();

	/**
	 * Storage for Diamond Builder layout object
	 */
	private $layout;

	/**
	 * An array of enabled shortcodes list
	 */
	public static $enabled = array();

	/**
	 *
	 */
	public function __construct() {
		self::setConfig();
	}

	/**
	 * Returns an instantiated AcquiaComposer object
	 */
	public static function getInstance($reset = FALSE) {
		$instance = &drupal_static(__FUNCTION__, NULL, $reset);

		if ( !isset($instance) ) {
			$instance = new AcquiaComposer();
		}

		return $instance;
	}

	/**
	 * Returns an instantiated AcquiaComposer object
	 */
	public function setEnabled($shortcodes = array()) {
		$this->enabled = $shortcodes;
	}

	/**
	 * Returns an instantiated AcquiaComposer object
	 */
	public function getEnabled() {
		return $this->enabled;
	}

	/**
	 * init config properties
	 */
	private static function setConfig() {
		$path = drupal_get_path('module', 'ac_composer');

		self::$config = array();
		self::$config['assets_dir'] = $path . '/assets';
	}

	/**
	 * returns given param value from $_POST array
	 */
	public function post($param) {
		return isset($_POST[$param]) ? $_POST[$param] : null;
	}

	/**
	 * returns given param value from $_GET array
	 */
	public function get($param) {
		return isset($_GET[$param]) ? $_GET[$param] : null;
	}

	/**
	 * returns URL of asset directory
	 */
	public function assetURL($asset) {
		return self::$config['APP_DIR'] . self::$config['ASSETS_DIR'] . $asset;
	}

	/**
	 * returns path to asset directory
	 */
	public function assetPath($asset) {
		return self::$config['APP_ROOT'] . self::$config['ASSETS_DIR'] . $asset;
	}

	/**
	 * returns value from VC config
	 */
	public static function config($name) {
		return isset(self::$config[$name]) ? self::$config[$name] : null;
	}
}


/**
 * Diamond Builder View Class
 *
 * This is the class for working with shortcode in composer
 * @TODO document
 */
class DiamondBuilderView extends AcquiaComposer{

	protected $atts, $settings;

	function __construct() {
	}

	/**
	 * Set settings for our shortcode
	 */
	public function setSettings($settings) {
		$this->settings = $settings;
		$this->settings['base'] = $settings['tag'];
		$this->settings['element_class'] = isset($this->settings['element_class']) ? $this->settings['element_class'] :'';
		$this->settings["header_title"] = isset($this->settings["header_title"]) ? $this->settings["header_title"] : TRUE;
		$this->settings["bottom_controls"] = isset($this->settings["bottom_controls"]) ? $this->settings["bottom_controls"] : TRUE;
		$this->settings["is_sortable"] = isset($this->settings["is_sortable"]) ? $this->settings["is_sortable"] : TRUE;
		$this->settings["child_sortable"] = isset($this->settings["child_sortable"]) ? $this->settings["child_sortable"] : TRUE;
	}

	/**
	 * Set attributes of our shortcode
	 */
	public function setAttrs($attrs) {
		$this->attrs = $attrs;
	}

	/**
	 * helper function for the editor_element function that tells the javascript were to insert the returned content
	 * you need to provide a "key" and a template
	 *
	 * @param string $key a string with argument or content key eg: img_src
	 * @param string $template a template that tells which content to insert. eg: <img src='{{img_src}}' />
	 * @return string
	 */

	function update_template($key, $template, $parent=TRUE)	{
		if ($parent) {
			$template =  htmlentities($template, ENT_QUOTES);
		}else{
		}
		$data = "data-update_with='$key' data-update_template='".$template."'";
		return $data;
	}

	/**
	 * helper function for the editor_element function that creates the correct classnames
	 * and data attributes for an AviaBuilder Canvas element in your backend
	 *
	 * @param string $classNames a string with classnames separated by coma
	 * @param array $args
	 * @return string
	 */
	function class_by_arguments($classNames, $args, $classNamesOnly = false) {
		$classNames = str_replace(" ","",$classNames);
		$dataString = "data-update_class_with='$classNames' ";
		$classNames = explode(',',$classNames);
		$classString = "class='";
		$classes = "";

		foreach($classNames as $class)
		{
			$classes .= "ac-$class-".str_replace(" ","_",$args[$class])." ";
		}

		if($classNamesOnly) return $classes;
		return $classString .$classes."' ".$dataString;
	}

	/**
	 * Generates element admin controls
	 *
	 * @param $controls
	 * @param string $extended_css
	 * @return string
	 */
	public function getControls($controls, $extended_css = '') {
		$controls_start = '<div class="db-controls controls_element'.(!empty($extended_css) ? " {$extended_css}" : '').'"><div class="db-controls-i">';
		$controls_end = '</div></div>';

		$controls_add = '';
		$controls_edit = ' <a class="db-control col-edit" href="#" title="'.sprintf(t('Edit %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-pencil"></i></a>';
		$controls_delete = ' <a class="db-control col-clone" href="#" title="'.sprintf(t('Clone %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-docs"></i></a>
		<a class="db-control col-delete" href="#" title="'.sprintf(t('Delete %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-trash"></i></a>';
		$controls_drag = '<a class="db-control col-drag" href="#" title="'.sprintf(t('Drag to move %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-move"></i><span>'.strtolower($this->settings('title')).'</span></a>';

		$column_controls_full = $controls_start . $controls_drag .  $controls_add . $controls_edit . $controls_delete . $controls_end;
		$column_controls_size_delete = $controls_start . $controls_drag . $controls_delete . $controls_end;
		$column_controls_popup_delete = $controls_start . $controls_drag . $controls_delete . $controls_end;
		$column_controls_edit_popup_delete = $controls_start . $controls_drag . $controls_edit . $controls_delete . $controls_end;
		if ( $controls == 'popup_delete' ) {
			return $column_controls_popup_delete;
		} else if ( $controls == 'edit_popup_delete' ) {
			return $column_controls_edit_popup_delete;
		} else if ( $controls == 'size_delete' ) {
			return $column_controls_size_delete;
		} else if ( $controls == 'popup_delete' ) {
			return $column_controls_popup_delete;
		} else if ($controls == 'add') {
			return $controls_start . $controls_add . $controls_end;
		} else {
			return $column_controls_full;
		}
	}

	protected function getHolderClasses() {
		$classes = array('db-'.str_replace('_', '-', $this->settings["base"]));
		$classes[] = 'db-content-level';
		$classes[] = 'db-sortable';
		$classes[] = 'clearfix';
		$classes[] = isset($this->settings['header_title']) && $this->settings['header_title'] != FALSE ? 'db-has-title' : NULL;
		$classes[] = isset($this->settings["wrapper_class"]) ? $this->settings["wrapper_class"] : NULL;
		$classes[] = isset($this->settings["as_parent"]) && $this->settings["as_parent"] ? 'ac-composer-parent' : NULL;
		return $classes;
	}

	protected function getContainerClasses() {
		$classes = array('db-visual-sc');
		return $classes;
	}

	/**
	 * Get Inner Content
	 */
	public function getInner($content) {
		$inner = '';
		if ( isset($this->settings["custom_markup"]) && $this->settings["custom_markup"] != '' ) {
			if ( $content != '' ) {
				$custom_markup = str_ireplace("%content%", $content, $this->settings["custom_markup"]);
			} else if ( $content == '' && isset($this->settings["default_content_in_template"]) && $this->settings["default_content_in_template"] != '' ) {
				$custom_markup = str_ireplace("%content%", $this->settings["default_content_in_template"], $this->settings["custom_markup"]);
			}
			$inner .= $custom_markup;
		}
		return $inner;
	}
	/**
	 * Generates Visual dispaly of element
	 * @param $width
	 * @return string
	 */
	public function getHolder($width) {
		acquia_include('utility', 'ac_composer');
		$output = '';
		$column_controls = $this->getControls($this->settings('controls'), 'top-controls');

		$holder_classes = array_filter($this->getHolderClasses(), 'strlen');
		$holder_classes = implode(' ', $holder_classes);

		$container_classes = array_filter($this->getContainerClasses(), 'strlen');
		$container_classes = implode(' ', $container_classes);

		$title = '';
		if (isset($this->settings['header_title']) && $this->settings['header_title'] != FALSE) {
			$title = '<h4 class="header-title">'.$this->iconTemplate() . $this->settings['title'].'</h4>';
		}

		$output .= '<section data-sc="'.$this->settings["base"].'" class="'.$holder_classes.'">';
		$output .= $title;
		$output .= str_replace("%column_size%", db_class_to_col_size($width), $column_controls);
		$output .= '<div class="'.$container_classes.'">';
		$output .= '%db_element_content%';
		$output .= '</div>';
		$output .= '</section>';
		return $output;
	}

	/**
	 * @param $atts
	 * @param $content
	 * @return string
	 */
	public function elementAdmin($atts, $content) {
		acquia_include('wp_bridge', 'ac_composer');
		$output = $custom_markup = $width = $el_position = '';

		if ( $content != NULL ) { $content = wpautop(stripslashes($content)); }

		if ( isset($this->settings['params']) ) {
			$shortcode_attributes = array('width' => '1/1');
			foreach ( $this->settings['params'] as $param ) {
				if ( $param['param_name'] != 'content' ) {
					if ( isset($param['value']) ) {
						$shortcode_attributes[$param['param_name']] = is_string($param['value']) ? t($param['value']) : $param['value'];
					} else {
						$shortcode_attributes[$param['param_name']] = '';
					}
				} else if ( $param['param_name'] == 'content' && $content == NULL ) {
					$content = t($param['value']);
				}
			}

			extract(shortcode_atts(
				$shortcode_attributes
				, $atts));
			$elem = $this->getHolder($width);
			if(isset($atts['el_position'])) $el_position = $atts['el_position'];
			$iner = $this->outputTitle($this->settings['title']);
			foreach ($this->settings['params'] as $param) {
				$param_value = isset($$param['param_name']) ? $$param['param_name'] : '';
				if ( is_array($param_value)) {
					// Get first element from the array
					reset($param_value);
					$first_key = key($param_value);
					$param_value = $param_value[$first_key];
				}
				$iner .= $this->elementLabels($param, $param_value);
			}
			$elem = str_ireplace('%db_element_content%', $iner, $elem);
			$output .= $elem;
		} else {
			//This is used for shortcodes without params (like simple divider)
			$width = '1/1';
			$elem = $this->getHolder($width);
			$inner = $this->getInner($content);
			$elem = str_ireplace('%db_element_content%', $inner, $elem);
			$output .= $elem;
		}
		return $output;
	}

	public function elementLabels($param, $value) {
		$output = '';
		$param_name = isset($param['param_name']) ? $param['param_name'] : '';
		$type = isset($param['type']) ? $param['type'] : '';
		$class = isset($param['class']) ? $param['class'] : '';

		if ( isset($param['holder']) === true && $param['holder'] !== 'hidden' ) {
			$output .= '<'.$param['holder'].' class="db-param-val ' . $param_name . ' ' . $type . ' ' . $class . '" name="' . $param_name . '">'.$value.'</'.$param['holder'].'>';
		} elseif(isset($param['holder']) === true && $param['holder'] == 'input') {
			$output .= '<'.$param['holder'].' readonly="true" class="db-param-val ' . $param_name . ' ' . $type . ' ' . $class . '" name="' . $param_name . '" value="'.$value.'">';
		} elseif(isset($param['holder']) === true && in_array($param['holder'], array('img', 'iframe'))) {
			$output .= '<'.$param['holder'].' class="db-param-val ' . $param_name . ' ' . $type . ' ' . $class . '" name="' . $param_name . '" src="'.$value.'">';
		}

		if (!isset($value)) {
			$value = '';
		}
		if ($type != 'textarea_html') {
			$output .= '<span class="db-label admin_label_'.$param['param_name'].'"><label>'.t($param['heading']).'</label>: '.$value.'</span>';
		}
		return $output;
	}

	/**
	 * Get Shortcode template
	 */
	public function template($content = '') {
		return $this->elementAdmin($this->atts, $content);
	}

	/**
	 * Get Shortcode settings by name
	 */
	public function settings($name) {
		return isset($this->settings[$name]) ? $this->settings[$name] : null;
	}

	protected function outputTitle($title) {
		if (!isset($this->settings['header_title']) || $this->settings['header_title'] == FALSE) {
			$title = '<h4 class="db_element_title">'.t($title).'</h4>';
		}else{
			$title = '';
		}
		return $title;
	}

	protected function iconTemplate() {
		$icon = isset($this->settings['icon']) ?  $this->settings['icon'] : 'icon-'.str_replace('_', '-', $this->settings['base']);
		if (!$icon) {
			return;
		}
		if (isset($this->settings['icon'])) {
			$icon = '<i class="visual-icon ac-icon '.$this->settings['icon'].'"></i>';
		}else if (isset($this->settings['icon_image'])) {
			$icon = '<img class="visual-icon ac-icon" src="'.$this->settings['icon_image'].'"/>';
		}else {
			$icon = '<i class="visual-icon ac-icon icon-'.str_replace('_', '-', $this->settings['base']).'"></i>';
		}
		return  $icon;
	}
}



/**
 * DiamondLayers Container Composer View Class
 *
 * This is the class for working with shortcode in composer
 * @TODO document
 */
class DiamondBuilderContainerView extends DiamondBuilderView {
	public function __construct($settings = array()) {
		parent::__construct($settings);
		acquia_include('utility', 'ac_composer');
		acquia_include('wp_bridge', 'ac_composer');
	}

	protected  $predefined_atts = array(
		'el_class' => '',
		'width' => '',
		'title' => ''
	);
	/**
	 * Generates element admin controls
	 *
	 * @param $controls
	 * @param string $extended_css
	 * @return string
	 */
	public function getControls($controls, $extended_css = '') {
		$controls_start = '<div class="db-controls controls_element'.(!empty($extended_css) ? " {$extended_css}" : '').'"><div class="db-controls-i">';
		$controls_end = '</div></div>';

		$controls_prepend = ' <a class="db-control col-add" href="#" title="'.sprintf(t('Prepend to %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-plus"></i></a>';
		$controls_append = ' <a class="db-control col-add" href="#" title="'.sprintf(t('Append to %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-plus"></i></a>';

		$controls_edit = ' <a class="db-control col-edit" href="#" title="'.sprintf(t('Edit %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-pencil"></i></a>';
		$controls_delete = ' <a class="db-control col-clone" href="#" title="'.sprintf(t('Clone %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-docs"></i></a>
		<a class="db-control col-delete" href="#" title="'.sprintf(t('Delete %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-trash"></i></a>';
		$controls_drag = '<a class="db-control col-drag" href="#" title="'.sprintf(t('Drag to move %s'), strtolower($this->settings('title'))).'"><i class="admin-icon icon-admin-move"></i><span>'.strtolower($this->settings('title')).'</span></a>';

		$column_controls_full = $controls_start . $controls_drag . $controls_prepend . $controls_edit . $controls_delete . $controls_end;
		$column_controls_prepend = $controls_start . $controls_drag . $controls_prepend . $controls_edit . $controls_delete . $controls_end;
		$column_controls_size_delete = $controls_start . $controls_drag . $controls_delete . $controls_end;
		$column_controls_popup_delete = $controls_start . $controls_drag . $controls_delete . $controls_end;
		$column_controls_edit_popup_delete = $controls_start . $controls_drag . $controls_edit . $controls_delete . $controls_end;

		if ( $controls == 'popup_delete' ) {
			return $column_controls_popup_delete;
		} else if ( $controls == 'edit_popup_delete' ) {
			return $column_controls_edit_popup_delete;
		} else if ( $controls == 'size_delete' ) {
			return $column_controls_size_delete;
		} else if ( $controls == 'popup_delete' ) {
			return $column_controls_popup_delete;
		} else if ($controls == 'add') {
			return $controls_start . $column_controls_prepend . $controls_end;
		} else if ($controls == 'append') {
			return $controls_start . $controls_append . $controls_end;
		} else {
			return $column_controls_full;
		}
	}
	public function prependVisual() {
		return FALSE;
	}

	public function appendVisual() {
		return FALSE;
	}

	protected function getHolderClasses() {
		$classes = array('db-'.str_replace('_', '-', $this->settings["base"]));
		$classes[] = 'db-content-level';
		if ($this->settings['is_sortable']) {
			$classes[] ='db-sortable';
		}
		$classes[] = 'clearfix';
		$classes[] = isset($this->settings['header_title']) && $this->settings['header_title'] != FALSE ? 'db-has-title' : NULL;
		$classes[] = $this->settings['element_class'];
		return $classes;
	}

	public function elementAdmin($atts, $content = null) {
		acquia_include('utility', 'ac_composer');
		acquia_include('wp_bridge', 'ac_composer');
		acquia_include('process', 'ac_shortcode');

		extract(shortcode_atts($this->predefined_atts, $atts));
		$output = '';
		$column_controls = $this->getControls($this->settings('controls'), 'top-controls');

		$holder_classes = array_filter($this->getHolderClasses(), 'strlen');
		$holder_classes = implode(' ', $holder_classes);

		$container_classes = array_filter($this->getContainerClasses(), 'strlen');
		$container_classes = implode(' ', $container_classes);

		$column_controls_bottom = '';
		if ($this->settings('bottom_controls') && $this->settings['bottom_controls'] != FALSE) {
			$column_controls_bottom = $this->getControls('append', 'bottom-controls');
		}
		$output .= '<section data-sc="'.$this->settings["base"].'" class="'.$holder_classes.'"'.$this->customAdminBlockParams().'>';

		$output .= $column_controls;
		if (isset($this->settings['header_title']) && $this->settings['header_title'] != FALSE) {
			$output .= '<h4 class="header-title">'.$this->iconTemplate() . $this->settings['title'].'</h4>';
		}

		$output .= '<div class="'.$container_classes.'">';
		$output .= $this->prependVisual();
		$output .= '<div '.drupal_attributes($this->containerAttributes()).'>';
		$output .=  $content;
		$output .= '</div>';
		$output .= $this->appendVisual();
		if ( isset($this->settings['params']) ) {
			$inner = '';
			foreach ($this->settings['params'] as $param) {
				$param_value = isset($$param['param_name']) ? $$param['param_name'] : '';
				if ( is_array($param_value)) {
					// Get first element from the array
					reset($param_value);
					$first_key = key($param_value);
					$param_value = $param_value[$first_key];
				}
				$inner .= $this->elementLabels($param, $param_value);
			}
			$output .= $inner;
		}
		$output .= '</div>';
		$output .= $column_controls_bottom;
		$output .= '</section>';
		return $output;
	}

	public function mainHtmlBlockParams() {
		$classes = array('db-'.str_replace('_', '-', $this->settings["base"]), 'db-content-level');
		if ($this->settings['is_sortable']) {
			$classes[] ='db-sortable';
		}

		$classes[] = isset($this->settings['header_title']) &&
		$this->settings['header_title'] != FALSE ? 'db-has-title' : NULL;
		$classes[] = $this->settings['element_class'];
		$classes = array_filter($classes, 'strlen');
		$classes = implode(' ', $classes);

		return 'data-sc="'.$this->settings["base"].'" class="'.$classes.'"'.$this->customAdminBlockParams();
	}

	public function containerAttributes() {
		$attrs['class'] = array();
		$attrs['class'] = array('db-column-container');
		$attrs['class'][] = 'db-column-like-container';
		$attrs['class'][] = 'db-parent';
		if ($this->settings('child_sortable')) {
			$attrs['class'][] = 'child-sortable';
		}
		return $attrs;
	}

	protected function outputTitle($title) {
		return  '';
	}

	public function customAdminBlockParams() {
		return '';
	}
}

/**
 *
 */
class DiamondBuilderCustomView extends DiamondBuilderView{
	public function elementAdmin($atts, $content) {
		$width = '1/1';

		$elem = $this->getHolder($width);

		$inner = $this->elementLabels($atts, $content);
		$elem = str_ireplace('%db_element_content%', $inner, $elem);
		return $elem;
	}
}

/**
 * Diamond Builder templates class
 *
 * Add/Edit/Delete Composer template from DB
 * @package AcquiaComposer
 */
class DiamondBuilderSavedTemplates{
	/**
	 * Whther reset cached tempaltes data from DB or not
	 */
	protected $reset = FALSE;

	/**
	 * Constructor Method
	 */
	public function __construct($reset = FALSE) {
		$this->reset = $reset;
		return $this;
	}

	/**
	 * Get Saved Templates list from DB
	 */
	public function GetSavedTemplates() {
		$templates = &drupal_static(__FUNCTION__, NULL, $this->reset);

		if (!isset($templates)) {
			$templates = db_select('{'.ACQUIA_COMPOSER_TEMPLATES_TABLE.'}', 'ac')
				->fields('ac')
				->execute()
				->fetchAll(PDO::FETCH_ASSOC);

			if (!count($templates)) {
				$templates = array();
			}
		}
		return $templates;
	}

	/**
	 * Save Template into Diamond Builder Templates table
	 * @param {array} $template
	 * 		An array of template details including below keys:
	 * 		1-	%tid: Template id - in case of updating saved template
	 * 		1-	%title: Title of template
	 * 		2-	%template: Tempalte content
	 */
	public function save($template){
		$fields = array();
		foreach ($this->db_fields() as $field_name) {
			$fields[$field_name] = $template[$field_name];
		}

		if (isset($template['tid'])) {
			db_update(ACQUIA_COMPOSER_TEMPLATES_TABLE)
				->fields($fields)
				->condition('tid', $template['tid'])
				->execute();
		}
		else {
			$template['tid'] = db_insert(ACQUIA_COMPOSER_TEMPLATES_TABLE)
				->fields($fields)
				->execute();
		}
		return $template['tid'];
	}

	/**
	 * Delete Template From Diamond Builder Templates table
	 * @param {int} $tid
	 * 		Template ID
	 */
	public function delete($tid){
		return db_delete(ACQUIA_COMPOSER_TEMPLATES_TABLE)
			->condition('tid', $tid)
			->execute();
	}

	/**
	 * Get Template from Diamond Builder Templates table
	 * @param {int} $tid
	 * 		Template id
	 */
	public function get_template_by_id($tid){
		if (!is_numeric($tid)) {
			return;
		}

		$templates = &drupal_static(__FUNCTION__, array(), $this->reset);

		if (!isset($templates[$tid])) {
			$templates[$tid] = db_select('{'.ACQUIA_COMPOSER_TEMPLATES_TABLE.'}', 'ac')
				->fields('ac')
				->condition('tid', $tid)
				->execute()
				->fetchAll(PDO::FETCH_ASSOC);

			$templates[$tid] = array_shift($templates[$tid]);
		}

		return $templates[$tid];
	}

	/**
	 * Getter method to get ac_composer templates table fields
	 */
	public function db_fields() {
		return array('tid', 'title', 'template');
	}
}
