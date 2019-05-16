<?php
foreach($items as $item){
// print "|".render($item)."|||";
}

// print $user->roles[1];

if(substr_count(render($items[0]),"<h2></h2>") == 1 AND $user->roles[1] == "anonymous user"){
print '<div class="voucher"><img src="/sites/default/files/images/golden-ticket-h.jpg" alt="Voucher for 2500 free mail pieces" /></div>';
print "<style>#regForm {display: none;}.voucher{margin:auto;} .voucher img {display:block; margin-left: auto; margin-right: auto; max-width: 60%; margin-top: -500px;}</style>";
}


if($user->roles[1] == "anonymous user"){
// get the url params
$q =  $_GET['q'];
$d = explode("/",$q);
$dealer1 = $d[0];
$purl = $d[1];
// lookup the user



$mysqli = new mysqli("192.168.1.170", "drupaluser", "", "zips");

/* check connection */
	if ($mysqli->connect_errno) {
    	printf("Connect failed: %s\n", $mysqli->connect_error);
    	exit();
	}

$sql = "SELECT * FROM mail_recips WHERE dealer like '%".$dealer1."' AND purl like '$purl' ORDER BY id DESC LIMIT 0,1";
$result = $mysqli->query($sql);



if($result->num_rows == 0){
$sql = "SELECT * FROM mail_recips WHERE dealer like '%".$dealer1."' AND purl like 'JohnDoe' ORDER BY id DESC LIMIT 0,1";
$result = $mysqli->query($sql);
} 


$row = $result->fetch_assoc();

$title = $row['purl'];
$fname = $row['fname'];
$lname = $row['lname'];
$PropID = $row['dealer'];
$dealer = $row['dealer'];
$address = $row['address'];
$address2 = $row['address2'];
$city = $row['city'];
$state = $row['state'];
$zip = $row['zip'];

$phone = $row['recip_phone'];
$email = $row['recip_email'];


$mysqli->close();

/*
print "<pre>";
print_r($row);
print "</pre>";
*/

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

	if($title != '' and $title != 'JohnDoe'){
 	$node_wrapper->save();
	}
}

?>



<form id="regForm" action="/thank-you.php" method="POST">
<input type="hidden" name="uid" value="<?php print $_GET['q'];; ?>">

<?php if(isset($_SESSION['sid'])) { ?>
<input type="hidden" name="sid" value="<?php print $_SESSION['sid']; ?>">
<?php } ?>

<?php if(isset($_GET['q'])){ 
if(substr($_GET['q'],0,4) != 'node'){
?>
<div id="form-intro">
<h2><?php print $d->field_form_title['und'][0]['value']; ?></h2>
<?php print $d->field_form_intro_text['und'][0]['value']; ?>
</div>
<?php } } ?>

<?php 
$x=0;



foreach($items as $item){

print '<div class="tab">';
print render($item);
print '</div>';

} 

?>


<?php if(isset($_GET['q'])){ 
	if(substr($_GET['q'],0,4) != 'node'){
?>

  	<div style="overflow:auto;">
    		<div style="float:right;">
      		<button type="button" id="prevBtn" onclick="nextPrev(-1)">Previous</button>
      		<button type="button" id="nextBtn" onclick="nextPrev(1)">Next</button>
    		</div>
  	</div>

<?php
	}
}
?>




  <!-- Circles which indicates the steps of the form: -->

  <div style="text-align:center;margin-top:40px;">
<?php
foreach($items as $item){
?>
    <span class="step"></span>
<?php

}
?>
  </div>
</form>


