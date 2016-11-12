<?php
require_once '../../config/config.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	do {
		$file_name = '../../photos/tmp/'.md5(uniqid(rand(), true)).'.png';
	} while (file_exists($file_name));
	if (!isset($_POST['image_url']))
		echo '{"state" : 0, "error" : "Empty image url."}';
	elseif ($_SESSION['request_time'] > time() - 5)
		echo '{"state" : 0, "error" : "Wait 5 seconds before submit a new photo."}';
	elseif (strlen($_POST['description']) > 140)
		echo '{"state" : 0, "error" : "Message too long, must be under 140 characters."}';
	elseif (!isset($_SESSION['mask_data']))
		echo '{"state" : 0, "error" : "No mask selected."}';
	else {
		$req = $db->prepare('INSERT INTO photo SET description=:description, image_url=:image_url, user_id=:user_id');
		$description = htmlentities($_POST['description']);
		$req->bindParam(':description', $description, PDO::PARAM_STR);
		$req->bindParam(':image_url', substr($file_name, 6), PDO::PARAM_STR);
		$req->bindParam(':user_id', $_SESSION['data']['id'], PDO::PARAM_INT);
		$req->execute();
		$photo_data = imagecreatefromstring(base64_decode(explode(',', $_POST['image_url'])[1]));
		$mask_data = imagecreatefrompng('../../photos/masks/'.$_SESSION['mask_data']['filename'].'.png');
		$out = imagecreatetruecolor(640, 480);
		imagecopyresampled($out, $photo_data, 0, 0, 0, 0, 640, 480, 640, 480);
		imagecopyresampled($out, $mask_data, 0, 0, 0, 0, 640, 480, 640, 480);
		imagepng($out, $file_name);
		unset($_SESSION['mask_data']);
		$_SESSION['request_time'] = time();
		echo '{"state" : 1}';
	}
} catch (PDOException $e) {
	echo '{"state" : 0, "error" : "Database error.", "real_error" : "'.$e->getMessage().'"}';
}
?>
