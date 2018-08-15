<?php

/**
 * @file
 * Class definition of VehicleModelProcessor.
 */

/**
 * Creates vehicle make and models from feed items.
 *
 * @todo Generate placeholder make_id from make_name upon importing.
 */
class VehicleModelProcessor extends FeedsProcessor {
  /**
   * Define entity type.
   */
  public function entityType() {
    return 'vehicle_model';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Vehicle models');
    return $info;
  }

  /**
   * Creates a new entity in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $model = new stdClass();
    $model->type = 'vehicle_model';
    $model->model_id = 0;
    $model->bundle_type = 'vehicle_model_bundle';
    $model->make_id = 0;
    $model->model_name = '';
    $model->model_trim = '';
    $model->model_body = '';
    return $model;
  }

  /**
   * Loads an existing model.
   */
  protected function entityLoad(FeedsSource $source, $mid) {
    return vehicle_model_load($mid);
  }

  /**
   * Validates a term.
   */
  protected function entityValidate($model) {
    if (empty($model->model_name)) {
      throw new FeedsValidationException(t('Vehicle model name missing.'));
    }
    if (empty($model->make_id)) {
      throw new FeedsValidationException(t('Vehicle model must be assigned a parent make.'));
    }
  }

  /**
   * Saves a model.
   */
  protected function entitySave($model) {
    vehicle_model_save($model);
  }

  /**
   * Deletes a series of models.
   */
  protected function entityDeleteMultiple($mids) {
    foreach ($mids as $mid) {
      vehicle_model_delete($mid);
    }
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();
    $targets += array(
      'make_id' => array(
        'name' => t('Model parent make'),
        'description' => t('Parent make of the vehicle model.'),
        'optional_unique' => FALSE,
      ),
      'model_year_start' => array(
        'name' => t('Model year start'),
        'description' => t('Vehicle model year start.'),
        'optional_unique' => FALSE,
      ),
      'model_year_end' => array(
        'name' => t('Model year end'),
        'description' => t('Vehicle model year end.'),
        'optional_unique' => FALSE,
      ),
      'model_name' => array(
        'name' => t('Model name'),
        'description' => t('Name of the vehicle model.'),
        'optional_unique' => FALSE,
      ),
      'model_trim' => array(
        'name' => t('Model trim'),
        'description' => t('Model trim used in YMM selector.'),
        'optional_unique' => FALSE,
      ),
      'model_body' => array(
        'name' => t('Model body style'),
        'description' => t('Model body style to further distinguish model.'),
        'optional_unique' => FALSE,
      ),
    );

    // Implementers of hook_feeds_term_processor_targets() add their targets.
    try {
      self::loadMappers();
      $entity_type = $this->entityType();
      $bundle = 'vehicle_model_bundle';
      drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);
    }
    catch (Exception $e) {
      // Do nothing.
    }
    return $targets;
  }
}
