(function( $ ) {
	/**
	 * DiamondLayers   Implementation of Perfect scrollbar plugin
	 */
	$.fn.acquiaNiceScroll = function (opts, action) {
		if (!jQuery().perfectScrollbar) return this;

		var settings = {
			wheelSpeed: 100,
		};
		$.extend(true, settings, opts);

		return this.each(function () {
			$(this).perfectScrollbar(settings, action)
		});
	};

})( jQuery );


(function( $ ) {
	/**
	 * DiamondLayers   Implementation of ColorPicker plugin
	 */
	$.fn.acquiaColorPicker = function (settings) {
		if (!jQuery().ColorPicker) return this;
		return this.each(function () {
			var field = $(this),
				hex = field.val();

			field
				.parent()
				.append('<div class="selectpicker"><div></div></div>');

			field.parent().find('.selectpicker').each(function(){
				var picker = $(this);
				picker.find('div').css('backgroundColor', hex);
				$(this).ColorPicker({
					color: hex,
					onShow: function (colpkr) {
						$(colpkr).fadeIn(500);
						return false;
					},
					onHide: function (colpkr) {
						$(colpkr).fadeOut(500);
						return false;
					},
					onChange: function (hsb, hex, rgb) {
						picker.find('div').css('backgroundColor', '#' + hex);
						field.attr('value', '#' + hex).trigger('colorChanged');
					}
				});
			});

		});

		$('.colorpicker_submit').text('Submit');
	};

})( jQuery );

/**
 * DiamondLayers   Fancy Select
 */
(function ($) {
	'use strict';
	$.fn.extend({
		acquiaFancySelect: function (options) {
			// filter out <= IE6
			if (typeof document.body.style.maxHeight === 'undefined') {
				return this;
			}
			var defaults = {
					customClass: 'customSelect',
					mapClass:    true,
					mapStyle:    true
				},
				options = $.extend(defaults, options),
				prefix = options.customClass,
				changed = function ($select,customSelectSpan) {
					var currentSelected = $select.find(':selected'),
						customSelectSpanInner = customSelectSpan.children(':first'),
						html = currentSelected.html() || '&nbsp;';

					customSelectSpanInner.html(html);

					if (currentSelected.attr('disabled')) {
						customSelectSpan.addClass(getClass('DisabledOption'));
					} else {
						customSelectSpan.removeClass(getClass('DisabledOption'));
					}

					setTimeout(function () {
						customSelectSpan.removeClass(getClass('Open'));
						$(document).off('mouseup.'+getClass('Open'));
					}, 60);
				},
				getClass = function(suffix){
					return prefix + suffix;
				};

			return this.each(function () {
				var $select = $(this),
					customSelectBtn = $('<span />').addClass(getClass('Btn')),
					customSelectInnerSpan = $('<span />').addClass(getClass('Inner')),
					customSelectSpan = $('<span />');

				$select.after(customSelectSpan.append(customSelectInnerSpan));
				customSelectSpan.append(customSelectBtn);
				// add BTN

				customSelectSpan.addClass(prefix);

				if (options.mapStyle) {
					customSelectSpan.attr('style', $select.attr('style'));
				}

				$select
					.addClass('hasCustomSelect')
					.on('update', function () {
						changed($select, customSelectSpan);

						var selectBoxWidth = parseInt($select.outerWidth(), 10);

						var selectBoxHeight = customSelectSpan.outerHeight();

						if ($select.attr('disabled')) {
							customSelectSpan.addClass(getClass('Disabled'));
						} else {
							customSelectSpan.removeClass(getClass('Disabled'));
						}
					})
					.on('change', function () {
						customSelectSpan.addClass(getClass('Changed'));
						changed($select,customSelectSpan);
					})
					.on('keyup', function (e) {
						if(!customSelectSpan.hasClass(getClass('Open'))){
							$select.blur();
							$select.focus();
						}else{
							if(e.which==13||e.which==27){
								changed($select,customSelectSpan);
							}
						}
					})
					.on('mousedown', function (e) {
						customSelectSpan.addClass(getClass('Open'));
					})
					.on('mouseup', function (e) {
						customSelectSpan.removeClass(getClass('Open'));
						if( !customSelectSpan.hasClass(getClass('Open'))){
							// if FF and there are other selects open, just apply focus
							if($('.'+getClass('Open')).not(customSelectSpan).length>0 && typeof InstallTrigger !== 'undefined'){
								$select.focus();
							}else{
								e.stopPropagation();
								$(document).one('mouseup.'+getClass('Open'), function (e) {
									if( e.target != $select.get(0) && $.inArray(e.target,$select.find('*').get()) < 0 ){
										$select.blur();
									}else{
										changed($select,customSelectSpan);
									}
								});
							}
						}
					})
					.focus(function () {
						customSelectSpan.removeClass(getClass('Changed')).addClass(getClass('Focus'));
					})
					.blur(function () {
						customSelectSpan.removeClass(getClass('Focus'));
						customSelectSpan.removeClass(getClass('Open'));
					})
					.hover(function () {
						customSelectSpan.addClass(getClass('Hover'));
					}, function () {
						customSelectSpan.removeClass(getClass('Hover'));
					})
					.trigger('update');

			});
		}
	});
})(jQuery);


