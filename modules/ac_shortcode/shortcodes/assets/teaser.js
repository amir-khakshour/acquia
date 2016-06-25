var ACQUIA = ACQUIA || {};

ACQUIA.behaviors	 = ACQUIA.behaviors || {};
ACQUIA.shortcodes  = ACQUIA.shortcodes || {};
ACQUIA.utils 			 = ACQUIA.utils || {};
	
(function($) {

	/*-------------------------------------------------------------------------*/
	/* Toggle shortcode javascript
	/*-------------------------------------------------------------------------*/
	ACQUIA.behaviors.scToggle = {
		attach: function (context, settings) {
			$('.ac-toggle-container', context).once('sc-toggle', function () {
				
				var $container = $(this),
				tagList = [];
				
				// Check if there are some toggles inside
				var $toggles = $('> .ac-toggle', this);
				if ($toggles.length == 0) {
					return;
				}

				$toggles.find('.ac-toggle-pane')
				.addClass('animated')
				.hide();
				
				if ($container.data('sorting') == 1) {
					var tags = new ACQUIA.shortcodes.scToggleTags({
						container: $container
					});
				}
					
				$toggles.each(function () {
					var toggle = this,
						tab = $(this).find('> .ac-toggle-tab'),
						pane = $(this).find('> .ac-toggle-pane'),
						$link = $('<a class="ac-toggle-title" href="#"></a>')
						.prepend(tab.contents())
						.appendTo(tab)
						.click(function (e) {
							e.preventDefault();
							if ($container.data('toggle-type') == 'accordion'){
								if ($(toggle).is('.ac-toggle-active')){
									return false;
								}
								$toggles
								.removeClass('ac-toggle-active')
								.find('.ac-toggle-pane').slideUp(400);
							}
							
							$(toggle).toggleClass('ac-toggle-active');

							if ($(toggle).is('.ac-toggle-active') && pane.is(':hidden')) {
								pane.slideDown(400);
							}else{
								pane.slideUp(400);
							}
						});
						
						if ($container.data('sorting') == 1) {
							tags.addTags($(toggle).data('tags'));
						}
						
						if ($(toggle).data('open') == 1) {
							$(toggle).addClass('ac-toggle-active').find('.ac-toggle-pane').show();
						}
						
				});
				
				if ($container.data('sorting') == 1) {
					// activate all tags
					tags.activateTag('{all}');
				}

			});
		}
	};

})(jQuery);

(function($) {

	/*-------------------------------------------------------------------------*/
	/* ACQUIA SHORCODES
	/*-------------------------------------------------------------------------*/
	ACQUIA.shortcodes = {

		/**
		 * Toggle by tags
		 */
		scToggleTags : function(settings) {
		
			/**
			 * Init function
			 */
			this.init = function(settings) {
				$.extend(this, settings);
				this.toggles = this.container.find('.ac-toggle'),
				this.tags = [],
				this.tagsHTML = $('<ul />', {class: 'tags-list'})
				.prependTo(this.container);
			},
			
			/**
			 * build tags
			 */
			this.addTags = function (_tags) {
				var self = this;
				_tags = _tags.split(' ');
				for (var i=0; i<_tags.length; i++) {
					if($.inArray(_tags[i], this.tags) === -1) { 
						this.tags.unshift(_tags[i]);
						var $tagLi = $('<li />', {class: 'tag-item'})
						.appendTo(this.tagsHTML);
						
						$('<a />', {href: '#', 'data-tag': _tags[i]})
						.text(_tags[i].replace(new RegExp('(^{)|(}$)','gm'), ''))
						.appendTo($tagLi)
						.click(function (e) {
								e.preventDefault();
								self.filter(this);
								return false;
						});
							
					}
				}
			},
			
			/**
			 * filter out toggles by given element tags
			 */
			this.filter = function (el) {
				var show = this.toggles.filter('[data-tags~="'+$(el).data('tag')+'"]'),
				hide = this.toggles.not('[data-tags~="'+$(el).data('tag')+'"]');
				this.activateTag($(el).data('tag'));
				show.slideDown(400);
				hide.slideUp(400);
			},
			
			 /**
			 * filter out toggles by given element tags
			 */
			this.activateTag = function (tag) {
				this.tagsHTML
				.find('>li').removeClass('active active-filter')
				.find('>a').filter('[data-tag="'+tag+'"]')
				.closest('li').addClass('active active-filter');
			};
			
			this.init(settings);

		},

})(jQuery);