<?php
 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);

// get the form field data

$q1 = $_POST['q1'];
$q2 = $_POST['q2'];
$q3 = $_POST['q3'];
$q4 = $_POST['q4'];
$q5 = $_POST['q5'];
$q6 = $_POST['q6'];
$q7 = $_POST['q7'];

$title = $_POST['ivr'];
$fname = $_POST['fname'];
$lname = $_POST['lname'];
$PropID = $_POST['sid'];
$address = $_POST['address'];
$address2 = $_POST['address2'];
$city = $_POST['city'];
$state = $_POST['state'];
$zip = $_POST['zip'];

$phone = $_POST['recip_phone'];
$email = $_POST['recip_email'];


$appointment = $_POST['appointment'];
if(strlen($appointment) > 3){
$appointment = strtotime($appointment);
} 

$origin = $_POST['origin'];
$notes = $_POST['notes'];

$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'job_dashboard')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->fieldCondition('field_job_id', 'value', $PropID, '=')
  ->range(0, 1)
  // Run the query as user 1.
  ->addMetaData('account', user_load(1));

$result = $query->execute();
if (isset($result['node'])) {
  $job_dashboard_nid = array_keys($result['node']);
  $dealer = entity_load('node', $job_dashboard_nid);
} 

foreach($dealer as $d){
$dealership = $d->vid;
$dealership_name = $d->title;
}

/*
 print "<pre>";
 print_r($dealer);
 print "</pre>";
*/


// Create a node without notes and appointment
$node = entity_create('node', array('type' => 'web_responses'));
// Create a Entity Wrapper of that new Entity.
$node_wrapper = entity_metadata_wrapper('node', $node);
// Set a title and some text field values.
$node_wrapper->language = LANGUAGE_NONE;
$node_wrapper->type = 'web_responses';
$node_wrapper->title = $title;
$node_wrapper->field_mail_recip_first_name = $fname;
$node_wrapper->field_mail_recip_last_name = $lname;
$node_wrapper->field_mail_recip_phone = $phone;
$node_wrapper->field_mail_recip_email = $email;
$node_wrapper->field_dealership = $dealership;
$node_wrapper->field_web_user_answer_1 = $q1;
$node_wrapper->field_web_user_answer_2 = $q2;
$node_wrapper->field_web_user_answer_3 = $q3;
$node_wrapper->field_web_user_answer_4 = $q4;
$node_wrapper->field_web_user_answer_5 = $q5;
$node_wrapper->field_web_user_answer_6 = $q6;
$node_wrapper->field_web_user_answer_7 = $q7;
$node_wrapper->field_response_origin = $origin;
$node_wrapper->field_web_user_address = array( 
        'country' => 'US',
        'thoroughfare' => $address,
        'premise' => $address2,
        'locality' => $city,
        'administrative_area' => $state,
	'name_line' => $fname . " " . $lname,
        'postal_code' => $zip
      );
}



if(strlen($notes) > 3){
// Create a node with notes
$node = entity_create('node', array('type' => 'web_responses'));
// Create a Entity Wrapper of that new Entity.
$node_wrapper = entity_metadata_wrapper('node', $node);
// Set a title and some text field values.
$node_wrapper->language = LANGUAGE_NONE;
$node_wrapper->type = 'web_responses';
$node_wrapper->title = $title;
$node_wrapper->field_mail_recip_first_name = $fname;
$node_wrapper->field_mail_recip_last_name = $lname;
$node_wrapper->field_mail_recip_phone = $phone;
$node_wrapper->field_mail_recip_email = $email;
$node_wrapper->field_dealership = $dealership;
$node_wrapper->field_web_user_answer_1 = $q1;
$node_wrapper->field_web_user_answer_2 = $q2;
$node_wrapper->field_web_user_answer_3 = $q3;
$node_wrapper->field_web_user_answer_4 = $q4;
$node_wrapper->field_web_user_answer_5 = $q5;
$node_wrapper->field_web_user_answer_6 = $q6;
$node_wrapper->field_web_user_answer_7 = $q7;
$node_wrapper->field_response_origin = $origin;
$node_wrapper->field_web_user_notes = array(
   0 => array(
   'value' => $notes,
   )
);
$node_wrapper->field_web_user_address = array( 
        'country' => 'US',
        'thoroughfare' => $address,
        'premise' => $address2,
        'locality' => $city,
        'administrative_area' => $state,
	'name_line' => $fname . " " . $lname,
        'postal_code' => $zip
      );
}



