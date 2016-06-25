(function($) {
	$(document).ready(function(){
			$('.ac-clone-options').once('ac-clone-options', function(){
				var container = $(this);
					$('.el .form-item', this).each(function(){
						var $el = $(this);
						title = $el.find('label').text();
						radio = $el.find('input');

						$el.append($('<a></a>', {class: 'ac-clone-option ac-val-'+ radio.val(), 'href': '#', 'title': title}));
						if (radio.attr('checked') == 'checked') {
							$el.find('.ac-clone-option').addClass('on');
						}
						$el.find('.ac-clone-option')
						.append($('<i></i>'))
						.append($('<span>'+title+'</span>'))
						.on('click', function(e){
							e.preventDefault();
							$(this).closest('.ac-clone-options').find('.ac-clone-option').removeClass('on');
							$(this).addClass('on').closest('.form-item').find('input').attr('checked', 'checked');
						});
					});
			});
	});
})(jQuery);