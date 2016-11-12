<?php
if ($current_page != 'recovery') {
	header('Location: ../index.php?page=404');
	die();
} elseif (isset($_SESSION['data'])) {
	header('Location: .');
	die();
}
$page_title = 'Account recovery';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div id="login-block">
		<h2>Enter your email</h2>
		<div id="alert">
		</div>
		<div class="login-form">
			<input name="email" id="email_field" type="email" placeholder="Email">
			<button name="submit" type="submit" onclick="recovery();">Next</button>
		</div>
	</div>
</div>