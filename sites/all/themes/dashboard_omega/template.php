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

function dashboard_omega_preprocess_html(&$variables) {
	if(@$GLOBALS['user']->roles[1] == "anonymous user"){
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
	$dealer_job_id = $cust_info[$customer_nid]->field_mail_recip_dealership_id['und'][0]['value'];

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
	}
}




