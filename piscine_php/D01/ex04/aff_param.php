#!/usr/bin/php
<?php
$len = count($argv);
if ($len > 1) {
	$i = 1;
	while ($i < $len) {
		echo $argv[$i++]."\n";
	}
}
?>
