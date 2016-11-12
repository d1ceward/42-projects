<?php
require_once('config.php');
$page = isset($_GET['page']) ? $_GET['page'] : NULL;
$current_page = "";
if ($page != NULL)
{
	if(isset($pages_list[$page])) {
		$current_page = $page;
		require_once('pages/'.$pages_list[$page]);
	}
	else
		require_once('pages/404.php');
} else {
	$current_page = "home";
	require_once('pages/home.php');
}
require_once('includes/footer.php');
?>