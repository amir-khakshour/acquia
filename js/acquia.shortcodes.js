/**
 * @file fields behaviors
 *	backend fields behaviors
 */
(function( $ ) {

/**
 * Adds functionallity to the font based icon selector.
 * when an item is clicked it stores the item code
 */
Drupal.behaviors.fieldAttachmentSel = {
	attach: function(t, n) {
		$("body").on('click', '.ac-inject-el', function() {
			var clicked = $(this),
				parent  = clicked.closest('.ac-attachment-container'),
				old 	= parent.find('.ac-active-el').removeClass('ac-active-el'),
				input	= parent.find('input.value-inject'),
				extra 	= parent.find('input[type=hidden]:eq(1)');
				
				clicked.addClass('ac-active-el');
				input.val(clicked.data('inject-val'));
				
				if(extra.length)
				{
					extra.val(clicked.html());
				}
				
				return false;
		});
	}
}


})( jQuery );