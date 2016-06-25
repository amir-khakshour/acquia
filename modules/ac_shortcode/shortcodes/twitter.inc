<?php
/**
 * @file shortcode defenition of twitter shortcode
 */

/**
 * Implements ac_shortcode_SHORTCODE_shortcode()
 * @return an array of shortcodes defenition
 *
 * 	Shortcode settings array consists of below values:
 * 	 %tag : Shortcode tag
 * 	 %title: Shortcode title
 * 	 %description: Shortcode description
 * 	 %category: An array of categories that this shortcode belongs to
 * 	 %class: A class name that contains methods to process the tag
 * 	 %file: Shortcode class file name
 * 	 %path: Relative path to shortcode class file
 * 	 %nested shortcodes: Array of shortcode tags that can be nested
 *    	in this shortcode and processed as a value of current shortcode
 * 	 %hidden: A Boolean value indicating whether this shortcode must
 *    	be hidden in the shortcodes list or not. it works in conjunction
 *    	with %enabled key.
 * 	 %enabled: Array of shortcode tags and a Boolean value that represents
 *    	the circumstances that the shortcode can be enabled based on the
 *    	status of other shortcodes.
 */

function ac_shortcode_twitter_shortcode() {
	return array(
		'ac_twitter' => array(
			'title' => t('Recent Tweets'),
			'description' => t('Displaying recent tweets in different formats.'),
			'form callback' => 'ac_shortcode_ac_twitter_form',
			'values process callback' => 'ac_shortcode_ac_twitter_preprocess',
			'process callback' => 'ac_shortcode_ac_twitter_process',
		),
	);
}

/**
 * Implements edit form of {{ac_twitter}} shortcode
 */
function ac_shortcode_ac_twitter_form($form, &$form_state) {
	acquia_include('options');
	$values = isset($form_state['values']) ? $form_state['values'] : array();
	$form['key'] = array(
		'#type' => 'textfield',
		'#title' => t('Twitter key'),
		'#description' => t('Twitter key, which can be a username (prepended with @) a hashtag (prepended with #) or a search keyword (no prefix).'),
		'#default_value' => isset($values['key']) ? $values['key'] : '@envato',
	);

	$form['items'] = array (
		'#type' => 'select',
		'#title' => t('Items'),
		'#description' => t ( 'Number of tweets to extract; e.g., 4' ),
		'#default_value' => isset($values['items']) ? $values['items'] : 4,
		'#options' => drupal_map_assoc ( range (1, 20) ),
	);

	$form['style'] = array (
		'#type' => 'select',
		'#title' => t('Style'),
		'#description' => '',
		'#default_value' => isset($values['style']) ? $values['style'] : 's',
		'#options' => array('compact'=> t('Compact'), 'full' => t('Full')),
	);

	/** Global shortcode elements **/
	$form['class'] = array(
		'#type' => 'textfield',
		'#title' => t('Extra class name'),
		'#description' => t('If you wish to style particular content element differently, then use this field to add a class name and then refer to it in your css file.'),
		'#default_value' => isset($values['class']) ? $values['class'] : '',
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('submit'),
	);

	return $form;
}

/**
 * Process {{ac_twitter}} shortcode values before making shortcode string
 */
function ac_shortcode_ac_twitter_preprocess(&$values) {

}

/**
 * process {{ac_twitter}} Shortcode
 * 	building the HTML output of shortcode
 */
function ac_shortcode_ac_twitter_process($attrs, $text = null, $shortcode = '') {
	return;
	acquia_include('content');
	$_attrs = ac_shortcode_attrs(array(
		'key' => '@envato',
		'items' => '4',
		'style' => 'compact',
	), $attrs);

// twitter_pull is required
	if (!module_exists('twitter_pull')) {
		return;
	}

	extract($_attrs);
	$sc_name = str_replace('_', '-', $shortcode);

	$classes = array();
	$classes[] = $sc_name;
	$classes[] = 'clearfix';
	$classes[]= acquia_get_class_by_args(array('style'), $_attrs);

	//---------------------------------------
	if (isset($attrs['class']) && !empty($attrs['class'])) {
		foreach (explode(' ', $attrs['class']) as $class) {
			$classes[] = $class;
		}
	}
	$classes = array_filter($classes, 'strlen');
	$classes = implode(' ', $classes);
	//---------------------------------------

	$attributes = array();
	$attributes['class'] = $classes;

	if ($style == 'compact') {
		$tweets = twitter_pull_retrieve($key, (int)$items +1, FALSE, NULL);
		if (!is_array($tweets) || empty($tweets)) {
			return;
		}

		$items =array();
		$i =0;
		foreach ($tweets as $tweet) {
			$tweet->time_ago = t('!time ago.', array('!time' => format_interval(time() - $tweet->timestamp)));
			$item = '    <span class="tweet-text clearfix">';
			$item .= '    			 ' .twitter_pull_add_links($tweet->text);
			$item .= '    </span>';
			$item .= '    <span class="tweet-time">' .l($tweet->time_ago, 'http://twitter.com/' . $tweet->screenname . '/status/' . $tweet->id) . '</span>';
			$items[] = $item;
		}
		$items = theme_item_list(array('items' => $items, 'type' => 'ul', 'title' => '', 'attributes' => array('class' => array('ac-s-li', 'ac-li-bordered'))));
	}else{
		$items = twitter_pull_render($key, NULL, $items);
	}

	$out  = '<div'.drupal_attributes($attributes).'>';
	$out .= $items;
	$out .= '</div>';

	return $out;
}
