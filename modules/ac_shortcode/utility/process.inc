<?php

/**
 * Process Shortcode attributes array
 */
function ac_shortcode_process_shortcode_attrs($tag, $values) {
	// find text_format id from text_format_cid field
	if (isset($values['text_format_cid'])) {
		foreach($values['text_format_cid'] as $cid => $key){
			$values[$key] = isset($values[$cid]) ? $values[$cid] : '';
			unset($values[$cid]);
		}
		unset($values['text_format_cid']);
	}
	
	if (isset($values['content'])) {
		$content = $values['content'];
		// markup text_format fields
		if (is_array($content) && isset($content['format']) && isset($content['value'])) {
			$values['content'] = $content['value'];
		}
	}
  
	// process animate fields
	if (isset($values['cssanimate']['enabled']) && $values['cssanimate']['enabled'] == 1) {
		unset($values['cssanimate']['enabled']);
		$values = array_merge($values, $values['cssanimate']);
	}
	unset($values['cssanimate']);
	
	// process animate fields
	if (isset($values['fonticon']['enabled']) && $values['fonticon']['enabled'] == 1) {
		unset($values['fonticon']['enabled']);
		unset($values['fonticon']['icon-filter']);
		$values = array_merge($values, $values['fonticon']);
	}
	unset($values['fonticon']);
	
	// process animate fields
	if (isset($values['tooltip']['enabled']) && $values['tooltip']['enabled'] == 1) {
		unset($values['tooltip']['enabled']);
		$values = array_merge($values, $values['tooltip']);
		if ($info == 'tooltip') {
			unset($values['info_content']);
		}
	}
	unset($values['tooltip']);
  
  return $values;
}

/**
 * Create shortcode string
 *  create shortcode for given tag and values
 *
 * @param {string} $tag
 *  shortcode tag
 * @param {array} $attrs
 *  shortcode attributes array
 */
function ac_shortcode_create_shortcode($tag, &$values) {
	acquia_include('utility');
	acquia_include('utility', 'ac_shortcode');
	
	$formats = user_enabled_filter_formats();
  $tag_info = ac_shortcode_get_sc_info($tag);
	
	$out = '';
	$content = '';
	$attrs = array();

  
  $values = ac_shortcode_process_shortcode_attrs($tag, $values);
	// @TODO move to ac_shortcode_process_shortcode_attrs
	$values['content'] = isset($values['content']) ? $values['content'] : '{{CONTENTHERE}}';
	
	// nested shortcodes
	$nested_shortcodes = array();
	if (!empty($tag_info) && isset($tag_info['nested shortcodes'])) {
		$nested_shortcodes = $tag_info['nested shortcodes'];
	}
	
  // findout markup enabled attributes
	foreach($values as $attr => &$value) {
   
		if (is_array($value)){
			if (isset($value['format']) && in_array($value['format'], array_keys($formats)) && isset($value['value'])) {
				$attrs[$attr] = $val['value'];
			}
			foreach($value as &$n_val) {
				if (in_array($attr, array_keys($nested_shortcodes))) {
					$content .= ac_shortcode_create_shortcode($nested_shortcodes[$attr], $n_val);
				}
			
			}
			continue;
		}
		
    $value = is_array($value) ? implode(',', $value) : $value;
    $attrs[] = $attr .'="'. $value .'"';
	}

	$attrs = implode(' ', $attrs);
	$out .= '[' .$tag. ' '. trim($attrs) .']';
	$out .= $content;
	$out .= '[/' .$tag. ']';
	return $out;
}

/**
 * Removes editor autop and invalid nesting of p tags, as well as br tags
 *
 * @param string $content html content by the editor
 * @return string $content
 */
function ac_shortcode_remove_autop($content) {
	acquia_include('utility', 'ac_shortcode');
	acquia_include('process', 'ac_shortcode');
	
	$shortcode_tags = ac_shortcode_list_tags();
	$tagregexp = join( '|', array_map('preg_quote', $shortcode_tags) );
	
	// opening tag
	$content = preg_replace("/(<p>)?\[($tagregexp)(\s[^\]]+)?\](<\/p>|<br \/>)?/","[$2$3]",$content);
	 
	// closing tag
	$content = preg_replace("/(<p>)?\[\/($tagregexp)](<\/p>|<br \/>)?/","[/$2]",$content);
	
	$content = shortcode_unautop( $content ); 
	$content = preg_replace('#^<\/p>|^<br\s?\/?>|<p>$|<p>\s*(&nbsp;)?\s*<\/p>#', '', $content);
	
	return $content;
}

/**
 * Escape Shortcode tags for code display purposes
 *
 * @param string $content html content by the editor
 * @return string $content
 */
function ac_shortcode_escape_tags($content) {
	acquia_include('utility', 'ac_shortcode');
	
	$shortcode_tags = ac_shortcode_list_tags();
	$tagregexp = join( '|', array_map('preg_quote', $shortcode_tags) );
	
	// opening tag
	$content = preg_replace("/\[($tagregexp)(\s[^\]]+)?\]/","[[$1$2]]",$content);
	 
	// closing tag
	$content = preg_replace("/\[\/($tagregexp)]/","[[/$1]]",$content);

	return $content;
}

/**
 * Don't auto-p wrap shortcodes that stand alone
 *
 * Ensures that shortcodes are not wrapped in <<p>>...<</p>>.
 *
 * @since 2.9.0
 *
 * @param string $pee The content.
 * @return string The filtered content.
 */
function shortcode_unautop( $pee ) {
	acquia_include('utility', 'ac_shortcode');
	
	$shortcode_tags = ac_shortcode_list_tags();
	
	if ( empty( $shortcode_tags ) || !is_array( $shortcode_tags ) ) {
		return $pee;
	}

	$tagregexp = join( '|', array_map( 'preg_quote', array_keys( $shortcode_tags ) ) );

	$pattern =
		  '/'
		. '<p>'                              // Opening paragraph
		. '\\s*+'                            // Optional leading whitespace
		. '('                                // 1: The shortcode
		.     '\\['                          // Opening bracket
		.     "($tagregexp)"                 // 2: Shortcode name
		.     '(?![\\w-])'                   // Not followed by word character or hyphen
		                                     // Unroll the loop: Inside the opening shortcode tag
		.     '[^\\]\\/]*'                   // Not a closing bracket or forward slash
		.     '(?:'
		.         '\\/(?!\\])'               // A forward slash not followed by a closing bracket
		.         '[^\\]\\/]*'               // Not a closing bracket or forward slash
		.     ')*?'
		.     '(?:'
		.         '\\/\\]'                   // Self closing tag and closing bracket
		.     '|'
		.         '\\]'                      // Closing bracket
		.         '(?:'                      // Unroll the loop: Optionally, anything between the opening and closing shortcode tags
		.             '[^\\[]*+'             // Not an opening bracket
		.             '(?:'
		.                 '\\[(?!\\/\\2\\])' // An opening bracket not followed by the closing shortcode tag
		.                 '[^\\[]*+'         // Not an opening bracket
		.             ')*+'
		.             '\\[\\/\\2\\]'         // Closing shortcode tag
		.         ')?'
		.     ')'
		. ')'
		. '\\s*+'                            // optional trailing whitespace
		. '<\\/p>'                           // closing paragraph
		. '/s';

	return preg_replace( $pattern, '$1', $pee );
}