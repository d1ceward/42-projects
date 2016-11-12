<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (strlen($_POST['login']) < 6 || strlen($_POST['login']) > 14)
		echo '{"state" : 0, "error" : "Invalid username length."}';
	elseif (strlen($_POST['pwd']) < 6 || strlen($_POST['pwd']) > 100)
		echo '{"state" : 0, "error" : "Invalid password length."}';
	elseif ($_POST['pwd'] != $_POST['confirm_pwd'])
		echo '{"state" : 0, "error" : "Invalid confirm password."}';
	elseif (strpbrk($_POST['login'], "#$%^&*()+=-[]';,./{}|:<>?~"))
		echo '{"state" : 0, "error" : "Invalid username."}';
	elseif (strlen($_POST['token']) != 32 || strpbrk($_POST['token'], "#$%^&*()+=-[]';,./{}|:<>?~"))
		echo '{"state" : 0, "error" : "Invalid token."}';
	else {
		$req = $db->prepare('SELECT * FROM users WHERE login=:login AND reset_pwd_token=:token');
		$req->bindParam(':login', $_POST['login'], PDO::PARAM_STR);
		$req->bindParam(':token', $_POST['token'], PDO::PARAM_STR);
		$req->execute();
		if ($req->rowCount() > 0) {
			$req->closeCursor();
			$req = $db->prepare('UPDATE users SET password=:pwd WHERE login=:login');
			$req->bindParam(':login', $_POST['login'], PDO::PARAM_STR);
			$req->bindParam(':pwd', hash("whirlpool", $_POST['pwd']), PDO::PARAM_STR);
			$req->execute();
			echo '{"state" : 1}';
		} else
			echo '{"state" : 0, "error" : "Invalid username or token."}';
	}	
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
