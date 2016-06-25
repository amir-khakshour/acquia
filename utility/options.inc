<?php
/**
 * @file
 *  options helper functions
 */

/**
 * Add default option to the given list
 */
function add_default_option(&$list) {
    $list = array('sw' => t('Sitewide Default')) + $list;
}

/**
 * Add default option to the given list
 */
function acquia_get_default_value($field, $values, $default) {
    return isset($values[$field]) ? $values[$field] : $default;
}

/**
 * List of css background-position attribute values
 */
function acquia_css_background_position() {
    return array(
        'top left' => t('Top Left'),
        'top center' => t('Top Center'),
        'top right' => t('Top Right'),
        'bottom left' => t('Bottom Left'),
        'bottom center' => t('Bottom Center'),
        'bottom right' => t('Bottom Right'),
        'center left' => t('Center Left'),
        'center center' => t('Center Center'),
        'center right' => t('Center Right'),
    );
}

/**
 *
 */
function acquia_column_class_to_width() {
    return array(
        'ac-fullwidth' => t('1/1'),
        'ac-one-half' => t('1/2'),
        'ac-one-third' => t('1/3'),
        'ac-one-fourth' => t('1/4'),
        'ac-one-fifth' => t('1/5'),
        'ac-two-third' => t('2/3'),
        'ac-two-fifth' => t('2/5'),
        'ac-three-fourth' => t('3/4'),
        'ac-three-fifth' => t('3/5'),
        'ac-four-fifth' => t('4/5'),
        'ac-five-sixth' => t('5/6'),
    );
}

/**
 *
 */
function acquia_column_width_to_class() {
    return array(
        '1/1' => 'ac-fullwidth',
        '1/2' => 'ac-one-half',
        '1/3' => 'ac-one-third',
        '1/4' => 'ac-one-fourth',
        '1/5' => 'ac-one-fifth',
        '1/6' => 'ac-one-sixth',
        '2/3' => 'ac-two-third',
        '2/5' => 'ac-two-fifth',
        '3/4' => 'ac-three-fourth',
        '3/5' => 'ac-three-fifth',
        '4/5' => 'ac-four-fifth',
        '5/6' => 'ac-five-sixth',
    );
}

/**
 * List of css background-repeat attribute values
 */
function acquia_css_background_repeat() {
    return array(
        'no-repeat' => t('No Repeat'),
        'repeat' => t('Repeat'),
        'repeat-x' => t('Tile Horizontally'),
        'repeat-y' => t('Tile Vertically'),
        'stretch' => t('Stretch to fit'),
    );
}

/**
 * List of css background-repeat attribute values
 */
function acquia_css_background_attachment() {
    return array(
        'scroll' => t('Scroll'),
        'fixed' => t('Fixed'),
    );
}

/**
 * List of internal padding types
 */
function acquia_padding() {
    return array(
        'zero' => t('No Padding'),
        'small' => t('Small Padding'),
        'default' => t('Default Padding'),
        'large' => t('Large Padding'),
        'x-large' => t('X-Large Padding'),
        'xx-large' => t('XX-Large Padding'),
        'xxx-large' => t('XXX-Large Padding'),
    );
}

/**
 * List of internal margin types
 */
function acquia_margin() {
    return array(
        'zero' => t('No Margin'),
        'x-small' => t('X-Small Margin'),
        'small' => t('Small Margin'),
        'default' => t('Medium Margin'),
        'large' => t('Large Margin'),
    );
}

/**
 * get list of dividers type
 */
function acquia_dividers_list() {
    return array(
        'shadow' => t('Shadow'),
        'thick_solid' => t('Thick solid line'),
        'thin_solid' => t('Thin solid line'),
        'line' => t('Solid Line'),
        'single_dotted' => t('Single dotted line'),
        'go_top' => t('Go to top'),
        'double_solid' => t('Double solid line'),
        'double_dot' => t('Double dot line'),
        'invisible' => t('Whitespace'),
        'icon' => t('Icon Divider'),
    );
}

/**
 * get list of theme skins
 */
