<?php 
/**
 * Basic stuff
 */
$vehicleYears = range(1941, date('Y'));
rsort($vehicleYears);

function validField($field) {
	return in_array($field, [
		'first name', 'last name', 'phone', 'email',
		'yes', 'no', 'year', 'make'
	]);
}

function getFieldsFromContent($content) {
	try {
		$fieldData = $content['field_answers']['#object']->field_answers['und'];
		$fields = array_map(function ($field) { return (object)['value' => $field['value'], 'name' => strtolower($field['value'])]; }, $fieldData);
		return $fields;
	} catch (\Exception $e) {
		error_log("unable to get fields from context in node-questions: ".$e->getMessage());
		die('unable to process at this time');
	}
}

$inputFields = [
	'first name' => (object) [
		'name' => 'fname',
		'type' => 'text',
	],
	'last name' => (object) [
		'name' => 'lname',
		'type' => 'text',
	],
	'phone' => (object) [
		'name' => 'phone',
		'type' => 'tel',
	],
	'email' => (object) [
		'name' => 'email',
		'type' => 'email',
	],
];

$fields = getFieldsFromContent($content);

if (! count($fields)) {
	error_log("[node--questions]: unable to isolate form fields from context variable! Exiting.");
	die("unable to process at this time");
}

print '<h2>'.$content['field_answers']['#object']->title.'</h2>';?>

<div class="form-interior"> 
<?php foreach ($fields as $field ) : ?>

<label class="input-group"> 
<div class="row"> </div> 

<?php if (validField($field->name)) {
	if (in_array($field->name, array_keys($inputFields))) {
		$fieldData = $inputFields[$field->name];
		print "<input type='{$fieldData->type}' name='{$fieldData->name}' size='20' placeholder='{$field->value}' required>";
	} else {
		if (in_array($field->name, ['yes', 'no'])) : ?>
	  <label class="container">
		<input type="radio" value="{$field->value}" name="q_<?=$content['field_answers']['#object']->vid;?>" id="accessible"> 
		<span class="checkmark"></span> <?=$field->value;?>
	  </label>
		<?php endif; ?>	
	<?php if ($field->name == "year") : // YEAR BLOCK ?>
<script type="text/javascript">
$(document).ready( function() {
	var carquery = new CarQuery();
	carquery.init();
	carquery.initYearMakeModelTrim('car-years', 'car-makes', 'car-models', 'car-model-trims');
	$('#cq-show-data').click(  function(){ carquery.populateCarData('car-model-data'); } );
});
</script>

<div id="select-mode">
	<table>
		<tbody>
			<tr valign="bottom">
				<th>Year:</th>
			</tr>
			<tr>
				<td>
					<select id="car-years" name="car-years">
						<option value="">---</option>
<?php foreach ($vehicleYears as $year) : ?>
						<option value="<?=$year;?>"><?=$year;?></option>
<?php endforeach; ?>
</select></td></tr>
<tr valign="bottom"><th>Make:</th></tr>
<tr><td><select id="car-makes" name="car-makes"><option value="">---</option></select></td></tr>
<tr valign="bottom"><th>Model:</th></tr>
<tr><td><select id="car-models" name="car-models"><option value="">---</option></select></td></tr>
<tr valign="bottom"><th>Trim:</th></tr>
</tr><td><select id="car-model-trims" name="car-model-trims"></select></td></tr>
</tbody></table></div>

<?php else: // YEAR BLOCK ELSE ?>

	if($field->name != "model" AND $field->name != "trim") : ?>
  <label class="container">
    <input type="radio" value="<?php print $d['value']; ?>" name="q_<?php print $content['field_answers']['#object']->vid; ?>" id="accessible"> 
	<span class="checkmark"></span><?php print $d['value']; ?>
  </label>
<?php endif; // YEAR BLOCK END ?>
<?php } } ?>


<?php endforeach; ?>
</div>
</label>

