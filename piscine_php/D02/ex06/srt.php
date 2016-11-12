#!/usr/bin/php
<?php
if ($argc == 2) {
	if (!file_exists($argv[1]))
		exit(0);
	if (($file = fopen($argv[1], "r")) == FALSE)
		exit(0);
	$ret = array();
	while (($str = fgets($file))) {
		$time = trim(fgets($file));
		$word = trim(fgets($file));
		fgets($file);
		$ret[$time] = $word;
	}
	fclose($file);
	ksort($ret);
	$i = 1;
	$len_max = count($ret);
	foreach($ret as $key => $val) {
		echo $i."\n".$key."\n".$val."\n";
		if ($i != $len_max)
			echo "\n";
		$i++;
	}
}
?>
