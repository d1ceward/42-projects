<?php
if (isset($_POST["id"]) && is_numeric($_POST["id"]) && isset($_POST["str"])) {
	$content = file_get_contents("list.csv");
	$content = $content.$_POST["id"].";".$_POST["str"]."\n";
	file_put_contents("list.csv", $content);
}
?>