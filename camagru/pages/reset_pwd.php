<?php
if ($current_page != 'reset_pwd') {
	header('Location: ../index.php?page=404');
	die();
} elseif (!isset($_GET['login']) || !isset($_GET['token'])) {
	header('Location: index.php?page=login&alert=error');
	die();
}
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	$sql = $db->prepare('SELECT * FROM users WHERE login=:login AND reset_pwd_token=:token');
	$sql->bindParam(':login', $_GET['login'], PDO::PARAM_STR);
	$sql->bindParam(':token', $_GET['token'], PDO::PARAM_STR);
	$sql->execute();
	if ($sql->rowCount() > 0)
		$data = $sql->fetch(PDO::FETCH_ASSOC);
	else
		header('Location: index.php?page=login&alert=error');
} catch (PDOException $e) {
	header('Location: index.php?page=login&alert=error');
	die();
}
$page_title = 'Reset password';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div id="login-block">
		<h2>Enter a new password</h2>
		<div id="alert">
		</div>
		<div class="login-form">
			<input name="password" id="pwd_field" type="password" placeholder="Password">
			<input name="confirm_pwd" id="confirm_field" type="password" placeholder="Confirm password">
			<input name="login" id="login_field" type="hidden" value="<?php echo $data['login']; ?>">
			<input name="token" id="token_field" type="hidden" value="<?php echo $data['reset_pwd_token']; ?>">
			<button name="submit" type="submit" onclick="reset();">Send</button>
		</div>
	</div>
</div>