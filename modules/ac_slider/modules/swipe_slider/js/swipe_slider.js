(function( $ ) {

jQuery.exists = function(selector) {
    return (jQuery(selector).length > 0);
};

$(document).ready(function(){
	$('.ac-swipe-slider').each(function() {
		var container = $(this),
				$next_arrow = container.find('.ac-swiper-nav.next'),
				$prev_arrow = container.find('.ac-swiper-nav.prev'),
				$pause = container.attr('data-pause'),
				$speed = container.attr('data-speed');
				$pager = container.attr('data-pager');
		$(Drupal.settings.ACQUIA.preloader).insertBefore(container);
		// Show item(s) when image inside is loaded
		container.css('opacity', 0).imagesLoaded(function (item) {
			var container = $(item.elements).addClass('ac-preloading'),
				isoLoader = container.siblings('.ac-preloader');
				setTimeout(function(){
					isoLoader.stop().animate({
						"opacity": 0,
					}, 150, function() {
						var acSwipe = container.swiper({
								mode: 'horizontal',
								createPagination: $pager,
								pagination: '.pagination',
								paginationClickable: true,
								loop: true,
								grabCursor: true,
								//useCSS3Transforms: true,
								mousewheelControl: false,
								// pagination : $pagination_class,
								freeModeFluid: true,
								speed: $speed,
								autoplay: $pause,
								autoplayDisableOnInteraction: true,
								onSwiperCreated: function(s) {
									container = isoLoader.siblings('.ac-preloading');
									isoLoader.css('display', 'none');
									container.removeClass('ac-preloading').animate({'opacity':1},500);
									if ($('body').is('.ac-transparent-header')) {
										$("body").removeClass("light-header dark-header").addClass(container.find(".swiper-slide").eq(1).attr("data-header-style") + "-header")
									}
								},
								onSlideChangeEnd: function(swiper) {
									if ($('body').is('.ac-transparent-header')) {
										$("body").removeClass("light-header dark-header").addClass($(acSwipe.getSlide(acSwipe.activeLoopIndex + 1)).attr("data-header-style") + "-header")
									}
								},
								onFirstInit: function(swiper) {
									ac_swipe_slider_responsive();
								}
						});

						$prev_arrow.click(function(e) {
								acSwipe.swipePrev();
						});

						$next_arrow.click(function(e) {
								acSwipe.swipeNext();
						});
					});

				},1000);
		});
	});

	function ac_swipe_slider_responsive() {
		$('.ac-swipe-slider').each(function() {
				var $this = $(this),
						$items = $this.find('.swiper-wrapper, .swiper-slide'),
						$outter = $this.closest('.swiper-outter'),
						$height = $this.attr('data-height'),
						$fullHeight = $this.attr('data-fullHeight');

				var $window_height = $(window).outerHeight();


				if ($.exists('#admin-menu')) {
						$window_height = $window_height - $('#admin-menu').outerHeight();
				}
				if ($.exists('.l-header') && !$('body').is('.ac-transparent-header')) {
						$window_height = $window_height - $('.l-header').outerHeight();
				}

				if ($.exists('.l-header')) {
						var $header_height = $('.l-header').outerHeight();
				}

				if ($(window).width() < 780) {
						$window_height = 600;
				} else if ($fullHeight == 'true') {
						$window_height = $window_height;
				} else {
						$window_height = $height;
				}

				$items.css({
						'height': $window_height
				}, 0);
				$outter.css({
						'height': $window_height
				}, 0);

				
				$this.find('.swiper-slide').each(function() {

						var $this = $(this),
								$content = $this.find('.swiper-caption'),
								$wrap = $content.closest('.swiper-caption-wrap');

						if ($content.hasClass('caption-pos-lc') || $content.hasClass('caption-pos-cc') || $content.hasClass('caption-pos-rc')) {
								var $this_height_half = $content.outerHeight() / 2,
										$window_half = $window_height / 2;

								$wrap.css({
										'marginTop': ($window_half - $this_height_half)
								});
						}

						if ($content.hasClass('caption-pos-lb') || $content.hasClass('caption-pos-cb') || $content.hasClass('caption-pos-rb')) {

								var $distance_from_top = $window_height - $content.outerHeight() - 90;

								$wrap.css({
										'marginTop': ($distance_from_top)
								});
						}

				});
		});
	}

	$(window).on("debouncedresize", function(event) {
			setTimeout(function() {
					ac_swipe_slider_responsive();
			}, 500);
	});
	
});

})( jQuery );
