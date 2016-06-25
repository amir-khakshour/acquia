<?php
/**
 * @file
 * Default DiamondLayers context
 */
define('ACQUIA_CONTEXT_FRONT', 'front-page');
define('ACQUIA_CONTEXT_NO_SIDES_MN', 'no-sidebars');
define('ACQUIA_CONTEXT_FULLWIDTH', 'full-width');
define('ACQUIA_CONTEXT_FULLWIDTH_NO_FOOTER', 'full-width-no-footer');
define('ACQUIA_CONTEXT_FULLWIDTH_NO_TOP_FOOTER', 'full-width-no-topbar-footer');
define('ACQUIA_CONTEXT_1ST_SIDEBAR_MN', 'first-sidebar');
define('ACQUIA_CONTEXT_2ND_SIDEBAR_MN', 'second-sidebar');
define('ACQUIA_CONTEXT_3_COLUMNS_MN', 'three-columns');
define('ACQUIA_CONTEXT_404_MN', '404page');
define('ACQUIA_CONTEXT_TAXONOMY_MN', 'taxonomy');


/**
 * Implements hook_ctools_plugin_api().
 */
function acquia_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_context_default_contexts().
 */
function acquia_context_default_contexts() {
  $export = array();

  /* FRONT PAGE
   *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_FRONT;
  $context->description = 'full width layout with no margins ';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-full',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'topbar' => 0,
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 'highlighted',
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'topbar' => 0,
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 'highlighted',
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('full width layout with no margins ');

  $export[ACQUIA_CONTEXT_FRONT] = $context;

  /* 1st sidebar
   *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_1ST_SIDEBAR_MN;
  $context->description = 'first sidebar and main content regions enabled.';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array(
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_second' => 'sidebar_second',
          'topbar' => 0,
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sidebar_first' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_second' => 'sidebar_second',
          'topbar' => 0,
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sidebar_first' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('first sidebar and main content regions enabled.');
  $export[ACQUIA_CONTEXT_1ST_SIDEBAR_MN] = $context;

  /* Full Width
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_FULLWIDTH;
  $context->description = 'full width layout with no margins ';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-full',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('full width layout with no margins ');
  $export[ACQUIA_CONTEXT_FULLWIDTH] = $context;

  /* No Sidebars
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_NO_SIDES_MN;
  $context->description = 'first and last sidebars disabled.';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array(
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('first and last sidebars disabled.');
  $export[ACQUIA_CONTEXT_NO_SIDES_MN] = $context;

  /* 2nd Sidebar
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_2ND_SIDEBAR_MN;
  $context->description = 'second sidebar and main content regions enabled.';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~*' => '~*',
      ),
    ),
  );
  $context->reactions = array(
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'sidebar_second' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'sidebar_second' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('second sidebar and main content regions enabled.');
  $export[ACQUIA_CONTEXT_2ND_SIDEBAR_MN] = $context;

  /* Three column
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_3_COLUMNS_MN;
  $context->description = 'Three columns layout, first sidebar, main content and second sidebar enabled.';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Three columns layout, first sidebar, main content and second sidebar enabled.');
  t('DiamondLayers page layout');
  $export[ACQUIA_CONTEXT_3_COLUMNS_MN] = $context;



  /* Taxonomy
  *---------------------------------------------------------*/
  // Taxonomy Context
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_TAXONOMY_MN;
  $context->description = 'taxonomy page view';
  $context->tag = 'taxonomy';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'taxonomy/*' => 'taxonomy/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-default',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sidebar_second' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sidebar_second' => 0,
          'footer' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),

    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('taxonomy');
  t('taxonomy page view');
  $export[ACQUIA_CONTEXT_TAXONOMY_MN] = $context;


  /* 404 page
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_404_MN;
  $context->description = '404 page layout';
  $context->tag = 'DiamondLayers Context';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-default',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'slider' => 'slider',
          'highlighted' => 'highlighted',
          'content_top' => 'content_top',
          'node_top' => 'node_top',
          'node_bottom' => 'node_bottom',
          'content_bottom' => 'content_bottom',
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'footer' => 'footer',
          'footer_bottom' => 'footer_bottom',
          'sub_footer' => 'sub_footer',
          'topbar' => 0,
          'header' => 0,
          'sub_menu' => 0,
          'help' => 0,
          'content' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'bartik' => array(
        'disable' => array(
          'header' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'highlighted' => 0,
          'featured' => 0,
          'content' => 0,
          'sidebar_first' => 0,
          'sidebar_second' => 0,
          'triptych_first' => 0,
          'triptych_middle' => 0,
          'triptych_last' => 0,
          'footer_firstcolumn' => 0,
          'footer_secondcolumn' => 0,
          'footer_thirdcolumn' => 0,
          'footer_fourthcolumn' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'omega' => array(
        'disable' => array(
          'branding' => 0,
          'header' => 0,
          'navigation' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content' => 0,
          'sidebar_first' => 0,
          'sidebar_second' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'seven' => array(
        'disable' => array(
          'content' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'sidebar_first' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'stark' => array(
        'disable' => array(
          'sidebar_first' => 0,
          'sidebar_second' => 0,
          'content' => 0,
          'header' => 0,
          'footer' => 0,
          'highlighted' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('404 page layout');
  t('DiamondLayers Context');

  $export[ACQUIA_CONTEXT_404_MN] = $context;


  /* full width layout with no margins and footer region
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_FULLWIDTH_NO_FOOTER;
  $context->description = 'full width layout with no margins and footer region';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-full',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'footer' => 'footer',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'footer' => 'footer',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('full width layout with no margins and footer region');

  $export[ACQUIA_CONTEXT_FULLWIDTH_NO_FOOTER] = $context;

  /* full width layout with no margins, topbar and footer region
  *---------------------------------------------------------*/
  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = ACQUIA_CONTEXT_FULLWIDTH_NO_TOP_FOOTER;
  $context->description = 'full width layout with no margins, topbar and footer region';
  $context->tag = 'DiamondLayers page layout';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'aura-full',
    ),
    'region' => array(
      'aura' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'footer' => 'footer',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'aura_sub' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'footer' => 'footer',
          'header' => 0,
          'slider' => 0,
          'sub_menu' => 0,
          'highlighted' => 0,
          'help' => 0,
          'content_top' => 0,
          'node_top' => 0,
          'content' => 0,
          'node_bottom' => 0,
          'content_bottom' => 0,
          'sub_footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('DiamondLayers page layout');
  t('full width layout with no margins, topbar and footer region');

  $export[ACQUIA_CONTEXT_FULLWIDTH_NO_TOP_FOOTER] = $context;
  return $export;
}
