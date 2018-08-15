<?php

/**
 * @file
 * Class definition of VehicleMakeProcessor.
 */

/**
 * Creates vehicle make and models from feed items.
 *
 * @todo Generate placeholder make_id from make_name upon importing.
 */
class VehicleMakeProcessor extends FeedsProcessor {
  /**
   * Define entity type.
   */
  public function entityType() {
    return 'vehicle_make';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Vehicle makes');
    return $info;
  }

  /**
   * Creates a new entity in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $make = new stdClass();
    $make->type = 'vehicle_make';
    $make->make_id = 0;
    $make->bundle_type = 'vehicle_make_bundle';
    $make->make_make_id = '';
    $make->make_name = '';
    $make->make_country = '';
    return $make;
  }

  /**
   * Loads an existing make.
   */
  protected function entityLoad(FeedsSource $source, $mid) {
    return vehicle_make_load($mid);
  }

  /**
   * Validates a term.
   */
  protected function entityValidate($make) {
    if (empty($make->make_make_id)) {
      throw new FeedsValidationException(t('Vehicle make machine name missing.'));
    }
    if (empty($make->make_name)) {
      throw new FeedsValidationException(t('Vehicle make name missing.'));
    }
  }

  /**
   * Saves a make.
   */
  protected function entitySave($make) {
    vehicle_make_save($make);
  }

  /**
   * Deletes a series of makes.
   */
  protected function entityDeleteMultiple($mids) {
    foreach ($mids as $mid) {
      vehicle_make_delete($mid);
    }
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();
    $targets += array(
      'make_make_id' => array(
        'name' => t('Make machine name'),
        'description' => t('Machine name of the vehicle make.'),
        'optional_unique' => FALSE,
      ),
      'make_name' => array(
        'name' => t('Make name'),
        'description' => t('Name of the vehicle make.'),
        'optional_unique' => TRUE,
      ),
      'make_country' => array(
        'name' => t('Country'),
        'description' => t('The vehicle make country of origin.'),
        'optional_unique' => TRUE,
      ),
    );

    // Implementers of hook_feeds_term_processor_targets() add their targets.
    try {
      self::loadMappers();
      $entity_type = $this->entityType();
      $bundle = 'vehicle_make_bundle';
      drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);
    }
    catch (Exception $e) {
      // Do nothing.
    }
    return $targets;
  }

  /**
   * Get id of an existing feed item term if available.
   */
  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    if ($mid = parent::existingEntityId($source, $result)) {
      return $mid;
    }

    // The only possible unique target is name.
    foreach ($this->uniqueTargets($source, $result) as $target => $value) {
      if ($target == 'make_name') {
        if ($mid = db_query("SELECT make_id FROM {vehicle_make} WHERE make_name = :name", array(':name' => $value))->fetchField()) {
          return $mid;
        }
      }
    }
    return 0;
  }
}
