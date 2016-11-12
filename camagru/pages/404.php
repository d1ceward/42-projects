<?php
if ($current_page != '404') {
	header('Location: ../index.php?page=404');
	die();
}
$page_title = 'Error 404';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div class="wrap">
		<div id="home-welcome">
			Error 404 - Page not found
		</div>
		<div id="home-message">
			Oops ! Looks like the page you're looking for was moved or never existed.<br>
			Make sure you typed the correct URL or followed a valid link.
		</div>
	</div>
</div>
