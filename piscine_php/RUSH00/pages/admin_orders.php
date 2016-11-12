<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
if (isset($_GET['valid_id'])) {
	$valid_id = ceil($_GET['valid_id']);
	mysqli_query($db, "UPDATE shop SET finished = finished + 1 WHERE id = ".$valid_id);
	mysqli_query($db, "UPDATE shop SET finished = 0 WHERE finished > 1");
	header("Location: index.php?page=admin_orders");
}
if (isset($_GET['del_id'])) {
	$del_id = ceil($_GET['del_id']);
	mysqli_query($db, "DELETE FROM shop WHERE id = ".$del_id);
	header("Location: index.php?page=admin_orders");
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Gestion des commandes (<a href='index.php?page=admin'>Retour</a>)</h1>
		<hr>
		<?php
		if (isset($msg)) {
			echo "<p>".$msg."</p>";
		}
		?>
		<table style="width: 100%">
			<tr>
				<td># ID</td>
				<td>LOGIN</td>
				<td>STATUS</td>
				<td>Action</td>
				<td>Changer le status</td>
				<td>Action</td>
			</tr>
			<?php
			$orders = mysqli_query($db, "SELECT shop.id, shop.finished, users.login FROM shop LEFT JOIN users ON users.id = shop.id_user ORDER BY shop.finished, shop.id");
			while ($data = mysqli_fetch_array($orders)) {
				?>
				<tr>
					<td>#<?php echo $data['id']; ?></td>
					<td><?php echo $data['login']; ?></td>
					<td><?php echo ($data['finished'] ? "Fini" : "En cours"); ?></td>
					<td><a href='index.php?page=admin_order&id=<?php echo $data['id']; ?>'>Voir la commande</a></td>
					<td><a href='index.php?page=admin_orders&valid_id=<?php echo $data['id']; ?>'><?php echo ($data['finished'] ? "Devalider" : "Valider"); ?></a></td>
					<td><a onclick="return confirm('Voulez-vous vraiment supprimer cette commande? Cette action est irreversible !');" href='index.php?page=admin_orders&del_id=<?php echo $data['id']; ?>'>Supprimer</a></td>
				</tr>
			<?php } ?>
		</table>
	</div>
</div>