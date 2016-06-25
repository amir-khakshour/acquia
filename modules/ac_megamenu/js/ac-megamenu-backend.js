Drupal.ACMegaMenu = Drupal.ACMegaMenu || {};

(function ($) {
  Drupal.behaviors.acMegaMenuBackendAction = {
    attach: function(context) {
      $('select[name="ac-megamenu-animation"]').change(function() {
        $('#ac-megamenu-duration-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
        $('#ac-megamenu-delay-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
      });
      $(".ac-megamenu-column-inner .close").click(function() {
        $(this).parent().html("");
      });
      $("#ac-megamenu-admin select").chosen({
        disable_search_threshold : 15,
        allow_single_deselect: true
      });
    }
  }
})(jQuery);

