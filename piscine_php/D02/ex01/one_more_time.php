#!/usr/bin/php
<?php
	function format_error(){
		echo "Worng Format\n";
		exit(1);
	}

	if ($argc != 2) exit(1);
	if(!preg_match_all("/^[a-zA-Z]{3,9}\\s\\d{1,2}\\s.{3,10}\\s\\d{4}\\s\\d{1,2}:\\d{2}:\\d{2}$/i", $argv[1], $m))
		format_error();

	$str = $argv[1];
	$tabMonth = array("/\s[Jj]anvier\s/" => "/01/", "/\s[Ff]evrier\s/" => "/02/", "/\s[Mm]ars\s/" => "/03/", "/\s[Aa]vril\s/" => "/04/", "/\s[Mm]ai\s/" => "/05/", "/\s[Jj]uin\s/" => "/06/",
		"/\s[Jj]uillet\s/" => "/07/", "/\s[Aa]out\s/" => "/08/", "/\s[Ss]eptembre\s/" => "/09/", "/\s[Oo]ctobre\s/" => "/10/", "/\s[Nn]ovembre\s/" => "/11/", "/\s[Dd]ecembre\s/" => "/12/");


	for ($i = 0; $i < 12; $i++){
		$str = preg_replace(array_keys($tabMonth)[$i], array_values($tabMonth)[$i], $str);
	}

	$tabDay = array("/[Dd]imanche\s/" => "", "/[Ll]undi\s/" => "", "/[Mm]ardi\s/" => "", "/[Mm]ercredi\s/" => "", "/[Jj]eudi\s/" => "", "/[Vv]endredi\s/" => "", "/[Ss]amedi\s/" => "");

	for ($i = 0; $i < 7; $i++){
		$str = preg_replace(array_keys($tabDay)[$i], array_values($tabDay)[$i], $str);
	}
	date_default_timezone_set("Europe/Paris");
	$parsed = date_create_from_format("d/m/Y H:i:s", $str);

	if ($parsed === FALSE)
		wrong_format();
	else {
		echo $parsed->getTimestamp()."\n";
	}
 ?>
