<?php
$id = ceil(isset($_GET['cat']) ? $_GET['cat'] : NULL);
if (isset($_GET['add'])) {
	$id_add = ceil($_GET['add']);
	if (!isset($_SESSION['basket']))
		$_SESSION['basket'] = array();
	if (isset($_SESSION['basket'][$id_add])) {
		$_SESSION['basket'][$id_add]++;
	} else {
		$_SESSION['basket'][$id_add] = 1;
	}
	header("Location: index.php?page=category&cat=".$id);
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<?php
		if (mysqli_num_rows(($res = mysqli_query($db, "SELECT * FROM categories WHERE id = '".$id."' LIMIT 1"))) > 0)
		{
			$cat = mysqli_fetch_array($res);
			echo "<h1>".$cat['name']."</h1><hr><table class='article_table'>";
			$articles = mysqli_query($db, "SELECT * FROM articles WHERE id_category = ".$cat['id']."");
			while ($article = mysqli_fetch_array($articles)) {
				?>
				<tr>
					<td class="photo"><img alt='<?php echo $article['name']; ?>' src='<?php echo $article['photo']; ?>' title='<?php echo $article['name']; ?>' /></td>
					<td class="name"><?php echo $article['name']; ?></td>
					<td class="price"><?php echo $article['price']; ?>&euro;</td>
					<td class="add"><a href="index.php?page=category&cat=<?php echo $id; ?>&add=<?php echo $article['id']; ?>">Ajouter au panier</a></td>
				</tr>
				<?php
			}
			echo "</table>";
		} else
			header("Location: index.php?page=404");
		?>
	</div>
</div>