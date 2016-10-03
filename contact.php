<!-- HTML5 Doc Type Declaration -->
<!DOCTYPE html>
<html>

<!-- Create the header -->
<head>

<!-- Set the metadata type and the browser title -->
<meta charset="utf-8">
<title>Welcome to the Webpage of Jay Jay Billings</title>

<!-- Bootstrap CSS file link. This is Bootstrap 3.0.2, not 2.3.2! -->
<link rel="stylesheet" href="css/bootstrap.css" type="text/css">
<!-- Stylesheet from Bootstrap examples to pad the navbar -->
<link href="navbar.css" rel="stylesheet">

</head>

<!-- Create the body -->
<body>

	<!-- Create the outermost container that will center everything -->
	<div class="container">

		<!-- Include the common parts of the body -->
		<?php include("bodyParts.shtml"); ?>

		<br>
		<p> Please feel free to contact me by any of the mechanisms described 
		below. I only ask that you direct inquiries about my work to my ORNL 
		email address, not my personal email address.</p> 
	
		<!-- Include contact information -->
		<?php include("contactInfo.shtml"); ?>		
		
	</div>

	<!-- Include JQuery and Bootstrap scripts. Putting them at the end preserves 
		website performance (the heavy stuff loads last). JQuery must be loaded
		before bootstrap. -->
	<script src="js/jquery.js"></script>
	<script src="js/bootstrap.js"></script>

	<!-- End the body -->
</body>

<!-- End the document -->
</html>
