/*
 * DiamondComposer > Models > Shortcode
 *
 * @author Amir Khakshour
 * @copyright 2015 DiamondLayers
 */
(function ($) {
    var db = Diamond.Builder,
        store = db.storage;

    db.Models.Shortcode = Backbone.Model.extend({
        defaults:function () {
            var id = db.Utils.guid();
            return {
                id:id,
                shortcode:'ac_text_block',
                order: db.shortcodeCollections.getNextOrder(),
                params:{},
                parent_id:false,
                root_id:id,
                cloned:false,
                html:false,
                view: false,
            };
        },
        initialize:function () {
            this.bind('remove', this.removeChildren, this);
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
        },
        /**
         * Remove all children of model from storage.
         * Will remove children of children models too.
         * @param parent - model which is parent
         */
        removeChildren:function (parent) {
            var models = db.shortcodeCollections.where({parent_id:parent.id});
            _.each(models, function (model) {
                db.storage.lock();
                model.destroy();
                this.removeChildren(model);
            }, this);
            if (models.length) db.storage.save();
        }
    });
})(window.jQuery);
