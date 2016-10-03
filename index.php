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

		<!-- About -->
		<span style="font-weight: bold;"><span><br> About:</span> </span> <span><br>
		</span>
		<div style="margin-left: 40px;">
			<p>I am a physicist and computer scientist at Oak Ridge National
				Laboratory. I am a junior member of the Research Staff in the
				Computer Science Research Group for David Bernholdt. My primary
				areas of research are energy science and computational physics and I
				lead research and development projects for new modeling and
				simulation software in these areas.</p>

			<p>This site contains a fair amount of information about me, all of
				which is accessible by the navigation bar at the top. Please enjoy
				and be sure to contact me if you have any questions. Any opinions
				expressed on this site are my own and not necessarily those of my
				employer or the U.S. Government, although they should be. ;)</p>
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
