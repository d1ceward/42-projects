<?php
if ($current_page != 'login') {
	header('Location: ../index.php?page=404');
	die();
} elseif (isset($_SESSION['data'])) {
	header('Location: .');
	die();
}
$page_title = 'Login';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div id="login-block">
		<h2>Login to your account</h2>
		<div id="alert">
			<?php
			if (isset($_GET['alert'])) {
				if ($_GET['alert'] == 'error') echo '<div class="error">An error occured.</div>';
				elseif ($_GET['alert'] == 'success') echo '<div class="success">Your account has been successfully activated.</div>';
				elseif ($_GET['alert'] == 'success_pwd') echo '<div class="success">Your password has been successfully changed.</div>';
				elseif ($_GET['alert'] == 'disable') echo '<div class="disable">You need to confirm your email.</div>';
				elseif ($_GET['alert'] == 'recovery') echo '<div class="disable">Please, check your email.</div>';
			}
			?>
		</div>
		<div class="login-form">
			<input name="login" id="login_field" type="text" placeholder="Username">
			<input name="password" id="pwd_field" type="password" placeholder="Password">
			<button name="submit" type="submit" onclick="login();">Login</button>
			<a href="index.php?page=recovery"><button>Account recovery</button></a>
		</div>
	</div>
</div>
