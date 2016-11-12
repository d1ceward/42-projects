<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta content="width=device-width, initial-scale=0.6, user-scalable=no" name="viewport">
	<title>Camagru <?php if ($page_title) echo ' - '.$page_title; ?></title>
	<link rel="stylesheet" type="text/css" href="assets/css/reset.css">
	<link rel="stylesheet" type="text/css" href="assets/css/main.css">
	<script type="text/javascript" src="assets/js/main.js"></script>
	<script type="text/javascript" src="assets/js/request.js"></script>
	<?php
		if ($current_page == 'login' || $current_page == 'register' || $current_page == 'reset_pwd' || $current_page == 'recovery' || $current_page == 'confirm_email')
			echo '<script type="text/javascript" src="assets/js/request-login.js"></script>';
		if ($current_page == 'gallery')
			echo '<script type="text/javascript" src="assets/js/request-gallery.js"></script>';
	?>
</head>
<body>
	<header>
		<div class="wrap">
			<a class="left" id="header-logo" href="index.php">Camagru</a>
			<?php if (isset($_SESSION['data'])) : ?>
			<div class="left">
				<a href="index.php?page=gallery">Gallery</a> |
				<a href="index.php?page=photo">Photo</a>
			</div>
			<div class="right">
				<span class="hidden">Welcome, <span style="font-weight: bold"><?php echo $_SESSION['data']['login']; ?></span> |</span>
				<a onclick="logout();">Logout</a>
			</div>
			<?php else: ?>
			<div class="left">
				<a href="index.php?page=offline_gallery">Gallery</a>
			</div>
			<div class="right">
				<a href="index.php?page=login">Login</a> |
				<a href="index.php?page=register">Register</a>
			</div>
			<?php endif; ?>
		</div>
	</header>
