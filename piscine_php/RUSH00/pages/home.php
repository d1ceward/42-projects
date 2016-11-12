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
	header("Location: index.php");
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<?php
		$prev = false;
		$categories = mysqli_query($db, "SELECT id, name FROM categories ORDER BY name");
		while ($category = mysqli_fetch_array($categories)) {
			if ($prev) {
				echo "<br />";
			} else {
				$prev = true;
			}
			echo "<h1>".$category['name']."</h1><hr><table class='article_table'>";
			$articles = mysqli_query($db, "SELECT * FROM articles WHERE id_category = ".$category['id']." ORDER BY rand() LIMIT 2");
			while ($article = mysqli_fetch_array($articles)) {
				?>
				<tr>
					<td class="photo"><img alt='<?php echo $article['name']; ?>' src='<?php echo $article['photo']; ?>' title='<?php echo $article['name']; ?>' /></td>
					<td class="name"><?php echo $article['name']; ?></td>
					<td class="price"><?php echo $article['price']; ?>&euro;</td>
					<td class="add"><a href="index.php?add=<?php echo $article['id']; ?>">Ajouter au panier</a></td>
				</tr>
				<?php
			}
			echo "</table>";
		}
		?>
	</div>
</div>