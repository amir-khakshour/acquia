/**
 * @file Icon Filter Behavior
 */
(function( $ ) {
	/*-------------------------------------------------------------------------*/
	/* Progress Bar shortcode javascript
	 /*-------------------------------------------------------------------------*/
	Drupal.behaviors.acquiaIconFilter = {
		attach: function (context, settings) {
			$('.fonticon-field input.value-filter', context).each(function () {
				var container = $(this, context),
					$list = container.closest('.fieldset-wrapper').find('.ac-el-container');
				$(this).on('keyup change', function(e){
					e.stopPropagation();
					var $control = $(e.currentTarget),
						filter = '.ico-element',
						name_filter = $control.val();
					if (name_filter.length > 0) {
						filter += ":contains('" + name_filter + "')";
					}
					$( '.ico-element', $list ).removeClass( 'visible').addClass('invisible');
					$( filter, $list).removeClass('invisible').addClass( 'visible' );
				});
			});
		}
	}

})(jQuery);
