<?php
// var_dump(gd_info());
// exit();

if(isset($_GET['fname'])){
$fname = strtoupper($_GET['fname']);
$lname = strtoupper($_GET['lname']);
$certificate = $_GET['certificate'];
} else {
$fname = strtoupper($_POST['fname']);
$lname = strtoupper($_POST['lname']);
$certificate = $_POST['certificate'];
}

ob_clean();
      header('Content-type: image/jpeg');

      // Create Image From Existing File
      $jpg_image = imagecreatefromjpeg('./sites/dashboard7.dd/files/'.$certificate);

      // Allocate A Color For The Text
      $white = imagecolorallocate($jpg_image, 255, 255, 255);

      // Set Path to Font File
      $font_path = 'C:\Users\James Crump\Sites\devdesktop\dashboard7\font.TTF';

      // Set Text to Be Printed On Image
      $text = $fname.' '.$lname;

      // Print Text On Image
      imagettftext($jpg_image, 35, 0, 175, 320, $white, $font_path, $text);

      // Send Image to Browser
      imagejpeg($jpg_image);

      // Clear Memory
      imagedestroy($jpg_image);


?>