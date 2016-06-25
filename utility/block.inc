<?php
/**
 *
 *
 */

/**
 * prepare auto generated blocks before display
 */
function acquia_prepare_block_display(&$block) {
    if (!isset($block->region)) {
        $block->region = '';
    }
    if (!isset($block->title)) {
        $block->title = '';
    }

    return $block;
}

/**
 * get block
 */
function acquia_get_block($module, $id, $check_for_cache = TRUE){
    $block = block_load('ac_slider', $header_slider['slid']);
    acquia_prepare_block_display($block);

    $block = array($block);
    $block_array = _block_render_blocks($block);

    foreach($block_array as &$_block){
        $_block->subject = '';
    }
    $vars['page']['slider'][] = _block_get_renderable_array($block_array);
}


