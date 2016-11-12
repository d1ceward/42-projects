<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>CarShop42</title>
	<link rel="stylesheet" type="text/css" href="includes/css/main.css">
	<link rel="icon" type="image/png" href="assets/icons/favicon.png" />
</head>
<body>
	<div id="page">
		<div id="top-bar">
			<div class="wrap group">
				<?php
				if (!isset($_SESSION["logged_as_user"])) {
					echo "<a class=\"login-icon\" href=\"index.php?page=login\">Se connecter</a>";
					echo "<a class=\"register-icon\" href=\"index.php?page=register\">Cr&eacute;er un compte</a>";
				}
				else {
					echo "Bienvenue, ".$_SESSION["logged_as_user"];
					echo "<a class=\"logout-icon\" href=\"index.php?page=logout\">D&eacute;connexion</a>";
				}
				?>
				<div id="cart">
					<?php 
					if (isset($_SESSION['basket'])) {
						$count = 0;
						foreach ($_SESSION['basket'] as $product)
							$count += $product;
						echo "<span>".$count." articles</span>";
					}
					else 
						echo "<span>0 articles</span>";
					?>
					<a href="index.php?page=basket">Voir le panier</a>
				</div>
			</div>
		</div>
		<div class="section">
			<header id="header">
				<div class="wrap group">
					<div class="group">
						<h1>CarShop42</h1>
						<p>Plein de voitures, juste 42</p>
					</div>
					<nav>
						<ul id="navigation">
							<li><a <?php if ($current_page === "home") echo "class=\"current\""; ?> href="index.php">Accueil</a></li>
							<?php
							$categories = mysqli_query($db, "SELECT id, name FROM categories ORDER BY name");
							while ($category = mysqli_fetch_array($categories)) {
								echo "<li><a href=\"index.php?page=category&cat=".$category['id']."\">".$category['name']."</a></li>";
							}
							?>
						</ul>
					</nav>
				</div>
			</header>
		</div>