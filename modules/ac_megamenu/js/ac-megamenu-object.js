Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};

!function ($) {
  var currentSelected = null,
      megamenu,
      nav_items,
      nav_subs,
      nav_cols,
      nav_all,
      modal_open = false;

  Drupal.ACMegaMenu.lockedAjax = false;

  Drupal.ACMegaMenu.lockAjax = function() {
    Drupal.ACMegaMenu.lockedAjax = true;
  }

  Drupal.ACMegaMenu.isLockedAjax = function() {
    return Drupal.ACMegaMenu.lockedAjax;
  }

  Drupal.ACMegaMenu.releaseAjax = function() {
    Drupal.ACMegaMenu.lockedAjax = false;
  }

  $.fn.megamenuAdmin = function (options) {
    var defaultOptions = {};
    var options = $.extend(defaultOptions, options);
    megamenu = $(this).find('.ac-megamenu');
    nav_items = megamenu.find('ul[class*="l-"]>li>:first-child');
    nav_subs = megamenu.find('.nav-child');
    nav_cols = megamenu.find('[class*="span"]');

    nav_all = nav_items.add(nav_subs).add(nav_cols);
    nav_items.each (function () {
      var a = $(this);
      var liitem = a.closest('li');
      if (liitem.attr('data-hidesub') == 1) {
        var sub = liitem.find('.nav-child:first');
        sub.css('display','none');
        a.removeClass ('dropdown-toggle').attr('data-toggle', '');
        liitem.removeClass('dropdown dropdown-submenu mega');
      }
    });

    $('#ac-megamenu-admin-mm-intro').show();

    bindEvents (nav_all);
    $('.toolbox-action, .toolbox-toggle, .toolbox-input').unbind ("focus blur click change keydown");
    $('.ac-megamenu-admin-mm-row').click (function(event) {
      event.stopPropagation();
    });

    $(document.body).click (function(event) {
      if (!modal_open){
        hide_toolbox (true);
      }
    });

    $('.back-megamenu-toolbox').click (function(event) {
      hide_toolbox (true);
    });

    $('.toolbox-action').click (function(event) {
      var action = $(this).attr('data-action');
      if (action) {
        actions.datas = $(this).data();
        actions[action] (options);
      }
      event.stopPropagation();
      return false;
    });

    $('.toolbox-toggle').change (function(event) {
      var action = $(this).attr('data-action');
      if (action) {
        actions.datas = $(this).data();
        actions[action] (options);
      }
      event.stopPropagation();
      return false;
    });

    $('.toolbox-input').bind ('focus blur click', function(event) {
      event.stopPropagation();
      return false;
    });

    $('.toolbox-input').bind ('keydown', function(event) {
      if (event.keyCode == '13') {
        apply_toolbox (this);
        event.preventDefault();
      }
    });

    $('.toolbox-input').change (function(event) {
      apply_toolbox (this);
      event.stopPropagation();
      return false;
    });

    $('.ac-fonticon-sel').on('click', function(event) {
      event.stopImmediatePropagation();
      // Build Modal
      var settings = Drupal.settings.acquiaModalStyle;
      settings.modalSize.height = .85;
      settings.modalSize.width = .85;
      settings.modalSaveBtn = true;
      Diamond.Modal.show(settings);
      modal_open = true;

      // Create a drupal ajax object
      var element_settings = {},
          toolItem = $(this).closest('li').find('input[name="toolitem-xicon"]');

      element_settings.url = Drupal.settings.basePath + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_URL;
      element_settings.progress = { type: 'throbber' };
      ajax = new Drupal.ajax(window.ajaxurl, this, element_settings);
      ajax.submit.action = 'load_font_icons';
      ajax.submit.mid = toolItem.attr('data-id');
      ajax.submit.icon = toolItem.val();
      $.ajax(ajax.options);
      return false;
    });

    return this;
  };

  /**
   *  Actions
   * @type {{}}
   */
  var actions = {};
  actions.data = {};
  /**
   * @action
   * Remove Background Image
   */
  actions.removeBG = function () {
    if (!currentSelected) return;
    currentSelected.attr('data-fid', '');
    currentSelected.attr('data-src', '');
    update_toolbox ();
  };
  /**
   * @action
   * Upload Background Image
   */
  actions.uploadBg = function () {
    if (!currentSelected) return;
    modal_open = true;
    Drupal.media.popups.mediaBrowser(function(t) {
      var mediaFile = t[0];
      currentSelected.attr('data-fid', mediaFile.fid);
      currentSelected.attr('data-src', mediaFile.url);
      update_toolbox();
    });
  };
  actions.fullWidthSubmenu = function () {
    if (!currentSelected) return ;
    var liitem = currentSelected.parent().toggleClass('mega-full-width');
    var sub = liitem.find ('.nav-child:first');

    var toggle = $('.input[name="togglesubFullPageWidth"]');
    toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
    if(parseInt(toggle.attr('data-auto-arrow'))) {
      update_toggle (toggle, 0);
      toggle.attr('data-auto-arrow', 0);
    }
    else {
      update_toggle (toggle, 1);
      toggle.attr('data-auto-arrow', 1);
    }

    var type = toolbox_type ();
    sub.attr('data-fullwidth', $('input[name="togglesubFullPageWidth"]:checked').val());
    update_toolbox ();
  };
  actions.toggleSub = function () {
    if (!currentSelected) {
      return ;
    }
    var liitem = currentSelected.closest('li'),
        sub = liitem.find ('.nav-child:first');
    if (parseInt(liitem.attr('data-group'))) {
      return;
    }
    if (sub.length == 0 || sub.css('display') == 'none') {
      if (sub.length == 0) {
        var column = Drupal.ACMegaMenu.ACElementsCounter['column'] + 1;
        Drupal.ACMegaMenu.ACElementsCounter['column'] ++;
        sub = $('<div class="ac-megamenu-submenu nav-child dropdown-menu mega-dropdown-menu"><div class="row-fluid"><div id=ac-megamenu-column-' + column + ' class="span12" data-width="12"><div class="mega-inner"></div></div></div></div>').appendTo(liitem);
        bindEvents (sub.find ('[class*="span"]'));
        liitem.addClass ('mega');
      }
      else {
        sub.css('display', '');
        liitem.attr('data-hidesub', 0);
      }
      liitem.attr('data-group', 0);
      currentSelected.addClass ('dropdown-toggle').attr('data-toggle', 'dropdown');
      liitem.addClass(liitem.attr('data-level') == 1 ? 'dropdown' : 'dropdown-submenu');
      bindEvents(sub);
    }
    else {
      unbindEvents(sub);
      if (liitem.find('ul.l-'+liitem.attr('data-level')).length > 0) {
        sub.css('display','none');
        liitem.attr('data-hidesub', 1);
      }
      else {
        sub.remove();
      }
      liitem.attr('data-group', 0);
      currentSelected.removeClass ('dropdown-toggle').attr('data-toggle', '');
      liitem.removeClass('dropdown dropdown-submenu mega');
    }
    update_toolbox ();
  }

  actions.toggleAutoArrow = function() {
    var toggle = $('.toolitem-auto-arrow');
    toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
    if(parseInt(toggle.attr('data-auto-arrow'))) {
      update_toggle (toggle, 0);
      toggle.attr('data-auto-arrow', 0);
    }
    else {
      update_toggle (toggle, 1);
      toggle.attr('data-auto-arrow', 1);
    }
  }

  actions.toggleAlwayShowSubmenu = function() {
    var toggle = $('.toolitem-always-show-submenu');
    toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
    if(parseInt(toggle.attr('data-always-show-submenu'))) {
      update_toggle (toggle, 0);
      toggle.attr('data-always-show-submenu', 0);
    }
    else {
      update_toggle (toggle, 1);
      toggle.attr('data-always-show-submenu', 1);
    }
  }

  actions.showBlockTitle = function() {
    if (!currentSelected) return ;
    var toggle = $('.toolcol-showblocktitle');
    toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
    if(parseInt(currentSelected.attr('data-showblocktitle'))) {
      update_toggle (toggle, 0);
      currentSelected.attr('data-showblocktitle', 0);
    }
    else {
      update_toggle (toggle, 1);
      currentSelected.attr('data-showblocktitle', 1);
    }
    if($('#ac-megamenu-block-wrapper select[name="toolcol-block"]').val() != '') {
      value = $('#ac-megamenu-block-wrapper select[name="toolcol-block"]').val();
      $('#ac-megamenu-admin-mm-ac #toolbox-loading').show();
      callAjax({'action': 'load_block', 'block_key': value, 'id': currentSelected.attr('id'), 'showblocktitle': parseInt(currentSelected.attr('data-showblocktitle'))});
    }
  }

  actions.toggleGroup = function () {
    if (!currentSelected) return ;
    var liitem = currentSelected.parent();
    var sub = liitem.find ('.nav-child:first');
    if (liitem.attr('data-level') == 1) {
      return;
    } // ignore for top level
    if (parseInt(liitem.attr('data-group'))) {
      liitem.attr('data-group', 0);
      liitem.removeClass('mega-group').addClass('dropdown-submenu');
      currentSelected.addClass ('dropdown-toggle').attr('data-toggle', 'dropdown');
      sub.removeClass ('mega-group-ct').addClass ('dropdown-menu mega-dropdown-menu');
      sub.css('width', sub.attr('data-width'));
      rebindEvents(sub);
    } else {
      currentSelected.removeClass ('dropdown-toggle').attr('data-toggle', '');
      liitem.attr('data-group', 1);
      liitem.removeClass('dropdown-submenu').addClass('mega-group');
      sub.removeClass ('dropdown-menu mega-dropdown-menu').addClass ('mega-group-ct');
      sub.css('width', '');
      rebindEvents(sub);
    }
    update_toolbox ();
  }

  actions.hideWhenCollapse = function () {
    if (!currentSelected) {
      return ;
    }
    var type = toolbox_type ();
    if (type == 'sub') {
      var liitem = currentSelected.closest('li');
      if (parseInt(liitem.attr('data-hidewcol'))) {
        liitem.attr('data-hidewcol', 0);
        liitem.removeClass ('sub-hidden-collapse');
      }
      else {
        liitem.attr('data-hidewcol', 1);
        liitem.addClass ('sub-hidden-collapse');
      }
    }
    else if (type == 'col') {
      if (parseInt(currentSelected.attr('data-hidewcol'))) {
        currentSelected.attr('data-hidewcol', 0);
        currentSelected.removeClass ('hidden-collapse');
      }
      else {
        currentSelected.attr('data-hidewcol', 1);
        currentSelected.addClass ('hidden-collapse');
      }
    }
    update_toolbox ();
  }

  actions.alignment = function () {
    var liitem = currentSelected.closest ('li');
    liitem.removeClass ('mega-align-left mega-align-center mega-align-right mega-align-justify').addClass ('mega-align-'+actions.datas.align);
    if (actions.datas.align == 'justify') {
      currentSelected.addClass('span12');
      currentSelected.css('width', '');
    } else {
      currentSelected.removeClass('span12');
      if (currentSelected.attr('data-width')) {
        currentSelected.css('width', currentSelected.attr('data-width'));
      }
    }
    liitem.attr('data-alignsub', actions.datas.align);
    update_toolbox ();
  }

  actions.moveItemsLeft = function () {
    if (!currentSelected) {
      return ;
    }
    var $item = currentSelected.closest('li'),
        $liparent = $item.parent().closest('li'),
        level = $liparent.attr('data-level'),
        $col = $item.closest ('[class*="span"]'),
        $items = $col.find ('ul:first > li'),
        itemidx = $items.index ($item),
        $moveitems = $items.slice (0, itemidx+1),
        itemleft = $items.length - $moveitems.length,
        $rows = $col.parent().parent().children ('[class*="row"]'),
        $cols = $rows.children('[class*="span"]').filter (function(){return !$(this).attr('data-block')}),
        colidx = $cols.index ($col);
    if (!$liparent.length) {
      return ;
    } // need make this is mega first

    if (colidx == 0) {
      var oldSelected = currentSelected;
      currentSelected = $col;
      actions.datas.addfirst = true;
      actions.addColumn ();
      $cols = $rows.children('[class*="span"]').filter (function(){return !$(this).attr('data-block')});
      currentSelected = oldSelected;
      colidx++;
    }
    var $tocol = $($cols[colidx-1]);
    var $ul = $tocol.find('ul:first');
    if (!$ul.length) {
      $ul = $('<ul class="mega-nav l-'+level+' ac-megamenu-subnav">').appendTo ($tocol.children('.mega-inner'));
    }
    $moveitems.appendTo($ul);
    if (itemleft == 0) {
      $col.find('ul:first').remove();
    }
    update_toolbox ();
  }

  actions.moveItemsRight = function () {
    if (!currentSelected) {
      return ;
    }
    var $item = currentSelected.closest('li'),
        $liparent = $item.parent().closest('li'),
        level = $liparent.attr('data-level'),
        $col = $item.closest ('[class*="span"]'),
        $items = $col.find ('ul:first > li'),
        itemidx = $items.index ($item),
        $moveitems = $items.slice (itemidx),
        itemleft = $items.length - $moveitems.length,
        $rows = $col.parent().parent().children ('[class*="row"]'),
        $cols = $rows.children('[class*="span"]').filter (function(){
          return $(this).children('.mega-inner').children('.ac-megamenu-block').length == 0;
        });

    var colidx = $cols.index ($col);
    if (!$liparent.length) {
      return ;
    } // need make this is mega first

    if (colidx == $cols.length - 1) {
      var oldSelected = currentSelected;
      currentSelected = $col;
      actions.datas.addfirst = false;
      actions.addColumn ();
      $cols = $rows.children('[class*="span"]').filter (function(){
        return $(this).children('.mega-inner').children('.ac-megamenu-block').length == 0;
      }),
          currentSelected = oldSelected;
    }
    var $tocol = $($cols[colidx+1]);
    var $ul = $tocol.find('.mega-inner ul.ac-megamenu-subnav:first');
    if (!$ul.length) {
      $ul = $('<ul class="mega-nav l-'+level+' ac-megamenu-subnav">').appendTo ($tocol.children('.mega-inner'));
    }
    $moveitems.prependTo($ul);
    if (itemleft == 0) {
      $col.find('ul:first').remove();
    }
    show_toolbox (currentSelected);
  }

  actions.addRow = function () {
    if (!currentSelected) {
      return ;
    }
    var column = Drupal.ACMegaMenu.ACElementsCounter['column'] + 1;
    Drupal.ACMegaMenu.ACElementsCounter['column'] ++;
    var $row = $('<div class="row-fluid"><div id=ac-megamenu-column-' + column + ' class="span12"><div class="mega-inner"></div></div></div>').appendTo(currentSelected.find('[class*="row"]:first').parent()),
        $col = $row.children();
    bindEvents ($col);
    currentSelected = null;
    show_toolbox ($col);
  }

  actions.addColumn = function () {
    if (!currentSelected) {
      return ;
    }
    var $cols = currentSelected.parent().children('[class*="span"]');
    var colcount = $cols.length + 1;
    var colwidths = defaultColumnsWidth (colcount);

    var column = Drupal.ACMegaMenu.ACElementsCounter['column'] + 1;
    Drupal.ACMegaMenu.ACElementsCounter['column'] ++;

    var $col = $('<div id=ac-megamenu-column-' + column + '><div class="mega-inner"></div></div>');
    if (actions.datas.addfirst) {
      $col.prependTo (currentSelected.parent());
    }
    else {
      $col.insertAfter (currentSelected);
    }
    $cols = $cols.add ($col);
    bindEvents ($col);
    $cols.each (function (i) {
      $(this).removeClass ('span'+$(this).attr('data-width')).addClass('span'+colwidths[i]).attr('data-width', colwidths[i]);
    });
    show_toolbox ($col);
  }

  actions.removeColumn = function () {
    if (!currentSelected) {
      return;
    }

    var $col = currentSelected,
        $row = $col.parent(),
        $rows = $row.parent().children ('[class*="row"]'),
        $allcols = $rows.children('[class*="span"]'),
        $allmenucols = $allcols.filter (function(){return !$(this).attr('data-block')}),
        $haspos = $allcols.filter (function(){return $(this).attr('data-block')}).length,
        $cols = $row.children('[class*="span"]'),
        colcount = $cols.length - 1,
        colwidths = defaultColumnsWidth (colcount),
        type_menu = $col.attr('data-block') ? false : true;

    if ((type_menu && ((!$haspos && $allmenucols.length == 1) || ($haspos && $allmenucols.length == 0))) || $allcols.length == 1) {
      show_toolbox ($(currentSelected).closest('.ac-megamenu-item'));
      currentSelected = $(currentSelected).closest('.ac-megamenu-item')
      currentSelected.find('.ac-megamenu-submenu').remove();

    } // if this is the only one column left
    else {
      if (type_menu) {
        var colidx = $allmenucols.index($col),
            tocol = colidx == 0 ? $allmenucols[1] : $allmenucols[colidx-1];

        $col.find ('ul:first > li').appendTo ($(tocol).find('ul:first'));
      }

      var colidx = $allcols.index($col),
          nextActiveCol = colidx == 0 ? $allcols[1] : $allcols[colidx-1];

      if (colcount < 1) {
        $row.remove();
      } else {
        $cols = $cols.not ($col);
        $cols.each (function (i) {
          $(this).removeClass ('span'+$(this).attr('data-width')).addClass('span'+colwidths[i]).attr('data-width', colwidths[i]);
        });
        $col.remove();
      }
      show_toolbox ($(nextActiveCol));
    }
  }

  actions.resetConfig = function (options) {
    if(Drupal.ACMegaMenu.isLockedAjax()) {
      window.setTimeout(function() {
        actions.resetConfig(options);
      }, 200);
      return;
    }
    Drupal.ACMegaMenu.lockAjax();
    $('#ac-megamenu-admin-mm-ac #toolbox-message').html("").hide();
    $('#ac-megamenu-admin-mm-ac #toolbox-loading').show();
    $.ajax({
      type: "POST",
      url: Drupal.settings.basePath + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_URL,
      data: { 'action': 'load', 'menu_name': options['menu_name']},
      complete: function( msg ) {
        $('#ac-megamenu-admin-mm-container').html(msg.responseText).megamenuAdmin({'menu_name': options['menu_name']});
        $('#ac-megamenu-admin-mm-container').find('.mega-inner').children('span.close').click(function() {
          $(this).parent().html("");
        });
        $('#ac-megamenu-admin-mm-ac #toolbox-loading').hide();
        $('#ac-megamenu-admin-mm-ac #toolbox-message').html(Drupal.t("All unsaved changed has been reseted!")).show();
        window.setTimeout(function() {
          $('#ac-megamenu-admin-mm-ac #toolbox-message').html("").hide();
        }, 5000);
        Drupal.ACMegaMenu.releaseAjax();
      }
    });
  }

  actions.saveConfig = function (options) {
    if(Drupal.ACMegaMenu.isLockedAjax()) {
      window.setTimeout(function() {
        actions.saveConfig(options);
      }, 200);
      return;
    }
    Drupal.ACMegaMenu.lockAjax();
    var menu_config = {},
        items = megamenu.find('ul[class*="l-"] > li');
    items.each (function(){
      var $this = $(this),
          id = $this.attr('data-id'),
          rows = [];
      var level = parseInt($this.attr('data-level'));
      var $sub = $this.find ('.nav-child:first');
      var $rows = $sub.find('[class*="row"]:first').parent().children('[class*="row"]');
      $rows.each (function () {
        var $cols = $(this).children('[class*="span"]');
        var cols = [];
        $cols.each (function(){
          var col_config = {};
          col_config['width'] = $(this).attr('data-width') ? $(this).attr('data-width') : "";
          col_config['class'] = $(this).attr('data-class') ? $(this).attr('data-class') : "";
          col_config['hidewcol'] = $(this).attr('data-hidewcol') ? $(this).attr('data-hidewcol') : "";
          col_config['fid'] = $(this).attr('data-fid') ? $(this).attr('data-fid') : "";
          col_config['showblocktitle'] = $(this).attr('data-showblocktitle') ? $(this).attr('data-showblocktitle') : "1";
          var col = {'col_content': [], 'col_config': col_config};
          $(this).find('ul[class*="l-"] > li:first').each(function() {
            var sub_level = parseInt($(this).attr('data-level'));
            if(sub_level == level + 1) {
              var ele = {};
              ele['mlid'] = $(this).attr('data-id');
              ele['type'] = $(this).attr('data-type');
              ele['ac_item_config'] = {};
              col['col_content'].push(ele);
            }
          });
          $(this).children('.mega-inner').children('.ac-megamenu-block').each(function() {
            var ele = {};
            ele['block_key'] = $(this).attr('data-block');
            ele['type'] = $(this).attr('data-type');
            ele['ac_item_config'] = {};
            col['col_content'].push(ele);
          });
          cols.push(col);
        });
        if(cols.length) {
          rows.push(cols);
        }
      });
      var submenu_config = {};
      submenu_config['width'] = $this.children('.mega-dropdown-menu').attr('data-width') ? $this.children('.mega-dropdown-menu').attr('data-width') : "";
      submenu_config['class'] = $this.children('.mega-dropdown-menu').attr('data-class') ? $this.children('.mega-dropdown-menu').attr('data-class') : "";
      submenu_config['group'] = $this.attr('data-group') ? $this.attr('data-group') : 0;
      submenu_config['fullwidth'] = $this.children('.mega-dropdown-menu').attr('data-fullwidth') ? $this.children('.mega-dropdown-menu').attr('data-fullwidth') : "0";
      submenu_config['fid'] = $sub.attr('data-fid') ? $sub.attr('data-fid') : "";
      var item_config = {};
      item_config['class'] = $this.attr('data-class') ? $this.attr('data-class') : "";
      item_config['xicon'] = $this.attr('data-xicon') ? $this.attr('data-xicon') : "";
      item_config['caption'] = $this.attr('data-caption') ? $this.attr('data-caption') : "";
      item_config['alignsub'] = $this.attr('data-alignsub') ? $this.attr('data-alignsub') : "";
      item_config['group'] = $this.attr('data-group') ? $this.attr('data-group') : "";
      item_config['hidewcol'] = $this.attr('data-hidewcol') ? $this.attr('data-hidewcol') : 1;
      item_config['hidesub'] = $this.attr('data-hidesub') ? $this.attr('data-hidesub') : 1;
      config = {'rows_content': rows, 'submenu_config': submenu_config, 'item_config': item_config};
      menu_config[id] = config;
    });
    var block_config = {};
    block_config['animation'] = $('select[name="ac-megamenu-animation"]').val();
    block_config['duration'] = parseInt($('input[name="ac-megamenu-duration"]').val());
    block_config['delay'] = parseInt($('input[name="ac-megamenu-delay"]').val());
    block_config['style'] = $('select[name="ac-megamenu-style"]').val();
    block_config['auto-arrow'] = $('#ac-megamenu-admin-mm-intro .toolitem-auto-arrow').attr('data-auto-arrow');
    block_config['always-show-submenu'] = $('#ac-megamenu-admin-mm-intro .toolitem-always-show-submenu').attr('data-always-show-submenu');
    $('#ac-megamenu-admin-mm-ac #toolbox-message').html("").hide();
    $('#ac-megamenu-admin-mm-ac #toolbox-loading').show();
    $.ajax({
      type: "POST",
      dataType: 'json',
      url: Drupal.settings.basePath + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_URL,
      data: {'action': 'save', 'menu_name': options['menu_name'], 'menu_config': JSON.stringify(menu_config), 'block_config': JSON.stringify(block_config)},
      complete: function( msg ) {
        $('#ac-megamenu-admin-mm-ac #toolbox-loading').hide();
        $div = $('<div id="console" class="clearfix"><div class="messages status"><h2 class="element-invisible">Status message</h2>' + Drupal.t("Saved config sucessfully!") + '</div></div>');
        $('#ac-megamenu-admin-mm-ac #toolbox-message').html($div).show();
        window.setTimeout(function() {
          $('#ac-megamenu-admin-mm-ac #toolbox-message').html("").hide();
        }, 5000);
        Drupal.ACMegaMenu.releaseAjax();
      }
    });
  }

  toolbox_type = function () {
    return currentSelected ? currentSelected.hasClass ('nav-child') ? 'sub' : (currentSelected[0].tagName == 'DIV' ? 'col':'item') : false;
  }

  hide_toolbox = function (show_intro) {
    $('#ac-megamenu-admin-mm-ac .admin-toolbox').hide();
    currentSelected = null;
    if (megamenu && megamenu.data('nav_all')) megamenu.data('nav_all').removeClass ('selected');
    megamenu.find ('li').removeClass ('open');
    if (show_intro) {
      $('#ac-megamenu-admin-mm-intro').show();
    } else {
      $('#ac-megamenu-admin-mm-intro').hide();
    }
  }

  show_toolbox = function (selected) {
    if(!selected.hasClass('ac-megamenu-column') && !selected.hasClass('ac-megamenu-submenu')) {

      level = parseInt($(selected).parent().attr('data-level'));
      if(level > 1) {
        $("#toogle-group-wrapper").show();
        $("#toogle-break-column-wrapper").show();
      }
      else {
        $("#toogle-group-wrapper").hide();
        $("#toogle-break-column-wrapper").hide();
      }
    }
    hide_toolbox (false);
    if (selected) currentSelected = selected;

    // Update IconSel attr
    $('.toolitem-xicon').attr('data-id', selected.closest('li').attr('data-id'));
    // remove class open for other
    megamenu.find ('ul[class*="l-"] > li').each (function(){
      if (!$(this).has (currentSelected).length > 0) $(this).removeClass ('open');
      else $(this).addClass ('open');
    });

    // set selected
    megamenu.data('nav_all').removeClass ('selected');
    currentSelected.addClass ('selected');
    var type = toolbox_type ();
    $('#ac-megamenu-admin-mm-tool' + type).show();
    update_toolbox (type);

    $('#ac-megamenu-admin-mm-ac').show();
  }

  update_toolbox = function (type) {
    if (!type) {
      type = toolbox_type ();
    }
    $('#ac-megamenu-admin-mm-ac .disabled').removeClass('disabled');
    $('#ac-megamenu-admin-mm-ac .active').removeClass('active');
    switch (type) {
      case 'item':
        var liitem = currentSelected.closest('li'),
            liparent = liitem.parent().closest('li'),
            sub = liitem.find ('.nav-child:first');

        $('.toolitem-exclass').attr('value', liitem.attr('data-class') || '');
        $('.toolitem-xicon').attr('value', liitem.attr('data-xicon') || '');
        $('.toolitem-caption').attr('value', liitem.attr('data-caption') || '');
        var toggle = $('.toolitem-sub');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (parseInt(liitem.attr('data-group'))) {
          $('.toolitem-sub').addClass ('disabled');
        }
        else if (sub.length == 0 || sub.css('display') == 'none') {
          update_toggle (toggle, 0);
        }
        else {
          update_toggle (toggle, 1);
        }

        var toggle = $('.toolitem-group');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (parseInt(liitem.attr('data-level')) == 1 || sub.length == 0 || parseInt(liitem.attr('data-hidesub')) == 1) {
          $('.toolitem-group').addClass ('disabled');
        }
        else if (parseInt(liitem.attr('data-group'))) {
          update_toggle (toggle, 1);
        }
        else {
          update_toggle (toggle, 0);
        }

        if (!liparent.length || !liparent.hasClass('mega')) {
          $('.toolitem-moveleft, .toolitem-moveright').addClass ('disabled');
        }
        break;

      case 'sub':
        // Upload
        var bg_img = $('.ac-upload img'),
            bg_src = currentSelected.attr('data-src');
        console.log(currentSelected);
        if (typeof bg_src != "undefined" && bg_src !='') {
          $(currentSelected).css('background-image', 'url(' + bg_src + ')');
          bg_img.attr('src', bg_src);
        }else{
          bg_img.attr('src', Drupal.ACMegaMenu.blank_image);
          $(currentSelected).css('background-image', 'none');
        }

        var liitem = currentSelected.closest('li'),
            sub = liitem.find ('.nav-child:first');
        $('.toolsub-exclass').attr('value', currentSelected.attr('data-class') || '');

        var toggle = $('.toolsub-fullPageWidth');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (parseInt(sub.attr('data-fullwidth')) && parseInt(sub.attr('data-fullwidth')) == 1) {
          $('.toolsub-width-wrap').hide ();
          update_toggle (toggle, 1);
          sub.css('width', '100%');
          sub.attr('data-width', '100%');
        }else{
          $('.toolsub-width-wrap').show ();
          sub.attr('data-width', '');
          sub.css('width', 'auto');
          update_toggle (toggle, 0);
        }

        if (parseInt(liitem.attr('data-group'))) {
          $('.toolsub-width').attr('value', '').addClass ('disabled');
          $('.toolitem-alignment').addClass ('disabled');
        }
        else {
          $('.toolsub-width').val(currentSelected.attr('data-width'));
          if (parseInt(liitem.attr('data-level')) > 1) {
            $('.toolsub-align-center').addClass ('disabled');
            $('.toolsub-align-justify').addClass ('disabled');
          }

          if (liitem.attr('data-alignsub')) {
            $('.toolsub-align-'+liitem.attr('data-alignsub')).addClass ('active');
            if (liitem.attr('data-alignsub') == 'justify') {
              $('.toolsub-width').addClass ('disabled');
            }
          }
        }

        var toggle = $('.toolsub-hidewhencollapse');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (parseInt(liitem.attr('data-hidewcol'))) {
          update_toggle (toggle, 1);
        }
        else {
          update_toggle (toggle, 0);
        }
        break;

      case 'col':
        // Upload
        var bg_img = $('.ac-upload img'),
            bg_src = currentSelected.attr('data-src');
        if (typeof bg_src != "undefined" && bg_src !='') {
          $(currentSelected).css('background-image', 'url(' + bg_src + ')');
          bg_img.attr('src', bg_src);
        }else{
          bg_img.attr('src', Drupal.ACMegaMenu.blank_image);
          $(currentSelected).css('background-image', 'none');
        }

        // Extra Class
        $('.toolcol-exclass').attr('value', currentSelected.attr('data-class') || '');

        // Block Column
        $('.toolcol-block').val (currentSelected.children('.mega-inner').children('.ac-megamenu-block').attr('data-block') || '').trigger("liszt:updated");
        $('.toolcol-width').val (currentSelected.attr('data-width') || '').trigger("liszt:updated");
        if (currentSelected.find ('.mega-nav').length > 0) {
          $('.toolcol-block').parent().addClass('disabled');
        }
        if (currentSelected.parent().children().length == 1) {
          $('.toolcol-width').parent().addClass ('disabled');
        }
        // Hide when collapse
        var toggle = $('.toolcol-hidewhencollapse');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (parseInt(currentSelected.attr('data-hidewcol'))) {
          update_toggle (toggle, 1);
        }
        else {
          update_toggle (toggle, 0);
        }

        // Show Block Title
        var toggle = $('.toolcol-showblocktitle');
        toggle.find('label').removeClass('active btn-success btn-danger btn-primary');
        if (!currentSelected.attr('data-showblocktitle') || parseInt(currentSelected.attr('data-showblocktitle'))) {
          update_toggle (toggle, 1);
        }
        else {
          update_toggle (toggle, 0);
        }
        break;
    }
  }

  update_toggle = function (toggle, val) {
    $input = toggle.find('input[value="'+val+'"]');
    $input.attr('checked', 'checked');
    $input.trigger ('update');
  }

  apply_toolbox = function (input) {
    var name = $(input).attr('data-name'),
        value = input.value,
        type = toolbox_type ();
    switch (name) {
      case 'width':
        value = parseInt(value);
        if(isNaN(value)) {
          value = "";
          if (type == 'sub') {
            currentSelected.width(value);
          }
          if (type == 'col') {
            currentSelected.removeClass('span'+currentSelected.attr('data-' + name));
          }
          currentSelected.attr('data-' + name, value);
        }
        else {
          if (type == 'sub') {
            currentSelected.width(value);
          }
          if (type == 'col') {
            currentSelected.removeClass('span'+currentSelected.attr('data-' + name)).addClass ('span'+value);
          }
          currentSelected.attr('data-' + name, value);
        }
        $(input).val(value);
        break;
      case 'duration':
        value = parseInt(value);
        if(isNaN(value)) {
          value = "";
        }
        $(input).val(value);
        break;
      case 'delay':
        value = parseInt(value);
        if(isNaN(value)) {
          value = "";
        }
        $(input).val(value);
        break;
      case 'class':
        if (type == 'item') {
          var item = currentSelected.closest('li');
        } else {
          var item = currentSelected;
        }
        item.removeClass(item.attr('data-' + name) || '').addClass (value);
        item.attr('data-' + name, value);
        break;

      case 'xicon':
        if (type == 'item') {
          currentSelected.closest('li').attr('data-' + name, value);
          currentSelected.find('i').remove();
          if (value) {
            currentSelected.prepend($('<i class="'+value+'"></i>'));
          }
        }
        break;

      case 'caption':
        if (type == 'item') {
          currentSelected.closest('li').attr('data-' + name, value);
          currentSelected.find('span.m-caption').remove();
          if (value) {
            currentSelected.append($('<span class="m-caption">'+value+'</span>'));
          }
        }
        break;

      case 'block':
        if (currentSelected.find ('ul[class*="l-"]').length == 0) {
          if (value) {
            $('#ac-megamenu-admin-mm-ac #toolbox-loading').show();
            callAjax({'action': 'load_block', 'block_key': value, 'id': currentSelected.attr('id'), 'showblocktitle': parseInt(currentSelected.attr('data-showblocktitle'))});
          }
          else {
            currentSelected.find('.mega-inner').html('');
          }
          currentSelected.attr('data-' + name, value);
        }
        break;
    }
  }

  callAjax = function(data) {
    if(Drupal.ACMegaMenu.isLockedAjax()) {
      window.setTimeout(function() {
        callAjax(data);
      }, 200);
      return;
    }
    Drupal.ACMegaMenu.lockAjax();
    switch(data.action) {
      case 'load_block':
        $.ajax({
          type: "POST",
          url: Drupal.settings.basePath + Drupal.ACMegaMenu.ajax_link + Drupal.ACMegaMenu.ajax_URL,
          data: data,
          complete: function( msg ) {
            var resp = $.parseJSON(msg.responseText);
            var content = resp.content ? resp.content : "";
            var close_button = $('<span class="close icon-remove" title="' + Drupal.t("Remove this block") + '">&nbsp;</span>');
            var id = resp.id ? resp.id : "";
            var currentElement = $("#" + id);
            if(currentElement.length) {
              currentElement.children('.mega-inner').html("").append(close_button).append($(content)).find(':input').removeAttr('name');
              currentElement.children('.mega-inner').children('span.close').click(function() {
                $(this).parent().html("");
              });
            }
            $('#ac-megamenu-admin-mm-ac #toolbox-loading').hide();
            Drupal.ACMegaMenu.releaseAjax();
          }
        });
        break;
      case 'load':
        break;
      case '':
        break;
    }
  }

  defaultColumnsWidth = function (count) {
    if (count < 1) {
      return null;
    }
    var total = 12,
        min = Math.floor(total / count),
        widths = [];
    for(var i=0;i<count;i++) {
      widths[i] = min;
    }
    widths[count - 1] = total - min*(count-1);
    return widths;
  }

  bindEvents = function (els) {
    if (megamenu.data('nav_all'))
      megamenu.data('nav_all', megamenu.data('nav_all').add(els));
    else
      megamenu.data('nav_all', els);

    els.mouseover(function(event) {
      megamenu.data('nav_all').removeClass ('hover');
      $this = $(this);
      clearTimeout (megamenu.attr('data-hovertimeout'));
      megamenu.attr('data-hovertimeout', setTimeout("$this.addClass('hover')", 100));
      event.stopPropagation();
    });
    els.mouseout(function(event) {
      clearTimeout (megamenu.attr('data-hovertimeout'));
      $(this).removeClass('hover');
    });

    els.click (function(event){
      show_toolbox ($(this));
      event.stopPropagation();
      return false;
    });
  }

  unbindEvents = function (els) {
    megamenu.data('nav_all', megamenu.data('nav_all').not(els));
    els.unbind('mouseover').unbind('mouseout').unbind('click');
  }

  rebindEvents = function (els) {
    unbindEvents(els);
    bindEvents(els);
  }
}(jQuery);

