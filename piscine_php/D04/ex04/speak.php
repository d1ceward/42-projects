<?php
session_start();
date_default_timezone_set('Europe/Paris');
if ($_SESSION["loggued_on_user"] && $_SESSION["loggued_on_user"] != "") {
	if ($_POST && $_POST["msg"]) {
		if (file_exists("../private/chat"))
		{
			$msgs = file_get_contents("../private/chat", LOCK_EX);
			$msgs = unserialize($msgs);
		}
		$msg["login"] = $_SESSION["loggued_on_user"];
		$msg["time"] = time();
		$msg["msg"] = $_POST["msg"];
		$msgs[] = $msg;
		file_put_contents("../private/chat", serialize($msgs));
	}
?>
<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>speak</title>
</head>
<body>
	<form action="speak.php" method="POST">
		<label for="msg">Message:</label>
		<input name="msg" value="" autofocus/>
		<input type="submit" value="OK" name="submit"/>
	</form>
	<script langage="javascript">top.frames["chat"].location = "chat.php";</script>
</body>
</html>
<?php
} else
	echo "ERROR\n";
?>