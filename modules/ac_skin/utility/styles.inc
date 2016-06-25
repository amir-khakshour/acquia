<?php
// $Id
/**
 *
 */
/**
 * returns list of typography keys
 */
function acquia_styles_keys(){
 // you can add attributes here
 $default_font_family = ', Helvetica, Arial, Verdana, sans-serif';
 $styles = array(
	 // General settings
	 'general' => array(
		 'title' => t('General'),
		 'description' => '',
			'scheme' => array(
				'accent-color' => array(
					'type' => 'hex_color',
					'title' => t('Accent color'),
					'default' => '#0370EA',
					'css-attr' => 'color',
				),
				'anchor-color' => array(
					'type' => 'hex_color',
					'title' => t('anchor color'),
					'default' => '#666',
					'css-attr' => 'color',
				),
				'sub-color' => array(
					'type' => 'hex_color',
					'title' => t('Subcolor'),
					'default' => '#747C83',
					'css-attr' => 'color',
				),
			),
		),
	 // Base settings
	 'base' => array(
		 'title' => t('body'),
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '13',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			// 'transform' => array(
			//		'type' => 'transform',
			//		'default' => 'up',
			//	),
			),
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 1,
					)
				),
				// Hex color type
				'color' => array(
					'type' => 'hex_color',
					'title' => t('color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
				// rgba_color type
				'bgcolor' => array(
					'type' => 'hex_color',
					'title' => t('background color'),
					'default' => '#fff',
					'css-attr' => 'background-color',
				),
				//'bgcolor' => array(
				//	'type' => 'rgba_color',
				//	'title' => t('background color'),
				//	'default' => array(
				//		 'color' => '#fff',
				//		 'opacity' => 100,
				//		 'ie' => '#fff',
				//	 ),
				//	'css-attr' => 'background-color',
				//),
			),
			'less-var' =>  'body',
		),
	 
		// Inner Body
    'page' => array(
			'title' => t('page'),
			'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
			),
			'selector' => '.l-page',
    ),

	 // Top bar
	 'topbar' => array(
		 'title' => t('Top bar'),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
				// Hex color type
				'color' => array(
					'type' => 'hex_color',
					'title' => t('color'),
					'default' => '#747C83',
					'css-attr' => 'color',
				),
				'social-color' => array(
					'type' => 'hex_color',
					'title' => t('Social icons color'),
					'default' => '#747C83',
					'css-attr' => 'color',
				),
			),
		),
		// topbar divider
		'topbardivider' => array(
		 'title' => t('Top bar divider'),
		 'description' => '',
		 'parent' => 'topbar',
			'scheme' => array(
				'color' => array(
					'type' => 'rgba_color',
					'title' => t('color'),
					'default' => array(
						 'color' => '#DADEE1',
						 'opacity' => 100,
						 'ie' => '#DADEE1',
					 ),
				),
			),
		),
		// Header region
	 'header' => array(
		 'title' => t('Header'),
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '13',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			),
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'hex_color',
					'title' => t('background color'),
					'default' => '#ffffff',
					'css-attr' => 'background-color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
				'dividercolor' => array(
					'type' => 'hex_color',
					'title' => t('divider color'),
					'default' => '#E5E5E5',
				),
			),
		),
	 // fixed Header
	 'fixed_header' => array(
		 'title' => t('Fixed Header'),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
			),
		),
	 // Sub Header
	 'sub_header' => array(
		 'title' => t('Sub Header'),
		 'description' => '',
		 'parent' => 'header',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
				'dividercolor' => array(
					'type' => 'rgba_color',
					'title' => t('Divider color'),
					'default' => array(
						 'color' => '#e5e5e5',
						 'opacity' => 100,
						 'ie' => '#e5e5e5',
					 ),
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
			),
		),
	 
	 // Main Menu
	 'menu' => array(
		 'title' => t('Main menu'),
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '15',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '36',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
			'scheme' => array(
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
			),
		),
		// submenu typography
	 'submenu' => array(
		 'title' => t('Sub Menu'),
		 'description' => '',
		 'parent' => 'menu',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '14',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '32',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
			'scheme' => array(
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#666',
					'css-attr' => 'color',
				),
				'dividercolor' => array(
					'type' => 'hex_color',
					'title' => t('divider color'),
					'default' => '#E5E5E5',
				),
				'active_bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('Active - background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					//'css-attr' => 'background-color',
				),
			),
		),
	 
	 // headings
	 'heading' => array(
		 'title' => t('Headings'),
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
			),
			'scheme' => array(
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#333',
					'css-attr' => 'color',
				),
			),
		),
	 // H1
	 'h1' => array(
		 'title' => t('H1'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '52',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '52',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // H2
	 'h2' => array(
		 'title' => t('H2'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '38',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '50',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // H2
	 'h3' => array(
		 'title' => t('H3'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '24',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '34',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // H4
	 'h4' => array(
		 'title' => t('H4'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '18',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'up',
				),
			),
		),
	 
	 // H5
	 'h5' => array(
		 'title' => t('H5'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '16',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // H5
	 'h6' => array(
		 'title' => t('H6'),
		 'parent' => 'heading',
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '14',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	  // button
	 'button' => array(
		 'title' => t('Button'),
		 'description' => '',
			'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
			),
		),
	 
	 // X-Large Button
	 'btn_xl' => array(
		 'title' => t('X-large Button'),
		 'description' => '',
		 'parent' => 'button',
			'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '18',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '52',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
		// Large Button
	 'btn_l' => array(
		 'title' => t('Large Button'),
		 'description' => '',
		 'parent' => 'button',
			'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '15',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '44',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // Medium Button
	 'btn_m' => array(
		 'title' => t('Medium Button'),
		 'description' => '',
		 'parent' => 'button',
			'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '13',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '38',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
	 // Small Button
	 'btn_s' => array(
		 'title' => t('Small Button'),
		 'description' => '',
		 'parent' => 'button',
			'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '11',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '32',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'cap',
				),
			),
		),
	 
		//	Block title
	 'title' => array(
		 'title' => t('Block title'),
		 'description' => '',
		 'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '18',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'up',
				),
			),
		),
	 	 
		//	Block title
	 '_2nd_title' => array(
		 'title' => t('Node and portfolio views title'),
		 'description' => '',
		 'typo' => array(
				'ffamily' => array(
					'type' => 'font',
					'title' => t('Font family'),
					'css-attr' => 'font-family',
					'default' => '',
					'prefix' => '"',
					'suffix' => '"' .$default_font_family,
				),
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '18',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
			 'transform' => array(
					'type' => 'transform',
					'default' => 'up',
				),
			),
		),
	 
		// Slideshow
	 'slider' => array(
		 'title' => t('Slideshow region'),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#fff',
						 'opacity' => 100,
						 'ie' => '#fff',
					 ),
					'css-attr' => 'background-color',
				),
			),
		),
	 
	 // hero
	 'hero' => array(
		 'title' => t('Hero region'),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'repeat',
						 'posx' => 'center',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#F2F2F2',
						 'opacity' => 100,
						 'ie' => '#F2F2F2',
					 ),
					'css-attr' => 'background-color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#4C4C4C',
					'css-attr' => 'color',
				),
			),
		),
	 
	 'herodivider' => array(
		 'title' => t('Hero Divider'),
		 'description' => '',
		 'parent' => 'hero',
			'scheme' => array(
				'bordercolor' => array(
					'type' => 'rgba_color',
					'title' => t('Border color'),
					'default' => array(
						 'color' => 'rgba(0, 0, 0, 0.05)',
						 'opacity' => 100,
						 'ie' => '#E9E9E9',
					 ),
				),
			),
		),
	 // hero title
	 'hero_title' => array(
		 'title' => t('Hero titles'),
		 'description' => '',
		 'parent' => 'hero',
			'scheme' => array(
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#333',
					'css-attr' => 'color',
				),
			),
		),
	 
	 // Content region
	 'content' => array(
		 'title' => t('Content region'),
		 'description' => '',
			'scheme' => array(
				'dividercolor' => array(
					'type' => 'rgba_color',
					'title' => t('Divider color'),
					'default' => array(
						 'color' => '#e5e5e5',
						 'opacity' => 100,
						 'ie' => '#e5e5e5',
					 ),
				),
			),
		),
	 
	 // Meta
	 'meta' => array(
		 'title' => t('meta'),
		 'parent' => 'content',
		 'description' => '',
			'scheme' => array(
				'color' => array(
					'type' => 'hex_color',
					'title' => t('Meta color'),
					'default' => '#252525',
					'css-attr' => 'color',
				),
			),
		),
	 // light Gradient box
	 'gradient-light' => array(
		 'title' => t('Light gradient box'),
		 'parent' => 'content',
		 'description' => '',
			'scheme' => array(
				'topcolor' => array(
					'type' => 'hex_color',
					'title' => t('Start color'),
					'default' => '#FFF',
					'css-attr' => 'color',
				),
				'bottomcolor' => array(
					'type' => 'hex_color',
					'title' => t('Bottom color'),
					'default' => '#F9F9F9',
					'css-attr' => 'color',
				),
			),
		),

		// light Gradient box
	 'gradient-hard' => array(
		 'title' => t('Hard gradient box'),
		 'parent' => 'content',
		 'description' => '',
			'scheme' => array(
				'topcolor' => array(
					'type' => 'hex_color',
					'title' => t('Start color'),
					'default' => '#f7f7f7',
				),
				'bottomcolor' => array(
					'type' => 'hex_color',
					'title' => t('Bottom color'),
					'default' => '#ebebeb',
				),
			),
		),

		// Footer
	 'footer' => array(
		 'title' => t('Footer region'),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#1A1A1A',
						 'opacity' => 100,
						 'ie' => '#1A1A1A',
					 ),
					'css-attr' => 'background-color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('Text color'),
					'default' => '#B2B2B2',
					'css-attr' => 'color',
				),
				'anchorcolor' => array(
					'type' => 'hex_color',
					'title' => t('Anchor color'),
					'default' => '#DFDFDF',
					'css-attr' => 'color',
				),
				'bordercolor' => array(
					'type' => 'hex_color',
					'title' => t('Border color'),
					'default' => '#202020',
				),
			),
		),
	 // Footer
	 'footerheader' => array(
		 'title' => t('Footer headers'),
		 'description' => '',
		 'parent' => 'footer',
		 'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '18',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '26',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
		 ),
			'scheme' => array(
				'color' => array(
					'type' => 'hex_color',
					'title' => t('text color'),
					'default' => '#ffffff',
				),
			),
		),
	 'footerdivider' => array(
		 'title' => t('Footer divider'),
		 'description' => '',
			'scheme' => array(
				'bordercolor' => array(
					'type' => 'rgba_color',
					'title' => t('Divider color'),
					'default' => array(
						 'color' => 'rgba(255, 255, 255, 0.05)',
						 'opacity' => 100,
						 'ie' => '#242424',
					 ),
				),
			),
		),
		
		// Subfooter
	 'subfooter' => array(
		 'title' => t('Subfooter region'),
		 'description' => '',
		 'typo' => array(
				'fsize' => array(
					'type' => 'slider',
					'title' => t('Font size'),
					'default' => '13',
					'css-attr' => 'font-size',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
				'lheight' => array(
					'type' => 'slider',
					'title' => t('Line height'),
					'default' => '22',
					'css-attr' => 'line-height',
					'min' => 9,
					'max' => 70,
					'step' => 1,
					'data' => array(
						'val-suffix' => 'px',
					),
					'suffix' => 'px',
				),
		 ),
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'no-repeat',
						 'posx' => 'left',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#202020',
						 'opacity' => 100,
						 'ie' => '#202020',
					 ),
					'css-attr' => 'background-color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('Text color'),
					'default' => '#808080',
					'css-attr' => 'color',
				),
				'bordercolor' => array(
					'type' => 'hex_color',
					'title' => t('Border color'),
					'default' => '#1A1A1A',
				),
				'anchorcolor' => array(
					'type' => 'hex_color',
					'title' => t('Anchor color'),
					'default' => '#ACACAC',
				),
			),
		),
	);
 
 // Add section styles
	for ($i= 0; $i<3; $i++) {
		$styles['section_' .($i+1) .''] = array(
		 'title' => t('Section style @num', array('@num' => $i+1)),
		 'description' => '',
			'scheme' => array(
				'bg' => array(
					'type' => 'bg',
					'default' => array(
						 'image' => '',
						 'repeat' => 'repeat',
						 'posx' => 'center',
						 'posy' => 'top',
						 'full' => 0,
					)
				),
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#F3F3F3',
						 'opacity' => 100,
						 'ie' => '#F3F3F3',
					 ),
					'css-attr' => 'background-color',
				),
				'bordercolor' => array(
					'type' => 'rgba_color',
					'title' => t('Border color'),
					'default' => array(
						 'color' => '#eee',
						 'opacity' => 100,
						 'ie' => '#eee',
					 ),
				),
			),
		);
		
		$styles['section_' .($i+1) .'_text'] = array(
		 'title' => t('text'),
		 'parent' => 'section_' .($i+1) .'',
		 'description' => '',
			'scheme' => array(
				'headercolor' => array(
					'type' => 'hex_color',
					'title' => t('Header color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
				'color' => array(
					'type' => 'hex_color',
					'title' => t('color'),
					'default' => '#747474',
					'css-attr' => 'color',
				),
			),
		);
		
		$styles['section_' .($i+1) .'_frame'] = array(
		 'title' => t('Frames'),
		 'parent' => 'section_' .($i+1) .'',
		 'description' => '',
			'scheme' => array(
				'bgcolor' => array(
					'type' => 'rgba_color',
					'title' => t('background color'),
					'default' => array(
						 'color' => '#F3F3F3',
						 'opacity' => 100,
						 'ie' => '#F3F3F3',
					 ),
					'css-attr' => 'background-color',
				),
			),
		);
		$styles['section_' .($i+1) .'_divider'] = array(
		 'title' => t('Dividers & lines'),
		 'parent' => 'section_' .($i+1) .'',
		 'description' => '',
			'scheme' => array(
				'color' => array(
					'type' => 'rgba_color',
					'title' => t('Dividers & lines'),
					'default' => array(
						 'color' => '#eee',
						 'opacity' => 100,
						 'ie' => '#eee',
					 ),
				),
			),
		);
	}
	return $styles;
}