if(strlen($appointment) > 3){
// Create a node with an appointment
$node = entity_create('node', array('type' => 'web_responses'));
// Create a Entity Wrapper of that new Entity.
$node_wrapper = entity_metadata_wrapper('node', $node);
// Set a title and some text field values.
$node_wrapper->language = LANGUAGE_NONE;
$node_wrapper->type = 'web_responses';
$node_wrapper->title = $title;
$node_wrapper->field_mail_recip_first_name = $fname;
$node_wrapper->field_mail_recip_last_name = $lname;
$node_wrapper->field_mail_recip_phone = $phone;
$node_wrapper->field_mail_recip_email = $email;
$node_wrapper->field_dealership = $dealership;
$node_wrapper->field_web_user_answer_1 = $q1;
$node_wrapper->field_web_user_answer_2 = $q2;
$node_wrapper->field_web_user_answer_3 = $q3;
$node_wrapper->field_web_user_answer_4 = $q4;
$node_wrapper->field_web_user_answer_5 = $q5;
$node_wrapper->field_web_user_answer_6 = $q6;
$node_wrapper->field_web_user_answer_7 = $q7;
$node_wrapper->field_response_origin = $origin;
$node_wrapper->field_scheduled_appointments = $appointment;
$node_wrapper->field_web_user_address = array( 
        'country' => 'US',
        'thoroughfare' => $address,
        'premise' => $address2,
        'locality' => $city,
        'administrative_area' => $state,
	'name_line' => $fname . " " . $lname,
        'postal_code' => $zip
      );
}




if(strlen($appointment) > 3 AND strlen($notes) > 3){
// Create a node with notes and an appointment
$node = entity_create('node', array('type' => 'web_responses'));
// Create a Entity Wrapper of that new Entity.
$node_wrapper = entity_metadata_wrapper('node', $node);
// Set a title and some text field values.
$node_wrapper->language = LANGUAGE_NONE;
$node_wrapper->type = 'web_responses';
$node_wrapper->title = $title;
$node_wrapper->field_mail_recip_first_name = $fname;
$node_wrapper->field_mail_recip_last_name = $lname;
$node_wrapper->field_mail_recip_phone = $phone;
$node_wrapper->field_mail_recip_email = $email;
$node_wrapper->field_dealership = $dealership;
$node_wrapper->field_web_user_answer_1 = $q1;
$node_wrapper->field_web_user_answer_2 = $q2;
$node_wrapper->field_web_user_answer_3 = $q3;
$node_wrapper->field_web_user_answer_4 = $q4;
$node_wrapper->field_web_user_answer_5 = $q5;
$node_wrapper->field_web_user_answer_6 = $q6;
$node_wrapper->field_web_user_answer_7 = $q7;
$node_wrapper->field_response_origin = $origin;
$node_wrapper->field_scheduled_appointments = $appointment;
$node_wrapper->field_web_user_notes = array(
   0 => array(
   'value' => $notes,
   )
);
$node_wrapper->field_web_user_address = array( 
        'country' => 'US',
        'thoroughfare' => $address,
        'premise' => $address2,
        'locality' => $city,
        'administrative_area' => $state,
	'name_line' => $fname . " " . $lname,
        'postal_code' => $zip
      );
}






 $node_wrapper->save();




?>
