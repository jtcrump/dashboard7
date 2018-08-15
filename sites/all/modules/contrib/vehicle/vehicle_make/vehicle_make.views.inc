<?php

/**
 * @file
 * Export Vehicle Make entity to Views.
 */

/**
 * Implements hook_views_data().
 */
function vehicle_make_views_data() {
  $data = array();

  $data['vehicle_make']['table']['group']  = t('Vehicle Make');

  $data['vehicle_make']['table']['base'] = array(
    'field' => 'make_id',
    'title' => t('Vehicle Make'),
    'help' => t('Information about a make of vehicle, based on Make List from carqueryapi.com.'),
  );
  $data['vehicle_make']['table']['entity type'] = 'vehicle_make';

  $data['vehicle_make']['make_id'] = array(
    'title' => t('Make id'),
    'help' => t('The make id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['vehicle_make']['make_make_id'] = array(
    'title' => t('Make machine name'),
    'help' => t('The make_id column from Make List.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vehicle_make']['make_name'] = array(
    'title' => t('Make name'),
    'help' => t('The make_display column from Make List.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vehicle_make']['make_country'] = array(
    'title' => t('Country'),
    'help' => t('The make_country column from Make List.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
