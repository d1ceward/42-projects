<?php
if ($current_page != 'confirm_email') {
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
	$sql = $db->prepare('SELECT * FROM users WHERE login=:login AND confirm_mail_token=:token');
	$sql->bindParam(':login', $_GET['login'], PDO::PARAM_STR);
	$sql->bindParam(':token', $_GET['token'], PDO::PARAM_STR);
	$sql->execute();
	if ($sql->rowCount() > 0) {
		$sql = $db->prepare('UPDATE users SET enable = 1, confirm_mail_token = NULL WHERE login=:login');
		$sql->bindParam(':login', $_GET['login'], PDO::PARAM_STR);
		$sql->execute();
		header('Location: index.php?page=login&alert=success');
	} else
		header('Location: index.php?page=login&alert=error');
} catch (PDOException $e) {
	header('Location: index.php?page=login&alert=error');
	die();
}
?>
