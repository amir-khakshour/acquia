Diamond.Modal = Diamond.Modal || {};
Diamond.Modal.openInstance = [];

(function ($) {
  /**
   * Build and shows Modal window
   *
   */
  Diamond.Modal.show = function(choice) {

    var opts = {};

    if (choice && typeof choice == 'string' && Drupal.settings[choice]) {
      // This notation guarantees we are actually copying it.
      $.extend(true, opts, Drupal.settings[choice]);
    }
    else if (choice) {
      $.extend(true, opts, choice);
    }

    var defaults = {
      modalTheme: 'acquiaModalDialog',
      throbberTheme: 'acquiaModalThrobber',
      animation: 'show',
      animationSpeed: 'fast',
      modalSize: {
        type: 'scale',
        width: .8,
        height: .8,
        addWidth: 0,
        addHeight: 0,
        // How much to remove from the inner content to make space for the
        // theming.
        contentRight: 25,
        contentBottom: 45
      },
      modalOptions: {
        opacity: .55,
        background: '#fff',
      },
      callBacks: {
        beforeSave: function(){}, // @function modal window callback function when the modal is open and finished loading
        onSave: function(){}, // @function modal window callback function when the save button is hit
        onLoad: function(){}, // @function modal window callback function when the modal is open and finished loading
      },
    };

    var settings = {};
    $.extend(true, settings, defaults, Drupal.settings.acquiaModalStyle, opts);

    // @obj pass the "this" var of the invoking function to apply the correct callback later
    settings.scope = opts.scope ? opts.scope : this;

    // @obj pass the "this" var of the invoking function to apply the correct callback later
    Diamond.Modal.currentSettings = settings;

    // add new modal Instance
    Diamond.Modal.openInstance.unshift(settings);

    // Internal used props
    settings.instanceNr		= Diamond.Modal.openInstance.length;
    settings.namespace		= 'acquiaModal-' + settings.instanceNr;
    settings.selector		= '#' + settings.namespace;
    settings.backdropId 	= settings.namespace + '-backdrop';
    settings.backdropSel 	= '#' + settings.backdropId;

    this.modal = $(Drupal.theme(settings.modalTheme, settings.namespace));
    this.backdrop = $('<div />', {id: settings.backdropId, class: 'acquia-modal-backdrop', style: "z-index: 990; display: none;"});

    var resize = function(e) {
      // When creating the modal, it actually exists only in a theoretical
      // place that is not in the DOM. But once the modal exists, it is in the
      // DOM so the context must be set appropriately.
      var context = e ? document : Diamond.Modal.modal;

      if (Diamond.Modal.currentSettings.modalSize.type == 'scale') {
        var width = $(window).width() * Diamond.Modal.currentSettings.modalSize.width;
        var height = $(window).height() * Diamond.Modal.currentSettings.modalSize.height;
      }
      else {
        var width = Diamond.Modal.currentSettings.modalSize.width;
        var height = Diamond.Modal.currentSettings.modalSize.height;
      }

      // Use the additionol pixels for creating the width and height.
      $('.acquia-modal-content', context).css({
        'width': width + Diamond.Modal.currentSettings.modalSize.addWidth + 'px',
        'height': height + Diamond.Modal.currentSettings.modalSize.addHeight + 'px'
      });
    }

    resize();

    if (settings.modalSize.type == 'scale') {
      $(window).bind('resize', resize);
    }

    $(document).trigger('acquiaAttachBehaviors');
    $('span.modal-title', Diamond.Modal.modal).html(Diamond.Modal.currentSettings.loadingText);
    Diamond.Modal.modalContent(Diamond.Modal.modal, settings.modalOptions, settings.animation, settings.animationSpeed);
    $(settings.selector).find('.modal-content > .inner').html(Drupal.theme(settings.throbberTheme));
    return this;
  };

  /**
   * modalContent
   * @param content string to display in the content box
   * @param css obj of css attributes
   * @param animation (fadeIn, slideDown, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Diamond.Modal.modalContent = function(content, css, animation, speed) {
    var settings = this.currentSettings;

    // If our animation isn't set, make it just show/pop
    if (!animation) {
      animation = 'show';
    }
    else {
      // If our animation isn't "fadeIn" or "slideDown" then it always is show
      if (animation != 'fadeIn' && animation != 'slideDown') {
        animation = 'show';
      }
    }

    if (!speed) {
      speed = 'fast';
    }

    // Build our base attributes and allow them to be overriden
    css = jQuery.extend({
      position: 'absolute',
      left: '0px',
      margin: '0px',
      background: '#000',
      opacity: '.55'
    }, css);

    // Add opacity handling for IE.
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';

    // position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    if (self.pageYOffset) { // all except Explorer
      var wt = self.pageYOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      var wt = document.documentElement.scrollTop;
    } else if (document.body) { // all other Explorers
      var wt = document.body.scrollTop;
    }

    // Get our dimensions

    // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
    var docHeight = $(document).height() + 50;
    var docWidth = $(document).width();
    var winHeight = $(window).height();
    var winWidth = $(window).width();
    if( docHeight < winHeight ) docHeight = winHeight;

    // Append new modal content
    //this.backdrop.appendTo('body');
    this.modal.html($(content).html()).appendTo('body');

    // set modal margin and z-index for nested modals
    var multiplier 	= settings.instanceNr - 1,
        z_old		= 999;

    this.modal.css({margin: (30 * multiplier), zIndex: (z_old + multiplier + 1 )});
    //this.backdrop.css({zIndex: (z_old + multiplier)});

    // Keyboard and focus event handler ensures focus stays on modal elements only
    modalEventHandler = function( event ) {
      target = null;
      if ( event ) { //Mozilla
        target = event.target;
      } else { //IE
        event = window.event;
        target = event.srcElement;
      }

      var parents = $(target).parents().get();
      for (var i = 0; i < parents.length; ++i) {
        var position = $(parents[i]).css('position');
        if (position == 'absolute' || position == 'fixed') {
          return true;
        }
      }
      if( $(target).filter('*:visible').parents(settings.selector).size()) {
        // allow the event only if target is a visible child node of #modalContent
        return true;
      }
      if ( $(settings.selector)) $(settings.selector).get(0).focus();
      return false;
    };

    $('body').bind( 'focus', modalEventHandler );
    $('body').bind( 'keypress', modalEventHandler );


    // Create our content div, get the dimensions, and hide it
    var modalContent = this.modal.css({'top':'-1000px'});
    var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight(false) / 2);
    var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth(false) / 2);
    //this.backdrop.css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
    var md_temp = modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'}).remove();
    $('body').append(md_temp);

    // Bind a click for closing the modalContent
    modalContentClose = function(){close(); return false;};
    $('.close').bind('click', modalContentClose);

    // Bind a keypress on escape for closing the modalContent
    modalEventEscapeCloseHandler = function(event) {
      if (event.keyCode == 27) {
        close();
        return false;
      }
    };
    $(document).bind('keydown', modalEventEscapeCloseHandler);


    // Close the open modal content and backdrop
    function close() {

      // Unbind the events
      $(window).unbind('resize',  modalContentResize);
      $('body').unbind( 'focus', modalEventHandler);
      $('body').unbind( 'keypress', modalEventHandler );
      $('.close').unbind('click', modalContentClose);
      $('body').unbind('keypress', modalEventEscapeCloseHandler);
      $(document).trigger('acquiaDetachBehaviors', $(settings.selector));

      // Set our animation parameters and use them
      if ( animation == 'fadeIn' ) animation = 'fadeOut';
      if ( animation == 'slideDown' ) animation = 'slideUp';
      if ( animation == 'show' ) animation = 'hide';

      // Close the content
      modalContent.hide()[animation](speed);

      //remove the first entry from the openInstance array
      Diamond.Modal.closeCurrentInstance();

      // Remove the content
      $(settings.selector).remove();
      $(settings.backdropSel).remove();

    };

    // Move and resize the modalBackdrop and modalContent on resize of the window
    modalContentResize = function(){
      // Get our heights
      var docHeight = $(document).height();
      var docWidth = $(document).width();
      var winHeight = $(window).height();
      var winWidth = $(window).width();
      if( docHeight < winHeight ) docHeight = winHeight;

      // Get where we should move content to
      var modalContent = $(settings.selector);
      var mdcTop = wt +( winHeight / 2 ) - (  modalContent.outerHeight(false) / 2);
      var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth(false) / 2);

      // Apply the changes
      $(settings.backdropSel).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
    };

    $(window).bind('resize', modalContentResize);
    this.modal.draggable();
    this.modal.focus();

  };


  /**
   * unmodalContent
   * @param content (The jQuery object to remove)
   * @param animation (fadeOut, slideUp, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Diamond.Modal.unmodalContent = function(content, animation, speed) {
    var settings = Diamond.Modal.currentSettings;

    // If our animation isn't set, make it just show/pop
    if (!animation) { var animation = 'show'; } else {
      // If our animation isn't "fade" then it always is show
      if (( animation != 'fadeOut' ) && ( animation != 'slideUp')) animation = 'show';
    }
    // Set a speed if we dont have one
    if ( !speed ) var speed = 'fast';

    // Unbind the events we bound
    $(window).unbind('resize', modalContentResize);
    $('body').unbind('focus', modalEventHandler);
    $('body').unbind('keypress', modalEventHandler);
    $('.close').unbind('click', modalContentClose);
    $(document).trigger('AcquiaDetachBehaviors', $('#modalContent'));
    // Remove the content

    // jQuery magic loop through the instances and run the animations or removal.
    content.each(function(){
      if ( animation == 'fade' ) {
        $(settings.selector).fadeOut(speed, function() {
          $(settings.backdropSel).fadeOut(speed, function() {
            $(this).remove();
          });
          $(this).remove();
        });
      } else {
        if ( animation == 'slide' ) {
          $(settings.selector).slideUp(speed,function() {
            $(settings.backdropSel).slideUp(speed, function() {
              $(this).remove();
            });
            $(this).remove();
          });
        } else {
          $(settings.selector).remove();
          $(settings.backdropSel).remove();
        }
      }
    });
  };

  /**
   * Hide the modal
   */
  Diamond.Modal.dismiss = function() {

    if (Diamond.Modal.modal) {
      Diamond.Modal.unmodalContent(Diamond.Modal.modal);
    }

    Diamond.Modal.closeCurrentInstance();
  };

  /**
   * Remove current opened modal instance
   */
  Diamond.Modal.closeCurrentInstance = function() {
    var oi = Diamond.Modal.openInstance;
    var cs = Diamond.Modal.currentSettings;
    if (Diamond.Modal.openInstance.length > 1) {
      // remove current modal
      Diamond.Modal.openInstance.shift();
      // assign the modal before current modal settings as current settings
      Diamond.Modal.currentSettings = Diamond.Modal.openInstance[0];
    }else if (Diamond.Modal.openInstance.length == 1){
      // assign the modal before current modal settings as current settings
      Diamond.Modal.currentSettings = Diamond.Modal.openInstance[0];
      // remove current modal
      Diamond.Modal.openInstance.shift();
    }
  };

  /**
   * Click function for modals that can be cached.
   */
  Diamond.Modal.clickAjaxCacheLink = function () {
    Diamond.Modal.show(Diamond.Modal.getSettings(this));
    return Diamond.AJAX.clickAJAXCacheLink.apply(this);
  };

  /**
   * Handler to prepare the modal for the response
   */
  Diamond.Modal.clickAjaxLink = function () {
    Diamond.Modal.show(Diamond.Modal.getSettings(this));
    return false;
  };

  /**
   * Submit responder to do an AJAX submit on all modal forms.
   */
  Diamond.Modal.submitAjaxForm = function(e) {
    var $form = $(this);
    var url = $form.attr('action');

    setTimeout(function() { Diamond.AJAX.ajaxSubmit($form, url); }, 1);
    return false;
  }


  // The following are implementations of AJAX responder commands.
  /**
   * AJAX responder command to place HTML within the modal.
   */
  Diamond.Modal.modal_display = function(ajax, response, status) {
    var settings = Diamond.Modal.currentSettings;

    if ($(settings.selector).length == 0) {
      Diamond.Modal.show();
    }
    $(settings.selector).find('.modal-title').html(response.title);
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.

    $('#' + settings.namespace + '-content > .inner').html(response.output).scrollTop(0);
    Drupal.attachBehaviors();
  }

  /**
   * AJAX responder command to dismiss the modal.
   */
  Diamond.Modal.modal_dismiss = function(command) {
    Diamond.Modal.dismiss();
    $('link.acquia-temporary-css').remove();
  }


  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.acquiaModalDialog = function (namespace) {
    var html = '',
        save = '';

    if (Diamond.Modal.currentSettings.modalSaveBtn != undefined && Diamond.Modal.currentSettings.modalSaveBtn == true) {
      save = '<a href="#save" class="acquia-modal-save acquia-button button button-primary button-large">';
      save += Diamond.Modal.currentSettings.saveBtnText;
      save += '</a>';
    }

    html += '	<div id="'+namespace+'" style="position:absolute" class="acquia-modal-wrap">'
    html += '		<div class="acquia-modal-inner">' // panels-modal-content
    html += '			<div class="acquia-modal ac-admin fancy-select">';
    html += '				<div id="'+namespace+'-header" class="modal-header">';
    html += '       			<h2 id="modal-title" class="modal-title">&nbsp;</h2>';
    html += '					<a class="close modal-close" href="#" title="'+Diamond.Modal.currentSettings.closeText+'">';
    html += '						<span class="admin-icon"></span>';
    html += '      	 			 </a>';
    html += '				</div>';
    html += '      			<div id="'+namespace+'-content" class="modal-content acquia-modal-content nice-scroll">';
    html += '      				<div class="inner">';
    html += '					</div>';
    html += '				</div>';
    html += '      			<div id="'+namespace+'-footer" class="modal-footer">' + save;
    html += '					<div class="modal-footer-inner">';
    html += '					</div>';
    html += '				</div>';
    html += '			</div>';
    html += '		</div>';
    html += '	</div>';

    return html;
  }

  /**
   * Provide the HTML to create the throbber.
   */
  Drupal.theme.prototype.acquiaModalThrobber = function () {
    var html = '';
    html += '  <div id="modal-throbber">';
    html += '    <div class="modal-throbber-wrapper">';
    html += '<div class="sk-folding-cube">';
    html += '  <div class="sk-cube1 sk-cube"></div>';
    html += '  <div class="sk-cube2 sk-cube"></div>';
    html += '  <div class="sk-cube4 sk-cube"></div>';
    html += '  <div class="sk-cube3 sk-cube"></div>';
    html += '</div>';
    html += '    </div>';
    html += '  </div>';

    return html;
  };

  /**
   * Figure out what settings string to use to display a modal.
   */
  Diamond.Modal.getSettings = function (object) {
    var match = $(object).attr('class').match(/acquia-modal-(\S+)/);
    if (match) {
      return match[1];
    }
  }


  $(function() {
    Drupal.ajax.prototype.commands.acquia_modal_display = Diamond.Modal.modal_display;
    Drupal.ajax.prototype.commands.acquia_modal_dismiss = Diamond.Modal.modal_dismiss;
    Drupal.ajax.prototype.commands.acquia_modal_loading = Diamond.Modal.modal_loading;
  });

})(jQuery);

