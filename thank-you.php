Thanks!
<?php
 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);
// get the form field data



// create web-responses the node

/*
title
field_user_id
field_mail_recip_phone
field_mail_recip_email
field_mail_recip_address
field_web_user_answer_1
field_web_user_answer_2
field_web_user_answer_3
field_web_user_answer_4
field_web_user_answer_5
field_web_user_answer_6
field_web_user_answer_7

Content: Address -postal address field - Thoroughfare (i.e. Street address)
Content: Address -postal address field - Locality (i.e. City)
Content: Address -postal address field - Administrative area (i.e. State / Province)
Content: Address -postal address field - Postal code

// Get the node id of the dealership

*/

$title = "foo";
$fname = $_SESSION['fname'];
$lname = $_SESSION['lname'];
$PropID = $_SESSION['sid'];

$phone = "504-236-0078";
$email = "jcrump@tulane.edu";


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
}

// print "<pre>";
// print_r($dealer);
// print "</pre>";


// Create a node
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

 $node_wrapper->save();



// display Thank You message




?>