<?php
function check_user($array, $user) {
	foreach ($array as $username) {
		if ($username["login"] === $user)
			return TRUE;
	}
	return FALSE;
}

if (!$_POST["submit"] || $_POST["submit"] != "OK" || !$_POST["login"] || !$_POST["passwd"])
	echo "ERROR\n";
else {
	if (!file_exists("../private"))
		mkdir("../private");
	if (file_exists("../private/passwd"))
		$users = unserialize(file_get_contents("../private/passwd"));
	else
		$users = array();
	if (check_user($users, $_POST["login"]))
		echo "ERROR\n";
	else {
		$array["login"] = $_POST["login"];
		$array["passwd"] = hash("whirlpool", $_POST["passwd"]);
		$users[] = $array;
		file_put_contents("../private/passwd", serialize($users));
		echo "OK\n";
	}
}
?>