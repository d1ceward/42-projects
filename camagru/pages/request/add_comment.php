<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (strlen($_POST['content']) < 1)
		echo '{"state" : 0, "error" : "Empty comment."}';
	elseif (strlen($_POST['content']) > 140)
		echo '{"state" : 0, "error" : "Message too long, must be under 140 characters."}';
	elseif ($_SESSION['request_time'] > time() - 5)
		echo '{"state" : 0, "error" : "Wait 5 seconds before submit a new comment."}';
	else if (!is_numeric($_POST['photo_id']))
		echo '{"state" : 0, "error" : "Invalid photo id."}';
	else {
		$req = $db->prepare('SELECT user_id FROM photo WHERE id=:photo_id');
		$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
		$req->execute();
		$user_id = $req->fetch()[0];
		$req->closeCursor();
		if ($user_id == $_SESSION['data']['id']) {
			$req = $db->prepare('INSERT INTO comment SET content=:content, photo_id=:photo_id, user_id=:user_id');
			$content = htmlentities($_POST['content']);
			$req->bindParam(':content', $content, PDO::PARAM_STR);
			$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
			$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
			$req->execute();
			$_SESSION['request_time'] = time();
			echo '{"state" : 1}';
		} else {
			$req = $db->query('SELECT email FROM users WHERE id='.$user_id);
			$user_email = $req->fetch()[0];
			$req->closeCursor();
			$header = "MIME-Version: 1.0\r\nContent-Type: text/html; charset=UTF-8\r\n";
			$message = '<div style="width: 100%; text-align: center; font-weight: bold; font-size:22px">New commentary on Camagru</div><br><br><div 	style="width: 100%; text-align: center">Someone posted a new commentary on one of your photos. Check it out !</div>';
			if (mail($user_email, 'New commentary on Camagru !', $message, $header)) {
				$req = $db->prepare('INSERT INTO comment SET content=:content, photo_id=:photo_id, user_id=:user_id');
				$content = htmlentities($_POST['content']);
				$req->bindParam(':content', $content, PDO::PARAM_STR);
				$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
				$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
				$req->execute();
				$_SESSION['request_time'] = time();
				echo '{"state" : 1}';
			} else
				echo '{"state" : 0, "error" : "Server error."}';
		}
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
