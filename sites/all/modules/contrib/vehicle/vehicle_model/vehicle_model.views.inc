<?php

/**
 * @file
 * Export Vehicle Model entity to Views.
 */

/**
 * Implements hook_views_data().
 */
function vehicle_model_views_data() {
  $data = array();

  $data['vehicle_model']['table']['group']  = t('Vehicle Model');

  $data['vehicle_model']['table']['base'] = array(
    'field' => 'model_id',
    'title' => t('Vehicle Model'),
    'help' => t('Information about a model of vehicle, based on Full Model / Trim Data from carqueryapi.com.'),
  );
  $data['vehicle_model']['table']['entity type'] = 'vehicle_model';

  $data['vehicle_model']['model_id'] = array(
    'title' => t('Model id'),
    'help' => t('The model id.'),
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

  $data['vehicle_model']['make_id'] = array(
    'title' => t('Make id'),
    'help' => t('The primary key of the associated vehicle make.'),
    'relationship' => array(
      'base' => 'vehicle_make',
      'field' => 'make_id',
      'left_field' => 'make_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Vehicle Make'),
    ),
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

  $data['vehicle_model']['model_name'] = array(
    'title' => t('Model name'),
    'help' => t('The model_name column from Full Model / Trim Data'),
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

  $data['vehicle_model']['model_trim'] = array(
    'title' => t('Trim'),
    'help' => t('The model_trim column from Full Model / Trim Data'),
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

  $data['vehicle_model']['model_year_start'] = array(
    'title' => t('Year Start'),
    'help' => t('The model_year column from Full Model / Trim Data'),
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

  $data['vehicle_model']['model_year_end'] = array(
    'title' => t('Year End'),
    'help' => t('The model_year column from Full Model / Trim Data'),
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

  $data['vehicle_model']['model_body'] = array(
    'title' => t('Body style'),
    'help' => t('The model_body column from Full Model / Trim Data'),
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
