<?php print '<h2>'.$content['field_answers']['#object']->title.'</h2>'; ?>
<?php foreach($content['field_answers']['#object']->field_answers['und'] as $d){ ?>
<label class="input-group">
<div class="row">
<span class="span label">
<?php if(strtolower($d['value']) != "yes" and strtolower($d['value']) != "no") { print $d['value']; } ?>
</span>
<span class="span error"></span>
</div>

<?php
	if(strtolower($d['value']) == "first name"){
	print '<input type="text" name="fname" size="20" value="'.$_SESSION['fname'].'">';
	}
	if(strtolower($d['value']) == "last name"){
	print '<input type="text" name="lname" size="20" value="'.$_SESSION['lname'].'">';
	}
	if(strtolower($d['value']) == "phone"){
	print '<input type="text" name="phone" size="20">';
	}
	if(strtolower($d['value']) == "email"){
	print '<input type="text" name="email" size="20">';
	}
	if(strtolower($d['value']) == "yes"){
?>
<fieldset>
  <label for="accessible">
    <input type="radio" value="Yes" name="quality" id="accessible"> 
	<span>Yes</span>
  </label>


<?php
	}
	if(strtolower($d['value']) == "no"){
?>
  <label for="pretty">
    <input type="radio" value="No" name="quality" id="pretty"> 
	<span>No</span>
  </label>

</fieldset>
<?php
	}
	if(strtolower($d['value']) == "year"){
// print_r(vehicle_ymm_selector());
?>
<select name="year">
<option>Select a year</option>
<option value="1990">1990</option>
<option value="1991">1991</option>
<option value="1992">1992</option>
<option value="1993">1993</option>
<option value="1994">1994</option>
<option value="1995">1995</option>
<option value="1996">1996</option>
<option value="1997">1997</option>
<option value="1998">1998</option>
<option value="1999">1999</option>
<option value="2000">2000</option>
<option value="2001">2001</option>
<option value="2002">2002</option>
<option value="2003">2003</option>
<option value="2004">2004</option>
<option value="2005">2005</option>
<option value="2006">2006</option>
<option value="2007">2007</option>
<option value="2008">2008</option>
<option value="2009">2009</option>
<option value="2010">2010</option>
<option value="2011">2011</option>
<option value="2012">2012</option>
<option value="2013">2013</option>
<option value="2014">2014</option>
<option value="2015">2015</option>
<option value="2016">2016</option>
<option value="2017">2017</option>
<option value="2018">2018</option>
</select>
<?php }


	if(strtolower($d['value']) == "make"){
?>
<select name="make">
<option>Select a make</option>
<option value="Acura">Acura</option>
<option value="Alfa Romero">Alfa Romero</option>
<option value="Aston Martin">Aston Martin</option>
<option value="Audi">Audi</option>
<option value="Bentley">Bentley</option>
<option value="BMW">BMW</option>
<option value="Bugatti">Bugatti</option>
<option value="Buick">Buick</option>
<option value="Cadillac">Cadillac</option>
<option value="Chevrolet">Chevrolet</option>
<option value="Chrysler">Chrysler</option>
<option value="Citroen">Citroen</option>
<option value="Daewoo">Daewoo</option>
<option value="Dodge">Dodge</option>
<option value="Eagle">Eagle</option>
<option value="Ferrari">Ferrari</option>
<option value="Fiat">Fiat</option>
<option value="Ford">Ford</option>
<option value="GMC">GMC</option>
<option value="Honda">Honda</option>
<option value="Hummer">Hummer</option>
<option value="Hyundai">Hyundai</option>
<option value="Infiniti">Infiniti</option>
<option value="Isuzu">Isuzu</option>
<option value="Jaguar">Jaguar</option>
<option value="Jeep">Jeep</option>
<option value="Kia">Kia</option>
<option value="Lamorghini">Lamorghini</option>
<option value="LandRover">LandRover</option>
<option value="Lexus">Lexus</option>
<option value="Lincoln">Lincoln</option>
<option value="Lotus">Lotus</option>
<option value="Maserati">Maserati</option>
<option value="Mazda">Mazda</option>
<option value="Mclaren">Mclaren</option>
<option value="Mercedes Benz">Mercedes Benz</option>
<option value="Mercury">Mercury</option>
<option value="Mini">Mini</option>
<option value="Mitsubishi">Mitsubishi</option>
<option value="Nissan">Nissan</option>
<option value="Oldsmobile">Oldsmobile</option>
<option value="Pagani">Pagani</option>
<option value="Peugeot">Peugeot</option>
<option value="Plymouth">Plymouth</option>
<option value="Pontiac">Pontiac</option>
<option value="Porche">Porche</option>
<option value="Ram">Ram</option>
<option value="Rolls Royce">Rolls Royce</option>
<option value="Saab">Saab</option>
<option value="Saleen">Saleen</option>
<option value="Saturn">Saturn</option>
<option value="Scion">Scion</option>
<option value="Smart">Smart</option>
<option value="Subaru">Subaru</option>
<option value="Suzuki">Suzuki</option>
<option value="Tesla">Tesla</option>
<option value="Toyota">Toyota</option>
<option value="Volkswagen">Volkswagen</option>
<option value="Volvo">Volvo</option>
</select>
<?php
}
}
?>
</label>
