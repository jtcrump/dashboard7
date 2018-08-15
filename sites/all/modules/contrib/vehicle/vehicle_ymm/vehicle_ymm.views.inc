<?php

/**
 * @file
 * Export Vehicle Make entity to Views.
 */

/**
 * Implements hook_views_data().
 */
function vehicle_ymm_views_data() {
  $data = array();

  $data['vehicle_ymm_index']['table']['group']  = t('Vehicle Make/Model');

  $data['vehicle_ymm_index']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'vehicle_make' => array(
      'left_field' => 'make_id',
      'field' => 'make_id',
    ),
    'vehicle_model' => array(
      'left_field' => 'model_id',
      'field' => 'model_id',
    ),
  );

  $data['vehicle_ymm_index']['nid'] = array(
    'title' => t('Content with make/model'),
    'help' => t('Relate all content tagged with a vehicle make/model.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'label' => t('node'),
      'skip base' => 'node',
    ),
  );

  $data['vehicle_ymm_index']['make_id'] = array(
    'title' => t('Vehicle make for content'),
    'help' => t('Relate vehicle make associated with content'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'vehicle_make',
      'base field' => 'make_id',
      'label' => t('vehicle make'),
      'skip base' => 'vehicle_make',
    ),
  );

  $data['vehicle_ymm_index']['model_id'] = array(
    'title' => t('Vehicle model for content'),
    'help' => t('Relate vehicle model associated with content'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'vehicle_model',
      'base field' => 'model_id',
      'label' => t('vehicle model'),
      'skip base' => 'vehicle_model',
    ),
  );

  return $data;
}
