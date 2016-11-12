<?php
unset($_SESSION['mask_data']);
if ($current_page != 'photo') {
	header('Location: ../index.php?page=404');
	die();
} elseif (!isset($_SESSION['data'])) {
	header('Location: .');
	die();
}
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('USE camagru_flefebvr');
	$req = $db->query('SELECT * FROM mask');
	$mask_data = $req->fetchAll(PDO::FETCH_ASSOC);
	$req->closeCursor();
	$req = $db->query('SELECT * FROM photo WHERE user_id='.$_SESSION['data']['id'].' ORDER BY date DESC');
	$photo_data = $req->fetchAll(PDO::FETCH_ASSOC);
} catch (PDOException $e) {
	echo $e->getMessage();
	die();
}
$page_title = 'Photo upload';
require_once 'includes/header.php';
?>
<div id="content">
	<div class="wrap">
		<div id="wrap_pu">
			<div id="alert-pm"></div>
			<div id="photo_upload">
				<video id="video"></video>
				<canvas id="canvas" style="display: none"></canvas>
				<img id="mask-img" style="display: none">
				<div id="panel-top">
					<input id="file" type="file" onchange="load_file()">
					<label for="file">Upload</label>
					<input id="uploaded_file" placeholder="Choose File" disabled="disabled">
					<button id="take-photo" type="submit" disabled="disabled">Take photo</button>
				</div>
				<div id="modal-photo" class="modal">
					<div class="modal-content">
						<span class="close" id="close-pt">x</span>
						<img id="photo">
						<img id="mask-modal" style="display: none">
						<div id="alert" class="alert-pt"></div>
						<textarea name="description" id="description" placeholder="Add an description..."></textarea>
						<button id="submit-pt" type="submit" onclick="add_photo()">Send photo</button>
					</div>
				</div>
				<div id="mask_section">
					<div id="mask_stitle">Masks list</div>
					<?php
					foreach ($mask_data as $mask)
						echo '<div style="float: left" onclick="add_mask('.$mask['id'].')"><img src="photos/masks/thumbs/'.$mask['filename'].'.png" title="'.$mask['name'].'"></div>';
					?>
				</div>
			</div>
			<div id="sb_title">
				Your photos
			</div>
			<div id="sidebar">
				<?php
				foreach ($photo_data as $photo) {
					echo '<img src="'.$photo['image_url'].'">';
				}
				?>
			</div>
		</div>
		<script src="assets/js/webcam.js"></script>
		<script src="assets/js/modal.js"></script>
	</div>
</div>
