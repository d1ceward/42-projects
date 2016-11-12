<?php
require_once 'database.php';
try {
	$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$db->exec('DROP DATABASE IF EXISTS camagru_flefebvr');
	$db->exec('CREATE DATABASE camagru_flefebvr');
	$db->exec('USE camagru_flefebvr');
	$db->exec('CREATE TABLE users (id int(11) NOT NULL AUTO_INCREMENT, login text NOT NULL, password text NOT NULL, email text NOT NULL, reset_pwd_token text, confirm_mail_token text, enable BOOLEAN NULL DEFAULT FALSE, PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8');
	$db->exec('CREATE TABLE photo (id int(11) NOT NULL AUTO_INCREMENT, user_id int(11) NOT NULL, description text NOT NULL, image_url text NOT NULL, date datetime NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8');
	$db->exec('CREATE TABLE likes (id int(11) NOT NULL AUTO_INCREMENT, user_id int(11) NOT NULL, photo_id int(11) NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8');
	$db->exec('CREATE TABLE comment (id int(11) NOT NULL AUTO_INCREMENT, user_id int(11) NOT NULL, photo_id int(11) NOT NULL, content text NOT NULL, date datetime NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8');
	$db->exec('CREATE TABLE mask (id int(11) NOT NULL AUTO_INCREMENT, name text NOT NULL, filename text NOT NULL, PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8');
	$db->exec("INSERT INTO mask SET name='GamerCat', filename='mask1'");
	$db->exec("INSERT INTO mask SET name='DealWithIt', filename='mask2'");
	$db->exec("INSERT INTO mask SET name='DeusVult', filename='mask3'");
	$db->exec("INSERT INTO mask SET name='RedHood', filename='mask4'");
} catch (PDOException $e) {
	echo $e->getMessage();
	die();
}
?>