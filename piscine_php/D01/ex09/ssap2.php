#!/usr/bin/php
<?php
function ft_split($str) {
	return array_filter(explode(" ", implode(" ", array_filter(explode("\t", $str), "strlen"))), "strlen");
}

function cmp($a, $b) {
	$i = 0;
	$a = strtolower($a);
	$b = strtolower($b);
	if ($a == $b) {
		return 0;
	}
	while ($a[$i] && $a[$i] == $b[$i]) {
		$i++;
	}
	$a = ord($a[$i]);
	$b = ord($b[$i]);
	if ($a >= 48 && $a <= 57) {
		$a = $a + 1000;
	} else if ($a < 97 || $a > 122) {
		$a = $a + 10000;
	}
	if ($b >= 48 && $b <= 57) {
		$b = $b + 1000;
	} else if ($b < 97 || $b > 122) {
		$b = $b + 10000;
	}
	return $a < $b ? -1 : 1;
}

$i = 1;
$array = array();
while ($i < $argc) {
	$strs = ft_split($argv[$i]);
	foreach ($strs as $str) {
		$array[] = $str;
	}
	$i++;
}
usort($array, "cmp");
$i = 0;
$len = count($array);
while ($i < $len) {
	echo $array[$i++]."\n";
}
?>
