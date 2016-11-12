#!/usr/bin/php
<?php
function ft_split($str) {
	return array_filter(explode(" ", implode(" ", array_filter(explode("\t", $str), "strlen"))), "strlen");
}

if (count($argv) > 1) {
	$array = array();
	$i = 1;
	$len = count($argv);
	while ($i < $len) {
		$array2 = ft_split($argv[$i]);
		foreach ($array2 as $str) {
			$array[] = $str;
		}
		$i++;
	}
	sort($array);
	foreach ($array as $str) {
		echo $str."\n";
	}
}
?>
