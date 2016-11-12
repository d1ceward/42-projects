<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (!is_numeric($_POST['comment_id']))
		echo '{"state" : 0, "error" : "Invalid comment id."}';
	else {
		$req = $db->prepare('SELECT * FROM comment WHERE user_id=:user_id AND id=:comment_id');
		$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
		$req->bindParam(':comment_id', $_POST['comment_id'], PDO::PARAM_INT);
		$req->execute();
		if ($req->rowCount() > 0) {
			$req->closeCursor();
			$req = $db->prepare('DELETE FROM comment WHERE user_id=:user_id AND id=:comment_id LIMIT 1');
			$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
			$req->bindParam(':comment_id', $_POST['comment_id'], PDO::PARAM_INT);
			$req->execute();
			echo '{"state" : 1}';
		} else
			echo '{"state" : 0, "error" : "Invalid comment id or invalid user."}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
