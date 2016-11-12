<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
$id_categorie = ceil(@$_GET['id']);
$retour = mysqli_query($db, "SELECT * FROM categories WHERE id = ".$id_categorie);
if (mysqli_num_rows($retour) == 0) {
	header("Location: index.php?page=admin_categories");
	exit;
}
$categorie = mysqli_fetch_assoc($retour);
if (isset($_GET['del_id'])) {
	$del_id = ceil($_GET['del_id']);
	mysqli_query($db, "DELETE FROM articles WHERE id = ".$del_id);
}
if (isset($_POST['modif'])) {
	$modif_id = ceil(@$_POST['id']);
	$name = ft_secure(@$_POST['name']);
	$photo = ft_secure(@$_POST['photo']);
	$price = ceil(@$_POST['price']);
	if ($name == "") {
		$error_msg = "Le nom de l'article est vide";
	} else if ($photo == "") {
		$error_msg = "L'url de la photo est vide";
	} else if ($price < 1) {
		$error_msg = "Le prix ne peut pas etre inferieur a 1 euro.";
	} else {
		$retour = mysqli_query($db, "UPDATE articles SET name = '".$name."', photo = '".$photo."', price = ".$price." WHERE id = ".$modif_id);
	}
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Gestion des articles dans "<?php echo $categorie['name']; ?>" (<a href='index.php?page=admin_categories'>Retour</a>)</h1>
		<hr>
		<?php
		if (isset($error_msg)) {
			echo "<p>".$error_msg."</p>";
		}
		?>
		<table>
			<?php
			$articles = mysqli_query($db, "SELECT * FROM articles WHERE id_category = ".$id_categorie." ORDER BY id");
			while ($data = mysqli_fetch_array($articles)) {
			?>
			<tr>
				<td>#<?php echo $data['id']; ?></td>
				<td class="photo"><img alt='<?php echo $data['name']; ?>' src='<?php echo $data['photo']; ?>' title='<?php echo $data['name']; ?>' /></td>
				<td>
					<form method="post" action="index.php?page=admin_articles&id=<?php echo $id_categorie; ?>">
						<input type="text" name="id" value="<?php echo $data['id']; ?>" style="display:none;">
						Nom: <input type="text" name="name" value="<?php echo $data['name']; ?>"><br>
						URL Photo: <input type="text" name="photo" value="<?php echo $data['photo']; ?>"><br>
						Prix: <input type="text" name="price" value="<?php echo $data['price']; ?>"><br>
						<input type="submit" name="modif" value="Valider les changements">
					</form>
				</td>
				<td><a onclick="return confirm('Voulez-vous vraiment supprimer cet article? Cette action est irreversible !');" href='index.php?page=admin_articles&id=<?php echo $id_categorie; ?>&del_id=<?php echo $data['id']; ?>'>Supprimer</a></td>
			</tr>
			<?php } ?>
		</table>
	</div>
</div>