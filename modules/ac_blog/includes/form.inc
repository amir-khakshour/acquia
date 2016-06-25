<?php
/**
 * @todo Document here
 */
function _ac_blog_node_form(&$form, &$form_state){
    // Just extracting and unserializing these keys
    $values = array();
    // editing saved node
    if (!isset($form_state['input']['blog_settings']) &&
        isset($form_state['node']->nid) &&
        isset($form_state['node']->nodemeta) &&
        is_array($form_state['node']->nodemeta)){
        $values = $form_state['node']->nodemeta;
    }else if (isset($form_state['input']['blog_settings'])) {
        $values = $form_state['input']['blog_settings'];
    }else {
        $values = array();
    }

    acquia_include('options');

    $form['blog_settings'] = array(
        '#type' => 'container',
        '#prefix' => '<div class="ac-admin">',
        '#suffix' => '</div>',
        '#tree' => TRUE,
    );

    /** Thumnail Details **/
    $form['blog_settings']['thumb'] = array(
        '#type' => 'fieldset',
        '#title' => t('blog Thumbnail'),
        '#collapsible' => TRUE,
    );
    $form['blog_settings']['thumb']['type'] = array(
        '#type' => 'select',
        '#title' => t('Thumbnail type'),
        '#description' => t('Choose what will be used for the item thumbnail.'),
        '#options' => array(
            '' => t('none'),
            'image' => t('Image'),
            'video' => t('Video'),
            'slider' => t('Slider - Images'),
        ),
        '#default_value' => isset($values['thumb']['type']) ? $values['thumb']['type'] : NULL,
    );

    if (!isset($form_state['ac_blog_thumb_nums']) && isset($values['thumb']['media'])) {
        $form_state['ac_blog_thumb_nums'] = count($values['thumb']['media']);
        $form_state['ac_blog_thumb_nums'] = $form_state['ac_blog_thumb_nums'] > 0 ? $form_state['ac_blog_thumb_nums'] : 1;
    }else if (!isset($form_state['ac_blog_thumb_nums'])) {
        $form_state['ac_blog_thumb_nums'] = 1;
    }

    $form['blog_settings']['thumb']['media'] = array(
        '#type' => 'fieldset',
        '#title' => t('Thumb assets'),
        '#prefix' => '<div id="ac-blog-thumbs">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#states' => array(
            'invisible' => array(
                ':input[name="blog_settings[thumb][type]"]' => array('value' => ''),
            ),
            'disabled' => array(
                ':input[name="blog_settings[thumb][type]"]' => array('value' => ''),
            ),
        ),
    );
    dpm($values['thumb']);
    for ($i = 0; $i < $form_state['ac_blog_thumb_nums']; $i++) {
        // Backward compatiblity
        // @todo depricate this
        if (isset($values['thumb']['media'][$i])) {
            $fid = acquia_get_media_field($values['thumb']['media'][$i]);
        }else{
            $fid = 0;
        }
        dpm($fid);
        $form['blog_settings']['thumb']['media'][$i]['file'] = array(
            '#type' => 'media',
            '#title' => t('Asset #@num file', array('@num' => $i +1)),
            '#default_value' => $fid,
            '#description' => '',
            '#media_options' => array(
                'global' => array(
                    'types' => array('image', 'video'),
                    'file_directory' => acquia_variable_get('public_path', 'acquia') . '/blog/misc',
                ),
            ),
        );
    }
    $form['blog_settings']['media']['add_thumbs'] = array(
        '#prefix' => '<div class="form-actions">',
        '#suffix' => '</div>',
        '#type' => 'submit',
        '#value' => t('Add another Image'),
        '#submit' => array('_ac_blog_node_form_add_thumb'),
        '#ajax' => array(
            'callback' => '_ac_blog_node_form_add_thumb',
            'wrapper' => 'ac-blog-thumbs',
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="blog_settings[thumb][type]"]' => array('value' => 'slider'),
            ),
            'enabled' => array(
                ':input[name="blog_settings[thumb][type]"]' => array('value' => 'slider'),
            ),
        ),
    );

    /** Preview Settings **/
    $form['blog_settings']['misc'] = array(
        '#type' => 'fieldset',
        '#title' => t('blog Misc'),
        '#collapsible' => TRUE,
        '#tree' => TRUE,
    );

    /** Preview Settings **/
    $form['blog_settings']['misc']['excerpt'] = array(
        '#type' => 'text_format',
        '#title' => t('excerpt'),
        '#description' => t('Enter a excerpt for use within the blog item index (optional).'),
        '#default_value' => isset($values['misc']['excerpt']['value']) ? $values['misc']['excerpt']['value']: '',
        '#format' => isset($values['misc']['excerpt']['format']) ? $values['misc']['excerpt']['format']: NULL,
        '#rows' => 15,
    );

    $form['blog_settings']['misc']['custom_frame'] = array(
        '#type' => 'checkbox',
        '#title' => t('Custom frame?'),
        '#description' => '',
        '#default_value' => isset($values['misc']['custom_frame']) ? $values['misc']['custom_frame'] : FALSE,
    );

    // Default image frame of gallery images
    $form['blog_settings']['misc']['frame']= array(
        '#type' => 'select',
        '#title' => t('Frame style'),
        '#description' => t('Note: you can set a global frame for all blog media items from !url', array('!url' => l('DiamondLayers blog setting page', 'admin/acquia/ac-blog'))),
        '#options' => acquia_image_frame_list(),
        '#default_value' => isset($values['misc']['frame']) ? $values['misc']['frame'] : NULL,
        '#states' => array(
            'visible' => array(
                ':input[name="blog_settings[misc][custom_frame]"]' => array('checked' => TRUE),
            ),
            'enabled' => array(
                ':input[name="blog_settings[misc][custom_frame]"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['blog_settings']['misc']['about_author'] = array(
        '#type' => 'checkbox',
        '#title' => t('Display about author block?'),
        '#default_value' => isset($values['misc']['about_author']) ? $values['misc']['about_author'] : TRUE,
    );

    $form['#submit'][] = '_ac_blog_node_form_submit';
}