function acquia_skins_list() {
    return array(
        'white' => t('White'),
        'blue' => t('Blue'),
        'red' => t('Red'),
        'green' => t('Green'),
        'orange' => t('Orange'),
        'aqua' => t('Aqua'),
        'teal' => t('Teal'),
        'purple' => t('Purple'),
        'pink' => t('Pink'),
        'silver' => t('Silver'),
        'grey' => t('Grey'),
        'black' => t('Black'),
    );
}

/**
 * get list of default size classes
 */
function acquia_sizes_list() {
    return array(
        'tiny' => t('Tiny'),
        'small' => t('Small'),
        'medium' => t('Medium'),
        'large' => t('Large'),
        'x-large' => t('X-Large'),
        'xx-large' => t('XX-Large'),
        'xxx-large' => t('XXX-Large'),
    );
}

/**
 * get list of alignment
 */
function acquia_align_list() {
    return array(
        'left' => t('Left'),
        'center' => t('Center'),
        'right' => t('Right'),
    );
}

/**
 * Get list of supported CSS animations
 */
function acquia_css_animate_list() {
    acquia_include('utility');
    $anims = array_merge(drupal_map_assoc(acquia_css_animate_extract_animation()), acquia_theme_anims());
    return $anims;
}

/**
 * Built in theme animation
 */
function acquia_theme_anims(){
    return array(
        //'ac_appear' => t('DiamondLayers Appear'),
        'ac_appear' => t('DiamondLayers Appear'),
        'ac-flip-x' => t('DiamondLayers Flip Horizontally'),
        'ac-flip-y' => t('DiamondLayers flip Vertically'),
    );
}

/**
 * Get list of supported animate point list
 */
function acquia_animate_point_list() {
    return array(
        'visible' => t('Animate when it\'s visible'),
        'almost_visible' => t('Animate when it\'s almost visible'),
    );
}

/**
 * List of HTML header tags
 */
function acquia_header_tags() {
    $tags = &drupal_static(__FUNCTION__);
    if (!isset($tags)) {
        $tags = array();
        for ($i = 1; $i<=6; $i++) {
            $tags['h' . $i . ''] = t('H' . $i  . '');
        }
    }
    return $tags;
}

/**
 * acquia_header_styles
 */
function acquia_header_styles() {
    return array(
        '' => t('None'),
        'subtitle' => t('Subtitle'),
        'strong' => t('Strong'),
        'special' => t('Special'),
    );
}

/**
 * List of fancy header styles
 */
function acquia_fancy_header_styles() {
    return array(
        'single_thin_bottom' => t('Single thin bottom line'),
        'single_thick_bottom' => t('Single thick bottom line'),
        'double_solid_thick_bottom' => t('Double solid and thick bottom line'),
        'double_solid' => t('Double solid line'),
        'single_line_centered' => t('Single Line centered'),
        'title_borderd' => t('Title bordered'),
    );
}

/**
 *  rollover_types
 */
function acquia_rollover_types() {
    return array(
        'none' => t('<none>'),
        'slideInBottom' => t('slide In Bottom'),
    );
}

/**
 * Get list of supported image frames
 */
function acquia_image_frame_list() {
    return array(
        'none' => t('<none>'),
        'simple' => t('simple'),
        'simple-bordered' => t('Simple bordered'),
        'bordered' => t('Gray bordered'),
        'rounded_borders' => t('Rounded - Borders'),
        'bordered_glow' => t('Glow bordered'),
        'dropshadow' => t('Drop shadow'),
        'bottomshadow' => t('Bottom shadow'),
        'circled' => t('Circled frame'),
        'circled_simple' => t('Circled simple frame'),
        'glow_circled' => t('Glow Circled'),
        'glow_circled_border' => t('Glow circled border'),
        'silver' => t('Silver style'),
    );
}

/**
 * Get list of supported video frames
 */
function acquia_video_frame_list() {
    return array(
        'none' => t('<none>'),
        'simple' => t('simple'),
        'bordered' => t('Gray bordered frame'),
        'rounded_borders' => t('Rounded - Borders frame'),
        'bordered_glow' => t('Glow border frame'),
        'dropshadow' => t('Drop shadow frame'),
        'bottomshadow' => t('Bottom shadow frame'),
        'silver' => t('Silver styled frame'),
    );
}

