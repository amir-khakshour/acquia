Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};
Drupal.ACMegaMenu.menuInstance = false;

(function ($) {
	$.fn.megasubs = function(options){
		var opts = $.extend({}, $.fn.supersubs.defaults, options);
		// return original object to support chaining
		return this.each(function() {
			// cache selections
			var $$ = $(this);
			// support metadata
			var o = $.meta ? $.extend({}, opts, $$.data()) : opts;
			// cache all ul elements and show them in preparation for measurements
			$ULs = $$.find(o.sub_sel).show();
			// get the font size of menu.
			// .css('fontSize') returns various results cross-browser, so measure an em dash instead
			//var fontsize = $('<li id="menu-fontsize">&#8212;</li>').css({
			//	'padding' : 0,
			//	'position' : 'absolute',
			//	'top' : '-999em',
			//	'width' : 'auto'
			//}).appendTo($$)[0].clientWidth; //clientWidth is faster than .width()
			//// remove em dash
			//$('#menu-fontsize').remove();
			// loop through each ul in menu
			$ULs.each(function(i) {
				// cache this ul
				var $ul = $(this);
				// get all (li) children of this ul
				var $LIs = $ul.children();
				// get all anchor grand-children
				var $As = $LIs.children('a');
				// force content to one line and save current float property
				var liFloat = $LIs.css('white-space','nowrap').css('float');
				// remove width restrictions and floats so elements remain vertically stacked
				$ul.add($LIs).add($As).css({
					'float' : 'none',
					//'width'	: 'auto'
				});
				// this ul will now be shrink-wrapped to longest li due to position:absolute
				// so save its width as ems.
				var emWidth = $ul[0].clientWidth;

				if ($ul.is('.sub-nav-row') && parseInt($LIs.length) > 1) {
					var child_width = parseInt($ul.css("borderLeftWidth")) + parseInt($ul.css("borderRightWidth"));
					for (var i=0; i<$LIs.length; i++) {
						$($LIs[i]).css('width', $LIs[i].clientWidth);
						child_width += parseFloat($LIs[i].clientWidth);
					}
					emWidth = child_width;
				}
				// add more width to ensure lines don't turn over at certain sizes in various browsers
				emWidth += o.extraWidth;
				// restrict to at least minWidth and at most maxWidth
				//if (emWidth > o.maxWidth)		{ emWidth = o.maxWidth; }
				//else if (emWidth < o.minWidth)	{ emWidth = o.minWidth; }
				// set ul to width in ems
				if ($ul.is('.sub-nav-row') && parseInt($LIs.length) > 1){
					//emWidth = emWidth * parseInt($LIs.length);
				}
				emWidth += 'px';
				$ul.css('width',emWidth);
				// restore li floats to avoid IE bugs
				// set li width to full width of this ul
				// revert white-space to normal
				$LIs.css({
					'float' : liFloat,
					//'width' : '100%',
					'white-space' : 'normal'
				})
					// update offset position of descendant ul to reflect new width of parent.
					// set it to 100% in case it isn't already set to this in the CSS
					.each(function(){
						var $childUl = $(this).children('ul');
						var offsetDirection = $childUl.css('left') !== undefined ? 'left' : 'right';
						$childUl.css(offsetDirection,'100%');
					});
			});
		});
	};

	// expose defaults
	$.fn.megasubs.defaults = {
		minWidth : 9,
		maxWidth : 25,
		extraWidth : 0,
		sub_sel : 'ul',
	};

	Drupal.behaviors.acMegaMenuAction = {
		attach: function(context) {
			var pageWidth = $(window).width();
			$(".ac-megamenu .sub-nav", context).parent().each(function() {
				var $this = $(this);

				if (!ACQUIA.g.mobile) {
					$(this).find('.nav-column-links, .ac-multi-cols').megasubs({
						maxWidth : 75,
						sub_sel: '.mega-nav',
					});

					$(this).find('.sub-nav-rows').megasubs({
						maxWidth : 75,
						sub_sel: '.sub-nav-row',
					});
				}

				var menuTimeoutShow,
					menuTimeoutHide,
					$subMenu = $this.find("> .sub-nav")

				if ($this.is('.menu-item-has-children')){
					if($this.hasClass("l-1")){
						$this.find('> a').append('<span class="sf-sub-indicator"><i class="acquia-icon-fontello icon-down-open"></i></span>');
					}else{
						$this.find('> a').append('<span class="sf-sub-indicator"><i class="acquia-icon-fontello icon-right-open"></i></span>');
					}
				}
				if($this.hasClass("l-1")){
					if (typeof $this.data('submenuH') == 'undefined' && $this.is('.menu-item-has-children')) {
						if ($this.is('.mega-full-width')){
							$this.data('submenuH', $('> .sub-nav-rows', $subMenu).outerHeight());
						}else{
							$this.data('submenuH', $subMenu.outerHeight());
						}
					}

					$this.on("mouseenter tap", function(e) {
						if(e.type == "tap") e.stopPropagation();
						ACQUIA.g.isHovering = true;

						var $this = $(this);
						$this.addClass("sfHover");

						var	$top = $this.height();

						if ($this.hasClass('mega-full-width')) {
							$top += $this.position().top;
						}

						$subMenu.css({
							top: $top,
							display: 'none',
						});

						// if($this.hasClass("mega-auto-width")){
						// var $_this = $(this),
						// $_this_sub = $_this.find(">.sub-nav >.sub-nav-row >li"),
						// $_this_par_width = $_this.parent().width(),
						// $_this_parents_ofs = $_this.offset().left - $this.parents(".l-header .ac-table").offset().left;

						// $_this.find(" > .sub-nav").css({
						// left: $_this_parents_ofs,
						// "marginLeft": -($_this.find(" > .sub-nav").width()/2 - $_this.width()/2)
						// });
						// }
						if($this.is(':first-child') && $this.is('.mega-full-width')){
							$this.find(" > .sub-nav-fullwidth").css({
								//left: $_this.offset().left - $this.parents(".l-header .ac-table, .ph-wrap-inner, .logo-center #navigation, .logo-classic #navigation, .logo-classic-centered #navigation").offset().left,
								left: $_this.offset().left - $this.parents(".l-header .ac-table").offset().left,
								"marginLeft": 0
							});
						}else if($this.is(':last-child') && $this.is('.mega-auto-width')){
							$this.find(" > .sub-nav-autowidth").css({
								left: "auto",
								//right: $this.parents("#header .wf-table, .ph-wrap-inner, .logo-center #navigation, .logo-classic #navigation, .logo-classic-centered #navigation").width() - ( $this.position().left + $this.width() ),
								right: $this.parents(".l-header .ac-table").width() - ( $this.position().left + $this.width() ),
								"marginLeft": 0
							});
						};
						if ($(".l-page").width() - ($this.offset().left - $(".l-page").offset().left) - $this.find("> .sub-nav").width() < 0) {
							$this.children(".sub-nav").addClass("right-overflow");
						};
						if($this.position().left < ($this.find("> .sub-nav").width()/2)) {
							$this.children(".sub-nav").addClass("left-overflow");
						}
						clearTimeout(menuTimeoutShow);
						clearTimeout(menuTimeoutHide);

						menuTimeoutShow = setTimeout(function() {
							if($this.hasClass("sfHover")){
								$this.find("> .sub-nav").stop().css({"visibility":"visible", "display": "block"}).animate({
									"opacity": 1,
								}, ACQUIA.g.menuAnimDuration);
							}
						}, 100);
					});

					$this.on("mouseleave", function(e) {
						var $this = $(this);
						$this.removeClass("sfHover");

						ACQUIA.g.isHovering = false;
						clearTimeout(menuTimeoutShow);
						clearTimeout(menuTimeoutHide);

						menuTimeoutHide = setTimeout(function() {
							if(!$this.hasClass("sfHover")){
								$this.find("> .sub-nav").stop().css({"visibility":"hidden", "display": "none"}).animate({
									"opacity": 0
								}, 10);

								setTimeout(function() {
									if(!$this.hasClass("sfHover")){
										//$this.find("> .sub-nav").removeClass("right-overflow");
										//$this.find("> .sub-nav").removeClass("left-overflow");
									}
								}, ACQUIA.g.menuAnimDuration *2 );

							}
						}, 150);

						$this.find("> a").removeClass("dt-clicked");
					});
				}else if ($this.hasClass('dropdown-submenu')){
					var $this = $(this);

					if ($this.is('.l-2')) {
						var subMenuWidth = $('> .sub-nav', this).outerWidth(true),
							subMenuOffset = $(this).offset().left + subMenuWidth;
						//if((subMenuOffset + subMenuWidth) > pageWidth){
						//	$('> .sub-nav', this).addClass('right-overflow').css({
						//		left: -subMenuWidth,
						//	});
						//}
					}

					$this.on("mouseenter tap", function(e) {
						if(e.type == "tap") e.stopPropagation();
						var $this = $(this);
						$this.addClass("sfHover");

						ACQUIA.g.isHovering = true;
						clearTimeout(menuTimeoutShow);
						clearTimeout(menuTimeoutHide);

						var subMenuWidth = $('> .sub-nav', this).outerWidth(true),
							subMenuOffset = $(this).offset().left + subMenuWidth;
						if((subMenuOffset + subMenuWidth) > pageWidth){
							$('> .sub-nav', this).addClass('right-overflow').css({
								left: -subMenuWidth,
							});
						}

						menuTimeoutShow = setTimeout(function() {
							if($this.hasClass("sfHover")){
								$this.find("> .sub-nav").stop().css({"visibility":"visible", "display": "block"}).animate({
									"opacity": 1,
								}, ACQUIA.g.menuAnimDuration, function(){
									$(this).css({
										overflow: "visible"
									})
								});
							}
						}, 100);
					});

					$this.on("mouseleave", function(e) {
						var $this = $(this);
						$this.removeClass("sfHover");

						ACQUIA.g.isHovering = false;
						clearTimeout(menuTimeoutShow);
						clearTimeout(menuTimeoutHide);

						menuTimeoutHide = setTimeout(function() {
							if(!$this.hasClass("sfHover")){
								if(!$this.parents().hasClass("mega-group")){
									$this.find("> .sub-nav").stop().animate({
										"opacity": 0,
									}, ACQUIA.g.menuAnimDuration, function() {
										$(this).css({"visibility":"hidden", "display": "none"});
									});
								}

								setTimeout(function() {
									if(!$this.hasClass("sfHover")){
										//$this.find("> .sub-nav").removeClass("right-overflow");
									}
								}, ACQUIA.g.menuAnimDuration *2);
							}
						}, ACQUIA.g.menuAnimDuration);

						$this.find("> a").removeClass("dt-clicked");
					});
				};

			});

			$(".ac-multi-cols", context).each(function() {
				var maxH = 0;
				$('>.menu-item', this).each(function(){
					if ($(this).innerHeight() > maxH) {
						maxH = $(this).innerHeight();
					}
				});
				if (maxH > 0) {
					$('>.menu-item', this).css('height', maxH);
				}
			});


			/*       $('.ac-megamenu-button').click(function() {
			 if(parseInt($(this).parent().children('.nav-collapse').height())) {
			 $(this).parent().children('.nav-collapse').css({height: 0, overflow: 'hidden'});
			 }
			 else {
			 $(this).parent().children('.nav-collapse').css({height: 'auto', overflow: 'visible'});
			 }
			 });
			 var isTouch = 'ontouchstart' in window && !(/hp-tablet/gi).test(navigator.appVersion);
			 if(!isTouch){
			 $(document).ready(function($){
			 var mm_duration = 0;
			 $('.t3-megamenu').each (function(){
			 if ($(this).data('duration')) {
			 mm_duration = $(this).data('duration');
			 }
			 });
			 var mm_timeout = mm_duration ? 100 + mm_duration : 500;
			 $('.nav > li, li.mega').hover(function(event) {
			 var $this = $(this);
			 if ($this.hasClass ('mega')) {
			 $this.addClass ('animating');
			 clearTimeout ($this.data('animatingTimeout'));
			 $this.data('animatingTimeout', setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
			 clearTimeout ($this.data('hoverTimeout'));
			 $this.data('hoverTimeout', setTimeout(function(){$this.addClass ('open')}, 100));
			 } else {
			 clearTimeout ($this.data('hoverTimeout'));
			 $this.data('hoverTimeout',
			 setTimeout(function(){$this.addClass ('open')}, 100));
			 }
			 },
			 function(event) {
			 var $this = $(this);
			 if ($this.hasClass ('mega')) {
			 $this.addClass ('animating');
			 clearTimeout ($this.data('animatingTimeout'));
			 $this.data('animatingTimeout',
			 setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
			 clearTimeout ($this.data('hoverTimeout'));
			 $this.data('hoverTimeout', setTimeout(function(){$this.removeClass ('open')}, 100));
			 } else {
			 clearTimeout ($this.data('hoverTimeout'));
			 $this.data('hoverTimeout',
			 setTimeout(function(){$this.removeClass ('open')}, 100));
			 }
			 });
			 });
			 } */
		}
	}
})(jQuery);

