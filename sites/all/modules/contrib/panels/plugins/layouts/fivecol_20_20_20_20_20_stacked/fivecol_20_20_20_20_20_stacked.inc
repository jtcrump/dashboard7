<?php

/**
 * @file
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Five column 20/20/20/20/20 stacked'),
  'category' => t('Columns: 5'),
  'icon' => 'fivecol_20_20_20_20_20_stacked.png',
  'theme' => 'panels_fivecol_20_20_20_20_20_stacked',
  'css' => 'fivecol_20_20_20_20_20_stacked.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left side'),
    'middleleft' => t('Middle left column'),
    'middle' => t('Middle column'),
    'middleright' => t('Middle right column'),
    'right' => t('Right side'),
    'bottom' => t('Bottom'),
  ),
);
