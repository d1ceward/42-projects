<?php
if ($current_page != 'gallery') {
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
	$req = $db->query('SELECT COUNT(*) FROM photo');
	$page_nb = ceil($req->fetch()[0] / $per_page);
	$req->closeCursor();
	if (isset($_GET['page_nb']) && is_numeric($_GET['page_nb'])) {
		$current_page_nb = intval($_GET['page_nb']);
		if ($current_page_nb > $page_nb)
			$current_page_nb = $page_nb;
	} else
		$current_page_nb = 1;
	$first_entry = ($current_page_nb - 1) * $per_page;
	$req = $db->query('SELECT * FROM photo ORDER BY date DESC LIMIT '.$first_entry.', '.$per_page);
} catch (PDOException $e) {
	echo $e->getMessage();
	die();
}
$page_title = 'Gallery';
require_once 'includes/header.php';
?>
<div id="content">
	<div class="wrap">
		<div id="gallery">
			<div id="alert"></div>
			<?php
			if ($req->rowCount() > 0) {
				$data = $req->fetchAll(PDO::FETCH_ASSOC);
				$req->closeCursor();
				foreach ($data as $row) {
					try {
						$db->exec('USE camagru_flefebvr');
						$req = $db->query('SELECT id FROM likes WHERE photo_id='.$row['id']);
						$like_nb = $req->rowCount();
						$req->closeCursor();
						$req = $db->query('SELECT id FROM likes WHERE user_id='.$_SESSION['data']['id'].' AND photo_id='.$row['id']);
						$user_liked = $req->rowCount();
						$req->closeCursor();
						$req = $db->query('SELECT login FROM users WHERE id='.$row['user_id']);
						$user_data = $req->fetch();
						$req->closeCursor();
						echo '<div class="photo"><div class="user-info"><img src="assets/images/user.svg"><div class="user-login">'.$user_data[0].'</div><div class="user-date">'.date('m/d/y - H:i', strtotime($row['date'])).'</div></div>';
						if ($row['user_id'] == $_SESSION['data']['id'])
							echo '<span class="close" onclick="delete_photo('.$row['id'].');" title="Delete">x</span>';
						echo '<div class="photo-info">'.$row['description'].'</div><img class="photo-img" src="'.$row['image_url'].'"><div class="like-button" onclick="add_like('.$row['id'].');">';
						if ($user_liked == 0)
							echo '<img class="like-icon" src="assets/images/like-empty.png">';
						else
							echo '<img class="like-icon" src="assets/images/like-filled.png">';
						echo 'Like</div><div class="like-count">'.$like_nb.' Likes</div>';
						$req = $db->query('SELECT * FROM comment WHERE photo_id='.$row['id'].' ORDER BY date DESC');
						if ($req->rowCount() > 0) {
							$data_cmt = $req->fetchAll(PDO::FETCH_ASSOC);
							$req->closeCursor();
							foreach ($data_cmt as $row_cmt) {
								$req = $db->query('SELECT login FROM users WHERE id='.$row_cmt['user_id'].'');
								$user_cmt = $req->fetch();
								$req->closeCursor();
								echo '<div class="comment"><div class="user-info"><img src="assets/images/user.svg"><div class="user-login">'.$user_cmt[0].'</div><div class="user-date">'.date('m/d/y - H:i', strtotime($row_cmt['date'])).'</div></div>';
								if ($row_cmt['user_id'] == $_SESSION['data']['id'])
									echo '<span class="close" onclick="delete_comment('.$row_cmt['id'].');" title="Delete">x</span>';
								echo '<div class="cmt-info">'.$row_cmt['content'].'</div></div>';
							}
						}
						$url = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
						$url = htmlspecialchars($url, ENT_QUOTES, 'UTF-8').$row['image_url'];
						echo '<div class="comment"><textarea name="content" id="comment-content-'.$row['id'].'" placeholder="Add an message..."></textarea><button id="submit-cmt" type="submit" onclick="add_comment('.$row['id'].')">Send</button><a id="twitter-share-button" href="https://twitter.com/intent/tweet?text=This%20photo%20is%20awesome%20!&url='.$url.'&hashtags=camagru" target="_blank"><img src="assets/images/twitter.svg"></a></div></div>';
					} catch (PDOException $e) {
						echo $e->getMessage();
						die();
					}
				}
				echo '<div id="pagination">';
				if ($page_nb > 1)
					echo pagination($current_page_nb, $page_nb, 'index.php?page=gallery&page_nb=').'<span class="right"><input id="jump_to" type="text"><button id="jump_to_submit" type="submit" onclick="jump_to()">Jump To</button></span>';
				echo '</div>';
			} else
				echo '<div id="home-welcome">No photo available.</div>';
			?>
		</div>
	</div>
</div>
