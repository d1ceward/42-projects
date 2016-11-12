<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (strlen($_POST['login']) < 6 && strlen($_POST['login']) > 14)
		echo '{"state" : 0, "error" : "Invalid username length."}';
	elseif (strlen($_POST['pwd']) < 6 && strlen($_POST['pwd']) > 100)
		echo '{"state" : 0, "error" : "Invalid password length."}';
	else {
		$req = $db->prepare('SELECT * FROM users WHERE login=:login AND password=:pwd');
		$req->bindParam(':login', $_POST['login'], PDO::PARAM_STR);
		$req->bindParam(':pwd', hash("whirlpool", $_POST['pwd']), PDO::PARAM_STR);
		$req->execute();
		if ($req->rowCount() > 0) {
			$data = $req->fetch(PDO::FETCH_ASSOC);
			if ($data['enable'] == 1) {
				$_SESSION['data'] = $data;
				echo '{"state" : 1}';
			} else
				echo '{"state" : 0, "error" : "Account disabled."}';
		} else
			echo '{"state" : 0, "error" : "Invalid username or password."}';
	}	
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
