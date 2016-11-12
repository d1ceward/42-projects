<?php
if (isset($_GET['add'])) {
	$id_add = ceil($_GET['add']);
	if (!isset($_SESSION['basket']))
		$_SESSION['basket'] = array();
	if (isset($_SESSION['basket'][$id_add])) {
		$_SESSION['basket'][$id_add]++;
	} else {
		$_SESSION['basket'][$id_add] = 1;
	}
	header("Location: index.php?page=basket");
}
if (isset($_GET['remove'])) {
	$id_add = ceil($_GET['remove']);
	if (isset($_SESSION['basket'][$id_add]) && $_SESSION['basket'][$id_add] != 0) {
		$_SESSION['basket'][$id_add]--;
	}
	if ($_SESSION['basket'][$id_add] == 0)
		unset($_SESSION['basket'][$id_add]);
	header("Location: index.php?page=basket");
}
if (isset($_POST['submit'])) {
	$res = mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION["logged_as_user"]."' LIMIT 1");
	$data= mysqli_fetch_array($res);
	mysqli_query($db, "INSERT INTO shop VALUES (NULL, ".$data['id'].", '".serialize($_SESSION['basket'])."', 0)");
	unset($_SESSION['basket']);
	header("Location: index.php");
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Valider votre commande</h1>
		<hr>
		<?php
		if (isset($_SESSION["logged_as_user"])) {
			if (!isset($_SESSION['basket']) || count($_SESSION['basket']) == 0)
				echo "Votre panier est vide";
			else {
				echo "<table style='width: 100%'>";
					$total = 0;
					foreach($_SESSION['basket'] as $id_article => $nb_article) {
						$retour = mysqli_query($db, "SELECT * FROM articles WHERE id = ".$id_article." LIMIT 1");
						if (mysqli_num_rows($retour) > 0) {
							$article = mysqli_fetch_array($retour);
							?>
							<tr>
								<td class="photo"><img alt='<?php echo $article['name']; ?>' src='<?php echo $article['photo']; ?>' title='<?php echo $article['name']; ?>' /></td>
								<td class="infos"><span class="name"><?php echo $article['name']; ?></span><br />Quantité: <?php echo $nb_article; ?><br /><a href="index.php?page=basket&remove=<?php echo $id_article; ?>">Moins</a> - <a href="index.php?page=basket&add=<?php echo $id_article; ?>">Plus</a></td>
								<td class="price"><?php echo $article['price'] * $nb_article; ?>&euro;</td>
							</tr>
							<?php
							$total += $article['price'] * $nb_article;
						}
					}
					?>
					<tr id="total">
						<td colspan="2" class="name">Total: </td>
						<td class="price"><?php echo $total; ?>&euro;</td>
					</tr>
				</table>
				<hr>
				<form class="login-form" method="post">
					<button name="submit" type="submit">Valider ma commande</button>
				</form>
				<?php
			}
		} else
			echo "Vous devez vous connecter pour valider votre commande";
		?>
	</div>
</div>