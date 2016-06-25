<?php
/**
 * @file
 *  options helper functions 
 */

/**
 * Get list of supported image frames
 */
function ac_block_settings_menu_styles() {
 return array(
   'ac-menu ac-menu-v' => t('Simple Vertical'),
   'ac-menu ac-simple-menu-h' => t('Simple Horizontal'),
   'ac-menu ac-menu-h' => t('Simple Horizontal bordered'),
   'ac-menu ac-menu-v ac-menu-borderd' => t('Simple vertical bordered'),
   'ac-menu ac-menu-v ac-fancy-menu' => t('Fancy vertical'),
   'ac-menu ac-menu-v ac-fancy-menu ac-menu-borderd' => t('Fancy vertical bordered'),
   'ac-menu ac-menu-v ac-fancy-menu ac-menu-borderd ac-menu-gradient' => t('Fancy vertical bordered + fancy background'),
 );
}

/**
 *
 * return array(
  'ac-simple-menu-v' => t('Simple Vertical'),
  'ac-simple-menu-h' => t('Simple Horizontal'),
  'ac-side-menu' => t('Simple bordered'),
  'ac-side-menu ac-fancy-menu' => t('Fancy Sidebar Menu'),
 );
 */
