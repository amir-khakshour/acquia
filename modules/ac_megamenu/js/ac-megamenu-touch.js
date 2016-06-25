Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};

(function ($) {
  Drupal.ACMegaMenu.createTouchMenu = function(items) {
      items.children('a').each( function() {
	var $item = $(this);
        var acitem = $(this).parent();
        $item.click( function(event){
          if ($item.hasClass('ac-megamenu-clicked')) {
            var $uri = $item.attr('href');
            window.location.href = $uri;
          }
          else {
            event.preventDefault();
            $item.addClass('ac-megamenu-clicked');
            if(!acitem.hasClass('open')){	
              acitem.addClass('open');
            }
          }
        }).closest('li').mouseleave( function(){
          $item.removeClass('ac-megamenu-clicked');
          acitem.removeClass('open');
        });
     });
     /*
     items.children('a').children('span.caret').each( function() {
	var $item = $(this).parent();
        $item.click(function(event){
          acitem = $item.parent();
          if ($item.hasClass('ac-megamenu-clicked')) {
            Drupal.ACMegaMenu.eventStopPropagation(event);
            if(acitem.hasClass('open')){	
              acitem.removeClass('open');
              $item.removeClass('ac-megamenu-clicked');
            }
          }
          else {
            Drupal.ACMegaMenu.eventStopPropagation(event);
            $item.addClass('ac-megamenu-clicked');
            if(!acitem.hasClass('open')){	
              acitem.addClass('open');
              $item.removeClass('ac-megamenu-clicked');
            }
          }
        });
     });
     */
  }
  
  Drupal.ACMegaMenu.eventStopPropagation = function(event) {
    if (event.stopPropagation) {
      event.stopPropagation();
    }
    else if (window.event) {
      window.event.cancelBubble = true;
    }
  }  
  Drupal.behaviors.acMegaMenuTouchAction = {
    attach: function(context) {
      var isTouch = 'ontouchstart' in window && !(/hp-tablet/gi).test(navigator.appVersion);
      if(isTouch){
        $('html').addClass('touch');
        Drupal.ACMegaMenu.createTouchMenu($('.ac-megamenu ul.nav li.mega').has('.dropdown-menu'));
      }
    }
  }
})(jQuery);
