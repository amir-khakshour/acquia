/*
 * DiamondComposer > Views > Base View
 *
 * @author Amir Khakshour
 * @copyright 2015 DiamondLayers
 */
(function ( $ ) {
    var db = Diamond.Builder,
        sc = db.shortcodeCollections || {};

    db.Views.Settings = Backbone.View.extend({
        tagName:'div',
        className:'db_bootstrap_modals',
        template:_.template($('#db-element-settings-modal-template').html() || '<div></div>'),
        textarea_html_checksum:'',
        dependent_elements:{},
        mapped_params:{},
        events:{
            'click .db_save_edit_form':'save',
            // 'click .close':'close',
            'hidden':'remove',
            'hide':'askSaveData',
            'shown':'loadContent'
        },
        initialize:function () {
            db.currentModelView = this;
            // Build Modal
            var settings = Drupal.settings.acquiaModalStyle,
                tag = this.model.get('shortcode'),
                tagInfo = _.isObject(db.map[tag]) ? db.map[tag] : [],
                modal = _.isObject(tagInfo.modal) ? tagInfo.modal : [];
            if (modal.modal_size != '' && modal.modal_size != undefined) {
                var fact = acquia_get_modal_size_factor(modal.modal_size);
                settings.modalSize.width = fact.width;
                settings.modalSize.height = fact.height;
            }else{
                settings['modalSize']['width'] = .4;
                settings['modalSize']['height'] = .5;
            }
            settings.modalSaveBtn = true;
            if (!_.isUndefined(db.modal) && _.isObject(db.modal)) {
                db.modal.dismiss();
            }
            db.modal = Diamond.Modal.show(settings);
            this.$el = db.modal.modal;

            var params = _.isObject(db.map[tag]) && _.isArray(db.map[tag].params) ? db.map[tag].params : [];
            _.bindAll(this, 'hookDependent');
            this.mapped_params = {};
            this.dependent_elements = {};
            _.each(params, function (param) {
                this.mapped_params[param.param_name] = param;
            }, this);
        },
        render:function () {
            // Create a drupal ajax object
            var element_settings = {};
            element_settings.url = window.ajaxurl + '/' + this.model.get('shortcode');
            element_settings.progress = { type: 'throbber' },
                settings = db.map[this.model.get('shortcode')];
            ajax = new Drupal.ajax(window.ajaxurl, this, element_settings);
            ajax.submit.element = this.model.get('shortcode');
            ajax.submit.shortcode = this.model.get('params');
            // load nested elements
            if ( !_.isUndefined(settings['nested shortcodes']) && _.isObject(settings['nested shortcodes']) ) {
                var model_ID = this.model.id;
                _.each(settings['nested shortcodes'], function(val, key){
                    var nested = sc.where({parent_id:model_ID});
                    ajax.submit.shortcode[key] = [];
                    _.each(nested, function(model){
                        ajax.submit.shortcode[key].push(model.get('params'));
                    });

                });
            }

            $.ajax(ajax.options);
            this.$content = this.$el.find('.modal-body > div');
            return this;
        },
        initDependency:function () {
            // setup dependencies
            _.each(this.mapped_params, function (param) {
                if (_.isObject(param) && _.isObject(param.dependency) && _.isString(param.dependency.element)) {
                    var $masters = $('[name=' + param.dependency.element + ']', this.$content),
                        $slave = $('[name= ' + param.param_name + ']', this.$content);
                    _.each($masters, function (master) {
                        var $master = $(master),
                            rules = param.dependency;
                        if (!_.isArray(this.dependent_elements[$master.attr('name')])) this.dependent_elements[$master.attr('name')] = [];
                        this.dependent_elements[$master.attr('name')].push($slave);
                        $master.bind('keyup change', this.hookDependent);
                        this.hookDependent({currentTarget:$master}, [$slave]);
                        if (_.isString(rules.callback)) {
                            window[rules.callback].call(this);
                        }
                    }, this);
                }
            }, this);
        },
        hookDependent:function (e, dependent_elements) {
            var $master = $(e.currentTarget),
                master_value,
                is_empty;
            dependent_elements = _.isArray(dependent_elements) ? dependent_elements : this.dependent_elements[$master.attr('name')],
                master_value = $master.is(':checkbox') ? _.map(this.$content.find('[name=' + $(e.currentTarget).attr('name') + ']:checked'),
                    function (element) {
                        return $(element).val();
                    })
                    : $master.val();
            is_empty = $master.is(':checkbox') ? !this.$content.find('[name=' + $master.attr('name') + ']:checked').length
                : !master_value.length;
            if($master.is(':hidden')) {
                _.each(dependent_elements, function($element) {
                    $element.closest('.db-row').hide();
                });
            } else {
                _.each(dependent_elements, function ($element) {
                    var param_name = $element.attr('name'),
                        rules = _.isObject(this.mapped_params[param_name]) && _.isObject(this.mapped_params[param_name].dependency) ? this.mapped_params[param_name].dependency : {},
                        $param_block = $element.closest('.db-row');
                    if (_.isBoolean(rules.not_empty) && rules.not_empty === true && !is_empty) { // Check is not empty show dependent Element.
                        $param_block.show();
                    } else if (_.isBoolean(rules.is_empty) && rules.is_empty === true && is_empty) {
                        $param_block.show();
                    } else if (_.isArray(rules.value) && _.intersection(rules.value, (_.isArray(master_value) ? master_value : [master_value])).length) {
                        $param_block.show();
                    } else {
                        $param_block.hide();
                    }
                    $element.trigger('change');
                }, this);
            }
            return this;
        },
        loadContent:function () {
            $.ajax({
                type:'POST',
                url:window.ajaxurl,
                data:{
                    element:this.model.get('shortcode'),
                    post_id: $('#post_ID').val(),
                    shortcode:this.model.get('params') // TODO: do it on server-side
                },
                context:this
            }).done(function (data) {
                this.$content.html(data);
                var $title = this.$content.find('h2');
                this.$el.find('h3').text($title.text());
                $title.remove();
                this.initDependency();
            });
        },
        save:function (e) {
            if (_.isObject(e)) e.preventDefault();
            var params = this.getParams();
            this.model.save({params:params});
            if(parseInt(Backbone.VERSION)== 0) {
                this.model.trigger('change:params', this.model);
            }
            this.data_saved = true;
            this.close();
            return this;
        },
        getParams: function() {
            var attributes_settings = this.mapped_params,
                params = _.extend({}, this.model.get('params'));
            //_.each(attributes_settings, function (param) {
            //    params[param.param_name] = vc.atts.parse.call(this, param);
            //}, this);
            return params;
        },
        getCurrentParams: function() {
            var attributes_settings = this.mapped_params,
                params = _.extend({}, this.model.get('params'));
            _.each(attributes_settings, function (param) {
                if(_.isUndefined(params[param.param_name])) params[param.param_name] = '';
                if(param.type === "textarea_html") params[param.param_name] = params[param.param_name].replace(/\n/g, '');
            }, this);
            return params;
        },
        show:function () {
            this.render();
            //this.$el.modal('show');
        },
        _killEditor:function () {
            if(!_.isUndefined(window.tinyMCE)) {
                $('textarea.textarea_html', this.$el).each(function () {
                    var id = $(this).attr('id');
                    window.tinyMCE.execCommand("mceRemoveControl", true, id);
                });
            }
        },
        dataNotChanged: function() {
            var current_params = this.getCurrentParams(),
                new_params = this.getParams();
            return _.isEqual(current_params, new_params);
        },
        askSaveData:function () {
            if (this.data_saved || this.dataNotChanged() || confirm(window.i18nLocale.if_close_data_lost)) {
                this._killEditor();
                this.data_saved = true;
                return true;
            }
            return false;
        },
        close:function () {
            db.modal.dismiss()
        }
    });
})( window.jQuery );
