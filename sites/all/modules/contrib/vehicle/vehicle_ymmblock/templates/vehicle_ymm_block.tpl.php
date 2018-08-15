<?php

/**
 * @file
 * Hierarchical display template file.
 *
 * Variables:
 * - $ymm_list: A structured list of vehicles arranged by Make>Model>Year.
 *
 * @see template_preprocess_ymmblock()
 */
?>
<?php print theme_item_list($ymm_list); ?>
<script>
  (function ($) {
    // Hide all children.
    $('.vehicle-ymm-block li > div').hide();
    // Expand anything with the class "expanded."
    $('.vehicle-ymm-block li > .expanded + ul').show('normal');
    $('.vehicle-ymm-block li > a.sublevels').bind("click", function() {
      // Hide all children.
      $(this).find('div').hide();
      // Toggle next UL.
      $(this).toggleClass('expanded').toggleClass('collapsed').next('div').toggle('normal');
      return false;
    });
  })(jQuery);
</script>
