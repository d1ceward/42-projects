<?php
session_start();
if ($_GET)
{
	if ($_GET["login"] && $_GET["submit"] && $_GET["submit"] == "OK")
		$_SESSION["login"] = $_GET["login"];
	if ($_GET["passwd"] && $_GET["submit"] && $_GET["submit"] == "OK")
		$_SESSION["passwd"] = $_GET["passwd"];
}
?>
<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>session</title>
</head>
<body>
	<form action="index.php" method="GET">
		<label for="login">Identifiant:</label>
		<input type="text" name="login" value="<?php if ($_SESSION && $_SESSION["login"]) echo $_SESSION["login"]; ?>"/>
		<br>
		<label for="passwd">Mot de passe:</label>
		<input type="password" name="passwd" value="<?php if ($_SESSION && $_SESSION["passwd"]) echo $_SESSION["passwd"]; ?>"/>
		<br>
		<input type="submit" value="OK" name="submit">
	</form>
	</body>
</html>