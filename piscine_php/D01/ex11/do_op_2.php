#!/usr/bin/php
<?php
function remove_spaces($str) {
	$str = str_replace(' ', '', $str);
	return str_replace("\t", '', $str);
}

function do_op($str, $operator) {
	$array = explode($operator, $str);
	if (count($array) == 2) {
		if (!is_numeric($array[0]) || !is_numeric($array[1])) {
			echo "Syntax Error\n";
			exit(0);
		}
		$nb1 = $array[0];
		$nb2 = $array[1];
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
		echo "Syntax Error\n";
	}
}

if ($argc == 2) {
	$str = remove_spaces($argv[1]);
	if ((bool)strpos($str, "+") && strrpos($str, "+") == strpos($str, "+")) {
		do_op($str, "+");
	} else if ((bool)strpos($str, "-") && strrpos($str, "-") == strpos($str, "-")) {
		do_op($str, "-");
	} else if ((bool)strpos($str, "*") && strrpos($str, "*") == strpos($str, "*")) {
		do_op($str, "*");
	} else if ((bool)strpos($str, "/") && strrpos($str, "/") == strpos($str, "/")) {
		do_op($str, "/");
	} else if ((bool)strpos($str, "%") && strrpos($str, "%") == strpos($str, "%")) {
		do_op($str, "%");
	} else {
		echo "Syntax Error\n";
	}
} else {
	echo "Incorrect Parameters\n";
}
?>