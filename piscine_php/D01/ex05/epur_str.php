#!/usr/bin/php
<?php
function ft_split($str) {
	return array_filter(explode(" ", implode(" ", array_filter(explode("\t", $str), "strlen"))), "strlen");
}

if (count($argv) == 2) {
	$array = ft_split($argv[1]);
	$array = array_values($array);
	$len = count($array);
	$i = 0;
	while ($i < $len) {
		echo $array[$i];
		if ($i != $len - 1) {
			echo " ";
		}
		$i++;
	}
	echo "\n";
}
?>