/**
 * acquia_image_effects
 */
function acquia_image_effects() {
    return array(
        'none' => t('<none>'),
        'overlay' => t('Overlay Effect'),
        'blur' => t('Blur Effect'),
        'zoom' => t('Zoom Image Effect'),
    );
}


/**
 * Get list of supported Columns
 */
function acquia_columns_list() {
    return array(
        'ac_fullwidth'    => t('1/1'),
        'ac_one_half'     => t('1/2'),
        'ac_one_third'    => t('1/3'),
        'ac_two_third'    => t('2/3'),
        'ac_one_fourth'   => t('1/4'),
        'ac_three_fourth' => t('3/4'),
        'ac_one_fifth'    => t('1/5'),
        'ac_one_sixth'    => t('1/6'),
        'ac_five_sixth'   => t('5/6'),
    );
}

/**
 *
 */
function acquia_column_numbers_map() {
    return array(
        'ac_fullwidth'    => 1,
        'ac_one_half'     => 1/2,
        'ac_one_third'    => 1/3,
        'ac_two_third'    => 2/3,
        'ac_one_fourth'   => 1/4,
        'ac_three_fourth' => 3/4,
        'ac_one_fifth'    => 1/5,
        'ac_one_sixth'    => 1/6,
        'ac_five_sixth'   => 5/6,
    );
}

/**
 *
 */
function acquia_spans() {
    return array(
        'span1' => t('span1'),
        'span2' => t('span2'),
        'span3' => t('span3'),
        'span4' => t('span4'),
        'span5' => t('span5'),
        'span6' => t('span6'),
        'span7' => t('span7'),
        'span8' => t('span8'),
        'span9' => t('span9'),
        'span10' => t('span10'),
        'span11' => t('span11'),
        'span12' => t('span12'),
    );
}

/**
 * Button Styles
 */
function acquia_button_styles() {
    return array(
        '2d' => t('2D'),
        '2d-soft' => t('2D - Soft'),
        '3d' => t('3D'),
        'subtle' => t('Subtle'),
        'subtle-fade' => t('Subtle fade icon'),
        'bordered' => t('Bordered'),
        'flip' => t('Flip'),
    );
}

/**
 * Button Types
 */
function acquia_btn_border_types() {
    return array(
        'square' => t('Square'),
        'rounded' => t('Rounded'),
        'pill' => t('Pill'),
        'rounded-soft' => t('Rounded soft'),
    );
}

/**
 * acquia_icon_types
 */
function acquia_icon_types() {
    return array(
        'simple' => t('simple - no background and no border'),
        'simple-bordered' => t('simple - Bordered'),
        'square' => t('Square'),
        'rounded' => t('Rounded'),
        'rounded-soft' => t('Rounded soft'),
        'circled' => t('Circled'),
    );
}

/**
 * acquia_iconbox_border_types
 */
function acquia_iconbox_border_types() {
    return array(
        'square' => t('Square'),
        'rounded' => t('Rounded'),
        'circled' => t('Circled'),
    );
}

/**
 * Message Box Types
 */
function acquia_message_box_types() {
    return array(
        'green' => t('Success (Green)'),
        'blue' => t('Notification (Blue)'),
        'red' => t('Warning (Red)'),
        'orange' => t('Alert (Orange)'),
        'silver' => t('Neutral (Light Grey)'),
        'silver_dark' => t('Neutral (Dark Grey)'),
    );
}

/**
 * Fancy Quote Types
 */
function acquia_quote_types() {
    return array(
        'blockquote' => t('Blockquote'),
        'pullquote' => t('Pullquote'),
    );
}

/**
 * Font Sizes
 */
function acquia_font_sizes() {
    return array(
        'normal' => t('Normal'),
        'small' => t('Small'),
        'big' => t('Big'),
        'bigger' => t('Bigger'),
    );
}

/**
 *
 */
