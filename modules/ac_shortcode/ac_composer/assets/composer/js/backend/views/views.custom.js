/*
 * DiamondComposer > Views > Custom
 *
 * @author Amir Khakshour
 * @copyright 2015 DiamondLayers
 */

(function ($) {
    var db = Diamond.Builder,
        Shortcodes = db.shortcodeCollections;
    window.VcRowView = db.Views.Shortcode.extend({
        change_columns_layout: false,
        events: {
            'click > .db-controls .col-delete': 'deleteShortcode',
            'click > .db-controls .set-layout': 'setColumns',
            'click > .db-controls .col-add': 'addElement',
            'click > .db-controls .col-edit': 'editElement',
            'click > .db-controls .col-clone': 'clone',
            'click > .db-controls .col-toggle': 'toggleElement',
            'click > .db-controls .col-move': 'moveElement',
            'click > .db-controls .col-codeview': 'copyToClipboard'
        },
        _convertRowColumns: function (layout) {

            var layout_split = layout.toString().split(/\_/),
                columns = Shortcodes.where({parent_id: this.model.id}),
                new_columns = [],
                new_width = '';
            _.each(layout_split, function (value, i) {
                var column_data = _.map(value.toString().split(''), function (v, i) {
                        return parseInt(v, 10);
                    }),
                    new_column_params, new_column;
                if (column_data.length > 3)
                    new_width = column_data[0] + '' + column_data[1] + '/' + column_data[2] + '' + column_data[3];
                else if (column_data.length > 2)
                    new_width = column_data[0] + '/' + column_data[1] + '' + column_data[2];
                else
                    new_width = column_data[0] + '/' + column_data[1];
                new_column_params = _.extend(!_.isUndefined(columns[i]) ? columns[i].get('params') : {}, {width: new_width}),
                    db.storage.lock();

                // Build a new Column
                new_column = Shortcodes.create({
                    shortcode: (this.model.get('shortcode') === 'ac_row_inner' ? 'ac_col_inner' : 'ac_col'),
                    params: new_column_params,
                    parent_id: this.model.id
                });
                // move all child of previous column to new one
                if (_.isObject(columns[i])) {
                    _.each(Shortcodes.where({parent_id: columns[i].id}), function (shortcode) {
                        db.storage.lock();
                        shortcode.save({parent_id: new_column.id});
                        db.storage.lock();
                        shortcode.trigger('change_parent_id');
                    });
                }

                new_columns.push(new_column);
            }, this);

            // move trimmed columns content to the latest one in the row
            if (layout_split.length < columns.length) {
                _.each(columns.slice(layout_split.length), function (column) {
                    _.each(Shortcodes.where({parent_id: column.id}), function (shortcode) {
                        db.storage.lock();
                        shortcode.save({'parent_id': _.last(new_columns).id});
                        db.storage.lock();
                        shortcode.trigger('change_parent_id');
                    });
                });
            }
            _.each(columns, function (shortcode) {
                db.storage.lock();
                shortcode.destroy();
            }, this);

            this._changeColumnParms();
            this.model.save();

            return false;
        },
        // Update Columns order attributes
        _changeColumnParms: function () {
            var columns = Shortcodes.where({parent_id: this.model.id});
            if (_.isObject(columns)) {
                _.each(columns, function (shortcode, i) {
                    var new_params = shortcode.get('params');
                    if (columns.length == 1) {
                        new_params.first = 'true';
                        new_params.last = 'true';
                    }
                    else if (i == 0) {
                        new_params.first = 'true';
                        delete new_params.last;
                    }
                    else if (i == columns.length - 1) {
                        new_params.last = 'true';
                        delete new_params.first;
                    } else {
                        if (!_.isUndefined(new_params.first)) {
                            delete new_params.first;
                        }
                        if (!_.isUndefined(new_params.last)) {
                            delete new_params.last;
                        }
                    }

                    if (i % 2 == 0) {
                        new_params.odd = 'true';
                        delete new_params.even;
                    } else {
                        new_params.even = 'true';
                        delete new_params.odd;
                    }

                    shortcode.set({params: new_params});

                });
            }
        },
        _getCurrentLayoutString: function () {
            var layouts = [];
            $('> .db-ac-col, > .db-ac-col_inner', this.$content).each(function () {
                var width = $(this).data('width');
                layouts.push(_.isUndefined(width) ? '1/1' : width);
            });
            return layouts.join(' + ');
        },
        setSorting: function () {
            var that = this;
            if (this.$content.find("> [data-sc=ac_col], > [data-sc=ac_col_inner]").length > 1) {
                this.$content.removeClass('db-not-sortable').sortable({
                    forcePlaceholderSize: true,
                    placeholder: "widgets-placeholder-column",
                    tolerance: "pointer",
                    // cursorAt: { left: 10, top : 20 },
                    cursor: "move",
                    //handle: '.controls',
                    items: "> [data-sc=ac_col], > [data-sc=ac_col_inner]", //db-sortablee
                    distance: 0.5,
                    start: function (event, ui) {
                        $('#db-visual').addClass('sorting-started');
                        ui.placeholder.width(ui.item.width());
                    },
                    stop: function (event, ui) {
                        $('#db-visual').removeClass('sorting-started');
                    },
                    update: function () {
                        var $columns = $("> [data-sc=ac_col], > [data-sc=ac_col_inner]", that.$content);
                        $columns.each(function () {
                            var model = $(this).data('model'),
                                index = $(this).index();
                            model.set('order', index);
                            if ($columns.length - 1 > index) db.storage.lock();
                            model.save();
                        });
                    },
                    over: function (event, ui) {
                        ui.placeholder.css({maxWidth: ui.placeholder.parent().width()});
                        ui.placeholder.removeClass('hidden-placeholder');
                        // if (ui.item.hasClass('not-column-inherit') && ui.placeholder.parent().hasClass('not-column-inherit')) {
                        //     ui.placeholder.addClass('hidden-placeholder');
                        // }
                    },
                    beforeStop: function (event, ui) {
                        // if (ui.item.hasClass('not-column-inherit') && ui.placeholder.parent().hasClass('not-column-inherit')) {
                        //     return false;
                        // }
                    }
                });
            } else {
                if (this.$content.hasClass('ui-sortable')) this.$content.sortable('destroy');
                this.$content.addClass('db-not-sortable');
            }
        },
        validateCellsList: function (cells) {

            var return_cells = [],
                split = cells.replace(/\s/g, '').split('+'),
                b;
            var sum = _.reduce(_.map(split, function (c) {
                if (c.match(/^[vc\_]{0,1}span\d{1,2}$/)) {
                    var converted_c = vc_convert_column_span_size(c);
                    if (converted_c === false) return 1000;
                    b = converted_c.split(/\//);
                    return_cells.push(b[0] + '' + b[1]);
                    return 12 * parseInt(b[0], 10) / parseInt(b[1], 10);
                } else if (c.match(/^[1-9]|1[0-2]\/[1-9]|1[0-2]$/)) {
                    b = c.split(/\//);
                    return_cells.push(b[0] + '' + b[1]);
                    return 12 * parseInt(b[0], 10) / parseInt(b[1], 10);
                }
                return 10000;

            }), function (num, memo) {
                memo = memo + num;
                return memo;
            }, 0);
            if (sum !== 12) return false;
            return return_cells.join('_');
        },
        setColumns: function (e) {
            if (_.isObject(e)) e.preventDefault();
            var $button = $(e.currentTarget);
            if ($button.data('cells') === 'custom') {
                var cells = window.prompt(window.i18nLocale.enter_custom_layout, this._getCurrentLayoutString());
                if (_.isString(cells)) {
                    if ((cells = this.validateCellsList(cells)) !== false) {
                        this.change_columns_layout = true;
                        this._convertRowColumns(cells);
                        this.$el.find('> .db-controls .db-active').removeClass('db-active');
                        $button.addClass('db-active');
                    } else {
                        window.alert(window.i18nLocale.wrong_cells_layout);
                    }
                }
                return;
            }
            if ($button.is('.db-active')) return false;

            this.$el.find('> .db-controls .db-active').removeClass('db-active');
            $button.addClass('db-active');
            this.change_columns_layout = true;

            _.defer(function (view, cells) {
                view._convertRowColumns(cells);
            }, this, $button.data('cells'));
        },
        sizeRows: function () {
            var max_height = 35;
            $('> .db-ac-col, > .db-ac-col_inner', this.$content).each(function () {
                var content_height = $(this).find('> .db-visual-sc > .db-column-container').css({minHeight: 0}).height();
                if (content_height > max_height) max_height = content_height;
            }).each(function () {
                $(this).find('> .db-visual-sc > .db-column-container').css({minHeight: max_height});
            });
        },
        ready: function (e) {
            window.VcRowView.__super__.ready.call(this, e);
            return this;
        },
        checkIsEmpty: function () {
            window.VcRowView.__super__.checkIsEmpty.call(this);
            this.setSorting();
        },
        changedContent: function (view) {
            if (this.change_columns_layout) return this;
            var column_layout = [];
            $('> .db-ac-col, > .db-ac-col_inner', this.$content).each(function () {
                var width = $(this).data('width');
                column_layout.push(_.isUndefined(width) ? '11' : width.replace('/', ''));
            });
            this.$el.find('> .db-controls .db-active').removeClass('db-active');
            var $button = this.$el.find('> .db-controls [data-layout=' + vc_get_column_mask(column_layout.join('_')) + ']');
            if ($button.length) {
                $button.addClass('db-active');
            } else {
                this.$el.find('> .db-controls [data-layout=custom]').addClass('db-active');
            }
            this.sizeRows();
            this._changeColumnParms();
        },
        moveElement: function (e) {
            e.preventDefault();
        },
        copyToClipboard: function (e) {
            e.preventDefault();
            var copyModel = this.model;
            copyModel.shortcode = this.model.get('shortcode');
            copyModel.params = this.model.get('params');
            //window.prompt("Copy to clipboard: Ctrl+C, Enter", db.storage.createShortcodeString(copyModel));
            var text = db.storage.createShortcodeString(copyModel);
            var settings = Drupal.settings.acquiaModalStyle;


            settings['modalSize']['width'] = .5;
            settings['modalSize']['height'] = .5;
            db.modal = Diamond.Modal.show(settings);
            var container = $('<textarea></textarea>', {class: 'codeview', id:'codeview'}).text(text).wrap("<div>").parent();
            Diamond.Modal.modal_display(null, {title: i18nLocale.copy_section_shortcodes, output: container.html()});
        }
    });

    window.DiamondBuilderColumnView = db.Views.Shortcode.extend({
        events: {
            'click > .db-controls .col-delete': 'deleteShortcode',
            'click > .db-controls .col-add': 'addElement',
            'click > .db-controls .col-edit': 'editElement',
            'click > .db-controls .col-clone': 'clone',
            'click > .db-controls .col-toggle': 'toggleElement',
            'click > .db-visual-sc > .col-empty': 'addToEmpty'
        },
        initialize: function (options) {
            window.DiamondBuilderColumnView.__super__.initialize.call(this, options);
            _.bindAll(this, 'setDropable', 'dropButton');
        },
        ready: function (e) {
            window.DiamondBuilderColumnView.__super__.ready.call(this, e);
            this.setDropable();
            return this;
        },
        render: function () {
            window.DiamondBuilderColumnView.__super__.render.call(this);
            this.$el.attr('data-width', this.model.get('params').width);
            this.setEmpty();
            return this;
        },
        addToEmpty: function (e) {
            e.preventDefault();
            if ($(e.target).hasClass('col-empty')) this.addElement(e);
        },
        setDropable: function () {
            this.$content.droppable({
                greedy: true,
                accept: (this.model.get('shortcode') == 'ac_col_inner' ? '.dropable_el' : ".dropable_el,.dropable_row"),
                hoverClass: "db_ui-state-active",
                drop: this.dropButton
            });
            return this;
        },
        dropButton: function (event, ui) {
            if (ui.draggable.is('#db-add-new-element')) {
                new db.Views.Block({model: {position_to_add: 'end'}}).show(this);
            } else if (ui.draggable.is('#db-add-new-row')) {
                this.createRow();
            }
        },
        setEmpty: function () {
            this.$el.addClass('db-empty-container');
            this.$content.addClass('col-empty');
        },
        unsetEmpty: function () {
            this.$el.removeClass('db-empty-container');
            this.$content.removeClass('col-empty');
        },
        checkIsEmpty: function () {
            if (Shortcodes.where({parent_id: this.model.id}).length) {
                this.unsetEmpty();
            } else {
                this.setEmpty();
            }
            if (this.model.get('parent_id')) {
                var row_view = db.app.views[this.model.get('parent_id')];
                if (row_view.model.get('shortcode').match(/^vcDiamondBuilderColumnView\_row/)) {
                    row_view.sizeRows();
                }
            }
            window.DiamondBuilderColumnView.__super__.checkIsEmpty.call(this);
        },
        /**
         * Create row
         */
        createRow: function () {
            var row = Shortcodes.create({shortcode: 'ac_row_inner', parent_id: this.model.id});
            Shortcodes.create({shortcode: 'ac_col_inner', params: {width: '1/1'}, parent_id: row.id});
            return row;
        }
    });

    window.VcAccordionView = db.Views.Shortcode.extend({
        adding_new_tab: false,
        events: {
            'click > .db-controls .col-delete': 'deleteShortcode',
            'click > .db-controls .col-add': 'addTab',
            'click > .add-tab': 'addTab',
            'click > .db-controls .col-edit': 'editElement',
            'click > .db-controls .col-clone': 'clone',
        },
        render: function () {
            window.VcAccordionView.__super__.render.call(this);
            var tag = this.model.get('shortcode');
            var add_tab = _.isObject(db.map[tag]) && _.isBoolean(db.map[tag].add_tab) && db.map[tag].add_tab === true;
            if (add_tab) {
                this.createAddTabButton();
            }
            return this;
        },
        changeShortcodeParams: function (model) {
            window.VcAccordionView.__super__.changeShortcodeParams.call(this, model);
            var collapsible = _.isString(this.model.get('params').collapsible) && this.model.get('params').collapsible === 'yes' ? true : false;
            if (this.$content.hasClass('ui-accordion')) {
                this.$content.accordion("option", "collapsible", collapsible);
            }
        },
        createAddTabButton: function () {
            var new_tab_button_id = (+new Date() + '-' + Math.floor(Math.random() * 11));
            this.$add_button = $('<h4 class="section-header add-tab" tabindex="-1"><i class="admin-icon icon-admin-plus"></i><span class="header-inner">' + window.i18nLocale.add_section + '</span></h4>').appendTo(this.$el);
        },
        changedContent: function (view) {
            if (this.$content.hasClass('ui-accordion')) this.$content.accordion('destroy');
            var collapsible = _.isString(this.model.get('params').collapsible) && this.model.get('params').collapsible === 'yes' ? true : false;
            this.$content.accordion({
                header: ".section-header",
                navigation: false,
                autoHeight: true,
                heightStyle: "content",
                collapsible: collapsible,
                active: this.adding_new_tab === false && view.model.get('cloned') !== true ? 0 : view.$el.index()
            });
            this.adding_new_tab = false;
        },
        addTab: function (e) {
            this.adding_new_tab = true;
            e.preventDefault();
            db.shortcodeCollections.create({
                shortcode: 'ac_accordion_tab',
                params: {title: window.i18nLocale.section},
                parent_id: this.model.id
            });
        },
        _loadDefaults: function () {
            window.VcAccordionView.__super__._loadDefaults.call(this);
        }
    });

    window.VcAccordionTabView = window.DiamondBuilderColumnView.extend({
        events: {
            'click > .db-visual-sc> .section-body> .db-controls .col-delete': 'deleteShortcode',
            'click > .db-visual-sc> .section-body> .db-controls .col-add': 'addElement',
            'click > .db-visual-sc> .section-body> .db-controls .col-edit': 'editElement',
            'click > .db-visual-sc> .section-body> .db-controls .col-clone': 'clone',
            'click > .db-visual-sc> .section-body> .db-controls .col-toggle': 'toggleElement',
            'click > .db-visual-sc> .section-body> .col-empty': 'addToEmpty'
        },
        setContent: function () {
            this.$content = this.$el.find('> .db-visual-sc > .section-body >.db-accordion-content');
        },
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcAccordionTabView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params) && _.isString(params.title)) {
                this.$el.find('>.db-visual-sc >.section-header> .header-inner').text(params.title);
            }
        },
        setEmpty: function () {
            $(this.$el).addClass('db-empty-container');
            this.$content.addClass('col-empty');
        },
        unsetEmpty: function () {
            $('> [data-sc]', this.$el).removeClass('db-empty-container');
            this.$content.removeClass('col-empty');
        },
        editElement: function (e) {
            if (_.isObject(e)) e.preventDefault();
            var parent = Shortcodes.where({id: this.model.get('parent_id')});
            parentParams = parent[0].get('params'),
                newParams = this.model.get('params');

            newParams.sorting = !_.isUndefined(parentParams.sorting) ? parentParams.sorting : false;
            this.model.set('params', newParams);
            window.VcAccordionTabView.__super__.editElement.call(this);
        }
    });

    window.VcMessageView = db.Views.Shortcode.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcMessageView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params) && _.isString(params.type)) {
                this.$el.find('> .db-visual-sc').removeClass(_.values(this.params.type.value).join(' ')).addClass(params.type);
            }
        }
    });

    window.VcTextSeparatorView = db.Views.Shortcode.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcTextSeparatorView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params) && _.isString(params.title_align)) {
                this.$el.find('> .db-visual-sc').removeClass(_.values(this.params.title_align.value).join(' ')).addClass(params.title_align);
            }
        }
    });

    window.VcCallToActionView = db.Views.Shortcode.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcCallToActionView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params) && _.isString(params.position)) {
                this.$el.find('> .db-visual-sc').removeClass(_.values(this.params.position.value).join(' ')).addClass(params.position);
            }
        }
    });

    window.VcToggleView = db.Views.Shortcode.extend({
        events: function () {
            return _.extend({
                'click .toggle_title': 'toggle'
            }, window.VcToggleView.__super__.events);
        },
        toggle: function (e) {
            e.preventDefault();
            $(e.currentTarget).toggleClass('toggle_title_active');
            $('.toggle_content', this.$el).toggle();
        },
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcToggleView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params) && _.isString(params.open) && params.open === 'true') {
                $('.toggle_title', this.$el).addClass('toggle_title_active').next().show();
            }
        }
    });

    window.VcButtonView = db.Views.Shortcode.extend({
        events: function () {
            return _.extend({
                'click button': 'buttonClick'
            }, window.VcToggleView.__super__.events);
        },
        buttonClick: function (e) {
            e.preventDefault();
        },
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            window.VcButtonView.__super__.changeShortcodeParams.call(this, model);
            if (_.isObject(params)) {
                var el_class = params.color + ' ' + params.size + ' ' + params.icon;
                this.$el.find('.db-visual-sc').removeClass(el_class);
                this.$el.find('button.title').attr({"class": "title textfield db_button " + el_class});
                if (params.icon !== 'none' && this.$el.find('button i.icon').length === 0) {
                    this.$el.find('button.title').append('<i class="icon"></i>');
                } else {
                    this.$el.find('button.title i.icon').remove();
                }
            }
        }
    });

    window.VcTabsView = db.Views.Shortcode.extend({
        new_tab_adding: false,
        events: {
            'click .add_tab': 'addTab',
            'click > .db-controls .col-delete': 'deleteShortcode',
            'click > .db-controls .col-edit': 'editElement',
            'click > .db-controls .col-toggle': 'toggleElement',
            'click > .db-controls .col-clone': 'clone',
        },
        initialize: function (params) {
            window.VcTabsView.__super__.initialize.call(this, params);
            _.bindAll(this, 'stopSorting');
        },
        render: function () {
            window.VcTabsView.__super__.render.call(this);
            this.$tabs = this.$el.find('>.db-visual-sc');
            this.$tabs_nav = this.$el.find('>.db-visual-sc >.ui-tabs-nav');
            this.createAddTabButton();
            return this;
        },
        ready: function (e) {
            window.VcTabsView.__super__.ready.call(this, e);
        },
        createAddTabButton: function () {
            var new_tab_button_id = (+new Date() + '-' + Math.floor(Math.random() * 11));
            this.$add_button = $('<li class="add_tab_block"><a href="#new-tab-' + new_tab_button_id + '" class="add_tab" title="' + window.i18nLocale.add_tab + '"><i class="admin-icon icon-admin-plus"></i></a></li>')
                .appendTo(this.$tabs_nav);
            this.$add_button.find('a').click(function (e) {
                this.addTab(e);
            }, this);
        },
        addTab: function (e) {
            e.preventDefault();
            this.new_tab_adding = true;
            var tab_title = this.model.get('shortcode') === 'ac_tour' ? window.i18nLocale.slide : window.i18nLocale.tab,
                tabs_count = this.$tabs.find('[data-sc=ac_tab]').length,
                tab_id = (+new Date() + '-' + tabs_count + '-' + Math.floor(Math.random() * 11));
            db.shortcodeCollections.create({
                shortcode: 'ac_tab',
                params: {title: tab_title, tab_id: tab_id},
                parent_id: this.model.id
            });
            return false;
        },
        stopSorting: function (event, ui) {
            var shortcode;
            this.$tabs.find('ul.tabs_controls li:not(.add_tab_block)').each(function (index) {
                var href = $(this).find('a').attr('href').replace("#", "");
                // $('#' + href).appendTo(this.$tabs);
                shortcode = db.shortcodeCollections.get($($('a', this).attr('href')).data('mid'));
                db.storage.lock();
                shortcode.save({'order': $(this).index()}); // Optimize
            });
            shortcode.save();
        },
        changedContent: function (view) {
            var params = view.model.get('params');
            if (!this.$tabs.hasClass('ui-tabs')) {
                this.$tabs.tabs({
                    select: function (event, ui) {
                        return !$(ui.tab).hasClass('add_tab');
                    }
                });
                this.$tabs.find(".ui-tabs-nav").sortable({
                    axis: (this.$tabs.closest('[data-sc]').data('sc') == 'ac_tour' ? 'y' : 'x'),
                    update: this.stopSorting,
                    items: "> li:not(.add_tab_block)"
                });
            }
            if (view.model.get('cloned') === true) {
                var cloned_from = view.model.get('cloned_from'),
                    $tab_controls = this.$tabs_nav.find('.add_tab_block'),
                    $new_tab = $("<li><a href='#tab-" + params.tab_id + "'>" + params.title + "</a></li>").insertBefore($tab_controls);
                this.$tabs.tabs('refresh');
                this.$tabs.tabs("option", 'active', $new_tab.index());
            } else {
                $("<li><a href='#tab-" + params.tab_id + "'>" + params.title + "</a></li>")
                    .insertBefore(this.$add_button);
                this.$tabs.tabs('refresh');
                this.$tabs.tabs("option",
                    "active",
                    this.new_tab_adding ? $('.ui-tabs-nav li', this.$content).length - 2 : 0);

            }
        },
        cloneModel: function (model, parent_id, save_order) {
            var shortcodes_to_resort = [],
                new_order = _.isBoolean(save_order) && save_order === true ? model.get('order') : parseFloat(model.get('order')) + db.clone_index,
                model_clone,
                new_params = _.extend({}, model.get('params'));
            if (model.get('shortcode') === 'ac_tab') _.extend(new_params, {tab_id: +new Date() + '-' + this.$tabs.find('[data-element-type=ac_tab]').length + '-' + Math.floor(Math.random() * 11)});
            model_clone = Shortcodes.create({
                shortcode: model.get('shortcode'),
                id: db.Utils.guid(),
                parent_id: parent_id,
                order: new_order,
                cloned: (model.get('shortcode') === 'ac_tab' ? false : true),
                cloned_from: model.toJSON(),
                params: new_params
            });
            _.each(Shortcodes.where({parent_id: model.id}), function (shortcode) {
                this.cloneModel(shortcode, model_clone.get('id'), true);
            }, this);
            return model_clone;
        }
    });

    window.VcTabView = window.DiamondBuilderColumnView.extend({
        render: function () {
            var params = this.model.get('params');
            this.id = 'tab-' + params.tab_id;
            this.$el.attr('id', this.id);
            this.$tabs = this.$el.closest('.db-ac-tabs');
            this.$tabs_nav = this.$el.closest('.db-ac-tabs').find('>.db-visual-sc >.ui-tabs-nav');
            $('<li></li>', {class: 'ui-tab'}).appendTo(this.$tabs_nav).append($('<a></a>', {href: "#" + this.id}));
            window.VcTabView.__super__.render.call(this);
            return this;
        },
        changeShortcodeParams: function (model) {
            window.VcAccordionTabView.__super__.changeShortcodeParams.call(this, model);
            var params = model.get('params');
            this.$tabs_nav = this.$el.closest('.db-ac-tabs').find('>.db-visual-sc >.ui-tabs-nav');
            if (_.isObject(params) && _.isString(params.tab_id)) {
                if (_.isString(params.title)) {
                    this.$tabs_nav.find('[href=#tab-' + params.tab_id + ']').text(params.title);
                }
                // @TODO add icons after to tab
            }
        },
        deleteShortcode: function (e) {
            if (_.isObject(e)) e.preventDefault();
            var answer = confirm(window.i18nLocale.press_ok_to_delete_section);
            if (answer !== true) return false;
            this.model.destroy();
            var params = this.model.get('params'),
                current_tab_index = $('[href=#tab-' + params.tab_id + ']', this.$tabs).parent().index();
            $('[href=#tab-' + params.tab_id + ']').parent().remove();
            this.activeTab = current_tab_index - 1;
            this.$tabs.tabs("setActive", this.activeTab);
            var tab_length = this.$tabs.find('.ui-tabs-nav li:not(.add_tab_block)').length;
            if (current_tab_index < tab_length) {
                this.$tabs.tabs("option", "active", current_tab_index);
            } else if (tab_length > 0) {
                this.$tabs.tabs("option", "active", tab_length - 1);
            }
        },
        cloneModel: function (model, parent_id, save_order) {
            console.log("Changed from Child");

            var shortcodes_to_resort = [],
                new_order = _.isBoolean(save_order) && save_order === true ? model.get('order') : parseFloat(model.get('order')) + db.clone_index,
                new_params = _.extend({}, model.get('params'));
            if (model.get('shortcode') === 'ac_tab')
                _.extend(new_params, {tab_id: +new Date() + '-' + this.$tabs.find('[data-sc=ac_tab]').length + '-' + Math.floor(Math.random() * 11)});

            var model_clone = Shortcodes.create({
                shortcode: model.get('shortcode'),
                parent_id: parent_id,
                order: new_order,
                cloned: true,
                cloned_from: model.toJSON(),
                params: new_params
            });
            //_.each(Shortcodes.where({parent_id: model.id}), function (shortcode) {
            //    this.cloneModel(shortcode, model_clone.id, true);
            //}, this);
            return model_clone;
        }
    });

    window.AcItemsList = window.VcAccordionView.extend({
        events: {
            'click > .db-controls .col-delete': 'deleteShortcode',
            'click > .db-controls .col-add': 'addTab',
            'click > .db-controls .col-edit': 'editElement',
            'click > .db-controls .col-clone': 'clone',
            'click > .db-controls .col-toggle': 'toggleElement',
            'click > .db-visual-sc > .col-empty': 'addToEmpty'
        },
        render: function () {
            window.VcAccordionView.__super__.render.call(this);
            this.$content.sortable({
                axis: "y",
                items: "> .db-sortable",
                start:function () {
                },
                stop: function (event, ui) {
                    // IE doesn't register the blur when sorting
                    // so trigger focusout handlers to remove .ui-state-focus
                    ui.item.prev().triggerHandler("focusout");
                    $(this).find('> .db-sortable').each(function () {
                        var shortcode = $(this).data('model');
                        shortcode.save({'order': $(this).index()}); // Optimize
                    });
                }
            });
            return this;
        },
        addTab: function (e) {
            e.preventDefault();
            settings = db.map[this.model.get('shortcode')];
            var cloneTag = !_.isUndefined(settings['clone_tag']) ? settings['clone_tag'] : this.model.get('shortcode');
            this.adding_new_tab = true;
            db.shortcodeCollections.create({
                shortcode: cloneTag,
                params: {title: window.i18nLocale.title},
                parent_id: this.model.id,
                position_to_add:!_.isObject(e) || !$(e.currentTarget).closest('.bottom-controls').hasClass('bottom-controls') ? 'start' : 'end'
            });
        },
    });

    /** Custom DiamondLayers Shortcode View **/
    window.DiamondBuilderShortcodeView = db.Views.Shortcode.extend({
        editElement: function (e) {
            if (_.isObject(e)) e.preventDefault();
            var params = this.model.get('params'),
                settings = db.map[this.model.get('shortcode')];
            // process nested shortcodes
            if (!_.isUndefined(settings['nested shortcodes']) && !_.isUndefined(params.content) && _.isObject(settings['nested shortcodes'])) {
                var model_ID = this.model.id;
                Shortcodes.createFromString(params.content, this.model);
                //delete params.content;
            }
            window.DiamondBuilderShortcodeView.__super__.editElement.call(this);
        },
        changeShortcodeParams: function (model) {
            var params = model.get('params'),
                settings = db.map[model.get('shortcode')],
                visual_updates = this.$el.find("[data-update_with]"),
                class_updates = this.$el.find("[data-update_class_with]").attr('class', ''),
                visual_el = "",
                visual_template = "",
                replace_val = "";

            if (!_.isUndefined(model.get('visual_params'))) {
                var params = $.extend({}, params, model.get('visual_params'));
            }
            // process nested shortcodes
            if (!_.isUndefined(settings['nested shortcodes']) && _.isObject(settings['nested shortcodes'])) {
                var model_ID = this.model.id;

                _.each(Shortcodes.where({parent_id: model_ID}), function (shortcode) {
                    db.storage.lock();
                    shortcode.destroy();
                }, this);

                _.each(settings['nested shortcodes'], function (val, key) {
                    if (params[key] != "undefined") {
                        _.each(params[key], function (n_params) {
                            // Build a new Column
                            Shortcodes.create({shortcode: val, id: db.Utils.guid(), params: n_params, parent_id: model_ID});
                        });
                        delete params[key];
                    }
                });
            }
            visual_updates.each(function () {
                var visual_el = $(this),
                    visual_template = visual_el.attr('data-update_template'),
                    visual_keys = visual_el.attr('data-update_with').split(','),
                    update_html = '';

                _.each(visual_keys, function (visual_key) {
                    if (_.isUndefined(params[visual_key])) {
                        return;
                    }
                    if (typeof params[visual_key] === "string" || typeof params[visual_key] === "number") {
                        replace_val = params[visual_key];
                        //apply autop to content
                        if (visual_key === "content") {
                            //if visual editor is disabled convert newlines to br for the canvas preview
                            replace_val = params[visual_key];
                        }

                        //check for a template
                        if (visual_template) {
                            update_html = visual_template.replace(new RegExp("{{" + visual_key + "}}", 'g'), replace_val);
                            visual_template = update_html;
                        }
                        else {
                            update_html = replace_val;
                        }
                    }
                    //update all elements
                    visual_el.html(update_html);
                });
            });
            class_updates.each(function () {
                visual_el = $(this);
                visual_key = visual_el.data('update_class_with').split(',');
                for (var i = 0; i < visual_key.length; i++) {
                    if (typeof params[visual_key[i]] === "string") {
                        visual_el.get(0).className += ' ac-' + visual_key[i] + '-' + params[visual_key[i]];
                    }
                }
            });
            window.DiamondBuilderShortcodeView.__super__.changeShortcodeParams.call(this, model);
        },
    });

    /** Image Shortcode Composer View **/
    window.DiamondBuilderImageView = window.DiamondBuilderShortcodeView.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params'),
                that = this,
                tag = this.model.get('shortcode'),
                style = _.isObject(db.map[tag]) && _.isObject(db.map[tag].visual_values) && _.isString(db.map[tag].visual_values.style) ? db.map[tag].visual_values.style : false;
            if (!_.isUndefined(params.fid) && params.fid !=0) {
                var data = {
                    action: 'db_get_img_src',
                    fid: params.fid
                };
                if (style) {
                    data['style'] = style;
                }
                else if (!_.isUndefined(params.style)) {
                    data['style'] = params.style;
                }
                $.ajax({
                    type: 'POST',
                    url: window.ajaxurl,
                    data: data,
                    dataType: 'html',
                    context: this
                }).done(function (src) {
                    model.set('visual_params', {'src': src});
                    this.$el.removeClass('default-params').addClass('custom-params');
                    window.DiamondBuilderImageView.__super__.changeShortcodeParams.call(that, model);
                });

            } else{
                window.DiamondBuilderImageView.__super__.changeShortcodeParams.call(that, model);
            }
        },
    });

    /** Image Shortcode Composer View **/
    window.dbBase64EncodedView = window.DiamondBuilderShortcodeView.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            var content = Diamond.Builder.Utils.decode64(params.content);
            model.set('visual_params', {'content': content});
            window.dbBase64EncodedView.__super__.changeShortcodeParams.call(this, model);
        },
    });

    // Icon list item composer view
    window.acIconView = window.DiamondBuilderShortcodeView.extend({
        changeShortcodeParams: function (model) {
            var params = model.get('params');
            if (!_.isUndefined(params.icon)) {
                this.$el.removeClass('default-params').addClass('custom-params');
            }
            window.acIconView.__super__.changeShortcodeParams.call(this, model);
        },
    });

    window.AcprogressbarItemView = window.DiamondBuilderShortcodeView.extend({
        editElement: function (e) {
            if (_.isObject(e)) e.preventDefault();
            var parent = Shortcodes.where({id: this.model.get('parent_id')});
            parentParams = parent[0].get('params'),
                newParams = this.model.get('params');

            newParams.style = !_.isUndefined(parentParams.style) ? parentParams.style : false;
            this.model.set('params', newParams);

            window.AcprogressbarItemView.__super__.editElement.call(this);
        },
    });

})(window.jQuery);