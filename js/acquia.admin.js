/**
 * @file admin behaviors
 *	Use only this file for modification or attaching behaviors
 */
(function( $ ) {

Drupal.behaviors.acquiaMisc = {
	attach: function(t, n) {
	
		/* Tipsy On Form Description */
		$('.use-tooltip .form-item .description', t).each(function(){
			if ($(this).text().length > 0) {
				$(this).hide();
				$('input, select, textarea', $(this).parent()).attr('data-help', $(this).html()).addClass('tooltip');
				$(this).remove();
			}
		});

		// state enabled form elements 
		for (key in n.states){
			if ($(key).is('fieldset')) {
				$(key).addClass('dependent-field');
			}else {
				$(key).closest('.form-item').addClass('dependent-field');
			}
		}
	}
}

/**
 *
 *
 */
Drupal.behaviors.attachPlugins = {
	attach: function(t, n) {

		$('.ac-admin:not(.raw-attach) :checkbox').once('ac-fancyCheckbox', function () {
			$(this).acquiaCheckbox();
		});	

		$('.ac-admin:not(.raw-attach) select').once('ac-fancySelect', function () {
			if (!$(this).is('.no-fancy-select')){ 
				$(this).acquiaFancySelect();
			}
		});
		
		$('input.field-colorpicker', t).once('ac-colorPicker', function () {
			$(this).acquiaColorPicker();
		});
		
		$('.nice-scroll, .ac-attachment-select-icons', t).once('ac-niceScroll', function () {
			$(this).acquiaNiceScroll();
		});

		$('.nice-scroll > *', t).on('resize', function () {
			$(this).parent('.nice-scroll:first').acquiaNiceScroll({}, 'update');
		});
		
		$('.tooltip').acquiaTooltip();
		
		$('.ac-admin:not(.raw-attach) .form-file', t).once('ac-nicefileinput', function () {
			$(this).nicefileinput();
		});
	}
}

/**
 * Toggle vertical Tabs
 */
	Drupal.behaviors.acquiaToggleVtabs = {
		attach: function (context) {
			$('.vertical-tabs-pane > legend').addClass('vtab-pane-legend');

			$('.toggle-tabs', context)
			.data('orig-title', $('.toggle-tabs').attr('title'))
			.click(function(e) {
				e.preventDefault();
				var target = $(this).closest('form');
				$(target).toggleClass('toggle-view');
				if ($(target).is('.toggle-view')){
					$(this).attr('title', Drupal.t('Show only current tab'));
				}else{
					$(this).attr('title', $(this).data('orig-title'));
				}
				$vTabs = $(target).find('.vertical-tabs');
				//Drupal.verticalTab.toggleTabs();
			}); 
		}
	};

	if (typeof Drupal.verticalTab != "undefined") {
			/**
			 * Hide Tabs and dispaly whole fieldsets
			 */
			Drupal.verticalTab.prototype.toggleTabs = function () {
				var window = $(window);
				return this;
			};
		
			
		/**
		 * Overriding Theme function for a vertical tab.
		 */
		Drupal.theme.prototype.verticalTab = function (settings) {
			var tab = {};
			tab.item = $('<li class="vertical-tab-button" tabindex="-1"></li>')
				.append(tab.link = $('<a href="#"></a>')
				.append(tab.icon = $('<span></span>', {'class': 'tab-icon'}))
					.append(tab.title = $('<strong></strong>').text(settings.title))
					.append(tab.summary = $('<span class="summary"></span>')
				)
			);
		
			return tab;
		};
	}


})(jQuery);

/**
* Provide the HTML to create the font icon.
*/
Drupal.theme.prototype.font_icon = function (icon) {
	var _class = 'font-icon';
	if (icon != 'undefined' || icon != '') {
		_class += ' '+ icon;
	}
  return '<span class="'+_class+'"></span>';
}




