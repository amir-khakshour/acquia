(function($) {
	$(document).ready(function(){

		// Preview
		if ( $( ".ac-g-fonts" ).length > 0 ) {

			$( ".ac-g-fonts" ).on( "change", function() {
				var _this = $( this ),
					id = _this.attr( "id" ),
					value = _this.val(),
					$_option = _this.find('option[value="'+value+'"]'),
					font_header = value.replace( / /g, "+" ),
					font_style = value.split( "&" )[0],
					target = $('.ac-target-' + _this.attr('data-target')),
					fontStyle = fontW = '';
					font_style = font_style.split( ":" );
					

					var protocol = 'http:';
					if ( typeof document.location.protocol != 'undefined' ) {
						protocol = document.location.protocol;
					}
					
				target.hide();
				
				if ($_option.closest('optgroup').attr('label') == Drupal.t('theme fonts')) {
					var ajax_settings = {};
					ajax_settings.url = Drupal.settings.basePath + Drupal.AC_SKIN.ajax_URL;
					ajax_settings.progress = { type: 'throbber' },
					
					ajax = new Drupal.ajax(window.ajaxurl, _this, ajax_settings);

					ajax.submit.action = 'load_theme_font';
					ajax.submit.font = value;
					$.ajax(ajax.options);
					
					target.css('font-weight', 'normal');
					target.css('font-family', value);
				}else {
					if ( font_style[1] ) {

						var vars = font_style[1].split( 'italic' );
						if ( 2 == vars.length ) { fontStyle = "italic"; }

						if ( '700' == vars[0] || 'fontW' == vars[0] ) {

							fontW = "bold";
						} else if ( '400' == vars[0] || 'normal' == vars[0] ) {

							fontW = "normal";
						} else if ( vars[0] ) {

							fontW = parseInt( vars[0] );
						} else {

							fontW = "normal";
						}

					}else {
						fontW = "normal;";
					}

					var linkHref = protocol + '//fonts.googleapis.com/css?family=' + font_header;
					var style = '<link id="' + id + '-font-preview" href="' + linkHref + '" rel="stylesheet" type="text/css">';

					$('#' + id + '-font-preview').remove();

					if ($_option.closest('optgroup').attr('label') == Drupal.t('Google Fonts')){
						$('head').append( style );
					}
					target.css('font-family', font_style[0]);
					if (!fontStyle.length > 0) {
						target.css('font-style', fontStyle);
					}
					
					if (!fontW.length > 0) {
						target.css('font-weight', fontW);
					}
				
				}
				target.show();
			});
			
			$( ".ac-g-fonts" ).trigger( 'change' );
		}
		
		// Color Picker
		$( ".ac-skin-color" ).each(function(){
			$(this).on('colorChanged', function(){
				var attr = $(this).attr('data-css-attr');
				$('.ac-target-' + $(this).attr('data-target')).css(attr, $(this).val());
				var ieColor = $(this).closest('.form-wrapper').find('.ac-ie-color');
				
				if (ieColor.length > 0){
					ieColor.val($(this).val());
					ieColor.siblings('.selectpicker').find('div').css(attr, $(this).val());
				}
			});
			
			$(this).trigger('colorChanged');
		});
		
    /** 
	   * Slider
	   */
			$( ".ac-slider" ).each(function() {
				var $input = $(this),
					$slider = $('<div class="ac-slider-ui"></div>').insertBefore($input),
					value = $input.val(),
					min = $input.attr('data-min'),
					max = $input.attr('data-max'),
					step = $input.attr('data-step'),
					attr = $input.attr('data-css-attr'),
					suffix = $input.attr('data-val-suffix');

					jQuery($slider).slider({
						value: parseInt(value),
						min: parseInt(min),
						max: parseInt(max),
						step: parseInt(step),
						range: 'min',
						slide: function( event, ui ) {
							attr = $input.attr('data-css-attr');
							suffix = $input.attr('data-val-suffix');
							$input.val( ui.value ).trigger('keyup');
							value = ui.value;
							if (typeof suffix != 'undefined') {
								value += suffix;
							}	

							if (attr == 'opacity') {
								color = $input.closest('.form-wrapper').find('.field-colorpicker').first().val();
								value = hexToRgba(color, value);
								attr = 'background-color';
							}
							if (typeof $input.attr('data-target') != "undefined") {
								$('.ac-target-' + $input.attr('data-target')).css(attr, value);
							}
						}
					});
					if (typeof suffix != 'undefined') {
						value += suffix;
					}
					if (attr == 'opacity') {
						color = $input.closest('.form-wrapper').find('.field-colorpicker').first().val();
						value = hexToRgba(color, value);
						attr = 'background-color';
					}
					if (typeof $input.attr('data-target') != "undefined") {
						$('.ac-target-' + $input.attr('data-target')).css(attr, value);
					}
					
			});
			
			var changeCase = function(el, _case){
				var target = el.attr('data-target');
				container = $('.ac-target-' + target);
				switch(_case) {
					case 'cap':
						container.css({'text-transform':'capitalize', 'font-style': 'normal'});
						break;

					case 'up':
						container.css({'text-transform':'uppercase', 'font-style': 'normal'});
						break;
						
					case 'it':
						container.css({'text-transform':'normal', 'font-style': 'italic'});
						break;
						
					case 'lo':
					default:
						container.css({'text-transform':'lowercase', 'font-style': 'normal'});
						break;
				}
			};
			
			$( ".ac-transform" ).each(function(){
				$(this).on('change', function(){
					changeCase($(this), $(this).val());
				});
				changeCase($(this), $(this).val());
			});	
			
			$(".ac-bg-sel .ac-sel").on('click', function(){
				$(this).closest('.ac-bg-sel').find('.ac-sel').removeClass('active');
				$(this).addClass('active');
				var $target = $(this).closest('.ac-bg-sel').attr('data-target');
				if (typeof $target !="undefined" && $target !='') {
					$target = $('input[name="'+$target+'"], select[name="'+$target+'"]');
				}else{
					$target = $(this).closest('.form-wrapper').find('.ac-img-sel-target');
				}

				if ($target.is('select')) {
					$target
						.val($(this).attr('data-uri'))
						.attr('data-src', $(this).attr('data-src')).trigger('change');
				}else{
					$target
						.val($(this).attr('data-uri'))
						.attr('data-src', $(this).attr('data-src')).trigger('inputChange');
				}
				
			});
			
			// Upload
			$(".upload-btn").live('click', function(e) {
				e.preventDefault();
				uploadInput = $(this).closest('.form-item').find('input');

				Drupal.media.popups.mediaBrowser(function(t) {
					var mediaFile = t[0];
					$(uploadInput).val(mediaFile.url);
					$(uploadInput).attr('data-src', mediaFile.url);
					$(uploadInput).trigger('inputChange');
				});
					return false;
			});
			
			// background image
			$(".ac-img-sel-target").on('inputChange', function(){
				var target = $(this).attr('data-target');
				$('.ac-target-' + target).css('backgroundImage', 'url(' +$(this).attr('data-src') + ')');
			});
			
			// set active from bg input
			$(".ac-img-sel-target").each(function(){
				$input = $(this),
				$val = $input.val();
				$input.trigger("inputChange");
				if ($input.is('.ac-hidden')) {
					$input.closest('.el').hide();
				}
				if ($val !='') {
					$input.closest('.form-item').find('.ac-sel').each(function(){
						if ($(this).attr('data-uri') == $val) {
							$(this).addClass('active');
						}
					});
				}
			});
			
			
			// background image
			$(".field-suffix .ac-reset").on('click', function(){
				var $input = $(this).closest('.form-item').find('.form-text');
				$input
					.val('')
					.attr('data-src', '').trigger('inputChange');
				if ($input.is('.ac-img-sel-target')) {
					$input.closest('.form-item').find('.ac-sel').removeClass('active');
				}
			});
			
	});
}(jQuery));

