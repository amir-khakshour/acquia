(function ($) {
// Make sure our objects are defined.
var Diamond = Diamond || {};
Diamond.Modal = Diamond.Modal || {};
Diamond.Modal.openInstance = [];

  
var selFilter = '';
var mceScBtn = Drupal.settings.shortcodes ? Drupal.settings.shortcodes.mce_btn : null;
var ajaxURL = Drupal.settings.shortcodes ? Drupal.settings.shortcodes.ajaxURL : null;

if (mceScBtn != null) {
	tinymce.create('tinymce.plugins.shortcodes', {
	
		init : function(editor, url) {
			// get selected format
			if ($('#' + editor.id).attr('name')) {
				selFilter = $('#' + editor.id).attr('name').replace(/\[value\]$/g, '[format]');
				selFilter = $('select[name="'+selFilter+'"]').val() ? $('select[name="'+selFilter+'"]').val() : null;
			}
			
			editor.addCommand("openModal", function (ui, params) {
				var settings = Drupal.settings.acquiaModalStyle;
				if (params.modal_size != '' && params.modal_size != undefined) {
					var fact = acquia_get_modal_size_factor(params.modal_size);
					settings.modalSize.width = fact.width;
					settings.modalSize.height = fact.height;
				}
				
				if (params.modalSaveBtn != '' && params.modalSaveBtn != undefined && params.modalSaveBtn == true) {
					settings.modalSaveBtn = true;
				}
				
				settings.editor = editor;
	
				var modal = Diamond.Modal.show(settings);
				
				// Create a drupal ajax object
				var element_settings = {};
				if (params.modal_ajax_url) {
					element_settings.url = params.modal_ajax_url;
					element_settings.progress = { type: 'throbber' };
				}
				var base = params.modal_ajax_url,
				ajax = new Drupal.ajax(base, this, element_settings);
	
				$.ajax(ajax.options);
		
				return false;
			});
			
		}, 
	
		createControl: function(n, cm) {
			switch (n) {
				case 'shortcodes':
							//create the button
	
					var cur_plugin 	= this,
							open_modal = Diamond.Modal.openInstance || [],
							c = cm.createMenuButton('shortcodes', {
								title : mceScBtn.title,
								image : mceScBtn.image,
								icons : false
							});
					c.onRenderMenu.add(function(c, m) {
						var shortcode_array = mceScBtn.options[selFilter],
						tmp = [],
						submenu = [];
						
						// get all groups
						for(var i in shortcode_array) {
							if(open_modal.length != 0 &&
							   shortcode_array[i].modal &&
							   shortcode_array[i].modal.hide_on_modal!= undefined &&
							   shortcode_array[i].modal.hide_on_modal == true
							   ) {
								continue;
							}
							if (shortcode_array[i].group_mn != undefined &&shortcode_array[i].group != undefined) {
								tmp[shortcode_array[i].group_mn] = shortcode_array[i].group;
							}
						}
						
						
						// create sub menus
						// dont create tab submenus if modal window is open
						for(var mn in tmp) {
							if( tmp[mn] != 'undefined') {
								submenu[mn] = m.addMenu({title: tmp[mn]});
							}
						}
						
						m.addSeparator();
						
						for(var z in shortcode_array) {
							
							if(open_modal.length != 0 &&
							   shortcode_array[z].modal &&
							   shortcode_array[z].modal.hide_on_modal!= undefined &&
							   shortcode_array[z].modal.hide_on_modal == true
							   ) {
								continue;
							}
							
							shortcode_array[z].tinymce = shortcode_array[z].tinymce || {};
	
							var current_menu = shortcode_array[z].group_mn ? submenu[shortcode_array[z].group_mn] : m;
						
							if(typeof shortcode_array[z].tinymce.instantInsert != 'undefined') {
								cur_plugin.instantInsert(current_menu, shortcode_array[z]);
							} else {
								cur_plugin.modalInsert(current_menu, shortcode_array[z]);
							}
						}
	
					});
					
					return c;
			}
			
			return null;
		},
		
		instantInsert: function (menu, shortcode) {
			menu.add({
				title: shortcode.tinymce.title || shortcode.title,
				onclick: function () {
					var selContent = tinymce.activeEditor.selection.getContent({format : 'text'});
					sc = shortcode.tinymce.instantInsert;
					sc = sc.replace(new RegExp("(\\{\\{CONTENTHERE\\}\\})", "g"), selContent);
					tinymce.activeEditor.execCommand("mceInsertContent", false, sc);
				}
			})
		},
		
		modalInsert: function (menu, shortcode) {
			menu.add({ 
				title: shortcode.tinymce.title || shortcode.title,
				onclick: function () {
					var modalData = $.extend({}, {modal_size:'', before_save:'' }, shortcode['modal']);
					
					tinymce.activeEditor.execCommand("openModal", false, {
						modal_size:       modalData.modal_size,
						shortcodehandler:  shortcode.shortcode, 
						modal_title: 		   shortcode.title, 
						modal_ajax_url: 	 ajaxURL + '/' + shortcode.shortcode,
						modalSaveBtn:      true,
					})
				}
			})
		}
		
		
	});
		
	// Register plugin with a short title
	tinymce.PluginManager.add('shortcodes', tinymce.plugins.shortcodes);

}

})(jQuery);


		
