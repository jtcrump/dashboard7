<?php

/**
 * Implements hook_views_data().
  */
function views_cumulative_field_views_data() {
  $data['views_cumulative_field']['table']['group'] = t('Global');
  $data['views_cumulative_field']['table']['join'] = array(
    // Exist in all views.
    '#global' => array(),
  );
  $data['views_cumulative_field']['cumulative_field'] = array(
    'title' => t('Cumulative Field'),
    'help' => t('Views field that calculates the cumulative value of another field in your view.'),
    'field' => array(
      'handler' => 'views_handler_cumulative_field',
     ),
  );
  return $data;
}
