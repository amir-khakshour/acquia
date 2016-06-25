/* =========================================================
 * composer-storage.js 1
 * =========================================================
 * Copyright 2013 dbakery
 *
 * Visual composer backbone/underscore Storage hidden field
 * ========================================================= */
(function ($) {
    var db = Diamond.Builder;

    /**
     * @constructor
     */
    var Storage = function () {
        // Storage for our models
        this.data = {};
    };
    /**
     * CRUD methods for content management.
     * @type {Object}
     */
    Storage.prototype = {
        url:window.ajaxurl,
        checksum:false,
        locked:false,
        /**
         * Create new object in storage. Require to define model name because system uses only one hidden field with
         * serialized JSON object.
         * @param model - Backbone.Model object
         * @return {*} - Backbone.Model object
         */
        create:function (model) {
            if (!model.id)
                model.id = model.attributes.id = db.Utils.guid();
            this.data[model.id] = model.toJSON();
            // optimize root update
            this.setModelRoot(model.id);
            this.save();
            return model;
        },
        /**
         * Optimization methods
         */
        // {{ Methods allows lock/unlock data parsing into Shortcodes and saving it in editor.
        lock:function () {
            this.locked = true;
        },
        unlock:function () {
            this.locked = false;
        },
        // }}
        /**
         * Set Root for model with given id
         * @param model id
         * @return void
         */
        setModelRoot:function (id) {
            var data = this.data[id];
            if (_.isString(data.parent_id) && _.isObject(this.data[data.parent_id])) {
                data.root_id = this.data[data.parent_id].root_id;
            }
            if (_.isObject(this.data[data.root_id]))
                this.data[data.root_id].html = false;
        },
        /**
         * Update object in storage.
         * @param model
         * @return {*}
         */
        update:function (model) {
            this.data[model.id] = model.toJSON();

            this.setModelRoot(model.id);
            this.save();
            return model;
        },
        /**
         * Remove record from storage
         * @param model
         * @return {*}
         */
        destroy:function (model) {
            if (!_.isUndefined(this.data[model.id]) && !_.isUndefined(this.data[model.id].root_id) && _.isObject(this.data[this.data[model.id].root_id])) {
                this.data[this.data[model.id].root_id].html = false;
            }
            if (!_.isUndefined(this.data[model.id])) {
                delete this.data[model.id];
            }
            this.save();
            return model;
        },
        /**
         * Find record by id
         * @param model_id - id of model.
         * @return {*} - object
         */
        find:function (model_id) {
            return this.data[model_id];
        },
        /**
         * Find all records in storage. Used by fetch.
         * @return {*}
         */
        findAll:function () {
            this.fetch();
            return _.values(this.data);
        },
        /**
         * Find all root models which are sorted by order field.
         * We set parent_id === false for those Models
         * @return {*}
         */
        findAllRootSorted:function () {
            var models = _.filter(_.values(this.data), function (model) {
                return model.parent_id === false;
            });
            return _.sortBy(models, function (model) {
                return model.order;
            });
        },
        /***
         * Escape double quotes in params value.
         * @param value
         * @return {*}
         */
        escapeParam:function (value) {
            if (_.isString(value)) {
                return value.replace(/"/g, '``');
            }
        },
        /**
         * Unescape double quotes in params valus.
         * @param value
         * @return {*}
         */
        unescapeParam:function (value) {
            return value.replace(/(\`{2})/g, '"');
        },
        /**
         * Converts model data to wordpress shortcode.
         * @param model
         * @return {*}
         */
        createShortcodeString:function (model) {
            var params = model.params,
                params_to_string = {};

            _.each(params, function (value, key) {
                if (key !== 'content' && !_.isEmpty(value)) params_to_string[key] = this.escapeParam(value);
            }, this);
            var content = this.getModelContent(model),
                is_container = _.isObject(db.map[model.shortcode]) && _.isBoolean(db.map[model.shortcode].is_container) && db.map[model.shortcode].is_container === true;
            return wp.shortcode.string({
                tag:model.shortcode,
                attrs:params_to_string,
                content:content,
            });
        },
        /**
         * Save data in hidden field.
         * @return {Boolean}
         */
        save:function () {
            if (this.locked) {
                this.locked = false;
                return false;
            }
            var content = _.reduce(this.findAllRootSorted(), function (memo, model) {
                // if(!_.isString(model.html)) {
                model.html = this.createShortcodeString(model);
                // }
                return memo + model.html;
            }, '', this);
            // new change = content = window.nl2br(content);
            this.setContent(content);
            this.checksum = window.md5(content);
            return this;
        },
        /**
         * If shortcode is container like, gets content of is shortcode in shortcodes style.
         * @param parent - shortcode inside which content is.
         * @return {*}
         * @private
         */
        getModelContent:function (parent) {

            var that = this,
                models = _.sortBy(_.filter(this.data, function (model) {
                    // Filter children
                    return model.parent_id === parent.id;
                }), function (model) {
                    // Sort by `order` field
                    return model.order;
                }),
                params = parent.params;

            if (!models.length) {
                if(_.isString(params.content)) {
                    //params.content = window.nl2br(params.content);
                }
                return _.isUndefined(params.content) ? '' : params.content;
            }
            return _.reduce(models, function (memo, model) {
                return memo + that.createShortcodeString(model);
            }, '');
        },
        /**
         * Get content of main editor of current post. Data is used as models collection of shortcodes.
         * @return {*}
         */
        getContent:function () {
            var content,
                mce = undefined,
                mceID = db.mceID;

            if (typeof mceID != "undefined" && typeof tinyMCE != "undefined") {
                mce = tinyMCE.editors[mceID];
                mce = _.isObject(mce) ? mce : tinymce.activeEditor;
            }

            if (typeof mce != 'undefined') {
                // window.switchEditors.go('content', 'html');
                //mce.content.save();
                content = mce.getContent(content);
            }else {
                content = $('#'+mceID).val();
            }
            return content;
        },
        /**
         * Set content of the current_post inside editor.
         * @param content
         * @private
         */
        setContent:function (content) {
            // @TODO move to helpers api
            var mce = undefined,
                mceID = db.mceID;

            if (typeof mceID != "undefined" && typeof tinyMCE != "undefined") {
                mce = tinyMCE.editors[mceID];
                mce = _.isObject(mce) ? mce : tinymce.activeEditor;
            }

            if (typeof mce != 'undefined') {
                mce.setContent(content);
            }else{
                $('#'+mceID).val(content);
            }
        },
        /**
         * Parse shortcode string into objects.
         * @param data
         * @param content
         * @param parent
         * @return {*}
         */
        parseContent:function (data, content, parent) {
            var tags = _.keys(db.map).join('|'),
                reg = window.wp.shortcode.regexp(tags),
                matches = content.trim().match(reg);
            if (_.isNull(matches)) return data;

            _.each(matches, function (raw) {
                var sub_matches = raw.match(this.regexp(tags)),
                    sub_content = sub_matches[5],
                    sub_regexp = new RegExp('^[\\s]*\\[\\[?(' + _.keys(db.map).join('|') + ')(?![\\w-])'),
                    id = db.Utils.guid(),
                    atts_raw = window.wp.shortcode.attrs(sub_matches[3]),
                    atts = {},
                    shortcode,
                    map_settings;

                _.each(atts_raw.named, function (value, key) {
                    atts[key] = this.unescapeParam(value);
                }, this);
                shortcode = {
                    id:id,
                    shortcode:sub_matches[2],
                    order:this.order,
                    params:_.extend({}, atts),
                    parent_id:(_.isObject(parent) ? parent.id : false),
                    root_id:(_.isObject(parent) ? parent.root_id : id)
                };
                map_settings = db.map[shortcode.shortcode];
                this.order += 1;
                data[id] = shortcode;
                if (id == shortcode.root_id) {
                    data[id].html = raw;
                }

                if (_.isString(sub_content) && sub_content.match(sub_regexp) &&
                    (
                        (_.isBoolean(map_settings.is_container) && map_settings.is_container === true) ||
                        (!_.isUndefined(map_settings.as_parent) && map_settings.as_parent !== false)
                    )) {

                    data = this.parseContent(data, sub_content, data[id]);
                } else if (_.isString(sub_content)) {
                    data[id].params.content = sub_content; // sub_content.match(/\n/) && !_.isUndefined(window.switchEditors) ? window.switchEditors.wpautop(sub_content) : sub_content;
                }
            }, this);

            return data;
        },
        /**
         * Checks by checksum is content changed.
         * @return {Boolean}
         */
        isContentChanged:function () {
            return this.checksum === false || this.checksum !== window.md5(this.getContent());
        },
        /**
         * Wrap content which is not inside vc shorcodes.
         * @param content
         * @return {*}
         */
        wrapData:function (content) {
            var tags = _.keys(db.map).join('|'),
                reg = this.regexp_split('ac_row'),
                starts_with_shortcode = new RegExp('^\\[(\\[?)' + tags, 'g'); //'^\\[(\\[?)\s*'
            matches = _.filter(content.trim().split(reg), function (value) {
                if (!_.isEmpty(value)) return value;
            });
            content = _.reduce(matches, function (mem, value) {
                if (!value.trim().match(starts_with_shortcode)) {
                    value = '[ac_row][ac_col][ac_col_text]' + value + '[/ac_col_text][/ac_col][/ac_row]';
                }
                return mem + value;
            }, '');
            return content;
        },
        /**
         * Get data from hidden field and parse it from string to objects list.
         * @return {*}
         */
        fetch:function () {
            if (!this.isContentChanged()) return this;
            this.order = 0;
            var content = this.getContent();

            this.checksum = window.md5(content);
            content = this.wrapData(content);
            this.data = this.parseContent({}, content);
            try {

            } catch (e) {
                this.data = {};
            }
        },
        /**
         * Append new data to existing one.
         * @param content - string of shortcodes.
         */
        append:function (content) {
            this.data = {};
            this.order = 0;
            try {
                var current_content = this.getContent();
                this.setContent(current_content + "" + content);
            } catch (e) {
            }
        },
        /**
         * Regexp used to split unwrapped data.
         */
        regexp_split:_.memoize(function (tags) {
            return new RegExp('(\\[(\\[?)[' + tags + ']+' +
                '(?![\\w-])' +
                '[^\\]\\/]*' +
                '[\\/' +
                '(?!\\])' +
                '[^\\]\\/]*' +
                ']?' +
                '(?:' +
                '\\/]' +
                '\\]|\\]' +
                '(?:' +
                '[^\\[]*' +
                '(?:\\[' +
                '(?!\\/' + tags + '\\])[^\\[]*' +
                ')*' +
                '' +
                '\\[\\/' + tags + '\\]' +
                ')?' +
                ')' +
                '\\]?)', 'g');
        }),
        regexp:_.memoize(function (tags) {
            return new RegExp('\\[(\\[?)(' + tags + ')(?![\\w-])([^\\]\\/]*(?:\\/(?!\\])[^\\]\\/]*)*?)(?:(\\/)\\]|\\](?:([^\\[]*(?:\\[(?!\\/\\2\\])[^\\[]*)*)(\\[\\/\\2\\]))?)(\\]?)');

        })
    };
    db.storage = new Storage();
})(window.jQuery);