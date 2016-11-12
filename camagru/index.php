<?php
require_once 'config/config.php';
require_once 'includes/functions.php';
$page = isset($_GET['page']) ? $_GET['page'] : NULL;
if ($page != NULL) {
	if(isset($pages_list[$page])) {
		$current_page = $page;
		require_once('pages/'.$pages_list[$page]);
	} else {
		$current_page = '404';
		require_once('pages/404.php');
	}
} else {
	if (isset($_SESSION['data'])) {
		$current_page = 'gallery';
		require_once('pages/gallery.php');
	} else {
		$current_page = 'home';
		require_once('pages/home.php');
	}
}
require_once 'includes/footer.php';
?>
