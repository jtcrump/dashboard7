<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

function dashboard_omega_theme() {
  $items = array();
	
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'dashboard_omega') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'dashboard_omega_preprocess_user_login'
    ),
  );
  $items['user_pass'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'dashboard_omega') . '/templates',
    'template' => 'user-pass',
    'preprocess functions' => array(
      'dashboard_omega_preprocess_user_pass'
    ),
  );
  return $items;
}

function dashboard_omega_preprocess_user_login(&$vars) {
  $vars['intro_text'] = t('Sign into your account');
}
function dashboard_omega_preprocess_user_pass(&$vars) {
  $vars['intro_text'] = t('This is my super awesome request new password form');
}


function dashboard_omega_preprocess_views_view(&$vars) {
$view = $vars['view'];


if($view->name == "customer_responses"){
	if($view->current_display == "page_3" or $view->current_display == "page_4"){
		if($view->current_display == "page_3"){
	             if(!isset($view->exposed_input['field_scheduled_appointments_value'])){
	             $day = date("d");
	             $month = date("m");
	             $year = date("Y");
                     } else {
		     $day = $view->exposed_input['field_scheduled_appointments_value']['value']['day'];
			if(strlen($day) == 1){ $month = "0".$day; }
		     $month = $view->exposed_input['field_scheduled_appointments_value']['value']['month'];
			if(strlen($month) == 1){ $month = "0".$month; }
		     $year = $view->exposed_input['field_scheduled_appointments_value']['value']['year'];
		     }
          }
		if($view->current_display == "page_4"){
	             if(!isset($view->exposed_input['date_filter']['value']['day'])){
	             $day = date("d");
	             $month = date("m");
	             $year = date("Y");
                     } else {
		     $day = $view->exposed_input['date_filter']['value']['day'];
			if(strlen($day) == 1){ $month = "0".$day; }
		     $month = $view->exposed_input['date_filter']['value']['month'];
			if(strlen($month) == 1){ $month = "0".$month; }
		     $year = $view->exposed_input['date_filter']['value']['year'];
		     }
        }
	$date = $year."-".$month."-".$day;
	$dnid = $view->result[0]->_field_data['nid_1']['entity']->field_dealership['und'][0]['target_id'];
	$node = node_load($dnid);
	$lat = $node->field_map_position['und'][0]['lat'];

		if($view->current_display == "page_3"){
		print '<p>&nbsp;</p><p><a href="/data/export_app/'.$dnid.'/'.$lat.'/'.$date.'" class="button">GET CSV FOR DATE</a></p>';
		} else {
		print '<p>&nbsp;</p><p><a href="/data/export_need_app/'.$dnid.'/'.$lat.'/'.$date.'" class="button">GET CSV FOR DATE</a></p>';
		}
	}
}

	if($view->name == 'get_mail_recipient') {
		if($view->current_display == 'block'){
// $_SESSION['fname'] = $view->result[0]->{'node/fname'};
// $_SESSION['lname'] = $view->result[0]->{'node/lname'};
// $_SESSION['address'] = $view->result[0]->{'node/address'};
// $_SESSION['address2'] = $view->result[0]->{'node/address2'};
// $_SESSION['city'] = $view->result[0]->{'node/city'};
// $_SESSION['state'] = $view->result[0]->{'node/state'};
// $_SESSION['zip'] = $view->result[0]->{'node/zip'};
// $_SESSION['recip_email'] = $view->result[0]->{'node/recip_email'};
// $_SESSION['recip_phone'] = $view->result[0]->{'node/recip_phone'};
// $_SESSION['purl'] = $view->result[0]->{'node/purl'};
// 
// $_SESSION['sid'] = $view->result[0]->{'node/sid'};
// $_SESSION['PropName'] = $view->result[0]->{'node/PropName'};
// $_SESSION['PropAddress'] = $view->result[0]->{'PropAddress'};
// $_SESSION['PropCity'] = $view->result[0]->{'node/PropCity'};
// $_SESSION['PropState'] = $view->result[0]->{'node/PropState'};
// $_SESSION['PropZip'] = $view->result[0]->{'PropZip'};

// print "<pre>";
// print_r($view->result[0]);
// print "</pre>";
		}
	}
}


function dashboard_omega_preprocess_html(&$variables) {

/*
	// make sure a dealer can only view jobs they are added as users to
	if(substr($_SERVER['REQUEST_URI'],0,8) == '/dealer/'){
		if(in_array('dealership',$GLOBALS['user']->roles)){
			if(substr_count($variables['page']['content']['system_main']['main']['#markup'],'johndoe') == 0){
			print "You are not authorised to see this job";
			exit();
			}
		}
	}
*/




/*

	if(@$GLOBALS['user']->roles[1] == "anonymous user" AND $_GET['q'] != 'login'){
	$wid = strtolower($GLOBALS['_GET']['q']);

	// get user node info
	$query = new EntityFieldQuery();
	$result = $query
  		->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'mail_recipient') 
		->propertyCondition('status', 1)
  		->fieldCondition('field_mail_recip_purl', 'value', $wid, '=')
  		->execute();
	$cust_nid = array_keys($result['node']);
	$cust_info = entity_load('node', $cust_nid);

	// get dealership node info
	$customer_nid = $cust_nid[0];
	$dealer_job_id = $cust_info[$customer_nid]->field_job_id['und'][0]['value'];

	$query = new EntityFieldQuery();
	$result = $query
  		->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'job_dashboard') 
		->propertyCondition('status', 1)
  		->fieldCondition('field_job_id', 'value', $dealer_job_id, '=')
  		->execute();
	$dealer_nid = array_keys($result['node']);
	$dealer_info = entity_load('node',$dealer_nid);

		foreach($dealer_info as $key){
   			foreach ($key as $value) {
				if($x ==0){
       				$dnid = $value;
				$x++;
				}
   			}
		}

	// get the web questions
	$questions_info = array();
	$questions = $dealer_info[$dnid]->field_web_questions['und'];
		foreach($questions as $q){
		$qid = $q['target_id'];
		array_push($questions_info, node_load($qid));
		}

	$variables[$myuser]['wid'] = $wid;
	$variables[$myuser]['cust_info'] = $cust_info;
	$variables[$myuser]['dealer_info'] = $dealer_info;
	$variables[$myuser]['questions_info'] = $questions_info;
	exit();
	}
*/
}



