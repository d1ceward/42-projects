<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
if (isset($_GET['del_id'])) {
	$del_id = ceil($_GET['del_id']);
	$articles = mysqli_query($db, "SELECT * FROM articles WHERE id_category = ".$del_id);
	if (mysqli_num_rows($articles) > 0) {
		$error_msg = "Il y a encore des articles dans cette categorie, vous ne pouvez donc pas la supprimer";
	} else {
		mysqli_query($db, "DELETE FROM categories WHERE id = ".$del_id);
	}
}
if (isset($_POST['modif'])) {
	$modif_id = ceil(@$_POST['id']);
	$name = ft_secure(@$_POST['name']);
	if ($name == "") {
		$error_msg = "Le nom de la categorie est vide";
	} else {
		$retour = mysqli_query($db, "UPDATE categories SET name = '".$name."' WHERE id = ".$modif_id);
	}
}
if (isset($_POST['add'])) {
	$name = ft_secure(@$_POST['name']);
	if ($name == "") {
		$error_msg = "Le nom de la categorie est vide";
	} else {
		$error_msg = "La categorie '".$name."' a bien ete ajoutee";
		mysqli_query($db, "INSERT INTO categories VALUES (NULL, '".$name."')");
	}
}
if (isset($_POST['add2'])) {
	$categorie = ceil(@$_POST['categorie']);
	$name = ft_secure(@$_POST['name']);
	$photo = ft_secure(@$_POST['photo']);
	$price = ceil(@$_POST['price']);
	if (mysqli_num_rows(mysqli_query($db, "SELECT id FROM categories WHERE id = ".$categorie)) == 0) {
		$error_msg = "Cette categorie n'existe pas";
	} else if ($name == "") {
		$error_msg = "Le nom de l'article est vide";
	} else if ($photo == "") {
		$error_msg = "L'url de la photo est vide";
	} else if ($price < 1) {
		$error_msg = "Le prix ne peut pas etre inferieur a 1 euro.";
	} else {
		$error_msg = "L'article '".$name."' a bien ete ajoutee";
		mysqli_query($db, "INSERT INTO articles VALUES (NULL, ".$categorie.", '".$name."', '".$photo."', ".$price.")");
	}
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Gestion des categories (<a href='index.php?page=admin'>Retour</a>)</h1>
		<hr>
		<?php
		if (isset($error_msg))
			echo "<p>".$error_msg."</p>";
		?>
		<table>
			<?php
			$categories = mysqli_query($db, "SELECT * FROM categories ORDER BY id");
			while ($data = mysqli_fetch_array($categories)) {
			?>
			<tr>
				<td>#<?php echo $data['id']; ?></td>
				<td>
					<form method="post">
						<input type="text" name="id" value="<?php echo $data['id']; ?>" style="display:none;" />
						<input type="text" name="name" value="<?php echo $data['name']; ?>" />
						<input type="submit" name="modif" value="OK" />
					</form>
				</td>
				<td>
					<a href='index.php?page=admin_articles&id=<?php echo $data['id']; ?>'>Gerer les articles</a>
				</td>
				<td>
					<a onclick="return confirm('Voulez-vous vraiment supprimer cette categorie? Cette action est irreversible !');" href='index.php?page=admin_categories&del_id=<?php echo $data['id']; ?>'>Supprimer</a>
				</td>
			</tr>
			<?php
			}
			?>
		</table>
		<br>
		<h1>Ajouter une categorie</h1>
		<hr>
		<form method="post">
			Nom de la categorie: <input type="text" name="name" />
			<input type="submit" name="add" value="OK" />
		</form>
		<br>
		<h1>Ajouter un article</h1>
		<hr>
		<form method="post">
			Categorie: <select name="categorie"><?php
			$categories = mysqli_query($db, "SELECT * FROM categories ORDER BY name");
			while ($data = mysqli_fetch_array($categories)) {
				echo "<option value='".$data['id']."'>".$data['name']."</option>";
			}
			?></select><br>
			Nom: <input type="text" name="name"><br>
			URL Photo: <input type="text" name="photo"><br>
			Prix: <input type="text" name="price"><br>
			<input type="submit" name="add2" value="Ajouter un article">
		</form>
	</div>
</div>