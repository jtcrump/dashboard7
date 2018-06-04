<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or
 *   'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 * @see omega_preprocess_html()
 */
?><!DOCTYPE html>
<?php if (omega_extension_enabled('compatibility') && omega_theme_get_setting('omega_conditional_classes_html', TRUE)): ?>
  <!--[if IEMobile 7]><html class="no-js ie iem7" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if lte IE 6]><html class="no-js ie lt-ie9 lt-ie8 lt-ie7" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if (IE 7)&(!IEMobile)]><html class="no-js ie lt-ie9 lt-ie8" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if IE 8]><html class="no-js ie lt-ie9" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if (gte IE 9)|(gt IEMobile 7)]><html class="no-js ie" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>><![endif]-->
  <!--[if !IE]><!--><html class="no-js" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>><!--<![endif]-->
<?php else: ?>
  <html class="no-js" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<?php endif; ?>
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body<?php print $attributes;?>>
  <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>

<?php 
/* if the user is an anonymous mailer recipient render their page */
if(@$user->roles[1] == "anonymous user"){
	if(isset($variables[$myurl])) {
	// print $variables[$myuser]['wid'];
	}

	if(isset($variables[$myurl]['cust_info'])) {
	print "<pre>";
	// print_r($variables[$myuser]['cust_info']);
	print "</pre>";

	$x=0;
		foreach($variables[$myuser]['cust_info'] as $key){
   			foreach ($key as $value) {
				if($x ==0){
       				$unid = $value;
				$x++;
				}
   			}
		}
	}

	if(isset($variables[$myurl]['dealer_info'])) {
 	print "<pre>";
	// print_r($variables[$myurl]['dealer_info']);
 	print "</pre>";

	$x=0;
		foreach($variables[$myuser]['dealer_info'] as $key){
   			foreach ($key as $value) {
				if($x ==0){
       				$dnid = $value;
				$x++;
				}
   			}
		}
	$djid = $variables[$myurl]['dealer_info'][$dnid]->field_job_id['und'][0]['value'];
	$dname = $variables[$myurl]['dealer_info'][$dnid]->title;
	$lat = $variables[$myurl]['dealer_info'][$dnid]->field_map_position['und'][0]['lat'];
	$long = $variables[$myurl]['dealer_info'][$dnid]->field_map_position['und'][0]['lon'];
	}

	if(isset($variables[$myurl]['questions_info'])) {
 	print "<pre>";
	// print_r($variables[$myuser]['questions_info']);
 	print "</pre>";
	}


/* add the form */
print '<h3>Hi '.ucwords(strtolower($variables[$myuser]['cust_info'][$unid]->field_mail_recip_first_name['und'][0]['value'])).'!</h3>';
?>

<form name="customer_response_form" action="/form.php" method="POST">
<input type="hidden" name="purl" value="<?php print $variables[$myuser]['wid']; ?>">
<input type="hidden" name="unid" value="<?php print $unid; ?>">
<input type="hidden" name="fname" value="<?php print ucwords(strtolower($variables[$myuser]['cust_info'][$unid]->field_mail_recip_first_name['und'][0]['value'])); ?>">
<input type="hidden" name="lname" value="<?php print ucwords(strtolower($variables[$myuser]['cust_info'][$unid]->field_mail_recip_last_name['und'][0]['value'])); ?>">
<input type="hidden" name="address" value="<?php print ucwords(strtolower($variables[$myuser]['cust_info'][$unid]->field_mail_recip_address['und'][0]['thoroughfare'])); ?>">
<input type="hidden" name="city" value="<?php print ucwords(strtolower($variables[$myuser]['cust_info'][$unid]->field_mail_recip_address['und'][0]['locality'])); ?>">
<input type="hidden" name="state" value="<?php print strtoupper($variables[$myuser]['cust_info'][$unid]->field_mail_recip_address['und'][0]['administrative_area']); ?>">
<input type="hidden" name="zip" value="<?php print strtoupper($variables[$myuser]['cust_info'][$unid]->field_mail_recip_address['und'][0]['postal_code']); ?>">
<input type="hidden" name="dealer_id" value="<?php print $dnid; ?>">

<?php
$z=0;

foreach($variables[$myuser]['questions_info'] as $q){
print $q->title;
print " ";
$zz=0;
	foreach($q->field_answers['und'] as $a){
	$zz++;
	}

	if($zz == 0){
	print '<input type="text" name="q'.$z.'" value="">';
	} else {
		foreach($q->field_answers['und'] as $a){
    		print '<input type="radio" id="contactChoice1" name="q'.$z.'" value="'.$a['value'].'"> <label for="contactChoice1">'.$a['value'].'</label>';
		print "  ";
		}
	}
$z++;
print "<br />";
}
print "<br />";
print "<br />";
?>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/gmap.js?p9m4zp"></script>
<script src="http://maps.googleapis.com/maps/api/js?v=3&amp;language=en&amp;sensor=false&amp;libraries=places%2Cgeometry&amp;key=AIzaSyA8INWQhJfF9GjmRSWRX-mUKX2u2Nn4vUs"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/icon.js?p9m4zp"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/marker.js?p9m4zp"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/highlight.js?p9m4zp"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/poly.js?p9m4zp"></script>
<script src="/sites/dashboard7.dd/files/js/gmap_markers.js"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/markerloader_static.js?p9m4zp"></script>
<script src="http://dashboard7.dd:8083/sites/all/modules/contrib/gmap/js/gmap_marker.js?p9m4zp"></script>
<script>jQuery.extend(Drupal.settings, {"basePath":"\/","pathPrefix":"","colorbox":{"opacity":"0.85","current":"{current} of {total}","previous":"\u00ab Prev","next":"Next \u00bb","close":"Close","maxWidth":"98%","maxHeight":"98%","fixed":true,"mobiledetect":true,"mobiledevicewidth":"480px"},"overlay":{"paths":{"admin":"node\/*\/webform\nnode\/*\/webform\/*\nnode\/*\/webform-results\nnode\/*\/webform-results\/*\nnode\/*\/submission\/*\nimport\nimport\/*\nnode\/*\/import\nnode\/*\/delete-items\nnode\/*\/log\nfield-collection\/*\/*\/edit\nfield-collection\/*\/*\/delete\nfield-collection\/*\/add\/*\/*\nfile\/add\nfile\/add\/*\nfile\/*\/edit\nfile\/*\/usage\nfile\/*\/delete\nmedia\/*\/edit\/*\nmedia\/*\/format-form\nmedia\/browser\nmedia\/browser\/*\nnode\/*\/edit\nnode\/*\/delete\nnode\/*\/revisions\nnode\/*\/revisions\/*\/revert\nnode\/*\/revisions\/*\/delete\nnode\/add\nnode\/add\/*\noverlay\/dismiss-message\nuser\/*\/shortcuts\nadmin\nadmin\/*\nbatch\ntaxonomy\/term\/*\/edit\nuser\/*\/cancel\nuser\/*\/edit\nuser\/*\/edit\/*\nfile\/*\/panelizer*\nnode\/*\/panelizer*\ntaxonomy\/term\/*\/panelizer*\nuser\/*\/panelizer*","non_admin":"admin\/structure\/block\/demo\/*\nadmin\/reports\/status\/php"},"pathPrefixes":[],"ajaxCallback":"overlay-ajax"},"better_exposed_filters":{"views":{"job_zip_code_stats":{"displays":{"block_1":{"filters":[]},"block":{"filters":[]}}},"test_map":{"displays":{"page_1":{"filters":[]}}},"answers_to_web_questions":{"displays":{"block":{"filters":[]},"block_1":{"filters":[]},"block_2":{"filters":[]},"block_3":{"filters":[]},"block_4":{"filters":[]},"block_5":{"filters":[]},"block_6":{"filters":[]}}}}},"gmap":{"auto1map":{"width":"600px","height":"500px","zoom":4,"maxzoom":"12","controltype":"Small","pancontrol":1,"streetviewcontrol":0,"align":"None","maptype":"Map","mtc":"standard","baselayers":{"Map":1},"styles":{"line_default":["0000ff","5","45","",""],"poly_default":["000000","3","25","ff0000","45"],"highlight_color":"ff0000"},"line_colors":["#00cc00","#ff0000","#0000ff"],"behavior":{"locpick":false,"nodrag":0,"nokeyboard":1,"nomousezoom":0,"nocontzoom":0,"autozoom":1,"dynmarkers":0,"overview":0,"collapsehack":0,"scale":0,"extramarkerevents":false,"clickableshapes":false,"highlight":0},"markermode":"0","id":"auto1map","markers":[{"latitude":<?php print $lat; ?>,"longitude":<?php print $long; ?>,"markername":"drupal","offset":0,"text":"<?php print $dname; ?>","autoclick":1,"opts":{"title":"","highlight":0,"highlightcolor":"#FF0000","animation":"2"}}],"latitude":"38.56439432970777","longitude":"-93.92399729011618"}}});</script>

<?php
$myView = views_embed_view('test_map','page_1',$djid);
if(isset($myView)){echo $myView;}
?>

<input type="submit" name="submit" value="submit">
</form>
<?php
} else {
?>

  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>

<?php } ?>


</body>
</html>
