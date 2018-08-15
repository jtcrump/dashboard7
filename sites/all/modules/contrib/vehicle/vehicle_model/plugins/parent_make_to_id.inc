<?php

/**
 * @file
 * Feeds Tamper module extension to convert Vehicle Make name to ID.
 */

$plugin = array(
  'form' => 'vehicle_model_parent_make_id_form',
  'callback' => 'vehicle_model_parent_make_id_callback',
  'name' => 'Vehicle make name to ID',
  'multi' => 'loop',
  'category' => 'Vehicle',
);

/**
 * Implements hook_form().
 */
function vehicle_model_parent_make_id_form($importer, $element_key, $settings) {
  $form = array();
  $form['mode'] = array(
    '#type' => 'radios',
    '#title' => t('Vehicle name format'),
    '#default_value' => isset($settings['mode']) ? $settings['mode'] : MAKE_MAKE_ID,
    '#options' => array(
      MAKE_MAKE_ID => t('Machine name'),
      MAKE_NAME => t('Display name'),
    ),
  );
  return $form;
}

/**
 * Implements hook_callback().
 */
function vehicle_model_parent_make_id_callback($result, $item_key, $element_key, &$field, $settings) {
  $field = db_query("SELECT make_id FROM {vehicle_make} WHERE " . $settings['mode'] . " = :name", array(':name' => $field))->fetchField();
}
