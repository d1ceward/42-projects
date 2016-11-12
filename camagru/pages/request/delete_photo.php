<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (!is_numeric($_POST['photo_id']))
		echo '{"state" : 0, "error" : "Invalid photo id."}';
	else {
		$req = $db->prepare('SELECT image_url FROM photo WHERE user_id=:user_id AND id=:photo_id');
		$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
		$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
		$req->execute();
		if ($req->rowCount() > 0) {
			$filename = $req->fetch()[0];
			$req->closeCursor();
			$req = $db->prepare('DELETE FROM photo WHERE user_id=:user_id AND id=:photo_id LIMIT 1');
			$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
			$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
			$req->execute();
			$req->closeCursor();
			$req = $db->prepare('DELETE FROM comment WHERE photo_id=:photo_id');
			$req->bindParam(':photo_id', $_POST['photo_id'], PDO::PARAM_INT);
			$req->execute();
			unlink('../../'.$filename);
			echo '{"state" : 1}';
		} else
			echo '{"state" : 0, "error" : "Invalid photo id or invalid user."}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
