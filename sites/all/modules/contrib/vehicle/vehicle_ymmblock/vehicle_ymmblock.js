(function ($) {
  Drupal.behaviors.vehicle_ymm_block = {
    attach: function() {
      // Hide all children.
      $('.vehicle-ymm-block li > ul').hide();
      // Expand anything with the class "expanded."
      $('.vehicle-ymm-block li > .expanded + ul').show('normal');
      $('.vehicle-ymm-block li > a').bind("click", function() {
        // Hide all children.
        $(this).find('ul').hide();
        // Toggle next UL.
        $(this).toggleClass('expanded').toggleClass('collapsed').next('ul').toggle('normal');
        return false;
      });
    }
  }
})(jQuery);
