<?php
ini_set('display_errors', '0');
session_start();
require_once 'database.php';
$pages_list = array('home' => 'home.php',
					'404' => '404.php',
					'gallery' => 'gallery.php',
					'login' => 'login.php',
					'register' => 'register.php',
					'photo' => 'photo.php',
					'confirm_email' => 'confirm_email.php',
					'recovery' => 'recovery.php',
					'reset_pwd' => 'reset_pwd.php',
					'offline_gallery' => 'offline_gallery.php');
$per_page = 5;
?>