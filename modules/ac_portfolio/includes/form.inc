<?php

function _ac_portfolio_node_form(&$form, &$form_state){
    // Just extracting and unserializing these keys
    $values = array();
    // editing saved node
    if (!isset($form_state['input']['portfolio_settings']) &&
        isset($form_state['node']->nid) &&
        isset($form_state['node']->nodemeta) &&
        is_array($form_state['node']->nodemeta)){
        $values = $form_state['node']->nodemeta;
    }else if (isset($form_state['input']['portfolio_settings'])) {
        $values = $form_state['input']['portfolio_settings'];
    }else {
        $values = array();
    }

    acquia_include('options');
    acquia_include('options', 'ac_portfolio');

    $form['#attached']['css'][] = drupal_get_path('module', 'ac_portfolio') . '/css/ac_portfolio.admin.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'ac_portfolio') . '/js/ac_portfolio.admin.js';

    $form['portfolio_settings'] = array(
        '#type' => 'container',
        '#prefix' => '<div class="ac-admin">',
        '#suffix' => '</div>',
        '#tree' => TRUE,
    );

    /** Thumnail Details **/
    $form['portfolio_settings']['thumb'] = array(
        '#type' => 'fieldset',
        '#title' => t('Portfolio Thumbnail'),
        '#collapsible' => TRUE,
    );
    $form['portfolio_settings']['thumb']['type'] = array(
        '#type' => 'select',
        '#title' => t('Thumbnail type'),
        '#description' => t('Choose what will be used for the item thumbnail.'),
        '#options' => ac_portfolio_thumb_types(),
        '#default_value' => isset($values['thumb']['type']) ? $values['thumb']['type'] : NULL,
    );

    if (!isset($form_state['ac_portfolio_thumb_nums']) && isset($values['thumb']['media'])) {
        $form_state['ac_portfolio_thumb_nums'] = count($values['thumb']['media']);
        $form_state['ac_portfolio_thumb_nums'] = $form_state['ac_portfolio_thumb_nums'] > 0 ? $form_state['ac_portfolio_thumb_nums'] : 1;
    }else if (!isset($form_state['ac_portfolio_thumb_nums'])) {
        $form_state['ac_portfolio_thumb_nums'] = 1;
    }

    $form['portfolio_settings']['thumb']['media'] = array(
        '#type' => 'fieldset',
        '#title' => t('Thumb assets'),
        '#prefix' => '<div id="ac-portfolio-thumbs">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#states' => array(
            'invisible' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => ''),
            ),
            'disabled' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => ''),
            ),
        ),
    );

    for ($i = 0; $i < $form_state['ac_portfolio_thumb_nums']; $i++) {
        $form['portfolio_settings']['thumb']['media'][$i]['file'] = array(
            '#type' => 'media',
            '#title' => t('Asset #@num file', array('@num' => $i +1)),
            '#default_value' => isset($values['thumb']['media'][$i]['fid']) ? $values['thumb']['media'][$i] : NULL,
            '#description' => '',
            '#media_options' => array(
                'global' => array(
                    'types' => array('image', 'video'),
                    'file_directory' => acquia_variable_get('public_path', 'acquia') . '/portfolio/misc',
                ),
            ),
        );
    }
    $form['portfolio_settings']['media']['add_thumbs'] = array(
        '#prefix' => '<div class="form-actions">',
        '#suffix' => '</div>',
        '#type' => 'submit',
        '#value' => t('Add another Image'),
        '#submit' => array('_ac_portfolio_node_form_add_thumb'),
        '#ajax' => array(
            'callback' => '_ac_portfolio_node_form_add_thumb',
            'wrapper' => 'ac-portfolio-thumbs',
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => 'slider'),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => 'slider'),
            ),
        ),
    );

    $form['portfolio_settings']['thumb']['link_type'] = array(
        '#type' => 'select',
        '#title' => t('Thumbnail link type'),
        '#description' => t('Choose what link will be used for the image(s) and title of the item.'),
        '#options' => ac_portfolio_thumb_link_types(),
        '#default_value' => isset($values['thumb']['link_type']) ? $values['thumb']['link_type'] : NULL,
        '#states' => array(
            'invisible' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => ''),
            ),
            'disabled' => array(
                ':input[name="portfolio_settings[thumb][type]"]' => array('value' => ''),
            ),
        ),
    );

    $form['portfolio_settings']['thumb']['link_image'] = array(
        '#type' => 'media',
        '#title' => t('Thumbnail link lightbox image'),
        '#description' => t('The image that will be used as the lightbox image.'),
        '#default_value' => isset($values['thumb']['link_image']) ? $values['thumb']['link_image'] : NULL,
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'lightbox_image'),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'lightbox_image'),
            ),
        ),
        '#media_options' => array(
            'global' => array(
                'types' => array('image'),
                'file_directory' => acquia_variable_get('public_path', 'acquia') . '/portfolio/img',
            ),
        ),
    );

    $form['portfolio_settings']['thumb']['link_video'] = array(
        '#type' => 'media',
        '#title' => t('Thumbnail link lightbox video'),
        '#description' => t('Select the video for the thumbnail lightbox.'),
        '#default_value' => isset($values['thumb']['link_video']) ? $values['thumb']['link_video'] : NULL,
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'video'),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'video'),
            ),
        ),
        '#media_options' => array(
            'global' => array(
                'types' => array('video'),
                'file_directory' => acquia_variable_get('public_path', 'acquia') . '/portfolio/video',
            ),
        ),
    );

    $form['portfolio_settings']['thumb']['link_url'] = array(
        '#type' => 'textfield',
        '#title' => t('URL'),
        '#description' => t('Enter the url for the thumbnail link.'),
        '#default_value' => isset($values['preview']['link_url']) ? $values['preview']['link_url'] : NULL,
        '#options' => ac_portfolio_thumb_link_types(),
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'url'),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[thumb][link_type]"]' => array('value' => 'url'),
            ),
        ),
    );

    /** Preview Settings **/
    $form['portfolio_settings']['preview'] = array(
        '#type' => 'fieldset',
        '#title' => t('Portfolio Preview'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
    );

    $form['portfolio_settings']['preview']['use_thumb'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the thumbnail content set above in preview?'),
        '#default_value' => isset($values['preview']['use_thumb']) && $values['preview']['use_thumb'] == false ?  FALSE : TRUE,
    );

    $form['portfolio_settings']['preview']['type'] = array(
        '#type' => 'select',
        '#title' => t('preview type'),
        '#description' => t('Choose what will be used for the post item detail.'),
        '#default_value' => isset($values['preview']['type']) ? $values['preview']['type'] : NULL,
        '#options' => array(
            'image' => t('Image'),
            'video' => t('Video'),
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
        ),
    );

    if (!isset($form_state['ac_portfolio_preview_nums']) && isset($values['preview']['media'])) {
        $form_state['ac_portfolio_preview_nums'] = count($values['preview']['media']);
    }else if (!isset($form_state['ac_portfolio_preview_nums'])) {
        $form_state['ac_portfolio_preview_nums'] = 1;
    }

    $form['portfolio_settings']['preview']['media'] = array(
        '#type' => 'fieldset',
        '#title' => t('Preview assets'),
        '#prefix' => '<div id="ac-portfolio-preview">',
        '#suffix' => '</div>',
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
        ),
        '#collapsible' => TRUE,
    );

    $preview_files = isset($values['preview']['media']) ? $values['preview']['media'] : array();
    if ($preview_files) {
        for ($i = 0; $i < $form_state['ac_portfolio_preview_nums']; $i++) {
            $form['portfolio_settings']['preview']['media'][$i]['file'] = array(
                '#type' => 'media',
                '#title' => t('Asset #@num file', array('@num' => $i +1)),
                '#default_value' => isset($preview_files[$i]['fid']) ? $preview_files[$i] : NULL,
                '#description' => '',
                '#media_options' => array(
                    'global' => array(
                        'types' => array('image', 'video'),
                        'file_directory' => acquia_variable_get('public_path', 'acquia') . '/portfolio/preview',
                    ),
                ),
            );

            $form['portfolio_settings']['preview']['media'][$i]['description'] = array(
                '#type' => 'textarea',
                '#title' => t('Asset #@num description', array('@num' => $i +1)),
                '#default_value' => isset($values['preview']['media'][$i]['description']) ? $values['preview']['media'][$i]['description'] : NULL,
                '#description' => '',
            );
        }
    }

    $form['portfolio_settings']['preview']['add_prev_item'] = array(
        '#prefix' => '<div class="form-actions">',
        '#suffix' => '</div>',   '#type' => 'submit',
        '#value' => t('Add another preview'),
        '#submit' => array('_ac_portfolio_node_form_add_preview'),
        '#ajax' => array(
            'callback' => '_ac_portfolio_node_form_add_preview',
            'wrapper' => 'ac-portfolio-preview',
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[preview][use_thumb]"]' => array('checked' => FALSE),
            ),
        ),
    );

    /** Preview Settings **/
    $form['portfolio_settings']['misc'] = array(
        '#type' => 'fieldset',
        '#title' => t('Portfolio Misc'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
    );

    /** Preview Settings **/
    $form['portfolio_settings']['misc']['excerpt'] = array(
        '#type' => 'text_format',
        '#title' => t('Excerpt'),
        '#description' => t('Enter some content to be shown on node teaser view.'),
        '#default_value' => isset($values['misc']['excerpt']['value']) ? $values['misc']['excerpt']['value']: '',
        '#format' => isset($values['misc']['excerpt']['format']) ? $values['misc']['excerpt']['format']: NULL,
        '#rows' => 15,
    );

    $form['portfolio_settings']['misc']['link'] = array(
        '#type' => 'textfield',
        '#title' => t('Project Link'),
        '#description' => t('Enter an external link for the item (optional) (NOTE: INCLUDE HTTP://).'),
        '#default_value' => isset($values['misc']['link']) ? $values['misc']['link']: '',
    );

    $form['portfolio_settings']['misc']['link_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Project Link title'),
        '#description' => t('Enter a title for the external link of item (optional).'),
        '#default_value' => isset($values['misc']['link_title']) ? $values['misc']['link_title']: '',
        '#states' => array(
            'invisible' => array(
                ':input[name="portfolio_settings[misc][link]"]' => array('value' => ''),
            ),
            'disabled' => array(
                ':input[name="portfolio_settings[misc][link]"]' => array('value' => ''),
            ),
        ),
    );

    $form['portfolio_settings']['misc']['layout'] = array(
        '#prefix' => '<div class="ac-clone-options">',
        '#suffix' => '</div>',   '#type' => 'radios',
        '#title' => t('Media display layout'),
        '#options' => ac_portfolio_node_layouts(),
        '#description' => '',
        '#default_value' => isset($values['misc']['layout']) ? $values['misc']['layout']: 'left',
    );

    $form['portfolio_settings']['misc']['custom_frame'] = array(
        '#type' => 'checkbox',
        '#title' => t('Custom frame?'),
        '#description' => '',
        '#default_value' => isset($values['misc']['custom_frame']) ? $values['misc']['custom_frame'] : FALSE,
    );

    // Default image frame of gallery images
    $form['portfolio_settings']['misc']['frame']= array(
        '#type' => 'select',
        '#title' => t('Frame style'),
        '#description' => t('Note: you can set a global frame for all portfolio media items from !url', array('!url' => l('DiamondLayers portfolio setting page', 'admin/acquia/ac-portfolio'))),
        '#options' => acquia_image_frame_list(),
        '#default_value' => isset($values['misc']['frame']) ? $values['misc']['frame'] : NULL,
        '#states' => array(
            'visible' => array(
                ':input[name="portfolio_settings[misc][custom_frame]"]' => array('checked' => TRUE),
            ),
            'enabled' => array(
                ':input[name="portfolio_settings[misc][custom_frame]"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['portfolio_settings']['misc']['view'] = array(
        '#prefix' => '<div class="ac-clone-options">',
        '#suffix' => '</div>',
        '#type' => 'radios',
        '#title' => t('Media view type'),
        '#options' => array('slideshow' => t('Slideshow'), 'gallery' => t('Gallery'), 'list' => t('List')),
        '#description' => '',
        '#default_value' => isset($values['misc']['view']) ? $values['misc']['view']: 'list',
    );

    $form['portfolio_settings']['misc']['display'] = array(
        '#type' => 'select',
        '#title' => t('Media Display'),
        '#options' => array('fullwidth' => t('Full width'), 'standard' => t('standard')),
        '#description' => '',
        '#default_value' => isset($values['misc']['display']) ? $values['misc']['display']: 'standard',
    );

    $form['portfolio_settings']['misc']['columns'] = array(
        '#type' => 'select',
        '#title' => t('Media Columns'),
        '#options' => drupal_map_assoc(range(1,6)),
        '#description' => '',
        '#default_value' => isset($values['misc']['columns']) ? $values['misc']['columns']: variable_get('ac_portfolio_gallery_columns', 1),
    );

    $form['portfolio_settings']['misc']['spaced'] = array(
        '#type' => 'checkbox',
        '#title' => t('Spaced items?'),
        '#description' => '',
        '#default_value' => isset($values['misc']['spaced']) ? $values['misc']['spaced'] : variable_get('ac_portfolio_gallery_spaced', TRUE),
    );

    $form['portfolio_settings']['misc']['meta'] = array(
        '#attributes' => array('data-help' => t('Display node tags, date, project link, likes?')),
        '#type' => 'checkbox',
        '#title' => t('Display node meta?'),
        '#default_value' => isset($values['misc']['meta']) ? $values['misc']['meta'] : FALSE,
    );

    $form['portfolio_settings']['misc']['social'] = array(
        '#type' => 'checkbox',
        '#title' => t('Include social sharing?'),
        '#default_value' => isset($values['misc']['social']) ? $values['misc']['social'] : TRUE,
    );

    $form['#submit'][] = '_ac_portfolio_node_form_submit';
}