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

function auth($login, $passwd) {
	if (($users = file_get_contents("../private/passwd")) === FALSE)
		return FALSE;
	$users = unserialize($users);
	if (($pos = check_user($users, $login)) < 0)
		return FALSE;
	if (hash("whirlpool", $passwd) != $users[$pos]["passwd"])
		return FALSE;
	return TRUE;
}
?>