(function($) {
$(document).ready(function(){

	$('body').addClass('has-js');
	
	/** THEME ADMIN PAGE **/
	// Set Equal height for vertical tab columns
	//setEqualHeightVtabs();
	setVtabsListClass();
	fakeSubmitBTN();
	layoutSelector();

	/**
	 * equal height for vertical tab lists and panes
	 */
	function setEqualHeightVtabs(){		
		var container = $('.vertical-tabs'),
		col1 = container.find('.vertical-tabs-list:first'),
		col2 = container.find('.vertical-tabs-panes:first'),
		col1MaxH = col1.height(),
		setHeight = function(el){
			var col2H = col2.height();
			if (typeof el == 'object') {
				var index = jQuery(el).parent('li:first').index();
				col2H = col2.find('> .vertical-tabs-pane').eq(index).height();
			}
			var col1H  = col1.height();
			if (col1MaxH > col2H) {
				col1.css({'height': col1MaxH});
				col2.css({'min-height': col1MaxH});
			}else{
				col1.css({'height': col2H});
				col2.css({'min-height': col2H});
			}
		};
		
		setHeight();
		col1.find('a').click(function(){
			setHeight(this);
		});
	}

	/**
	 * Add fieldset class of theme settings form to vertical panel list items
	 */
	function setVtabsListClass(){		
		var container = $('.vertical-tabs'),
		list = container.find('.vertical-tabs-list:first .vertical-tab-button'),
		panes = container.find('.vertical-tabs-panes:first .vertical-tabs-pane');
		
		panes.each(function(){
			list.eq($(this).index()).addClass($(this).attr('id'));
		});

	}

	/**
	 * Add behavior to fake submit button
	 */
	function fakeSubmitBTN() {
		$('.fake-submit').on('click', function(){
			var target = $(this).data('target');
			$(target).submit();
		});
	}

	/**
	 * Add behavior to fake submit button
	 */
	function layoutSelector() {
		$('#edit-omega-layout').once('omega-layout-selection', function(){
			var container = $(this).addClass('ac-sel');
				$('.omega-layout-selection-wrapper', this).each(function(){
					var $el = $(this);
					title = $el.find('label').text();
					radio = $el.find('input');
					$el.find('.omega-layout-icon').wrap($('<a></a>', {class: 'omega-layout-sel ac-sel', 'href': '#', 'title': title})).removeClass('omega-layout-icon');
					if (radio.attr('checked') == 'checked') {
						$el.find('.ac-sel').addClass('active');
					}
					$el.find('.omega-layout-sel').append('<i></i>').on('click', function(e){
						e.preventDefault();
						container.find('.omega-layout-selection-wrapper').find('.ac-sel').removeClass('active');
						$(this).closest('.omega-layout-selection-wrapper').find('.ac-sel').addClass('active').find('input').attr('checked', 'checked');
					});
				});
		});
	}
	
});
}(jQuery));