!function($){
  $.extend(Drupal.ACMegaMenu, {
    prepare: function(){
      var panel = $('#jform_params_mm_type').closest ('.controls');
      panel.append ($('#ac-megamenu-admin').removeClass('hidden'));
      if ($('#jform_params_navigation_type').val() == 'megamenu') {
        setTimeout(function(){
          $('#jform_params_mm_type').trigger('change.less');
        }, 500);
      } else {
        $('#jform_params_navigation_type').bind('change', function(e) {
          if ($(this).val() == 'megamenu'){
            $('#jform_params_mm_type').trigger('change.less');
          }
        });
      }
    },

    ac_megamenu: function(form, ctrlelm, ctrl, rsp){
      $('#ac-megamenu-admin-mm-container').html(rsp).megamenuAdmin().find(':input').removeAttr('name');
    },

    initPanel: function(){
      $('#jform_params_mm_panel').hide();
    },

    initPreSubmit: function(){
      var form = document.adminForm;
      if(!form){
        return false;
      }

      var onsubmit = form.onsubmit;
      form.onsubmit = function(e){
        $('.toolbox-saveConfig').trigger('click');
        if($.isFunction(onsubmit)){
          onsubmit();
        }
      };
    },

    initRadioGroup: function(){
      var ac_megamenu_instance = $('.ac-megamenu-admin');
      ac_megamenu_instance.find('.radio.btn-group label').addClass('btn');
      ac_megamenu_instance.find('.btn-group label').unbind('click').click(function() {
        var label = $(this),
            input = $('#' + label.attr('for'));

        if (!input.attr('checked')){
          label.closest('.btn-group')
              .find('label')
              .removeClass('active btn-success btn-danger btn-primary');

          label.addClass('active ' + (input.val() == '' ? 'btn-primary' : (input.val() == 0 ? 'btn-danger' : 'btn-success')));

          input.attr('checked', true).trigger('change');
        }
      });
      ac_megamenu_instance.find('input[type=radio]').bind('update', function(){
        if(this.checked){
          $(this)
              .closest('.btn-group')
              .find('label').removeClass('active btn-success btn-danger btn-primary')
              .filter('[for="' + this.id + '"]')
              .addClass('active ' + ($(this).val() == '' ? 'btn-primary' : ($(this).val() == 0 ? 'btn-danger' : 'btn-success')));
        }
      });
      ac_megamenu_instance.find('.btn-group input[checked=checked]').each(function(){
        if($(this).val() == ''){
          $('label[for=' + $(this).attr('id') + ']').addClass('active btn-primary');
        } else if($(this).val() == 0){
          $('label[for=' + $(this).attr('id') + ']').addClass('active btn-danger');
        } else {
          $('label[for=' + $(this).attr('id') + ']').addClass('active btn-success');
        }
      });
    }
  });

  $(window).load(function(){
    Drupal.ACMegaMenu.initPanel();
    Drupal.ACMegaMenu.initPreSubmit();
    Drupal.ACMegaMenu.initRadioGroup();
    Drupal.ACMegaMenu.prepare();
  });
}(jQuery);

(function ($) {
  // Make sure our objects are defined.
  var Diamond = Diamond || {};
  Diamond.utils = Diamond.utils || {};
  Diamond.Modal = Diamond.Modal || {};
  Diamond.utils.acMegamenuUpdateFontIcon = function(ajax, response, status){
    modal_open = false;
    if (typeof response.icon != "undefined") {
      var $el = $('li[data-id="'+response.mid+'"]')
          .attr('data-xicon', response.icon).find('>a');
      var $icon = $el.find('.ac-icon');
      if (!$icon.length){
        $el.prepend($('<i class="ac-icon icon-'+response.icon+'"></i>'));
      }else {
        $icon.attr('class', 'ac-icon icon-'+response.icon);
      }
    }
  }
  $(function() {
    Drupal.ajax.prototype.commands.acMegamenuUpdateFontIcon = Diamond.utils.acMegamenuUpdateFontIcon;
  });

  // Clear uploaded image
  jQuery(document).on({
    mouseenter : function() {
      jQuery(this).addClass('ac-hovered');
    },
    mouseleave : function() {
      jQuery(this).removeClass('ac-hovered');
    }
  }, '.ac-upload');

})(jQuery);