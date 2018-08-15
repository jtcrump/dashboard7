(function ($) {
  Drupal.behaviors.vehicle_ymm_dropdown = {
    attach: function() {
      $('select.vehicle-ymm-make').change(function(){
        var makeElement = $(this);
        var fieldsetElement = makeElement.parent();
        var yearElement = fieldsetElement.children('select.vehicle-ymm-year');
        var modelElement = fieldsetElement.children('select.vehicle-ymm-model');
        var trimElement = fieldsetElement.children('select.vehicle-ymm-trim');
        var limitSelectorElement = fieldsetElement.children('.vehicle-ymm-limit-selector');
        var path = Drupal.settings.basePath + 'vehicle/ymm/' + limitSelectorElement.val() + '/99/' + makeElement.val() + '/model';
        $.getJSON(path, function(j){
          var options = '';
          var optionsArray = [];
          $.each(j, function(key,val) { optionsArray.push(val+'.'+key) });
          optionsArray.sort();

          for(var i = 0; i < optionsArray.length; i++) {
            var thisOption = optionsArray[i].split('.');
            if(thisOption[0].toLowerCase() == 'model') {
              options = '<option value="0">Model</option>'+options;
            } else {
              options += '<option value="' + thisOption[1] + '">' + thisOption[0] + '</option>';
            }
          }

          modelElement.html(options);
          yearElement.html('<option value="0">Year</option>');
          trimElement.html('<option value="0">Trim</option>');
        })
      });
      $('select.vehicle-ymm-model').change(function(){
        var modelElement = $(this);
        var fieldsetElement = modelElement.parent();
        var yearElement = fieldsetElement.children('select.vehicle-ymm-year');
        var makeElement = fieldsetElement.children('select.vehicle-ymm-make');
        var trimElement = fieldsetElement.children('select.vehicle-ymm-trim');
        var limitSelectorElement = fieldsetElement.children('.vehicle-ymm-limit-selector');
        var path = Drupal.settings.basePath + 'vehicle/ymm/' + limitSelectorElement.val() + '/' + makeElement.val() + '/' + modelElement.val() + '/years';
        $.getJSON(path, function(j){
          var options = '';
          $.each(j, function(key,val) { options += '<option value="' + key + '">' + val + '</option>'; });
          yearElement.html(options);
          trimElement.html('<option value="0">Trim</option>');
        })
      });
      $('select.vehicle-ymm-year').change(function(){
        var yearElement = $(this);
        var fieldsetElement = yearElement.parent();
        var makeElement = fieldsetElement.children('select.vehicle-ymm-make');
        var modelElement = fieldsetElement.children('select.vehicle-ymm-model');
        var trimElement = fieldsetElement.children('select.vehicle-ymm-trim');
        var limitSelectorElement = fieldsetElement.children('.vehicle-ymm-limit-selector');
        var path = Drupal.settings.basePath + 'vehicle/ymm/' + limitSelectorElement.val() + '/' + yearElement.val() + '/' + makeElement.val() + '/' + modelElement.val() + '/trim';
        $.getJSON(path, function(j){
          var options = '';
          var optionsArray = [];
          $.each(j, function(key,val) { optionsArray.push(val+'.'+key) });
          optionsArray.sort();

          for(var i = 0; i < optionsArray.length; i++) {
            var thisOption = optionsArray[i].split('.');
            if(thisOption[0].toLowerCase() == 'trim') {
              options = '<option value="0">Trim</option>'+options;
            } else {
              options += '<option value="' + thisOption[1] + '">' + thisOption[0] + '</option>';
            }
          }

          trimElement.html(options);
        })
      });
      $('a.vehicle_ymm_remove_button').click(function(){
        // Get parent table row.
        var row = jQuery(this).closest('td').parent('tr');

        // Hide and empty values.
        jQuery(row).hide();
        jQuery(row).find('select').val('');

        // Fix table row classes.
        var table_id = jQuery(row).parent('tbody').parent('table').attr('id');
        jQuery('#' + table_id + ' tr.draggable:visible').each(function(index, element) {
          jQuery(element).removeClass('odd').removeClass('even');
          if ((index % 2) == 0) {
            jQuery(element).addClass('odd');
          } else {
            jQuery(element).addClass('even');
          }
        });
      });
    }
  }
})(jQuery);