/**
 * Toggle vertical Tabs
 */
(function ($) {
	Drupal.behaviors.acquiaToggleVtabs = {
		attach: function (context) {
			
			$('.toggle-tabs', context)
			.data('orig-title', $('.toggle-tabs').attr('title'))
			.click(function(e) {
				e.preventDefault();
				var target = $(this).data('target');
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

  /**
   * Hide Tabs and dispaly whole fieldsets
   */
	if (typeof(Drupal.verticalTab) != "undefined") {
		Drupal.verticalTab.prototype.toggleTabs = function () {
			var window = $(window);
			return this;
		};
	}
	
})(jQuery);




(function ($) {
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

})(jQuery);


function hexToRgba(hex, opacity) {
	var rgb = hexToRgb(hex);
	if (rgb != null){
		return 'rgba('+rgb.r+', '+rgb.g+', '+rgb.b+', '+(opacity/100)+')';
	}
}

function hexToRgb(hex) {
		if (hex.length == 4) {
			hex += hex.substring(1);
		}
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

(function($) {
$(document).ready(function(){

	$('#edit-acquia-skin-skin').once('ac-skins', function(){
		var container = $(this);
			$('.ac-skin-selection-wrapper', this).each(function(){
				var $el = $(this).addClass('ac-sel');
				title = $el.find('label').text();
				radio = $el.find('input');
				if (radio.attr('checked') == 'checked') {
					$el.addClass('active');
				}
				$el.find('.ac-skin-screenshot').wrap($('<a></a>', {class: 'ac-skin-sel', 'href': '#', 'title': title}))

				$el.find('.ac-skin-sel')
				.prependTo($el.closest('.ac-skin-selection-wrapper'))
				.on('click', function(e){
					e.preventDefault();
					container.find('.ac-skin-selection-wrapper').removeClass('active');
					$(this).closest('.ac-skin-selection-wrapper').addClass('active').find('input').attr('checked', 'checked');
				});
			});
	});
	
});
}(jQuery));