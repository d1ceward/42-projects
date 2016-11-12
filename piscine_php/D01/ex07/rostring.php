#!/usr/bin/php
<?php
function ft_split($str) {
	return array_filter(explode(" ", $str), "strlen");
}

if (count($argv) > 1) {
	$array = array();
	$i = 1;
	$len = count($argv);
	$array = array_values(ft_split($argv[1]));
	$array[] = $array[0];
	array_shift($array);
	$len = count($array);
	$i = 0;
	while ($i < $len) {
		echo $array[$i];
		if ($i != $len - 1) {
			echo " ";
		} else {
			echo "\n";
		}
		$i++;
	}
}
?>
