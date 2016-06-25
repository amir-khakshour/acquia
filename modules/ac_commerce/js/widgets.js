(function ($) {
    /**
     * Make it so when you enter text into the "New set" textfield, the
     * corresponding radio button gets selected.
     */
    Drupal.behaviors.CommerceFancyButtons = {
        attach: function (context, settings) {
            $('.form-type-ac-commerce-fancy-buttons input:checked').closest('.form-item').addClass('active');
            $('.form-type-ac-commerce-fancy-buttons label').on('click', function(e){
                if ($(this).closest('.form-item').is('.active')) {
                    return false;
                }
                $(this).closest('.form-type-ac-commerce-fancy-buttons').find('.form-item').removeClass('active').find('input').prop( "checked", false );
                $(this).closest('.form-item').addClass('active').find('input').prop( "checked", true ).trigger("change");
            });
        }
    };

    // Add a spinner on quantity widget.
    Drupal.behaviors.quantityWidgetSpinner = {
        attach: function ( context, settings ) {

        }
    };

    // Add to cart
    Drupal.ac_commerce_add_to_cart = function() {
        $('.commerce-add-to-cart input[type="submit"]').mousedown();
    };

    // Increase/decrease quantity
    Drupal.commerce_extra_quantity_quantity = function(selector, way) {
        // Find out current quantity and figure out new one
        var quantity = parseInt($(selector).val());
        if (way == 1) {
            // Increase
            var new_quantity = quantity+1;
        }
        else if (way == -1) {
            // Decrease
            var new_quantity = quantity-1;
        }
        else {
            var new_quantity = quantity;
        }

        // Set new quantity
        if (new_quantity >= 1) {
            $(selector).val(new_quantity);
        }

        // Set disabled class depending on new quantity
        if (new_quantity <= 1) {
            $(selector).addClass('disabled');
        }
        else {
            $(selector).removeClass('cdisabled');
        }
    }

})(jQuery);