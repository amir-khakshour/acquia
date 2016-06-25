(function($) {
$(document).ready(function(){

	$('.ac-node-page-layout').once('ac-node-page-layout', function(){
		var container = $(this);
			$('.acquia-layout-selection-wrapper', this).each(function(){
				var $el = $(this).addClass('ac-sel');
				title = $el.find('label').text();
				radio = $el.find('input');
				if (radio.attr('checked') == 'checked') {
					$el.addClass('on');
				}
				$el.find('.acquia-layout-icon').wrapInner($('<a></a>', {class: 'acquia-layout-sel', 'href': '#', 'title': title})).removeClass('acquia-layout-icon');
				$el.find('.acquia-layout-sel').prepend('<i></i>').on('click', function(e){
					e.preventDefault();
					container.find('.acquia-layout-selection-wrapper').removeClass('on');
					$(this).closest('.acquia-layout-selection-wrapper').addClass('on').find('input').attr('checked', 'checked');
				});
			});
	});
	
});
}(jQuery));