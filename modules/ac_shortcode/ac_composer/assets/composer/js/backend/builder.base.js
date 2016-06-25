/*
 * DiamondBuilder > Base
 *
 * @author Amir Khakshour
 * @copyright 2015 DiamondLayers
 */
Diamond.Builder = {
    filters:{
        templates:[]
    }, addTemplateFilter: function (callback) {
        if (_.isFunction(callback)) this.filters.templates.push(callback);
    }
};
Diamond.Builder.Views = Diamond.Builder.Views || {};
Diamond.Builder.Models = Diamond.Builder.Models || {};
Diamond.Builder.Collections = Diamond.Builder.Collections || {};
Diamond.Builder.Utils = Diamond.Builder.Utils || {};
Diamond.Builder.clone_index = 1;
Diamond.Builder.element_start_index = 0;
Diamond.Builder.modal = null;

Diamond.Builder.templateOptions = {
    default: {
        evaluate: /<%([\s\S]+?)%>/g,
        interpolate: /<%=([\s\S]+?)%>/g,
        escape: /<%-([\s\S]+?)%>/g
    },
    custom: {
        evaluate: /<#([\s\S]+?)#>/g,
        interpolate: /\{\{\{([\s\S]+?)\}\}\}/g,
        escape: /\{\{([^\}]+?)\}\}(?!\})/g
    }
};

(function ($) {
    tinymce = typeof tinymce != 'undefined' ? tinymce : {};
    tinymce.settings = typeof tinymce.settings != 'undefined' ? tinymce.settings : {};
    tinymce.settings.forced_root_block = '';

    Drupal.behaviors.DiamondBuilder = {
        attach: function(t, n) {
            var settings = Drupal.settings.DiamondBuilder;
            window.ajaxurl = settings.ajaxurl;
            window.i18nLocale = settings.i18n || {};
            Diamond.Builder.map = jQuery.parseJSON(settings.shortcodes);
            $('.col-toggle').click(function(){
                $(this).parent('h4').siblings('.db-visual-sc').toggle();
            });

        }
    };

    /**
     *  Implementation of Drupal Command Callback
     * @param ajax
     * @param response
     * @param status
     */
	Diamond.Builder.Utils.acquiaUpdateComposer = function(ajax, response, status){
		if (!_.isObject(Diamond.Builder.currentModelView)) {
			return;
		}
		if (typeof response.output != "undefined") {
			var params = response.output,
				modelView = Diamond.Builder.currentModelView;
			modelView.model.save({params:params});
			modelView.data_saved = true;
			modelView.close();
		}
	}

	$(function() {
		Drupal.ajax.prototype.commands.acquiaUpdateComposer = Diamond.Builder.Utils.acquiaUpdateComposer;
	});

})(jQuery);

