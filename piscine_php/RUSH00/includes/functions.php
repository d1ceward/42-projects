<?php
function ft_secure($str) {
	return str_replace('\\', '/', htmlentities(htmlspecialchars(trim($str)), ENT_QUOTES));
}

function crypt_pwd($pwd) {
	return hash("whirlpool", $pwd);
}
?>