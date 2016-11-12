<?php
session_start();
include_once 'auth.php';
if (!$_POST["login"] || !$_POST["passwd"] || !auth($_POST["login"], $_POST["passwd"]))
	echo "ERROR\n<br /><a href='index.html'>Back</a>\n";
else {
	$_SESSION["loggued_on_user"] = $_POST["login"];
?>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>login</title>
</head>
<body>
	<iframe name="chat" src="chat.php" width="100%" height="550px"></iframe>
	<iframe name="speak" src="speak.php" width="100%" height="50px"></iframe>
</body>
</html>
<?php
}
?>
