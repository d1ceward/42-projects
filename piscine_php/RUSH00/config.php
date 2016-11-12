<?php
session_start();
require_once('includes/functions.php');
if (!($db = mysqli_connect("localhost", "root", "", "rush00")))
	die("Erreur de connexion &agrave; la base de donn&eacute;e");
// Pages list
$pages_list = array('home' => "home.php",
					'login' => "login.php",
					'register' => "register.php",
					'logout' => "logout.php",
					'category' => "category.php",
					'admin' => "admin.php",
					'basket' => "basket.php",
					'admin_users' => "admin_users.php",
					'admin_orders' => "admin_orders.php",
					'admin_order' => "admin_order.php",
					'admin_categories' => "admin_categories.php",
					'admin_articles' => "admin_articles.php");
?>