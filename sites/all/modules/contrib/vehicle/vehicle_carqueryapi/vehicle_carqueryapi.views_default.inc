<?php

/**
 * @file
 * Default views for filtering using the additional fields from CarQuery API.
 */

/**
 * Implements hook_views_default_views().
 */
function vehicle_ymm_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'vehicle_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Vehicle Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Vehicle Search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Vehicle Make/Model: Vehicle make for content */
  $handler->display->display_options['relationships']['make_id']['id'] = 'make_id';
  $handler->display->display_options['relationships']['make_id']['table'] = 'vehicle_ymm_index';
  $handler->display->display_options['relationships']['make_id']['field'] = 'make_id';
  $handler->display->display_options['relationships']['make_id']['required'] = TRUE;
  /* Relationship: Vehicle Make/Model: Vehicle model for content */
  $handler->display->display_options['relationships']['model_id']['id'] = 'model_id';
  $handler->display->display_options['relationships']['model_id']['table'] = 'vehicle_ymm_index';
  $handler->display->display_options['relationships']['model_id']['field'] = 'model_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Vehicle Make: Make name */
  $handler->display->display_options['filters']['make_name']['id'] = 'make_name';
  $handler->display->display_options['filters']['make_name']['table'] = 'vehicle_make';
  $handler->display->display_options['filters']['make_name']['field'] = 'make_name';
  $handler->display->display_options['filters']['make_name']['relationship'] = 'make_id';
  $handler->display->display_options['filters']['make_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['make_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['make_name']['expose']['operator_id'] = 'make_name_op';
  $handler->display->display_options['filters']['make_name']['expose']['label'] = 'Make';
  $handler->display->display_options['filters']['make_name']['expose']['operator'] = 'make_name_op';
  $handler->display->display_options['filters']['make_name']['expose']['identifier'] = 'make_name';
  $handler->display->display_options['filters']['make_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Model name */
  $handler->display->display_options['filters']['model_name']['id'] = 'model_name';
  $handler->display->display_options['filters']['model_name']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_name']['field'] = 'model_name';
  $handler->display->display_options['filters']['model_name']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_name']['expose']['operator_id'] = 'model_name_op';
  $handler->display->display_options['filters']['model_name']['expose']['label'] = 'Model';
  $handler->display->display_options['filters']['model_name']['expose']['operator'] = 'model_name_op';
  $handler->display->display_options['filters']['model_name']['expose']['identifier'] = 'model_name';
  $handler->display->display_options['filters']['model_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Trim */
  $handler->display->display_options['filters']['model_trim']['id'] = 'model_trim';
  $handler->display->display_options['filters']['model_trim']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_trim']['field'] = 'model_trim';
  $handler->display->display_options['filters']['model_trim']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_trim']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_trim']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_trim']['expose']['operator_id'] = 'model_trim_op';
  $handler->display->display_options['filters']['model_trim']['expose']['label'] = 'Trim';
  $handler->display->display_options['filters']['model_trim']['expose']['operator'] = 'model_trim_op';
  $handler->display->display_options['filters']['model_trim']['expose']['identifier'] = 'model_trim';
  $handler->display->display_options['filters']['model_trim']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Year Start */
  $handler->display->display_options['filters']['model_year_start']['id'] = 'model_year_start';
  $handler->display->display_options['filters']['model_year_start']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_year_start']['field'] = 'model_year_start';
  $handler->display->display_options['filters']['model_year_start']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_year_start']['operator'] = 'between';
  $handler->display->display_options['filters']['model_year_start']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_year_start']['expose']['operator_id'] = 'model_year_start_op';
  $handler->display->display_options['filters']['model_year_start']['expose']['label'] = 'Year start';
  $handler->display->display_options['filters']['model_year_start']['expose']['operator'] = 'model_year_start_op';
  $handler->display->display_options['filters']['model_year_start']['expose']['identifier'] = 'model_year_start';
  $handler->display->display_options['filters']['model_year_start']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Year End */
  $handler->display->display_options['filters']['model_year_end']['id'] = 'model_year_end';
  $handler->display->display_options['filters']['model_year_end']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_year_end']['field'] = 'model_year_end';
  $handler->display->display_options['filters']['model_year_end']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_year_end']['operator'] = 'between';
  $handler->display->display_options['filters']['model_year_end']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_year_end']['expose']['operator_id'] = 'model_year_end_op';
  $handler->display->display_options['filters']['model_year_end']['expose']['label'] = 'Year end';
  $handler->display->display_options['filters']['model_year_end']['expose']['operator'] = 'model_year_end_op';
  $handler->display->display_options['filters']['model_year_end']['expose']['identifier'] = 'model_year_end';
  $handler->display->display_options['filters']['model_year_end']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Sold in US */
  $handler->display->display_options['filters']['model_sold_in_us']['id'] = 'model_sold_in_us';
  $handler->display->display_options['filters']['model_sold_in_us']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_sold_in_us']['field'] = 'model_sold_in_us';
  $handler->display->display_options['filters']['model_sold_in_us']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_sold_in_us']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_sold_in_us']['expose']['operator_id'] = 'model_sold_in_us_op';
  $handler->display->display_options['filters']['model_sold_in_us']['expose']['label'] = 'Sold in US (1=Yes)';
  $handler->display->display_options['filters']['model_sold_in_us']['expose']['operator'] = 'model_sold_in_us_op';
  $handler->display->display_options['filters']['model_sold_in_us']['expose']['identifier'] = 'model_sold_in_us';
  $handler->display->display_options['filters']['model_sold_in_us']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Body style */
  $handler->display->display_options['filters']['model_body']['id'] = 'model_body';
  $handler->display->display_options['filters']['model_body']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_body']['field'] = 'model_body';
  $handler->display->display_options['filters']['model_body']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_body']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_body']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_body']['expose']['operator_id'] = 'model_body_op';
  $handler->display->display_options['filters']['model_body']['expose']['label'] = 'Body style';
  $handler->display->display_options['filters']['model_body']['expose']['operator'] = 'model_body_op';
  $handler->display->display_options['filters']['model_body']['expose']['identifier'] = 'model_body';
  $handler->display->display_options['filters']['model_body']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine position */
  $handler->display->display_options['filters']['model_engine_position']['id'] = 'model_engine_position';
  $handler->display->display_options['filters']['model_engine_position']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_position']['field'] = 'model_engine_position';
  $handler->display->display_options['filters']['model_engine_position']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_position']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_engine_position']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_position']['expose']['operator_id'] = 'model_engine_position_op';
  $handler->display->display_options['filters']['model_engine_position']['expose']['label'] = 'Engine position';
  $handler->display->display_options['filters']['model_engine_position']['expose']['operator'] = 'model_engine_position_op';
  $handler->display->display_options['filters']['model_engine_position']['expose']['identifier'] = 'model_engine_position';
  $handler->display->display_options['filters']['model_engine_position']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine type */
  $handler->display->display_options['filters']['model_engine_type']['id'] = 'model_engine_type';
  $handler->display->display_options['filters']['model_engine_type']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_type']['field'] = 'model_engine_type';
  $handler->display->display_options['filters']['model_engine_type']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_type']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_engine_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_type']['expose']['operator_id'] = 'model_engine_type_op';
  $handler->display->display_options['filters']['model_engine_type']['expose']['label'] = 'Engine type';
  $handler->display->display_options['filters']['model_engine_type']['expose']['operator'] = 'model_engine_type_op';
  $handler->display->display_options['filters']['model_engine_type']['expose']['identifier'] = 'model_engine_type';
  $handler->display->display_options['filters']['model_engine_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine cylinders */
  $handler->display->display_options['filters']['model_engine_num_cyl']['id'] = 'model_engine_num_cyl';
  $handler->display->display_options['filters']['model_engine_num_cyl']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_num_cyl']['field'] = 'model_engine_num_cyl';
  $handler->display->display_options['filters']['model_engine_num_cyl']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_num_cyl']['operator'] = 'between';
  $handler->display->display_options['filters']['model_engine_num_cyl']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_num_cyl']['expose']['operator_id'] = 'model_engine_num_cyl_op';
  $handler->display->display_options['filters']['model_engine_num_cyl']['expose']['label'] = 'Engine cylinders between';
  $handler->display->display_options['filters']['model_engine_num_cyl']['expose']['operator'] = 'model_engine_num_cyl_op';
  $handler->display->display_options['filters']['model_engine_num_cyl']['expose']['identifier'] = 'model_engine_num_cyl';
  $handler->display->display_options['filters']['model_engine_num_cyl']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine max power (PS) */
  $handler->display->display_options['filters']['model_engine_power_ps']['id'] = 'model_engine_power_ps';
  $handler->display->display_options['filters']['model_engine_power_ps']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_power_ps']['field'] = 'model_engine_power_ps';
  $handler->display->display_options['filters']['model_engine_power_ps']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_power_ps']['operator'] = 'between';
  $handler->display->display_options['filters']['model_engine_power_ps']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_power_ps']['expose']['operator_id'] = 'model_engine_power_ps_op';
  $handler->display->display_options['filters']['model_engine_power_ps']['expose']['label'] = 'Engine power (PS) between';
  $handler->display->display_options['filters']['model_engine_power_ps']['expose']['operator'] = 'model_engine_power_ps_op';
  $handler->display->display_options['filters']['model_engine_power_ps']['expose']['identifier'] = 'model_engine_power_ps';
  $handler->display->display_options['filters']['model_engine_power_ps']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine max torque (Nm) */
  $handler->display->display_options['filters']['model_engine_torque_nm']['id'] = 'model_engine_torque_nm';
  $handler->display->display_options['filters']['model_engine_torque_nm']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_torque_nm']['field'] = 'model_engine_torque_nm';
  $handler->display->display_options['filters']['model_engine_torque_nm']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_torque_nm']['operator'] = 'between';
  $handler->display->display_options['filters']['model_engine_torque_nm']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_torque_nm']['expose']['operator_id'] = 'model_engine_torque_nm_op';
  $handler->display->display_options['filters']['model_engine_torque_nm']['expose']['label'] = 'Engine torque (Nm) between';
  $handler->display->display_options['filters']['model_engine_torque_nm']['expose']['operator'] = 'model_engine_torque_nm_op';
  $handler->display->display_options['filters']['model_engine_torque_nm']['expose']['identifier'] = 'model_engine_torque_nm';
  $handler->display->display_options['filters']['model_engine_torque_nm']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Engine fuel type */
  $handler->display->display_options['filters']['model_engine_fuel']['id'] = 'model_engine_fuel';
  $handler->display->display_options['filters']['model_engine_fuel']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_engine_fuel']['field'] = 'model_engine_fuel';
  $handler->display->display_options['filters']['model_engine_fuel']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_engine_fuel']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_engine_fuel']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_engine_fuel']['expose']['operator_id'] = 'model_engine_fuel_op';
  $handler->display->display_options['filters']['model_engine_fuel']['expose']['label'] = 'Engine fuel type';
  $handler->display->display_options['filters']['model_engine_fuel']['expose']['operator'] = 'model_engine_fuel_op';
  $handler->display->display_options['filters']['model_engine_fuel']['expose']['identifier'] = 'model_engine_fuel';
  $handler->display->display_options['filters']['model_engine_fuel']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Top speed (KPH) */
  $handler->display->display_options['filters']['model_top_speed_kph']['id'] = 'model_top_speed_kph';
  $handler->display->display_options['filters']['model_top_speed_kph']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_top_speed_kph']['field'] = 'model_top_speed_kph';
  $handler->display->display_options['filters']['model_top_speed_kph']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_top_speed_kph']['operator'] = 'between';
  $handler->display->display_options['filters']['model_top_speed_kph']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_top_speed_kph']['expose']['operator_id'] = 'model_top_speed_kph_op';
  $handler->display->display_options['filters']['model_top_speed_kph']['expose']['label'] = 'Top speed (KPH) between';
  $handler->display->display_options['filters']['model_top_speed_kph']['expose']['operator'] = 'model_top_speed_kph_op';
  $handler->display->display_options['filters']['model_top_speed_kph']['expose']['identifier'] = 'model_top_speed_kph';
  $handler->display->display_options['filters']['model_top_speed_kph']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Drive */
  $handler->display->display_options['filters']['model_drive']['id'] = 'model_drive';
  $handler->display->display_options['filters']['model_drive']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_drive']['field'] = 'model_drive';
  $handler->display->display_options['filters']['model_drive']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_drive']['operator'] = 'contains';
  $handler->display->display_options['filters']['model_drive']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_drive']['expose']['operator_id'] = 'model_drive_op';
  $handler->display->display_options['filters']['model_drive']['expose']['label'] = 'Drivetrain';
  $handler->display->display_options['filters']['model_drive']['expose']['operator'] = 'model_drive_op';
  $handler->display->display_options['filters']['model_drive']['expose']['identifier'] = 'model_drive';
  $handler->display->display_options['filters']['model_drive']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Seats */
  $handler->display->display_options['filters']['model_seats']['id'] = 'model_seats';
  $handler->display->display_options['filters']['model_seats']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_seats']['field'] = 'model_seats';
  $handler->display->display_options['filters']['model_seats']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_seats']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_seats']['expose']['operator_id'] = 'model_seats_op';
  $handler->display->display_options['filters']['model_seats']['expose']['label'] = 'Seats';
  $handler->display->display_options['filters']['model_seats']['expose']['operator'] = 'model_seats_op';
  $handler->display->display_options['filters']['model_seats']['expose']['identifier'] = 'model_seats';
  $handler->display->display_options['filters']['model_seats']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Doors */
  $handler->display->display_options['filters']['model_doors']['id'] = 'model_doors';
  $handler->display->display_options['filters']['model_doors']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_doors']['field'] = 'model_doors';
  $handler->display->display_options['filters']['model_doors']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_doors']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_doors']['expose']['operator_id'] = 'model_doors_op';
  $handler->display->display_options['filters']['model_doors']['expose']['label'] = 'Doors';
  $handler->display->display_options['filters']['model_doors']['expose']['operator'] = 'model_doors_op';
  $handler->display->display_options['filters']['model_doors']['expose']['identifier'] = 'model_doors';
  $handler->display->display_options['filters']['model_doors']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Vehicle Model: Weight (kg) */
  $handler->display->display_options['filters']['model_weight_kg']['id'] = 'model_weight_kg';
  $handler->display->display_options['filters']['model_weight_kg']['table'] = 'vehicle_model';
  $handler->display->display_options['filters']['model_weight_kg']['field'] = 'model_weight_kg';
  $handler->display->display_options['filters']['model_weight_kg']['relationship'] = 'model_id';
  $handler->display->display_options['filters']['model_weight_kg']['operator'] = 'between';
  $handler->display->display_options['filters']['model_weight_kg']['exposed'] = TRUE;
  $handler->display->display_options['filters']['model_weight_kg']['expose']['operator_id'] = 'model_weight_kg_op';
  $handler->display->display_options['filters']['model_weight_kg']['expose']['label'] = 'Weight (kg) between';
  $handler->display->display_options['filters']['model_weight_kg']['expose']['operator'] = 'model_weight_kg_op';
  $handler->display->display_options['filters']['model_weight_kg']['expose']['identifier'] = 'model_weight_kg';
  $handler->display->display_options['filters']['model_weight_kg']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'vehicle-search';

  $views[$view->name] = $view;

  return $views;
}