(function ($) {



  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.acquiaModal = {
    attach: function(context) {
      // Bind links
      // Note that doing so in this order means that the two classes can be
      // used together safely.
      /*
       * @todo remimplement the warm caching feature
       $('a.acquia-use-modal-cache', context).once('acquia-use-modal', function() {
       $(this).click(Diamond.Modal.clickAjaxCacheLink);
       Diamond.AJAX.warmCache.apply(this);
       });
       */
      // Bind our custom event to the form submit
      if ( $('.acquia-modal-save').length >0 ) {
        $('.acquia-modal-save').closest('.acquia-modal-wrap').addClass('save-btn-on').find('input[value="'+Drupal.t('submit')+'"]').css('display', 'none');
        $('.acquia-modal-save').click(function(e){
          e.preventDefault();
          $(this).closest('.acquia-modal-wrap').find('form input[value="'+Drupal.t('submit')+'"]').trigger('click');
          return false;
        });
      }

      $('input', context).keypress(function (e) {
        if (e.which == 13) {
          $(this).closest('.acquia-modal-wrap').find('form input[value="'+Drupal.t('submit')+'"]').trigger('click');
        }
      });

      $('area.acquia-use-modal, a.acquia-use-modal', context).once('acquia-use-modal', function() {
        var $this = $(this);
        $this.click(Diamond.Modal.clickAjaxLink);
        // Create a drupal ajax object
        var element_settings = {};
        if ($this.attr('href')) {
          element_settings.url = $this.attr('href');
          element_settings.event = 'click';
          element_settings.progress = { type: 'throbber' };
        }
        var base = $this.attr('href');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
      });

      // Bind buttons
      $('input.acquia-use-modal, button.acquia-use-modal', context).once('acquia-use-modal', function() {
        var $this = $(this);
        $this.click(Diamond.Modal.clickAjaxLink);
        var button = this;
        var element_settings = {};

        // AJAX submits specified in this manner automatically submit to the
        // normal form action.
        element_settings.url = Diamond.Modal.findURL(this);
        element_settings.event = 'click';

        var base = $this.attr('id');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);

        // Make sure changes to settings are reflected in the URL.
        $('.' + $(button).attr('id') + '-url').change(function() {
          Drupal.ajax[base].options.url = Diamond.Modal.findURL(button);
        });
      });

      // Bind our custom event to the form submit
      $('.acquia-modal-wrap form', context).once('acquia-use-modal', function() {
        var $this = $(this);
        var element_settings = {};

        element_settings.url = $this.attr('action');
        element_settings.event = 'submit';
        element_settings.progress = { 'type': 'throbber' }
        var base = $this.attr('id');

        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
        Drupal.ajax[base].form = $this;

        $('input[type=submit], button', this).click(function(event) {
          Drupal.ajax[base].element = this;
          this.form.clk = this;
          // An empty event means we were triggered via .click() and
          // in jquery 1.4 this won't trigger a submit.
          if (event.bubbles == undefined) {
            $(this.form).trigger('submit');
            return false;
          }
        });
      });

      // Bind a click handler to allow elements with the 'acquia-close-modal'
      // class to close the modal.
      $('.acquia-close-modal', context).once('acquia-close-modal')
          .click(function() {
            Diamond.Modal.dismiss();
            return false;
          });

      // add class to wysiwyg editor wrapper so we can style it properly
      $('.filter-list.wysiwyg', context).once('acquia-filter-list', function() {
        $(this).closest('.text-format-wrapper').addClass('acquia-wysiwyg-enabled');
      });


    }
  };

  // add acquia-modal-on to body for styling
  $(document).on('acquiaAttachBehaviors acquiaDetachBehaviors', function(){
    $('body').toggleClass('acquia-modal-on');
  });

})(jQuery);

/**
 * Get Modal Size factors
 *
 * @param {string} size - size of modal (smal, medium, big, full)
 * @return {array} width and height factors of modal based on window width and height
 */
function acquia_get_modal_size_factor(size) {
  switch (size) {
    case 'small':
      return {'width':.5, 'height':.5};

    default:
    case 'medium':
      return {'width':.6, 'height':.6};

    case 'big':
      return {'width':.75, 'height':.75};

    case 'bigger':
      return {'width':.85, 'height':.85};

    case 'full':
      return {'width':1, 'height':1};
  }
}

