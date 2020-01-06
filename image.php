<?php
// var_dump(gd_info());




 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);

if(isset($_GET['purl'])){
$purl = $_GET['purl'];
$PropID = $_GET['propid'];
} else {
	if(isset($_POST['purl'])){
	$purl = strtoupper($_POST['purl']);
	$PropID = $_POST['propid'];
	} else {
	$purl_url = request_uri(); 
	$pu = explode("?",$purl_url);
	$p = explode("/",$pu[1]);
	$PropID = $p[0];
	$purl = $p[1];
	}
}


// get dealership info for sale from dashboard
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
$daddress = $d->field_address['und'][0];
$dphone= $d->field_dealer_phone['und'][0]['value'];
$certificate = $d->field_certificate['und'][0]['filename'];
}



/*
print "<pre>";
print_r($dphone);
print "</pre>";
exit();
*/


// get customer info from 170
db_set_active('zipsdb');


$query = db_select('mail_recips', 'fe');
$query
->fields('fe', array('fname', 'lname', 'dealer', 'address', 'address2', 'city', 'state', 'zip', 'recip_phone', 'recip_email'))
->condition('purl',$purl,'=')
->condition('dealer',$PropID,'=')
->range(0,1)
;

$result = $query->execute();

// print_r($result);
// exit();

if(!isset($result)){
// make up generic user info
$fname = "Preferred";
$lname = "Customer";
$address = "";
$address2 = "";
$city = "";
$state = "";
$zip = "";
$phone = "";
$email = "";
} else {
	foreach($result AS $r) {
	$fname = $r->fname;
	$lname = $r->lname;
	$address = $r->address;
	$address2 = $r->address2;
	$city = $r->city;
	$state = $r->state;
	$zip = $r->zip;
$zip = substr($zip , 0, 6);
$zip = str_replace("-","",$zip);
	$phone = $r->recip_phone;
	$email = $r->recip_email;
	}
}
$title = $fname."-".$lname;
// print $title;
// exit();

db_set_active();




// insert into the dashboard
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
$node_wrapper->field_dealership = $dealership;
$node_wrapper->field_response_origin = "Web";
$node_wrapper->field_mail_recip_phone = $phone;
$node_wrapper->field_mail_recip_email = $email;

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



// give them the personalized voucher
ob_clean();


$info =  field_info_field('field_certificate');
$default_img_fid = $info['settings']['default_image'];
$default_img_file = file_load($default_img_fid);

header("Content-Type: image/jpeg");

if(!file_exists('./sites/dashboard7.dd/files/' . $certificate)){
$certificate = 'default_images/'.$default_img_file->filename;
}

      // Create Image From Existing File
      $jpg_image = imagecreatefromjpeg('./sites/dashboard7.dd/files/' . $certificate);

      // Allocate A Color For The Text
      $white = imagecolorallocate($jpg_image, 255, 255, 255);

      // Set Path to Font File
      $font_path = '/var/www/html/font.ttf';


/*
    [country] => US
    [administrative_area] => FL
    [sub_administrative_area] => 
    [locality] => Winter Park
    [dependent_locality] => 
    [postal_code] => 32789
    [thoroughfare] => 126 S. Park Ave.
    [premise] => 
    [sub_premise] => 
    [organisation_name] => 
    [name_line] => ABC Auto Samples
    [first_name] => ABC
    [last_name] => Auto Samples
    [data] => 
*/



$address_city_state = $daddress['thoroughfare'].", ".$daddress['locality'].", ".$daddress['administrative_area'];

      // Set Text to Be Printed On Image
      $text = $fname;
      $text2 = $lname;
      $text3 = $dealership_name;

if(strlen($text3) > 23){
$dealer_full = $text3;
$dealer_split = explode(" ",$text3);
$text3 = $dealer_split[0] . " " . $dealer_split[1] . " " . $dealer_split[2];
$text4 = str_replace($text3." ", "", $dealer_full);
$text5 = $address_city_state;
if(strlen($dphone) > 3) {
$text6 = "Call: " . $dphone;
} else {
$text6 = "";
} 
      imagettftext($jpg_image, 35, 0, 375, 280, $white, $font_path, $text3);
      imagettftext($jpg_image, 35, 0, 375, 315, $white, $font_path, $text4);
      imagettftext($jpg_image, 25, 0, 375, 345, $white, $font_path, $text5);
      imagettftext($jpg_image, 25, 0, 375, 380, $white, $font_path, $text6);
} else {
$text4 = $address_city_state;
if(strlen($dphone) > 3) {
$text5 = "Call: " . $dphone;
} else {
$text5 = "";
}
      imagettftext($jpg_image, 35, 0, 375, 280, $white, $font_path, $text3);
      imagettftext($jpg_image, 25, 0, 375, 310, $white, $font_path, $text4);
      imagettftext($jpg_image, 25, 0, 375, 345, $white, $font_path, $text5);
}

// size - angle - margin left - from top
      // Print Text On Image
      imagettftext($jpg_image, 45, 0, 525, 150, $white, $font_path, $text);
      imagettftext($jpg_image, 45, 0, 525, 195, $white, $font_path, $text2);



      // Send Image to Browser
      imagejpeg($jpg_image);

      // Clear Memory
      imagedestroy($jpg_image);