(function( $ ) {

// plugin definition
	$.fn.acquiaTooltip = function(options) {
		var
			defaults = {
				eventName: 'click',
				onShow: function () {},
				onBeforeShow: function(){},
				onHide: function () {},
				onChange: function () {},
				onSubmit: function () {},
				color: 'ff0000',
				livePreview: true,
				flat: false
			},
			open = function(el) {
				// Create tooltip
				$('body').prepend( $('<div>', { 'class' : 'acquia-tooltip' })
						.append( $('<div>', { 'class' : 'inner' }))
						.append( $('<span>') )
				);

				// Get tooltip
				var tooltip = $('.acquia-tooltip');

				// Set tooltip text
				tooltip.find('.inner').text( $(el).attr('data-help'));

				// Get viewport dimensions
				var v_w = $(window).width();

				// Get element dimensions
				var e_w = $(el).width();

				// Get element position
				var e_l = $(el).offset().left;
				var e_t = $(el).offset().top;

				// Get toolip dimensions
				var t_w = tooltip.outerWidth(true);
				var t_h = tooltip.outerHeight(true);

				var left_pos = e_l - (t_w - e_w) / 2;
				left_pos = left_pos > 0 ? left_pos : 0;
				// Position tooltip

				tooltip.css({ top : e_t - t_h - 10, left : left_pos  });
				// Fix right position
				if(tooltip.offset().left + t_w > v_w) {
					tooltip.css({ 'left' : 'auto', 'right' : 10 });
					tooltip.find('span').css({ left : 'auto', right : v_w - $(el).offset().left - $(el).outerWidth() / 2 - 17, marginLeft : 'auto' });
				}

			},

			close = function() {
				$('.acquia-tooltip').remove();
			};

		options = $.extend({}, defaults, options||{});

		return this.each(function () {

			$(this).mouseover(function() {
				open(this);
			});

			$(this).mouseout(function() {
				close(this);
			});

		});

	};

})( jQuery );


