<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Administration</h1>
		<hr>
		<a href="index.php?page=admin_users">Gestion des utilisateurs</a><br>
		<a href="index.php?page=admin_categories">Gestion des categories / articles</a><br>
		<a href="index.php?page=admin_orders">Gestion des commandes</a><br>
	</div>
</div>