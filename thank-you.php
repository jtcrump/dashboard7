<html>
<head>
<title></title>
<style>
body {
<?php // phpinfo(); // exit(); ?>
background: url("/sites/default/files/images/ty_bg.jpg") no-repeat center center fixed;
  -webkit-background-size: cover;
  -moz-background-size: cover;
  -o-background-size: cover;
  background-size: cover;

.ty-box {max-width: 300px;margin: 200px auto 0 auto;text-align: center;background-color: #fff; font-family: arial; padding: 50px 30px 50px 30px }
.ty-box hr {width: 20%;}
}

.container {margin: auto;max-width: 400px; text-align: center;background-color: white; padding: 50px;font-family: arial !important;}
</style>
</head>

<body>
<?php
 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);
// get the form field data

$q = array();

foreach ($_POST as $key => $value) {
   // echo "Field ".htmlspecialchars($key)." is ".htmlspecialchars($value)."<br>";
	if(substr_count(htmlspecialchars($key),"q_") > 0){
	array_push($q, htmlspecialchars($value));
	} else {
		if(substr_count(htmlspecialchars($key),"year") > 0){
		// get year/make/model/trim
		$year = $_POST['car-years'];
		$make = $_POST['car-makes'];
		$model = $_POST['car-models'];
		$trim = $_POST['car-model-trims'];
		$vehicle = $year.'/'.$make.'/'.$model.'/'.$trim;
		array_push($q, htmlspecialchars($vehicle));
		}
	}
}

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

$title = $_SESSION['purl'];

if(!isset($_POST['fname'])){
$fname = $_SESSION['fname'];
$lname = $_SESSION['lname'];
} else {
$fname = $_POST['fname'];
$lname = $_POST['lname'];
$title = $fname . "-" . $lname;
}


$PropID = $_SESSION['sid'];
$dealer = $_SESSION['sid'];
$address = $_SESSION['address'];
$address2 = $_SESSION['address2'];
$city = $_SESSION['city'];
$state = $_SESSION['state'];
$zip = $_SESSION['zip'];

if(!isset($_POST['phone'])){
$phone = $_SESSION['recip_phone'];
} else {
$phone = $_POST['phone'];
}
if(!isset($_POST['email'])){
$email = $_SESSION['recip_email'];
} else {
$email = $_POST['email'];
}


if($title == ''){
$title = $_POST['fname'] . "-" . $_POST['lname'];
$fname = $_POST['fname'];
$lname = $_POST['lname'];
$phone = $_POST['phone'];
$email = $_POST['email'];
}

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
$certificate = $d->field_certificate['und'][0]['filename'];

/*
print "<pre>";
print_r($d->field_certificate);
print "</pre>";
*/
}

/*
 print "<pre>";
 print_r($dealer);
 print "</pre>";
*/

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

$node_wrapper->field_web_user_answer_1 = $q[0];
$node_wrapper->field_web_user_answer_2 = $q[1];
$node_wrapper->field_web_user_answer_3 = $q[2];
$node_wrapper->field_web_user_answer_4 = $q[3];
$node_wrapper->field_web_user_answer_5 = $q[4];
$node_wrapper->field_web_user_answer_6 = $q[5];
$node_wrapper->field_web_user_answer_7 = $q[6];
$node_wrapper->field_response_origin = "Web";

$node_wrapper->field_web_user_address = array( 
        'country' => 'US',
        'thoroughfare' => $address,
        'premise' => $address2,
        'locality' => $city,
        'administrative_area' => $state,
	'name_line' => $fname . " " . $lname,
        'postal_code' => $zip
      );

 $node_wrapper->save();





// send email notification if required


$node = node_load($dealership);
$wrapper = entity_metadata_wrapper('node', $node);
$dealer_email = $wrapper->field_dealer_email->value();
$email_lead = $wrapper->field_email_leads->value();
$email_contact = $wrapper->field_dealer_contact->value();


if(isset($email_lead)){
$from = "mycampaignboard@ypprint.com";
$subject = "[My Campaign Board] Congratulations! A new lead has been generated on your campaign!";
$body = 'Hello ' . $email_contact . ',<br />A new lead has been generated on your campaign. Please log into your dashboard <a href="http://mycampaginboard.com/login">http://mycampaginboard.com/login</a> to work with this potential sale.<br />Thank you!';

simple_mail_send($from, $dealer_email, $subject, $body);
}



// display Thank You message

foreach ($_POST as $key => $value) {
   // echo "Field ".htmlspecialchars($key)." is ".htmlspecialchars($value)."<br>";
}


?>
<div class="container">
<div class="ty-box">
<h2>THANK YOU</h2>
<hr />
<h4>Your information has been submitted</h4>
<h3><?php print render($dealership_name); ?></h3>
<h4>will contact you soon</h4>
</div>
</div>

<style>
.cert {width: 100%;text-align: center;margin-top: 30px;}
.cert img{max-width: 600px;}
</style>
<?php if(isset($certificate)){ 


print '<div class="cert">';
print '<img src="image.php?fname='.$fname.'&lname='.$lname.'&certificate='.$certificate.'">';


 // print '<h2>'.$fname.' '.$lname.'</h2>';
 // print '<img src="/sites/dashboard7.dd/files/'.$certificate.'">';
print '</div>';
}
?>

</body>
</html>