#!/usr/bin/php
<?php
	function rm($path) {
		if (is_dir($path)){
			$files = array_diff(scandir($path), array( '.', '..'));
			foreach ($files as $file) {
				rm(realpath($path) . '/' . $file);
			}
			return rmdir($path);
		}
		else if (is_file($path))
			return unlink($path);
		return false;
	}

	if ($argc != 2)
		return;
	$html = null;
	$imgs = null;
	$ch = null;
	$ch = curl_init($argv[1]);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	$html = curl_exec($ch);
	curl_close($ch);
	if (!preg_match_all( '/<img.*?src ?= ?["\'"](?P<img_url>.*?)["\']/si', $html, $imgs))
		return;
	$path = substr(strrchr($argv[1], "/" ), 1);
	rm($path);
	if (!mkdir($path))
		return;
	foreach ($imgs['img_url'] as $imglink) {
		$imglink = preg_replace('/^\/\//', "http://", $imglink);
		$imgname = substr(strrchr( $imglink, "/" ), 1);
		$ch = curl_init($imglink);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$img = curl_exec($ch);
		$fp = fopen($path . '/' . $imgname, 'w');
		fwrite($fp, $img);
	}
?>
