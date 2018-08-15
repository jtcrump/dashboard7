<?php
 define('DRUPAL_ROOT', getcwd());

 include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
 drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 drupal_set_time_limit(240);


// get the customer info

	$query = new EntityFieldQuery();
	$result = $query
  		->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'mail_recipient') 
		->propertyCondition('status', 1)
  		->fieldCondition('field_mail_recip_phone_code', 'value', '127513', '=')
  		->execute();
	$cust_nid = array_keys($result['node']);
	$cust_info = entity_load('node',$cust_nid);

	$x=0;
		foreach($cust_info as $key){
   			foreach ($key as $value) {
				if($x ==0){
       				$cnid = $value;
				break;
				}
   			}
		}
$dealer_job_id = $cust_info[$cnid]->field_mail_recip_dealer_job_id['und'][0]['value'];
print "<br />";

// print $cnid;
print "<pre>";
// print_r($cust_info);
print "</pre>";




// get the dealer info
	$query = new EntityFieldQuery();
	$result = $query
  		->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'job_dashboard') 
		->propertyCondition('status', 1)
  		->fieldCondition('field_job_id', 'value', $dealer_job_id, '=')
  		->execute();
	$dealer_nid = array_keys($result['node']);
	$dealer_info = entity_load('node',$dealer_nid);

	$x=0;
		foreach($dealer_info as $key){
   			foreach ($key as $value) {
				if($x ==0){
       				$dnid = $value;
				break;
				}
   			}
		}
// print $dnid;

print "<pre>";
// print_r($dealer_info);
print "</pre>";




// make a form
?>

Hi <?php print $cust_info[$cnid]->field_mail_recip_first_name['und'][0]['value']; ?> welcome to the sales event for <?php print $dealer_info[$dnid]->title; ?> taking place from <?php print $dealer_info[$dnid]->field_sale_start_date['und'][0]['value']; ?> through <?php print $dealer_info[$dnid]->field_sale_end_date['und'][0]['value']; ?>









