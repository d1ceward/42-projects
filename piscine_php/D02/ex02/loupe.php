#!/usr/bin/php
<?php
	if ($argc != 2)
		exit(1);
	$str = null;
	if (!file_exists($argv[1]) || !($str = file_get_contents($argv[1])))
		exit(1);
	function f1($pm) {
		return (preg_replace_callback(array('/(>)(.*?)(<)/s', '/(title=")(.*?)(")/s'), function ($m) { return ($m[1] . strtoupper($m[2]).$m[3]); }, $pm[0]));
	}
	echo (preg_replace_callback('/<a href=(.*?)>(.*?)<\/a>/s', "f1", $str));
?>
