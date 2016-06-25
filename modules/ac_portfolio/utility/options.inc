<?php
/**
 * @file
 *  options helper functions 
 */

 /**
  * DiamondLayers Portfolio Thumbnail types
  */
function ac_portfolio_appearance(){
 return array(
   'masonry' => t('Masonry'),
   'grid' => t('Grid'),
   'multigrid' => t('Multigrid'),
   'scroller' => t('Scroller'),
   'slider' => t('Slider'),
   'thumb' => t('Thumbnail'),
 );
}

/**
  * ac_portfolio_gplus_effects
  */
function ac_portfolio_gplus_effects(){
 return array(
   'fly' => t('Fly'),
   'moveUp' => t('Move Up'),
   'fallPerspective' => t('Fall Perspective'),
   'flipTop' => t('Flip from top'),
   'flipHor' => t('Flip Horizontial'),
   'scaleUp' => t('Scale Up'),
 );
}

/**
  * DiamondLayers Portfolio Thumbnail types
  */
function ac_portfolio_thumb_types(){
 return array(
  '' => t('none'),
  'image' => t('Image'),
  'video' => t('Video'),
  'slider' => t('Slider - Images'),
 );
}

/**
  * ac_portfolio_node_layouts
  */
function ac_portfolio_node_layouts(){
 return array(
   'left' => t('Media on the left of content'),
   'right' => t('Media on the right of content'),
   'before' => t('Media before content area'),
   'after' => t('Media after content area'),
   'disabled' => t('Media disabled (Only description is show.)'),
 );
}

/**
  * DiamondLayers Portfolio Thumbnail Link types
  */
function ac_portfolio_thumb_link_types(){
 return array(
  'item' => t('Link to Item'),
  'url' => t('Link to URL'),
  'lightbox_thumb' => t('Lightbox to the thumbnail image'),
  'lightbox_image' => t('Lightbox to image (select below)'),
  'lightbox_link' => t('Lightbox to the thumbnail image and link to item'),
  'video' => t('Fullscreen Video Overlay (select below)'),
 );
}

/**
  * Item view styles
  */
function ac_portfolio_item_view_styles(){
  return array(
    'simple-sep' => t('Simple Seperated'),
    'simple-bordered' => t('Simple Bordered'),
    'dribbble' => t('Dribbble style'),
    'fade-in-bottom' => t('Fade In Bottom'),
    'dark-fade' => t('Dark fade'),
    'fade-in-left' => t('Fade In Left'),
    'overlaid-center' => t('overlaid center'),
    'overlaid-left' => t('overlaid left'),
    'overlaid-gradient' => t('overlaid Gradient'),
 );
}

/**
  * order types
  */
function ac_portfolio_orders(){
  return array(
    'created' => t('Simple Seperated'),
    'modified' => t('Simple Seperated'),
    'title' => t('Fade In Bottom'),
    'author' => t('overlaid center'),
    'id' => t('overlaid left'),
 );
}

/**
 * ac_portfolio_filter_styles
 */
function ac_portfolio_filter_styles() {
  return array(
    'simple centered' => t('Simple'),
    'simple sep' => t('Simple - seperated'),
    'fancy no-sep' => t('Facny'),
    'fancy sep' => t('Facny - Seperated'),
  );
}

/**
 * DiamondLayers Portfolio tags view
 */
function ac_portfolio_tags_view(){
 return array(
   'tagclouds' => t('Tagclouds'),
   'list' => t('List view'),
   'tag' => t('Tags view'),
 );
}

