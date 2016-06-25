//global newline helper
function acquia_nl2br (str, is_xhtml)
{
	var breakTag = (is_xhtml || typeof is_xhtml === 'undefined') ? '<br ' + '/>' : '<br>';
	return (str + '').replace(/([^>\r\n]?)(\r\n|\n\r|\r|\n)/g, '$1' + breakTag + '$2');
}

(function($) {



})(jQuery);


(function ($) {


})(jQuery);
