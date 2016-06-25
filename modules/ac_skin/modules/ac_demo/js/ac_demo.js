/**
 * Acquia Demo - Skin changer
 */


var ACQUIA = ACQUIA || {},
	Drupal = Drupal || {};
ACQUIA.g = ACQUIA.g || {};
ACQUIA.g.demoCookiesSettings = {expires: 1, path: '/'};

(function($) {
	$(document).ready(function(){
		if( $("#ac-demo-panel").length > 0 ) {
			var skinLoader = $(Drupal.theme('skinSwitcherOverlay')).hide().appendTo("body");
		}
		else {
			return false;
		};

		var $demoPanel = $("#ac-demo-panel").css('margin', 0);

		if ($.cookie("acUserSkin")) {
			var currentSkin = $.cookie("acUserSkin");
			$('.ac-skin-preview', $demoPanel).removeClass('on');
			$('#skin-' + currentSkin).addClass('on');
			if ($.cookie("acPageLayout") == "boxed") {
				$("#ac-boxed-layout").attr("checked", "checked");
				$("body").addClass("ac-boxed-layout");
				$window.trigger("debouncedresize");
			}
		}
		// Skin selector
		$('.ac-skin-preview a', $demoPanel).click(function(e){
			e.preventDefault();
			var $this = $(this),
				skin = $this.attr("data-skin");

			$('#ac-skin-spinner').css('border-top-color', $this.attr("data-accent"));
			$this.closest('.ac-skin-preview')
				.addClass('on')
				.siblings('.ac-skin-preview')
				.removeClass('on');

			$.cookie("acUserSkin", skin, ACQUIA.g.demoCookiesSettings);
			location.reload( true );
			skinLoader.stop().fadeIn(500);
			return false;
		});

		// Close Panel
		$("#ac-demo-panel .ac-demo-close-btn .toggle").click( function (e) {
			e.preventDefault();
			if ($demoPanel.is('.on')) {
				$demoPanel.removeClass("on").animate({ margin: "0px" }, { duration: 500, complete: function () {} } );
			}
			else {
				$demoPanel.addClass("on").animate(
					{
						marginLeft: "-350px"
					}, {
						duration: 500,
					}
				);
			}
			return false;
		});

		$("#ac-demo-layout-sel input").on("change", function(e) {
			var layout = $(this).val();
			$('#ac-demo-layout-sel .form-item').removeClass('checked');
			$(this).closest('.form-item').addClass('checked');
			if ( 'wide' == layout ) {
				$("body").removeClass("ac-boxed-layout");
			} else if ( 'boxed' == layout ) {
				$("body").addClass("ac-boxed-layout");
				$window.trigger("debouncedresize");
			} else {
				return;
			}
			$(window).trigger("resize");
			$.cookie("acPageLayout", layout, ACQUIA.g.demoCookiesSettings);
		});

	});

	/**
	 * Provide the HTML to create the throbber.
	 */
	Drupal.theme.prototype.skinSwitcherOverlay = function () {
		var html = '';
		html += '  <div id="ac-skin-preloader">';
		html += '    <div id="ac-skin-status">';
		html += '       <div id="ac-skin-spinner"></div>';
		html += '    </div>';
		html += '  </div>';
		return html;
	};

}(jQuery));

