<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
$id_commande = ceil(@$_GET['id']);
$retour = mysqli_query($db, "SELECT * FROM shop WHERE id = ".$id_commande);
if (mysqli_num_rows($retour) == 0)
	header("Location: index.php?page=admin_orders");
$commande = mysqli_fetch_assoc($retour);
$content = unserialize($commande['content']);
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Commande #<?php echo $id_commande; ?> (<a href='index.php?page=admin_orders'>Retour</a>)</h1>
		<hr>
		<table width="100%">
			<?php
			$total = 0;
			foreach($content as $id_article => $nb_article) {
				$retour = mysqli_query($db, "SELECT * FROM articles WHERE id = ".$id_article." LIMIT 1");
				if (mysqli_num_rows($retour) > 0) {
					$article = mysqli_fetch_array($retour);
					?>
					<tr>
						<td class="photo"><img alt='<?php echo $article['name']; ?>' src='<?php echo $article['photo']; ?>' title='<?php echo $article['name']; ?>' /></td>
						<td><span class="name"><?php echo $article['name']; ?></span><br />Quantité: <?php echo $nb_article; ?></td>
						<td class="price"><?php echo $article['price'] * $nb_article; ?>&euro;</td>
					</tr>
					<?php
					$total += $article['price'] * $nb_article;
				}
			}
			?>
			<tr>
				<td colspan="2" class="name">Total: </td>
				<td class="price"><?php echo $total; ?>&euro;</td>
			</tr>
		</table>
	</div>
</div>