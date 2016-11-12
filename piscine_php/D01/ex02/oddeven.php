#!/usr/bin/php
<?php
function isEven($n) {
	return !($n & 1);
}

$str = "";
while (42) {
	echo "Entrez un nombre: ";
	$str = fgets(STDIN);
	if (feof(STDIN) === TRUE) {
		echo "\n";
		break;
	}
	$str = rtrim($str);
	if (is_numeric($str) && strpos($str, ".") === FALSE) {
		if (isEven($str)) {
			echo "Le chiffre ".$str." est Pair\n";
		} else {
				echo "Le chiffre ".$str." est Impair\n";
		}
	} else {
		echo "'".$str."' n'est pas un chiffre\n";
	}
}
?>