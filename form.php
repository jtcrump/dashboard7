<?php
 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);


// get all the vars
$purl = $_POST['purl'];
$unid = $_POST['unid'];
$fname = $_POST['fname'];
$lname = $_POST['lname'];
$address = $_POST['address'];
$city = $_POST['city'];
$state = $_POST['state'];
$zip = $_POST['zip'];
$dealer_id = $_POST['dealer_id'];


$q0 = $_POST['q0'];
$q1 = $_POST['q1'];
$q2 = $_POST['q2'];
$q3 = $_POST['q3'];
$q4 = $_POST['q4'];
$q5 = $_POST['q5'];
$q6 = $_POST['q6'];


		// Create a node
		$node = entity_create('node', array('type' => 'web_responses'));
		// Create a Entity Wrapper of that new Entity.
		$node_wrapper = entity_metadata_wrapper('node', $node);
		// Set a title and some text field values.
		$node_wrapper->language = LANGUAGE_NONE;
		$node_wrapper->type = 'web_responses';
		$node_wrapper->title = $purl;
		$node_wrapper->field_user_id = $unid;
		$node_wrapper->field_dealership = $dealer_id;
		$node_wrapper->field_web_user_answer_1 = $q0;
		$node_wrapper->field_web_user_answer_2 = $q1;
		$node_wrapper->field_web_user_answer_3 = $q2;
		$node_wrapper->field_web_user_answer_4 = $q3;
		$node_wrapper->field_web_user_answer_5 = $q4;
		$node_wrapper->field_web_user_answer_6 = $q5;
		$node_wrapper->field_web_user_answer_7 = $q6;
		

	$node_wrapper->save();




print "Thank you for your response " . $fname . "!";




?>