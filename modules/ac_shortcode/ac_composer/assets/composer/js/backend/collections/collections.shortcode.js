/*
 * DiamondComposer > Collections > Shortcode
 *
 * @author Amir Khakshour
 * @copyright 2015 DiamondLayers
 */
(function ($) {
    var store = Diamond.Builder.storage;
    /**
     * Collection of shortcodes.
     * Extended Backbone.Collection object.
     * This collection can be used for root(raw) shortcodes list and inside another shortcodes list as inner shortcodes.
     * @type {*}
     */
    Diamond.Builder.Collections.Shortcodes = Backbone.Collection.extend({
        model: Diamond.Builder.Models.Shortcode,
        last_index: 0,
        getNextOrder:function () {
            return this.last_index++;
        },
        comparator:function (model) {
            return model.get('order');
        },
        initialize:function () {
            // this.on('add', this.checkUpdateOrder, this);
        },
        /**
         * Updates order of other models if new one has not last order value.
         */
        checkUpdateOrder:function (model) {
            var model_order = model.get('order');
            if (model_order < this.length) {
                _.each(this.filter(function (shortcode) {
                    return model.id != shortcode.id && model.get('parent_id') === shortcode.get('parent_id') && shortcode.get('order') >= model_order;
                }), function (shortcode) {
                    shortcode.save({order:shortcode.get('order') + 1});
                });
            }
        },
        /**
         * Create new models from shortcode string.
         * @param shortcodes_string - string of shortcodes.
         * @param parent_model - parent shortcode model for parsed objects from string.
         */
        createFromString:function (shortcodes_string, parent_model) {
            var data = Diamond.Builder.storage.parseContent({}, shortcodes_string, _.isObject(parent_model) ? parent_model.toJSON() : false);
            _.each(_.values(data), function (model) {
                Diamond.Builder.shortcodeCollections.create(model);
            }, this);
        },
        /**
         * Synchronize data with our storage.
         * @param method
         * @param model
         * @param options
         */
        sync:function (method, model, options) {
            var resp;
            // Select action to do with data in you storage
            switch (method) {
                case "read":
                    resp = model.id ? store.find(model) : store.findAll();
                    break;
                case "create":
                    resp = store.create(model);
                    break;
                case "update":
                    resp = store.update(model);
                    break;
                case "delete":
                    resp = store.destroy(model);
                    break;
            }
            // Response
            if (resp) {
                options.success(resp);

            } else {
                options.error("Record not found");
            }
        }
    });
    // A Collection of Shortcodes
    Diamond.Builder.shortcodeCollections = new Diamond.Builder.Collections.Shortcodes();
})(window.jQuery);
