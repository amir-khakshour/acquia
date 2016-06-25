/**
 * @file main Ctools file for acquia commands
 *
 */

(function ($) {
	// Make sure our objects are defined.
	var Diamond = Diamond || {};
	Diamond.utils = Diamond.utils || {};
	Diamond.Modal = Diamond.Modal || {};

	Diamond.utils.acquiaInsertShortcode = function(ajax, response, status){
		var editor = Diamond.Modal.currentSettings.editor ?
			Diamond.Modal.currentSettings.editor : tinymce.activeEditor;
		if (response.output != undefined && response.output != '') {
			var sc = response.output;
			var selContent = editor.selection.getContent({format : 'text'});
			sc = sc.replace("\{\{CONTENTHERE\}\}", selContent);
			editor.execCommand("mceInsertContent", false, sc)
		}
	}


	$(function() {
		Drupal.ajax.prototype.commands.acquiaInsertShortcode = Diamond.utils.acquiaInsertShortcode;
	});

})(jQuery);
