<?php
if ($current_page != 'register') {
	header('Location: ../index.php?page=404');
	die();
} elseif (isset($_SESSION['data'])) {
	header('Location: .');
	die();
}
$page_title = 'Register';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div id="login-block">
		<h2>Create an account</h2>
		<div id="alert">
		</div>
		<div class="login-form">
			<input name="login" id="login_field" type="text" placeholder="Username">
			<input name="password" id="pwd_field" type="password" placeholder="Password">
			<input name="confirm_pwd" id="confirm_field" type="password" placeholder="Confirm password">
			<input name="email" id="email_field" type="email" placeholder="Email">
			<button name="submit" type="submit" onclick="register();">Register</button>
		</div>
	</div>
</div>
