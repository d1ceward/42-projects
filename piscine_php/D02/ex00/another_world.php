#!/usr/bin/php
<?php
	if($argc >= 2)
		echo preg_replace('/(^\\s)|(\\s$)/', '', preg_replace('!\s+!', ' ', $argv[1]));
?>
