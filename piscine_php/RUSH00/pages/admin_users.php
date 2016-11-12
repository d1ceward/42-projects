<?php
if (!isset($_SESSION["logged_as_user"]) || mysqli_num_rows(mysqli_query($db, "SELECT * FROM users WHERE login = '".$_SESSION['logged_as_user']."' AND admin = 1 LIMIT 1")) < 1)
	header("Location: index.php?page=404");
if (isset($_GET['del_id'])) {
	$del_id = ceil($_GET['del_id']);
	mysqli_query($db, "DELETE FROM users WHERE id = ".$del_id);
	header("Location: index.php?page=admin_users");
}
if (isset($_GET['modif_id'])) {
	$modif_id = ceil($_GET['modif_id']);
	mysqli_query($db, "UPDATE users SET admin = admin + 1 WHERE id = ".$modif_id);
	mysqli_query($db, "UPDATE users SET admin = 0 WHERE admin > 1");
	header("Location: index.php?page=admin_users");
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Gestion des utilisateurs (<a href='index.php?page=admin'>Retour</a>)</h1>
		<hr>
		<table style="width: 100%">
			<tr>
				<td># ID</td>
				<td>LOGIN</td>
				<td>STATUS</td>
				<td>Changer le status</td>
				<td>Action</td>
			</tr>
			<?php
			$users = mysqli_query($db, "SELECT * FROM users ORDER BY id");
			while ($data = mysqli_fetch_array($users)) {
			?>
			<tr>
				<td>#<?php echo $data['id']; ?></td>
				<td><?php echo $data['login']; ?></td>
				<td><?php echo ($data['admin'] ? "Admin" : "User"); ?></td>
				<td><a href='index.php?page=admin_users&modif_id=<?php echo $data['id']; ?>'><?php echo ($data['admin'] ? "- Admin" : "+ Admin"); ?></a></td>
				<td><a onclick="return confirm('Voulez-vous vraiment supprimer cet utilisateur? Cette action est irreversible !');" href='index.php?page=admin_users&del_id=<?php echo $data['id']; ?>'>Supprimer</a></td>
			</tr>
			<?php } ?>
		</table>
	</div>
</div>