(function( $ ) {

	var methods = {
		init : function(options) {
			return this.each(function() {
				// Get the original element
				var el = this;

				// Hide the checkbox
				$(this).hide();

				// controll label
				$(this).closest('.form-item').find('label').addClass('acquia-checkbox-in').on('click', function(e){
					// Prevent browers default submission
					e.preventDefault();

					// Get AC checkbox
					var el = $(this).prev()[0];
					$(el).trigger('click');
				});

				// Create replacement element
				var rep = $('<a href="#"><span></span></a>').addClass('acquia-checkbox').insertAfter(this);

				// Check help attr
				if(typeof($(this).attr('data-help')) != "undefined") {
					$(rep).attr('data-help', $(this).attr('data-help')).addClass('tooltip');
				}

				// Set default state
				if($(this).is(':checked')) {
					//$(this).prop('value', true);
					$(rep).addClass('on');
				} else {
					//$(this).prop('value', false);
					$(rep).addClass('off');
				}
				// Events
				rep.on('click' , function(e) {
					$(this).acquiaCheckbox('click', e);
				});

			});

		},
		click : function(e) {
			e.preventDefault();
			// Get checkbox
			var el = $(this).prev()[0];
			if ( $(el).is(':checked') ) {
				$(el).trigger('click');
				$(el).prop('checked', false);
				//$(el).prop('value', false);
				$(el).attr('checked', false);
				$(this).removeClass('on').addClass('off');
			} else {
				$(el).trigger('click');
				//$(el).prop('value', true);
				$(el).prop('checked', true);
				$(el).attr('checked', true);
				$(this).removeClass('off').addClass('on');
			}

			// Trigger events
			//$(document).trigger( jQuery.Event('click', { target : el } ) );
		},
		hide : function( ) {  },// GOOD
		update : function( content ) {  }// !!!
	};

	$.fn.acquiaCheckbox = function(op) {
		if ( methods[op] ) {
			return methods[ op ].apply( this, Array.prototype.slice.call( arguments, 1 ));
		} else if ( typeof op === 'object' || ! op ) {
			// Default to "init"
			return methods.init.apply( this, arguments );
		} else {
			$.error( 'Method ' +  op + ' does not exist on jQuery.acquiaCheckbox' );
		}
	};

})( jQuery );


/*
 jQuery.NiceFileInput.js
 --------------------------------------
 Nice File Input - jQuery plugin which makes file inputs CSS styling an easy task.
 By Jorge Moreno - @alterebro

 Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
 Based on previous work of:
 - Shaun Inman (concept) http://www.shauninman.com/archive/2007/09/10/styling_file_inputs_with_css_and_the_dom
 - Mika Tuupola (jQuery plugin implementation) http://www.appelsiini.net/projects/filestyle
 */
(function($) {
	$.fn.nicefileinput = function(o) {
		// filter out <= IE6
		if (typeof document.body.style.maxHeight === 'undefined') {
			return this;
		}

		var s = {
			label : 'Browse', // Default button text
			customClass : 'ac-niceform-', // Default class prefix
		};

		if(o) { $.extend(s, options); };

		var prefix = s.customClass,
			/**
			 * Updates the filename tag based on the value of the real input
			 * element.
			 *
			 * @param jQuery $el Actual form element
			 * @param jQuery $filenameTag Span/div to update
			 * @param Object options Uniform options for this element
			 */
			setFilename = function($el, $filenameTag, options) {
				var filename = $el.val();

				if (filename === "") {
					filename = options.fileDefaultHtml;
				} else {
					filename = filename.split(/[\/\\]+/);
					filename = filename[(filename.length - 1)];
				}

				$filenameTag.text(filename);
			},
			getClass = function(suffix){
				return prefix + suffix;
			},
			getGid = function(){
				var d = new Date();
				return gid = d.getTime();
			};

		return this.each(function() {
			if ($(self).attr('data-styled') === undefined) {
				var gid = getGid(),
					input = $(this),
					btn = $('<span />').addClass(getClass('btn')),
					wrap = $('<span />').addClass(getClass('wrap'));

				var fakeInput = $('<div>', {
					type: 'text',
					class: getClass('fakeinput'),
					id: getClass('fakeinput')+gid,
				});

				input.addClass(getClass('base'))
					.after(wrap.append(fakeInput));

				btn.html(s.label).appendTo(wrap);

				$(btn).bind("click", function() {
					$(input).trigger('click');
				});

				$(input).bind("change", function() {
					setFilename($(input), fakeInput, {'fileDefaultHtml': ''});
				});

				$(input).attr('data-styled', true);
			}
		});

	};
})(jQuery);