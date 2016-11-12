#!/usr/bin/php
<?php
if ($argc == 3) {
	if (!file_exists($argv[1]))
		exit(0);
	if (($file = fopen($argv[1], "r")) == FALSE)
		exit(0);
	$keys = fgets($file);
	$keys = trim($keys);
	$keys = explode(";", $keys);
	$index = array_search($argv[2], $keys);
	$lines = array();
	while (($line = fgets($file))) {
		$line = trim($line);
		$lines[] = $line;
	}
	fclose($file);
	$i = 0;
	foreach ($keys as $key) {
		${$key} = array();
		foreach ($lines as $line) {
			$line = explode(";", $line);
			${$key}[$line[$index]] = $line[$i];
		}
		$i++;
	}
	while (1) {
		echo "Entrez votre commande: ";
		$str = fgets(STDIN);
		if (feof(STDIN) == TRUE) {
			echo "\n";
			break;
		}
		eval($str);
	}
}
?>