function acquia_menu_types() {
    return array(
        'mm-simple mm-fade-from-bottom' => t('Simple fade from bottom'),
        'mm-simple mm-fade-from-top' => t('Simple fade from top'),
        'mm-simple mm-fade-from-in' => t('Simple fade in'),
        'mm-top-bordered' => t('Top bordered - fade in'),
        'mm-bottom-bordered' => t('Bottom bordered - fade in'),
        'mm-full-bordered' => t('Full bordered fade in'),
        'mm-full-bordered mm-full-bg' => t('Full background fade in'),
    );
}


/**
 * acquia_header_layouts
 */
function acquia_header_layouts() {
    return array(
        'left' => t('Left aligned'),
        'center' => t('Center aligned'),
        'classic' => t('Classic'),
        'classic-centered' => t('Classic centered'),
    );
}

/**
 * Icon Box Types
 */
function acquia_iconbox_types() {
    return array(
        'simple' => t('Simple - Bordered'),
        'simple no-border' => t('Simple - No Border'),
        'simple full' => t('Simple - Full background'),
        'inline' => t('Inline with header'),
        'inline-sep' => t('Inline with header - Seperated icon'),
        'boxed-simple' => t('Boxed simple'),
        'boxed-fancy' => t('Boxed fancy'),
        'boxed-inline' => t('Boxed inline'),
        'boxed-animated' => t('Boxed animated'),
    );
}

/**
 * Team Box type
 */
function acquia_team_types() {
    return array(
        'simple' => t('simple'),
        'simple glow' => t('simple glow'),
        'simple compact' => t('simple Compact'),
        'simple circled' => t('Simple Circled'),
        'overlaid' => t('Overlaid description'),
        'blur' => t('Blured image'),
        'columns' => t('Columns'),
    );
}

/**
 * Team Box effects
 */
function acquia_google_map_types() {
    return array(
        'roadmap' => t('Default'),
        'satellite' => t('Satellite'),
        'hybrid' => t('Hybrid'),
        'terrain' => t('Terrain'),
        'cartoon' => t('Cartoon'),
        'grey' => t('Grey'),
        'light_grey' => t('Light Grey'),
        'ultra_light' => t('Ultra Light with Labels'),
        'bw' => t('Black & White'),
        'night' => t('Night'),
        'night_light' => t('Night light'),
        'retro' => t('Retro'),
        'papiro' => t('Papiro'),
        'bwater' => t('Blue water'),
    );
}

/**
 * Border Types
 */
function acquia_border_types() {
    return array(
        'no' => t('<none>'),
        'top' => t('Top Border'),
        'left' => t('Left Border'),
        'right' => t('Right Border'),
        'bottom' => t('Bottom Border'),
        'vertical' => t('Vertical Borders'),
        'horizontal' => t('Horizontal Borders'),
        'all' => t('All Borders'),
    );
}

/**
 * tooltip Types
 */
function acquia_tooltip_info() {
    return array(
        'tooltip' => t('Tooltip'),
        'popover' => t('Popover'),
    );
}

/**
 * tooltip Types
 */
function acquia_tooltip_info_triggers() {
    return array(
        'hover' => t('hover'),
        'click' => t('click'),
        'focus' => t('focus'),
    );
}

/**
 * acquia_directions
 */
function acquia_directions() {
    return array(
        'top' => t('top'),
        'right' => t('right'),
        'bottom' => t('bottom'),
        'left' => t('left'),
    );
}

/**
 * acquia_visibility_list
 */
function acquia_visibility_list() {
    return array(
        'hidden-phone' => t('Hidden on Phone'),
        'hidden-tablet' => t('Hidden on Tablet'),
        'hidden-tablet-down' => t('Hidden on Tablet and Smaller Screens'),
        'hidden-desktop' => t('Hidden on Desktop'),
        'hidden-desktop-up' => t('Hidden on Desktop and Bigger Screens'),
        'visible-phone' => t('Visible on Phone'),
        'visible-tablet' => t('Visible on Tablet'),
        'visible-desktop' => t('Visible on Desktop'),
    );
}

/**
 * acquia_callout_border_types
 */
