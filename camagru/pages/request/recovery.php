<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL))
		echo '{"state" : 0, "error" : "Invalid email."}';
	else {
		$req = $db->prepare('SELECT * FROM users WHERE email=:email');
		$req->bindParam(':email', $_POST['email'], PDO::PARAM_STR);
		$req->execute();
		if ($req->rowCount() > 0) {
			$data = $req->fetch(PDO::FETCH_ASSOC);
			$req->closeCursor();
			if ($data['enable'] == 1) {
				$reset_pwd_token = md5(uniqid(rand(), true));
				$url = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
				$escaped_url = htmlspecialchars($url, ENT_QUOTES, 'UTF-8');
				$url = substr($escaped_url, 0, -26).'index.php?page=reset_pwd&login='.$data['login'].'&token='.$reset_pwd_token;
				$header = "MIME-Version: 1.0\r\nContent-Type: text/html; charset=UTF-8\r\n";
				$message = '<div style="width: 100%; text-align: center; font-weight: bold; font-size:22px">Camagru account recovery</div><br><br><div style="width: 100%; text-align: center">Your login is : <span style="font-weight: bold">'.$data['login'].'</span></div><br><div style="width: 100%; text-align: center">Please click or copy the link below to reset your password.</div><br><div style="width: 100%; text-align: center"><a href="'.$url.'">'.$url.'</a></div>';
				if (mail($data['email'], 'Camagru account recovery', $message, $header)) {
					$req = $db->prepare('UPDATE users SET reset_pwd_token=:reset_pwd_token WHERE email=:email');
					$req->bindParam(':reset_pwd_token', $reset_pwd_token, PDO::PARAM_STR);
					$req->bindParam(':email', $_POST['email'], PDO::PARAM_STR);
					$req->execute();
					echo '{"state" : 1}';
				} else 
					echo '{"state" : 0, "error" : "Server error."}';
			} else {
				$confirm_mail_token = md5(uniqid(rand(), true));
				$url = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
				$escaped_url = htmlspecialchars($url, ENT_QUOTES, 'UTF-8');
				$url = substr($escaped_url, 0, -26).'index.php?page=confirm_email&login='.$data['login'].'&token='.$confirm_mail_token;
				$header = "MIME-Version: 1.0\r\nContent-Type: text/html; charset=UTF-8\r\n";
				$message = '<div style="width: 100%; text-align: center; font-weight: bold; font-size:22px">Welcome '.$data['login'].' on Camagru !</div><br><br><div style="width: 100%; text-align: center">Your email confirmation is almost complete. Please click or copy the link below to verify your email adress and continue.</div><br><div style="width: 100%; text-align: center"><a href="'.$url.'">'.$url.'</a></div>';
				if (mail($data['email'], 'Welcome on Camagru !', $message, $header)) {
					$req = $db->prepare('UPDATE users SET confirm_mail_token=:confirm_mail_token WHERE email=:email');
					$req->bindParam(':confirm_mail_token', $confirm_mail_token, PDO::PARAM_STR);
					$req->bindParam(':email', $_POST['email'], PDO::PARAM_STR);
					$req->execute();
					echo '{"state" : 1}';
				} else 
					echo '{"state" : 0, "error" : "Server error."}';
			}
		} else
			echo '{"state" : 0, "error" : "The email does not exist."}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
