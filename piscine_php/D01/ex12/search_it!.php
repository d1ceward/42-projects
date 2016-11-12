#!/usr/bin/php
<?php
if (($tmp = $argc) > 2) {
	$tmp--;
	$key = $argv[1];
	$len = strlen($key);
	while ($tmp > 1) {
		if (strpos($argv[$tmp], $key) === 0 && $argv[$tmp][$len] === ':') {
			echo substr($argv[$tmp], strpos($argv[$tmp], ":") + 1)."\n";
			$tmp = -1;
		}
		$tmp--;
	}
}
?>