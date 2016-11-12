<?php
function check_user($array, $user) {
	$i = 0;
	foreach ($array as $username) {
		if ($username["login"] === $user)
			return $i;
		$i++;
	}
	return -1;
}

if (!$_POST["submit"] || $_POST["submit"] != "OK" || !$_POST["login"] || !$_POST["oldpw"] || !$_POST["newpw"])
	echo "ERROR\n";
else {
	if (($users = file_get_contents("../private/passwd")) == FALSE)
		$users = array();
	else
		$users = unserialize($users);
	if (($pos = check_user($users, $_POST["login"])) < 0)
		echo "ERROR\n";
	else {
		if (hash("whirlpool", $_POST["oldpw"]) != $users[$pos]["passwd"])
			echo "ERROR\n";
		else {
			$array["login"] = $_POST["login"];
			$array["passwd"] = hash("whirlpool", $_POST["newpw"]);
			$users[$pos] = $array;
			file_put_contents("../private/passwd", serialize($users));
			echo "OK\n";
			header("Location: index.html");
		}
	}
}
?>