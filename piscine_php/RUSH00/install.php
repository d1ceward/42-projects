<?php
$db = mysqli_connect('localhost', 'root', '');

mysqli_query($db, "CREATE DATABASE IF NOT EXISTS rush00");
mysqli_query($db, "USE rush00");

mysqli_query($db, "CREATE TABLE categories (
  id int(11) NOT NULL AUTO_INCREMENT,
  name text NOT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1");
mysqli_query($db, "INSERT INTO categories VALUES (NULL, 'Alfa Romeo')");
mysqli_query($db, "INSERT INTO categories VALUES (NULL, 'Audi')");
mysqli_query($db, "INSERT INTO categories VALUES (NULL, 'Porsche')");
mysqli_query($db, "INSERT INTO categories VALUES (NULL, 'Seat')");

mysqli_query($db, "CREATE TABLE articles (
	id int(11) NOT NULL AUTO_INCREMENT,
	id_category int(11) NOT NULL,
	name text NOT NULL,
	photo text NOT NULL,
	price int(11) NOT NULL,
	PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 1, '75 Turbo Evo', 'assets/cars/alfa-romeo-75-turbo-evo.jpg', 100)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 2, '200 Quattro', 'assets/cars/audi-200-quattro.jpg', 65)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 3, '911 Carrera RS', 'assets/cars/porsche-911-carrera-rs.jpg', 100)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 4, '124', 'assets/cars/seat-124.jpg', 60)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 1, '1750 Berlina', 'assets/cars/1750-berlina.jpg', 108)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 2, '90', 'assets/cars/audi-90.jpg', 865)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 3, '997', 'assets/cars/porsche-997.jpg', 100)");
mysqli_query($db, "INSERT INTO articles VALUES (NULL, 4, 'Fura Crono', 'assets/cars/seat-fura-crono.jpg', 160)");


mysqli_query($db, "CREATE TABLE users (
  id int(11) NOT NULL AUTO_INCREMENT,
  login text NOT NULL,
  password text NOT NULL,
  admin tinyint(4) NOT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1");
mysqli_query($db, "INSERT INTO users VALUES (NULL, 'root', '06948d93cd1e0855ea37e75ad516a250d2d0772890b073808d831c438509190162c0d890b17001361820cffc30d50f010c387e9df943065aa8f4e92e63ff060c', 1)");

mysqli_query($db, "CREATE TABLE shop (
  id int(11) NOT NULL AUTO_INCREMENT,
  id_user int(11) NOT NULL,
  content text NOT NULL,
  finished int(11) NOT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1");
?>
<h1>Ok</h1>
<hr>
<a href="index.php">Retour</a>