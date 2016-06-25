<?php
// $id
/**
 * Options used in select form elements
 */

/**
 *
 */
function ac_blog_related_views() {
  return array(
    'circled' => t('Circled thumbnail'),
    'teaser' => t('Teaser'),
  );
}


/**
  * Item view styles
  */
function ac_blog_item_view_styles(){
  return array(
    'simple-sep' => t('Simple Seperated'),
    'timeline' => t('Timeline style'),
 );
}

/**
  * Item view styles
  */
function ac_blog_appearance(){
  return array(
    'teaser' => t('Teaser'),
    'circled' => t('Circled'),
    'masonry' => t('Masonry'),
    'grid' => t('Grid'),
    'scroller' => t('Scroller'),
    'timeline' => t('Timeline'),
  );
}
