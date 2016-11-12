<?php
if ($current_page != 'home') {
	header('Location: ../index.php?page=404');
	die();
} elseif (isset($_SESSION['data'])) {
	header('Location: .');
	die();
}
$page_title = 'Home';
require_once 'includes/header.php';
?>
<style>body{background: url('assets/images/home_bg.jpg') 75% 50% / cover no-repeat}</style>
<div id="content">
	<div id="home-welcome">
		Welcome on Camagru !
	</div>
</div>
