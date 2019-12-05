<?php

/**
 * @file
 * Custom views handler definition.
 *
 * Place this code in
 * /sites/all/modules/views_cumulative_field/includes/views_handler_cumulative_field.inc
 */
/**
* Custom handler class.
 *
 * @ingroup views_field_handlers
 */
class views_handler_cumulative_field extends views_handler_field_numeric {
  /**
    * {@inheritdoc}
    *
    * Perform any database or cache data retrieval here. In this example there is
    * none.
    */
  function query() {
    $this->additional_fields['cumulative_field_data'] = 0;
  }
  /**
    * {@inheritdoc}
    *
    * Modify any end user views settings here. Debug $options to view the field
    * settings you can change.
    */
  function option_definition() {
    $options = parent::option_definition();
    $options['data_field'] = array('default' => '');
    return $options;
  }
  /**
    * {@inheritdoc}
    *
    * Make changes to the field settings form seen by the end user when adding
    * your field.
    */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['data_field'] = array(
      '#type' => 'radios',
      '#title' => t('Data Field'),
      '#options' => $this->view->display_handler->get_field_labels(),
      '#default_value' => $this->options['data_field'],
      '#description' => t('Select the field for which to calculate the cumulative value.'),
      '#weight' => -10,
    );
  }

  /**
   * Render callback handler.
   *
   * Return the markup that will appear in the rendered field.
   */
  function get_value($values, $field = NULL)
  {
    $datafield = $this->options['data_field'];
    $this->additional_fields['cumulative_field_data'] = $values->_field_data['nid']['entity']->{$datafield}['und'][0]['value'] + $this->additional_fields['cumulative_field_data'];
    $value = $this->additional_fields['cumulative_field_data'];
    drupal_set_message(json_encode($value));
    return $value;
  }

  /**
    * Render callback handler.
    *
    * Return the markup that will appear in the rendered field.
    */
  function render($values)
  {
    $datafield = $this->options['data_field'];
    $this->additional_fields['cumulative_field_data'] = $values->_field_data['nid']['entity']->{$datafield}['und'][0]['value'] + $this->additional_fields['cumulative_field_data'];
    $value = $this->additional_fields['cumulative_field_data'];
    // Hiding should happen before rounding or adding prefix/suffix.
    if ($this->options['hide_empty'] && empty($value) && ($value !== 0 || $this->options['empty_zero'])) {
      return '';
    }

    if (!empty($this->options['set_precision'])) {
      $value = number_format($value, $this->options['precision'], $this->options['decimal'], $this->options['separator']);
    }
    else {
      $remainder = abs($value) - intval(abs($value));
      $value = $value > 0 ? floor($value) : ceil($value);
      $value = number_format($value, 0, '', $this->options['separator']);
      if ($remainder) {
        // The substr may not be locale safe.
        $value .= $this->options['decimal'] . substr($remainder, 2);
      }
    }

    // Should we format as a plural.
    if (!empty($this->options['format_plural'])) {
      $value = format_plural($value, $this->options['format_plural_singular'], $this->options['format_plural_plural']);
    }

    return $this->sanitize_value($this->options['prefix'], 'xss') . $this->sanitize_value($value) . $this->sanitize_value($this->options['suffix'], 'xss');
  }

}
