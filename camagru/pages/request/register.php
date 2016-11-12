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
	elseif (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL))
		echo '{"state" : 0, "error" : "Invalid email."}';
	elseif (strpbrk($_POST['login'], "#$%^&*()+=-[]';,./{}|:<>?~"))
		echo '{"state" : 0, "error" : "Special characters are forbidden."}';
	else {
		$req = $db->prepare('SELECT * FROM users WHERE login=:login OR email=:email');
		$req->bindParam(':login', $_POST['login'], PDO::PARAM_STR);
		$req->bindParam(':email', $_POST['email'], PDO::PARAM_STR);
		$req->execute();
		if ($req->rowCount() == 0) {
			$req->closeCursor();
			$confirm_mail_token = md5(uniqid(rand(), true));
			$url = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
			$escaped_url = htmlspecialchars($url, ENT_QUOTES, 'UTF-8');
			$url = substr($escaped_url, 0, -26).'index.php?page=confirm_email&login='.$_POST['login'].'&token='.$confirm_mail_token;
			$header = "MIME-Version: 1.0\r\nContent-Type: text/html; charset=UTF-8\r\n";
			$message = '<div style="width: 100%; text-align: center; font-weight: bold; font-size:22px">Welcome '.$_POST['login'].' on Camagru !</div><br><br><div style="width: 100%; text-align: center">Your email confirmation is almost complete. Please click or copy the link below to verify your email adress and continue.</div><br><div style="width: 100%; text-align: center"><a href="'.$url.'">'.$url.'</a></div>';
			if (mail($_POST['email'], 'Welcome on Camagru !', $message, $header)) {
				$req = $db->prepare('INSERT INTO users SET login=:login, password=:pwd, email=:email, confirm_mail_token=:confirm_mail_token');
				$req->bindParam(':login', $_POST['login'], PDO::PARAM_STR);
				$req->bindParam(':pwd', hash("whirlpool", $_POST['pwd']), PDO::PARAM_STR);
				$req->bindParam(':email', $_POST['email'], PDO::PARAM_STR);
				$req->bindParam(':confirm_mail_token', $confirm_mail_token, PDO::PARAM_STR);
				$req->execute();
				echo '{"state" : 1}';
			} else
				echo '{"state" : 0, "error" : "Server error."}';
		} else
			echo '{"state" : 0, "error" : "Username or email already exist."}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