function acquia_callout_border_types() {
    return array(
        'square' => t('Square'),
        'rounded' => t('Rounded'),
        'square-dashed' => t('Square Dashed'),
        'rounded-dashed' => t('Rounded Dashed'),
    );
}

/**
 * acquia_callout_btn_align_list
 */
function acquia_callout_btn_align_list() {
    return array(
        'corner' => t('Corner of box'),
        'after' => t('Center Right After Text'),
    );
}

/**
 * acquia_pricing_table_types
 */
function acquia_pricing_table_types() {
    return array(
        'standard' => t('Standard'),
        'bordered' => t('Bordered'),
        'bordered_alt' => t('Bordered alt'),
        'labeled' => t('Labled'),
    );
}

/**
 * acquia_list_styles
 */
function acquia_list_styles() {
    return array(
        'un' => t('Unordered'),
        'or' => t('Ordered (numbers)'),
        'no' => t('No bullets'),
        'icon' => t('Icon List'),
    );
}

/**
 * acquia_accordion_styles
 */
function acquia_accordion_styles() {
    return array(
        'minimal' => t('Minimal'),
        'simple' => t('Simple'),
        'simple-circled' => t('Simple Circled'),
        'fancy' => t('Fancy'),
        'fancy hard' => t('Fancy style 2'),
    );
}

/**
 * acquia_accordion_styles
 */
function acquia_tab_styles() {
    return array(
        'simple no-sep' => t('Simple'),
        'simple centered no-sep' => t('Simple - Centered tabs'),
        'simple sep' => t('Simple - Seperated tabs'),
        'fancy no-sep' => t('Fancy - News style'),
        'fancy sep' => t('Facny - News Style - Seperated tabs'),
    );
}

/**
 * acquia_social_icons
 */
function acquia_social_icons() {
    return array(
        'facebook' => t('facebook'),
        'twitter' => t('twitter'),
        'gplus' => t('Google Plus'),
        'pinterest' => t('pinterest'),
        'email' => t('Email'),
    );
}

/**
 * acquia_breadcrumb_styles
 */
function acquia_breadcrumb_styles() {
    return array(
        'simple' => t('Simple'),
        'simple boxed' => t('Simple Boxed'),
        'fancy'=> t('Fancy'),
    );
}

/**
 * acquia_contact_info
 */
function acquia_contact_info() {
    return array(
        'person' => t('person'),
        'company' => t('company'),
        'address'=> t('address'),
        'phone' => t('phone number'),
        'fax' => t('fax'),
        'email' => t('e-mail'),
        'website' => t('website'),
        'skype' => t('skype'),
        'working_hours' => t('Working hours'),
    );
}

/**
 * acquia_easing_types
 */
function acquia_easing_types() {
    $_easing = &drupal_static(__FUNCTION__, NULL);

    if (!isset($_easing)) {
        $_easing = array();
        $easing = array(
            'linear',
            'swing',
            'easeInQuad',
            'easeOutQuad',
            'easeInOutQuad',
            'easeInCubic',
            'easeOutCubic',
            'easeInOutCubic',
            'easeInQuart',
            'easeOutQuart',
            'easeInOutQuart',
            'easeInQuint',
            'easeOutQuint',
            'easeInOutQuint',
            'easeInSine',
            'easeOutSine',
            'easeInOutSine',
            'easeInExpo',
            'easeOutExpo',
            'easeInOutExpo',
            'easeInCirc',
            'easeOutCirc',
            'easeInOutCirc',
            'easeInElastic',
            'easeOutElastic',
            'easeInOutElastic',
            'easeInBack',
            'easeOutBack',
            'easeInOutBack',
            'easeInBounce',
            'easeOutBounce',
            'easeInOutBounce'
        );

        foreach($easing as $val) {
            $_easing[$val] = t($val);
        }
    }
    return $_easing;
}

/**
 * DiamondLayers Ubercart tags view
 */
function acquia_tags_view(){
    return array(
        'tagclouds' => t('Tagclouds'),
        'list' => t('List view'),
        'tag' => t('Tags view'),
    );
}

