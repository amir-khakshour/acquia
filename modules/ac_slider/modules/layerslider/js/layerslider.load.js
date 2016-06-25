(function ($) {

// Behavior to load revolution_slider
Drupal.behaviors.layerSlider = {
  attach: function(context, settings) {
    var sliders = [];

    for (id in settings.acquiaLayerSlider.instances) {
      
      if (settings.acquiaLayerSlider.instances[id] !== undefined) {
          sliders[id] = settings.acquiaLayerSlider.instances[id];
      }
    }
    // Slider set
    for (id in sliders) {
      layerslider_init(id, sliders[id], context);
    }
  }
};

/**
 * Initialize the layerSlider instance
 */
function layerslider_init(id, properties, context) {
  $('#' + id, context).once('layerslider', function() {
    if (properties) {
      $(this).layerSlider(properties);
    }
    else {
      $(this).layerSlider();
    }
  });
}

})( jQuery );
