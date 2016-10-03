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

		<!-- Tools -->
		<span style="font-weight: bold;">Tools:</span> <br>
		<div style="margin-left: 40px;">
			<p>
				Click <a href="http://www.jayjaybillings.org/tools/">here</a> if you
				need some of the various scripts that I have written.These tools are
				mostly for my students and has not been updated for awhile, but I
				have a lot of new stuff that I will add soon.
			</p>
		</div>
	
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
