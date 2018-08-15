<?php

/**
 * @file
 * Views for the default order UI.
 */

/**
 * Implements hook_views_default_views().
 */
function vehicle_ymm_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'vehicles_by_year_and_make';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Vehicles by Year and Make';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Vehicles by Year and Make';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There is currently no content classified with this vehicle year and make.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Vehicle Make/Model: Vehicle model for content */
  $handler->display->display_options['relationships']['model_id']['id'] = 'model_id';
  $handler->display->display_options['relationships']['model_id']['table'] = 'vehicle_ymm_index';
  $handler->display->display_options['relationships']['model_id']['field'] = 'model_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Vehicle Model: Year Start */
  $handler->display->display_options['arguments']['model_year_start']['id'] = 'model_year_start';
  $handler->display->display_options['arguments']['model_year_start']['table'] = 'vehicle_model';
  $handler->display->display_options['arguments']['model_year_start']['field'] = 'model_year_start';
  $handler->display->display_options['arguments']['model_year_start']['relationship'] = 'model_id';
  $handler->display->display_options['arguments']['model_year_start']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['model_year_start']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['model_year_start']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['model_year_start']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Vehicle Model: Year End */
  $handler->display->display_options['arguments']['model_year_end']['id'] = 'model_year_end';
  $handler->display->display_options['arguments']['model_year_end']['table'] = 'vehicle_model';
  $handler->display->display_options['arguments']['model_year_end']['field'] = 'model_year_end';
  $handler->display->display_options['arguments']['model_year_end']['relationship'] = 'model_id';
  $handler->display->display_options['arguments']['model_year_end']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['model_year_end']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['model_year_end']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['model_year_end']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Vehicle Model: Make id */
  $handler->display->display_options['arguments']['make_id']['id'] = 'make_id';
  $handler->display->display_options['arguments']['make_id']['table'] = 'vehicle_model';
  $handler->display->display_options['arguments']['make_id']['field'] = 'make_id';
  $handler->display->display_options['arguments']['make_id']['relationship'] = 'model_id';
  $handler->display->display_options['arguments']['make_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['make_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['make_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['make_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'vehicles-by-year-and-make';

  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'vehicles_by_style';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Vehicles by Style';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Vehicles by Style';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There is currently no content classified with this vehicle body style.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Vehicle Make/Model: Vehicle model for content */
  $handler->display->display_options['relationships']['model_id']['id'] = 'model_id';
  $handler->display->display_options['relationships']['model_id']['table'] = 'vehicle_ymm_index';
  $handler->display->display_options['relationships']['model_id']['field'] = 'model_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Vehicle Model: Body style */
  $handler->display->display_options['arguments']['model_body']['id'] = 'model_body';
  $handler->display->display_options['arguments']['model_body']['table'] = 'vehicle_model';
  $handler->display->display_options['arguments']['model_body']['field'] = 'model_body';
  $handler->display->display_options['arguments']['model_body']['relationship'] = 'model_id';
  $handler->display->display_options['arguments']['model_body']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['model_body']['title'] = '%1';
  $handler->display->display_options['arguments']['model_body']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['model_body']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['model_body']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['model_body']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['model_body']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'vehicles-by-style';

  $views[$view->name] = $view;

  return $views;
}
