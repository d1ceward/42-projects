#!/usr/bin/php
<?php
function remove_spaces($str) {
	$str = str_replace(' ', '', $str);
	return str_replace("\t", '', $str);
}

if ($argc == 4) {
	$nb1 = remove_spaces($argv[1]);
	$operator = remove_spaces($argv[2]);
	$nb2 = remove_spaces($argv[3]);
	switch ($operator) {
		case "+":
			$ret = $nb1 + $nb2;
			break;
		case "-":
			$ret = $nb1 - $nb2;
			break;
		case "*":
			$ret = $nb1 * $nb2;
			break;
		case "/":
			$ret = $nb1 / $nb2;
			break;
		case "%":
			$ret = $nb1 % $nb2;
			break;
	}
	echo $ret."\n";
} else {
	echo "Incorrect Parameters\n";
}
?>