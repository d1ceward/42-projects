<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	if (!is_numeric($_POST['mask_id']))
		echo '{"state" : 0, "error" : "Invalid mask id."}';
	else {
		$req = $db->prepare('SELECT * FROM mask WHERE id=:mask_id LIMIT 1');
		$req->bindParam(':mask_id', $_POST['mask_id'], PDO::PARAM_INT);
		$req->execute();
		if ($req->rowCount() > 0) {
			$mask_data = $req->fetch(PDO::FETCH_ASSOC);
			$_SESSION['mask_data'] = $mask_data;
			echo '{"state" : 1, "mask_id" : '.$mask_data['id'].', "filename" : "'.$mask_data['filename'].'", "name" : "'.$mask_data['name'].'"}';
		} else
			echo '{"state" : 0, "error" : "Invalid mask id."}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>